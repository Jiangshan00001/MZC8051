#include "icode.h"
#include "icode_sym_rebuild.h"

icode_sym_rebuild::icode_sym_rebuild()
{
}

int icode_sym_rebuild::process_one_icode(icode *ic, std::vector<icode *> &parent, int index, void *user_data, class icode *iparent)
{
    if(m_level>0)
    {
        //局部符号不处理
        return 0;
    }


    /// 此处不能添加临时变量，因为临时变量名字可能会重复
    ///
    if(!((ic->m_type==ICODE_TYPE_DEF_VAR)||
            (ic->m_type==ICODE_TYPE_FUNC)))
    {
        return 0;
    }
    m_sym_manage.add_symbol(ic->name,ic, 0);

    return 1;
}
