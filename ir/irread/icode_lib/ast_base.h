#ifndef AST_BASE_H
#define AST_BASE_H
#include <iostream>

class ast_base
{
public:
    ast_base();
};


///用于输出打印时，<<算符重载中的函数
template<class A>
std::ostream& PTR_JSON_OUT(A *ptr, std::string ptr_name, std::ostream &out_stream)
{
    if(ptr==nullptr)
    {
    out_stream<<ptr_name<<":null,";
    }
    else
    {
        out_stream<<ptr_name<<":"<<*ptr<<",";
    }

    return out_stream;
}
#endif // AST_BASE_H
