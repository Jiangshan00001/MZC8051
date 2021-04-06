// $Id$

#include <iostream>
#include <fstream>

#include "driver.h"
#include "comp_context.h"
#include "argv.h"

void main_t1()
{
    NS_IR2ICODE::comp_context calc(E_8051_TARGET);
    NS_IR2ICODE::Driver driver(calc);
	
	
	driver.trace_parsing = true;
	driver.trace_scanning = true;
	//driver.parse_stream("file_name_in", "somethin string");
	
    //bool result =
    driver.parse_string("string context", "input");
	
}

void run_stdin_input(NS_IR2ICODE::comp_context &calc, NS_IR2ICODE::Driver &driver)
{

    std::cout << "Reading expressions from stdin" << std::endl;

    std::string line;
    while( std::cout << "input: " &&
       std::getline(std::cin, line) &&
       !line.empty() )
    {
        bool result = driver.parse_string(line, "input");

        if (result)
        {
            #if 0
            for (unsigned int ei = 0; ei < calc.expressions.size(); ++ei)
            {
            std::cout << "tree:" << std::endl;
            calc.expressions[ei]->print(std::cout);
            std::cout << "evaluated: "
                  << calc.expressions[ei]->evaluate()
                  << std::endl;
            }
            #endif
        }
    }
}


#ifdef QT_WID
int main2(int argc, char *argv[])
#else
int main(int argc, char *argv[])
#endif
{
    ArgsParser args(argc, argv);



    NS_IR2ICODE::comp_context calc(E_8051_TARGET);
    NS_IR2ICODE::Driver driver(calc);
    //bool readfile = false;


    if(args.HaveOption('p'))
    {
        driver.trace_parsing = true;
    }
    if(args.HaveOption('s'))
    {
        driver.trace_scanning = true;
    }

    std::string input_file_name = args.GetOption('i');
    std::string output_file_name = args.GetOption('o');

    if(input_file_name.size()==0)
    {
        //stdin输入
        run_stdin_input(calc, driver);
        return 0;
    }

    driver.parse_file(input_file_name);

    std::string to_out = calc.m_top_icodes->m_top_icodes->to_str();

    if(output_file_name.size()>0)
    {
        std::ofstream ofile(output_file_name);
        ofile.write(to_out.c_str(), to_out.size());
    }
}


