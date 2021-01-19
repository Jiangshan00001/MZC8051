#include "icode_ptr_in_calc.h"

icode_ptr_in_calc::icode_ptr_in_calc()
{
}

int icode_ptr_in_calc::process_one_icode(icode *ic, std::vector<icode *> &parent, int index, void *user_data, icode *iparent)
{
    if((ic->m_type!=ICODE_TYPE_DEF_VAR_IN_VAR)&&
            (ic->m_type!=ICODE_TYPE_DEF_VAR_IN_VAR_TMP))
    {
        return 0;
    }
    if(ic->is_ptr>=-1)
    {
        return 0;
    }

    int to_ptr=ic->is_ptr;
    /// TODO: 重叠指针符号的拆分
    /// char ***a;
    /// ***a=1;
    ///
    /// void main()
    /// {
    /// int ***a;
    /// ***a=3;
    /// }
    ///
    /// def_var: $a,u24*3*[i16];
    /// opr: "=", null;, iconst:0x3;, var_in:%a*3;
    ///
    ///
    /// def_var_tmp: $tmp1;,$a,u24*2*[i16];
    /// def_var_tmp: $tmp2;,$a,u24*1*[i16];
    /// opr: "=", null;, var_in:%a*1;, %tmp1;
    /// opr: "=", null;, var_in:%tmp1*1;, %tmp2;
    /// opr: "=", null;, iconst:0x3;, var_in:%tmp2*1;
    ///
    ///
    /// int *a;
    /// *a=3;
    ///
    /// def_var: $a,u24*1*[i16];
    /// opr: "=", null;, iconst:0x3;, var_in:%a*1;
    ///
    /// int **a;
    /// **a=3;
    ///
    /// def_var: $a,u24*2*[i16];
    /// def_var_tmp: $tmp1, u24*1*[i16];
    /// opr: "=", null;, var_in:%a*1;, %tmp1;
    /// opr: "=", null;, iconst:0x3;, var_in:%tmp1*1;
    ///
    ///
    ///
    ///
    /// ic var_in
    /// ic->result 是一个指针(的ref?)。指针内容在m_in_ptr_type中。
    ///

    icode * tmp_var_curr = pcompi->get_def_var(ic->result);
    int is_first=1;
    while(to_ptr<0)
    {
        to_ptr++;
        {
        ///创建1个临时变量
        icode * tmp_var = pcompi->new_temp_var(pcompi->get_def_var(ic->result)->m_in_ptr_type);
        assert(tmp_var->is_ptr);
        tmp_var->is_ptr = to_ptr;

        /// opr: "=", null;, var_in:%a*1;, %tmp1;
        icode *var_in1 = pcompi->new_var_in_var_tmp_icode(tmp_var_curr);
        icode *opr = pcompi->new_icode();
        opr->m_type= ICODE_TYPE_EXP_OP;
        opr->name = "=";
        opr->right = var_in1;
        opr->result = tmp_var;
        m_icode_to_insert_before_inst.push_back(tmp_var);
        m_icode_to_insert_before_inst.push_back(opr);
        tmp_var_curr = tmp_var;
        }
    }
    m_to_rep_ic = tmp_var_curr;
    return 0;
}

void icode_ptr_in_calc::execute(icodes *ics)
{
    this->pcompi = ics;
    this->process_topcode(ics->m_top_icodes);

}
