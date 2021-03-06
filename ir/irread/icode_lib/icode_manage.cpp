#include "icode_manage.h"
#include "mylog.h"
#include "target_base.h"
#include "icodes.h"
#include "number2str.h"
using mylog::cout;
using mylog::cerr;

icode_manage::icode_manage(int target_typ)
{
    //m_icode_index = 0;

    m_label_index=0;
    m_curr_func = NULL;
    m_top_icodes =  new icodes(target_typ);
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

icode *icode_manage::new_opr_icode(std::string name, icode * left, icode* right, icode* result)
{
    return m_top_icodes->new_opr_icode(name, left, right, result);
}

icode* icode_manage::new_icode(ICODE_TYPE mtype)
{
    icode *n = m_top_icodes->new_icode(mtype);
    if(mtype==ICODE_TYPE_LABELED_BLOCK)
    {
        n->name = get_temp_label_name("");
    }
    return n;
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
    /// 定义新变量

    /// typedec(int) def_ic(a)
    /// typedec(int) def_ic(*a)
    /// typedef(typedef int) def_ic(a)
    /// typedef(typedef int) def_ic(*a)
    icode *a= new_icode();

    a->m_type = ICODE_TYPE_DEF_VAR;
    a->name = def_ic->name;
    this->add_symbol(a->name, a);

    if(def_ic->m_type==ICODE_TYPE_FUNC)
    {
        ///函数声明。 def_ic中包含函数名称，函数参数等信息
        ///         typecdec中是返回值的类型信息
        int aid = a->m_icode_number;
        *a = *def_ic;
        a->m_icode_number = aid;
        a->name = def_ic->name;


        assert(a->sub_icode.size()>0);
        //正常函数
        a->m_type=ICODE_TYPE_FUNC;
        a->is_extern = 1;

        ///函数返回值
        int sid = a->sub_icode[0]->m_icode_number;
        *a->sub_icode[0] = *typedec;
        a->sub_icode[0]->m_icode_number = sid;

        a->sub_icode[0]->m_type = ICODE_TYPE_FUNC_RET_TYPE;
        a->sub_icode[0]->name = this->get_func_ret_var_name(def_ic->name);
        a->sub_icode[0]->is_typedef = 0;

        for(int i=1;i<a->sub_icode.size();++i)
        {
            a->sub_icode[i]->m_type = ICODE_TYPE_FUNC_DEF_ARG;
        }



    }


    if((! def_ic->is_array)&&(!def_ic->is_ptr))
    {
        if(a->m_type!=ICODE_TYPE_FUNC)
        {
            //复制所有的，除了id号和name
            int aid = a->m_icode_number;
            *a = *typedec;
            a->m_icode_number = aid;
            a->name = def_ic->name;
        }
    }
    else if(def_ic->is_array)
    {
        ///数组定义 int a[]; 数组is_array属性在后面def_ic，而不是typedec
        a->m_in_ptr_type = new_icode(*typedec);


        ///2021.3.19 解决typedef char [10] A;的问题
        a->is_typedef = typedec->is_typedef;
        a->m_in_ptr_type->is_typedef = 0;//内部的不能是typedef?????

        //数组
        a->is_array = def_ic->is_array;
        a->array_cnt=def_ic->array_cnt;


        //数组元素，总体无符号
        a->is_signed = 0;

        //2021.1.28添加数组声明。如果数组中元素是const或者code。则数组定义为const或code
        if(typedec->is_const)a->is_const = 1;
        if(typedec->is_code)a->is_code = 1;


        /// 2021.1.23 此处已经不需要先设置m_bit_width。只需要设置m_in_ptr_type即可
        /// 2020. 此处必须先设置bitwidth为单个元素的bitwidth，才能求得总体元素的所有bitwidth
        a->m_bit_width = typedec->m_bit_width;
        //a->m_bit_width = a->get_array_bit_width();
        a->refresh_array_total_bit_width();



    }
    else if(def_ic->is_ptr)
    {

        if(def_ic->m_type==ICODE_TYPE_FUNC)
        {
            ///是函数指针
            ///函数至少有一个返回值
            a->m_in_ptr_type = new_icode(*a);
            a->m_in_ptr_type->is_ptr = 0;//函数指针，指向的类型是函数，而不是函数指针
            a->m_type=ICODE_TYPE_DEF_VAR;
            a->is_extern = 0;//函数指针，默认不再是extern类型
        }
        else
        {
            a->m_type=ICODE_TYPE_DEF_VAR;
            ///指针定义 int *a; is_ptr属性在后面def_ic，而不是typedec
            a->m_in_ptr_type = new_icode(*typedec);
        }


        ///2021.3.19 解决typedef char * A;的问题
        /// typedec(typedef char) def_ic(*A)
        ///
        a->is_typedef = typedec->is_typedef;
        a->m_in_ptr_type->is_typedef = 0;//内部的不能是typedef?????
        //a->m_in_ptr_bit_width = a->m_bit_width;
        //a->m_in_ptr_is_float32 = a->is_float32;
        //a->m_in_ptr_is_signed = a->is_signed;

        //指针元素，总体无符号
        a->is_signed = 0;
        a->m_bit_width = this->m_top_icodes->m_target->get_basic_type_bit_width("GENERIC_PTR");
        a->is_ptr = def_ic->is_ptr;

    }




    ///-----------------
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

std::string icode_manage::get_label_name(std::string str1)
{
    if(m_curr_func==NULL)
    {
        return "_labelgo_"+str1;
    }
    return "_labelgo_"+m_curr_func->name+"_"+str1;
}

std::string icode_manage::get_temp_label_name(std::string str1)
{
    if(m_curr_func==NULL)
    {
        return "_labelc_"+NumberToStr(m_label_index++);
    }
    return "_labelc_"+m_curr_func->name+"_"+NumberToStr(m_label_index++);
}

icode *icode_manage::get_def_var(icode *ic)
{
    return m_top_icodes->get_def_var(ic);

}




std::string icode_manage::get_func_ret_var_name(std::string func_name)
{
    return "__"+func_name+"_ret";
}
