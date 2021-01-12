#include "icode.h"
#include <assert.h>
#include <algorithm>
#include <map>
#include <iostream>
#include <sstream>
#include "icode.h"
#include "ast_base.h"
#include "mylog.h"


using mylog::cout;

std::map<int, std::string> g_icode_type_2_str;
std::map<std::string, int> g_icode_str_2_type;

int icode::g_icode_base_dot_index = 0;

void load_icode_debug_info()
{

    typedef struct {
        int type;
        std::string str;
    } icode_types;

    icode_types a[] = {
      {ICODE_TYPE_I_CONST, "iconst"},
        {ICODE_TYPE_F_CONST, "fconst"},
        {ICODE_TYPE_CONST_STRING, "cstring"},
        {ICODE_TYPE_DEF_VAR, "def_var"},
        {ICODE_TYPE_DEF_VAR_IN_VAR, "var_in"},
        {ICODE_TYPE_DEF_VAR_IN_VAR_TMP, "var_in_tmp"},
        {ICODE_TYPE_DEF_VAR_TMP, "def_var_tmp"},
        {ICODE_TYPE_SYMBOL_REF, "%"},
        {ICODE_TYPE_FUNC, "func"},
        {ICODE_TYPE_FUNC_RET_TYPE, "ret_type"},
        {ICODE_TYPE_FUNC_DEF_ARG, "def_arg"},
        {ICODE_TYPE_EXP_OP, "opr"},
        {ICODE_TYPE_BLOCK, "+{"},
        {ICODE_TYPE_UNKNOWN, "unknown"},
        {ICODE_TYPE_CALL, "call"},
        {ICODE_TYPE_LABELED_BLOCK, "#BS"},
        {ICODE_TYPE_LABELED_BLOCK_START_REF, "@"},
        {ICODE_TYPE_LABELED_BLOCK_END_REF, "lbend"},
        {ICODE_TYPE_FUNC_RETURN, "return"},
        {ICODE_TYPE_CONST_LIST, "clist"},
        {ICODE_TYPE_ASM, "asm"},
        {ICODE_TYPE_SCOPE, "{"},
    };

    for(unsigned i=0;i<sizeof(a)/sizeof(a[0]);i++)
    {
        g_icode_type_2_str[a[i].type] = a[i].str;
        g_icode_str_2_type[a[i].str] = a[i].type;
    }
}

std::string icode::get_type_str(int type_int)
{
    return g_icode_type_2_str[type_int];
}
int icode::get_type_int(std::string type_str)
{
    return g_icode_str_2_type[type_str];
}





std::string icode::to_dotb()
{
    std::string def_str, ref_str;
    to_dot(def_str, ref_str);
    return def_str;
}

int icode::get_dot_index()
{
    return g_icode_base_dot_index++;
}

std::string icode::get_dot_name1()
{
    std::stringstream stA;

    stA<<"IC_"<< this->m_icode_number;
    return stA.str();
}
std::string icode::get_dot_name()
{
    if((m_type==ICODE_TYPE_FUNC)||
            (m_type==ICODE_TYPE_BLOCK))
    {
        return "cluster_"+ icode::get_dot_name1();
    }

    return icode::get_dot_name1();
}

std::string icode::get_dot_start_name_ref_block()
{
    if((this->m_type==ICODE_TYPE_BLOCK)&&
            (this->sub_icode.size()>0))
    {
        return this->sub_icode[0]->get_dot_start_name_ref_block();
    }
    return get_dot_name();
}

std::string icode::get_dot_end_name_ref_block()
{
    if((this->m_type==ICODE_TYPE_BLOCK)&&
            (this->sub_icode.size()>0))
    {
        return this->sub_icode[this->sub_icode.size()-1]->get_dot_end_name_ref_block();
    }
    return get_dot_name();
}

std::string icode::get_name()
{
    if(this->m_full_name.size()>0)
    {
        return this->m_full_name;
    }
    return this->name;
}

void icode::set_left(icode *mleft)
{

    this->left = mleft;
    if(mleft!=NULL)
    {
        mleft->m_parent = this;
    }
}

void icode::set_right(icode *mright)
{

    this->right = mright;
    if(mright!=NULL)
    {
        mright->m_parent = this;
    }
}

void icode::set_result(icode *mresult)
{
    this->result = mresult;
    if(mresult!=NULL)
    {
        mresult->m_parent = this;
    }
}
















