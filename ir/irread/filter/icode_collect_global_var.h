#ifndef ICODE_COLLECT_GLOBAL_VAR_H
#define ICODE_COLLECT_GLOBAL_VAR_H


#include <string>
#include <vector>
#include "icode_visitor.h"


class icode_collect_global_var : public icode_visitor
{
public:
    icode_collect_global_var();

    void execute(icodes* ics);


    virtual int process_one_icode(class icode *ic, std::vector<class icode *> &parent, int index, void *user_data, class icode *iparent);


    //此处是找到的变量：带初始化指令的全局变量和初始化指令代码
    std::vector<class icode*> m_init_gvar;
    std::vector<class icode*> m_init_gvar_opr;
    /// 此处是不需要初始化的全局变量
    std::vector<class icode*> m_uninit_gvar;
};

#endif // ICODE_COLLECT_GLOBAL_VAR_H
