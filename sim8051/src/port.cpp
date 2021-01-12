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
#include <set>
#include <string>
#include "alu.hpp"
#include "block.hpp"
#include "cpu8051.hpp"
#include "port.hpp"
#include "sfr.hpp"

SfrIO::SfrIO(std::string name, Block &block, std::uint8_t address, std::uint8_t resetValue, std::set<std::uint8_t> pages, std::uint8_t p):
  SfrBitAddressable(name, block, address, resetValue, pages), port(p)
{
}

bool SfrIO::ReadBit(std::uint8_t bit)
{
  return block.alu.GetCallback()->OnGPIORead(*block.alu.GetCallbackCpu(), port, bit);
}

void SfrIO::WriteBit(std::uint8_t bit, bool value)
{
  return block.alu.GetCallback()->OnGPIOWrite(*block.alu.GetCallbackCpu(), port, bit, value);
}

Port::Port(std::string name, Scheduler &s, Alu &a): Block(name, s, a)
{
}
