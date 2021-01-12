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

#include <string>
#include "port.hpp"
#include "port1.hpp"
#include "sfr.hpp"

Port1::Port1(std::string name, Scheduler &s, Alu &a) :
  Port(name, s, a),
  p1mdin("P1MDIN", *this, 0xf2, 0xff, {0x0}),
  p1mdout("P1MDOUT", *this, 0xa5, 0x00, {0x0}),
  p1("P1", *this, 0x90, 0xff, {0x0,0xf}, 1),
  p1skip("P1SKIP", *this, 0xd5, 0x00, {0x0})
{
}
