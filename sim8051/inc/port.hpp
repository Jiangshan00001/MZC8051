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

#ifndef _PORT_HPP
#define _PORT_HPP

#include <cstdint>
#include <set>
#include <string>
#include "alu.hpp"
#include "block.hpp"

// Common superclass for P0, P1 and P2
class SfrIO: public SfrBitAddressable
{
  public:
    SfrIO(std::string name, Block &block, std::uint8_t address, std::uint8_t resetValue, std::set<std::uint8_t> pages, std::uint8_t port);
    void WriteBit(std::uint8_t bit, bool value);
    bool ReadBit(std::uint8_t bit);
  private:
    std::uint8_t port;
};

class Port: public Block
{
  public:
    Port(std::string name, Scheduler &s, Alu &a);
};

#endif
