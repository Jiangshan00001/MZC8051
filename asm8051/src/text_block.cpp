#include "text_block.h"

T_HEX_TEXT_BLOCK::T_HEX_TEXT_BLOCK()
{
}

int T_HEX_TEXT_BLOCK::set_src_text(std::string src, int line_no)
{
    m_source = src;
    m_line_no = line_no;
    m_address = 0;
    return 0;
}

int T_HEX_TEXT_BLOCK::set_address()
{

    return 0;
}

std::string T_HEX_TEXT_BLOCK::get_hex()
{

    return "";
}


