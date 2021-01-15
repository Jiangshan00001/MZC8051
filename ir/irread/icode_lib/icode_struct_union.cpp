#include <algorithm>
#include "icode_struct_union.h"
#include "icode.h"


int icode::get_member_offset_bit_width(std::string member_name)
{
    if((this->m_type==ICODE_TYPE_DEF_VAR_IN_VAR)||
            (this->m_type==ICODE_TYPE_DEF_VAR_IN_VAR_TMP))
    {
        return this->result->get_member_offset_bit_width(member_name);
    }
    if(this->is_ptr)
    {
        return this->m_in_ptr_type->get_member_offset_bit_width(member_name);
    }



    if(this->is_union)
    {
        //联合，所有offset都是0
        return 0;
    }



    unsigned ret = 0;
    for(unsigned i=0;i<m_struct_name.size();++i)
    {
        if(m_struct_name[i]==member_name)
        {
            break;
        }
        ret += m_struct_type[i]->m_bit_width;
    }
    return ret;
}

icode* icode::get_member_icode(std::string member_name)
{
    if((this->m_type==ICODE_TYPE_DEF_VAR_IN_VAR)||
            (this->m_type==ICODE_TYPE_DEF_VAR_IN_VAR_TMP))
    {
        return this->result->get_member_icode(member_name);
    }
    if(this->is_ptr)
    {
        return this->m_in_ptr_type->get_member_icode(member_name);
    }
    auto it = std::find(m_struct_name.begin(), m_struct_name.end(), member_name);
    if(it==m_struct_name.end())
    {
        return NULL;
    }
    int cnt = std::distance(m_struct_name.begin(), it);
    return m_struct_type[cnt];
}
