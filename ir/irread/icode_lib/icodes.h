#ifndef ICODES_H
#define ICODES_H

#include <map>
#include <list>
#include "icode.h"
#include "sym_manage.h"
#include "target_base.h"
//class target_base;
class icodes
{
public:
    icodes(int target_typ);
    virtual ~icodes();

    std::list<icode*> m_icodes;
    std::map<int, icode *> m_icode_number_dict;
    int m_icode_index;

    icode * m_top_icodes;

    int new_icode_number();
    icode* new_icode();
    icode* new_icode(ICODE_TYPE mtype);
    icode* new_icode(const icode &cp);
    icode* new_iconst_icode(int const_num);
    icode* new_opr_icode(std::string name, icode * left, icode* right, icode* result);
    void clear_all_icode();


    icode * get_def_var(icode* ic);

public:
    icode *new_ref_icode(icode *to_ref);
    icode *new_temp_var();
    /// 生成一个新的临时变量，类型和to_copy一样
    icode *new_temp_var(icode* to_copy);
    icode *new_copy_icode_gen(icode *from, icode *to);
    icode *new_var_in_var_icode(icode *to_ref);
    icode *new_var_in_var_tmp_icode(icode *to_ref);
    icode *new_temp_ptr_var(icode *in_ptr_type);
    icode *new_temp_ptr_ptr_var();
    icode* get_function(std::string func_name);



    ///=========================================
    ///
    ///  符号表管理
    sym_manage m_sym_manage;


    target_base *m_target;
};

#endif // ICODES_H
