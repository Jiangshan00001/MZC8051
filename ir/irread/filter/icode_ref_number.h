#ifndef ICODE_REF_NUMBER_H
#define ICODE_REF_NUMBER_H

#include "icode_visitor.h"

///计算引用数,用于后期变量的清理，不被引用的变量去除，和常亮传播
class icode_ref_number : public icode_visitor
{

public:
    icode_ref_number();
public:
    int process_one_icode(class icode *ic, std::vector<class icode *> &parent, int index, void *user_data, class icode *iparent);
    int process_one_icode_clean(class icode *ic, std::vector<class icode *> &parent, int index, class icode *iparent);
    int process_one_icode_addref(class icode *ic, std::vector<class icode *> &parent, int index, class icode *iparent);

    void execute(class icodes* ics);


};

#endif // ICODE_REF_NUMBER_H
