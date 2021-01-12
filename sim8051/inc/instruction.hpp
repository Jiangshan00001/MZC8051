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

#ifndef _INSTRUCTION_HPP
#define _INSTRUCTION_HPP

#include <cstdint>
#include <vector>
#include <string>
#include "memory.hpp"
#include "alu.hpp"

static const std::vector<std::string> constraintNames = {"R0", "R1", "R2", "R3", "R4", "R5", "R6", "R7", "A", "DPL", "DPH", "C", "NC"};

enum Constraints {R0, R1, R2, R3, R4, R5, R6, R7, RegisterA, DPL, DPH, C, NC, NumConstraints};

enum class ConstraintType
{
  None, // We make no assumptions about the register contents
  Interval, // The register is between 'low' and 'high'
  RegisterInterval, // Only used for C and !C - the flag is set if register 'reg' is between 'low' and 'high'
  Memory, // Register 'reg' is the contents of a memory location between 'low' and 'high'
  True, // Only used for C and !C - the flag must be set
  False // Only used for C and !C - the flag cannot be set
};

class Constraint
{
  public:
    int low, high, reg;
    ConstraintType type;
    void Print(std::string name);
    void SetNone();
    void SetInterval(int low, int high);
    void SetMemory(int low, int high);
    void SetRegisterInterval(int register, int low, int high);
    void SetTrue();
    void SetFalse();
    Constraint();
};

class RegisterConstraints
{
  public:
    Constraint constraints[NumConstraints];
    int constraintRef[NumConstraints];
    void Print();
    void Clear();
    RegisterConstraints();
    Constraint& GetConstraint(enum Constraints);
    void SetNone(enum Constraints);
    void SetInterval(enum Constraints, int low, int high);
    void SetMemory(enum Constraints, int low, int high);
    void SetRegisterInterval(enum Constraints, int register, int low, int high);
    void SetAlias(enum Constraints, enum Constraints);
    void SetTrue(enum Constraints);
    void SetFalse(enum Constraints);
    int GetAlias(enum Constraints c);
  private:
    int CreateRef(enum Constraints c);
};

class Instruction
{
  protected:
    std::uint8_t operands;
    std::uint8_t opcode;
    Alu &alu;
  public:
    Instruction(Alu&, std::uint8_t opcode);
    Instruction(Alu&);
    virtual bool IsJump(std::uint16_t address) const;
    virtual std::vector<std::uint16_t> GetNextAddresses(std::uint16_t address) const;
    virtual std::string Disassemble(std::uint16_t address) const = 0;
    virtual void Execute() const;
    virtual void UpdateConstraints(RegisterConstraints &c, std::uint16_t address, std::uint16_t destination);
    std::uint8_t GetOperands() const;
    void IncPC() const;
    std::uint8_t cycles;
};

#endif
