#ifndef C8051_API_H
#define C8051_API_H

#include <vector>
#include <string>


/**
*
* @mainpage c8051
* @ref compile_intro
*
*
* **/

class icodes;

class c8051_api
{
public:

    //c语言代码转icode
    icodes* c_to_icode(std::istream &istr, std::string file_name, int is_debug);
    icodes* c_to_icode(std::string file_name, int is_debug);
    icodes* c_to_icode(std::string file_str, std::string file_name, int is_debug);

    //c转为语法树
    std::string c_to_yy(std::istream &istr, std::string file_name, int is_debug);
    std::string c_to_yy(std::string file_name, int is_debug);
    std::string c_to_yy(std::string file_str, std::string file_name, int is_debug);
};



#endif // MAIN_API_H
