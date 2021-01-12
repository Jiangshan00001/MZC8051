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

#include <exception>
//#include <ncurses.h>
#include "block.hpp"
#include "alu.hpp"
#include "scheduler.hpp"

Block::Block(std::string n, Scheduler &s, Alu &a) : alu(a), remainingTicks(-1), scheduler(s), name(n)
{
}

const std::string &Block::GetName() const
{
  return name;
}

void Block::ReportActive()
{
  scheduler.ReportActive(this);
}

int Block::GetTicks()
{
  return remainingTicks;
}

void Block::Tick(int ticks)
{
  // '-1' indicates inactive block
  if (remainingTicks == -1)
  {
    return;
  }
  if (ticks > remainingTicks)
  {
    printf("Block %s remaining %d ticks %d\n", name.c_str(), remainingTicks, ticks);
    throw new std::runtime_error("Invalid tick");
  }
  remainingTicks -= ticks;
  if (remainingTicks == 0)
  {
    ClockEvent();
  }
}

void Block::Reset()
{
  for (std::map<std::string,Sfr*>::iterator i = sfrRegisters.begin(); i != sfrRegisters.end(); i++)
  {
    i->second->Reset();
  }
  remainingTicks = -1;
}

void Block::RegisterSfr(Sfr *sfr)
{
  alu.RegisterSfr(sfr);
  sfrRegisters[sfr->GetName()] = sfr;
}

int Block::CalculateRemainingTicks()
{
  return -1;
}

void Block::ClockEvent()
{
}
