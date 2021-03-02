#include <assert.h>
#include "mylog.h"

#include "icode_collect_global_var.h"

using  mylog::cerr;

icode_collect_global_var::icode_collect_global_var()
{
}

void icode_collect_global_var::execute(icodes *ics)
{
    m_init_gvar.clear();
    m_init_gvar_opr.clear();
    m_uninit_gvar.clear();
    this->pcompi = ics;
    this->reset();
    this->process_topcode(ics->m_top_icodes);
}

int icode_collect_global_var::process_one_icode(icode *ic, std::vector<icode *> &parent, int index, void *user_data, icode *iparent)
{
    if(this->m_level>0)
    {
        ///只找全局变量。非全局清况直接返回
        return 0;
    }

    if((ic->m_type!=ICODE_TYPE_DEF_VAR)&&
            (ic->m_type!=ICODE_TYPE_DEF_VAR_TMP)&&
            (ic->m_type!=ICODE_TYPE_EXP_OP)
            )
    {
        return 0;
    }


    if((ic->m_type==ICODE_TYPE_EXP_OP)&&
            (ic->name!="init"))
    {
        cerr<<"level=0. type=op. name!=init." <<ic->m_type<<". actual name="<< ic->name<<"\n";
        assert(0);
        return 0;
    }


    if(ic->m_type==ICODE_TYPE_EXP_OP)
    {
        if((ic->result->m_type==ICODE_TYPE_SYMBOL_REF)&&
                (ic->result->result!=NULL)
                )
        {
                icode *var_to_init = ic->result->result;
            auto it =std::find(m_uninit_gvar.begin(), m_uninit_gvar.end(), var_to_init);
                if(it!=m_uninit_gvar.end())
                {
                    m_uninit_gvar.erase(it);
                    m_init_gvar_opr.push_back(ic);
                    m_init_gvar.push_back(var_to_init);
                }
        }
        else
        {
            //init error???
            cerr<<"icode_collect_global_var:ic->result->m_type:"<<ic->result->m_type<<". "<<ic->result->result<<"\n";
            cerr<<ic->to_str(1)<<"\n";
            assert(0);
        }
        return 0;
    }

    if(ic->is_extern)
    {
        //extern变量，不收集
        return 0;
    }

    //此处为变量
    m_uninit_gvar.push_back(ic);

    return 0;
}
