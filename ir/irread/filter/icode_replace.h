#ifndef ICODE_REPLACE_H
#define ICODE_REPLACE_H

#include "icode_visitor.h"


/**
 * @brief 替换icode的使用，去除icode的定义
 *
 *
 *
 */
class icode_replace : public icode_visitor
{
public:
    icode_replace();

    virtual int process_one_icode(class icode * ic, std::vector<class icode *> &parent, int index, void *user_data, class icode *iparent);

    // replace 1 with 2
    // 找到前面的，替换为后面的
    std::map<class icode *, class icode *> sym_rep;
};

#endif // ICODE_REPLACE_H
