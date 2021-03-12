#include <sstream>
#include <assert.h>
#include "comp_context.h"
#include "token_defs.h"
#include "parser.h"
#include "driver.h"
#include "icode.h"
#include "comp_context_gen_defs.h"
#include "mylog.h"
#include "comp_context_yy_debug.h"

using mylog::cerr;
using mylog::cout;
using mylog::cwarn;
using mylog::cdbg;

namespace NS_AMS8051HEX{

comp_context::comp_context()
{
    m_just_ret_tree = 0;
}

comp_context::~comp_context()
{
}

void comp_context::parse_start_token(token_defs &start_tk)
{
    if(m_just_ret_tree)
    {
        m_yy_tree = m_yy_tree + token_to_tree(&start_tk);
    }
    else
    {
        cdbg<<"get token:"<< start_tk.m_type<<"\n";
        m_top_icode = this->ast_to_icode(&start_tk, 0, 0);
        cdbg<<"parse finish!\n";
    }
}
icode* comp_context::new_icode()
{
return new icode();
}
icode* comp_context::new_icode(int itype)
{
icode*ic =new icode();
ic->m_type= itype;
return ic;

}


std::string comp_context::token_to_tree(token_defs *tdefs)
{
    std::map<int, std::string> m_ast_type;
    std::map<int, std::string> m_elem_type;

    for(int i=0;i<g_ast_debug_str.size();++i)
    {
        m_ast_type[g_ast_debug_str[i].m_type] = g_ast_debug_str[i].m_name;
    }
    for(int i=0;i<g_elem_debug_str.size();++i)
    {
        m_elem_type[g_elem_debug_str[i].m_type] = g_elem_debug_str[i].m_name;
    }





    std::stringstream ss;
    if(tdefs==NULL){ return "";}
    if((tdefs->m_type==TOKEN_DEFS_TYPE_AST)||(tdefs->m_tk_type_int_list.size()>0))
    {
        //return ast_to_icode_ast(tdefs, need_result_icode, result_ic);
        int top_type=tdefs->m_tk_type_int;
        if(tdefs->m_tk_type_int_list.size()>0)
        {
            top_type=tdefs->m_tk_type_int_list[tdefs->m_tk_type_int_list.size()-1];
            tdefs->m_tk_type_int_list.pop_back();
        }
        /// 此处显示字符串
        ///
        /// top_type
        ss<<m_ast_type[top_type]<<"\n";


        if((tdefs->m_type==TOKEN_DEFS_TYPE_AST)&&
                (tdefs->m_tk_type_int_list.size()==0)&&
                (tdefs->m_tk_elems.size()==0)
                )
        {//ast 已经处理完成
            return ss.str();
        }

        /// 处理子类字符串
        ///
        if(tdefs->m_tk_type_int_list.size()>0)//(tdefs->m_tk_elems.size()==0)
        {
            ss<< token_to_tree(tdefs);
        }
        else  if(tdefs->m_type==TOKEN_DEFS_TYPE_ELEM)
        {
            ss<< token_to_tree(tdefs);
        }
        else
        {
            ss<<"-\n";
            for(int i=0;i<tdefs->m_tk_elems.size();++i)
            {
                ss<< token_to_tree(tdefs->m_tk_elems[i]);
            }
        }
    }
    else if(tdefs->m_type==TOKEN_DEFS_TYPE_ELEM)
    {
        //return ast_to_icode_elem(tdefs, need_result_icode, result_ic);
        //tdefs->m_token_type
        ss<<m_elem_type[tdefs->m_token_type]<<"("<< tdefs->val_str<<")" <<"\n";
        ss<<"=\n";
    }
    else
    {
        assert(0);
    }



    return ss.str();
}



}


