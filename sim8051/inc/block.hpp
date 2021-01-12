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

#ifndef _BLOCK_HPP
#define _BLOCK_HPP

#include <string>
#include <map>
#include "sfr.hpp"

/*
 * "Block" is a superclass describing the commonalities of the various functional blocks in the system.
 * Each block can be reset, can be clocked, and has a number of Special Function Registers.
 * Blocks also report the number of ticks remaining to their next scheduled action.
 * The "ClockEvent" operation is called at the appropriate time to perform the scheduled actions.
 */

class Alu;
class Scheduler;

class Block
{
  public:
    Block(std::string name, Scheduler &scheduler, Alu &alu);
    virtual void Reset();
    void Tick(int ticks);
    void RegisterSfr(Sfr *sfr);
    Alu &alu;
    const std::string &GetName() const;
    int GetTicks();
    virtual int CalculateRemainingTicks();
    void ReportActive();
    int remainingTicks;
    Scheduler &scheduler;
  protected:
    std::string name;
    std::map<std::string, Sfr*> sfrRegisters;
    virtual void ClockEvent();
};

#endif
