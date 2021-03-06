#ifndef ICODE_PASS1_H
#define ICODE_PASS1_H

#include <vector>
#include <map>
#include <string>



class var_used
{
public:
    std::string name;
    int var_bit_width;
    bool is_used;
    class icode * def_icode;
};

///
/// \brief The icode_pass1 class
///icode 输入，输出icode的函数调用关系，函数变量使用，全局变量使用情况 等。
///
class icode_pass1
{
public:
    icode_pass1();

    void process_topcode(std::vector<class icode *>top_icodes);

    // 某个函数，调用的函数列表
    std::map<std::string, std::vector<std::string> > m_call_func;
    //某个函数，被调用的函数列表
    std::map<std::string, std::vector<std::string> > m_be_called_func;

    ///函数变量占用空间情况，分为3种类型变量：返回值 参数 和 局部变量
    std::map<std::string, int > m_func_ret;
    std::map<std::string, int > m_func_arg;
    std::map<std::string, std::vector<var_used> > m_func_var;
    std::string m_curr_func_name;


    void fun_var_count(class icode *ic);


};

#endif // ICODE_PASS1_H
