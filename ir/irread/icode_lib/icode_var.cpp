#include "icode.h"
#include "icode_var.h"


bool icode::is_def_var()
{
    if((m_type==ICODE_TYPE_DEF_VAR)||
            (m_type==ICODE_TYPE_DEF_VAR_TMP)||
            (m_type==ICODE_TYPE_FUNC_DEF_ARG)||
            (m_type==ICODE_TYPE_FUNC_RET_TYPE)||
            (m_type==ICODE_TYPE_DEF_VAR_IN_VAR)||
            (m_type==ICODE_TYPE_DEF_VAR_IN_VAR_TMP)
            )
    {
        return true;
    }
    return false;
}


void icode::set_width_from(icode *from)
{
    ///根据from的值，设置当前width值


    if(from->m_type==ICODE_TYPE_SYMBOL_REF)
    {
        if(from->result)
        {
            if(this->m_bit_width < from->result->m_bit_width)
            {
                this->m_bit_width = from->result->m_bit_width;
            }
        }
        else
        {
            if(this->m_bit_width < from->m_bit_width)
            {
                this->m_bit_width = from->m_bit_width;
            }
        }

        return;
    }
    if(from->m_type==ICODE_TYPE_I_CONST)
    {
        if(this->m_bit_width < from->m_bit_width)
        {
            this->m_bit_width = from->m_bit_width;
        }
        return;
    }
    if(from->m_type==ICODE_TYPE_F_CONST)
    {
        if(this->m_bit_width < from->m_bit_width)
        {
            this->m_bit_width = from->m_bit_width;
        }
        return;
    }
    assert(0);
}

bool icode::is_float()
{
    if(this->m_type==ICODE_TYPE_F_CONST)
    {
        return true;
    }



    if(this->m_type==ICODE_TYPE_SYMBOL_REF)
    {
        if(this->result==NULL)
        {
            return false;
        }
        if(this->result->is_float32)
        {
            return true;
        }
        return false;
    }

    if(this->is_float32)
    {
        return true;
    }
    return false;

}

bool icode::is_symbol()
{
    icode * ic = this;
    if((ic->m_type==ICODE_TYPE_DEF_VAR)||
            (ic->m_type==ICODE_TYPE_DEF_VAR_IN_VAR)||
            (ic->m_type==ICODE_TYPE_DEF_VAR_IN_VAR_TMP)||
            (ic->m_type==ICODE_TYPE_DEF_VAR_TMP)||
            (ic->m_type==ICODE_TYPE_FUNC)||
            (ic->m_type==ICODE_TYPE_FUNC_DEF_ARG)
            )
    {
        return true;
    }
    return false;
}

int icode::to_dot_var(std::string &def_str, std::string &ref_str)
{
    std::stringstream stA;

    ref_str = this->get_dot_name();

    stA.clear();
    stA.str("");

    stA<<ref_str<<"[label=\" DEF_VAR "<<this->name;
    stA<<". bw:"<< this->m_bit_width;
    if(is_float32)
    {
        stA<<". is_float32. ";
    }

    stA<<"\"" ;

    stA<<" ]\n";
    def_str = stA.str();

    return 0;
}

