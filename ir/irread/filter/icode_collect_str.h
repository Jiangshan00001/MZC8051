#ifndef ICODE_COLLECT_STR_H
#define ICODE_COLLECT_STR_H

#include <string>
#include <vector>
#include "icode_visitor.h"

///将代码中，所有常量字符串收集得到一起，用于后期生成代码、
/// 字符串和const数组，都采用统一的c51_addr中的数组的方式处理
/// 相等的字符串，合并为1个
class icode_collect_str: public icode_visitor
{
public:
    icode_collect_str();
    ~icode_collect_str();

    int process_one_icode(class icode *ic, std::vector<class icode *> &parent, int index, void *user_data, class icode *iparent);


    //此处是生成的icodes
    std::vector<class icode*> m_icodes;

};

#endif // ICODE_COLLECT_STR_H
