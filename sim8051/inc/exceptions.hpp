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

#ifndef _EXCEPTIONS_HPP
#define _EXCEPTIONS_HPP

#include <exception>

class IllegalAddressException: public std::exception
{
  virtual const char *what() const throw()
  {
    return "Illegal address";
  }
};

class InvalidHexFileException: public std::exception
{
  virtual const char *what() const throw()
  {
    return "Illegal HEX file";
  }
};

class IllegalInstructionException: public std::exception
{
  virtual const char *what() const throw()
  {
    return "Illegal instruction";
  }
};

#endif

