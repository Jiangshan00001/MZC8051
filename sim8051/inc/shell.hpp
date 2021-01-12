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

#ifndef _SHELL_HPP
#define _SHELL_HPP

#include "cpu8051.hpp"
#include "trie.hpp"
#include <string>
#include <vector>

enum class ParameterType
{
  String,
  Numeric
};

class Parameter
{
  public:
    ParameterType type;
    std::string string;
    int number;
    Parameter(int number);
    Parameter(std::string string);
};

class CommandCallback
{
  public:
    virtual void OnCommand(Cpu8051 &cpu, std::string command, std::vector<Parameter*> parameters) = 0;
};

class CommandInfo
{
  public:
    std::string command;
    CommandCallback *callback;
    std::vector<ParameterType> parameterTypes;
    CommandInfo(std::string command, CommandCallback *callback, std::vector<ParameterType> parameterTypes);
};

class Shell
{
  public:
    Shell();
    Cpu8051 cpu;
    Trie trie;
    std::vector<CommandInfo*> callbacks;
  public:
    //void CommandLoop();
    void RegisterCommand(std::string command, CommandCallback *callback, std::vector<ParameterType> parameters);
    void RegisterCommand(std::string command, CommandCallback *callback);

    void RunCommand(std::string command, std::vector<std::string> params);

};

#endif
