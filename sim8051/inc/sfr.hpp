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

#ifndef _SFR_HPP
#define _SFR_HPP

#include <set>
#include <cstdint>
#include <string>

class Block;

class Sfr
{
  public:
    Sfr(std::string name, Block &block, std::uint8_t address, std::uint8_t resetValue, std::set<std::uint8_t> pages);
    virtual void Write(std::uint8_t data);
    virtual std::uint8_t Read();
    virtual void Reset();
    std::uint8_t data;
    std::string GetName() const;
    std::uint8_t address;
    std::set<std::uint8_t> pages;
  protected:
    std::string name;
    Block &block;
    std::uint8_t resetValue;
};

class SfrBitAddressable: public Sfr
{
  public:
    SfrBitAddressable(std::string name, Block &block, std::uint8_t address, std::uint8_t resetValue, std::set<std::uint8_t> pages);
    virtual void WriteBit(std::uint8_t bit, bool value);
    virtual bool ReadBit(std::uint8_t bit);
};

#endif
