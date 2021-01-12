#include "icode.h"
#include "icode_replace.h"

icode_replace::icode_replace()
{
}


int icode_replace::process_one_icode(icode *ic, std::vector<icode *> &parent, int index, void *user_data, class icode *iparent)
{
    for(auto it=sym_rep.begin();it!=sym_rep.end();++it)
    {
        if(ic->m_type==ICODE_TYPE_SYMBOL_REF)
        {
            if(ic->result!=NULL)
            {
                if(ic->result==it->first)
                {
                    ic->result = it->second;
                    return 1;
                }
            }
        }

        if(ic!=it->first)
        {
            continue;
        }
        /// 如果找到ic,则删除
        //assert(parent[index]==ic);
        //parent.erase(parent.begin()+index);
        this->m_to_erase_ic = true;
        //ic = it->second;
        return 1024;
    }

    return 0;
}




