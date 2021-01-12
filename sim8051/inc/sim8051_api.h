#ifndef SIM8051_API_H
#define SIM8051_API_H

#include <string>

int sim8051_run(std::string hex_file);
int sim8051_run_str(std::string hex_str);

#endif // SIM8051_API_H
