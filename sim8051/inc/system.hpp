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

#ifndef _SYSTEM_HPP
#define _SYSTEM_HPP

#include <set>
#include "alu.hpp"
#include "block.hpp"

class CLKSEL: public Sfr
{
  public:
    CLKSEL(std::string name, Block &block, std::uint8_t addresss, std::uint8_t resetValue, std::set<std::uint8_t> pages);
    std::uint8_t Read();
};

class RSTSRC: public Sfr
{
  public:
    RSTSRC(std::string name, Block &block, std::uint8_t address, std::uint8_t resetValue, std::set<std::uint8_t> pages);
    void Write(std::uint8_t value);
};

class System: public Block
{
  public:
    System(std::string name, Scheduler &s, Alu &alu);
  private:
    CLKSEL clksel;
    Sfr oscicn;
    RSTSRC rstsrc;
    Sfr ref0cn;
    Sfr reg0cn;
    Sfr vdm0cn;
    Sfr crc0auto;
    Sfr it01cf;
};

#endif
