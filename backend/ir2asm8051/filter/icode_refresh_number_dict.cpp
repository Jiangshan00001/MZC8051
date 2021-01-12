#include "icode.h"
#include "icodes.h"
#include "icode_refresh_number_dict.h"

icode_refresh_number_dict::icode_refresh_number_dict()
{
}

int icode_refresh_number_dict::process_one_icode(icode *ic, std::vector<icode *> &parent, int index, void *user_data, class icode *iparent)
{
    this->pcompi->m_icode_number_dict[ic->m_icode_number] = ic;


    if(ic->m_type==ICODE_TYPE_FUNC)
    {
        sym*s = this->pcompi->m_sym_manage.find_symbol(ic->name);
        if(s!=NULL)
        {
            s->def_icode = ic;
        }
        else
        {
            this->pcompi->m_sym_manage.add_symbol(ic->name, ic);
        }

    }


    return 0;
}
