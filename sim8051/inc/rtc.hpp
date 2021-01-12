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

#ifndef _RTC_HPP
#define _RTC_HPP

#include <cstdint>
#include <set>
#include <string>
#include "alu.hpp"
#include "block.hpp"
#include "sfr.hpp"

class RTC0DAT: public Sfr
{
  public:
    RTC0DAT(std::string name, Block &block, std::uint8_t addresss, std::uint8_t resetValue, std::set<std::uint8_t> pages);
    void Write(std::uint8_t value);
    std::uint8_t Read();
};

class Rtc: public Block
{
  public:
    Rtc(std::string name, Scheduler &s, Alu &alu);
    int CalculateRemainingTicks();
    void ClockEvent();
    void Reset();
    std::uint8_t rtc0xcn;
    std::uint8_t rtc0cn;
    std::uint32_t alarm;
    std::uint32_t capture;
    unsigned long long ticks;
    Sfr rtc0adr;
  private:
    Sfr rtc0key;
    RTC0DAT rtc0dat;
};

#endif
