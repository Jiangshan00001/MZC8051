#include "icode.h"
#include <assert.h>
#include <sstream>
#include "icode_base.h"
#include "icode_iconst.h"


bool icode::is_const_var()
{
    /// 此处const只处理iconst 和fconst，不处理常量数组
    //(this->m_type==ICODE_TYPE_CONST_LIST)||
    //(this->m_type==ICODE_TYPE_CONST_STRING)
    //||
    //                (this->result->m_type==ICODE_TYPE_CONST_LIST)||
    //                (this->result->m_type==ICODE_TYPE_CONST_STRING)

    if ((this->m_type==ICODE_TYPE_I_CONST)||
            (this->m_type==ICODE_TYPE_F_CONST))
    {
        return true;
    }
    if((this->m_type!=ICODE_TYPE_SYMBOL_REF)||
            (this->result==NULL))
    {

        return false;
    }

    ///正常情况下const不会被引用。
    /// 但是在常量折叠中，原来是变量，使用的引用，后来变为常量后，会有常量引用的情况
    if ((this->result->m_type==ICODE_TYPE_I_CONST)||
            (this->result->m_type==ICODE_TYPE_F_CONST))
    {
        return true;
    }
}

bool icode::is_const_list()
{
    if ((this->m_type==ICODE_TYPE_CONST_LIST)||
            (this->m_type==ICODE_TYPE_CONST_STRING))
    {
        return true;
    }
    if((this->m_type!=ICODE_TYPE_SYMBOL_REF)||
            (this->result==NULL))
    {

        return false;
    }

    ///正常情况下const不会被引用。
    /// 但是在常量折叠中，原来是变量，使用的引用，后来变为常量后，会有常量引用的情况
    if ((this->result->m_type==ICODE_TYPE_CONST_LIST)||
            (this->result->m_type==ICODE_TYPE_CONST_STRING))
    {
        return true;
    }
}

void icode::const_copy_from(icode *ic)
{
    this->m_type = ic->m_type;
    this->num = ic->num;
    this->fnum = ic->fnum;
    this->m_bit_width = ic->m_bit_width;
    //this->right = NULL;
    //this->left = NULL;
    //this->result = NULL;
}


void icode::const_refresh_width()
{
    if(this->m_type==ICODE_TYPE_I_CONST)
    {
        if(this->num<0)
        {
            if(this->num>=-128)
            {
                //0x80
                this->m_bit_width=8;
            }
            else if(this->num>=-32768)
            {
                this->m_bit_width=16;
            }
            else
            {
                this->m_bit_width=32;
            }
        }
        else
        {
            ///根据当前num值，确定参数的 width
            if(num<255)
            {
                this->m_bit_width = 8;
            }
            else if(num<0x10000)
            {
                this->m_bit_width = 16;
            }
            else if(num<0x100000000ll)
            {
                this->m_bit_width = 32;
            }
            else
            {
                this->m_bit_width = 64;
            }
        }



    }
    else if(this->m_type==ICODE_TYPE_CONST_STRING)
    {
        this->m_bit_width = this->name.size()*8;
    }
    else if(this->m_type==ICODE_TYPE_F_CONST)
    {
        this->m_bit_width = 4*8;//FLOAT 4byte... FIXME 此处需要读取目标类型？
    }
    else if(this->m_type==ICODE_TYPE_CONST_LIST)
    {
        //里面所有const的bitwidth加和
        /// FIXME: 此处限定const_list为flat之后的。而不是带scope的。
        this->m_bit_width = 0;
        for(int i=0;i<this->sub_icode.size();++i)
        {
            this->m_bit_width += this->sub_icode[i]->m_bit_width;
        }

    }
    else
    {
        assert(0);
    }
}

int icode::to_dot_const(std::string &def_str, std::string &ref_str)
{
    std::stringstream ret_str;

    ref_str = this->get_dot_name();

    ret_str.clear();
    ret_str.str("");


    ret_str<< ref_str;
    if(this->m_type==ICODE_TYPE_I_CONST)
    {
        ret_str<< "[label=\"I-("<< this->num<< ")\"]\n";
    }
    else if(this->m_type==ICODE_TYPE_F_CONST)
    {
        ret_str<< "[label=\"F-("<< this->fnum<< ". bw="<< this->m_bit_width<< ")\"]\n";
    }
    else
    {
        assert(0);
    }
    def_str = ret_str.str();

    return 0;
}


