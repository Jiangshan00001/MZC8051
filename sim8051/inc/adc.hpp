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

#ifndef _ADC_HPP
#define _ADC_HPP

#include <string>
#include "alu.hpp"
#include "block.hpp"
#include "sfr.hpp"

class SfrADC0CN: public SfrBitAddressable
{
  public:
    SfrADC0CN(std::string name, Block &b, std::uint8_t address, std::uint8_t resetValue, std::set<std::uint8_t> pages);
    std::uint8_t Read();
    bool ReadBit(std::uint8_t bit);
};

class Adc: public Block
{
  public:
    Adc(std::string name, Scheduler &s, Alu &alu);
  private:
    Sfr toffh;
    Sfr toffl;
    Sfr adc0cf;
    Sfr adc0pwr;
    Sfr adc0ac;
    SfrADC0CN adc0cn;
    Sfr adc0mx;
    Sfr ref0cn;
    Sfr adc0gtl;
    Sfr adc0gth;
    Sfr adc0ltl;
    Sfr adc0lth;
    Sfr adc0l;
    Sfr adc0h;
};

#endif
