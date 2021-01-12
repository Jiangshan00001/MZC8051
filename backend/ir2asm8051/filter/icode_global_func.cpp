#include "icode_global_func.h"

icode_global_func::icode_global_func()
{
    g_INIT_FUNC_NAME = "__init_global_var";
}

int icode_global_func::execute(icodes *ics)
{
    pcompi=ics;
    add_function(ics);
    process_topcode(ics->m_top_icodes);
    resort_function(ics->m_top_icodes);
    return 0;
}

int icode_global_func::add_function(icodes *ics)
{
    ///  ///查找func : void __init_global_var(void){
    ///
    ///
    ///
    /// }
    /// 如果没找到，则添加函数
    ///

    icode *init_func=NULL;
    std::vector<icode*> &top_icodes = ics->m_top_icodes->sub_icode;

    for(unsigned i=0;i<top_icodes.size();++i)
    {
        icode * curr = top_icodes[i];
        if(curr->m_type!=ICODE_TYPE_FUNC)
        {
            continue;
        }
        if(curr->name!=g_INIT_FUNC_NAME)
        {
            continue;
        }
        init_func = curr;
        break;
    }

    if(init_func==NULL)
    {
        ///没有这个函数，需要添加
        init_func= pcompi->new_icode();
        init_func->m_type=ICODE_TYPE_FUNC;
        init_func->name = g_INIT_FUNC_NAME;

        init_func->sub_icode.push_back(pcompi->new_icode());
        init_func->sub_icode[0]->m_type=ICODE_TYPE_FUNC_RET_TYPE;
        init_func->sub_icode[0]->m_bit_width = 0;
        init_func->sub_icode[0]->is_signed=0;
        init_func->sub_icode[0]->name = "void";
        //此处确保initfunction 在最前面第一个函数
        top_icodes.insert(top_icodes.begin(), init_func);

        ics->m_sym_manage.add_symbol(g_INIT_FUNC_NAME, init_func);
    }
    m_init_func = init_func;
    return 0;
}

int icode_global_func::resort_function(icode *ic)
{
    ///block前置
    ///
    /// __init_func
    ///
    ///function后置

    std::vector<icode *> blocks;
    std::vector<icode*> funcs;
    std::vector<icode*> &top_icodes = ic->sub_icode;
    icode * init_func;

    for(unsigned i=0;i<top_icodes.size();++i)
    {
        if(top_icodes[i]->m_type==ICODE_TYPE_FUNC)
        {
            if(top_icodes[i]->name==g_INIT_FUNC_NAME)
            {
                init_func = top_icodes[i];
            }
            else
            {
                funcs.push_back(top_icodes[i]);
            }
        }
        else if(top_icodes[i]->m_type==ICODE_TYPE_BLOCK)
        {
            blocks.push_back(top_icodes[i]);
        }
        else
        {
            blocks.push_back(top_icodes[i]);
            //assert(0);
        }
    }

    assert(init_func!=NULL);
    top_icodes.clear();
    top_icodes.insert(top_icodes.begin(), blocks.begin(), blocks.end());
    top_icodes.insert(top_icodes.end(), init_func);
    top_icodes.insert(top_icodes.end(), funcs.begin(), funcs.end());

}

int icode_global_func::process_one_icode(icode *ic, std::vector<icode *> &parent, int index, void *user_data, icode *iparent)
{

    if(this->m_level!=0)
    {
        //全局变量的初始化，只有level=0时需要添加处理
        return 0;
    }
    if(ic->m_type==ICODE_TYPE_EXP_OP)
    {
        m_init_func->merge_icode(ic);
        m_to_erase_ic = true;
    }



    return 0;
}
