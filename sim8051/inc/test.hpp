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

#ifndef _TEST_HPP
#define _TEST_HPP

#include <cstdint>
#include <string>

#include "cpu8051.hpp"

class TestCase: public Cpu8051Callbacks
{
  public:
    TestCase(std::string name);
    TestCase(std::string name, bool trace);
    virtual bool Run(Cpu8051 &cpu) = 0;
    void OnInstructionExecuted(Cpu8051 &handler);
    virtual bool OnGPIORead(Cpu8051 &handler, std::uint8_t port, std::uint8_t bit) = 0;
    virtual void OnGPIOWrite(Cpu8051 &handler, std::uint8_t port, std::uint8_t bit, bool value) = 0;
    virtual void OnUARTTx(Cpu8051 &handler, char tx);
    virtual void OnReset(Cpu8051 &handler);
    std::string GetName();
  private:
    std::string name;
    bool trace;
};

class TestSuite
{
  public:
    TestSuite(std::string hexFile, std::string symFile);
    void Add(TestCase &t);
    void Run();
  private:
    std::list<TestCase*> tests;
    Cpu8051 cpu;
    std::string hexFile, symFile;
};

#endif
