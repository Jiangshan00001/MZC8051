#include "icode_array.h"
#include "icode.h"


int icode::refresh_array_total_bit_width()
{
    this->m_bit_width = this->get_array_bit_width();
    return 0;
}

bool icode::is_var_in()
{
    return ((m_type==ICODE_TYPE_DEF_VAR_IN_VAR)||(m_type==ICODE_TYPE_DEF_VAR_IN_VAR_TMP));
}

int icode::get_array_bit_width()
{
    if(!is_array)
    {
        return 0;
    }

    assert((is_array>0) &&(is_array==array_cnt.size()));
    unsigned arr_cnt = array_cnt[0]->num;;
    for(unsigned arrtmp=1;arrtmp<array_cnt.size();++arrtmp)
    {
        arr_cnt *= array_cnt[arrtmp]->num;
    }

    return this->m_in_ptr_type->m_bit_width * arr_cnt;
}
int icode::set_array_bit_width(int total_bit_width)
{
    if(!is_array)
    {
        return 0;
    }
    /// int a[]={1,2,3,4};
    /// int a[][5]={{1,2,3,4},{5,6,7,8}};

    assert(is_array==1);
    // 此处只处理1维数组。如果有多维，则需要先获取每层的大小，只能设置最外层的大小

    int total_comp_cnt = total_bit_width/m_bit_width;
    this->array_cnt[0]->num = total_comp_cnt;
    this->array_cnt[0]->fnum = total_comp_cnt;

    return 0;
}
