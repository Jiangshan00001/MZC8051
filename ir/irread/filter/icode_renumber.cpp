#include "icode.h"
#include "icodes.h"
#include "icode_renumber.h"

icode_renumber::icode_renumber()
{
}

int icode_renumber::process_one_icode(icode *ic, std::vector<icode *> &parent, int index, void *user_data, class icode *iparent)
{

    /// 之前写的如果号码已经存在，则不再编号，会导致相同的icode_Number，不同的icode
    //if(m_icode_map.find(ic->m_icode_number)==m_icode_map.end())
    {
        int num = pcompi->new_icode_number();
        ic->m_icode_number = num;
        m_icode_map[num] = ic;
    }


    return 0;
}
