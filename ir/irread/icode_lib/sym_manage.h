#ifndef SYM_MANAGE_H
#define SYM_MANAGE_H

#include <vector>
#include <deque>

#include "sym.h"

class sym_manage
{
public:
    sym_manage();



    ///当前代码层级。每个层级中，只能有一个变量定义，否则报重复定义变量的错误
    /// 如果一个层级种的变量和全局变量重名，则报警告
    int m_level;

    ///暂时未用：
    ///栈位置。每次新函数，会将此变量清0.
    /// 变量作用是记录函数中局部变量的大小和位置
    //int m_stack_pos;
    //int m_stack_pos_max;


    void add_symbol(std::string &name, class icode *pdef=NULL, int level=-1);
    sym* find_symbol(const std::string &name);
    //int find_symbol(class icode* to_find);

    unsigned get_symbol_list_size();
    int set_symbol_list_size(unsigned nsize);


    int level_enter();

    int level_leave();
private:

    std::vector<int>  m_last_sym_size;
    ///符号表
    std::deque<sym> m_symbols;



};

#endif // SYM_MANAGE_H
