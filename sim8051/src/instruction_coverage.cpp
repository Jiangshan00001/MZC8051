/*
 * Copyright (C) 2016 Sensative AB
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>

#include "alu.hpp"
#include "instruction_coverage.hpp"
#include "symbol_table.hpp"

BasicBlock::BasicBlock(int n, std::uint16_t address) : number(n), firstAddress(address), lastAddress(address)
{
}

void InstructionCoverage::Initialize(Alu &alu)
{
  std::set<std::pair<BasicBlock*, std::uint16_t>> waiting;
  constexpr const int IndirectJumpOpcode = 0x73; // JMP @DPTR

  basicBlockCount = 0;
  basicBlocks.erase(basicBlocks.begin(), basicBlocks.end());
  reachable.erase(reachable.begin(), reachable.end());
  for (int i = 0; i < 65536; i++)
  {
    executionCount[i] = 0;
  }
  for (std::uint16_t vector : {0x0, 0x3, 0xb, 0x13, 0x1b, 0x23, 0x2b})
  {
    // Let's assume an unused interrupt vector entry is zeroed out.
    if (alu.flash.Read(vector) || alu.flash.Read(vector+1))
    {
      BasicBlock *currentBlock = new BasicBlock(++basicBlockCount, vector);
      basicBlocks[currentBlock->number] = currentBlock;
      reachable[vector] = currentBlock->number;
      waiting.insert(std::make_pair(currentBlock, vector));
    }
  }

  while (!waiting.empty())
  {
    while (!waiting.empty())
    {
      std::set<std::pair<BasicBlock*, std::uint16_t>>::iterator elt = waiting.begin(); // Pick an arbitrary element
      std::uint16_t address = elt->second;
      BasicBlock *currentBlock = elt->first;
      waiting.erase(elt);
      if (address >= alu.flash.GetSize())
      {
        continue;
      }

      bool isJump = false;
      bool isVisited = false;
      while (!isJump && !isVisited)
      {
        if (alu.IsJump(address))
        {
          isJump = true;
        }
        else
        {
          std::vector<uint16_t> nextAddresses = alu.GetNextAddresses(address);
          address = nextAddresses[0];

          if (reachable[address])
          {
            isVisited = true;
          }
          else
          {
            reachable[address] = currentBlock->number;
            currentBlock->lastAddress = address;
            address = *(nextAddresses.begin());
          }
        }
      }

      if (isJump)
      {
        std::vector<uint16_t> nextAddresses = alu.GetNextAddresses(address);

        for (uint16_t next : nextAddresses)
        {
          // Already visited -> if instruction is not first address in basic block, split it
          if (reachable[next])
          {
            BasicBlock *referencedBlock = basicBlocks[reachable[next]];

            // If the jump destination is the first address of a block,
            // we just need to add the edges.
            if (next == referencedBlock->firstAddress)
            {
              currentBlock->outEdges.push_back(referencedBlock->number);
              referencedBlock->inEdges.push_back(currentBlock->number);
              continue;
            }

            // New block starts with referenced address
            // Original block is shortened
            BasicBlock *newBlock = new BasicBlock(++basicBlockCount, next);

            for (int addr = next; addr <= referencedBlock->lastAddress; addr++)
            {
              if (reachable[addr] == referencedBlock->number)
              {
                reachable[addr] = newBlock->number;
              }
            }
            basicBlocks[newBlock->number] = newBlock;
            newBlock->lastAddress = referencedBlock->lastAddress;

            referencedBlock->lastAddress = next - 1;
            newBlock->outEdges = referencedBlock->outEdges;
            referencedBlock->outEdges.erase(referencedBlock->outEdges.begin(), referencedBlock->outEdges.end());
            newBlock->inEdges.push_back(referencedBlock->number);
            referencedBlock->outEdges.push_back(newBlock->number);
          }
          else
          {
            BasicBlock *newBlock = new BasicBlock(++basicBlockCount, next);
            reachable[next] = newBlock->number;

            basicBlocks[newBlock->number] = newBlock;
            currentBlock->outEdges.push_back(newBlock->number);
            newBlock->inEdges.push_back(currentBlock->number);
            waiting.insert(std::make_pair(newBlock, next));
          }
        }
      }
      else if (isVisited)
      {
        BasicBlock *referencedBlock = basicBlocks[reachable[address]];
        currentBlock->outEdges.push_back(referencedBlock->number);
        referencedBlock->inEdges.push_back(currentBlock->number);
      }
    }

    for (std::map<int,BasicBlock*>::iterator it = basicBlocks.begin(); it != basicBlocks.end(); it++)
    {
      BasicBlock *block = it->second;
      std::uint16_t addr = block->firstAddress;

      bool foundIndirectJump = false;
      while (addr <= block->lastAddress)
      {
        if (alu.flash.Read(addr) == IndirectJumpOpcode)
        {
          foundIndirectJump = true;
        }      
        if (alu.IsJump(addr))
          break;
        std::vector<std::uint16_t> next = alu.GetNextAddresses(addr);
        addr = next[0];
      }
      if (foundIndirectJump)
      {
        BasicBlock *refBlock = block;
        std::vector<BasicBlock*> blocks;

        while (refBlock->inEdges.size() == 1)
        {
          blocks.push_back(basicBlocks[refBlock->inEdges[0]]);
          refBlock = basicBlocks[refBlock->inEdges[0]];
        }

        RegisterConstraints c;

        // Calculate exit constraints of referencing chain of blocks
        for (int i = blocks.size() - 1; i >= 0; i--)
        {
          std::uint16_t addr = blocks[i]->firstAddress;

          while (addr <= blocks[i]->lastAddress && alu.flash.Read(addr) != IndirectJumpOpcode)
          {
            alu.UpdateConstraints(c, addr, i?blocks[i-1]->firstAddress:block->firstAddress);
            std::vector<std::uint16_t> next = alu.GetNextAddresses(addr);
            addr = next[0];
          }
        }

        // Using entry constraints to block using indirect jump, calculate constraints at call site
        addr = block->firstAddress;
        while (addr <= block->lastAddress)
        {
          if (alu.IsJump(addr))
          {
            break;
          }
          alu.UpdateConstraints(c, addr, block->firstAddress);
          std::vector<std::uint16_t> next = alu.GetNextAddresses(addr);
          addr = next[0];
        }

        if (c.GetConstraint(DPL).type == ConstraintType::Memory && c.GetConstraint(DPH).type == ConstraintType::Memory)
        {
          // Add the switch labels as destinations (if not already visited)
          for (int i = c.GetConstraint(DPL).low; i <= c.GetConstraint(DPL).high; i++)
          {
            addr = alu.flash.Read(i) + alu.flash.Read(c.GetConstraint(DPH).low + i - c.GetConstraint(DPL).low) * 256;

            if (reachable[addr])
            {
              continue;
            }

            BasicBlock *newBlock = new BasicBlock(++basicBlockCount, addr);
            reachable[addr] = newBlock->number;
            basicBlocks[newBlock->number] = newBlock;
            block->outEdges.push_back(newBlock->number);
            newBlock->inEdges.push_back(block->number);
            waiting.insert(std::make_pair(newBlock, addr));
          }
        }
      }
    }
  }
}

void InstructionCoverage::GetCoverage(int &totalInstructions, int &executedInstructions)
{
  totalInstructions = 0;
  executedInstructions = 0;

  for (int i = 0; i < 65536; i++)
  {
    if (reachable[i])
    {
      totalInstructions++;
    }
    if (executionCount[i])
    {
      executedInstructions++;
    }
  }
}

void InstructionCoverage::InstructionExecuted(std::uint16_t address)
{
  executionCount[address]++;
}
