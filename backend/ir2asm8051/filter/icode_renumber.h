#ifndef ICODE_RENUMBER_H
#define ICODE_RENUMBER_H

#include <map>
#include "icode_visitor.h"

///所有icode重新编号
///

///
/// \brief The icode_renumber class icode_number重新编号
/// 将micode中的 m_icode_number 改为重新申请，避免冲突。
class icode_renumber : public icode_visitor
{
public:
    icode_renumber();

    virtual int process_one_icode(class icode *ic, std::vector<class icode *> &parent, int index, void *user_data, class icode *iparent);

    std::map<int, class icode*> m_icode_map;

};

#endif // ICODE_RENUMBER_H

