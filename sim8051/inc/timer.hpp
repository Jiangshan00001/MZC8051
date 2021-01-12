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

#ifndef _TIMER_HPP
#define _TIMER_HPP

#include <cstdint>
#include <set>
#include <string>
#include "alu.hpp"
#include "block.hpp"
#include "sfr.hpp"

class TCON: public SfrBitAddressable
{
  public:
    TCON(std::string name, Block &b, std::uint8_t address, std::uint8_t resetValue, std::set<std::uint8_t> pages);
    void Write(std::uint8_t value);
    void WriteBit(std::uint8_t bit, bool value);
};

class Timer: public Block
{
  public:
    Timer(std::string name, Scheduler &s, Alu &alu);
    int CalculateRemainingTicks();
    void ClockEvent();
  private:
    Sfr ckcon;
    Sfr th1;
    Sfr th0;
    Sfr tl1;
    Sfr tl0;
    Sfr tmod;
    TCON tcon;
    Sfr tmr2rll;
    Sfr tmr2rlh;
    Sfr tmr2l;
    Sfr tmr2h;
    SfrBitAddressable tmr2cn;
};

#endif
