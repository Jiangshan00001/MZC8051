#ifndef ICODE_POSITIVE_OPR_H
#define ICODE_POSITIVE_OPR_H

#include "icode_visitor.h"

///正号翻译，将正好翻译转移为=号. a=+3;---> right=3;result=a; opr=+.
class icode_positive_opr : public icode_visitor
{
public:
    icode_positive_opr();

    void execute(icodes* ics);

    virtual int process_one_icode(class icode *ic, std::vector<class icode *> &parent, int index, void *user_data, class icode *iparent);

};

#endif // ICODE_POSITIVE_OPR_H
