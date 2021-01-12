#ifndef IR_API_H
#define IR_API_H

#include <string>
#include "icodes.h"
class icode_manage;

class ir_api
{
public:
    ir_api();


    std::string icode_to_ir(icodes *ic);
    icodes* ir_to_icode(std::istream &istr, std::string file_name, int is_debug);
    icodes* ir_to_icode(std::string file_name, int is_debug);
    icodes* ir_to_icode(std::vector<std::string> file_name, int is_debug);
public:

};

#endif // IR_API_H
