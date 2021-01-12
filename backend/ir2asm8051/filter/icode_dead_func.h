#ifndef ICODE_DEAD_FUNC_H
#define ICODE_DEAD_FUNC_H

#include <vector>
#include <map>

#include "icode_visitor.h"

///
/// \brief The icode_dead_func class
/// 检查和删除未被调用的函数
class icode_dead_func : public icode_visitor
{
public:
    icode_dead_func();


    virtual int process_topcode(class icode *top_ic, void *user_data=NULL, class icode *iparent=NULL);
    virtual int process_one_icode(class icode *ic, std::vector<class icode *> &parent, int index, void *user_data, class icode *iparent);


    int second_cleanup(std::vector<icode *> &top_icodes);

    // 某个函数，调用的函数列表
    std::map<std::string, std::vector<std::string> > m_call_func;
    //某个函数，被调用的函数列表
    std::map<std::string, std::vector<std::string> > m_be_called_func;

    std::map<std::string, class icode* > m_func_list;

    std::map<std::string, int > m_func_in_use;
    std::map<std::string, class icode*> m_func_not_in_use;
    std::map<class icode*, std::string> m_func_not_in_use2;

    // main函数和其他中断函数
    std::vector<std::string> m_key_func;

    std::string m_curr_func;


    void a_call_b(std::string a, std::string b);
    void call_func_search(icode *ic, std::map<std::string, std::vector<std::string> > &call_func, std::map<std::string, std::vector<std::string> > &be_called_func, std::string m_curr_func);

    void add_func_in_use(std::string func_name);

};

#endif // ICODE_DEAD_FUNC_H
