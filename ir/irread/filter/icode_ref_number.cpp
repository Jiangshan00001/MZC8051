#include <vector>
#include "mylog.h"
#include "icode.h"

#include "icode_ref_number.h"


using mylog::cerr;

icode_ref_number::icode_ref_number()
{

}

int icode_ref_number::process_one_icode_clean(icode *ic, std::vector<icode *> &parent, int index, icode *iparent)
{
    if(ic->is_def_var())
    {
        ic->m_ref_number = 0;
        ic->m_ref_read_number = 0;
        ic->m_ref_write_number = 0;
        return 0;
    }
    return 0;
}

int icode_ref_number::process_one_icode_addref(icode *ic, std::vector<icode *> &parent, int index, icode *iparent)
{
    if(ic->m_type!=ICODE_TYPE_SYMBOL_REF)
    {
        return 0;
    }
    if(ic->result==NULL)
    {
        return 0;
    }
    if(!ic->result->is_def_var())
    {
        return 0;
    }

    ic->result->m_ref_number++;

    if(parent[index]->m_type==ICODE_TYPE_EXP_OP)
    {
        if((parent[index]->result!=NULL)&&
                (parent[index]->result==ic))
        {

            ic->result->m_ref_write_number++;
        }
        else
        {
            ic->result->m_ref_read_number++;
        }
    }
    else if(parent[index]->m_type==ICODE_TYPE_CALL)
    {
        ic->result->m_ref_read_number++;
    }
    else if(parent[index]->m_type==ICODE_TYPE_FUNC)
    {
        ic->result->m_ref_read_number++;
    }
    else if((parent[index]->m_type==ICODE_TYPE_DEF_VAR_IN_VAR_TMP)||
            (parent[index]->m_type==ICODE_TYPE_DEF_VAR_IN_VAR))
    {
        /// 此处是只读???
        ic->result->m_ref_read_number++;
    }
    else
    {
        cerr<<"icode_ref_number: unknown type:" << parent[index]->to_str()<<"\n";
        assert(0);
    }

    return 0;
}

int icode_ref_number::process_one_icode(icode *ic, std::vector<icode *> &parent, int index, void *user_data, icode *iparent)
{
    if(user_data==0)
    {
        return process_one_icode_addref(ic, parent, index, iparent);
    }
    else
    {
        return process_one_icode_clean(ic, parent, index, iparent);
    }
    return 0;
}


void icode_ref_number::execute(icodes *ics)
{
    this->pcompi = ics;
    ///清除ref_number
    this->process_topcode(ics->m_top_icodes, (void*)1);
    ///重新标记ref_number
    this->process_topcode(ics->m_top_icodes, 0);

}
