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
#include <set>
#include <string>
#include "alu.hpp"
#include "block.hpp"
#include "cpu8051.hpp"
#include "sfr.hpp"
#include "uart.hpp"

SBUF0::SBUF0(std::string name, Block &block, std::uint8_t address, std::uint8_t resetValue, std::set<std::uint8_t> pages):
  Sfr(name, block, address, resetValue, pages)
{
}

SCON0::SCON0(std::string name, Block &block, std::uint8_t address, std::uint8_t resetValue, std::set<std::uint8_t> pages):
  SfrBitAddressable(name, block, address, resetValue, pages)
{
}

#define TI0 2
#define TI0_BIT 1

void SCON0::Write(std::uint8_t value)
{
  data = value;
}

void SCON0::WriteBit(std::uint8_t bit, bool value)
{
  SfrBitAddressable::WriteBit(bit, value);
}

void SBUF0::Write(std::uint8_t tx)
{
  block.alu.GetCallback()->OnUARTTx(*block.alu.GetCallbackCpu(), tx);
  Uart *u = dynamic_cast<Uart*>(&block);
  u->remainingTicks = 100; // This will work for now, calculate a better value later
  u->ReportActive();
}

Uart::Uart(std::string name, Scheduler &s, Alu &a) :
  Block(name, s, a),
  sbuf0("SBUF0", *this, 0x99, 0x00, {0x0}),
  scon0("SCON0", *this, 0x98, 0x40, {0x0})
{
}

#define REN0 16
#define RI0 1

void Uart::SimulateRx(char c)
{
  scon0.data |= RI0;
  sbuf0.data = (uint8_t) c;
  if (scon0.data & REN0)
  {
    alu.UartInterrupt();
  }
  else
  {
    printf("UART input with RX disabled\n");
  }
}

void Uart::ClockEvent()
{
  scon0.data |= TI0;
  alu.UartInterrupt();
  // After retrieving RX buffer, UART goes back to being idle
  remainingTicks = -1;
}
