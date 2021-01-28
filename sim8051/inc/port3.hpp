#ifndef PORT3_H
#define PORT3_H

#include <string>
#include "alu.hpp"
#include "port.hpp"
#include "sfr.hpp"


class Port3 : public Port
{
public:
    Port3(std::string name, Scheduler &s, Alu &alu);
private:
  SfrIO p3;
};

#endif // PORT3_H
