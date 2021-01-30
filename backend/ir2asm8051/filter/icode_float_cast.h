#ifndef ICODE_FLOAT_CAST_H
#define ICODE_FLOAT_CAST_H

#include "icode_visitor.h"

/// += -= *= /=
/// 如果是float变量和整形变量运算，则先将整形转换为float变量，再进行运算
///
/// float变量作为实参，进行函数调用，则是正常不需要转换。避免循环调用。
///

class icode_float_cast : public icode_visitor
{
public:
    icode_float_cast();
    void execute(icodes *ics);

    virtual int process_one_icode(class icode *ic, std::vector<class icode *> &parent, int index, void *user_data, class icode *iparent);


    icode *new_to_float_icode(icode *ic, icode **tmp_val);
    icode *new_float_to_int_icode(icode *ic, icode **tmp_val);
};

#endif // ICODE_FLOAT_CAST_H
