#include <assert.h>
#include "c51_addr.h"

c51_addr::c51_addr()
{
    m_type = DATA_TYPE_UNKNOWN;
    m_addr = 0;
    m_bit_width = 0;

    is_signed=0;
    is_float32 = 0;

    is_array=0;
    is_ptr = 0;

    m_bit_width_array_comp = 0;
    ptr_target = NULL;
}

int c51_addr::refresh_width_from_addr()
{
    if(this->m_type==DATA_TYPE_J_DATA)
    {
        ///根据当前num值，确定参数的 width
        if(m_addr<255)
        {
            this->m_bit_width = 8;
        }
        else if(m_addr<0x10000)
        {
            this->m_bit_width = 16;
        }
        else if(m_addr<0x100000000ll)
        {
            this->m_bit_width = 32;
        }
        else
        {
            this->m_bit_width = 64;
        }
    }
    else
    {
        assert(0);
    }
    return 0;
}

bool c51_addr::is_equal(c51_addr *another)
{
    if(this->m_type!=another->m_type)
    {
        return false;
    }
    if(this->m_addr!=another->m_addr)
    {
        return false;
    }
    if(this->m_bit_width!=another->m_bit_width)
    {
        return false;
    }
    if(this->m_type==DATA_TYPE_IN_GENRIC_PTR)
    {
        if((this->ptr_target==NULL)||(another->ptr_target==NULL))
        {
            return false;
        }
        if((this->ptr_target->m_addr!=another->ptr_target->m_addr))
        {
            return false;
        }
    }


    return true;
}
