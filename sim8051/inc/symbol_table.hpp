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

#ifndef _SYMBOL_TABLE_HPP
#define _SYMBOL_TABLE_HPP

#include <string>
#include <cstdint>
#include <map>

class SymbolTable
{
  private:
    std::map<std::uint16_t, std::string> addressMap;
    std::map<std::string, std::uint16_t> symbolMap;
    SymbolTable() {};
  public:
    int ParseFile(const std::string &fileName);
    void LookupSymbol(const std::string &symbolName, std::uint16_t &address, bool &found);
    void LookupAddress(const std::uint16_t address, std::string &symbolName, bool &found);
    static SymbolTable& GetInstance()
    {
      static SymbolTable instance;

      return instance;
    }
    void RegisterSymbol(std::uint16_t address, std::string name);
};

#endif
