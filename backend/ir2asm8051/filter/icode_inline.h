#ifndef ICODE_INLINE_H
#define ICODE_INLINE_H


#include <map>
#include <string>
#include <vector>
#include "icode_visitor.h"

/// 处理inline函数。将inline函数放入直接代码位置。
class icode_inline: public icode_visitor
{
public:
    icode_inline();
    ~icode_inline();

    int process_one_icode(class icode *ic, std::vector<class icode *> &parent, int index, void *user_data, class icode *iparent);

    ///内嵌函数内容复制，其中变量地址需要替换
    class icode * inline_copy(icode *ic, std::map<icode *, icode *> &old_new_var_ptr, std::vector<icode *> &parent, int index, int is_alloc);
    class icode * inline_replace(class icode *ic, std::map<icode *, icode *> &old_new_var_ptr);

};


#endif // ICODE_INLINE_H
