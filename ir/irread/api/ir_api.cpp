#include "ir_api.h"
#include "target_base.h"
#include "../context/comp_context.h"
#include "../lex_yacc_adapt/driver.h"
using namespace NS_IR2ICODE;

ir_api::ir_api()
{
}

std::string ir_api::icode_to_ir(icodes *ic)
{

    return ic->m_top_icodes->to_str();
}

icodes *ir_api::ir_to_icode(std::istream &istr, std::string file_name, int is_debug)
{
    NS_IR2ICODE::comp_context calc(E_8051_TARGET);
    NS_IR2ICODE::Driver driver(calc);


    driver.trace_parsing = is_debug;
    driver.trace_scanning = is_debug;
    driver.parse_stream(istr, file_name);

    return calc.m_top_icodes;

}


icodes *ir_api::ir_to_icode(std::string file_name, int is_debug)
{
    NS_IR2ICODE::comp_context calc(E_8051_TARGET);
    NS_IR2ICODE::Driver driver(calc);


    driver.trace_parsing = is_debug;
    driver.trace_scanning = is_debug;
    driver.parse_file(file_name);

    return calc.m_top_icodes;
}
icodes* ir_api::ir_to_icode(std::vector<std::string> file_name, int is_debug)
{
    icodes * all=NULL;
    for(int i=0;i<file_name.size();++i)
    {
        NS_IR2ICODE::comp_context calc(E_8051_TARGET);
        NS_IR2ICODE::Driver driver(calc);

        if(all!=NULL)
        {
            delete calc.m_top_icodes;
            calc.m_top_icodes =all;
        }

        driver.trace_parsing = is_debug;
        driver.trace_scanning = is_debug;
        driver.parse_file(file_name[i]);


        all= calc.m_top_icodes;
    }
    return all;

}
