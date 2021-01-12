#include "driver.h"

namespace asm_lex_stuff {



driver::driver()
{
    m_lexer=NULL;
    m_parse_success = 0;
}


bool driver::parse_stream(std::istream& in, const std::string& sname)
{
    m_stream_name = sname;

    Scanner scanner(&in);
    scanner.set_debug(0);
    this->m_lexer = &scanner;

    Parser parser(this);
    parser.set_debug_level(0);

    //pcompi->mp_parser = &parser;
    //pcompi->mp_scanner = &scanner;
    //scanner.pcompi = pcompi;

    return (parser.parse() == 0);
}





}
