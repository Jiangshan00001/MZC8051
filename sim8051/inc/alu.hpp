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

#ifndef _ALU_HPP
#define _ALU_HPP

#include <cstdint>
#include <map>
#include <string>
#include <vector>
#include "block.hpp"
#include "flash.hpp"
#include "memory.hpp"
#include "sfr.hpp"

class SfrPMU0CF: public Sfr
{
  public:
    SfrPMU0CF(std::string name, Block &block, std::uint8_t address, std::uint8_t resetValue, std::set<std::uint8_t> pages);
    void Write(std::uint8_t data);
    std::uint8_t Read();
};

class Cpu8051Callbacks;
class Cpu8051;
class Instruction;
class RegisterConstraints;

class Alu : public Block
{
  public:
    Flash flash;
    Memory xram;
    Memory iram;
    std::string Disassemble(std::uint16_t address);
    void UpdateConstraints(RegisterConstraints &c, std::uint16_t address, std::uint16_t destination);
    std::uint8_t GetOperands(std::uint16_t address);
    bool IsJump(std::uint16_t address);
    std::vector<std::uint16_t> GetNextAddresses(std::uint16_t address);
    Alu(std::string name, Scheduler &s, std::uint16_t xramSize, std::uint16_t iramSize, std::uint16_t flashSize);
    void Reset();
    std::uint16_t GetPC();
    std::uint8_t GetSP();
    std::uint8_t GetA();
    void SetPC(std::uint16_t pc);
    void SetSP(std::uint8_t sp);
    void SetA(std::uint8_t data);
    std::uint16_t GetDP();
    void RegisterSfr(Sfr *sfr);
    std::uint8_t GetReg(std::uint8_t reg);
    void SetReg(std::uint8_t reg, std::uint8_t value);
    void SetDPTR(std::uint16_t val);
    std::uint16_t GetDPTR();
    std::uint8_t GetB() const;
    void SetB(std::uint8_t val);
    bool GetC();
    void SetC();
    void ClrC();
    void SetAC();
    void ClrAC();
    void SetOV();
    void ClrOV();


    //读写R寄存器，0-7
    std::uint8_t ReadR(std::uint8_t address);
    void WriteR(std::uint8_t address, std::uint8_t dat);

    // Handles byte access to IRAM as well as SFR
    std::uint8_t Read(std::uint8_t address);
    void Write(std::uint8_t address, std::uint8_t value);
    // Handles writes done via 'MOVX' - these can go to either flash or external RAM
    void WriteX(std::uint16_t address, std::uint8_t value);
    std::uint8_t ReadX(std::uint16_t address);

    // Handles bit access to bit-addressable IRAM as well as SFR
    bool ReadBit(std::uint8_t address);
    void WriteBit(std::uint8_t address, bool value);
    // Get readable name of bit address
    std::string GetBitAddressName(std::uint8_t address);

    bool GetTraceSfr();
    void SetTraceSfr(bool val);

    void RegisterCallback(Cpu8051Callbacks *cb, Cpu8051* cpu);
    Cpu8051Callbacks *GetCallback() const;
    Cpu8051* GetCallbackCpu() const;
    int CalculateRemainingTicks();
    void ClockEvent();
    void TimerInterrupt(int timer);
    void UartInterrupt();
    void RTCWakeup();
    std::map<std::uint8_t, std::map<std::uint8_t, Sfr*> > specialFunctionRegisters;
    std::map<std::uint8_t, SfrBitAddressable*> bitAddressableSfr;
    Sfr sfrDPL;
    Sfr sfrDPH;
  private:
    std::vector<Instruction*> instructionSet;
    std::uint16_t pc;
    Sfr sfrSP;
    Sfr sfrIP;
    SfrBitAddressable sfrPSW;
    SfrBitAddressable sfrIE;
    Sfr sfrSFRPAGE;
    SfrBitAddressable sfrB;
    SfrBitAddressable sfrACC;
    SfrPMU0CF sfrPMU0CF;
    Sfr sfrPCON;
    Sfr sfrPSCTL;
    Sfr sfrFLSCL;
    Sfr sfrFLKEY;
    Sfr sfrFLWR;
    Sfr sfrEIE1;
    bool traceSfr;
    int tickCount;
    Cpu8051Callbacks *callbacks;
    Cpu8051* callbackCpu;
    std::uint8_t interruptPending;
    Instruction *currentInstruction;
};

#endif
