#ifndef ICODE_MANAGE_H
#define ICODE_MANAGE_H

#include <list>
#include <map>
#include <string>

#include "icode.h"
#include "sym_manage.h"
#include "icodes.h"


class icode_manage
{
public:
    icode_manage();

    virtual ~icode_manage();


public:


    icode* new_icode();
    icode* new_opr_icode(std::string name, icode *left, icode *right, icode *result);
    icode* new_icode(ICODE_TYPE mtype);
    icode* new_icode(const icode &cp);
    icode* new_iconst_icode(int const_num);


    int m_top_icodes_need_free;
    icodes* m_top_icodes;

public:
    //将icode的json字符串标识，载入内存，并且合并到m_top_icodes中
    void merge_mzo(const std::string &mzo_str);


    // 将内部icode转为字符串
    std::string to_str();
    std::string to_str(icode * ic);



public:

    ///=========================================
    /// 此处为全局符号表:包括 m_functions
    ///
    /// 所有符号添加标号，标号代表了符号本身
    std::map<std::string, class icode*> m_functions;


public:
    /// 用户自定义类型表
    /// 内部的icode是dev_var 定义变量的类型
    std::vector<class icode*> m_typedef;

public:

    ///2021.1.9
    /// m_sym_manage 从icode_manage改到icodes中


    void add_symbol(std::string &name, class icode *pdef=NULL)
    {
        m_top_icodes->m_sym_manage.add_symbol(name, pdef);
    }
    sym* find_symbol(const std::string &name)
    {
        return m_top_icodes->m_sym_manage.find_symbol(name);

    }

    unsigned get_symbol_list_size()
    {
       return m_top_icodes->m_sym_manage.get_symbol_list_size();
    }

    void level_enter()
    {
        m_top_icodes->m_sym_manage.level_enter();
    }

    void level_leave()
    {
        m_top_icodes->m_sym_manage.level_leave();
    }

    int set_symbol_list_size(unsigned nsize)
    {
        return m_top_icodes->m_sym_manage.set_symbol_list_size(nsize);
    }
    int get_level()
    {
        return m_top_icodes->m_sym_manage.m_level;
    }

    ///当前代码层级。每个层级中，只能有一个变量定义，否则报重复定义变量的错误
    /// 如果一个层级种的变量和全局变量重名，则报警告
    //int m_level;

public:
    icode *new_var(std::string name, icode *typedec, int &is_already_exist);
    icode *new_var(icode *def_ic, icode *typedec, int &is_already_exist);
    icode *new_temp_var();
    void new_var_struct_add_full_name(icode *a);


    icode *get_def_var(icode *ic);



    std::string get_temp_name(std::string prefix="tmp_var_");
    int m_tmp_var_name_index;
public:
    ///需要对应的数据类型长度等函数信息，是和后端相关的
    class target_base *m_target;


public:
    ///当前变量类型，用于处理变量声明时使用
    /// int a, b;先处理 int，并把类型写入curr_var_type. 然后处理a, b. 生成2个变量
    icode *m_curr_var_type;


public:

    /// 所有枚举类型
    /// 所有枚举类型的各常量都在这个列表里
    std::map<std::string, int > m_enum_items;
    /// 每个枚举类型，里面包含的常量字符串。具体常量值需要查询上表
    std::map<std::string, std::vector<std::string> > m_enum_def;
    /// 每个枚举类型的位宽
    std::map<std::string, int> m_enum_bitwidth;

    //当前enum的名称，只有在解析enum时使用
    std::string m_curr_enum_name;
    //当前enum的index，只有在解析enum时使用
    int m_curr_enum_index;


public:


    ///用于goto的标签
    std::map<std::string, class icode *> m_goto_label;
    //此处 放置没有位置的标签。eg:
    /// goto LabelA; --》此处标签没有位置，则生成一个放入unset中
    /// LabelA:
    /// 对应： IAN_LABELED_STATEMENT_1
    std::vector<std::string> m_goto_label_unset;
public:
    //在for和while 循环中，需要提前设置这2个标签。循环外需要清空此标签
    icode *m_continue_label_dst;
    icode *m_break_label_dst;
    std::vector<int> m_case_int_vec;
    std::map<int, class icode*> m_case_label;
    //switch 语句中default对应的标签
    class icode * m_default_label;
public:
    std::map<std::string, std::vector<class icode*> > m_struct_union_type;
    std::map<std::string, std::vector<std::string> > m_struct_union_name;
    std::map<std::string, int> m_struct_or_union;///0--union. 1--struct
    std::map<std::string, int> m_struct_union_bitwidth;

    std::string m_curr_struct_union_name;

};



#endif // ICODE_MANAGE_H
