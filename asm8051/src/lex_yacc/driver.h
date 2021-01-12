#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include <iostream>

#include "../asm_token.h"
#include "scanner.h"

namespace asm_lex_stuff {


class driver
{
public:
    driver();

    std::string m_stream_name;

    Scanner *m_lexer;
    bool parse_stream(std::istream& in, const std::string& sname);


    asm_token m_token_result;

    int m_parse_success;
};


}

#endif // DRIVER_H
