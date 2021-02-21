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
#include "memory.hpp"
#include "exceptions.hpp"

Memory::Memory(std::string n, std::uint16_t s) : name(n), size(s)
{
  data = new std::uint8_t[s];

}

Memory::Memory(std::string iname, unsigned isize, unsigned istart_addr)
{

}

std::uint8_t Memory::Read(std::uint16_t address) const
{
  if (address < size)
  {
    return data[address];
  }
  else
  {
    printf("Illegal memory read at %4.4x\n", address);
    throw new IllegalAddressException();
  }
}

void Memory::Write(std::uint16_t address, std::uint8_t value)
{

  if (address < size)
  {
    data[address] = value;

  }
  else
  {
    printf("Illegal memory write at %4.4x\n", address);
    throw new IllegalAddressException();
  }
}


std::uint16_t Memory::GetSize() const
{
  return size;
}
