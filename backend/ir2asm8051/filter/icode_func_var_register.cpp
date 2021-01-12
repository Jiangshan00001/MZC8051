#include <assert.h>
#include "split.h"
#include "trim.h"
#include "icodes.h"
#include "icode.h"
#include "icode_func_var_register.h"

icode_func_var_register::icode_func_var_register()
{
}

int icode_func_var_register::process_one_icode(icode *ic, std::vector<icode *> &parent, int index, void *user_data, class icode *iparent)
{
    ///不是func直接返回
    if(ic->m_type!=ICODE_TYPE_FUNC)
    {
        return 0;
    }

    ///没有regparams属性，直接返回
    if(!ic->is_regparams)
    {
        return 0;
    }

    std::string reg_desc_all = ic->m_reg_params_desc;
    if(reg_desc_all.size()==0)
    {
        ///没有具体分配空间说明，去除此属性，直接返回
        ///
        ic->is_regparams = 0;
        ic->is_naked = 1;
        return 0;
    }

    std::vector<std::string> reg_desc_list = split(reg_desc_all, ";");

    if(reg_desc_list.size()==0)
    {
        ///没有具体分配空间说明，去除此属性，直接返回
        ///
        ic->is_regparams = 0;
        ic->is_naked = 1;
        return 0;
    }


    assert((ic->sub_icode.size()+1)>=(reg_desc_list.size()));
    for(unsigned i=0;i<reg_desc_list.size();++i)
    {
        if(reg_desc_list[i].empty())
        {
            ///本身没有描述，则直接不操作
            continue;
        }

        //每个参数，都对应ic->sub_icode[i]
        icode *curr_var_ref = ic->sub_icode[i];
        icode *curr_var = pcompi->get_def_var(curr_var_ref);



        ///一定是变量
        assert(curr_var->is_def_var());

        curr_var->is_register = 1;
        curr_var->m_register_desc = trim(reg_desc_list[i]);
    }

    ic->is_regparams = 0;
    ic->is_naked = 1;
    ic->m_reg_params_desc="";
    return 0;
}



