#ifndef ASM_CONTEXT_H
#define ASM_CONTEXT_H


#include <vector>
#include <string>
#include <map>
#include "text_block.h"
#include "asm_keywords.h"

#include "asm_token.h"

#include "lex_yacc/scanner.h"


#define DEBUG_ALL 1



/// 编译函数:
/// 返回值：0--正常。 -1--未找到合适的参数编译，没有正确未编译
///        1---需要二遍生成代码(例如label需要二次定位地址)；
typedef int(* CODE_GEN_FUNC_PTR) (class T_ASM_CONTEXT *mCtx);


class  T_ASM_CONTEXT
{
public:

    T_ASM_CONTEXT();
    ~T_ASM_CONTEXT();

    /// 0---成功生成代码； 1---需要二遍生成代码(例如label需要二次定位地址)； 2-其他错误

    ///当前行号--改名为： m_current_line_cnt
    int m_current_line_no;

    unsigned long m_current_address;///当前代码地址

    ///当前一行要处理的字符串
    T_HEX_TEXT_BLOCK m_current_block;

    //代码段，每次追加,每行一个block
    std::vector<T_HEX_TEXT_BLOCK> m_text_block;

    ///所有的命令，和对应的代码生成函数
    std::map<std::string, CODE_GEN_FUNC_PTR> m_line_key_word_ptr;

    ///所有的带TOKEN_MACRO的，
    std::map<std::string, CODE_GEN_FUNC_PTR> m_line_macro_ptr;


    ///记录每个label的地址
    std::map<std::string, unsigned long> m_label_address;

    ///预处理的数据，包括 EQU  DATA BIT等数据
    /// 都通过替换的方式来实现预处理
    std::map<std::string, asm_token> m_preprocess_var;

    ///记录每个需要更新label地址的位置
    std::vector<int> m_text_block_need_refresh_index;

public:
    ///一行的预处理。
    /// 去除空行，注释 和 \t符号
    std::string& asm_line_preprocess(std::string &mOneLine);

    ///在当前环境下，对某个token求值
    int eval_token(asm_token& tk, unsigned long curr_addr, unsigned curr_cmd_byte_size, int not_eval_label=0);

    // 对于 jnz jz sjmp等跳转指令，如果指令跳转范围达不到，则直接扩展为更长的跳转指令
    int m_jmp_auto_extend;

private:

    asm_token param_parse(std::string str1);
    ///判断一个字符串是否是标签格式。是 字符串+“：”符号 格式判断
    bool is_label(std::string str1, asm_token &tk);

    //用于扩展指令时，生成临时标签
    std::string get_tmp_label(std::string prefix);
public:
    ///返回值位扩展后的指令长度。如果没有扩展，返回0
    int extend_inst(int index);


public:
    std::string m_dir_source;
    int m_dir_line_no;



};

bool bit_addr_parse(unsigned a, unsigned b, unsigned &bit_addr);

#endif // ASM_CONTEXT_H

