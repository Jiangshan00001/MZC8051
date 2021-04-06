// $Id$
/** \file driver.cc Implementation of the example::Driver class. */

#include <fstream>
#include <sstream>

#include "driver.h"
#include "scanner.h"
#include "comp_context.h"
#include "mylog.h"
using mylog::cerr;
using mylog::cdbg;


namespace NS_C2IR {

Driver::Driver(comp_context &_calc)
    : trace_scanning(false),
      trace_parsing(false),
      calc(_calc)
{
    calc.mp_driver = this;
    this->lexer = NULL;
    this->parser = NULL;
}

bool Driver::parse_stream(std::istream& in, const std::string& sname)
{
    streamname = sname;

    Scanner scanner(*this, &in);
    scanner.set_debug(trace_scanning);
    this->lexer = &scanner;

    Parser parser(*this);
    this->parser = &parser;
    parser.set_debug_level(trace_parsing);
    return (parser.parse() == 0);
}

bool Driver::parse_file(const std::string &filename)
{
    std::ifstream in(filename.c_str());
    if (!in.good()) return false;
    return parse_stream(in, filename);
}

bool Driver::parse_string(const std::string &input, const std::string& sname)
{
    std::istringstream iss(input);
    return parse_stream(iss, sname);
}

void Driver::error(const class location& l,
		   const std::string& m)
{
    cerr << l << ": " << m << std::endl;
#if 0
    if(parser!=NULL)
    {
        for(unsigned i=0;i<parser->semantic_stack_type.height();++i)
        {
            cerr<<parser->semantic_stack_type[i]    <<" ";
        }
    }
    cerr<<"\n";
#endif

}

void Driver::error(const std::string& m)
{
    std::cerr << m << std::endl;
}

} // namespace example
