#include "icode_label.h"
#include "icode.h"
std::string icode::get_block_start_label()
{
    std::stringstream retA;
    retA<<"__block__" << this->m_icode_number<<"_start";
    return retA.str();
}

std::string icode::get_block_end_label()
{
    std::stringstream retA;
    retA<<"__block__" << this->m_icode_number<<"_end";
    return retA.str();
}
