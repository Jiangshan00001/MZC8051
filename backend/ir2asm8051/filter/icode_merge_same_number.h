#ifndef ICODE_MERGE_SAME_NUMBER_H
#define ICODE_MERGE_SAME_NUMBER_H

#include "icode_visitor.h"
#include <map>


///
/// \brief The icode_merge_same_number class 相同icode_number的改为1个icode
/// 将 micodes中信息m_icode_number中相同的icode,修改为1个。
class icode_merge_same_number : public icode_visitor
{
public:
    icode_merge_same_number();

    virtual int process_one_icode(class icode * ic, std::vector<class icode *> &parent, int index, void *user_data, class icode *iparent);


    std::map<int, class icode*> m_icode_map;

};

#endif // ICODE_MERGE_SAME_NUMBER_H
