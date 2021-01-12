#include"icode.h"
#include "mylog.h"
#include "icode_unresolved.h"


using mylog::cerr;
using mylog::cout;

icode_unresolved::icode_unresolved()
{
}

icode_unresolved::~icode_unresolved()
{

}

int icode_unresolved::process_one_icode(icode *ic, std::vector<icode *> &parent, int index, void *user_data, class icode *iparent)
{
    if((ic->m_type==ICODE_TYPE_SYMBOL_REF)&&
            (ic->result==NULL))
    {
        cerr<<"ERROR:unresolved symbol\n";
        cerr<<*ic;
        m_icodes.push_back(ic);
        return 1;
    }

    return 0;
}
