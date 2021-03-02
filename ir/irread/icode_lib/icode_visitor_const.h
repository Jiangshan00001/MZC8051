#ifndef ICODE_VISITOR_CONST_H
#define ICODE_VISITOR_CONST_H


#include <vector>
#include <string>
#include <set>
#include "icodes.h"


///
/// \brief The icode_visitor_const class
/// 只访问所有的icode，但不修改
/// 用于代码的生成
///
class icode_visitor_const
{
public:
    icode_visitor_const();

    virtual ~icode_visitor_const();


    ///
    /// \brief process_topcode 此函数一般不需要被重载，除非特别情况
    /// \param top_icodes
    /// \param user_data
    /// \return
    /// 顶层调用函数。传入所有icode。此函数会对每个icode，调用一次process_one_icode
    virtual int process_topcode(class icode *top_icode, void *user_data=NULL);
    ///
    /// \brief process_one_icode 单个icode处理函数，在process_topcode 中被的多次调用。
    /// 此函数一般需要被重载
    /// \param ic
    /// \param parent
    /// \param index
    /// \param user_data
    /// \param iparent
    /// \return
    virtual int process_one_icode_start(class icode *ic, void *user_data, class icode *iparent);
    virtual int process_one_icode_end(class icode *ic, void *user_data, class icode *iparent);


    /// 因为枚举是一个循环，如果后期需要从头开始再次枚举，则调用此函数清空中间变量
    virtual void reset();
private:
    int enum_all_child(icode *ic, void *user_data, class icode *iparent);
    int enum_one_start(icode *ic, void *user_data, class icode *iparent);
    int enum_one_end(icode *ic, void *user_data, class icode *iparent);

    ///两个函数，在SCOPE进入后，和退出前，会调用此函数
    void level_enter();
    void level_leave();

public:

    icodes *pcompi;
    int m_level;
    ///当前所在的函数，在函数外部时，为NULL
    icode *m_curr_func;

    ///每个类型的变量，第一次是定义，后面都是引用，所以此处只需要将遍历过的number记下来，保证每个icode只遍历一次
    std::set<class icode*> m_icode_number_set;
    std::set<class icode*> m_icode_number_set_end;
};

#endif // ICODE_VISITOR_CONST_H
