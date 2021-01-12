#ifndef ICODES_H
#define ICODES_H

#include <map>
#include <list>
#include "icode.h"
#include "sym_manage.h"

class target_base;
class icodes
{
public:
    icodes();
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
    void clear_all_icode();


    icode * get_def_var(icode* ic);

public:
    icode *new_ref_icode(icode *to_ref);
    icode *new_temp_var();
    icode *new_copy_icode_gen(icode *from, icode *to);
    icode *new_var_in_var_icode(icode *to_ref);
    icode *new_temp_ptr_var(icode *in_ptr_type, target_base* mtarget);
    icode *new_temp_ptr_ptr_var(target_base *mtarget);
    icode* get_function(std::string func_name);



    ///=========================================
    ///
    ///  符号表管理
    sym_manage m_sym_manage;


#if 0
    icode* operator->() const
    {
        return m_top_icodes;
    }
#endif

};

#endif // ICODES_H
