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

#include "command.hpp"
#include "shell.hpp"
#include "trie.hpp"
#include <locale.h>
//#include <ncurses.h>
#include <string>
#include <vector>

Parameter::Parameter(std::string s) : type(ParameterType::String), string(s)
{
}

Parameter::Parameter(int n) : type(ParameterType::Numeric), number(n)
{
}

CommandInfo::CommandInfo(std::string c, CommandCallback *ca, std::vector<ParameterType> p):
  command(c), callback(ca), parameterTypes(p)
{
}

Shell::Shell()
{
    cpu.Reset();
}

void Shell::RegisterCommand(std::string command, CommandCallback *callback, std::vector<ParameterType> parameters)
{
  trie.AddString(command);
  callbacks.push_back(new CommandInfo(command, callback, parameters));
}

void Shell::RegisterCommand(std::string command, CommandCallback *callback)
{
    return RegisterCommand(command, callback, {});
}

void Shell::RunCommand(std::string command, std::vector<std::string> params)
{

  int index;
  for (index = 0; index < callbacks.size(); index++)
  {
    if (!command.compare(callbacks[index]->command))
    {
      break;
    }
  }

  if(index==callbacks.size())
  {
      //command not found!
      return ;
  }

  std::vector<Parameter*> parameters;
  std::vector<ParameterType> &ptype = callbacks[index]->parameterTypes;


  if(ptype.size()>params.size())
  {
      printf("command params not match\n");
      return;
  }


  for(unsigned i=0;i<ptype.size();++i)
  {
      if(ptype[i]==ParameterType::String)
      {
        parameters.push_back( new Parameter(params[i]));
      }
      else
      {
          parameters.push_back( new Parameter(stoi(params[i], nullptr, 16)));
      }
  }

  printf("\n");
  callbacks[index]->callback->OnCommand(cpu, command, parameters);

  for(unsigned i=0;i<parameters.size();++i)
  {
      delete parameters[i];
  }
}


