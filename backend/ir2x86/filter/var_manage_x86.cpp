#include "var_manage_x86.h"
#include "number2str.h"

#include "mylog.h"

using mylog::cerr;



/**
 * @brief var_manage_x86::var_manage_x86

https://www.cnblogs.com/freshair_cnblog/p/11671416.html
https://stackoverflow.com/questions/664744/what-is-the-direction-of-stack-growth-in-most-modern-systems

x86: down.
SPARC: selectable. The standard ABI uses down.
PPC: down, I think.
System z: in a linked list, I kid you not (but still down, at least for zLinux).
ARM: selectable, but Thumb2 has compact encodings only for down (LDMIA = increment after, STMDB = decrement before).
6502: down (but only 256 bytes).
RCA 1802A: any way you want, subject to SCRT implementation.
PDP11: down.
8051: up.
注意，常见的CPU的栈都是往下生长的；8051单片机不同，它的栈是往上长的。

*/






var_manage_x86::var_manage_x86()
{
}


int var_manage_x86::collect_level0_var(icode *ic)
{
    if(this->m_level>0)
    {
        ///只找全局变量。非全局清况直接返回
        return 0;
    }

    if((ic->m_type!=ICODE_TYPE_DEF_VAR)&&
            (ic->m_type!=ICODE_TYPE_DEF_VAR_TMP)&&
            (ic->m_type!=ICODE_TYPE_EXP_OP)
            )
    {
        return 0;
    }


    if((ic->m_type==ICODE_TYPE_EXP_OP)&&
            (ic->name!="init"))
    {
        cerr<<"level=0. type=op. name!=init." <<ic->m_type<<". actual name="<< ic->name<<"\n";
        assert(0);
        return 0;
    }


    if(ic->m_type==ICODE_TYPE_EXP_OP)
    {
        if((ic->result->m_type==ICODE_TYPE_SYMBOL_REF)&&
                (ic->result->result!=NULL)
                )
        {
                icode *var_to_init = ic->result->result;
            auto it =std::find(m_uninit_gvar.begin(), m_uninit_gvar.end(), var_to_init);
                if(it!=m_uninit_gvar.end())
                {
                    m_uninit_gvar.erase(it);
                    m_init_gvar_opr.push_back(ic);
                    m_init_gvar.push_back(var_to_init);
                }
        }
        else
        {
            //init error???
            cerr<<"icode_collect_global_var:ic->result->m_type:"<<ic->result->m_type<<". "<<ic->result->result<<"\n";
            cerr<<ic->to_str(1)<<"\n";
            assert(0);
        }
        return 0;
    }

    if(ic->is_extern)
    {
        //extern变量，不收集
        return 0;
    }

    //此处为变量
    m_uninit_gvar.push_back(ic);

    return 0;
}

int var_manage_x86::collect_ret_var(icode *ic)
{
    if(ic->m_type!=ICODE_TYPE_FUNC_RET_TYPE)
    {
        return 0;
    }
    m_ret_var.push_back(ic);
    return 0;
}

int var_manage_x86::collect_arg_var(icode *ic)
{
    if(ic->m_type!=ICODE_TYPE_FUNC_DEF_ARG)
    {
        return 0;
    }
    m_arg_var.push_back(ic);
    return 0;
}

int var_manage_x86::collect_static_local_var(icode *ic)
{
    if(this->m_level==0)return 0;


    if(ic->m_type==ICODE_TYPE_EXP_OP)
    {
        if(ic->name=="init")
        {
            if((ic->result->m_type==ICODE_TYPE_SYMBOL_REF)&&
                    (ic->result->result!=NULL)
                    )
            {
                icode *var_to_init = ic->result->result;
                auto it =std::find(m_static_local_var.begin(),
                                   m_static_local_var.end(), var_to_init);
                if(it!=m_static_local_var.end())
                {
                    int disti = it - m_static_local_var.begin();
                    m_static_local_var_opt[disti] = ic;
                }
            }
            else
            {
                //init error???
                cerr<<"icode_collect_global_var:ic->result->m_type:"<<ic->result->m_type<<". "<<ic->result->result<<"\n";
                cerr<<ic->to_str(1)<<"\n";
                assert(0);
            }
            return 0;
        }
        return 0;
    }

    if((ic->m_type!=ICODE_TYPE_DEF_VAR)&&
            (ic->m_type!=ICODE_TYPE_DEF_VAR_TMP)
            )
    {
        return 0;
    }
    if(!ic->is_static)return 0;

    m_static_local_var.push_back(ic);
    m_static_local_var_opt.push_back(NULL);
    return 0;
}

int var_manage_x86::collect_local_var(icode *ic)
{

    if(this->m_level==0)return 0;
    if((ic->m_type!=ICODE_TYPE_DEF_VAR)&&
            (ic->m_type!=ICODE_TYPE_DEF_VAR_TMP)
            )
    {
        return 0;
    }
    if(ic->is_static)return 0;

    m_local_var.push_back(ic);
    return 0;
}

int var_manage_x86::collect_const(icode *ic)
{
    if(ic->m_type==ICODE_TYPE_CONST_STRING)
    {
        m_const_string.push_back(ic);
        if(this->m_curr_func!=NULL)
        {
            ic->m_var_info.m_name = "str_"+this->m_curr_func->name+"_"+ NumberToStr((unsigned) ic);
        }
        else
        {
            ic->m_var_info.m_name = "str_global_"+ NumberToStr((unsigned) ic);
        }
    }
    else if(ic->m_type==ICODE_TYPE_CONST_LIST)
    {
        m_const_list.push_back(ic);

        if(this->m_curr_func!=NULL)
        {
            ic->m_var_info.m_name = "clist_"+this->m_curr_func->name+"_"+ NumberToStr((unsigned) ic);
        }
        else
        {
            ic->m_var_info.m_name = "clist_global_"+ NumberToStr((unsigned) ic);
        }
    }
    return 0;

}


int var_manage_x86::process_one_icode(icode *ic, std::vector<icode *> &parent, int index, void *user_data, icode *iparent)
{
    collect_level0_var(ic);
    collect_ret_var(ic);
    collect_arg_var(ic);
    collect_static_local_var(ic);
    collect_local_var(ic);
    collect_const(ic);
    return 0;
}

void var_manage_x86::execute(icodes *ics)
{
    ///先搜索一遍。获取所有变量分类：
    /// 全局变量放入 data bss
    /// 局部变量放入stack
    /// 函数入参和返回值，放入stack
    ///
    m_init_gvar.clear();
    m_init_gvar_opr.clear();
    m_uninit_gvar.clear();
    this->pcompi = ics;
    this->reset();
    this->process_topcode(ics->m_top_icodes);



    ///-------------------------------------
    ///
    ///

    ///全局初始化的变量
    for(int i=0;i<m_init_gvar.size();++i)
    {
        icode *var = m_init_gvar[i];
        var->m_var_info.m_type = X86_VAR_TYPE_DATA;
    }

    /// 全局未初始化的变量
    for(int i=0;i<m_uninit_gvar.size();++i)
    {
        icode *var = m_init_gvar[i];
        var->m_var_info.m_type = X86_VAR_TYPE_BSS;
    }

    ///函数返回值 和 参数 局部变量等
    for(int i=0;i<m_ret_var.size();++i)
    {
        m_ret_var[i]->m_var_info.m_type = X86_VAR_TYPE_STACK;
    }

    for(int i=0;i<m_arg_var.size();++i)
    {
        m_arg_var[i]->m_var_info.m_type = X86_VAR_TYPE_STACK;
    }
    for(int i=0;i<m_local_var.size();++i)
    {
        m_local_var[i]->m_var_info.m_type = X86_VAR_TYPE_STACK;
    }

    /// 静态变量
    ///
    for(int i=0;i<m_static_local_var.size();++i)
    {
        icode *var = m_static_local_var[i];
        var->m_var_info.m_type = X86_VAR_TYPE_DATA;
    }

    /// 常量字符串，常量数值
    ///

    for(int i=0;i<m_const_string.size();++i)
    {
        icode *var = m_const_string[i];
        var->m_var_info.m_type=X86_VAR_TYPE_DATA;
    }
    for(int i=0;i<m_const_list.size();++i)
    {
        icode *var = m_const_string[i];
        var->m_var_info.m_type=X86_VAR_TYPE_DATA;
    }


    return;
}



