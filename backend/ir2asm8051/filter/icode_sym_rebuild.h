#ifndef ICODE_SYM_REBUILD_H
#define ICODE_SYM_REBUILD_H

#include "icode_visitor.h"
#include "sym_manage.h"

///
/// \brief The icode_sym_rebuild class 重建符号表。
/// 之后全局符号保存下来，局部变量和局部符号不会重建
/// 操作：只读，不会修改icode
class icode_sym_rebuild : public icode_visitor
{
public:
    icode_sym_rebuild();
    sym_manage m_sym_manage;
    virtual int process_one_icode(class icode *ic, std::vector<class icode *> &parent, int index, void *user_data, class icode *iparent);

};

#endif // ICODE_SYM_REBUILD_H

