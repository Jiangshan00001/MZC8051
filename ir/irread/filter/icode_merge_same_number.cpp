#include "icode.h"
#include "icode_merge_same_number.h"
#include "mylog.h"

using mylog::cdbg;

icode_merge_same_number::icode_merge_same_number()
{
}

int icode_merge_same_number::process_one_icode(icode *ic, std::vector<icode *> &parent, int index, void *user_data, icode *iparent)
{
    if(ic->m_type==ICODE_TYPE_SYMBOL_REF)
    {
        if(ic->result)
        {
            if(m_icode_map.find(ic->result->m_icode_number)!=m_icode_map.end())
            {
                ic->result = m_icode_map[ic->result->m_icode_number];
                return 1;
            }
        }
    }

    if(ic->m_parent!=NULL)
    {
        if(m_icode_map.find(ic->m_parent->m_icode_number)!=m_icode_map.end())
        {
            ic->m_parent = m_icode_map[ic->m_parent->m_icode_number];
            return 1;
        }
    }



    if(m_icode_map.find(ic->m_icode_number)==m_icode_map.end())
    {
        m_icode_map[ic->m_icode_number] = ic;
    }
    else
    {
        cdbg<<"icode_merge_same_number:"<< ic->m_icode_number<<"\n";
        //ic = m_icode_map[ic->m_icode_number];
        this->m_to_rep_ic = m_icode_map[ic->m_icode_number];
        return 1;
    }
    return 0;
}


