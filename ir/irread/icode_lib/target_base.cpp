#include "target_base.h"

target_base::target_base(TAG_E_TARGET_BASE_TYPE typ)
{
    m_target_type = typ;//E_8051_TARGET;

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


    m_type_bit_list_win64 =
    {
        {"void", 0},
        {"bit", 1},
        {"bool", 32},
        {"char", 8},
        {"signed char", 8},
        {"unsigned char", 8},
        {"enum", 32},
        {"short", 32},
        {"signed short", 32},
        {"unsigned short", 32},
        {"short int", 32},
        {"signed short int", 32},
        {"unsigned short int", 32},
        {"int", 32},
        {"signed int", 32},
        {"unsigned int", 32},
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
        {"GENERIC_PTR", 8*8},
    };


}
target_base::~target_base()
{

}

int target_base::get_basic_type_bit_width(const std::string &type_str)
{
    switch(m_target_type)
    {
    case E_8051_TARGET:
    {
        auto it = m_type_bit_list_c51.find(type_str);
        if(it!=m_type_bit_list_c51.end())
        {
            return it->second;
        }

        return 8;
    }
        break;
    case E_WIN64_TARGET:
    {
        auto it = m_type_bit_list_win64.find(type_str);
        if(it!=m_type_bit_list_win64.end())
        {
            return it->second;
        }

        return 32;
    }
        break;
    default:
        return 32;
        break;
    }


}
