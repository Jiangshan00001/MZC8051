#include "icode.h"
#include "icodes.h"
#include "icode_dead_func.h"




icode_dead_func::icode_dead_func()
{
}

void icode_dead_func::a_call_b(std::string a, std::string b)
{
    std::map<std::string, std::vector<std::string> > &call_func = m_call_func;
    //某个函数，被调用的函数列表
    std::map<std::string, std::vector<std::string> > &be_called_func = m_be_called_func;


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


int icode_dead_func::process_topcode(class icode *top_ic, void *user_data, icode *iparent)
{

    std::vector<icode *> &top_icodes = top_ic->sub_icode;
    int *user_idata = (int*)user_data;

    if((user_data==NULL)||
            (*user_idata==0))
    {
        return icode_visitor::process_topcode(top_ic, user_data);
    }

    return second_cleanup(top_icodes);
}

int icode_dead_func::process_one_icode(icode *ic, std::vector<icode *> &parent, int index, void *user_data, icode *iparent)
{
    ///收集func信息
    /// 此函数依赖一个默认的icode枚举顺序：
    ///   先枚举自己，再枚举自己里面的sub_icode
    if(ic->m_type==ICODE_TYPE_FUNC)
    {
        m_curr_func = ic->name;

        ///此处将函数放入
        /// m_func_list
        /// m_key_func
        ///

        assert(m_func_list.find(m_curr_func)==m_func_list.end());
        m_func_list[m_curr_func] = ic;
        if(ic->is_interrupt)
        {
            m_key_func.push_back(ic->name);
        }
    }
    else if(ic->m_type==ICODE_TYPE_CALL)
    {
        assert(m_curr_func.size()>0);
        assert(ic->result->result!=NULL);
        a_call_b(m_curr_func, ic->result->result->name);
    }
    return 0;
}

void icode_dead_func::execute(icodes *ics)
{
    pcompi = ics;
    process_topcode(ics->m_top_icodes);//计算调用次数
    int clean_up_folder_tmp=1;
    process_topcode(ics->m_top_icodes, &clean_up_folder_tmp);//清理调用不到的函数


}


void icode_dead_func::add_func_in_use(std::string key_func)
{

    if(m_func_in_use[key_func]>0)
    {///保证每个函数，只遍历一遍，避免重复遍历
        return;
    }

    m_func_in_use[key_func]++;
    std::vector<std::string> key_list = m_call_func[key_func];
    for(unsigned j=0;j<key_list.size();++j)
    {
        std::string func_usedA =key_list[j];
        add_func_in_use(func_usedA);
    }
}


int icode_dead_func::second_cleanup(std::vector<icode *> &top_icodes)
{
    m_key_func.push_back("main");
    m_key_func.push_back("__init_global_var");


    /// 查找使用的函数
    /// ==================
    for(unsigned i=0;i<m_key_func.size();++i)
    {
        std::string key_func = m_key_func[i];

        add_func_in_use(key_func);

    }

    ///===================
    /// 查找未用的函数
    ///
    for(auto it=m_func_list.begin();it!=m_func_list.end();++it )
    {
        std::string func_name = it->first;
        icode * func_icode = it->second;

        if(m_func_in_use.find(func_name)==m_func_in_use.end())
        {
            m_func_not_in_use[func_name] = func_icode;
            m_func_not_in_use2[func_icode] = func_name;
        }
    }

    ///===================


    for(int i=0;i<top_icodes.size();++i)
    {
        icode * curr_ic = top_icodes[i];
        if(curr_ic->m_type==ICODE_TYPE_BLOCK)
        {
            for(int j=0;j<curr_ic->sub_icode.size();++j)
            {
                icode * curr_ic2= curr_ic->sub_icode[j];
                if(curr_ic2->m_type==ICODE_TYPE_FUNC)
                {
                    if(m_func_not_in_use2.find(curr_ic2)!=m_func_not_in_use2.end())
                    {
                        //此处要删除不用代码
                        curr_ic->sub_icode.erase(curr_ic->sub_icode.begin()+j);
                        j--;
                        //curr_ic2->m_type=ICODE_TYPE_BLOCK;
                        //curr_ic2->sub_icode.clear();
                    }
                }
            }
        }
        else if(curr_ic->m_type==ICODE_TYPE_FUNC)
        {
            if(m_func_not_in_use2.find(curr_ic)!=m_func_not_in_use2.end())
            {
                //此处要删除不用代码
                //因为删除代码，会导致程序循环的递归异常，所以不去除代码，而是转为func->block
                top_icodes.erase(top_icodes.begin()+i);
                i--;
                //curr_ic->m_type=ICODE_TYPE_BLOCK;
                //curr_ic->sub_icode.clear();
            }
        }
        else if(curr_ic->m_type==ICODE_TYPE_DEF_VAR)
        {
            continue;
        }
    }

    return 0;
}







