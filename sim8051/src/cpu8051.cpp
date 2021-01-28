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

#include "cpu8051.hpp"
#include "rtc.hpp"
//#include <ncurses.h>

Cpu8051::Cpu8051() :
  alu("Alu", *this, 1024*64-1, 256, 1024*64-1),
  port0("Port0", *this, alu),
  port1("Port1", *this, alu),
  port2("Port2", *this, alu),
  port3("Port3", *this, alu),
  pca("Pca", *this, alu),
  system("System", *this, alu),
  uart("Uart", *this, alu),
  adc("Adc", *this, alu),
  rtc("Rtc", *this, alu),
  timer("Timer", *this, alu),
  ticks(0),
  activatedBlock(false)
{
  blocks.push_back(&alu);
  blocks.push_back(&port0);
  blocks.push_back(&port1);
  blocks.push_back(&port2);
  blocks.push_back(&port3);
  blocks.push_back(&pca);
  blocks.push_back(&system);
  blocks.push_back(&uart);
  blocks.push_back(&adc);
  blocks.push_back(&rtc);
  blocks.push_back(&timer);
  for (int i = 0; i < blocks.size(); i++)
  {
    activeBlocks.push_back(blocks[i]);
  }
  Reset();
}

void Cpu8051::ReportActive(Block *b)
{
  activatedBlock = true;
  activatedBlocks.push_back(b);
}

unsigned long long Cpu8051::GetTicks()
{
  return ticks;
}

void Cpu8051::Reset()
{
  ticks = 0;
  for (std::vector<Block*>::iterator i = blocks.begin(); i != blocks.end(); i++)
  {
    (*i)->Reset();
  }
}

void Cpu8051::InjectEvent(int deltaTicks, char c)
{
  externalEvents.push(std::make_pair(ticks + deltaTicks, c));
}

void Cpu8051::Tick()
{
  long long smallestTick = -1;
  std::list<Block*>::iterator i = activeBlocks.begin();
  while (i != activeBlocks.end())
  {
    std::list<Block*>::iterator j = i;
    long long tick = (*i)->GetTicks();
    i++;
    if (tick == -1)
    {
      activeBlocks.erase(j);
    }
    else if ((smallestTick == -1 || tick < smallestTick))
    {
      smallestTick = tick;
    }
  }

  if (externalEvents.size() == 0 && smallestTick <= 0)
  {
    printf("No upcoming event %4.4x\n", alu.GetPC());
    throw new std::runtime_error("No next event");
  }
  bool hasExternalEvent = false;
  ExternalEvent event;
  if (externalEvents.size())
  {
    if (externalEvents.top().first - ticks < smallestTick)
    {
      event = externalEvents.top();
      externalEvents.pop();
      hasExternalEvent = true;
      smallestTick = event.first - ticks;
    }
  }
  for (std::list<Block*>::iterator i = activeBlocks.begin(); i != activeBlocks.end(); i++)
  {
    (*i)->Tick(smallestTick);
  }
  ticks += smallestTick;
  if (hasExternalEvent)
  {
    uart.SimulateRx(event.second);
  }
  if (activatedBlock)
  {
    // Move any blocks that became active to the active list
    for (std::list<Block*>::iterator i = activatedBlocks.begin(); i != activatedBlocks.end(); i++)
    {
      bool found = false;
      for (std::list<Block*>::iterator j = activeBlocks.begin(); j != activeBlocks.end(); j++)
      {
        if (*i == *j)
        {
          found = true;
          break;
        }
      }
      if (!found)
      {
        activeBlocks.push_back(*i);
      }
    }
    activatedBlock = false;
    activatedBlocks.erase(activatedBlocks.begin(), activatedBlocks.end());
  }
}
