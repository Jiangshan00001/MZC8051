#include "c8051_api.h"

#include <iostream>
#include <fstream>


#include "../lex_yacc_adapt/driver.h"
#include "../context/comp_context.h"
#include "replace.h"

#include "main_var.h"

#include "simplecpp.h"
#include "dir_file.h"
#include "mylog.h"
#include "icodes.h"


using mylog::cout;
using mylog::cerr;



icodes* c8051_api::c_to_icode(std::istream & istr, std::string file_name, int is_debug)
{
    NS_C2IR::comp_context calc;
    NS_C2IR::Driver driver(calc);


    driver.trace_parsing = is_debug;
    driver.trace_scanning = is_debug;
    bool result = driver.parse_stream(istr, file_name);

    return calc.m_top_icodes;
}

icodes* c8051_api::c_to_icode(std::string file_name, int is_debug)
{
    std::ifstream fin(file_name);
    return c_to_icode(fin, file_name, is_debug);
}

icodes* c8051_api::c_to_icode(std::string file_str, std::string file_name, int is_debug)
{
    std::stringstream ss(file_str);
    return c_to_icode(ss, file_name, is_debug);
}

std::string c8051_api::c_to_yy(std::istream &istr, std::string file_name, int is_debug)
{
    NS_C2IR::comp_context calc;
    NS_C2IR::Driver driver(calc);


    calc.m_just_ret_tree=1;
    driver.trace_parsing = is_debug;
    driver.trace_scanning = is_debug;
    bool result = driver.parse_stream(istr, file_name);

    return calc.m_yy_tree;
}

std::string c8051_api::c_to_yy(std::string file_name, int is_debug)
{
    std::ifstream fin(file_name);
    return c_to_yy(fin, file_name, is_debug);
}

std::string c8051_api::c_to_yy(std::string file_str, std::string file_name, int is_debug)
{
    std::stringstream ss(file_str);
    return c_to_yy(ss, file_name, is_debug);
}

