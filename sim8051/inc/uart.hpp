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

#ifndef _UART_HPP
#define _UART_HPP

#include <set>
#include "uart.hpp"
#include "alu.hpp"
#include "block.hpp"

class SBUF0: public Sfr
{
  public:
    SBUF0(std::string name, Block &block, std::uint8_t address, std::uint8_t resetValue, std::set<std::uint8_t> pages);
    void Write(std::uint8_t tx);
};

class SCON0: public SfrBitAddressable
{
  public:
    SCON0(std::string name, Block &block, std::uint8_t address, std::uint8_t resetValue, std::set<std::uint8_t> pages);
    void Write(std::uint8_t value);
    void WriteBit(std::uint8_t bit, bool value);
};

class Uart: public Block
{
  public:
    Uart(std::string name, Scheduler &s, Alu &alu);
    void SimulateRx(char c);
    SBUF0 sbuf0;
    SCON0 scon0;
  private:
    void ClockEvent();
};

#endif
