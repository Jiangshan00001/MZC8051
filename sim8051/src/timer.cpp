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
#include <stdexcept>
#include <string>
#include "block.hpp"
#include "sfr.hpp"
#include "timer.hpp"

#define T0M 4
#define SCA 3
#define TR0 16
#define TR0_BIT 4

TCON::TCON(std::string name, Block &block, std::uint8_t address, std::uint8_t resetValue, std::set<std::uint8_t> pages):
  SfrBitAddressable(name, block, address, resetValue, pages)
{
}

void TCON::Write(std::uint8_t value)
{
  bool isEnabled = (!(data & TR0) && (value & TR0));

  Sfr::Write(value);
  block.remainingTicks = block.CalculateRemainingTicks();

  if (isEnabled)
  {
    // If we're enabling the timer, we need to report that we have an upcoming event
    block.ReportActive();
  }
}

void TCON::WriteBit(std::uint8_t bit, bool value)
{
  bool isEnabled = (!(data & TR0) && (bit == TR0_BIT) && value);

  SfrBitAddressable::WriteBit(bit, value);
  block.remainingTicks = block.CalculateRemainingTicks();

  if (isEnabled)
  {
    // If we're enabling the timer, we need to report that we have an upcoming event
    block.ReportActive();
  }  
}

Timer::Timer(std::string name, Scheduler &s, Alu &a) :
  Block(name, s, a),
  ckcon("CKCON", *this, 0x8e, 0, {0x0}),
  th1("TH1", *this, 0x8d, 0, {0x0}),
  th0("TH0", *this, 0x8c, 0, {0x0}),
  tl1("TL1", *this, 0x8b, 0, {0x0}),
  tl0("TL0", *this, 0x8a, 0, {0x0}),
  tmod("TMOD", *this, 0x89, 0, {0x0}),
  tcon("TCON", *this, 0x88, 0, {0x0}),
  tmr2rll("TMR2RLL", *this, 0xca, 0, {0x0}),
  tmr2rlh("TMR2RLH", *this, 0xcb, 0, {0x0}),
  tmr2l("TMR2L", *this, 0xcc, 0, {0x0}),
  tmr2h("TMR2H", *this, 0xcd, 0, {0x0}),
  tmr2cn("TMR2CN", *this, 0xc8, 0, {0x0})
{
}

void Timer::ClockEvent()
{
  // Timer wraps, recalculate the time to the next event
  tl0.Write(0);
  th0.Write(0);
  remainingTicks = CalculateRemainingTicks();
  alu.TimerInterrupt(0);
}

int Timer::CalculateRemainingTicks()
{
  // Only support Timer0 in 16-bite mode for now

  if (tcon.data & TR0)
  {
    int divisor;
    int timerConfig = tl0.data + 256 * th0.data;

    // Check timer configuration, T0M and SCA bits in CKCON
    if (ckcon.data & T0M)
    {
      divisor = 1;
    }
    else
    {
      int sca = ckcon.data & SCA;
      if (sca == 0)
      {
        divisor = 12;
      }
      else if (sca == 1)
      {
        divisor = 4;
      }
      else if (sca == 2)
      {
        divisor = 48;
      }
      else
      {
        throw new std::runtime_error("illegal timer configuration");
      }
    }

    // Timer counting upwards
    return divisor * (65536 - timerConfig);
  }
  else
  {
    return -1;
  }
}
