#include "icodes.h"
#include "icode.h"
#include "icode_positive_opr.h"

icode_positive_opr::icode_positive_opr()
{
    m_negative_func = "_sys_negative";
}

void icode_positive_opr::execute(icodes *ics)
{
    pcompi = ics;
    process_topcode(ics->m_top_icodes);
    return;
}

int icode_positive_opr::process_one_icode(icode *ic, std::vector<icode *> &parent, int index, void *user_data, icode *iparent)
{
    if(ic->m_type!=ICODE_TYPE_EXP_OP)
    {
        return 0;
    }

    if(ic->name=="positive")
    {
        ic->name = "=";
        ic->left = ic->result;
        return 0;
    }


    if((ic->name=="negative")&&
            (!m_negative_func.empty())
            )
    {
        icode *real_right = ic->right;
        icode * real_result = ic->result;

        ic->m_type=ICODE_TYPE_CALL;
        ic->sub_icode.push_back(real_right);
        ic->result = pcompi->new_ref_icode( pcompi->get_function(m_negative_func));

        icode *new_mov = pcompi->new_copy_icode_gen(ic->result->result->sub_icode[0], real_result);
        this->m_icode_to_insert_after_inst.push_back(new_mov);
    }

    return 0;
}
