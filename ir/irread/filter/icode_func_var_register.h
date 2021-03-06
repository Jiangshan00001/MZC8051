#ifndef ICODE_FUNC_VAR_REGISTER_H
#define ICODE_FUNC_VAR_REGISTER_H

#include "icode_visitor.h"

///
/// \brief The icode_func_var_register class
/// 对 regparams参数进行处理
/// 此参数是函数属性。 描述了函数的返回值和各参数的寄存器使用情况
/// 通过
class icode_func_var_register : public icode_visitor
{
public:
    icode_func_var_register();


    virtual int process_one_icode(class icode *ic, std::vector<class icode *> &parent, int index, void *user_data, class icode *iparent);

};

#endif // ICODE_FUNC_VAR_REGISTER_H
