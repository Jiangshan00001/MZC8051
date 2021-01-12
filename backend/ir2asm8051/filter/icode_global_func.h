#ifndef ICODE_GLOBAL_FUNC_H
#define ICODE_GLOBAL_FUNC_H
#include "icode_visitor.h"


///
/// \brief The icode_global_func class
/// 添加一个全局函数。里面是各变量的初始值的添加
/// 将全局变量中，不是函数定义的，不是变量定义的，其他语句，都移动到 全局变量初始化函数 中
///
/// 使用：
/// icode_global_func m_global_func;
/// m_global_func.execute(ics);
///
class icode_global_func : public icode_visitor
{
public:
    icode_global_func();
public:
    int execute(icodes *ics);
    int add_function(icodes *ics);
    int resort_function(icode *ic);
    virtual int process_one_icode(class icode *ic, std::vector<class icode *> &parent, int index, void *user_data, class icode *iparent);


    std::string g_INIT_FUNC_NAME;
    icode *m_init_func;

};

#endif // ICODE_GLOBAL_FUNC_H
