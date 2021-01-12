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

#include <iostream>
#include "pca.hpp"
#include "sfr.hpp"
#include "block.hpp"

Pca::Pca(std::string name, Scheduler &s, Alu &a):
  Block(name, s, a),
  pca0cpl2("PCA0CPL2", *this, 0xeb, 0x00, {0x0}),
  pca0h("PCA0H", *this, 0xfa, 0x00, {0x0}),
  pca0l("PCA0L", *this, 0xf9, 0x00, {0x0}),
  pca0md("PCA0MD", *this, 0xd9, 0x40, {0x0}),
  pca0cn("PCA0CN", *this, 0xd8, 0x00, {0x0}),
  pca0cph2("PCA0CPH2", *this, 0xec, 0x00, {0x0})
{
}
