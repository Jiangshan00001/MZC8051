#ifndef ICODE_PTR_IN_CALC_H
#define ICODE_PTR_IN_CALC_H

#include "icode_visitor.h"

///
/// \brief The icode_ptr_in_calc class
/// var_in:%a*2 ->
///     def_var_tmp $b;
///     b=var_in:%a*1
///     var_in:%b*1 <---
/// 对于指针内的内容读写，如果是多重指针，则此处翻译为1重指针的多次读写
///
///
///
class icode_ptr_in_calc : public icode_visitor
{
public:
    icode_ptr_in_calc();

    virtual int process_one_icode(class icode *ic, std::vector<class icode *> &parent, int index, void *user_data, class icode *iparent);

    void execute(icodes* ics);

};

#endif // ICODE_PTR_IN_CALC_H
