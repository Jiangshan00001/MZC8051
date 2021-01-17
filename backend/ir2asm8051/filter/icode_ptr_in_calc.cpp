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
    return 0;


}

void icode_ptr_in_calc::execute(icodes *ics)
{
    this->pcompi = ics;
    this->process_topcode(ics->m_top_icodes);

}
