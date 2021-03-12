#ifndef TO_ASM_H
#define TO_ASM_H

#include <iostream>
#include <string>
#include <map>

#include "dis_funcs.h"
#include "text_block.h"

namespace NS_AMS8051HEX{
class to_asm
{
public:
    to_asm();

public:
    /// 输入的是hex，返回的是反汇编后的汇编代码
    /// 因为汇编代码需要添加地址标号，但是是否需要标号是遇到跳转指令时才知道。
    /// 所以需要处理两边，才能正常输出反汇编代码。
    /// 为了添加标号方便，此处对反汇编的代码按照指令记录下来。
    std::string add_hex_str(std::string hex_format_str);

    std::string type_to_str_TOKEN_AB(unsigned value, unsigned curr_addr, int inst_byte_cnt);
    std::string type_to_str_TOKEN_ACC(unsigned value, unsigned curr_addr, int inst_byte_cnt);
    std::string type_to_str_TOKEN_AT_A_PLUS_DPTR(unsigned value, unsigned curr_addr, int inst_byte_cnt);
    std::string type_to_str_TOKEN_AT_A_PLUS_PC(unsigned value, unsigned curr_addr, int inst_byte_cnt);
    std::string type_to_str_TOKEN_AT_DPTR(unsigned value, unsigned curr_addr, int inst_byte_cnt);
    std::string type_to_str_TOKEN_C(unsigned value, unsigned curr_addr, int inst_byte_cnt);
    std::string type_to_str_TOKEN_DPTR(unsigned value, unsigned curr_addr, int inst_byte_cnt);

    std::string type_to_str_TOKEN_ADDR11(unsigned value, unsigned curr_addr, int inst_byte_cnt);
    std::string type_to_str_TOKEN_ADDR16(unsigned value, unsigned curr_addr, int inst_byte_cnt);
    std::string type_to_str_TOKEN_AT_RI(unsigned value, unsigned curr_addr, int inst_byte_cnt);
    std::string type_to_str_TOKEN_BIT(unsigned value, unsigned curr_addr, int inst_byte_cnt);
    std::string type_to_str_TOKEN_DIRECT(unsigned value, unsigned curr_addr, int inst_byte_cnt);
    std::string type_to_str_TOKEN_REL(unsigned addr, unsigned curr_addr, int inst_byte_cnt);
    std::string type_to_str_TOKEN_RN(unsigned value, unsigned curr_addr, int inst_byte_cnt);
    std::string type_to_str_TOKEN_IMM16(unsigned value, unsigned curr_addr, int inst_byte_cnt);
    std::string type_to_str_TOKEN_IMM8(unsigned value, unsigned curr_addr, int inst_byte_cnt);
    std::string type_to_str_TOKEN_NBIT(unsigned value, unsigned curr_addr, int inst_byte_cnt);

    std::map<unsigned,  DIS_FUNC_PTR> m_dis_funcs;
    std::map<unsigned, std::string> m_label_code_address;


    std::vector< std::vector<T_HEX_TEXT_BLOCK> > m_blocks;
    ///hex_to_code1 遍历hex，只生成代码
    int hex_to_code1(std::string &hex_format_str);
    /// 函数根据生成的代码，添加标签，生成汇编代码
    std::string hex_to_code2();
};

}//namespace

#endif // TO_ASM_H
