#include "icode_manage.h"
#include "mylog.h"
#include "target_base.h"
#include "icodes.h"
using mylog::cout;
using mylog::cerr;

icode_manage::icode_manage()
{
    //m_icode_index = 0;


    m_top_icodes =  new icodes();
    m_top_icodes_need_free=0;
}

icode_manage::~icode_manage()
{
    if(m_top_icodes_need_free)
    {
        delete m_top_icodes;
        m_top_icodes=NULL;
    }

}


icode* icode_manage::new_icode()
{
    //cout<<"new_icode:icode_index:"<<m_icode_index<<"\n";

    return m_top_icodes->new_icode();
}

icode* icode_manage::new_icode(ICODE_TYPE mtype)
{
    return m_top_icodes->new_icode(mtype);
}

icode* icode_manage::new_icode(const icode &cp)
{

    return m_top_icodes->new_icode(cp);
}

icode *icode_manage::new_iconst_icode(int const_num)
{
    return m_top_icodes->new_iconst_icode(const_num);
}


#if 0
int icode_manage::new_icode_number()
{
    return m_icode_index++;
}

void icode_manage::clear_all_icode()
{
    for(auto i=m_icodes.begin();i!=m_icodes.end();++i)
    {
        delete (*i);
    }
    m_icodes.clear();
    m_icode_number_dict.clear();
    m_icode_index = 0;

}
#endif



void icode_manage::merge_mzo(const std::string& mzo_str)
{
}

std::string icode_manage::to_str()
{
    return m_top_icodes->m_top_icodes->to_str();
}

std::string icode_manage::to_str(icode *ic)
{
    return ic->to_str();
}


icode * icode_manage::new_var(std::string name, icode * typedec, int &is_already_exist)
{
    icode *def_ic = new_icode();

    def_ic->name = name;
    return new_var(def_ic, typedec, is_already_exist);
}


icode *icode_manage::new_var(icode *def_ic, icode *typedec, int &is_already_exist)
{

    is_already_exist = 0;
    ///============================
    //需要检查，之前是否有extern。如果有，则替换之前的

    sym * s = this->find_symbol(def_ic->get_name());

    if(s!=NULL)
    {
        //找到已有
        if(s->def_icode->m_level==this->m_top_icodes->m_sym_manage.m_level)
        {
            is_already_exist = 1;

            //找到并且是1个等级的，则必须是extern?
            if(!s->def_icode->is_extern)
            {
                //重复定义？
                cerr<<"variable multipi-definiation error. "<< *s->def_icode<<"\n";
                cerr<<"first defined here: "<< s->def_icode->m_dir_source<<": "<<s->def_icode->m_dir_line_no<<"\n";
                cerr<<"now defined here: "<< typedec->m_dir_source<<": "<<typedec->m_dir_line_no<<"\n";
                return s->def_icode;
            }

            //之前有一个extern的变量：同名且同等级
            s->def_icode->is_extern = 0;
            return s->def_icode;
        }
        else if(0==s->def_icode->m_level)
        {
            cout<<"WARNING: symbol redefined in local as global name:"<<s->def_icode->name<<"\n";
        }
    }

    ///============================
    ///

    icode *a= new_icode();

    a->m_type = ICODE_TYPE_DEF_VAR;
    a->name = def_ic->name;
    this->add_symbol(a->name, a);

    if((! def_ic->is_array)&&(!def_ic->is_ptr))
    {
        //复制所有的，除了id号和name
        int aid = a->m_icode_number;
        *a = *typedec;
        a->m_icode_number = aid;
        a->name = def_ic->name;

    }
    else if(def_ic->is_array)
    {
        ///数组定义 int a[]; 数组is_array属性在后面def_ic，而不是typedec
        a->m_in_ptr_type = new_icode(*typedec);
        //数组
        a->is_array = def_ic->is_array;
        a->array_cnt=def_ic->array_cnt;
        //数组元素，总体无符号
        a->is_signed = 0;
        ///此处必须先设置bitwidth为单个元素的bitwidth，才能求得总体元素的所有bitwidth
        a->m_bit_width = typedec->m_bit_width;
        a->m_bit_width = a->get_array_bit_width();
    }
    else if(def_ic->is_ptr)
    {
        ///指针定义 int *a; is_ptr属性在后面def_ic，而不是typedec
        a->m_type=ICODE_TYPE_DEF_VAR;
        a->m_in_ptr_type = new_icode(*typedec);
        //a->m_in_ptr_bit_width = a->m_bit_width;
        //a->m_in_ptr_is_float32 = a->is_float32;
        //a->m_in_ptr_is_signed = a->is_signed;

        //指针元素，总体无符号
        a->is_signed = 0;
        a->m_bit_width = this->m_target->get_basic_type_bit_width("GENERIC_PTR");
        a->is_ptr = def_ic->is_ptr;
    }


    if(a->is_typedef)
    {
        m_typedef.push_back(a);
    }

    ///20201206
    /// 添加m_full_name
    /// 用于结构体内部变量
    ///

    a->m_full_name.clear();
    new_var_struct_add_full_name(a);

    return a;
}



icode *icode_manage::new_temp_var()
{
    return m_top_icodes->new_temp_var();
}




void icode_manage::new_var_struct_add_full_name(icode *a)
{
    if(a->is_struct || a->is_union)
    {
        ///新建一个结构体时，将内部变量进行复制
        ///

        std::vector<icode*> old_ic = a->m_struct_type;
        a->m_struct_type.clear();
        for(int i=0;i<old_ic.size();++i)
        {
            //复制所有的，除了id号
            icode * nn = new_icode();
            int aid = nn->m_icode_number;

            *nn = *old_ic[i];
            nn->m_icode_number = aid;
            a->m_struct_type.push_back(nn);
        }



        for(int i=0;i<a->m_struct_type.size();++i)
        {
            icode *sub = a->m_struct_type[i];
            sub->m_full_name = (a->is_ptr? a->get_name()+"->"+sub->name:a->get_name()+"."+sub->name);
            new_var_struct_add_full_name(sub);
        }
    }
}


std::string icode_manage::get_temp_name(std::string prefix)
{
    ///生成一个临时变量的名字
    std::stringstream a;

    m_tmp_var_name_index++;

    a<<prefix<<m_tmp_var_name_index;

    return a.str();
}

icode *icode_manage::get_def_var(icode *ic)
{
    return m_top_icodes->get_def_var(ic);
#if 0
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
#endif
}
