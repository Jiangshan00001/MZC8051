#include "port3.hpp"

Port3::Port3(std::string name, Scheduler &s, Alu &alu):
    Port(name, s, alu),
    p3("P3", *this, 0xb0, 0xff, {0x0, 0xf}, 3)
{
}
