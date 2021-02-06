#include "icode.h"
#include "icode_collect_str.h"

icode_collect_str::icode_collect_str()
{
}

icode_collect_str::~icode_collect_str()
{

}

int icode_collect_str::process_one_icode(icode *ic, std::vector<icode *> &parent, int index, void *user_data, class icode *iparent)
{
    if(ic->m_type==ICODE_TYPE_CONST_STRING)
    {
        m_icodes.push_back(ic);
    }
    if(ic->m_type==ICODE_TYPE_CONST_LIST)
    {
        m_icodes.push_back(ic);
    }


    return 0;
}


