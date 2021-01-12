// $Id$

#include <iostream>
#include <fstream>


int main()
{
	
	return 0;
}

#if 0
#include "driver.h"
#include "comp_context.h"


void main_t1()
{
    NS_C2IR::comp_context calc;
    NS_C2IR::Driver driver(calc);
	
	
	driver.trace_parsing = true;
	driver.trace_scanning = true;
	//driver.parse_stream("file_name_in", "somethin string");
	
    //calc.clearExpressions();
	bool result = driver.parse_string("string context", "input");
	
}


#ifdef QT_WID
int main2(int argc, char *argv[])
#else
int main(int argc, char *argv[])
#endif
{
    NS_C2IR::comp_context calc;
    NS_C2IR::Driver driver(calc);
    bool readfile = false;

    for(int ai = 1; ai < argc; ++ai)
    {
        if (argv[ai] == std::string ("-p")) {
            driver.trace_parsing = true;
        }
        else if (argv[ai] == std::string ("-s")) {
            driver.trace_scanning = true;
        }

    }

    std::cout << "Reading expressions from stdin" << std::endl;

    std::string line;
    while( std::cout << "input: " &&
	   std::getline(std::cin, line) &&
	   !line.empty() )
    {
        calc.clearExpressions();
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
#endif
