#include <assert.h>
#include <vector>
#include <string>
#include "asm_context.h"
#include "asm_macro_keywords.h"
#include "split.h"
#include "asm8051_lex.h"
#include "number2str.h"
#include "str2number.h"

int ORG_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //eg: ORG 0100H
    T_ASM_CONTEXT &m_context = *mCtx;

    std::vector<asm_token> &tokens = mCtx->m_current_block.m_tokens;

    assert(tokens[0].val_str=="ORG");

    m_context.m_current_address = m_context.m_current_block.m_tokens[1].num;

    return 0;
}

int END_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //END
    return 0;
}

int DATA_CodeGen(T_ASM_CONTEXT *mCtx)
{
    /// BUSY DATA 30H


    std::vector<asm_token> &tokens = mCtx->m_current_block.m_tokens;
    assert(tokens.size()==3);

    ///在放入预处理之前，先求值
    /// 避免重复预处理情况：
    /// Fosc_KHZ    EQU 11059
    /// Timer0_Reload   EQU     (65536 - Fosc_KHZ)
    /// 如果不先求值，Timer0_Reload的结果会不对
    mCtx->eval_token(tokens[2],0,0);

    tokens[0].m_resolved=1;
    mCtx->m_preprocess_var[tokens[0].val_str] = tokens[2];
    return 0;
}


int EQU_CodeGen(T_ASM_CONTEXT *mCtx)
{
    /// TMP EQU 33H
    std::vector<asm_token> &tokens = mCtx->m_current_block.m_tokens;
    if(tokens.size()!=3)
    {
        std::cout<<"ERROR: line:"<<mCtx->m_current_block.m_line_no<<". "<<mCtx->m_current_block.m_source;
        std::cout<<"EQU need exactly 3 tokens. not" <<tokens.size() <<".\n";
        return 0;
    }


    ///在放入预处理之前，先求值
    /// 避免重复预处理情况：
    /// Fosc_KHZ    EQU 11059
    /// Timer0_Reload   EQU     (65536 - Fosc_KHZ)
    /// 如果不先求值，Timer0_Reload的结果会不对
    mCtx->eval_token(tokens[2],0,0);

    tokens[0].m_resolved=1;
    mCtx->m_preprocess_var[tokens[0].val_str] = tokens[2];
    return 0;
}


bool bit_addr_parse(unsigned a, unsigned b, unsigned &bit_addr)
{
    if((a>=0x20)&&(a<=0x2f))
    {
        bit_addr = (a-0x20)*8 +b;
    }
    else if((a>=0x80)&&(a<=0xff))
    {
        bit_addr = a + b;
    }
    else
    {
        bit_addr = 0;
        return false;
    }
    return true;
}


bool bit_token_parse(T_ASM_CONTEXT *mCtx, asm_token & bit_token, asm_token &tk1)
{

    ///bit时，20H.1对应的是-->00H
    /// stc8 的bit寻址：ram的20h->2fh  16个寄存器可位寻址，对应位地址：00-7fh
    /// stc8 的bit寻址：ram种sfr，地址能被8整除的16个寄存器可位寻址，对应位地址:0x80-0xff

    std::vector<std::string> wds = split(bit_token.val_str, ".");
    if((bit_token.type==TOKEN_NUM)&&(wds.size()<2))
    {
        //直接是一个位地址
        tk1.type = TOKEN_NUM;
        tk1.num = bit_token.num;
        tk1.val_str = bit_token.val_str;
        tk1.m_resolved = 1;
        bit_token.m_resolved = 1;
        return true;
    }
    unsigned long a = StrToNumber(wds[0]);
    unsigned long b = StrToNumber(wds[1]);
    unsigned int bit_addr=0;

    bool is_bit_addr = bit_addr_parse(a, b, bit_addr);
    if(!is_bit_addr )
    {
        if(mCtx->m_preprocess_var.find(wds[0])!=mCtx->m_preprocess_var.end())
        {
            wds[0] = mCtx->m_preprocess_var[wds[0]].val_str;
            a = StrToNumber(wds[0]);
            b = StrToNumber(wds[1]);
            is_bit_addr = bit_addr_parse(a, b, bit_addr);
        }
    }


    tk1.type=TOKEN_NUM;
    tk1.num = bit_addr;
    tk1.val_str = NumberToStr(bit_addr);
    tk1.m_resolved = 1;
    bit_token.m_resolved = 1;

    if(!is_bit_addr)
    {

        std::cout<<"ERROR:unknown bit address"<<bit_token.val_str<<"a:"<<a<<"b:"<<b;
        return false;
    }
    return true;
}

int BIT_CodeGen(T_ASM_CONTEXT *mCtx)
{
    /// BUSY BIT P1.5
    ///
    std::vector<asm_token> &tokens = mCtx->m_current_block.m_tokens;
    assert(tokens.size()==3);

    asm_token tk1;

    bit_token_parse(mCtx, tokens[2], tk1);

    tokens[0].m_resolved=1;
    mCtx->m_preprocess_var[tokens[0].val_str] = tk1;

    return 0;
}
int SBIT_CodeGen(T_ASM_CONTEXT *mCtx)
{
    ///SBIT PPP P1.3;
    std::vector<asm_token> &tokens = mCtx->m_current_block.m_tokens;
    assert(tokens.size()==3);

    asm_token tk1;
    bit_token_parse(mCtx, tokens[2], tk1);

    tokens[1].m_resolved=1;
    mCtx->m_preprocess_var[tokens[1].val_str] = tk1;

    return 0;
}


int NOMOD51_CodeGen(T_ASM_CONTEXT *mCtx)
{
    mCtx->m_preprocess_var.clear();
    return 0;
}
int SFR_CodeGen(T_ASM_CONTEXT *mCtx)
{
    std::vector<asm_token> &tokens = mCtx->m_current_block.m_tokens;
    assert(tokens.size()==3);


    ///在放入预处理之前，先求值
    /// 避免重复预处理情况：
    /// Fosc_KHZ    EQU 11059
    /// Timer0_Reload   EQU     (65536 - Fosc_KHZ)
    /// 如果不先求值，Timer0_Reload的结果会不对
    mCtx->eval_token(tokens[2],0,0);

    tokens[1].m_resolved=1;
    mCtx->m_preprocess_var[tokens[1].val_str] = tokens[2];
    return 0;
}
int USING_CodeGen(T_ASM_CONTEXT *mCtx)
{
    std::vector<asm_token> &tokens = mCtx->m_current_block.m_tokens;
    assert(tokens.size()==2);

    //FIXME using 代码应该是对应的PSW中bit的修改，暂时不修改，不起作用
    return 0;
}

int DB_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //变量初始定义
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;

    //添加生成的hex到m_hex_text

    for(unsigned i=0;i<m_tokens[0].m_childs.size();++i)
    {
        m_hex_text.push_back(m_tokens[0].m_childs[i].num);
    }

    //返回0代表正常结束
    return 0;

    //unknown code
    return -1;
}
