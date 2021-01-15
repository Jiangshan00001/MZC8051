#include <sstream>
#include "icodes.h"
#include "target_base.h"

icodes::icodes()
{
    m_icode_index = 0;
    m_top_icodes = new_icode(ICODE_TYPE_BLOCK);
}

icodes::~icodes()
{
    clear_all_icode();
    //delete m_top_icodes;
}

int icodes::new_icode_number()
{
    return m_icode_index++;
}
icode* icodes::new_icode()
{
    //cout<<"new_icode:icode_index:"<<m_icode_index<<"\n";

    int num = new_icode_number();
    icode * nn =  new icode(num);
    //nn->m_new_inst = this;

    m_icodes.push_back(nn);
    m_icode_number_dict[nn->m_icode_number] = nn;

    return nn;
}

icode* icodes::new_icode(ICODE_TYPE mtype)
{
    icode * n = new_icode();
    n->m_type= mtype;
    return n;
}

icode* icodes::new_icode(const icode &cp)
{

    icode* ic = new_icode();
    int n = ic->m_icode_number;
    *ic = cp;
    ic->m_icode_number = n;
    //cout<<"new_icode:icode_index"<<m_icode_index<<"\n";
    return ic;
}

icode *icodes::new_iconst_icode(int const_num)
{
    icode *nn = new_icode(ICODE_TYPE_I_CONST);
    nn->num = const_num;
    nn->const_refresh_width();
    return nn;
}


void icodes::clear_all_icode()
{
    for(auto i=m_icodes.begin();i!=m_icodes.end();++i)
    {
        delete (*i);
    }
    m_icodes.clear();
    m_icode_number_dict.clear();
    m_icode_index = 0;

}

icode *icodes::get_def_var(icode *ic)
{
    if(ic==NULL)return NULL;
    if((ic->m_type==ICODE_TYPE_SYMBOL_REF)&&ic->result)
    {
        ic=ic->result;
    }
    else if((ic->m_type==ICODE_TYPE_BLOCK)&&(ic->result!=NULL))
    {
        if(ic->result->m_type==ICODE_TYPE_SYMBOL_REF)
        {
            ic=ic->result->result;
        }
    }

    return ic;
}

icode *icodes::new_ref_icode(icode *to_ref)
{
    if(to_ref!=NULL)
    {
        if((to_ref->m_type==ICODE_TYPE_I_CONST)||
                (to_ref->m_type==ICODE_TYPE_F_CONST))
        {
            return to_ref;//i f 常量，暂时没有引用的用法。引用就是他自己
        }
        if((to_ref->m_type==ICODE_TYPE_DEF_VAR_IN_VAR)||
                (to_ref->m_type==ICODE_TYPE_DEF_VAR_IN_VAR_TMP))
        {
            return to_ref;//数组或指针的使用（a[34][34] **a 等），暂时没有引用的用法。引用就是他自己
        }
        if((to_ref->m_type==ICODE_TYPE_CONST_STRING)||(to_ref->m_type==ICODE_TYPE_CONST_LIST))
        {
            return to_ref;//2020.12.18 常量字符串和列表，不要引用
        }

    }



    icode *e_ref = new_icode();
    e_ref->m_type = ICODE_TYPE_SYMBOL_REF;
    if(to_ref==NULL)
    {
        ///未知引用
        e_ref->result = (NULL);
        return e_ref;
    }
    if(to_ref->m_type==ICODE_TYPE_SYMBOL_REF)
    {
        ///ref 的设置，不能使用set_result 否则会导致变量parent的变化
        //如果已经是引用，则去除一层引用
        e_ref->result = to_ref->result;
        if(to_ref->result==NULL)
        {
            e_ref->name = to_ref->name;
            e_ref->is_ptr = to_ref->is_ptr;
            e_ref->is_array = to_ref->is_array;
            e_ref->array_cnt = to_ref->array_cnt;
        }
    }
    else
    {
        e_ref->result = to_ref;
    }

    return e_ref;
}

icode *icodes::new_temp_var()
{
    std::stringstream ss;


    icode *e = new_icode();


    ss<<e;

    e->m_type = ICODE_TYPE_DEF_VAR_TMP;
    e->name = "TMP_" + ss.str(); //get_temp_name();
    return e;
}

icode *icodes::new_copy_icode_gen(icode *from, icode *to)
{
    icode *b = new_icode();
    b->m_type = ICODE_TYPE_EXP_OP;
    b->name = "=";//"="

    if(from->is_def_var())
    {
        from = new_ref_icode(from);
    }
    if((to->is_def_var()))
    {
        to = new_ref_icode(to);
    }


    b->right = from;
    /// 2020.8.19 修改为left=NULL
    //b->left = to;
    b->left = NULL;
    b->result = to;


    return b;
}

icode *icodes::new_var_in_var_icode(icode *to_ref)
{
    icode * to_def = get_def_var(to_ref);

#if 0
    if((to_def->m_type==ICODE_TYPE_DEF_VAR_IN_VAR)||
            (to_def->m_type==ICODE_TYPE_DEF_VAR_IN_VAR_TMP))
    {//如果已经是变量内部引用，则只复制，增加ptr

        icode *e_ref = new_ref_icode(to_def->result);
        e_ref->m_type = ICODE_TYPE_DEF_VAR_IN_VAR;
        if(to_def->result==NULL)
        {
            ///未知引用
            e_ref->result = NULL;
            return e_ref;
        }
        e_ref->is_ptr = to_def->result->is_ptr;
        e_ref->is_ptr--;
        return e_ref;
    }
#endif

    icode *e_ref = new_ref_icode(to_ref);
    e_ref->m_type = ICODE_TYPE_DEF_VAR_IN_VAR;
    if(to_ref==NULL)
    {
        ///未知引用
        e_ref->result = NULL;
        return e_ref;
    }

    e_ref->is_ptr--;

    return e_ref;
}
icode *icodes::new_var_in_var_tmp_icode(icode *to_ref)
{
#if 0
    icode * to_def = get_def_var(to_ref);

    if((to_def->m_type==ICODE_TYPE_DEF_VAR_IN_VAR)||
            (to_def->m_type==ICODE_TYPE_DEF_VAR_IN_VAR_TMP))
    {//如果已经是变量内部引用，则只复制，增加ptr

        icode *e_ref = new_ref_icode(to_def->result);
        e_ref->m_type = ICODE_TYPE_DEF_VAR_IN_VAR_TMP;
        if(to_def->result==NULL)
        {
            ///未知引用
            e_ref->result = NULL;
            return e_ref;
        }
        e_ref->is_ptr = to_def->result->is_ptr;
        e_ref->is_ptr--;
        return e_ref;
    }
#endif



    icode *e_ref = new_ref_icode(to_ref);
    e_ref->m_type = ICODE_TYPE_DEF_VAR_IN_VAR_TMP;
    if(to_ref==NULL)
    {
        ///未知引用
        e_ref->result = NULL;
        return e_ref;
    }

    e_ref->is_ptr--;

    return e_ref;
}

icode *icodes::new_temp_ptr_var(icode *in_ptr_type, target_base* mtarget)
{

    icode *result_new = new_temp_var();
    result_new->m_bit_width = mtarget->get_basic_type_bit_width("GENERIC_PTR");;/// FIXME 通用指针长度需要通过m_target获取。而m_target不在此处访问？ this->m_target->get_basic_type_bit_width("GENERIC_PTR");
    result_new->is_ptr=1;//1维指针
    result_new->is_signed = 0;
    result_new->m_in_ptr_type = new_icode( * in_ptr_type );//指针指向的数据类型


    return result_new;
}

icode *icodes::new_temp_ptr_ptr_var(target_base* mtarget)
{
    icode *ptr_type_ic = new_temp_var();
    ptr_type_ic->m_bit_width = mtarget->get_basic_type_bit_width("GENERIC_PTR");
    ptr_type_ic->is_signed = 0;
    return new_temp_ptr_var(ptr_type_ic, mtarget);
}

icode *icodes::get_function(std::string func_name)
{
    sym*s = m_sym_manage.find_symbol(func_name);

    if (s==NULL)
    {
        return NULL;
    }
    return s->def_icode;

}

