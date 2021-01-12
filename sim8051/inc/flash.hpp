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

#ifndef _FLASH_HPP
#define _FLASH_HPP

#include <string>
#include <cstdint>
#include "memory.hpp"

class Flash : public Memory
{
  public:
    Flash(std::string name, std::uint16_t size);
    int ParseHex(std::string fileName);
    int ParseHexStr(std::string hex_format_str);
    int ParseHexStream(std::istream & hex_stream );
};

#endif
