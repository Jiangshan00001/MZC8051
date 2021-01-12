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

#include <sstream>
#include <iostream>
#include <string>
#include "flash.hpp"
#include "alu.hpp"
#include "cpu8051.hpp"
#include "instruction.hpp"
#include "instruction_coverage.hpp"
#include "instruction_set.hpp"
#include "exceptions.hpp"
#include "sfr.hpp"
#include "command.hpp"
//#include <ncurses.h>

#define INTERRUPT_PENDING_TIMER0 1
#define INTERRUPT_PENDING_UART0 2

SfrPMU0CF::SfrPMU0CF(std::string name, Block &block, std::uint8_t address, std::uint8_t resetValue, std::set<std::uint8_t> pages) :
  Sfr(name, block, address, resetValue, pages)
{
}

void SfrPMU0CF::Write(std::uint8_t data)
{
  this->data = data;
}

std::uint8_t SfrPMU0CF::Read()
{
  return (this->data & 0xC0) | 4; // Let's assume we always wake up due to a RTC alarm
}

Alu::Alu(std::string name, Scheduler &s, std::uint16_t xramSize, std::uint16_t iramSize, std::uint16_t flashSize):
    Block(name, s, *this),
    flash("FLASH", flashSize),
    xram("XRAM", xramSize),
    iram("IRAM", iramSize),
    sfrDPL("DPL", *this, 0x82, 0x00, {0x0, 0xf}),
    sfrDPH("DPH", *this, 0x83, 0x00, {0x0, 0xf}),
    instructionSet(256),
    sfrSP("SP", *this, 0x81, 0x07, {0x0, 0xf}),
    sfrIP("IP", *this, 0xb8, 0x80, {0x0, 0xf}),
    sfrPSW("PSW", *this, 0xd0, 0x00, {0x0, 0xf}),
    sfrIE("IE", *this, 0xa8, 0x00, {0x0, 0xf}),
    sfrSFRPAGE("SFRPAGE", *this, 0xa7, 0x00, {0x0, 0xf}),
    sfrB("B", *this, 0xf0, 0x00, {0x0, 0xf}),
    sfrACC("ACC", *this, 0xe0, 0x00, {0x0, 0xf}),
    sfrPMU0CF("PMU0CF", *this, 0xb5, 0x00, {0x0}),
    sfrPCON("PCON", *this, 0x87, 0x00, {0x0, 0xf}),
    sfrPSCTL("PSCTL", *this, 0x8f, 0x00, {0x0, 0xf}),
    sfrFLSCL("FLSCL", *this, 0xb7, 0x00, {0x0}),
    sfrFLKEY("FLKEY", *this, 0xb6, 0x00, {0x0, 0xf}),
    sfrFLWR("FLWR", *this, 0xe5, 0x00, {0x0, 0xf}),
    sfrEIE1("EIE1", *this, 0xe6, 0x00, {0x0, 0xf}),
    traceSfr(false),
    callbacks(nullptr),
    interruptPending(0)
{
  for (auto i = 0x11; i <= 0xf1; i += 0x20)
  {
    instructionSet[i] = new ACALL(*this, i);
  }

  for (auto i = 0x01; i <= 0xe1; i += 0x20)
  {
    instructionSet[i] = new AJMP(*this, i);
  }

  for (auto i = 0; i < 8; i++)
  {
    instructionSet[0x08 + i] = new IncRegister(*this, 0x08 + i);
    instructionSet[0x18 + i] = new DecRegister(*this, 0x18 + i);
    instructionSet[0x28 + i] = new AddRegister(*this, 0x28 + i, false);
    instructionSet[0x38 + i] = new AddRegister(*this, 0x38 + i, true);
    instructionSet[0x48 + i] = new BitwiseOperationARegister(*this, 0x48 + i);
    instructionSet[0x58 + i] = new BitwiseOperationARegister(*this, 0x58 + i);
    instructionSet[0x68 + i] = new BitwiseOperationARegister(*this, 0x68 + i);
    instructionSet[0x78 + i] = new MovRegisterImmediate(*this, 0x78 + i);
    instructionSet[0x88 + i] = new MovAddressRegister(*this, 0x88 + i);
    instructionSet[0x98 + i] = new SubARegister(*this, 0x98 + i);
    instructionSet[0xa8 + i] = new MovRegisterAddress(*this, 0xa8 + i);
    instructionSet[0xb8 + i] = new CJNERegister(*this, 0xb8 + i);
    instructionSet[0xc8 + i] = new XCHRegister(*this, 0xc8 + i);
    instructionSet[0xd8 + i] = new DJNZRegister(*this, 0xd8 + i);
    instructionSet[0xe8 + i] = new MovARegister(*this, 0xe8 + i);
    instructionSet[0xf8 + i] = new MovRegisterA(*this, 0xf8 + i);
  }

  instructionSet[0x24] = new AddImmediate(*this, 0x24, false);
  instructionSet[0x25] = new AddMemory(*this, 0x25, false);
  instructionSet[0x26] = new AddIndirectRegister(*this, 0x26, false);
  instructionSet[0x27] = new AddIndirectRegister(*this, 0x27, false);
  instructionSet[0x34] = new AddImmediate(*this, 0x34, true);
  instructionSet[0x35] = new AddMemory(*this, 0x35, true);
  instructionSet[0x36] = new AddIndirectRegister(*this, 0x36, true);
  instructionSet[0x37] = new AddIndirectRegister(*this, 0x37, true);

  for (auto i = 4; i <= 7; i++)
  {
    instructionSet[0x40 + i] = new BitwiseOperation(*this, 0x40 + i);
    instructionSet[0x50 + i] = new BitwiseOperation(*this, 0x50 + i);
    instructionSet[0x60 + i] = new BitwiseOperation(*this, 0x60 + i);
  }

  instructionSet[0x82] = new ANL_82(*this);
  instructionSet[0xb0] = new ANL_B0(*this);
  instructionSet[0xb4] = new CJNE_B4(*this, 0xb4);
  instructionSet[0xb5] = new CJNE_B5(*this, 0xb5);
  instructionSet[0xb6] = new CJNE_B6(*this, 0xb6);
  instructionSet[0xb7] = new CJNE_B7(*this, 0xb7);
  instructionSet[0xc2] = new CLR_C2(*this);
  instructionSet[0xc3] = new CLR_C3(*this);
  instructionSet[0xe4] = new CLR_E4(*this);
  instructionSet[0xf4] = new CPL_F4(*this);
  instructionSet[0xb3] = new CPL_B3(*this);
  instructionSet[0xb2] = new CPL_B2(*this);
  instructionSet[0xd4] = new DA_D4(*this);
  instructionSet[0x15] = new DEC_15(*this);
  instructionSet[0x14] = new DEC_14(*this);
  instructionSet[0x84] = new DIV_84(*this);
  instructionSet[0xd5] = new DJNZ_D5(*this);
  instructionSet[0x05] = new INC_5(*this);
  instructionSet[0x04] = new INC_4(*this);
  instructionSet[0x06] = new IncDecIndirectRegister(*this, 0x06);
  instructionSet[0x07] = new IncDecIndirectRegister(*this, 0x07);
  instructionSet[0x16] = new IncDecIndirectRegister(*this, 0x16);
  instructionSet[0x17] = new IncDecIndirectRegister(*this, 0x17);
  instructionSet[0xa3] = new INC_A3(*this);
  instructionSet[0x10] = new JBC_10(*this, 0x10);
  instructionSet[0x20] = new JB(*this, 0x20);
  instructionSet[0x30] = new JB(*this, 0x30);
  instructionSet[0x40] = new JC(*this, 0x40);
  instructionSet[0x50] = new JC(*this, 0x50);
  instructionSet[0x60] = new JZ(*this, 0x60);
  instructionSet[0x70] = new JZ(*this, 0x70);
  instructionSet[0x73] = new JMP_73(*this);
  instructionSet[0x12] = new LCALL_12(*this);
  instructionSet[0x02] = new LJMP_2(*this);
  instructionSet[0x90] = new MOV_90(*this);
  instructionSet[0x75] = new MOV_75(*this);
  instructionSet[0x85] = new MOV_85(*this);
  instructionSet[0x76] = new MovRegisterIndirectImmediate(*this, 0x76);
  instructionSet[0x77] = new MovRegisterIndirectImmediate(*this, 0x77);
  instructionSet[0xa6] = new MovIndirectFromMem(*this, 0xa6);
  instructionSet[0xa7] = new MovIndirectFromMem(*this, 0xa7);
  instructionSet[0x74] = new MOV_74(*this);
  instructionSet[0xe5] = new MOV_E5(*this);
  instructionSet[0xa2] = new MOV_A2(*this);
  instructionSet[0x92] = new MOV_92(*this);
  instructionSet[0x86] = new MovMemoryIndirectRegister(*this, 0x86);
  instructionSet[0x87] = new MovMemoryIndirectRegister(*this, 0x87);
  instructionSet[0xf5] = new MOV_F5(*this);
  instructionSet[0xf6] = new MovIndirect(*this, 0xf6);
  instructionSet[0xf7] = new MovIndirect(*this, 0xf7);
  instructionSet[0xe6] = new MovIndirectRegister(*this, 0xe6);
  instructionSet[0xe7] = new MovIndirectRegister(*this, 0xe7);
  instructionSet[0x93] = new MOVC_93(*this);
  instructionSet[0x83] = new MOVC_83(*this);
  instructionSet[0xf0] = new MOVX_F0(*this);
  instructionSet[0xf2] = new MOVXRegisterA(*this, 0xf2);
  instructionSet[0xf3] = new MOVXRegisterA(*this, 0xf3);
  instructionSet[0xe0] = new MOVX_E0(*this);
  instructionSet[0xe2] = new MOVXARegister(*this, 0xe2);
  instructionSet[0xe3] = new MOVXARegister(*this, 0xe3);
  instructionSet[0xa4] = new MUL_A4(*this);
  instructionSet[0x00] = new NOP(*this);
  instructionSet[0x42] = new BitwiseOperationMemory(*this, 0x42);
  instructionSet[0x43] = new BitwiseOperationMemory(*this, 0x43);
  instructionSet[0x52] = new BitwiseOperationMemory(*this, 0x52);
  instructionSet[0x53] = new BitwiseOperationMemory(*this, 0x53);
  instructionSet[0x62] = new BitwiseOperationMemory(*this, 0x62);
  instructionSet[0x63] = new BitwiseOperationMemory(*this, 0x63);
  instructionSet[0x72] = new ORL_72(*this);
  instructionSet[0xa0] = new ORL_A0(*this);
  instructionSet[0xd0] = new POP_D0(*this);
  instructionSet[0xc0] = new PUSH_C0(*this);
  instructionSet[0x22] = new RET_22(*this);
  instructionSet[0x32] = new RETI_32(*this);
  instructionSet[0x23] = new RL_23(*this);
  instructionSet[0x33] = new RLC_33(*this);
  instructionSet[0x03] = new RR_3(*this);
  instructionSet[0x13] = new RRC_13(*this);
  instructionSet[0xd3] = new SETB_D3(*this);
  instructionSet[0xd2] = new SETB_D2(*this);
  instructionSet[0x80] = new SJMP_80(*this);
  instructionSet[0x94] = new SUBB_94(*this, 0x94);
  instructionSet[0x95] = new SUBB_95(*this, 0x95);
  instructionSet[0x96] = new SUBBIndirectRegister(*this, 0x96);
  instructionSet[0x97] = new SUBBIndirectRegister(*this, 0x97);
  instructionSet[0xc4] = new SWAP_C4(*this, 0xc4);
  instructionSet[0xc5] = new XCH_C5(*this);
  instructionSet[0xc6] = new XCHIndirectRegister(*this, 0xc6);
  instructionSet[0xc7] = new XCHIndirectRegister(*this, 0xc7);
  instructionSet[0xd6] = new XCHD(*this, 0xd6);
  instructionSet[0xd7] = new XCHD(*this, 0xd7);

  instructionSet[0xa5] = new SIMTRAP_A5(*this, 0xA5);

}

std::string Alu::Disassemble(std::uint16_t address)
{
  const std::uint8_t opcode = flash.Read(address);

  if (instructionSet[opcode] == nullptr)
  {
    throw new IllegalInstructionException();
  }
  else
  {
    return instructionSet[opcode]->Disassemble(address);
  }
}

void Alu::UpdateConstraints(RegisterConstraints &c, std::uint16_t address, std::uint16_t destination)
{
  const std::uint8_t opcode = flash.Read(address);

  if (instructionSet[opcode] == nullptr)
  {
    throw new IllegalInstructionException();
  }
  else
  {
    return instructionSet[opcode]->UpdateConstraints(c, address, destination);
  }
}

std::uint8_t Alu::GetOperands(std::uint16_t address)
{
  const std::uint8_t opcode = flash.Read(address);

  if (instructionSet[opcode] == nullptr)
  {
    throw new IllegalInstructionException();
  }
  else
  {
    return instructionSet[opcode]->GetOperands();
  }
}

bool Alu::IsJump(std::uint16_t address)
{
  const std::uint8_t opcode = flash.Read(address);

  if (instructionSet[opcode] == nullptr)
  {
    throw new IllegalInstructionException();
  }
  else
  {
    return instructionSet[opcode]->IsJump(address);
  }
}

std::vector<std::uint16_t> Alu::GetNextAddresses(std::uint16_t address)
{
  const std::uint8_t opcode = flash.Read(address);

  if (instructionSet[opcode] == nullptr)
  {
    throw new IllegalInstructionException();
  }
  else
  {
    return instructionSet[opcode]->GetNextAddresses(address);
  }
}

void Alu::Reset()
{
  Block::Reset();
  this->SetA(0);
  pc = 0;
  for (int i = 0; i < 8; i++)
  {
     SetReg(i, 0);
  }
  remainingTicks = CalculateRemainingTicks();
  ReportActive();
  if (callbacks)
  {
    callbacks->OnReset(*callbackCpu);
  }
}

std::uint16_t Alu::GetPC()
{
  return pc;
}

std::uint8_t Alu::GetSP()
{
  return sfrSP.data;
}
void Alu::SetSP(std::uint8_t s)
{
  sfrSP.data = s;
}

void Alu::SetPC(std::uint16_t newPC)
{
  pc = newPC;
}

void Alu::SetA(std::uint8_t a)
{
  sfrACC.data = a;
}

std::uint8_t Alu::GetA()
{
  return sfrACC.data;
}

std::uint8_t Alu::GetReg(std::uint8_t reg)
{
  return iram.Read(reg);
}

void Alu::SetReg(std::uint8_t reg, std::uint8_t value)
{
  return iram.Write(reg, value);
}

void Alu::SetDPTR(std::uint16_t val)
{
  sfrDPL.data = val & 255;
  sfrDPH.data = val / 256;
}

std::uint16_t Alu::GetDPTR()
{
  return sfrDPL.data + 256 * sfrDPH.data;
}

// PSW bits
#define CY 0x80
#define AC 0x40
#define OV 0x04

bool Alu::GetC()
{
  return sfrPSW.data & CY;
}

void Alu::SetC()
{
  sfrPSW.data |= CY;
}

void Alu::ClrC()
{
  sfrPSW.data &= ~CY;
}

void Alu::SetAC()
{
  sfrPSW.data |= AC;
}

void Alu::ClrAC()
{
  sfrPSW.data &= ~AC;
}

void Alu::SetOV()
{
  sfrPSW.data |= OV;
}

void Alu::ClrOV()
{
    sfrPSW.data &= ~OV;
}

std::uint8_t Alu::ReadR(std::uint8_t address)
{
    int rs0= sfrPSW.data &0x08;
    int rs1= sfrPSW.data &0x10;

    int rs_bank = rs1*2+rs0;

    return iram.Read(address + rs_bank*8 );
}

void Alu::WriteR(std::uint8_t address, std::uint8_t dat)
{
    int rs0= sfrPSW.data &0x08;
    int rs1= sfrPSW.data &0x10;

    int rs_bank = rs1*2+rs0;

    return iram.Write(address + rs_bank*8, dat );

}

void Alu::RegisterSfr(Sfr *sfr)
{
  for (std::set<std::uint8_t>::iterator i = sfr->pages.begin(); i != sfr->pages.end(); i++)
  {
    specialFunctionRegisters[*i][sfr->address] = sfr;
  }

  SfrBitAddressable *b = dynamic_cast<SfrBitAddressable*>(sfr);
  if (b)
  {
    bitAddressableSfr[sfr->address] = b;
  }
}

void Alu::Write(std::uint8_t address, std::uint8_t data)
{
  if (address < 0x80)
  {
    iram.Write(address, data);
  }
  else if (specialFunctionRegisters[sfrSFRPAGE.data].find(address) != specialFunctionRegisters[sfrSFRPAGE.data].end())
  {
    specialFunctionRegisters[sfrSFRPAGE.data][address]->Write(data);
  }
  else
  {
    printf("Illegal byte address %x PC %x\n", address, GetPC());
    throw new IllegalAddressException();
  }
}

std::uint8_t Alu::Read(std::uint8_t address)
{
  if (address < 0x80)
  {
    return iram.Read(address);
  }
  else if (specialFunctionRegisters[sfrSFRPAGE.data].find(address) != specialFunctionRegisters[sfrSFRPAGE.data].end())
  {
    return specialFunctionRegisters[sfrSFRPAGE.data][address]->Read();
  }
  else
  {
    printf("Illegal byte address %x PC %x\n", address, GetPC());
    throw new IllegalAddressException();
  }
}

bool Alu::ReadBit(std::uint8_t address)
{
  if (address < 0x80)
  {
    std::uint8_t byteAddr = 0x20 + address / 8;
    std::uint8_t bit = 1 << address % 8;

    return iram.Read(byteAddr) & bit;
  }
  else if (bitAddressableSfr.find(address & 0xf8) != bitAddressableSfr.end())
  {
    return bitAddressableSfr[address & 0xf8]->ReadBit(address % 8);
  }
  else
  {
    printf("Illegal bit address %x PC %x\n", address, GetPC());
    throw new IllegalAddressException();
  }
}

void Alu::WriteBit(std::uint8_t address, bool value)
{
  if (address < 0x80)
  {
    std::uint8_t byteAddr = 0x20 + address / 8;
    std::uint8_t bit = 0;

    bit = 1 << address % 8;

    iram.Write(byteAddr, iram.Read(byteAddr) & ~bit);
    if (value)
    {
      iram.Write(byteAddr, iram.Read(byteAddr) | bit);
    }
  }
  else if (bitAddressableSfr.find(address & 0xf8) != bitAddressableSfr.end())
  {
    bitAddressableSfr[address & 0xf8]->WriteBit(address % 8, value);
  }
  else
  {
    printf("Illegal bit address %x PC %x\n", address, GetPC());
    throw new IllegalAddressException();
  }
}

std::string Alu::GetBitAddressName(std::uint8_t address)
{
  std::stringstream ss;
  std::uint8_t bit = address % 8;

  if (bitAddressableSfr.find(address & 0xf8) != bitAddressableSfr.end())
  {
    ss << bitAddressableSfr[address & 0xf8]->GetName();
  }
  else
  {
    ss << std::hex << 0x20 + (int) (address) / 8;
  }
  ss << "." << (int) bit;
  return ss.str();
}


bool Alu::GetTraceSfr()
{
  return traceSfr;
}

void Alu::SetTraceSfr(bool value)
{
  traceSfr = value;
}

void Alu::ClockEvent()
{
  if (interruptPending & INTERRUPT_PENDING_TIMER0)
  {
    interruptPending &= ~INTERRUPT_PENDING_TIMER0;
    SetSP(alu.GetSP() + 1);
    iram.Write(alu.GetSP(), (uint8_t) alu.GetPC());
    SetSP(alu.GetSP() + 1);
    iram.Write(alu.GetSP(), alu.GetPC() / 256);
    SetPC(0xb);
    InstructionCoverage::GetInstance().InstructionExecuted(0xb);
  }
  else if (interruptPending & INTERRUPT_PENDING_UART0)
  {
    interruptPending &= ~INTERRUPT_PENDING_UART0;
    SetSP(alu.GetSP() + 1);
    iram.Write(alu.GetSP(), (uint8_t) alu.GetPC());
    SetSP(alu.GetSP() + 1);
    iram.Write(alu.GetSP(), alu.GetPC() / 256);
    SetPC(0x23);
    InstructionCoverage::GetInstance().InstructionExecuted(0x23);
  }
  else
  {
    InstructionCoverage::GetInstance().InstructionExecuted(pc);
    instructionSet[flash.Read(pc)]->Execute();
  }
  remainingTicks = CalculateRemainingTicks();
  if (callbacks)
  {
    callbacks->OnInstructionExecuted(*callbackCpu);
  }
}

#define IDLE_MODE 1
#define STOP_MODE 2
#define SUSPEND_MODE 64
#define SLEEP_MODE 128

int Alu::CalculateRemainingTicks()
{
  // If any sleep mode bit is set, code execution stops. So we return -1 here
  if (sfrPCON.data & (IDLE_MODE | STOP_MODE) || sfrPMU0CF.data & (SUSPEND_MODE | SLEEP_MODE))
  {
    return -1;
  }
  else if (interruptPending)
  {
    // Let's assume that jumping to the interrupt vector takes two cycles
    return 2;
  }
  else
  {
    int cycles = instructionSet[flash.Read(pc)]->cycles;

    return cycles;
  }
}

void Alu::RegisterCallback(Cpu8051Callbacks *c, Cpu8051* cpu)
{
  callbackCpu = cpu;
  callbacks = c;
}

Cpu8051Callbacks *Alu::GetCallback() const
{
  return callbacks;
}

Cpu8051 *Alu::GetCallbackCpu() const
{
  return callbackCpu;
}

#define ET0 2
#define ES0 16

void Alu::TimerInterrupt(int timer)
{
  // Wake-up from Idle mode
  sfrPCON.data &= ~IDLE_MODE;
  // Check if interrupt is enabled
  if ((timer == 0) && (sfrIE.data & ET0))
  {
    interruptPending |= INTERRUPT_PENDING_TIMER0;
  }
  remainingTicks = CalculateRemainingTicks();
  ReportActive();
}

void Alu::UartInterrupt()
{
  // Wake-up from Idle mode
  sfrPCON.data &= ~IDLE_MODE;
  // Check if interrupt is enabled
  if (sfrIE.data & ES0)
  {
    interruptPending |= INTERRUPT_PENDING_UART0;
  }
  remainingTicks = CalculateRemainingTicks();
  ReportActive();
}

void Alu::RTCWakeup()
{
  // Wake-up from Sleep mode
  // There is no interrupt handler for this event, we just wake up the ALU again.
  sfrPMU0CF.Write(sfrPMU0CF.Read() & ~SLEEP_MODE);
  remainingTicks = CalculateRemainingTicks();
  ReportActive();
}

std::uint8_t Alu::GetB() const
{
  return sfrB.data;
}
void Alu::SetB(std::uint8_t val)
{
  sfrB.data=val;
}

#define PSEE 2
#define PSWE 1

void Alu::WriteX(std::uint16_t address, std::uint8_t value)
{
  if (sfrPSCTL.data & PSWE)
  {
    if (sfrPSCTL.data & PSEE)
    {
      std::uint16_t base = address & 0xff00;
      for (int i = 0; i < 256; i++)
      {
        flash.Write(base + i, value);
      }
    }
    else
    {
      flash.Write(address, value);
    }
    sfrPSCTL.data &= ~(PSWE | PSEE);
  }
  else
  {
    xram.Write(address, value);
  }
}

std::uint8_t Alu::ReadX(std::uint16_t address)
{
  return xram.Read(address);
}
