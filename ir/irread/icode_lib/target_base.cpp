#include "target_base.h"

target_base::target_base()
{

    m_type_bit_list_c51=
    {
        {"void", 0},
        {"bit", 1},
        {"bool", 8},
        {"char", 8},
        {"signed char", 8},
        {"unsigned char", 8},
        {"enum", 16},
        {"short", 16},
        {"signed short", 16},
        {"unsigned short", 16},
        {"short int", 16},
        {"signed short int", 16},
        {"unsigned short int", 16},
        {"int", 16},
        {"signed int", 16},
        {"unsigned int", 16},
        {"long", 32},
        {"signed long", 32},
        {"unsigned long", 32},
        {"long int", 32},
        {"signed long int", 32},
        {"unsigned long int", 32},
        {"float", 32},
        {"double", 32},
        {"sbit", 1},
        {"sfr", 8},
        {"sfr16", 16},
        {"sfr32", 32},
        {"GENERIC_PTR", 3*8},
    };

}
target_base::~target_base()
{

}

int target_base::get_basic_type_bit_width(const std::string &type_str)
{
    auto it = m_type_bit_list_c51.find(type_str);
    if(it!=m_type_bit_list_c51.end())
    {
        return it->second;
    }

    return 8;
}
