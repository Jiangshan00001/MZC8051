#include "icode_to_str.h"
#include "replace.h"



static std::string string_to_printf(std::string strA)
{
    std::string retA=strA;
    replace(retA, "\n", "\\n");
    replace(retA, "\r", "\\r");
    replace(retA, "\t", "\\t");
    replace(retA, "\v", "\\v");
    replace(retA, "\f", "\\f");
    replace(retA, "\"", "\\\"");

    return retA;
}

std::string icode::to_str(int is_one_line, int is_dbg)
{
    unsigned i=0;
    std::stringstream ret_str;

    switch(m_type)
    {

    case ICODE_TYPE_I_CONST:
        ret_str<<icode::get_type_str(this->m_type)<< ":0x"<<std::hex<<this->num <<":0x"<<std::hex<<this->m_bit_width ; //<< ";"
    break;
    case ICODE_TYPE_F_CONST:
        ret_str<<icode::get_type_str(this->m_type)<<":"<<this->fnum <<":0x"<<std::hex<<this->m_bit_width ;//<<";"
    break;
    case ICODE_TYPE_CONST_STRING:
        ret_str<<icode::get_type_str(this->m_type)<<":\""<<string_to_printf(this->name)<<"\"";//<<";"
        if(!is_one_line)
        {ret_str<<"\n";}
    break;

    case ICODE_TYPE_DEF_VAR_IN_VAR:
    case ICODE_TYPE_DEF_VAR_IN_VAR_TMP:

        ret_str<<icode::get_type_str(this->m_type)<<":";
        ret_str<<"%"<<this->result->get_name();
        if(this->is_array)
        {
            for(int i=0;i<this->array_cnt.size();++i)
            {
                ret_str<<"["<<this->array_cnt[i]->to_str(1)<<"]";
            }
        }
        if(this->is_ptr)
        {
            ///如果是ptr，则is_ptr<=0. 此处添加负号，保证生成是是>=0的数字
            ret_str<<"*"<<- this->is_ptr<<"";
        }
        if(!is_one_line){ret_str<<"\n";}
        break;


    case ICODE_TYPE_DEF_VAR:
    case ICODE_TYPE_DEF_VAR_TMP:/*中间临时变量*/

    {
        ret_str<<icode::get_type_str(this->m_type)  <<": $"<<this->get_name()<<","<<this->get_var_type()<<";";
        if(!is_one_line)
        {
            ret_str<<"\n";
        }
    }
    break;

    case ICODE_TYPE_SYMBOL_REF: ///只是符号引用
    {
        std::string array_cnt_str = vector_icode_ptr_cont(this->array_cnt);
        if(this->result)
        {
            ret_str<<icode::get_type_str(this->m_type)<<string_to_printf(this->result->get_name());
            ret_str <<  "";
        }
        else
        {
            ret_str<<icode::get_type_str(this->m_type)<<"("<<string_to_printf(this->get_name())<<", UNRESOLVED"<<")";
        }
    }
        break;
    case ICODE_TYPE_FUNC: //函数开始

        ret_str<< icode::get_type_str(this->m_type) <<":$" <<this->get_name();

        /// @todo : is_regparams 参数转为ir？
        if(this->is_regparams)
        {
            ret_str<<","<<"REGPARAMS(\""<<this->m_reg_params_desc<< "\")";
        }

        if(this->is_interrupt)
        {
            ret_str<<",";
            ret_str<<"INTERRUPT("<<this->m_interrupt_num<<")";
        }
        if(this->is_extern)
        {
            ret_str<<",";
            ret_str<<"EXTERN("<<1<<")";
        }
        if(this->is_static)
        {
            ret_str<<",";
            ret_str<<"STATIC("<<1<<")";
        }


        ret_str<<";";



        if(!is_one_line)
        {ret_str<<"\n";}
        for(i=0;i<this->sub_icode.size();++i)
        {
            ret_str<<"\t"<< this->sub_icode[i]->to_str();;
        }
        ret_str<<"func_end:%" <<this->get_name()<<";";
        if(!is_one_line)
        {ret_str<<"\n";}
        break;

    case ICODE_TYPE_FUNC_RET_TYPE: //函数返回值

        ret_str<<icode::get_type_str(this->m_type)  <<": $"<<this->get_name()<<","<<this->get_var_type()<<";\n";

        break;
    case ICODE_TYPE_FUNC_DEF_ARG:   //函数参数
        ret_str<<icode::get_type_str(this->m_type)  <<": $"<<this->get_name()<<","<<this->get_var_type()<<";\n";


        break;
    case ICODE_TYPE_EXP_OP:        //算符
    {

        ret_str<< icode::get_type_str(this->m_type)<< ": \""<<this->get_name()<<"\", ";
        ret_str<<this->that_to_str(this->left)<<";";
        ret_str<<", "<<this->that_to_str(this->right) <<";";
        ret_str<<", "<<this->that_to_str(this->result)<<";";
        if(!is_one_line)
        {ret_str<<"\n";}
    }
        break;
    case ICODE_TYPE_LABELED_BLOCK:
        ret_str<<icode::get_type_str(this->m_type)<<":";

        ret_str<< this->name<<";";
        if(!is_one_line)
        {ret_str<<"\n";}

        assert(this->sub_icode.size()==0);

        break;

    case ICODE_TYPE_CONST_LIST:
    {
        ret_str<<icode::get_type_str(this->m_type)<<": [";
        for(i=0;i<this->sub_icode.size();++i)
        {
            ret_str<< this->sub_icode[i]->to_str(1)<<"; ";
        }
        ret_str<<"] ";

    }
        break;
    case ICODE_TYPE_BLOCK://2020.1.2 block不再显示
        //if(!is_one_line)
        //{ret_str<<"\n";}

        for(i=0;i<this->sub_icode.size();++i)
        {
            ret_str<< this->sub_icode[i]->to_str();
        }
        //if(!is_one_line)
        //{ret_str<<"\n";}

        break;
    case ICODE_TYPE_SCOPE:
        ret_str<<icode::get_type_str(this->m_type)<< ":";
        if(!is_one_line)
        {ret_str<<"\n";}

        for(i=0;i<this->sub_icode.size();++i)
        {
            ret_str<< this->sub_icode[i]->to_str();
        }
        if(m_type==ICODE_TYPE_SCOPE)
        {
            ret_str<<"};";
        }
        else
        {
            ret_str<<"+};";
        }
        if(!is_one_line)
        {ret_str<<"\n";}

        break;
    case ICODE_TYPE_CALL:
        ret_str<<icode::get_type_str(this->m_type)<< ":" <<this->result->to_str()<<";";
        if(!is_one_line)
        {ret_str<<"\n";}
        for(i=0;i<this->sub_icode.size();++i)
        {
            ret_str<< this->sub_icode[i]->to_str(1)<<";";
            if(!is_one_line)
            {ret_str<<"\n";}
        }
        ret_str<<"call_end:" <<this->result->to_str()<<";";
        if(!is_one_line)
        {ret_str<<"\n";}
        break;
    case ICODE_TYPE_LABELED_BLOCK_END_REF:
        ret_str<<"LABEL_REF_BEND( this should never show. "<<this->result->m_icode_number<<")";
       break;
   case ICODE_TYPE_LABELED_BLOCK_START_REF:
    {

        if(this->result!=NULL)
        {
            ret_str<<icode::get_type_str(this->m_type)<<"BS" <<":"<<this->result->name;
        }
        else
        {
            ret_str<<"LABEL_REF_BSTART(null)";
        }
    }
       break;
    case ICODE_TYPE_FUNC_RETURN:
    {
        ret_str<<icode::get_type_str(this->m_type) <<";\n";
    }
        break;

    case ICODE_TYPE_ASM:
    {
        /// @todo : asm此处转为ir时，如何转回？
        ret_str<<icode::get_type_str(this->m_type)<< ":\"" << string_to_printf(this->name)<<"\";\n";
    }
        break;

    case ICODE_TYPE_UNKNOWN:
    default:
        ret_str<<"ERROR:unknown code\n";
        break;
    }

    return ret_str.str();
}

std::string icode::that_to_str(icode *that)
{
    if(that==NULL)
    {
        return "null";
    }
    return that->to_str(1);
}
