#include "icode_from_str.h"
#include "replace.h"
#include "mylog.h"


using mylog::cout;
using mylog::cerr;


icode *icode::from_str(const std::string &istr)
{

    size_t first_pos = istr.find(':');

    if(first_pos==std::string::npos)
    {
        cerr<<"from_str: : not found\n";
        return NULL;
    }

    std::string key = istr.substr(0, first_pos);

    int type_int = get_type_int(key);
    if(type_int==0)
    {
        //unknown icode type
        return NULL;
    }

    icode * thiz = new icode(0);
    thiz->m_type = (ICODE_TYPE)type_int;

    std::string other_str = istr.substr(first_pos+1);

    switch(type_int)
    {

    case ICODE_TYPE_I_CONST:
    {
        //std::string iconst_hex_num = get_word(other_str, ',');


        //ret_str<<icode::get_type_str(this->m_type)<< ":0x"<<std::hex<<this->num<<"," <<this->get_var_type()<< ";";
    }
    break;
    case ICODE_TYPE_F_CONST:
        //ret_str<<icode::get_type_str(this->m_type)<<":"<<this->fnum<<","<<this->get_var_type() <<";";
    break;
    case ICODE_TYPE_CONST_STRING:
        //ret_str<<icode::get_type_str(this->m_type)<<":"<<string_to_printf(this->name)<<";";
    break;

    case ICODE_TYPE_DEF_VAR_IN_VAR:
    case ICODE_TYPE_DEF_VAR_IN_VAR_TMP:


        break;


    case ICODE_TYPE_DEF_VAR:
    case ICODE_TYPE_DEF_VAR_TMP:/*中间临时变量*/
    {

    }
    break;

    case ICODE_TYPE_SYMBOL_REF: ///只是符号引用
    {

    }
        break;
    case ICODE_TYPE_FUNC: //函数开始

        break;

    case ICODE_TYPE_FUNC_RET_TYPE: //函数返回值


        break;
    case ICODE_TYPE_FUNC_DEF_ARG:   //函数参数


        break;
    case ICODE_TYPE_EXP_OP:        //算符
    {

    }
        break;
    case ICODE_TYPE_LABELED_BLOCK:

        break;

    case ICODE_TYPE_CONST_LIST:

        break;
    case ICODE_TYPE_BLOCK:
    case ICODE_TYPE_SCOPE:


        break;
    case ICODE_TYPE_CALL:

        break;
    case ICODE_TYPE_LABELED_BLOCK_END_REF:
        //ret_str<<"LABEL_REF_BEND( this should never show. "<<this->result->m_icode_number<<")";
       break;
   case ICODE_TYPE_LABELED_BLOCK_START_REF:
    {
            //ret_str<<icode::get_type_str(this->m_type)<< ":"<<"BS"<<this->result->m_icode_number<<")";
    }
       break;
    case ICODE_TYPE_FUNC_RETURN:
    {
        //ret_str<<"return;\n";
    }
        break;

    case ICODE_TYPE_ASM:
    {
        //ret_str<<icode::get_type_str(this->m_type)<< ":\"" << string_to_printf(this->name)<<"\"\n";
    }
        break;

    case ICODE_TYPE_UNKNOWN:
    default:
        //ret_str<<"ERROR:unknown code\n";
        break;

    }






    return 0;
}

