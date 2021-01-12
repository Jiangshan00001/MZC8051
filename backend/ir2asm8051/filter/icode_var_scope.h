#ifndef ICODE_VAR_SCOPE_H
#define ICODE_VAR_SCOPE_H

#include "icode_visitor.h"





/**
 * @brief The icode_var_scope class
 *
 *
 * 更新变量的范围
 * 每个变量，添加一个scope。
 * 此功能分为3步：
 * 1 清除所有icode的parent；清除所有变量的scope vec
 * 2 添加所有icode的parent;添加所有变量的scope vec
 * 3 根据调用关系，生成函数调用图，
 *
 *
 * 函数调用图示例：
 *
 *  - main
 *  -- m1--m2
 *  -- m3--m4-m5
 * main函数调用了m1 m3，所以在main中的变量，和全局变量有一样的声明周期。
 * m1内部调用了 m2，所以，要先编译m1，再编译m2，然后释放m2中局部变量，然后释放m1中局部变量
 *
 * 根据调用关系，进行内存变量的声明空间释放
 *
 *
 *

 *
 *
 * \bug 变量范围，在结构体时，访问c.a，并不知道c被使用了
 * \bug 变量范围，在指针时，范围不能确定了? int a; int *b=&a; 后期使用*b
 * @code
 * struct A
{
        int a;
        char b;
};

void main()
{
        struct A c;
        c.a = 1;

        c.b = 2;
        struct A *d;
        d=&c;
        int e=12;
}
 * @endcode
 *
 *
 */
class icode_var_scope : public icode_visitor
{
public:
    icode_var_scope();

    virtual int process_one_icode(class icode *ic, std::vector<class icode *> &parent, int index, void *user_data, class icode *iparent);
public:
    void clear_parent(class icode *ic);
    int icode_scope_fill(class icode *ic);
    int fix_var_scope(class icode *ic);


public:

    void add_parent(class icode *parent, class icode** child);

    std::vector<int> find_var_blocks(class icode *ic);
    std::vector<int> find_var_blocks(int icode_number);

public:

};

#endif // ICODE_VAR_SCOPE_H




