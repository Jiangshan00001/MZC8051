#include "icodes.h"
#include "icode_ref_number.h"
#include "icode_tmp_var_opt1.h"

icode_tmp_var_opt1::icode_tmp_var_opt1()
{
}

int icode_tmp_var_opt1::process_one_icode(icode *ic, std::vector<icode *> &parent, int index, void *user_data, icode *iparent)
{
    if(user_data==0)
    {
        process_find1(ic, parent, index, iparent);
    }
    else
    {
        process_find2(ic, parent, index, iparent);
    }

}

int icode_tmp_var_opt1::process_find1(icode *ic, std::vector<icode *> &parent, int index, icode *iparent)
{
    if(ic->m_type!=ICODE_TYPE_EXP_OP)
    {
        return 0;
    }

    if((ic->name!="=")&&
            (ic->name!="init"))
    {
        return 0;
    }

    icode *right_t=pcompi->get_def_var(ic->right);

    if((right_t->m_type!=ICODE_TYPE_DEF_VAR_IN_VAR_TMP)&&
            (right_t->m_type!=ICODE_TYPE_DEF_VAR_TMP))
    {
        ///只处理2中临时变量
        return 0;
    }

    if((right_t->m_ref_number!=2)||
            (right_t->m_ref_write_number!=1))
    {
        //且引用次数为2.1次读，1次写
        return 0;
    }

    ///确定，此处为读临时变量1次。需要找到写的地方，替换为此处的result。
    /// 然后将此处ic变为空block


    m_replaced_to_var = ic->result;
    m_be_replaced_var = right_t;
    this->process_topcode(pcompi->m_top_icodes,(void*)1);
    ic->m_type=ICODE_TYPE_BLOCK;
    ic->left=NULL;
    ic->right=NULL;
    ic->result=NULL;
    m_replaced_to_var = NULL;
    m_be_replaced_var=NULL;
    return 0;
}

int icode_tmp_var_opt1::process_find2(icode *ic, std::vector<icode *> &parent, int index, icode *iparent)
{
    if((ic->m_type!=ICODE_TYPE_DEF_VAR_IN_VAR_TMP)&&
            (ic->m_type!=ICODE_TYPE_DEF_VAR_TMP)&&
            (ic->m_type!=ICODE_TYPE_EXP_OP)
            )
    {
        return 0;
    }

    if((ic->m_type==ICODE_TYPE_DEF_VAR_IN_VAR_TMP)||
            (ic->m_type==ICODE_TYPE_DEF_VAR_TMP))
    {
        if(ic==m_be_replaced_var)
        {
            //this->m_to_rep_ic = pcompi->new_icode(ICODE_TYPE_BLOCK);
            ic->m_type=ICODE_TYPE_BLOCK;
            ic->sub_icode.clear();
            return 0;
        }
        return 0;
    }
    if(ic->m_type==ICODE_TYPE_EXP_OP)
    {
        if(ic->result==NULL)
        {
            return 0;
        }
        icode *result_t=pcompi->get_def_var(ic->result);
        if(result_t==m_be_replaced_var)
        {
            ic->result = pcompi->new_ref_icode(m_replaced_to_var);
            return 0;
        }
    }
    return 0;
}

void icode_tmp_var_opt1::execute(icodes *ics)
{

    icode_ref_number m_ref_number;
    m_ref_number.execute(ics);

    this->pcompi = ics;
    this->process_topcode(ics->m_top_icodes,0);
}
