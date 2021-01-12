#ifndef ICODE_FUNC_H
#define ICODE_FUNC_H

#include "icode_var.h"
#include <string>
#include <vector>


/// ICODE_TYPE_FUNC:
/// sub_ic-> [0]--ret 返回值   ICODE_TYPE_FUNC_RET_TYPE
/// sub_ic-> [1] ICODE_TYPE_FUNC_DEF_ARG
/// sub_ic-> [2] ICODE_TYPE_FUNC_DEF_ARG...
/// sub_ic->... 函数功能,expr等
///
///
/// ICODE_TYPE_CALL:
/// sub_icode[0]--ret 返回值 实参
/// sub_icode[1]--参数1 实参
/// sub_icode[2]--参数2 实参
/// 。。。
/// result --- 被调函数的icode
///
///
///
///
/// \brief The icode_func class
///


#endif // ICODE_FUNC_H
