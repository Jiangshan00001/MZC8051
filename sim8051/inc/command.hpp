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

#ifndef _COMMAND_HPP
#define _COMMAND_HPP

#include <cstdint>
#include <vector>
#include <string>
#include "cpu8051.hpp"
#include "shell.hpp"

constexpr auto NumBreakpoints = 4;

class Command : public Cpu8051Callbacks, public CommandCallback
{
  private:
    bool trace[256];
    int instructionCount;
    int instructionLimit;
    /// 当前已经中断的次数
    int breakCount;
    /// 中断次数限制，默认为1，即1此中断就中断
    int breakLimit;
    int breakpoints[NumBreakpoints];
  protected:
    Shell &shell;
  public:
    Command(Shell&);
    void OnInstructionExecuted(Cpu8051 &cpu);
    bool OnGPIORead(Cpu8051 &cpu, std::uint8_t port, std::uint8_t bit);
    void OnGPIOWrite(Cpu8051 &vpu, std::uint8_t port, std::uint8_t bit, bool value);
    void OnUARTTx(Cpu8051 &cpu, char tx);
    void OnCommand(Cpu8051 &cpu, std::string command, std::vector<Parameter*> parameters);
    void OnReset(Cpu8051 &handler);
};

#endif
