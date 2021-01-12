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
#include <string>
#include <set>
#include "sfr.hpp"
#include "block.hpp"
#include "alu.hpp"
#include "symbol_table.hpp"

Sfr::Sfr(std::string n, Block &b, std::uint8_t addr, std::uint8_t r, std::set<std::uint8_t> p) :
  address(addr),
  pages(p),
  name(n),
  block(b),
  resetValue(r)
{
  SymbolTable::GetInstance().RegisterSymbol(address, name);
  block.RegisterSfr(this);
}

std::string Sfr::GetName() const
{
  return name;
}

void Sfr::Write(std::uint8_t d)
{
  if (block.alu.GetTraceSfr())
  {
    printf("%s write %d\n", name.c_str(), d);
  }
  data = d;
}

std::uint8_t Sfr::Read()
{
  if (block.alu.GetTraceSfr())
  {
    printf("%s read %d\n", name.c_str(), data);
  }
  return data;
}

void Sfr::Reset()
{
  data = resetValue;
}

SfrBitAddressable::SfrBitAddressable(std::string n, Block &b, std::uint8_t addr, std::uint8_t r, std::set<std::uint8_t> p) :
  Sfr(n, b, addr, r, p)
{
  block.RegisterSfr(this);
}

void SfrBitAddressable::WriteBit(std::uint8_t bit, bool value)
{
  std::uint8_t bitShifted = 1 << bit;

  if (block.alu.GetTraceSfr())
  {
    printf("%s write bit %d %d\n", name.c_str(), bit, value);
  }

  data &= ~bitShifted;
  if (value)
  {
    data |= bitShifted;
  }
}

bool SfrBitAddressable::ReadBit(std::uint8_t bit)
{
  std::uint8_t bitShifted = 1 << bit;

  if (block.alu.GetTraceSfr())
  {
    printf("%s read bit %d %d\n", name.c_str(), bit, data & bitShifted);
  }

  return data & bitShifted;
}
