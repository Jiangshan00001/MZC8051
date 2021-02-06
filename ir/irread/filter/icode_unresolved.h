#ifndef ICODE_UNRESOLVED_H
#define ICODE_UNRESOLVED_H

#include <string>
#include <vector>
#include "icode_visitor.h"

class icode_unresolved: public icode_visitor
{
public:
    icode_unresolved();
    ~icode_unresolved();


    int process_one_icode(class icode *ic, std::vector<class icode *> &parent, int index, void *user_data, class icode *iparent);

    //此处是生成的icodes
    std::vector<class icode*> m_icodes;

};

#endif // ICODE_UNRESOLVED_H
