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

#ifndef _MEMORY_HPP
#define _MEMORY_HPP

#include <cstdint>
#include <string>

class Memory
{
public:
    Memory(std::string name, std::uint16_t size);
    Memory(std::string iname, unsigned isize, unsigned istart_addr);


  public:
    std::uint16_t GetSize() const;
    std::uint8_t Read(std::uint16_t address) const;
    void Write(std::uint16_t address, std::uint8_t value);

protected:
    unsigned m_start_address;
//private:
    std::uint8_t *data;
    std::uint16_t size;

    std::string name;
};

#endif
