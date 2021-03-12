#include "icode.h"


namespace NS_AMS8051HEX{

icode::icode()
{

}

icode::icode(int itype)
{
    m_type = itype;

}

int icode::merge_icode(icode *ic)
{
    if(ic==NULL)return 0;

    if(ic->m_type==ICODE_TYPE_BLOCK)
    {
        sub_icode.insert(sub_icode.end(), ic->sub_icode.begin(), ic->sub_icode.end());
    }
    else
    {
        sub_icode.push_back(ic);
    }



    return 0;
}


}


