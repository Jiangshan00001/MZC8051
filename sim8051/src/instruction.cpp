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

#include <cstdint>
//#include <ncurses.h>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>
#include "instruction.hpp"

void Constraint::Print(std::string name)
{
  if (type == ConstraintType::None)
  {
    return;
  }

  printf("%s ", name.c_str());
  if (type == ConstraintType::True)
  {
    printf("True");
  }
  else if (type == ConstraintType::False)
  {
    printf("False");
  }
  else if (type == ConstraintType::Memory)
  {
    printf("Memory: %d %d", low, high);
  }
  else if (type == ConstraintType::Interval)
  {
    printf("Interval: %d %d", low, high);
  }
  else if (type == ConstraintType::RegisterInterval)
  {
    printf("Register: %d %d %d", reg, low, high);
  }
  printf("\n");
}

void Constraint::SetNone()
{
  type = ConstraintType::None;
}

void Constraint::SetInterval(int l, int h)
{
  type = ConstraintType::Interval;
  low = l;
  high = h;
}

void Constraint::SetMemory(int l, int h)
{
  type = ConstraintType::Memory;
  low = l;
  high = h;
}

void Constraint::SetRegisterInterval(int r, int l, int h)
{
  type = ConstraintType::RegisterInterval;
  reg = r;
  low = l;
  high = h;
}

void Constraint::SetTrue()
{
  type = ConstraintType::True;
}

void Constraint::SetFalse()
{
  type = ConstraintType::False;
}

Constraint::Constraint()
{
  SetNone();
}

void RegisterConstraints::Clear()
{
  for (int i = 0; i < NumConstraints; i++)
  {
    constraintRef[i] = i;
  }
}

RegisterConstraints::RegisterConstraints()
{
  Clear();
}

void RegisterConstraints::Print()
{
  for (int i = 0; i < NumConstraints; i++)
  {
    constraints[constraintRef[i]].Print(constraintNames[i]);
  }
}

// Returns the first found alias of the given constraint
int RegisterConstraints::GetAlias(enum Constraints c)
{
  for (int i = 0; i < NumConstraints; i++)
  {
    if (i != c && constraintRef[i] == constraintRef[c])
    {
      return i;
    }
  }

  return -1;
}

// Find an available slot in the Constraint array
// Either the existing one (if not shared), or a new one.
int RegisterConstraints::CreateRef(enum Constraints c)
{
  int count = 0;
  bool occupied[NumConstraints];

  for (int i = 0; i < NumConstraints; i++)
  {
    occupied[i] = false;
  }

  for (int i = 0; i < NumConstraints; i++)
  {
    occupied[constraintRef[i]] = true;
    if (constraintRef[i] == constraintRef[c])
    {
      count++;
    }
  }

  // If the current constraint isn't shared, we're done.
  if (count == 1)
  {
    return c;
  }

  // Otherwise, pick the first available one
  for (int i = 0; i < NumConstraints; i++)
  {
    if (!occupied[i])
    {
      return i;
    }
  }

  // We'll never reach this point, there will always be an available constraint
  return 0;
}

void RegisterConstraints::SetNone(enum Constraints c)
{
  constraintRef[c] = CreateRef(c);
  constraints[constraintRef[c]].SetNone();
}

void RegisterConstraints::SetInterval(enum Constraints c, int low, int high)
{
  constraintRef[c] = CreateRef(c);
  constraints[constraintRef[c]].SetInterval(low, high);
}

void RegisterConstraints::SetMemory(enum Constraints c, int low, int high)
{
  constraintRef[c] = CreateRef(c);
  constraints[constraintRef[c]].SetMemory(low, high);
}

void RegisterConstraints::SetRegisterInterval(enum Constraints c, int reg, int low, int high)
{
  constraintRef[c] = CreateRef(c);
  constraints[constraintRef[c]].SetRegisterInterval(reg, low, high);
}

void RegisterConstraints::SetAlias(enum Constraints a, enum Constraints b)
{
  constraintRef[a] = constraintRef[b];
}

void RegisterConstraints::SetTrue(enum Constraints c)
{
  constraintRef[c] = CreateRef(c);
  constraints[constraintRef[c]].SetTrue();
}

void RegisterConstraints::SetFalse(enum Constraints c)
{
  constraintRef[c] = CreateRef(c);
  constraints[constraintRef[c]].SetFalse();
}

Constraint& RegisterConstraints::GetConstraint(enum Constraints c)
{
  return constraints[constraintRef[c]];
}

Instruction::Instruction(Alu& a, std::uint8_t o) : opcode(o), alu(a)
{
    operands = 0;
}

Instruction::Instruction(Alu& a) : opcode(0), alu(a)
{
    operands = 0;
}

std::uint8_t Instruction::GetOperands() const
{
  return operands;
}

void Instruction::Execute() const
{
  printf("Instruction %x at address %4.4x not implemented\n", opcode, alu.GetPC());
  throw new std::runtime_error("instruction not implemented");
}

void Instruction::IncPC() const
{
  alu.SetPC(alu.GetPC() + 1 + operands);
}

bool Instruction::IsJump(std::uint16_t address) const
{
  return false;
}

std::vector<std::uint16_t> Instruction::GetNextAddresses(std::uint16_t address) const
{
  return {static_cast<std::uint16_t>(address + 1 + operands)};
}

void Instruction::UpdateConstraints(RegisterConstraints &c, std::uint16_t address, std::uint16_t destination)
{
  c.Clear();
}
