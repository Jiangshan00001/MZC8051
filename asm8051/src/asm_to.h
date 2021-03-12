#ifndef ASM_TO_H
#define ASM_TO_H
#include <string>
#include <map>
#include <vector>

#include "text_block.h"
#include "icode.h"
#include "hex_generator.h"

namespace NS_AMS8051HEX{


///
/// \brief The asm_to class
///
/// asm生成hex
/// 1 label处理：代码遍历2边。第一遍只处理生成标签地址。第二遍重新生成正确代码
/// 2 代码地址转为偏移地址：通过函数abs_to_rel实现
/// 3 跳转错误检查：如果跳转指令跳转太远跳转不到，则会报错。但是第一遍可能因为标签未找到，所以不能报错。
///   跳转如果跳转不到，返回单独的号：0x01.代表需要扩展跳转指令???
class asm_to
{
public:
    asm_to();
public:
    int compile();
    int add_src(std::string code_src, std::string file_name="");
    std::string generate_hex();
public:
        int m_is_debug;
private:
    void *m_inst;

    std::map<std::string, unsigned> m_label_code_address;
    std::map<std::string, unsigned> m_other_symbol_val;
    icode *m_top_icode;

    std::vector< std::vector<T_HEX_TEXT_BLOCK> > m_blocks;

    int visitor_ic(icode *ic);
    unsigned m_address;

    std::vector<hex_block> m_hex_blocks;
    int calc_icode_type(icode *ic);
    unsigned calc_icode_val(icode*ic);
    int process_macro(icode *ic);
    int m_is_second_pass;
};

}

#endif // ASM_TO_H
