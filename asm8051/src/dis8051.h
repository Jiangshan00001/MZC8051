#ifndef DIS8051_H
#define DIS8051_H

#include <string>
#include<map>
#include "asm_table.h"
#include "dis_keywords.h"
#include "text_block.h"

class dis8051
{
public:
    dis8051();
    ~dis8051();
public:
    /// 输入的是hex，返回的是反汇编后的汇编代码
    std::string add_hex_str(std::string hex_format_str);

    int clear();


    int load_inst();

private:
    std::string dis_one_inst(std::string mhex, hex_code_asm_table &inst_info, unsigned curr_addr);
    //std::string dis_one_inst_default(std::string mhex, hex_code_asm_table &inst_info);

    std::map<unsigned int, hex_code_asm_table> m_inst_dis;
    std::map<unsigned, DIS_FUNC_PTR>  m_inst_dis_func;

    std::vector<T_HEX_TEXT_BLOCK> m_text_block;
    std::map<unsigned int, std::string> m_label_code_address;
    std::string generate_str();

public:

    ///当前地址curr_addr 和inst_byte_cnt只有在相对偏移地址计算时有用
    std::string CODE_ADDR_DIS(unsigned addr, unsigned curr_addr=0, unsigned inst_byte_cnt=0);
    std::string ABS_CODE_ADDR_DIS(unsigned addr, unsigned curr_addr=0, unsigned inst_byte_cnt=0);
    ///FIXME 此处相对地址addr 只能是8bit负数
    std::string REL_CODE_ADDR_DIS(unsigned addr, unsigned curr_addr=0, unsigned inst_byte_cnt=0);
    std::string DATA_ADDR_DIS(unsigned addr, unsigned curr_addr=0, unsigned inst_byte_cnt=0);
    std::string BIT_ADDR_DIS(unsigned addr, unsigned curr_addr=0, unsigned inst_byte_cnt=0);
    std::string DATA_VALUE_DIS(unsigned addr, unsigned curr_addr=0, unsigned inst_byte_cnt=0);
    std::string MBIT_ADDR_DIS(unsigned addr, unsigned curr_addr=0, unsigned inst_byte_cnt=0);

};

#endif // DIS8051_H

