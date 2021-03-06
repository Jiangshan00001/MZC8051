#include <iostream>
#include <assert.h>
#include "icodes.h"
#include <icode.h>
#include "icode_pass1.h"




void a_call_b(std::string a, std::string b, std::map<std::string, std::vector<std::string> > &call_func, std::map<std::string, std::vector<std::string> > &be_called_func)
{

    if(call_func.find(a)==call_func.end())
    {
        std::vector<std::string> empty1;
        call_func[a] = empty1;
    }
    call_func[a].push_back(b);

    if(be_called_func.find(b)==be_called_func.end())
    {
        std::vector<std::string> empty1;
        be_called_func[b] = empty1;
    }
    be_called_func[b].push_back(a);
}

void call_func_search(class icode * ic, std::map<std::string, std::vector<std::string> > &call_func,
                      std::map<std::string, std::vector<std::string> > &be_called_func, std::string curr_func)
{
    if((ic->m_type ==ICODE_TYPE_BLOCK)||
            (ic->m_type ==ICODE_TYPE_LABELED_BLOCK))
    {
        for(unsigned i=0;i<ic->sub_icode.size();++i)
        {
            call_func_search(ic->sub_icode[i], call_func, be_called_func, curr_func);
        }
        return;
    }

    if(ic->m_type==ICODE_TYPE_FUNC)
    {
        curr_func = ic->name;

        for(unsigned i=0;i<ic->sub_icode.size();++i)
        {
            call_func_search(ic->sub_icode[i], call_func, be_called_func, curr_func);
        }
    }
    if(ic->m_type==ICODE_TYPE_CALL)
    {
        assert(curr_func.size()>0);
        a_call_b(curr_func, ic->result->name, call_func, be_called_func);
    }
}


icode_pass1::icode_pass1()
{
}

void icode_pass1::process_topcode(std::vector<icode *> top_icodes)
{
    for(unsigned i=0;i<top_icodes.size();++i)
    {
        icode * curr = top_icodes[i];

        std::string curr_func ="";
        call_func_search(curr, m_call_func, m_be_called_func, curr_func);

    }

    for(unsigned i=0;i<top_icodes.size();++i)
    {
        icode * curr = top_icodes[i];
        fun_var_count(curr);
    }


    std::cout<<"func_count:"<<m_func_var.size()<<std::endl;
    for(auto it=m_func_var.begin();it!=m_func_var.end();++it)
    {
        std::string func_name = it->first;

        std::cout<<"\n";
        std::cout<<"func:" <<func_name<<std::endl;
        std::cout<<"call_list:"<<std::endl;
        for(unsigned j=0;j<m_call_func[func_name].size();++j)
        {
            std::cout<<"\t"<<m_call_func[func_name][j] <<std::endl;
        }
        std::cout<<"be_called_list:"<<std::endl;
        for(unsigned j=0;j<m_be_called_func[func_name].size();++j)
        {
            std::cout<<"\t"<<m_be_called_func[func_name][j] <<std::endl;
        }
        std::cout<<"func_ret_size:"<<m_func_ret[func_name]<<std::endl;
        std::cout<<"func_arg_size:"<<m_func_arg[func_name]<<std::endl;
        for(unsigned i=0;i<m_func_var[func_name].size();++i)
        {
            std::cout<<"func_lvar_size:"<<std::dec<<m_func_var[func_name][i].var_bit_width<<", "<< m_func_var[func_name][i].name<<std::endl;
        }
    }

    //每个函数的占用变量情况
}

void icode_pass1::fun_var_count(icode *ic)
{
    if(ic->m_type==ICODE_TYPE_FUNC)
    {
        m_curr_func_name = ic->name;
        if(m_func_arg.find(m_curr_func_name)==m_func_arg.end())
        {
            m_func_arg[m_curr_func_name] = 0;
        }
        if(m_func_var.find(m_curr_func_name)==m_func_var.end())
        {
            std::vector<var_used> var1;
            m_func_var[m_curr_func_name] = var1;
        }
        m_func_ret[m_curr_func_name] = 0;



        for(unsigned i=0;i<ic->sub_icode.size();++i)
        {
            fun_var_count(ic->sub_icode[i]);
        }
        return;
    }
    if((ic->m_type ==ICODE_TYPE_BLOCK)||
            (ic->m_type ==ICODE_TYPE_LABELED_BLOCK))
    {
        for(unsigned i=0;i<ic->sub_icode.size();++i)
        {
            fun_var_count(ic->sub_icode[i]);
        }
        return;
    }

    if(ic->m_type==ICODE_TYPE_FUNC_RET_TYPE)
    {
        assert(m_curr_func_name.size()>0);
        m_func_ret[m_curr_func_name] = ic->m_bit_width;
        return;
    }
    if(ic->m_type==ICODE_TYPE_FUNC_DEF_ARG)
    {
        assert(m_curr_func_name.size()>0);
        m_func_arg[m_curr_func_name] += ic->m_bit_width;
        return;
    }
    if((ic->m_type==ICODE_TYPE_DEF_VAR)||(ic->m_type==ICODE_TYPE_DEF_VAR_TMP))
    {
        if(m_curr_func_name.size()==0)
        {
            return;
        }

        //TODO: 先查询是否有释放的大小一致变量，如果有，则直接使用



        var_used v;
        v.var_bit_width = ic->m_bit_width;
        v.is_used = 1;
        v.def_icode = ic;
        v.name = ic->name;
        m_func_var[m_curr_func_name].push_back(v);
        return;
    }

}





