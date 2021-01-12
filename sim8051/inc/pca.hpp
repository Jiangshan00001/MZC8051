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

#ifndef _PCA_HPP
#define _PCA_HPP

#include "alu.hpp"
#include "block.hpp"

class Pca: public Block
{
  public:
    Pca(std::string name, Scheduler &s, Alu &alu);
  private:
    Sfr pca0cpl2;
    Sfr pca0h;
    Sfr pca0l;
    Sfr pca0md;
    Sfr pca0cn;
    Sfr pca0cph2;
};

#endif
