#ifndef VAR_MANAGE_BASE_H
#define VAR_MANAGE_BASE_H

#include "icode_visitor.h"


///变量的存储 管理分配策略
///
///
///
class var_manage_base : public icode_visitor
{
public:
    var_manage_base();
    virtual ~var_manage_base();

    virtual void execute(icodes *ics);
public:


};

#endif // VAR_MANAGE_BASE_H
