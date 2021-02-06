#include "mylog.h"
#include "icode.h"
#include "icodes.h"
#include "icode_const_folder.h"
#include "icode_ref_number.h"
using mylog::cerr;

icode_const_folder::icode_const_folder()
{
}

icode_const_folder::~icode_const_folder()
{

}

void icode_const_folder::execute(icodes *ics)
{
    /// 常量折叠前，需要先更新各变量的引用计数
    /// 因为引用计数可能不对。
    icode_ref_number m_ref_number;
    m_ref_number.execute(ics);


    this->pcompi = ics;
    //通过循环，知道所有常量都处理完成。
    int ret = process_topcode(ics->m_top_icodes);
    while(ret>0)
    {
        ret = process_topcode(ics->m_top_icodes);
    }

    second_cleanup_tmp_var();

}


///https://en.cppreference.com/w/c/language/expressions
/// 运算符根据上面网址编写
long long icode_const_folder::iconst_opr(icode *ic, bool &can_folder)
{
    long long ret = 0;

    can_folder = 1;
    if(ic->name=="+")
    {
        ret = ic->right->num;
        ret += ic->left->num;
    }
    else if(ic->name=="-")
    {
        ret = ic->left->num;
        ret -= ic->right->num;
    }
    else if(ic->name=="*")
    {
        ret = ic->left->num;
        ret *= ic->right->num;
    }
    else if(ic->name=="/")
    {
        ret = ic->left->num;
        ret /= ic->right->num;
    }
    else if(ic->name=="%")
    {
        ret = ic->left->num % ic->right->num;
    }
    else if(ic->name=="~")
    {
        //需要知道算符是left还是right
        //assert(0);
        ret = ~ ic->right->num;
    }
    else if(ic->name=="&")
    {
        ret = ic->left->num & ic->right->num;
    }
    else if(ic->name=="|")
    {
        ret = ic->left->num | ic->right->num;
    }
    else if(ic->name=="^")
    {
        ret = ic->left->num ^ ic->right->num;
    }
    else if(ic->name=="<<")
    {
        ret = ic->left->num << ic->right->num;
    }
    else if(ic->name==">>")
    {
        ret = ic->left->num >> ic->right->num;
    }
    else if(ic->name=="!")
    {
        ret = !ic->right->num;
    }
    else if(ic->name=="&&")
    {
        ret = ic->left->num && ic->right->num;
    }
    else if(ic->name=="||")
    {
        ret = ic->left->num || ic->right->num;
    }
    else if(ic->name=="==")
    {
        if(ic->left->num==ic->right->num)
        {
            ret=1;
        }
        else
        {
            ret=0;
        }
    }
    else if(ic->name=="!=")
    {
        if(ic->left->num==ic->right->num)
        {
            ret=0;
        }
        else
        {
            ret=1;
        }
    }
    else if(ic->name=="<")
    {
        if(ic->left->num<ic->right->num)
        {
            ret=1;
        }
        else
        {
            ret=0;
        }
    }
    else if(ic->name==">")
    {
        if(ic->left->num>ic->right->num)
        {
            ret=1;
        }
        else
        {
            ret=0;
        }
    }
    else if(ic->name=="<=")
    {
        if(ic->left->num<=ic->right->num)
        {
            ret=1;
        }
        else
        {
            ret=0;
        }
    }
    else if(ic->name==">=")
    {
        if(ic->left->num>=ic->right->num)
        {
            ret=1;
        }
        else
        {
            ret=0;
        }
    }
    else if(ic->name=="negative")
    {
        ///只有right
        ///
        ret = -ic->right->num;
    }
    else if(ic->name=="positive")
    {
        ///只有right
        ///
        ret = +ic->right->num;
    }
    else if((ic->name=="+=")||
            (ic->name=="-=")||
            (ic->name=="*=")||
            (ic->name=="/=")||
            (ic->name=="%=")||
            (ic->name=="&=")||
            (ic->name=="|=")||
            (ic->name=="^=")||
            (ic->name=="<<=")||
            (ic->name==">>=")||
            (ic->name=="++")||
            (ic->name=="--")||
            (ic->name=="init")
            )

    {
        can_folder = 0;
    }
    else
    {
        cerr<<"const folder: unknown opr"<< ic->name<<"\n";
        can_folder = 0;
    }
    return ret;
}


double icode_const_folder::fconst_opr(icode *ic, bool &can_folder)
{
    double ret=0.0;
    can_folder = 1;

    if(ic->name=="+")
    {
        ret = ic->right->m_type==ICODE_TYPE_F_CONST?ic->right->fnum: ic->right->num;
        ret += ic->left->m_type==ICODE_TYPE_F_CONST?ic->left->fnum: ic->left->num;
    }
    else if(ic->name=="-")
    {
        ret = ic->left->m_type==ICODE_TYPE_F_CONST?ic->left->fnum: ic->left->num;
        ret -= ic->right->m_type==ICODE_TYPE_F_CONST?ic->right->fnum: ic->right->num;
    }
    else if(ic->name=="*")
    {
        ret = ic->left->m_type==ICODE_TYPE_F_CONST?ic->left->fnum: ic->left->num;
        ret *= ic->right->m_type==ICODE_TYPE_F_CONST?ic->right->fnum: ic->right->num;
    }
    else if(ic->name=="/")
    {
        ret = ic->left->m_type==ICODE_TYPE_F_CONST?ic->left->fnum: ic->left->num;
        ret /= ic->right->m_type==ICODE_TYPE_F_CONST?ic->right->fnum: ic->right->num;
    }
    else if(ic->name=="negative")
    {
        ///只有right
        ///
        ret = -ic->right->fnum;
    }
    else
    {
        can_folder = 0;
        cerr<<"const folder: unknown opr"<< ic->name<<"\n";
        //assert(0);
    }
    return ret;
}

bool icode_const_folder::is_const_ref(icode *ic)
{
    if(ic==NULL)
    {
        return false;
    }
    if((ic->m_type==ICODE_TYPE_SYMBOL_REF)&&
            (ic->result!=NULL)&&
            (ic->result->is_const_var())
            )
    {
        return true;
    }
    return false;
}


icode *icode_const_folder::const_folder_opr(icode *ic, bool &can_folder)
{
    icode * result_tmp = pcompi->new_icode();

    if(((ic->right)&&(ic->right->m_type==ICODE_TYPE_F_CONST))||
            ((ic->left)&&(ic->left->m_type==ICODE_TYPE_F_CONST)))
    {
        result_tmp->m_type=ICODE_TYPE_F_CONST;
    }
    else
    {
        result_tmp->m_type=ICODE_TYPE_I_CONST;
    }

    if(result_tmp->m_type==ICODE_TYPE_I_CONST)
    {
        long long val = iconst_opr(ic, can_folder);
        result_tmp->num = val;
    }
    else
    {
        result_tmp->fnum = fconst_opr(ic, can_folder);
    }

    result_tmp->const_refresh_width();

    return result_tmp;
}

int icode_const_folder::process_one_icode(icode *ic, std::vector<icode *> &parent, int index, void *user_data, class icode *iparent)
{

    return first_folder(ic, parent, index);
}

int icode_const_folder::second_cleanup_tmp_var()
{
    for(unsigned i=0;i<this->m_icodes.size();++i)
    {
        assert(this->m_icodes[i]->right==NULL);
        assert(this->m_icodes[i]->left==NULL);
        assert(this->m_icodes[i]->result==NULL);
        assert(this->m_icodes[i]->sub_icode.size()==0);
        this->m_icodes[i]->m_type=ICODE_TYPE_BLOCK;
    }
    this->m_icodes.clear();
    return 0;
}

int icode_const_folder::first_folder(icode *ic, std::vector<icode *> &parent, int index)
{

    /// 处理常量计算的数据
    ///
    ///

    ///=========================================
    ///正常情况下const不会被引用。
    /// 但是在常量折叠中，原来是变量，使用的引用，后来变为常量后，会有常量引用的情况
    ///
    if(is_const_ref(ic->right))
    {
        ///如果是常量的引用，则复制常量，去掉引用
        ic->right->const_copy_from(ic->right->result);
        ic->right->result = NULL;
    }

    if(is_const_ref(ic->left))
    {
        //ic->left = ic->left->result;
        ic->left->const_copy_from(ic->left->result);
        ic->left->result = NULL;
    }

    if(is_const_ref(ic->result))
    {
        //ic->result = ic->result->result;
        ic->result->const_copy_from(ic->result->result);
        ic->result->result = NULL;
    }

    for(unsigned i=0;i<ic->sub_icode.size();++i)
    {
        if(is_const_ref(ic->sub_icode[i]))
        {
            ic->sub_icode[i]->const_copy_from(ic->sub_icode[i]->result);
            ic->sub_icode[i]->result = NULL;
            //ic->sub_icode[i]->result = ic->sub_icode[i]->result->result;
        }
    }

    ///=========================================

    ///================
    /// 常量表达式折叠。只有表达式才能
    if(ic->m_type!=ICODE_TYPE_EXP_OP)
    {
        return 0;
    }

    /// 没有结果的表达式，不操作
    if(ic->result==NULL)
    {
        return 0;
    }

    if((ic->name=="=")||
            (ic->name=="init")
            )
    {
        ///赋值表达式，不能再求折叠
        return 0;
    }


    // right 和left如果非空，则必须是常量

    if((ic->right!=NULL)&& (!ic->right->is_const_var()))
    {
        return 0;
    }
    if((ic->left!=NULL)&&(!ic->left->is_const_var()))
    {
        return 0;
    }


    if(ic->result->m_type!=ICODE_TYPE_SYMBOL_REF)
    {
        ///结果不是变量引用
        return 0;
    }
    if(ic->result->result==NULL)
    {
        ///结果未定义？
        return 0;
    }

    bool can_folder=0;
    icode *result_tmp = const_folder_opr(ic, can_folder);
    if(!can_folder)
    {
        //不能折叠，直接返回
        return 0;
    }

    if(ic->result->result->m_type==ICODE_TYPE_DEF_VAR_TMP)
    {
        if((ic->result->result->m_ref_number>2)||
                (ic->result->result->m_ref_write_number>1))
        {
            return 0;
        }
        /// 一个临时变量，写操作只有不大于1，次，读操作不大于1次.
        ///

        this->m_icodes.push_back(ic->result->result);

        /// 将临时变量改为常量
        icode *ret_tmp = ic->result->result;
        ret_tmp->const_copy_from(result_tmp);


        ///将算符运算icode改为空的block
        assert(parent[index]==ic);
        parent[index] = pcompi->new_icode();
        parent[index]->m_type=ICODE_TYPE_BLOCK;
        return 1;
    }
    else if(ic->result->result->m_type==ICODE_TYPE_DEF_VAR)
    {
        //普通变量，遇到常数计算，则将算符改为=
        ic->name = "=";
        ic->right = result_tmp;
        ic->left = NULL;//ic->result;
        return 1;
    }

    assert(0);
    return 0;
}




