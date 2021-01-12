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
#include "port0.hpp"
#include "port2.hpp"
#include "sfr.hpp"

Port2::Port2(std::string name, Scheduler &s, Alu &a) :
  Port(name, s, a),
  p2("P2", *this, 0xa0, 0x80, {0x0, 0xf}, 2),
  xbr2("XBR2", *this, 0xe3, 0x00, {0x0})
{
}
