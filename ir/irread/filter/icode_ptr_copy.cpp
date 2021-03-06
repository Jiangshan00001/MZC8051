#include "icode.h"
#include "icodes.h"
#include "icode_ptr_copy.h"

icode_ptr_copy::icode_ptr_copy()
{
    m_copy_func = "__byte_copy";
}

int icode_ptr_copy::process_one_icode(icode *ic, std::vector<icode *> &parent, int index, void *user_data, class icode *iparent)
{
    ///如果=赋值运算，两边bit_width>16,则转为函数调用

    if(ic->m_type!=ICODE_TYPE_EXP_OP)
    {
        return 0;
    }
    if(ic->name!="=")
    {
        return 0;
    }
    if((ic->right==NULL)||(ic->result==NULL))
    {
        return 0;
    }
    if((!ic->right->is_array)&&(!ic->right->is_ptr))
    {
        return 0;
    }
    if((!ic->result->is_array)&&(!ic->result->is_ptr))
    {
        return 0;
    }

    if((ic->right->is_array+ ic->right->is_ptr +ic->right->result->is_ptr+ ic->right->result->is_array>0)||
            (ic->result->is_array+ic->result->is_ptr + ic->result->result->is_ptr+ ic->result->result->is_array>0))
    {
        return 0;
    }

    if((ic->right->m_bit_width<=32)||(ic->result->m_bit_width<=32))
    {
        return 0;
    }

    int m_bit = ic->right->m_bit_width;
    if(m_bit>ic->result->m_bit_width)
    {
        m_bit = ic->result->m_bit_width;
    }


    ///此处必须是指针内容复制
    ///


    ic->m_type=ICODE_TYPE_CALL;
    ic->sub_icode.clear();
    ic->sub_icode.push_back(ic->right);
    ic->sub_icode.push_back(ic->result);
    ic->sub_icode.push_back(pcompi->new_icode());
    ic->sub_icode[2]->m_type=ICODE_TYPE_I_CONST;
    ic->sub_icode[2]->num = m_bit/8;
    ic->sub_icode[2]->const_refresh_width();



    ic->right->is_array = 0;
    ic->right->is_ptr = 0;
    ic->result->is_array = 0;
    ic->result->is_ptr = 0;

    ic->result = pcompi->new_ref_icode( pcompi->get_function(m_copy_func));
    assert(ic->result->result!=NULL);

    return 1;

}





