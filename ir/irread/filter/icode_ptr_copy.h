#ifndef ICODE_PTR_COPY_H
#define ICODE_PTR_COPY_H

#include "icode_visitor.h"

///对变量的初始化复制操作，通过函数进行
class icode_ptr_copy : public icode_visitor
{
public:
    icode_ptr_copy();
    virtual int process_one_icode(class icode *ic, std::vector<class icode *> &parent, int index, void *user_data, class icode *iparent);

    std::string m_copy_func;



};

#endif // ICODE_PTR_COPY_H
