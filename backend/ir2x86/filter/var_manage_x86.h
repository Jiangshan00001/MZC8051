#ifndef VAR_MANAGE_X86_H
#define VAR_MANAGE_X86_H

#include "var_manage_base.h"


enum TAG_X86_VAR_TYPE{
    X86_VAR_TYPE_DATA=1,
    X86_VAR_TYPE_BSS,
    X86_VAR_TYPE_STACK,
    X86_VAR_TYPE_REG,

};






class var_manage_x86 : public var_manage_base
{
public:
    var_manage_x86();
public:


    virtual int process_one_icode(class icode *ic, std::vector<class icode *> &parent, int index, void *user_data, class icode *iparent);


    void execute(icodes* ics);

    int collect_level0_var(icode *ic);
    int collect_ret_var(icode *ic);
    int collect_arg_var(icode *ic);
    int collect_static_local_var(icode *ic);
    int collect_local_var(icode *ic);
    int collect_const(icode* ic);

    //此处是找到的变量：带初始化指令的全局变量和初始化指令代码
    std::vector<class icode*> m_init_gvar;
    std::vector<class icode*> m_init_gvar_opr;
    /// 此处是不需要初始化的全局变量
    std::vector<class icode*> m_uninit_gvar;

    /// 函数返回值， 函数参数，局部变量，静态局部变量
    std::vector<class icode*> m_ret_var;
    std::vector<class icode*> m_arg_var;
    std::vector<class icode*> m_local_var;//< 此局部变量，不包括static类型的局部变量
    std::vector<class icode*> m_static_local_var;//<- 此为静态局部变量。如果有初始化，则在m_static_local_var_opt中，否则为NULL
    std::vector<class icode*> m_static_local_var_opt;

    ///代码中的常量字符串和常量字符列表
    std::vector<icode*> m_const_string;
    std::vector<icode*> m_const_list;




};

#endif // VAR_MANAGE_X86_H
