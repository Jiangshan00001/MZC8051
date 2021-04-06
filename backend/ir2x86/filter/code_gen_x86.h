#ifndef CODE_GEN_X86_H
#define CODE_GEN_X86_H

#include <iostream>
#include <stack>
#include <deque>
#include "icode_visitor_const.h"
#include "reg_alloc2.h"

class code_gen_x86 : public icode_visitor_const
{
public:
    code_gen_x86();

    int execute(icodes* ics, std::stringstream &istr);


    void code_gen_db_init(icode *var, icode *var_init_opr, std::stringstream &istr);
    void code_gen_resb_init(icode *var, std::stringstream &istr);

    void code_gen_cdecl_func(icode *ic, std::stringstream &istr);
    void code_gen_cdecl_func_call(icode *ic, std::stringstream &istr);
    std::string get_var_size_qualifier(int ibitwidth);
private:
    virtual int process_one_icode_start(class icode *ic, void *user_data, class icode *iparent);
    virtual int process_one_icode_end(class icode *ic, void *user_data, class icode *iparent);


    std::string opr_get(icode * ic, std::stringstream &istr, bool add_size_quali=1);
    int get_bitwidth(icode *ic);

    std::deque<icode*> m_func_stack;
    std::deque<int> m_func_stack_byte_width;
    int m_esp;//stack pointer top
    int m_ebp;//stack base pointer


    ///返回数据相对ebp的位置
    int get_stack_pos(icode*var);

    reg_alloc2<std::string> m_Reg;

    int m_label_tmp_cnt;
    std::string creat_lb();
    std::string get_eax(icode *var_bitwidth);

};

#endif // CODE_GEN_X86_H
