#include <assert.h>
#include <time.h>
#include <iostream>
#include <string>
#include <sstream>
#include "asm_context.h"
#include "asm_keywords.h"
#include "split.h"
#include "asm8051_lex.h"
#include "asm_macro_keywords.h"



T_ASM_CONTEXT::T_ASM_CONTEXT()
{
    m_current_line_no=0;
    m_current_address = 0;
    m_jmp_auto_extend=1;



    asm8051_context_init(this);

    this->m_line_key_word_ptr["DB"] = &DB_CodeGen;



    m_line_macro_ptr["ORG"]= &ORG_CodeGen;
    m_line_macro_ptr["END"]= &END_CodeGen;
    m_line_macro_ptr["DATA"]= &DATA_CodeGen;
    m_line_macro_ptr["XDATA"]= &DATA_CodeGen;

    m_line_macro_ptr["EQU"]= &EQU_CodeGen;
    m_line_macro_ptr["BIT"]= &BIT_CodeGen;
    m_line_macro_ptr["$NOMOD51"]= &NOMOD51_CodeGen;
    m_line_macro_ptr["SFR"]= &SFR_CodeGen;
    m_line_macro_ptr["SBIT"]= &SBIT_CodeGen;
    m_line_macro_ptr["USING"]= &USING_CodeGen;
}

std::string T_ASM_CONTEXT::get_tmp_label(std::string prefix)
{

  static unsigned long tmp_label = 0;
  std::stringstream asm_str;
  asm_str<<"__asm_context_"<< prefix<<"_"<< time(NULL)<<"_"<<  tmp_label;

  tmp_label++;
  return asm_str.str();
}


T_ASM_CONTEXT::~T_ASM_CONTEXT()
{

}

