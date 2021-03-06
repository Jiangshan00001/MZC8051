#ifndef ICODE_VISITOR_H
#define ICODE_VISITOR_H

#include <vector>
#include <string>
#include <set>
#include "icodes.h"


///
/// \brief The icode_visitor class
/// 对icode进行遍历，方便处理
///
class icode_visitor
{
public:
    icode_visitor();
    virtual ~icode_visitor();




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
    virtual int process_one_icode(class icode *ic, std::vector<class icode *> &parent, int index, void *user_data, class icode *iparent);

    ///两个函数，在SCOPE进入后，和退出前，会调用此函数
    virtual void level_enter();
    virtual void level_leave();

    /// 因为枚举是一个循环，如果后期需要从头开始再次枚举，则调用此函数清空中间变量
    virtual void reset();
private:
    int enum_all_child(icode *ic, std::vector<class icode *> &parent, int index, void *user_data, class icode *iparent);
    int enum_one(class icode *ic, std::vector<class icode *> &parent, int index, void *user_data, class icode *iparent);

public:

    icodes *pcompi;

    ///此处添加ic指针，说明想用这个来替换掉当前的ic
    /// 因为不能在process_one_icode中直接替换，所以通过此此参数传递到上层函数中
    class icode * m_to_rep_ic; ///< 设置此变量，说明要把ic替换为此变量
    bool m_to_erase_ic;        ///< 设置此变量为true，说明要把此ic删除
    std::vector<class icode*> m_icode_to_insert_before_inst; ///< 需要在ic后面插入的代码icode
    std::vector<class icode*> m_icode_to_insert_after_inst;  ///< 需要在ic前面插入的代码icode

    void check_rep(class icode * & ic);
    void check_insert_inst(std::vector<class icode *> &inst_parent, int &index );

    int m_level;



    ///因为可能会在调用过程中，再次调用，所以需要添加堆栈类型变量
    /// 需求为 icode_tmp_var_opt1.cpp
    ///  对于只读写了各一次的临时变量，找到写ir后，再查找读ir，将读ir和写ir两个做修改才能实现优化掉此变量
    std::vector<std::set<class icode*> > m_icode_number_set_list;
    ///每个类型的变量，第一次是定义，后面都是引用，所以此处只需要将遍历过的number记下来，保证每个icode只遍历一次
    std::set<class icode*> *m_icode_number_set;

    ///当前所在的函数，在函数外部时，为NULL
    icode *m_curr_func;

};

#endif // ICODE_VISITOR_H
