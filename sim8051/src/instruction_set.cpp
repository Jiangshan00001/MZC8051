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

#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>
#include "instruction.hpp"
#include "instruction_set.hpp"
#include "symbol_table.hpp"
#include "exceptions.hpp"


// Bits one and two set -> register indirect operand
constexpr int IndirectOperandMask = 0x06;

// Register indirect operand, register is indicated by bit zero
constexpr int IndirectRegisterMask = 0x01;

// Register operand, register is lower three bits
constexpr int RegisterMask = 0x07;

// Lower three bits indicate operand type
constexpr int BitwiseOperandMask = 0x07;

constexpr int ImmediateOperandMemory = 0x03;
constexpr int ImmediateOperand = 0x04;
constexpr int AddressOperand = 0x05;

// High bits of opcode contain operation
constexpr int BitwiseOpMask = 0xf0;
constexpr int BitwiseOr = 0x40;
constexpr int BitwiseAnd = 0x50;
constexpr int BitwiseXor = 0x60;

static void PrintAddress(std::stringstream &ss, std::uint8_t address)
{
  bool found;
  std::string name;

  SymbolTable::GetInstance().LookupAddress(address, name, found);
  if (found)
  {
    ss << name;
  }
  else
  {
    ss << std::setw(2) << (int) address;
  }
}

static void PrintAddress(std::stringstream &ss, std::uint16_t address)
{
  bool found;
  std::string name;

  SymbolTable::GetInstance().LookupAddress(address, name, found);
  if (found)
  {
    ss << name;
  }
  else
  {
    ss << std::setw(4) << (int) address;
  }
}

ACALL::ACALL(Alu &a, std::uint8_t opcode) : Instruction(a, opcode)
{
  operands = 1;
  cycles = 2;
}

std::string ACALL::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << "ACALL ";
  ss << (int) alu.flash.Read(address+1);
  return ss.str();
}

void ACALL::Execute() const
{
  std::uint8_t sp = alu.GetSP();
  std::uint8_t addr = alu.flash.Read(alu.GetPC() + 1);

  alu.iram.Write(sp + 1, (alu.GetPC() + 1 + operands) % 256);
  alu.iram.Write(sp + 2, (alu.GetPC() + 1 + operands) / 256);
  alu.SetSP(sp + 2);

  alu.SetPC((alu.flash.Read(alu.GetPC()) & 0x3) * 256 + addr);
}

/* 0x24 and 0x34 */
AddImmediate::AddImmediate(Alu &a, std::uint8_t opcode, bool c) : AdditionHelper(a, opcode, c)
{
  operands = 1;
}

std::string AddImmediate::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << "ADD";
  if (carry)
  {
    ss << "C";
  }
  ss << " A, #";
  ss << (int) alu.flash.Read(address+1);
  return ss.str();
}

void AddImmediate::UpdateConstraints(RegisterConstraints &c, std::uint16_t address, std::uint16_t destination)
{
  std::uint8_t operand = alu.flash.Read(address + 1);
  Constraint &aConstraint = c.GetConstraint(RegisterA);
  Constraint &cConstraint = c.GetConstraint(C);
  Constraint &ncConstraint = c.GetConstraint(NC);

  if (carry)
  {
    c.SetNone(C);
    c.SetNone(NC);
  }
  else if (aConstraint.type == ConstraintType::Interval && c.GetAlias(RegisterA) >= 0)
  {
    if (operand >= aConstraint.low && operand <= aConstraint.high)
    {
      cConstraint.SetRegisterInterval(c.GetAlias(RegisterA), 0xff - operand + 1, aConstraint.high);
      ncConstraint.SetRegisterInterval(c.GetAlias(RegisterA), aConstraint.low, 0xff - operand);
    }
    else if (aConstraint.high + operand <= 255)
    {
      c.SetFalse(C);
      c.SetTrue(NC);
    }
    else if (aConstraint.low + operand > 255)
    {
      c.SetTrue(C);
      c.SetFalse(NC);
    }
    else
    {
      c.SetNone(C);
      c.SetNone(NC);
    }
    int low = (aConstraint.low + operand) % 256;
    int high = (aConstraint.high + operand) % 256;
    if (low > high)
    {
      c.SetNone(RegisterA);
    }
    else
    {
      c.SetInterval(RegisterA, low, high);
    }
  }
  else
  {
    c.SetNone(RegisterA);
    c.SetNone(C);
    c.SetNone(NC);
  }
}

void AddImmediate::Execute() const
{
  Helper(alu.flash.Read(alu.GetPC() + 1));
}

AdditionHelper::AdditionHelper(Alu &alu, std::uint8_t opcode, bool c): Instruction(alu, opcode), carry(c)
{
  cycles = 1;
}

void AdditionHelper::Helper(std::uint16_t data) const
{ 
  if (carry && alu.GetC())
  {
    data++;
  }
 
  std::uint16_t result = data + alu.GetA();

  if (result > 255)
  {
    alu.SetC();
  }
  else
  {
    alu.ClrC();
  }

  result = (data & 0xf) + (alu.GetA() & 0xf);
  if (result > 0xf)
  {
    alu.SetAC();
  }
  else
  {
    alu.ClrAC();
  }

  std::int16_t signedResult = (int8_t) data + (int8_t) alu.GetA();
  if (signedResult > 127 || signedResult < -128)
  {
    alu.SetOV();
  }
  else
  {
    alu.ClrOV();
  }

  alu.SetA(data + alu.GetA());
  IncPC();
}

/* 0x25 and 0x35 */
AddMemory::AddMemory(Alu &a, std::uint8_t opcode, bool c) : AdditionHelper(a, opcode, c)
{
  operands = 1;
}

std::string AddMemory::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << "ADD A";
  if (carry)
  {
    ss << "C";
  }
  ss << ",";
  ss << (int) alu.flash.Read(address+1);
  return ss.str();
}

void AddMemory::Execute() const
{
  Helper(alu.Read(alu.flash.Read(alu.GetPC() + 1)));
}

AddIndirectRegister::AddIndirectRegister(Alu &a, std::uint8_t o, bool carry) : AdditionHelper(a, o, carry)
{
  operands = 0;
}

std::string AddIndirectRegister::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << "ADD A";
  if (carry)
  {
    ss << "C";
  }
  ss << ", @R" << (int) (opcode & IndirectRegisterMask);
  return ss.str();
}

void AddIndirectRegister::Execute() const
{
  std::uint16_t data = alu.Read(alu.GetReg(opcode & RegisterMask));

  Helper(data);
}

AddRegister::AddRegister(Alu &a, std::uint8_t o, bool c) : AdditionHelper(a, o, c)
{
  operands = 0;
}

std::string AddRegister::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << "ADD";
  if (carry)
  {
    ss << "C ";
  }
  ss << "A, R" << (int) (opcode & RegisterMask);
  return ss.str();
}

void AddRegister::Execute() const
{
  std::uint16_t data = alu.GetReg(opcode & RegisterMask);

  Helper(data);
}

AJMP::AJMP(Alu &a, std::uint8_t opcode) : Instruction(a, opcode)
{
  operands = 1;
  cycles = 2;
}

std::string AJMP::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << "AJMP ";
  ss << (int) alu.flash.Read(address+1);
  return ss.str();
}

void AJMP::Execute() const
{
  std::uint8_t addr = alu.flash.Read(alu.GetPC() + 1);

  alu.SetPC(alu.flash.Read((alu.GetPC()) & 0x3) * 256 + addr);
}

ANL_82::ANL_82(Alu &a) : Instruction(a)
{
  opcode = 0x82;
  operands = 1;
  cycles = 1;
}

std::string ANL_82::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << "ANL C, ";
  ss << (int) alu.flash.Read(address+1);
  return ss.str();
}

void ANL_82::Execute() const
{
    std::int8_t bitaddr = alu.flash.Read(alu.GetPC() + 1);

    //ANL C, bit
    bool bit_val = this->alu.ReadBit(bitaddr);
    if(!bit_val)
    {
        this->alu.ClrC();
    }
    IncPC();
}

ANL_B0::ANL_B0(Alu &a) : Instruction(a)
{
  opcode = 0xB0;
  operands = 1;
  cycles = 1;
}

std::string ANL_B0::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << "ANL C, /";
  ss << (int) alu.flash.Read(address+1);
  return ss.str();
}

void ANL_B0::Execute() const
{
    std::int8_t bitaddr = alu.flash.Read(alu.GetPC() + 1);

    //ANL C, /bit
    bool bit_val = this->alu.ReadBit(bitaddr);
    if(bit_val)
    {
        this->alu.ClrC();
    }
    IncPC();
}

CJNEHelper::CJNEHelper(Alu &a, std::uint8_t opcode) : Instruction(a, opcode)
{
  operands = 2;
  cycles = 2;
}

void CJNEHelper::Helper(std::uint8_t operand1, std::uint8_t operand2) const
{
  std::int8_t reladdr = alu.flash.Read(alu.GetPC() + 2);

  if (operand1 != operand2)
  {
    alu.SetPC(alu.GetPC() + 1 + operands + reladdr);
  }
  else
  {
    IncPC();
  }

  if (operand1 < operand2)
  {
    alu.SetC();
  }
  else
  {
    alu.ClrC();
  }
}

bool CJNEHelper::IsJump(std::uint16_t address) const
{
  std::int8_t reladdr = alu.flash.Read(address + 2);

  // If the relative address is zero, we 'jump' to the following instruction.
  // This is not a jump from a control flow point of view, so we need
  // to check the relative address to determine whether to return true or false.

  if (reladdr)
  {
    return true;
  }
  else
  {
    return false;
  }
}

std::vector<std::uint16_t> CJNEHelper::GetNextAddresses(std::uint16_t address) const
{
  std::int8_t reladdr = alu.flash.Read(address + 2);

  return {static_cast<std::uint16_t>(address + 1 + operands + reladdr), static_cast<std::uint16_t>(address + 1 + operands)};
}

CJNE_B4::CJNE_B4(Alu &a, std::uint8_t opcode) : CJNEHelper(a, opcode)
{
}

std::string CJNE_B4::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << "CJNE A, #";
  ss << (int) alu.flash.Read(address+1) << ", " << (int) alu.flash.Read(address+2);
  return ss.str();
}

void CJNE_B4::Execute() const
{
  Helper(alu.GetA(), alu.flash.Read(alu.GetPC() + 1));
}

CJNE_B5::CJNE_B5(Alu &a, std::uint8_t opcode) : CJNEHelper(a, opcode)
{
}

std::string CJNE_B5::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << "CJNE A, ";
  ss << (int) alu.flash.Read(address+1) << ", " << (int) alu.flash.Read(address+2);
  return ss.str();
}

void CJNE_B5::Execute() const
{
  std::uint8_t addr = alu.flash.Read(alu.GetPC() + 1);

  Helper(alu.GetA(), alu.Read(addr));
}

CJNE_B6::CJNE_B6(Alu &a, std::uint8_t opcode) : CJNEHelper(a, opcode)
{
}

std::string CJNE_B6::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::hex;
  ss << "CJNE @R0, #";
  ss << std::setw(2) << (int) alu.flash.Read(address+1) << ", " << std::setw(2) << (int) alu.flash.Read(address+2);
  return ss.str();
}

void CJNE_B6::Execute() const
{
  Helper(alu.Read(alu.GetReg(opcode & IndirectRegisterMask)), alu.flash.Read(alu.GetPC() + 1));
}

CJNE_B7::CJNE_B7(Alu &a, std::uint8_t opcode) : CJNEHelper(a, opcode)
{
}

std::string CJNE_B7::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << "CJNE @R1, #";
  ss << (int) alu.flash.Read(address+1) << ", " << (int) alu.flash.Read(address+2);
  return ss.str();
}

void CJNE_B7::Execute() const
{
  Helper(alu.Read(alu.GetReg(opcode & IndirectRegisterMask)), alu.flash.Read(alu.GetPC() + 1));
}

CJNERegister::CJNERegister(Alu &a, std::uint8_t opcode) : CJNEHelper(a, opcode)
{
}

std::string CJNERegister::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::hex;
  ss << "CJNE R" << (int) (opcode & RegisterMask) << ", #";
  ss << std::setw(2) << (int) alu.flash.Read(address+1) << ", " << std::setw(2) << (int) alu.flash.Read(address+2);
  return ss.str();
}

void CJNERegister::Execute() const
{
  Helper(alu.GetReg(opcode & RegisterMask), alu.flash.Read(alu.GetPC() + 1));
}

void CJNERegister::UpdateConstraints(RegisterConstraints &c, std::uint16_t address, std::uint16_t destination)
{
  std::uint8_t reg = opcode & RegisterMask;
  std::int8_t reladdr = alu.flash.Read(address + 2);
  std::int8_t operand = alu.flash.Read(address + 1);
  Constraint &cConstraint = c.GetConstraint(C);
  Constraint &ncConstraint = c.GetConstraint(NC);
  Constraint &registerConstraint = c.GetConstraint(static_cast<enum Constraints>(reg));

  // If relative address is zero, the only effect of the instruction is setting the C flag
  if (reladdr == 0)
  {
    if (registerConstraint.type == ConstraintType::None)
    {
      cConstraint.SetRegisterInterval(reg, 0, operand - 1);
      ncConstraint.SetRegisterInterval(reg, operand, 0xff);
    }
    else if (registerConstraint.type == ConstraintType::Interval &&
             registerConstraint.low < operand && registerConstraint.high >= operand)
    {
      cConstraint.SetRegisterInterval(reg, registerConstraint.low, operand - 1);
      ncConstraint.SetRegisterInterval(reg, operand, registerConstraint.high);
    }
    else
    {
      cConstraint.SetNone();
      ncConstraint.SetNone();
    }
  }
}

CLR_C2::CLR_C2(Alu &a) : Instruction(a)
{
  opcode = 0xC2;
  operands = 1;
  cycles = 1;
}

std::string CLR_C2::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::hex;
  ss << "CLR ";
  ss << alu.GetBitAddressName((int) alu.flash.Read(address+1));
  return ss.str();
}

void CLR_C2::Execute(void) const
{
  std::uint8_t bitAddr = alu.flash.Read(alu.GetPC() + 1);

  alu.WriteBit(bitAddr, false);
  alu.SetPC(alu.GetPC() + 1 + operands);
}

CLR_C3::CLR_C3(Alu &a) : Instruction(a)
{
  opcode = 0xC3;
  operands = 0;
  cycles = 1;
}

std::string CLR_C3::Disassemble(std::uint16_t address) const
{
  return "CLR C";
}

void CLR_C3::Execute() const
{
  alu.ClrC();
  IncPC();
}

CLR_E4::CLR_E4(Alu &a) : Instruction(a)
{
  opcode = 0xE4;
  operands = 0;
  cycles = 1;
}

std::string CLR_E4::Disassemble(std::uint16_t address) const
{
  return "CLR A";
}

void CLR_E4::Execute(void) const
{
  alu.SetA(0);
  IncPC();
}

void CLR_E4::UpdateConstraints(RegisterConstraints &c, std::uint16_t address, std::uint16_t destination)
{
  c.SetInterval(RegisterA, 0, 0);
}

CPL_F4::CPL_F4(Alu &a) : Instruction(a)
{
  opcode = 0xF4;
  operands = 0;
  cycles = 1;
}

std::string CPL_F4::Disassemble(std::uint16_t address) const
{
  return "CPL A";
}

void CPL_F4::Execute() const
{
  alu.SetA(0xff - alu.GetA());

  IncPC();
}

CPL_B3::CPL_B3(Alu &a) : Instruction(a)
{
  opcode = 0xB3;
  operands = 0;
  cycles = 1;
}

std::string CPL_B3::Disassemble(std::uint16_t address) const
{
  return "CPL C";
}

void CPL_B3::Execute() const
{
  if (alu.GetC())
  {
    alu.ClrC();
  }
  else
  {
    alu.SetC();
  }
  IncPC();
}

CPL_B2::CPL_B2(Alu &a) : Instruction(a)
{
  opcode = 0xB2;
  operands = 1;
  cycles = 1;
}

std::string CPL_B2::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << "CPL ";
  ss << alu.flash.Read(address+1);
  return ss.str();
}

void CPL_B2::Execute() const
{
  std::uint16_t address = alu.flash.Read(alu.GetPC() + 1);

  alu.WriteBit(address, !alu.ReadBit(address));

  IncPC();
}

DA_D4::DA_D4(Alu &a) : Instruction(a)
{
  opcode = 0xD4;
  operands = 0;
  cycles = 1;
}

std::string DA_D4::Disassemble(std::uint16_t address) const
{
  return "DA";
}

DEC_15::DEC_15(Alu &a) : Instruction(a)
{
  opcode = 0x15;
  operands = 1;
  cycles = 1;
}

std::string DEC_15::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << "DEC ";
  ss << alu.flash.Read(address+1);
  return ss.str();
}

void DEC_15::Execute() const
{
  //alu.flash.Write(alu.GetPC() + 1, alu.flash.Read(alu.GetPC() + 1) - 1);
    uint8_t val = alu.GetReg(alu.flash.Read(alu.GetPC() + 1));
    alu.SetReg(alu.flash.Read(alu.GetPC() + 1), val-1);

  IncPC();
}

DEC_14::DEC_14(Alu &a) : Instruction(a)
{
  opcode = 0x14;
  operands = 0;
  cycles = 1;
}

std::string DEC_14::Disassemble(std::uint16_t address) const
{
  return "DEC A";
}

void DEC_14::Execute() const
{
  alu.SetA(alu.GetA() - 1);
  IncPC();
}

DIV_84::DIV_84(Alu &a) : Instruction(a)
{
  opcode = 0x84;
  operands = 0;
  cycles = 4;
}

std::string DIV_84::Disassemble(std::uint16_t address) const
{
    return "DIV AB";
}

void DIV_84::Execute() const
{
    if(this->alu.GetB()==0)
    {
        this->alu.SetOV();
        IncPC();
        return;
    }


    unsigned ret = this->alu.GetA()/this->alu.GetB();
    unsigned modr = this->alu.GetA()%this->alu.GetB();
    this->alu.SetA(ret);
    this->alu.SetB(modr);

    IncPC();
}

DJNZ_D5::DJNZ_D5(Alu &a) : Instruction(a)
{
  opcode = 0xD5;
  operands = 2;
  cycles = 2;
}

std::string DJNZ_D5::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << "DJNZ ";
  ss << (int) alu.flash.Read(address+1) << ", " << (int) alu.flash.Read(address+2);
  return ss.str();
}

void DJNZ_D5::Execute() const
{
  std::uint8_t addr = alu.flash.Read(alu.GetPC() + 1);
  std::int8_t reladdr = alu.flash.Read(alu.GetPC() + 2);

  alu.Write(addr, alu.Read(addr) - 1);
  if (alu.Read(addr))
  {
    alu.SetPC(alu.GetPC() + 1 + operands + reladdr);
  }
  else
  {
    IncPC();
  }
}

DJNZRegister::DJNZRegister(Alu &a, std::uint8_t opcode) : Instruction(a, opcode)
{
  operands = 1;
  cycles = 2;
}

std::string DJNZRegister::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << "DJNZ R" << (int) (opcode & RegisterMask) << ", ";
  ss << (int) alu.flash.Read(address+1);
  return ss.str();
}

void DJNZRegister::Execute() const
{
  std::int8_t reladdr = alu.flash.Read(alu.GetPC() + 1);

  alu.SetReg(opcode & RegisterMask, alu.GetReg(opcode & RegisterMask) - 1);

  if (alu.GetReg(opcode & RegisterMask))
  {
    alu.SetPC(alu.GetPC() + 1 + operands + reladdr);
  }
  else
  {
    IncPC();
  }
}

bool DJNZRegister::IsJump(std::uint16_t address) const
{
  return true;
}

std::vector<std::uint16_t> DJNZRegister::GetNextAddresses(std::uint16_t address) const
{
  std::int8_t reladdr = alu.flash.Read(address + 1);

  return {static_cast<std::uint16_t>(address + 1 + operands + reladdr), static_cast<std::uint16_t>(address + 1 + operands)};
}

INC_5::INC_5(Alu &a) : Instruction(a)
{
  opcode = 5;
  operands = 1;
  cycles = 1;
}

std::string INC_5::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << "INC ";
  ss << (int) alu.flash.Read(address+1);
  return ss.str();
}

void INC_5::Execute() const
{
  std::uint8_t address = alu.flash.Read(alu.GetPC() + 1);

  alu.Write(address, alu.Read(address) + 1);
  IncPC();
}

INC_4::INC_4(Alu &a) : Instruction(a)
{
  opcode = 4;
  operands = 0;
  cycles = 1;
}

std::string INC_4::Disassemble(std::uint16_t address) const
{
  return "INC A";
}

void INC_4::Execute() const
{
  alu.SetA(alu.GetA() + 1);
  IncPC();
}

constexpr int IncDecMask = 0x10;
constexpr int Dec = 0x10;

IncDecIndirectRegister::IncDecIndirectRegister(Alu &a, std::uint8_t opcode): Instruction(a, opcode)
{
  cycles = 1;
}

std::string IncDecIndirectRegister::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  if ((opcode & IncDecMask) == Dec)
  {
    ss << "DEC";
  }
  else
  {
    ss << "INC";
  }
  ss << " @R" << (int) (opcode & IndirectRegisterMask);
  return ss.str();
}

void IncDecIndirectRegister::Execute() const
{
  std::uint8_t addr = alu.GetReg(opcode & IndirectRegisterMask);

  if ((opcode & IncDecMask) == Dec)
  {
    alu.Write(addr, alu.Read(addr) - 1);
  }
  else
  {
    alu.Write(addr, alu.Read(addr) + 1);
  }
  IncPC();
}

BitwiseOperation::BitwiseOperation(Alu &a, std::uint8_t opcode) : Instruction(a, opcode)
{
  cycles = 1;
  if ((opcode & IndirectOperandMask) == IndirectOperandMask)
  {
    operands = 0;
  }
  else if ((opcode & BitwiseOperandMask) == ImmediateOperand)
  {
    operands = 1;
  }
  else if ((opcode & BitwiseOperandMask) == AddressOperand)
  {
    operands = 1;
  }
}

std::string BitwiseOperation::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  if ((opcode & BitwiseOpMask) == BitwiseAnd)
  {
    ss << "ANL";
  }
  else if ((opcode & BitwiseOpMask) == BitwiseOr)
  {
    ss << "ORL";
  }
  else if ((opcode & BitwiseOpMask) == BitwiseXor)
  {
    ss << "XRL";
  }
  if ((opcode & IndirectOperandMask) == IndirectOperandMask)
  {  
    ss << " A, @R" << (int) (opcode & IndirectRegisterMask);
  }
  else if ((opcode & BitwiseOperandMask) == ImmediateOperand)
  {
    ss << " A, #";
    ss << std::setw(2) << (int) alu.flash.Read(address+1);
  }
  else if ((opcode & BitwiseOperandMask) == AddressOperand)
  {
    ss << " A, ";
    ss << std::setw(2) << (int) alu.flash.Read(address+1);
  }
  return ss.str();
}

void BitwiseOperation::Execute() const
{
  std::uint8_t operand;

  if ((opcode & IndirectOperandMask) == IndirectOperandMask)
  {
    operand = alu.Read(opcode & IndirectRegisterMask);
  }
  else if ((opcode & BitwiseOperandMask) == ImmediateOperand)
  {
    operand = alu.flash.Read(alu.GetPC() + 1);
  }
  else if ((opcode & BitwiseOperandMask) == AddressOperand)
  {
    operand = alu.Read(alu.flash.Read(alu.GetPC() + 1));
  }


  if ((opcode & BitwiseOpMask) == BitwiseAnd)
  {
    alu.SetA(alu.GetA() & operand);
  }
  else if ((opcode & BitwiseOpMask) == BitwiseOr)
  {
    alu.SetA(alu.GetA() | operand);
  }
  else if ((opcode & BitwiseOpMask) == BitwiseXor)
  {
    alu.SetA(alu.GetA() ^ operand);
  }
  IncPC();
}

IncRegister::IncRegister(Alu &a, std::uint8_t opcode): Instruction(a, opcode)
{
  cycles = 1;
  operands = 0;

}

std::string IncRegister::Disassemble(std::uint16_t address) const

{
  std::stringstream ss;
  ss << "INC R" << (int) (opcode & RegisterMask);
  return ss.str();
}

void IncRegister::Execute() const
{
  alu.SetReg(opcode & RegisterMask, alu.GetReg(opcode & RegisterMask) + 1);
  IncPC();
}

DecRegister::DecRegister(Alu &a, std::uint8_t opcode): Instruction(a, opcode)
{
  cycles = 1;
}

std::string DecRegister::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << "DEC R" << (int) (opcode & RegisterMask);
  return ss.str();
}

void DecRegister::Execute() const
{
  alu.SetReg(opcode & RegisterMask, alu.GetReg(opcode & RegisterMask) - 1);
  IncPC();
}

INC_A3::INC_A3(Alu &a) : Instruction(a)
{
  opcode = 0xA3;
  operands = 0;
  cycles = 1;
}

std::string INC_A3::Disassemble(std::uint16_t address) const
{
  return "INC DPTR";
}

void INC_A3::Execute() const
{
  alu.SetDPTR(alu.GetDPTR() + 1);
  IncPC();
}

CondJump::CondJump(Alu &a, std::uint8_t opcode) : Instruction(a, opcode)
{
}

std::vector<std::uint16_t> CondJump::GetNextAddresses(std::uint16_t address) const
{
  std::int8_t relAddr = alu.flash.Read(address + operands);

  return {static_cast<std::uint16_t>(address + 1 + operands + relAddr), static_cast<std::uint16_t>(address + 1 + operands)};
}

bool CondJump::IsJump(std::uint16_t address) const
{
  return true;
}

JBC_10::JBC_10(Alu &a, std::uint8_t opcode) : CondJump(a, opcode)
{
  operands = 2;
  cycles = 2;
}

std::string JBC_10::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << "JBC ";
  ss << (int) alu.flash.Read(address+1) << ", " << (int) alu.flash.Read(address+2);
  return ss.str();
}

void JBC_10::Execute() const
{
  std::uint8_t bitAddr = alu.flash.Read(alu.GetPC() + 1);
  std::int8_t relAddr = alu.flash.Read(alu.GetPC() + 2);

  if (alu.ReadBit(bitAddr))
  {
    alu.WriteBit(bitAddr, false);
    alu.SetPC(alu.GetPC() + 1 + operands + relAddr);
  }
  else
  {
    IncPC();
  }
}

constexpr int InvertFlag = 0x10;

JC::JC(Alu &a, std::uint8_t opcode) : CondJump(a, opcode)
{
  operands = 1;
  cycles = 2;
}

std::string JC::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << "J";
  if (opcode & InvertFlag)
  {
    ss << "N";
  }
  ss << "C ";
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << (int) alu.flash.Read(address+1);
  return ss.str();
}

void JC::Execute() const
{
  bool condition = alu.GetC();

  if (opcode & InvertFlag)
  {
    condition = !condition;
  }
  if (condition)
  {
    std::int8_t reladdr = alu.flash.Read(alu.GetPC() + 1);
    alu.SetPC(alu.GetPC() + 1 + operands + reladdr);
  }
  else
  {
    IncPC();
  }
}

JMP_73::JMP_73(Alu &a) : Instruction(a)
{
  opcode = 0x73;
  operands = 0;
  cycles = 2;
}

std::string JMP_73::Disassemble(std::uint16_t address) const
{
  return "JMP @A+DPTR";
}

bool JMP_73::IsJump(std::uint16_t address) const
{
  return true;
}

void JMP_73::Execute() const
{
  alu.SetPC(alu.GetDPTR() + alu.GetA());
}

std::vector<std::uint16_t> JMP_73::GetNextAddresses(std::uint16_t address) const
{ 
  // Now we miss a lot of instructions. We'll reach them by following the labels generated by SDCC.
  return {};
}

JB::JB(Alu &a, std::uint8_t opcode) : CondJump(a, opcode)
{
  operands = 2;
  cycles = 2;
}

std::string JB::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << "J";
  if (opcode & InvertFlag)
  {
    ss << "N";
  }
  ss << "B";
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << (int) alu.flash.Read(address+1) << ", " << (int) alu.flash.Read(address+2);
  return ss.str();
}

void JB::Execute() const
{
  std::uint8_t bitAddr = alu.flash.Read(alu.GetPC() + 1);
  std::int8_t relAddr = alu.flash.Read(alu.GetPC() + 2);
  bool condition = alu.ReadBit(bitAddr);

  if (opcode & InvertFlag)
  {
    condition = !condition;
  }
  if (condition)
  {
    alu.SetPC(alu.GetPC() + 1 + operands + relAddr);
  }
  else
  {
    IncPC();
  }
}

void JC::UpdateConstraints(RegisterConstraints &c, std::uint16_t address, std::uint16_t destination)
{
  std::uint16_t carrySetDestination;
  std::uint16_t carryClearDestination;
  std::int8_t reladdr = alu.flash.Read(address + 1);

  if (opcode & InvertFlag)
  {
    carryClearDestination = address + 1 + operands + reladdr;
    carrySetDestination = address + 1 + operands;
  }
  else
  {
    carrySetDestination = address + 1 + operands + reladdr;
    carryClearDestination = address + 1 + operands;
  }

  Constraint &cConstraint = c.GetConstraint(C);
  Constraint &ncConstraint = c.GetConstraint(NC);

  if (cConstraint.type == ConstraintType::RegisterInterval && destination == carrySetDestination)
  {
    c.SetInterval(static_cast<enum Constraints>(cConstraint.reg), cConstraint.low, cConstraint.high);
  }
  else if (ncConstraint.type == ConstraintType::RegisterInterval && destination == carryClearDestination)
  {
    c.SetInterval(static_cast<enum Constraints>(ncConstraint.reg), ncConstraint.low, ncConstraint.high);
  }
}

JZ::JZ(Alu &a, std::uint8_t opcode) : CondJump(a, opcode)
{
  operands = 1;
  cycles = 2;
}

std::string JZ::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << "J";
  if (opcode & InvertFlag)
  {
    ss << "N";
  } 
  ss << "Z ";
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << (int) alu.flash.Read(address+1);
  return ss.str();
}

void JZ::Execute() const
{
  bool condition = alu.GetA() == 0;

  if (opcode & InvertFlag)
  {
    condition = !condition;
  }
 
  if (condition)
  {
    std::int8_t reladdr = alu.flash.Read(alu.GetPC() + 1);
    alu.SetPC(alu.GetPC() + 1 + operands + reladdr);
  }
  else
  {
    IncPC();
  }
}

LCALL_12::LCALL_12(Alu &a) : Instruction(a)
{
  opcode = 0x12;
  operands = 2;
  cycles = 2;
}

std::string LCALL_12::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << "LCALL ";
  PrintAddress(ss, (uint16_t) (alu.flash.Read(address + 1) * 256 + alu.flash.Read(address + 2)));
  return ss.str();
}

void LCALL_12::Execute() const
{
  std::uint8_t sp = alu.GetSP();
  std::uint8_t high = alu.flash.Read(alu.GetPC() + 1);
  std::uint8_t low = alu.flash.Read(alu.GetPC() + 2);

  alu.iram.Write(sp + 1, (alu.GetPC() + 3) % 256);
  alu.iram.Write(sp + 2, (alu.GetPC() + 3) / 256);
  alu.SetSP(sp + 2);

  alu.SetPC(low + 256 * high);
}

bool LCALL_12::IsJump(std::uint16_t address) const
{
  return true;
}

std::vector<std::uint16_t> LCALL_12::GetNextAddresses(std::uint16_t address) const
{ 
  return {static_cast<std::uint16_t>(address + 1 + operands),
          static_cast<std::uint16_t>(256 * alu.flash.Read(address + 1) + alu.flash.Read(address + 2))};
}

LJMP_2::LJMP_2(Alu &a) : Instruction(a)
{
  opcode = 0x2;
  operands = 2;
  cycles = 2;
}

std::string LJMP_2::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::hex;
  ss << "LJMP ";
  PrintAddress(ss, (uint16_t) (alu.flash.Read(address + 1) * 256 + alu.flash.Read(address + 2)));
  return ss.str();
}

void LJMP_2::Execute() const
{
  alu.SetPC(256 * alu.flash.Read(alu.GetPC() + 1) + alu.flash.Read(alu.GetPC() + 2));
}

bool LJMP_2::IsJump(std::uint16_t address) const
{
  return true;
}

std::vector<std::uint16_t> LJMP_2::GetNextAddresses(std::uint16_t address) const
{
  return {static_cast<std::uint16_t>(256 * alu.flash.Read(address + 1) + alu.flash.Read(address + 2))};
}

MOV_90::MOV_90(Alu &a) : Instruction(a)
{
  opcode = 0x90;
  operands = 2;
  cycles = 1;
}

std::string MOV_90::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::hex;
  ss << "MOV DPTR, #";
  ss << std::setw(2) << (int) alu.flash.Read(address+1);
  ss << std::setw(2) << (int) alu.flash.Read(address+2);
  return ss.str();
}

void MOV_90::Execute() const
{
  alu.SetDPTR(alu.flash.Read(alu.GetPC() + 1) * 256 + alu.flash.Read(alu.GetPC() + 2));
  alu.SetPC(alu.GetPC() + 1 + operands);
}

void MOV_90::UpdateConstraints(RegisterConstraints &c, std::uint16_t address, std::uint16_t destination)
{
  c.SetInterval(DPL, alu.flash.Read(address+1), alu.flash.Read(address+1));
  c.SetInterval(DPH, alu.flash.Read(address+2), alu.flash.Read(address+2));
}

MOV_75::MOV_75(Alu &a) : Instruction(a)
{
  opcode = 0x75;
  operands = 2;
  cycles = 2;
}

std::string MOV_75::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;

  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << "MOV ";
  PrintAddress(ss, alu.flash.Read(address+1));
  ss << ", #" << std::setw(2) << (int) alu.flash.Read(address+2);
  return ss.str();
}

void MOV_75::Execute() const
{
  std::uint8_t address = alu.flash.Read(alu.GetPC() + 1);
  std::uint8_t data = alu.flash.Read(alu.GetPC() + 2);

  alu.Write(address, data);
  IncPC();
}

MOV_85::MOV_85(Alu &a) : Instruction(a)
{
  opcode = 0x85;
  operands = 2;
  cycles = 2;
}

std::string MOV_85::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << "MOV ";
  ss << std::setw(2) << (int) alu.flash.Read(address+1) << ", " << std::setw(2) << (int) alu.flash.Read(address+2);
  return ss.str();
}

void MOV_85::Execute() const
{
  std::uint8_t data = alu.Read(alu.flash.Read(alu.GetPC() + 1));

  alu.Write(alu.flash.Read(alu.GetPC() + 2), data);
  IncPC();
}

MovRegisterIndirectImmediate::MovRegisterIndirectImmediate(Alu &a, std::uint8_t opcode) : Instruction(a, opcode)
{
  operands = 1;
  cycles = 2;
}

std::string MovRegisterIndirectImmediate::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << "MOV @R" << (int) (opcode & IndirectRegisterMask) << ", #";
  PrintAddress(ss, alu.flash.Read(address+1));
  return ss.str();
}

void MovRegisterIndirectImmediate::Execute() const
{
  alu.Write(alu.GetReg(opcode & IndirectRegisterMask), alu.flash.Read(alu.GetPC() + 1));
  IncPC();
}

MOV_74::MOV_74(Alu &a) : Instruction(a)
{
  opcode = 0x74;
  operands = 1;
  cycles = 1;
}

std::string MOV_74::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << "MOV A, #";
  ss << (int) alu.flash.Read(address+1);
  return ss.str();
}

void MOV_74::Execute() const
{
  alu.SetA(alu.flash.Read(alu.GetPC() + 1));
  IncPC();
}

MOV_E5::MOV_E5(Alu &a) : Instruction(a)
{
  opcode = 0xE5;
  operands = 1;
  cycles = 1;
}

std::string MOV_E5::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << "MOV A, ";
  PrintAddress(ss, alu.flash.Read(address+1));
  return ss.str();
}

void MOV_E5::Execute() const
{
  std::uint8_t address = alu.flash.Read(alu.GetPC() + 1);

  alu.SetA(alu.Read(address));
  IncPC();
}

MOV_A2::MOV_A2(Alu &a) : Instruction(a)
{
  opcode = 0xA2;
  operands = 1;
  cycles = 1;
}

std::string MOV_A2::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << "MOV C, ";
  ss << alu.GetBitAddressName(alu.flash.Read(address+1));
  return ss.str();
}

void MOV_A2::Execute(void) const
{
  std::uint8_t bitAddr = alu.flash.Read(alu.GetPC() + 1);

  if (alu.ReadBit(bitAddr))
  {
    alu.SetC();
  }
  else
  {
    alu.ClrC();
  }
  IncPC();
}

MovRegisterImmediate::MovRegisterImmediate(Alu &a, std::uint8_t opcode) : Instruction(a, opcode)
{
  operands = 1;
  cycles = 1;
}

std::string MovRegisterImmediate::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << "MOV R" << (int) (opcode & RegisterMask) << ", #";
  ss << std::setw(2) << std::hex << (int) alu.flash.Read(address+1);
  return ss.str();
}

void MovRegisterImmediate::Execute() const
{
  alu.SetReg(opcode & RegisterMask, alu.flash.Read(alu.GetPC() + 1));
  IncPC();
}

MovRegisterA::MovRegisterA(Alu &a, std::uint8_t opcode) : Instruction(a, opcode)
{
  operands = 0;
  cycles = 1;
}

std::string MovRegisterA::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << "MOV R" << (int) (opcode & RegisterMask) << ", A";
  return ss.str();
}

void MovRegisterA::Execute() const
{
  alu.SetReg(opcode & RegisterMask, alu.GetA());
  IncPC();
}

void MovRegisterA::UpdateConstraints(RegisterConstraints &c, std::uint16_t address, std::uint16_t destination)
{
  c.SetAlias(static_cast<enum Constraints>(opcode & RegisterMask), RegisterA);
}

MovRegisterAddress::MovRegisterAddress(Alu &a, std::uint8_t opcode) : Instruction(a, opcode)
{
  operands = 1;
  cycles = 2;
}

std::string MovRegisterAddress::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << "MOV R" << (int) (opcode & RegisterMask) << ", ";
  PrintAddress(ss, alu.flash.Read(address+1));
  return ss.str();
}

void MovRegisterAddress::Execute() const
{
  std::uint8_t address = alu.flash.Read(alu.GetPC() + 1);

  alu.SetReg(opcode & RegisterMask, alu.Read(address));
  IncPC();
}

MOV_92::MOV_92(Alu &a) : Instruction(a)
{
  opcode = 0x92;
  operands = 1;
  cycles = 2;
}

std::string MOV_92::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << "MOV ";
  ss << alu.GetBitAddressName((int) alu.flash.Read(address+1)) << ", C";
  return ss.str();
}

void MOV_92::Execute(void) const
{
  std::uint8_t bitAddr = alu.flash.Read(alu.GetPC() + 1);

  alu.WriteBit(bitAddr, alu.GetC());
  IncPC();
}

MovMemoryIndirectRegister::MovMemoryIndirectRegister(Alu &a, std::uint8_t opcode) : Instruction(a, opcode)
{
  operands = 1;
  cycles = 2;
}

std::string MovMemoryIndirectRegister::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << "MOV ";
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << (int) alu.flash.Read(address+1) << ", @R" << (int) (opcode & IndirectRegisterMask);
  return ss.str();
}

void MovMemoryIndirectRegister::Execute() const
{
  alu.Write(alu.flash.Read(alu.GetPC() + 1), alu.Read(alu.GetReg(opcode & IndirectRegisterMask)));
  IncPC();
}

MovAddressRegister::MovAddressRegister(Alu &a, std::uint8_t opcode) : Instruction(a, opcode)
{
  operands = 1;
  cycles = 2;
}

std::string MovAddressRegister::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << "MOV " << (int) alu.flash.Read(address+1) << ", R" << (int) (opcode & RegisterMask);
  return ss.str();
}

void MovAddressRegister::Execute() const
{
  alu.Write(alu.flash.Read(alu.GetPC()+ 1), alu.GetReg(opcode & RegisterMask));
  IncPC();
}

MovARegister::MovARegister(Alu &a, std::uint8_t opcode) : Instruction(a, opcode)
{
  operands = 0;
  cycles = 1;
}

std::string MovARegister::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << "MOV A, R" << (int) (opcode & RegisterMask);
  return ss.str();
}

void MovARegister::UpdateConstraints(RegisterConstraints &c, std::uint16_t address, std::uint16_t destination)
{
  c.SetAlias(RegisterA, static_cast<enum Constraints>(opcode & RegisterMask));
}

void MovARegister::Execute() const
{
  alu.SetA(alu.GetReg(opcode & RegisterMask));
  IncPC();
}

MOV_F5::MOV_F5(Alu &a) : Instruction(a)
{
  opcode = 0xF5;
  operands = 1;
  cycles = 1;
}

std::string MOV_F5::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << "MOV ";
  PrintAddress(ss, alu.flash.Read(address+1));
  ss << ", A";
  return ss.str();
}

void MOV_F5::Execute() const
{
  std::uint8_t addr = alu.flash.Read(alu.GetPC() + 1);

  alu.Write(addr, alu.GetA());
  IncPC();
}

void MOV_F5::UpdateConstraints(RegisterConstraints &c, std::uint16_t address, std::uint16_t destination)
{
  std::uint8_t addr = alu.flash.Read(address + 1);

  if (addr == alu.sfrDPL.address)
  {
    c.SetAlias(DPL, RegisterA);
  }
  else if (addr == alu.sfrDPH.address)
  {
    c.SetAlias(DPH, RegisterA);
  }
}

MovIndirect::MovIndirect(Alu &a, std::uint8_t opcode) : Instruction(a, opcode)
{
  operands = 0;
  cycles = 1;
}

std::string MovIndirect::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << "MOV @R";
  ss << (int) (opcode & IndirectRegisterMask);
  ss << ", A";
  return ss.str();
}

void MovIndirect::Execute() const
{
  alu.iram.Write(alu.GetReg(opcode & IndirectRegisterMask), alu.GetA());
  IncPC();
}

MovIndirectFromMem::MovIndirectFromMem(Alu &a, std::uint8_t opcode) : Instruction(a, opcode)
{
  operands = 1;
  cycles = 2;
}

std::string MovIndirectFromMem::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << "MOV @R";
  ss << (int) (opcode & IndirectRegisterMask);
  ss << ", ";
  ss << std::hex << std::setw(2) << (int) alu.flash.Read(alu.GetPC() + 1);
  return ss.str();
}

void MovIndirectFromMem::Execute() const
{
  alu.iram.Write(alu.GetReg(opcode & IndirectRegisterMask), alu.iram.Read(alu.flash.Read(alu.GetPC() + 1)));
  IncPC();
}

MovIndirectRegister::MovIndirectRegister(Alu &a, std::uint8_t o) : Instruction(a, o)
{
  operands = 0;
  cycles = 1;
}

std::string MovIndirectRegister::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << "MOV A, @R" << (int) (opcode & IndirectRegisterMask);
  return ss.str();
}

void MovIndirectRegister::Execute() const
{
  alu.SetA(alu.Read(alu.GetReg(opcode & IndirectRegisterMask)));
  IncPC();
}

MOVC_93::MOVC_93(Alu &a) : Instruction(a)
{
  opcode = 0x93;
  operands = 0;
  cycles = 2;
}

std::string MOVC_93::Disassemble(std::uint16_t address) const
{
  return "MOVC A, @A+DPTR";
}

void MOVC_93::Execute() const
{
  std::uint16_t address = alu.GetA() + alu.GetDPTR();

  alu.SetA(alu.flash.Read(address));
  IncPC();
}

MOVC_83::MOVC_83(Alu &a) : Instruction(a)
{
  opcode = 0x83;
  operands = 0;
  cycles = 2;
}

std::string MOVC_83::Disassemble(std::uint16_t address) const
{
  return "MOVC A, @A+PC";
}

void MOVC_83::Execute() const
{
  alu.SetA(alu.flash.Read(alu.GetA() + 1 + alu.GetPC()));
  IncPC();
}

void MOVC_83::UpdateConstraints(RegisterConstraints &c, std::uint16_t address, std::uint16_t destination)
{
  Constraint& aConstraint = c.GetConstraint(RegisterA);

  if (aConstraint.type == ConstraintType::Interval)
  {
    aConstraint.SetMemory(aConstraint.low + address + 1, aConstraint.high + address + 1);
  }
}

MOVX_F0::MOVX_F0(Alu &a) : Instruction(a)
{
  opcode = 0xF0;
  operands = 0;
  cycles = 2;
}

std::string MOVX_F0::Disassemble(std::uint16_t address) const
{
  return "MOVX @DPTR, A";
}

void MOVX_F0::Execute() const
{
  alu.WriteX(alu.GetDPTR(), alu.GetA());
  IncPC();
}

MOVXRegisterA::MOVXRegisterA(Alu &a, std::uint8_t opcode) : Instruction(a, opcode)
{
  operands = 0;
  cycles = 2;
}

std::string MOVXRegisterA::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;

  ss << "MOVX @R" << (int) (opcode & IndirectRegisterMask) << ", A";
  return ss.str();
}

void MOVXRegisterA::Execute() const
{
  alu.WriteX(alu.GetReg(opcode & IndirectRegisterMask), alu.GetA());
  IncPC();
}

MOVXARegister::MOVXARegister(Alu &a, std::uint8_t opcode) : Instruction(a, opcode)
{
  operands = 0;
  cycles = 2;
}

std::string MOVXARegister::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;

  ss << "MOVX A, @R" << (int) (opcode & IndirectRegisterMask);
  return ss.str();
}

void MOVXARegister::Execute() const
{
  alu.SetA(alu.ReadX(alu.GetReg(opcode & IndirectRegisterMask)));
  IncPC();
}

MOVX_E0::MOVX_E0(Alu &a) : Instruction(a)
{
  opcode = 0xE0;
  operands = 0;
  cycles = 2;
}

std::string MOVX_E0::Disassemble(std::uint16_t address) const
{
  return "MOVX A, @DPTR";
}

void MOVX_E0::Execute() const
{
  alu.SetA(alu.ReadX(alu.GetDPTR()));
  IncPC();
}

MUL_A4::MUL_A4(Alu &a) : Instruction(a)
{
  opcode = 0xA4;
  operands = 0;
  cycles = 4;
}

std::string MUL_A4::Disassemble(std::uint16_t address) const
{
  return "MUL AB";
}

void MUL_A4::Execute() const
{
  std::uint16_t result = alu.GetA() * alu.GetB();

  alu.ClrC();
  alu.SetA((uint8_t) result);
  if (result > 255)
  {
    alu.SetOV();
  }
  else
  {
    alu.ClrOV();
  }
  alu.SetB((uint8_t)(result>>8));

  IncPC();
}

NOP::NOP(Alu &a) : Instruction(a)
{
  opcode = 0;
  operands = 0;
  cycles = 1;
}

std::string NOP::Disassemble(std::uint16_t address) const
{
  return "NOP";
}

void NOP::Execute() const
{
  IncPC();
}

BitwiseOperationMemory::BitwiseOperationMemory(Alu &a, std::uint8_t opcode) : Instruction(a, opcode)
{
  if ((opcode & BitwiseOperandMask) == ImmediateOperandMemory)
  {
    operands = 2;
  }
  else
  {
    operands = 1;
  }
  cycles = 2;
}

std::string BitwiseOperationMemory::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  if ((opcode & BitwiseOpMask) == BitwiseAnd)
  {
    ss << "ANL ";
  }
  else if ((opcode & BitwiseOpMask) == BitwiseOr)
  {
    ss << "ORL ";
  }
  else if ((opcode & BitwiseOpMask) == BitwiseXor)
  {
    ss << "XRL ";
  }
  ss << std::setfill('0') << std::hex;
  PrintAddress(ss, alu.flash.Read(address + 1));
  ss << ", #" << std::setw(2) << (int) alu.flash.Read(address+2);
  return ss.str();
}

void BitwiseOperationMemory::Execute() const
{
  std::uint8_t operand;
  std::uint8_t address = alu.flash.Read(alu.GetPC() + 1);

  if ((opcode & BitwiseOperandMask) == ImmediateOperandMemory)
  {
    operand = alu.flash.Read(alu.GetPC() + 2);
  }
  else
  {  
    operand = alu.GetA();
  }

  if ((opcode & BitwiseOpMask) == BitwiseAnd)
  {
    alu.Write(address, operand & alu.Read(address));
  }
  else if ((opcode & BitwiseOpMask) == BitwiseOr)
  {
    alu.Write(address, operand | alu.Read(address));
  }
  else if ((opcode & BitwiseOpMask) == BitwiseXor)
  {
    alu.Write(address, operand ^ alu.Read(address));
  }
  IncPC();
}

ORL_72::ORL_72(Alu &a) : Instruction(a)
{
  opcode = 0x72;
  operands = 1;
}

std::string ORL_72::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << "ORL C, ";
  ss << (int) alu.ReadBit(address+1);
  return ss.str();
}

ORL_A0::ORL_A0(Alu &a) : Instruction(a)
{
  opcode = 0xA0;
  operands = 1;
  cycles = 2;
}

std::string ORL_A0::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << "ORL C, ";
  ss << (int) alu.flash.Read(address+1);
  return ss.str();
}

BitwiseOperationARegister::BitwiseOperationARegister(Alu &a, std::uint8_t opcode) : Instruction(a, opcode)
{
  cycles = 1;
}

std::string BitwiseOperationARegister::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  if ((opcode & BitwiseOpMask) == BitwiseAnd)
  {
    ss << "ANL";
  }
  else if ((opcode & BitwiseOpMask) == BitwiseOr)
  {
    ss << "ORL";
  }
  else if ((opcode & BitwiseOpMask) == BitwiseXor)
  {
    ss << "XRL";
  }
  ss << " A, R";
  ss << (int) (opcode & RegisterMask);
  return ss.str();
}

void BitwiseOperationARegister::Execute() const
{
  if ((opcode & BitwiseOpMask) == BitwiseAnd)
  {
    alu.SetA(alu.GetA() & alu.GetReg(opcode & RegisterMask));
  }
  else if ((opcode & BitwiseOpMask) == BitwiseOr)
  {
    alu.SetA(alu.GetA() | alu.GetReg(opcode & RegisterMask));
  }
  else if ((opcode & BitwiseOpMask) == BitwiseXor)
  {
    alu.SetA(alu.GetA() ^ alu.GetReg(opcode & RegisterMask));
  }
  IncPC();
}

POP_D0::POP_D0(Alu &a) : Instruction(a)
{
  opcode = 0xD0;
  operands = 1;
  cycles = 2;
}

std::string POP_D0::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << "POP ";
  ss << (int) alu.flash.Read(address+1);
  return ss.str();
}

void POP_D0::Execute() const
{
  alu.Write(alu.flash.Read(alu.GetPC() + 1), alu.iram.Read(alu.GetSP()));
  alu.SetSP(alu.GetSP() - 1);
  IncPC();
}

PUSH_C0::PUSH_C0(Alu &a) : Instruction(a)
{
  opcode = 0xC0;
  operands = 1;
  cycles = 2;
}

std::string PUSH_C0::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::hex;
  ss << "PUSH ";
  ss << std::setw(2) << (int) alu.flash.Read(address+1);
  return ss.str();
}

void PUSH_C0::Execute() const
{
  alu.SetSP(alu.GetSP() + 1);
  alu.iram.Write(alu.GetSP(), alu.Read(alu.flash.Read(alu.GetPC() + 1)));
  IncPC();
}

RET_22::RET_22(Alu &a) : Instruction(a)
{
  opcode = 0x22;
  operands = 0;
  cycles = 2;
}

std::string RET_22::Disassemble(std::uint16_t address) const
{
  return "RET";
}

void RET_22::Execute() const
{
  std::uint8_t sp = alu.GetSP();
  std::uint8_t high = alu.iram.Read(sp);
  std::uint8_t low = alu.iram.Read(sp-1);

  alu.SetPC(low + high * 256);
  alu.SetSP(sp - 2);
}

bool RET_22::IsJump(std::uint16_t address) const
{
  return true;
}

std::vector<std::uint16_t> RET_22::GetNextAddresses(std::uint16_t address) const
{ 
  return {};
}

RETI_32::RETI_32(Alu &a) : Instruction(a)
{
  opcode = 0x32;
  operands = 0;
  cycles = 2;
}

void RETI_32::Execute() const
{
  std::uint8_t sp = alu.GetSP();
  std::uint8_t high = alu.iram.Read(sp);
  std::uint8_t low = alu.iram.Read(sp-1);

  alu.SetPC(low + high * 256);
  alu.SetSP(sp - 2);
}

bool RETI_32::IsJump(std::uint16_t address) const
{
  return true;
}

std::vector<std::uint16_t> RETI_32::GetNextAddresses(std::uint16_t address) const
{ 
  return {};
}

std::string RETI_32::Disassemble(std::uint16_t address) const
{
  return "RETI";
}

RL_23::RL_23(Alu &a) : Instruction(a)
{
  opcode = 0x23;
  operands = 0;
  cycles = 1;
}

std::string RL_23::Disassemble(std::uint16_t address) const
{
  return "RL A";
}

void RL_23::Execute() const
{
  std::uint16_t result = alu.GetA() << 1;

  if (result & 0x100)
  {
    result |= 0x01;
  }
  result = result & 0xff;
  alu.SetA((uint8_t) result);
  IncPC();
}

RLC_33::RLC_33(Alu &a) : Instruction(a)
{
  opcode = 0x33;
  operands = 0;
  cycles = 1;
}

std::string RLC_33::Disassemble(std::uint16_t address) const
{
  return "RLC A";
}

void RLC_33::Execute() const
{
  std::uint16_t result = alu.GetA() << 1;
  bool c = alu.GetC();

  if (result & 0x100)
  {
    alu.SetC();
  }
  else
  {
    alu.ClrC();
  }

  result = result & 0xff;
  if (c)
  {
    result |= 0x01;
  }
  alu.SetA((uint8_t) result);
  IncPC();
}

RR_3::RR_3(Alu &a) : Instruction(a)
{
  opcode = 3;
  operands = 0;
  cycles = 1;
}

void RR_3::Execute() const
{
  std::uint8_t a;

  a = alu.GetA();
  if (a & 1)
  {
    a = 0x80 | (a >> 1);
  }
  else
  {
    a = a >> 1;
  }
  alu.SetA(a);
  IncPC();
}

std::string RR_3::Disassemble(std::uint16_t address) const
{
  return "RR A";
}

RRC_13::RRC_13(Alu &a) : Instruction(a)
{
  opcode = 0x13;
  operands = 0;
  cycles = 1;
}

std::string RRC_13::Disassemble(std::uint16_t address) const
{
    return "RRC A";
}

void RRC_13::Execute() const
{
    bool tmp = this->alu.GetA()&1;
    this->alu.SetA((this->alu.GetA()>>1) | (this->alu.GetC()<<7)) ;
    if(tmp)
    {
    this->alu.SetC();
    }
    else
    {
        this->alu.ClrC();
    }

    ///FIXME songjiangshan
    IncPC();

}

SETB_D3::SETB_D3(Alu &a) : Instruction(a)
{
  opcode = 0xD3;
  operands = 0;
  cycles = 1;
}

std::string SETB_D3::Disassemble(std::uint16_t address) const
{
    return "SETB C";
}

void SETB_D3::Execute() const
{
    alu.SetC();
    IncPC();
}

SETB_D2::SETB_D2(Alu &a) : Instruction(a)
{
  opcode = 0xD2;
  operands = 1;
  cycles = 1;
}

std::string SETB_D2::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << "SETB ";
  ss << alu.GetBitAddressName((int) alu.flash.Read(address+1));
  return ss.str();
}

void SETB_D2::Execute(void) const
{
  std::uint8_t bitAddr = alu.flash.Read(alu.GetPC() + 1);

  alu.WriteBit(bitAddr, true);
  IncPC();
}

SJMP_80::SJMP_80(Alu &a) : Instruction(a)
{
  opcode = 0x80;
  operands = 1;
  cycles = 2;
}

std::string SJMP_80::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << "SJMP ";
  ss << (int) alu.flash.Read(address+1);
  return ss.str();
}

void SJMP_80::Execute() const
{
  std::int8_t reladdr = alu.flash.Read(alu.GetPC() + 1);
  alu.SetPC(alu.GetPC() + 1 + operands + reladdr);
}

bool SJMP_80::IsJump(std::uint16_t address) const
{
  return true;
}

std::vector<std::uint16_t> SJMP_80::GetNextAddresses(std::uint16_t address) const
{ 
  std::int8_t reladdr = alu.flash.Read(address + 1);

  return {static_cast<std::uint16_t>(address + 1 + operands + reladdr)};
}

SubtractionHelper::SubtractionHelper(Alu &alu, std::uint8_t opcode): Instruction(alu, opcode)
{
  cycles = 1;
}

void SubtractionHelper::Helper(std::uint16_t operand) const
{
  if (alu.GetC())
  {
    operand++;
  }

  if (operand > alu.GetA())
  {
    alu.SetC();
  }
  else
  {
    alu.ClrC();
  }

  if ((operand & 0xf) > (alu.GetA() & 0xf))
  {
    alu.SetAC();
  }
  else
  {
    alu.ClrAC();
  }

  std::int16_t signedResult = (int8_t) alu.GetA() - (int8_t) operand;
  if (signedResult > 127 || signedResult < -128)
  {
    alu.SetOV();
  }
  else
  {
    alu.ClrOV();
  }

  alu.SetA(alu.GetA() - operand);
  IncPC();
}

SUBB_94::SUBB_94(Alu &a, std::uint8_t opcode) : SubtractionHelper(a, opcode)
{
  operands = 1;
}

std::string SUBB_94::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << "SUBB A, #";
  ss << (int) alu.flash.Read(address+1);
  return ss.str();
}

void SUBB_94::Execute() const
{
  std::uint8_t operand = alu.flash.Read(alu.GetPC() + 1);

  Helper(operand);
}

SUBB_95::SUBB_95(Alu &a, std::uint8_t opcode) : SubtractionHelper(a, opcode)
{
  operands = 1;
}

std::string SUBB_95::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << "SUBB A, ";
  ss << (int) alu.flash.Read(address+1);
  return ss.str();
}

void SUBB_95::Execute() const
{
  std::uint8_t operand = alu.Read(alu.flash.Read(alu.GetPC() + 1));

  Helper(operand);
}

SUBBIndirectRegister::SUBBIndirectRegister(Alu &a, std::uint8_t opcode) : SubtractionHelper(a, opcode)
{
  operands = 0;
  cycles = 1;
}

std::string SUBBIndirectRegister::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;

  ss << "SUBB A, @R" << (int) (opcode & IndirectRegisterMask);
  return ss.str();
}

void SUBBIndirectRegister::Execute() const
{
  std::uint8_t operand = alu.Read(alu.GetReg(opcode & IndirectRegisterMask));

  Helper(operand);
}

SubARegister::SubARegister(Alu &a, std::uint8_t opcode) : SubtractionHelper(a, opcode)
{
  operands = 0;
}

std::string SubARegister::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << "SUBB A, R";
  ss << (int) (opcode & RegisterMask);
  return ss.str();
}

void SubARegister::Execute() const
{
  Helper(alu.GetReg(opcode & RegisterMask));
}

SWAP_C4::SWAP_C4(Alu &a, std::uint8_t opcode) : Instruction(a, opcode)
{
  operands = 0;
  cycles = 1;
}

std::string SWAP_C4::Disassemble(std::uint16_t address) const
{
  return "SWAP A";
}

void SWAP_C4::Execute(void) const
{
  std::uint8_t data = alu.GetA();

  data = ((data & 0xf) << 4) | ((data & 0xf0) >> 4);
  alu.SetA(data);
  IncPC();
}

XCH_C5::XCH_C5(Alu &a) : Instruction(a)
{
  opcode = 0xC5;
  operands = 1;
  cycles = 1;
}

std::string XCH_C5::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex;
  ss << "XCH A, ";
  ss << (int) alu.flash.Read(address+1);
  return ss.str();
}

void XCH_C5::Execute() const
{
  std::uint8_t addr = alu.flash.Read(alu.GetPC() + 1);
  std::uint8_t temp = alu.GetA();

  alu.SetA(alu.Read(addr));
  alu.Write(addr, temp);
  IncPC();
}

XCHIndirectRegister::XCHIndirectRegister(Alu &a, std::uint8_t opcode) : Instruction(a, opcode)
{
  operands = 0;
  cycles = 1;
}

std::string XCHIndirectRegister::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;

  ss <<  "XCH A, @R" << (int) (opcode & IndirectRegisterMask);
  return ss.str();
}

void XCHIndirectRegister::Execute() const
{
  std::uint8_t addr = alu.GetReg(opcode & IndirectRegisterMask);
  std::uint8_t temp = alu.GetA();

  alu.SetA(alu.Read(addr));
  alu.Write(addr, temp);
  IncPC();
}

XCHRegister::XCHRegister(Alu &a, std::uint8_t opcode) : Instruction(a, opcode)
{
  operands = 0;
  cycles = 1;
}

std::string XCHRegister::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << "XCH A, R" << (int) (opcode & RegisterMask);
  return ss.str();
}

void XCHRegister::Execute() const
{
  std::uint8_t temp = alu.GetReg(opcode & RegisterMask);

  alu.SetReg(opcode & RegisterMask, alu.GetA());
  alu.SetA(temp);
  IncPC();
}

XCHD::XCHD(Alu &a, std::uint8_t opcode) : Instruction(a, opcode)
{
  operands = 0;
  cycles  =1;
}

std::string XCHD::Disassemble(std::uint16_t address) const
{
  std::stringstream ss;
  ss << "XCHD A, @R" << (int) (opcode & IndirectRegisterMask);
  return ss.str();
}

void XCHD::Execute() const
{
  std::uint8_t temp = alu.GetA() & 0x0f;
  std::uint8_t address = alu.GetReg(opcode & IndirectRegisterMask);

  alu.SetA((alu.GetA() & 0xf0) | (alu.Read(address) & 0x0f));
  alu.Write(address, (alu.Read(address) & 0xf0) | temp); 
}


SIMTRAP_A5::SIMTRAP_A5(Alu &a, std::uint8_t opcode):Instruction(a, opcode)
{
    opcode = 0xA5;
    operands = 2;
    cycles = 1;
}

std::string SIMTRAP_A5::Disassemble(std::uint16_t address) const
{
    std::stringstream ss;

    ss << "SIMTRAP   ";
    ss <<std::hex<< (int) alu.flash.Read(address+1);
    ss<<", ";
    ss <<std::hex<< (int) alu.flash.Read(address+2);
    //ss <<std::hex<< (int) alu.flash.Read(address+3);

    return ss.str();
}

#include <stdlib.h>


void SIMTRAP_A5::Execute() const
{
    std::uint8_t b0 = alu.flash.Read(alu.GetPC() + 1);
    std::uint8_t b1 = alu.flash.Read(alu.GetPC() + 2);
    //std::uint8_t b2 = alu.flash.Read(alu.GetPC() + 3);

    unsigned cmd = (((unsigned)b1)<<8)|b0;

    std::uint8_t a = alu.GetA();

    if(cmd==0)
    {
        if(a!=0)
        {
            printf("SIMTRAP A_NOT_ZERO PASS\n");
        }
        else
        {
            printf("SIMTRAP A_NOT_ZERO FAILED\n");
        }
    }
    else if(cmd==1)
    {
        printf("SIMTRAP exit\n");
        ///FIXME 此处应该将状态传递到上层。例如调用printf，或者其他系统函数
        exit(0);
    }

    IncPC();
}




MOV_A7::MOV_A7(Alu &a):Instruction(a)
{

}

std::string MOV_A7::Disassemble(std::uint16_t address) const
{

}


MOV_A6::MOV_A6(Alu &a):Instruction(a)
{

}

std::string MOV_A6::Disassemble(std::uint16_t address) const
{

}

