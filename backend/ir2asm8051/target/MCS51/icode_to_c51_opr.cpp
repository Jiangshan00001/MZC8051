#include <assert.h>
#include <sstream>

#include "mylog.h"
#include "bit_addr_parse.h"
#include "icode_to_c51.h"
#include "icode_to_c51_opr.h"
#include "c51_addr.h"

using mylog::cout;
using mylog::cerr;

using namespace IR2ASM8051;

std::string icode_to_c51::to_asm_opr_is_not_equal(icode *ic)
{
    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);

    // 如果result没有，则无效？
    if(ic->result==NULL)
    {
        return std::string("");
    }

    c51_addr *left_t = get_target(ic->left);
    c51_addr *right_t = get_target(ic->right);
    c51_addr *result_t = get_target(ic->result);

    assert(result_t!=NULL);
    assert(left_t!=NULL);
    assert(right_t!=NULL);


    asm_str<<is_not_equal(left_t, right_t, result_t);
    return asm_str.str();
}

std::string icode_to_c51::to_asm_opr_is_equal(icode *ic)
{

    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);

    // 如果result没有，则无效？
    if(ic->result==NULL)
    {
        return std::string("");
    }

    c51_addr *left_t = get_target(ic->left);
    c51_addr *right_t = get_target(ic->right);
    c51_addr *result_t = get_target(ic->result);

    assert(result_t!=NULL);
    assert(left_t!=NULL);
    assert(right_t!=NULL);


    asm_str<<is_equal(left_t, right_t, result_t);
    return asm_str.str();
}

std::string icode_to_c51::to_asm_opr_logic_not(icode *ic)
{
    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);

    // 如果result没有，则无效？
    if(ic->result==NULL)
    {
        return std::string(";logic not with no result. just ignore\n");
    }

    c51_addr *right_t = get_target(ic->right);
    c51_addr *result_t = get_target(ic->result);

    assert(result_t!=NULL);
    assert(right_t!=NULL);


    asm_str<<logic_not(right_t, result_t);
    return asm_str.str();
}

std::string icode_to_c51::to_asm_opr_logic_and(icode *ic)
{
    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);

    // 如果result没有，则无效？
    if(ic->result==NULL)
    {
        return std::string(";logic and with no result. just ignore\n");
    }

    c51_addr *right_t = get_target(ic->right);
    c51_addr *left_t = get_target(ic->left);
    c51_addr *result_t = get_target(ic->result);

    assert(result_t!=NULL);
    assert(right_t!=NULL);
    assert(left_t!=NULL);

    asm_str<<logic_and(left_t, right_t, result_t);
    return asm_str.str();
}
std::string icode_to_c51::to_asm_opr_logic_or(icode *ic)
{
    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);

    // 如果result没有，则无效？
    if(ic->result==NULL)
    {
        return std::string(";logic and with no result. just ignore\n");
    }

    c51_addr *right_t = get_target(ic->right);
    c51_addr *left_t = get_target(ic->left);
    c51_addr *result_t = get_target(ic->result);

    assert(result_t!=NULL);
    assert(right_t!=NULL);
    assert(left_t!=NULL);

    asm_str<<logic_or(left_t, right_t, result_t);
    return asm_str.str();
}

std::string icode_to_c51::to_asm_opr_init(icode *ic)
{
    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);
    assert(ic->name=="init");

    c51_addr *right_t = get_target(ic->right);
    c51_addr *result_t = get_target(ic->result);


    assert(result_t!=NULL);
    assert(right_t!=NULL);

    ///==============================
    /// 此处处理sfr地址问题
    if(((get_def_var( ic->result)->is_sfr)||
            (get_def_var( ic->result)->is_sfr16)||
            (get_def_var( ic->result)->is_sfr32)))
    {//(result_t->m_addr==UNKNOWN_ADDR) (result_t->m_type==DATA_TYPE_DIRECT)
        ///此处是寄存器变量未赋值，则赋值
        /// sfr P0=0xC0;
        if(result_t->m_addr==UNKNOWN_ADDR)
        {
            result_t->m_addr = right_t->m_addr;
            asm_str<<";sfr "<<pcompi->get_def_var(ic->result)->name<<". addr:0x"<<std::hex<<right_t->m_addr<<"\n";
        }
        else if(result_t->m_addr != right_t->m_addr)
        {
            cerr<<"sfr address not equal err: 0x"<<std::hex<<result_t->m_addr<<". 0x"<<right_t->m_addr<<"\n";
            asm_str<<";sfr_addr_err "<<pcompi->get_def_var(ic->result)->name<<". old_addr:0x"<<std::hex<<result_t->m_addr<<"new_addr:"<<right_t->m_addr<<"\n";
        }
        return asm_str.str();
    }
    else if(get_def_var( ic->result)->is_sbit)//(result_t->m_type==DATA_TYPE_BIT)
    {
        ///&&(result_t->m_addr==UNKNOWN_ADDR)
        ///sbit变量地址赋值
        /// sbit P01=0xC1;
        if(result_t->m_addr==UNKNOWN_ADDR)
        {
            result_t->m_addr = right_t->m_addr;
        }
        else if(result_t->m_addr != right_t->m_addr)
        {
            cerr<<"sbit address not equal err: 0x"<<std::hex<<result_t->m_addr<<". 0x"<<right_t->m_addr<<"\n";
        }
        asm_str<<";sbit "<<pcompi->get_def_var(ic->result)->name<<". addr:0x"<<std::hex<<right_t->m_addr<<"\n";
        return asm_str.str();
    }
    ///==============================

    if(ic->right->m_type==ICODE_TYPE_CONST_LIST)
    {
        if((ic->result->m_type==ICODE_TYPE_SYMBOL_REF)&&
                (ic->result->result->m_type==ICODE_TYPE_DEF_VAR)&&
                (ic->result->result->is_array))
        {
            if((ic->result->result->is_const)||
                    (ic->result->result->is_code))
            {
                /// int code a[]={1,2,3,5};
                /// code char a[] = "aabbcc";
                /// code不可能赋值，只有1此添加初始值的机会
                //result_t->labelA = left_t->labelA;

                //此处初始值初始化，只是将数组标签改为变量标签。因为变量默认都是没有空间的。
                /// FIXME: 无初始值的code代码会出问题？？？？ 因为没有初始值，就没有申请代码空间
                //right_t->labelA = result_t->ptr_target->labelA;
                ic->result->result->target->ptr_target->labelA = right_t->labelA;
                ic->result->result->target->labelA = right_t->labelA;
                //此处left一般为label
                return asm_str.str();
            }
            else
            {
                /// int a[]={1,2,3,5};
                asm_str<<mov(right_t, result_t->ptr_target);
                return asm_str.str();

            }


        }


    }

    ///==============================
    /// char a[]="1234";初始化，将字符串复制到数组a中
    /// char a[4]={1,2,3,4};

    if((ic->right->m_type==ICODE_TYPE_CONST_STRING)&&
            (ic->result->m_type==ICODE_TYPE_SYMBOL_REF)&&
            (ic->result->result->m_type==ICODE_TYPE_DEF_VAR)&&
            (ic->result->result->is_array)
            )
    {
        if((ic->result->result->is_const)||
                (ic->result->result->is_code)
                )
        {
            ic->result->result->target->ptr_target->labelA = right_t->labelA;
            ic->result->result->target->labelA = right_t->labelA;

        }
        else
        {
            asm_str<<mov(right_t->ptr_target, result_t->ptr_target);
            return asm_str.str();
        }
    }

    ///
    ///==============================
    ///
    /// 其他变量的初始化，使用mov函数
    ///
    ///

    asm_str<<mov(right_t, result_t);
    return asm_str.str();
}

//{"mov", DATA_TYPE_DIRECT, DATA_TYPE_DIRECT}
std::string icode_to_c51::to_asm_opr_mov(icode *ic)
{
    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);
    assert(ic->name=="=");

    ///2020.8.10 left_t 修改为right.
    /// 原来的 a=b; result=a; left=b
    /// 修改后：     result=a; right=b; left=a;
    c51_addr *left_t = get_target(ic->right);
    c51_addr *result_t = get_target(ic->result);


    assert(result_t!=NULL);
    assert(left_t!=NULL);




    asm_str<<mov(left_t, result_t);
    return asm_str.str();
}




///
/// \brief icode_to_c51::to_asm_opr_plus
/// \param ic
/// \return
std::string icode_to_c51::to_asm_opr_plus(icode *ic)
{
    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);
    assert(ic->name=="+");

    // 如果result没有，则无效？
    if(ic->result==NULL)
    {
        return std::string("");
    }

    c51_addr *left_t = get_target(ic->left);
    c51_addr *right_t = get_target(ic->right);
    c51_addr *result_t = get_target(ic->result);

    assert(result_t!=NULL);
    assert(left_t!=NULL);
    assert(right_t!=NULL);

    asm_str << add(left_t, right_t, result_t);

    return asm_str.str();
}



std::string icode_to_c51::to_asm_opr_sub(icode *ic)
{

    /// SUBB	A,Rn	Subtract Register from Acc with borrow
    /// SUBB	A,direct	Subtract direct byte from Acc with borrow
    /// SUBB	A,@Ri	Subtract indirect RAM from ACC with borrow
    /// SUBB	A,#data	Subtract immediate data from Acc with borrow


    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);
    assert(ic->name=="-");

    // 如果result没有，则无效？
    if(ic->result==NULL)
    {
        return std::string("");
    }

    c51_addr *left_t = get_target(ic->left);
    c51_addr *right_t = get_target(ic->right);
    c51_addr *result_t = get_target(ic->result);

    assert(result_t!=NULL);
    assert(left_t!=NULL);
    assert(right_t!=NULL);


    asm_str<<sub(left_t, right_t, result_t);
    return asm_str.str();
}


std::string icode_to_c51::to_asm_opr_mul(icode *ic)
{
    /// a=b * c;
    /// left=b right=c result=a;
    ///
    /// *a = b;
    /// right=a;
    /// result=var_tmp
    /// left=null
    ///
    /// b=*a;
    /// right=a;
    /// result=b;
    /// left=null;



    //MUL	AB	Multiply A & B

    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);
    assert(ic->name=="*");

    // 如果result没有，则无效？
    if(ic->result==NULL)
    {
        return std::string(";* opr with no result. just ignore");
    }

    c51_addr *left_t = get_target(ic->left);
    c51_addr *right_t = get_target(ic->right);
    c51_addr *result_t = get_target(ic->result);

    assert(result_t!=NULL);
    assert(right_t!=NULL);

    if(left_t!=NULL)
    {
        //普通乘法
        asm_str<<mulA(left_t, right_t, result_t);
    }
    else
    {
        //指针运算
        //此处是指针运算
        assert(0);
    }

    return asm_str.str();
}

std::string icode_to_c51::to_asm_opr_div(icode *ic)
{


    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);
    //assert(ic->name=="/");

    // 如果result没有，则无效？
    if(ic->result==NULL)
    {
        return std::string("");
    }

    c51_addr *left_t = NULL;


    if(ic->name=="/")
    { left_t = get_target(ic->left);
    }
    else if(ic->name=="/=")
    {
      left_t = get_target(ic->result);
    }
    else
    {
        assert(0);
    }
    c51_addr *right_t = get_target(ic->right);
    c51_addr *result_t = get_target(ic->result);

    assert(result_t!=NULL);
    assert(left_t!=NULL);
    assert(right_t!=NULL);


    asm_str<<divA(left_t, right_t, result_t);
    return asm_str.str();
}

std::string icode_to_c51::to_asm_opr_mod(icode *ic)
{
    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);

    // 如果result没有，则无效？
    if(ic->result==NULL)
    {
        return std::string("");
    }


    c51_addr *left_t = NULL;

    if(ic->name=="%")
    {
        left_t = get_target(ic->left);
    }
    else
    {
        left_t = get_target(ic->result);
    }


    c51_addr *right_t = get_target(ic->right);
    c51_addr *result_t = get_target(ic->result);

    assert(result_t!=NULL);
    assert(left_t!=NULL);
    assert(right_t!=NULL);


    asm_str<<modA(left_t, right_t, result_t);
    return asm_str.str();
}

std::string icode_to_c51::to_asm_opr_bit_and(icode *ic)
{
    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);

    // 如果result没有，则无效？
    if(ic->result==NULL)
    {
        return std::string("");
    }

    c51_addr *left_t = NULL;
    if(ic->name=="&")
    {
        left_t = get_target(ic->left);
    }
    else if(ic->name=="&=")
    {
        left_t = get_target(ic->result);
    }
    else
    {
        assert(0);
    }




    c51_addr *right_t = get_target(ic->right);
    c51_addr *result_t = get_target(ic->result);

    assert(result_t!=NULL);
    assert(left_t!=NULL);
    assert(right_t!=NULL);


    asm_str<<bit_and(left_t, right_t, result_t);
    return asm_str.str();
}

std::string icode_to_c51::to_asm_opr_bit_or(icode *ic)
{
    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);

    // 如果result没有，则无效？
    if(ic->result==NULL)
    {
        return std::string("");
    }

    c51_addr *left_t = NULL;
    if(ic->name=="|")
    {
        left_t = get_target(ic->left);
    }
    else
    {
        assert(ic->name=="|=");
        left_t = get_target(ic->result);
    }



    c51_addr *right_t = get_target(ic->right);
    c51_addr *result_t = get_target(ic->result);

    assert(result_t!=NULL);
    assert(left_t!=NULL);
    assert(right_t!=NULL);


    asm_str<<bit_or(left_t, right_t, result_t);
    return asm_str.str();
}

std::string icode_to_c51::to_asm_opr_shiftr(icode *ic)
{

    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);
    assert(ic->name==">>");

    // 如果result没有，则无效？
    if(ic->result==NULL)
    {
        return std::string("");
    }

    c51_addr *left_t = get_target(ic->left);
    c51_addr *right_t = get_target(ic->right);
    c51_addr *result_t = get_target(ic->result);

    assert(result_t!=NULL);
    assert(left_t!=NULL);
    assert(right_t!=NULL);


    asm_str<<shiftR(left_t, right_t, result_t);
    return asm_str.str();
}

std::string icode_to_c51::to_asm_opr_shiftl(icode *ic)
{
    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);
    assert(ic->name=="<<");

    // 如果result没有，则无效？
    if(ic->result==NULL)
    {
        return std::string("");
    }

    c51_addr *left_t = get_target(ic->left);
    c51_addr *right_t = get_target(ic->right);
    c51_addr *result_t = get_target(ic->result);

    assert(result_t!=NULL);
    assert(left_t!=NULL);
    assert(right_t!=NULL);


    asm_str<<shiftL(left_t, right_t, result_t);
    return asm_str.str();
}

std::string icode_to_c51::to_asm_opr_rotate_shiftr(icode *ic)
{

    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);
    assert(ic->name==">><");

    // 如果result没有，则无效？
    if(ic->result==NULL)
    {
        return std::string("");
    }

    c51_addr *left_t = get_target(ic->left);
    c51_addr *right_t = get_target(ic->right);
    c51_addr *result_t = get_target(ic->result);

    assert(result_t!=NULL);
    assert(left_t!=NULL);
    assert(right_t!=NULL);


    asm_str<<rotate_shiftR(left_t, right_t, result_t);
    return asm_str.str();
}

std::string icode_to_c51::to_asm_opr_rotate_shiftl(icode *ic)
{
    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);
    assert(ic->name=="><<");

    // 如果result没有，则无效？
    if(ic->result==NULL)
    {
        return std::string("");
    }

    c51_addr *left_t = get_target(ic->left);
    c51_addr *right_t = get_target(ic->right);
    c51_addr *result_t = get_target(ic->result);

    assert(result_t!=NULL);
    assert(left_t!=NULL);
    assert(right_t!=NULL);


    asm_str<<rotate_shiftL(left_t, right_t, result_t);
    return asm_str.str();
}


std::string icode_to_c51::to_asm_opr_plus_eq(icode *ic)
{
    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);
    assert(ic->name=="+=");

    // 如果result没有，则无效？
    if(ic->result==NULL)
    {
        return std::string("");
    }

    c51_addr *right_t = get_target(ic->right);
    c51_addr *result_t = get_target(ic->result);

    assert(result_t!=NULL);
    assert(right_t!=NULL);

    asm_str << add(right_t, result_t, result_t);

    return asm_str.str();
}

std::string icode_to_c51::to_asm_opr_sub_eq(icode *ic)
{
    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);
    assert(ic->name=="-=");

    // 如果result没有，则无效？
    if(ic->result==NULL)
    {
        return std::string("");
    }

    c51_addr *right_t = get_target(ic->right);
    c51_addr *result_t = get_target(ic->result);

    assert(result_t!=NULL);
    assert(right_t!=NULL);


    asm_str<<sub(result_t,right_t, result_t);
    return asm_str.str();
}

std::string icode_to_c51::to_asm_opr_mul_eq(icode *ic)
{
    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);
    assert(ic->name=="*=");

    // 如果result没有，则无效？
    if(ic->result==NULL)
    {
        return std::string("");
    }

    c51_addr *right_t = get_target(ic->right);
    c51_addr *result_t = get_target(ic->result);

    assert(result_t!=NULL);
    assert(right_t!=NULL);


    asm_str<<mulA(right_t, result_t, result_t);
    return asm_str.str();
}

std::string icode_to_c51::to_asm_opr_div_eq(icode *ic)
{
    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);
    assert(ic->name=="/=");

    // 如果result没有，则无效？
    if(ic->result==NULL)
    {
        return std::string("");
    }

    c51_addr *right_t = get_target(ic->right);
    c51_addr *result_t = get_target(ic->result);

    assert(result_t!=NULL);
    assert(right_t!=NULL);


    asm_str<<divA(result_t, right_t, result_t);
    return asm_str.str();
}

std::string icode_to_c51::to_asm_opr_shiftr_eq(icode *ic)
{
    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);
    assert(ic->name==">>=");

    // 如果result没有，则无效？
    if(ic->result==NULL)
    {
        return std::string("");
    }

    c51_addr *right_t = get_target(ic->right);
    c51_addr *result_t = get_target(ic->result);

    assert(result_t!=NULL);
    assert(right_t!=NULL);


    asm_str<<shiftR(result_t, right_t, result_t);
    return asm_str.str();
}

std::string icode_to_c51::to_asm_opr_shiftl_eq(icode *ic)
{
    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);
    assert(ic->name=="<<=");

    // 如果result没有，则无效？
    if(ic->result==NULL)
    {
        return std::string("");
    }

    c51_addr *right_t = get_target(ic->right);
    c51_addr *result_t = get_target(ic->result);

    assert(result_t!=NULL);
    assert(right_t!=NULL);


    asm_str<<shiftL(result_t, right_t, result_t);
    return asm_str.str();
}



std::string icode_to_c51::to_asm_opr_bit_not(icode *ic)
{
    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);
    assert(ic->name=="~");

    // 如果result没有，则无效？
    if(ic->result==NULL)
    {
        return std::string("");
    }

    c51_addr *right_t = get_target(ic->right);
    c51_addr *result_t = get_target(ic->result);

    assert(result_t!=NULL);
    assert(right_t!=NULL);


    asm_str<<bit_not(right_t, result_t);
    return asm_str.str();
}


std::string icode_to_c51::to_asm_opr_less(icode *ic)
{
    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);

    // 如果result没有，则无效？
    if(ic->result==NULL)
    {
        return std::string("");
    }

    c51_addr *left_t = get_target(ic->left);
    c51_addr *right_t = get_target(ic->right);
    c51_addr *result_t = get_target(ic->result);

    assert(result_t!=NULL);
    assert(left_t!=NULL);
    assert(right_t!=NULL);

    asm_str << lessA(left_t, right_t, result_t);

    return asm_str.str();
}

std::string icode_to_c51::to_asm_opr_greater(icode *ic)
{
    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);

    // 如果result没有，则无效？
    if(ic->result==NULL)
    {
        return std::string("");
    }

    c51_addr *left_t = get_target(ic->left);
    c51_addr *right_t = get_target(ic->right);
    c51_addr *result_t = get_target(ic->result);

    assert(result_t!=NULL);
    assert(left_t!=NULL);
    assert(right_t!=NULL);

    asm_str << greaterA(left_t, right_t, result_t);

    return asm_str.str();
}


std::string icode_to_c51::to_asm_opr_less_eq(icode *ic)
{
    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);

    // 如果result没有，则无效？
    if(ic->result==NULL)
    {
        return std::string("");
    }

    c51_addr *left_t = get_target(ic->left);
    c51_addr *right_t = get_target(ic->right);
    c51_addr *result_t = get_target(ic->result);

    assert(result_t!=NULL);
    assert(left_t!=NULL);
    assert(right_t!=NULL);

    asm_str << lessA(left_t, right_t, result_t, 1);

    return asm_str.str();
}

std::string icode_to_c51::to_asm_opr_greater_eq(icode *ic)
{
    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);

    // 如果result没有，则无效？
    if(ic->result==NULL)
    {
        return std::string("");
    }

    c51_addr *left_t = get_target(ic->left);
    c51_addr *right_t = get_target(ic->right);
    c51_addr *result_t = get_target(ic->result);

    assert(result_t!=NULL);
    assert(left_t!=NULL);
    assert(right_t!=NULL);

    asm_str << greaterA(left_t, right_t, result_t, 1);

    return asm_str.str();
}



std::string icode_to_c51::to_asm_opr_xor(icode *ic)
{
    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);

    // 如果result没有，则无效？
    if(ic->result==NULL)
    {
        return std::string("");
    }



    c51_addr *left_t = ic->name.size()==2?get_target(ic->result): get_target(ic->left);
    c51_addr *right_t = get_target(ic->right);
    c51_addr *result_t = get_target(ic->result);

    assert(result_t!=NULL);
    assert(left_t!=NULL);
    assert(right_t!=NULL);



    assert(result_t!=NULL);
    assert(left_t!=NULL);
    assert(right_t!=NULL);

    ///==============================
    /// 此处处理sbit地址问题
    if((get_def_var(ic->result)->is_sbit)&&(result_t->m_addr==UNKNOWN_ADDR))
    {
        //此处是
        unsigned bit_addr = 0;
        bool is_valid = bit_addr_parse(left_t->m_addr, right_t->m_addr, bit_addr);
        assert(is_valid);

        result_t->m_addr =  bit_addr;
        asm_str<<";sbit "<<get_def_var(ic->result)->name<<". addr:0x"<<std::hex<<bit_addr<<"\n";
        return asm_str.str();
    }
    ///==============================


    asm_str << xorA(left_t, right_t, result_t);

    return asm_str.str();
}


std::string icode_to_c51::to_asm_opr_jmp(icode *ic)
{
    std::stringstream asm_str;
    //根据距离，使用sjmp ajmp ljmp？？？
    //暂时只用ljmp.后期交给汇编优化

    assert(ic->result!=NULL);
    assert((ic->result->m_type==ICODE_TYPE_LABELED_BLOCK_START_REF)||(ic->result->m_type==ICODE_TYPE_LABELED_BLOCK_END_REF));

    if(ic->result->m_type==ICODE_TYPE_LABELED_BLOCK_START_REF)
    {
        asm_str<<"SJMP "<<this->m_inline_func_label_prefix<<  ic->result->result->get_block_start_label()<<";\n";
    }
    else
    {
        asm_str<<"SJMP "<<this->m_inline_func_label_prefix<< ic->result->result->get_block_end_label()<<";\n";
    }

    return asm_str.str();
}

///
/// \brief icode_to_c51::to_asm_opr_jnz
/// \param ic
/// \return
/// JC	rel	Jump if Carry is set
/// JNC	rel	Jump if Carry not set
/// JB	bit,rel	Jump if direct Bit is set
/// JNB	bit,rel	Jump if direct Bit is Not set
/// JBC	bit,rel	Jump if direct Bit is set & clear bit
/// AJMP	addr11	Absolute Jump
/// LJMP	addr16	Long Jump
/// SJMP	rel	Short Jump (relative addr)
/// JMP	@A+DPTR	Jump indirect relative to the DPTR
/// JZ	rel	Jump if Accumulator is Zero
/// JNZ	rel	Jump if Accumulator is Not Zero
/// CJNE	A,direct,rel	Compare direct byte to Acc and Jump if Not Equal
/// CJNE	A,#data,rel	Compare immediate to Acc and Jump if Not Equal
/// CJNE	Rn,#data,rel	Compare immediate to register and Jump if Not Equal
/// CJNE	@Ri,#data,rel	Compare immediate to indirect and Jump if Not Equal
/// DJNZ	Rn,rel	Decrement register and Jump if Not Zero
/// DJNZ	direct,rel	Decrement direct byte and Jump if Not Zero


std::string icode_to_c51::to_asm_opr_jnz(icode *ic)
{
    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);
    assert(ic->name=="JNZ");

    // 如果result没有，则无效？
    if(ic->result==NULL)
    {
        return std::string("");
    }

    c51_addr *left_t = get_target(ic->left);
    c51_addr *result_t = get_target(ic->result);

    assert(result_t!=NULL);
    assert(left_t!=NULL);

    asm_str<<jzA(left_t, result_t, 1);

    return asm_str.str();
}

std::string icode_to_c51::to_asm_opr_address_of(icode *ic)
{
    c51_addr *right_t = get_target(ic->right);
    c51_addr *result_t = get_target(ic->result);

    assert(result_t!=NULL);
    assert(right_t!=NULL);

    std::stringstream asm_str;
    c51_addr *ad = new c51_addr();

    ///char code a[5]={1,2,3};
    /// char *b=&a;
    /// &a <<----DATA_TYPE_J_DATA_LABEL

    if((right_t->m_type==DATA_TYPE_CODE)||
            (right_t->m_type==DATA_TYPE_J_DATA_LABEL)
            )
    {
        ad->m_type =DATA_TYPE_J_DATA_LABEL;
        ad->labelA = right_t->labelA;
    }
    else
    {
        ad->m_type = DATA_TYPE_J_DATA;
        ad->m_addr = right_t->m_addr;
    }
    ad->m_bit_width = 3*8;
    /// 2021.1.23 此处注释掉。
    /// right_t->m_addr=0x010008
    /// ad->m_addr = 010008 就是对的，添加上m_type=DATA_TYPE_J_DATA(7) 反而不对 了？？？
    if(right_t->m_type<=DATA_TYPE_CODE)
    {
        ad->m_addr =(ad->m_addr&0xffff)| (right_t->m_type <<16);
    }




    asm_str<<this->mov(ad, result_t);





    return asm_str.str();

}

std::string icode_to_c51::to_asm_opr_negative(icode *ic)
{
    std::stringstream asm_str;
    cerr<<"unsupported negative opr. should be done in ast-function\n";
#if 0
    if(ic->right->is_float())
    {
        //float数值，读出后，将最高位取反，其他不变，放入result


        return asm_str.str();
    }


    //没有direct，复制到A, R2 然后加
    int mov_bit=result->m_bit_width;
    int mov_byte_shift=0;
    while(mov_bit>0)
    {

        asm_str<<mov_byte_to_a(a1, mov_byte_shift);
        asm_str<<"MOV R7, A;\n";
        asm_str<<mov_byte_to_a(a2, mov_byte_shift);

        if(mov_byte_shift)
        {
            asm_str<<"ADDC A, R7;\n";
        }
        else
        {
            asm_str<<"ADD A, R7;\n";
        }
        asm_str<<mov_byte_a_to(result,  mov_byte_shift);

        mov_byte_shift++;
        mov_bit-=8;
    }
#endif
    return asm_str.str();
}

std::string icode_to_c51::to_asm_opr_mm(icode *ic)
{
    std::stringstream asm_str;

    assert(ic->m_type==ICODE_TYPE_EXP_OP);
    assert(ic->name=="--");


    c51_addr *result_t = get_target(ic->result);

    asm_str<<decA(result_t);
    return asm_str.str();
}
std::string icode_to_c51::to_asm_opr_pp(icode *ic)
{
    std::stringstream asm_str;

    assert(ic->m_type==ICODE_TYPE_EXP_OP);
    assert(ic->name=="++");


    //自增算符 ++i i++
    c51_addr *result_t = get_target(ic->result);

    asm_str<<incA(result_t);
    return asm_str.str();
}


std::string icode_to_c51::to_asm_opr_jz(icode *ic)
{
    std::stringstream asm_str;
    assert(ic->m_type==ICODE_TYPE_EXP_OP);
    assert(ic->name=="JZ");

    // 如果result没有，则无效？
    if(ic->result==NULL)
    {
        return std::string("");
    }

    c51_addr *left_t = get_target(ic->left);
    c51_addr *result_t = get_target(ic->result);

    assert(result_t!=NULL);
    assert(left_t!=NULL);

    asm_str<<jzA(left_t, result_t);

    return asm_str.str();
}




std::string icode_to_c51::add(c51_addr* a1, c51_addr* a2, c51_addr *result)
{

    ///
    /// ADD	A,Rn	Add register to Accumulator	1	12	ARITHMETIC OPERATIONS	0x28+$2
    /// ADD	A,direct	Add direct byte to Accumulator	2	12	ARITHMETIC OPERATIONS	0x25	$2
    /// ADD	A,@Ri	Add indirect RAM to Accumulator	1	12	ARITHMETIC OPERATIONS	0x26+$2
    /// ADD	A,#data	Add immediate data to Accumulator	2	12	ARITHMETIC OPERATIONS	0x24	$2
    /// ADDC	A,Rn	Add register to Accumulator with Carry	1	12	ARITHMETIC OPERATIONS	0x38+$2
    /// ADDC	A,direct	Add direct byte to Accumulator with Carry	2	12	ARITHMETIC OPERATIONS	0x35	$2
    /// ADDC	A,@Ri	Add indirect RAM to Accumulator with Carry	1	12	ARITHMETIC OPERATIONS	0x36+$2
    /// ADDC	A,#data	Add immediate data to Acc with Carry	2	12	ARITHMETIC OPERATIONS	0x34	$2
    /// CLR	A
    ///
    std::stringstream asm_str;


    if(a1->is_float32 || a2->is_float32)
    {
        ///此处只能执行浮点数的add
        /// 结果存入result
        /// 如果result不是float，则需要转换


        ///有一个字段是float的，则需要转为float，进行float计算
        ///

        if((a1->is_float32)&&(!a2->is_float32))
        {
            //from不是float，to是float。需要转换from为float
            asm_str<<this->mov_byte_to_r4(a2, 0);
            asm_str<<this->mov_byte_to_r5(a2, 1);
            asm_str<<this->mov_byte_to_r6(a2, 2);
            asm_str<<this->mov_byte_to_r7(a2, 3);

            asm_str<< this->lcall("_sys_fcast");

            asm_str<<this->mov_byte_to_r0(a1, 0);
            asm_str<<this->mov_byte_to_r1(a1, 1);
            asm_str<<this->mov_byte_to_r2(a1, 2);
            asm_str<<this->mov_byte_to_r3(a1, 3);


            asm_str<<this->lcall("_sys_fpadd");


            asm_str<<this->mov_byte_r4_to(result, 0);
            asm_str<<this->mov_byte_r5_to(result, 1);
            asm_str<<this->mov_byte_r6_to(result, 2);
            asm_str<<this->mov_byte_r7_to(result, 3);

            return asm_str.str();
        }
        else if((!a1->is_float32)&&(a2->is_float32))
        {
            asm_str<<this->mov_byte_to_r4(a1, 0);
            asm_str<<this->mov_byte_to_r5(a1, 1);
            asm_str<<this->mov_byte_to_r6(a1, 2);
            asm_str<<this->mov_byte_to_r7(a1, 3);

            asm_str<< this->lcall("_sys_fcast");

            asm_str<<this->mov_byte_to_r0(a2, 0);
            asm_str<<this->mov_byte_to_r1(a2, 1);
            asm_str<<this->mov_byte_to_r2(a2, 2);
            asm_str<<this->mov_byte_to_r3(a2, 3);


            asm_str<<this->lcall("_sys_fpadd");

            ///此处需要判断result是否是float，如不是，则cast先
            asm_str<<this->mov_byte_r4_to(result, 0);
            asm_str<<this->mov_byte_r5_to(result, 1);
            asm_str<<this->mov_byte_r6_to(result, 2);
            asm_str<<this->mov_byte_r7_to(result, 3);

            return asm_str.str();
        }
        else
        {
            //2个数据都是float，直接mov
            asm_str<<this->mov_byte_to_r4(a1, 0);
            asm_str<<this->mov_byte_to_r5(a1, 1);
            asm_str<<this->mov_byte_to_r6(a1, 2);
            asm_str<<this->mov_byte_to_r7(a1, 3);

            asm_str<<this->mov_byte_to_r0(a2, 0);
            asm_str<<this->mov_byte_to_r1(a2, 1);
            asm_str<<this->mov_byte_to_r2(a2, 2);
            asm_str<<this->mov_byte_to_r3(a2, 3);


            asm_str<<this->lcall("_sys_fpadd");

            asm_str<<this->mov_byte_r4_to(result, 0);
            asm_str<<this->mov_byte_r5_to(result, 1);
            asm_str<<this->mov_byte_r6_to(result, 2);
            asm_str<<this->mov_byte_r7_to(result, 3);

            return asm_str.str();
        }

        return asm_str.str();
    }


    if((a1->m_type==DATA_TYPE_J_DATA)&&(a2->m_type==DATA_TYPE_J_DATA))
    {
        //此处生成新的变量，使用mov语句操作
        c51_addr a3;
        a3.m_type = DATA_TYPE_J_DATA;
        a3.m_bit_width = a1->m_bit_width>a2->m_bit_width?a1->m_bit_width:a2->m_bit_width;
        a3.m_addr = a1->m_addr+a2->m_addr;
        asm_str<<this->mov(&a3, result);
    }
    else if((a1->m_type==DATA_TYPE_DIRECT)||(a2->m_type==DATA_TYPE_DIRECT))
    {
        if((!result->is_signed)||
                (!a1->is_signed)||
                (!a2->is_signed)
                )
        {
            ///add not signed
            ///
            int mov_bit=result->m_bit_width;
            int mov_byte_shift=0;
            while(mov_bit>0)
            {
                ///两个direct。如果长度不相等，则需要转移？

                c51_addr *dir_reg = a2;
                //将不是direct的放到a，和direct相加
                if(a2->m_type!=DATA_TYPE_DIRECT)
                {
                    dir_reg=a1;
                    asm_str<<mov_byte_to_a(a2, mov_byte_shift);
                }
                else
                {
                    dir_reg = a2;
                    asm_str<<mov_byte_to_a(a1, mov_byte_shift);
                }

                if(mov_byte_shift)
                {
                    if(mov_byte_shift< dir_reg->m_bit_width/8)
                    {
                        asm_str<<"ADDC A, 0x" <<std::hex<< dir_reg->m_addr+mov_byte_shift<<";\n";
                    }
                    else
                    {
                        ///超过了范围，添加到B?
                        ///

                        asm_str<<";ADDC A, #0\n";
                    }
                }
                else
                {
                    asm_str<<"ADD A, 0x" <<std::hex<< dir_reg->m_addr+mov_byte_shift<<";\n";
                }
                asm_str<<mov_byte_a_to(result,  mov_byte_shift);

                mov_byte_shift++;
                mov_bit-=8;
            }
        }
        else
        {
            //有符号数
            //没有direct，复制到A, R2 然后加
            int mov_bit=result->m_bit_width;
            int mov_byte_shift=0;
            while(mov_bit>0)
            {

                asm_str<<mov_byte_to_r7(a1, mov_byte_shift);
                asm_str<<mov_byte_to_a(a2, mov_byte_shift);

                if(mov_byte_shift)
                {
                    asm_str<<"ADDC A, R7;\n";
                }
                else
                {
                    asm_str<<"ADD A, R7;\n";
                }
                asm_str<<mov_byte_a_to(result,  mov_byte_shift);

                mov_byte_shift++;
                mov_bit-=8;
            }

        }



    }
    else
    {
        //没有direct，复制到A, R2 然后加
        int mov_bit=result->m_bit_width;
        int mov_byte_shift=0;
        while(mov_bit>0)
        {

            asm_str<<mov_byte_to_r7(a1, mov_byte_shift);
            asm_str<<mov_byte_to_a(a2, mov_byte_shift);

            if(mov_byte_shift)
            {
                asm_str<<"ADDC A, R7;\n";
            }
            else
            {
                asm_str<<"ADD A, R7;\n";
            }
            asm_str<<mov_byte_a_to(result,  mov_byte_shift);

            mov_byte_shift++;
            mov_bit-=8;
        }
    }

    return asm_str.str();
}



std::string icode_to_c51::sub(c51_addr *a1, c51_addr *a2, c51_addr *result, int is_set_c)
{
    ///2021.3.6
    /// 添加没有result的情况。
    /// 此情况是在两个数值做比较时，会调用sub函数。但是实际上相减的数值不需要复制，
    /// 只会通过CY结果判断大小


    /// SUBB	A,Rn	Subtract Register from Acc with borrow
    /// SUBB	A,direct	Subtract direct byte from Acc with borrow
    /// SUBB	A,@Ri	Subtract indirect RAM from ACC with borrow
    /// SUBB	A,#data	Subtract immediate data from Acc with borrow

    std::stringstream asm_str;
    if(is_set_c)
    {
        asm_str<<"SETB C;\n";
    }
    else
    {
        asm_str<<"CLR C;\n";
    }

    if((a1->m_type==DATA_TYPE_J_DATA)&&(a2->m_type==DATA_TYPE_J_DATA))
    {
        //此处生成新的变量，使用mov语句操作
        c51_addr a3;
        a3.m_type = DATA_TYPE_J_DATA;
        a3.m_bit_width = a1->m_bit_width>a2->m_bit_width?a1->m_bit_width:a2->m_bit_width;
        a3.m_addr = a1->m_addr - a2->m_addr;
        if(result!=NULL)
        {
            asm_str<<this->mov(&a3, result);
        }


    }
    else if((a2->m_type==DATA_TYPE_DIRECT))//(a1->m_type==DATA_TYPE_DIRECT)||
    {

        int mov_bit=a1->m_bit_width > a2->m_bit_width? a1->m_bit_width:a2->m_bit_width;
        if(result)
        {
            mov_bit = result->m_bit_width;
        }
        int mov_byte_shift=0;
        c51_addr *dir_reg = a2;

        while(mov_bit>0)
        {
            asm_str<<mov_byte_to_a(a1, mov_byte_shift);

            asm_str<<"SUBB A, 0x" <<std::hex<< dir_reg->m_addr+mov_byte_shift<<";\n";
            if(result!=NULL)
            {
                asm_str<<mov_byte_a_to(result,  mov_byte_shift);
            }
            mov_byte_shift++;
            mov_bit-=8;
        }
    }
    else
    {
        //没有direct，复制到A, R2 然后加
        int mov_bit=a1->m_bit_width>a2->m_bit_width?a1->m_bit_width:a2->m_bit_width;
        if(result)
        {
            mov_bit = result->m_bit_width;
        }
        int mov_byte_shift=0;
        while(mov_bit>0)
        {

            asm_str<<mov_byte_to_a(a2, mov_byte_shift);
            asm_str<<"MOV R2, A;\n";
            asm_str<<mov_byte_to_a(a1, mov_byte_shift);
            asm_str<<"SUBB A, R2;\n";
            if(result!=NULL)
            {
                asm_str<<mov_byte_a_to(result,  mov_byte_shift);
            }

            mov_byte_shift++;
            mov_bit-=8;
        }
    }
    return asm_str.str();
}


std::string icode_to_c51::mulA(c51_addr *a1, c51_addr *a2, c51_addr *result)
{

    std::stringstream asm_str;

    if((a1->m_type==DATA_TYPE_J_DATA)&&(a1->m_addr==1))
    {
        //任何数乘以1，都等于自己
        asm_str<<this->mov(a2, result);
    }
    else if((a2->m_type==DATA_TYPE_J_DATA)&&(a2->m_addr==1))
    {
        //任何数乘以1，都等于自己
        asm_str<<this->mov(a1, result);
    }
    else if((a1->m_type==DATA_TYPE_J_DATA)&&(a2->m_type==DATA_TYPE_J_DATA))
    {
        //此处生成新的变量，使用mov语句操作
        c51_addr a3;
        a3.m_type = DATA_TYPE_J_DATA;
        a3.m_bit_width = a1->m_bit_width>a2->m_bit_width?a1->m_bit_width:a2->m_bit_width;
        a3.m_addr = a1->m_addr*a2->m_addr;
        asm_str<<this->mov(&a3, result);
    }
    else if((a1->m_bit_width==8)&&(a2->m_bit_width==8))
    {

        //MUL	AB	Multiply A & B
        // 结果低位在A，高位在B

        /// 因为to_b会覆盖A，所以必须先to_b
        asm_str<<this->mov_byte_to_b(a1);
        asm_str<<this->mov_byte_to_a(a2);
        asm_str<<"MUL AB;\n";

        //此处必须先移动A，再移动B，因为移动B时会覆盖A

        asm_str<<this->mov_byte_a_to(result, 0);
        if(result->m_bit_width>8)
        {
            asm_str<<this->mov_byte_b_to(result, 1);
        }
        if(result->m_bit_width>16)
        {
            asm_str<<"MOV A, 0x0;\n";
            asm_str<<this->mov_byte_a_to(result, 2)<<"\n";
        }
        if(result->m_bit_width>24)
        {
            asm_str<<"MOV A, 0x0;\n";
            asm_str<<this->mov_byte_a_to(result, 3)<<"\n";
        }
        if(result->m_bit_width>32)
        {
            cerr<<"mul result not support>32bit \n";
            assert(0);
        }



    }
    else
    {
        unsigned max_bit_width = a1->m_bit_width;
        if(max_bit_width<a2->m_bit_width)
        {
            max_bit_width = a2->m_bit_width;
        }
        if(max_bit_width==16)
        {
            ///乘法 byte2xbyte2
            /// 乘数： R4 R5
            /// 被乘数: R6 R7
            /// 结果： R6 R7
            asm_str<<this->mov_byte_to_r4(a1, 0);
            asm_str<<this->mov_byte_to_r5(a1, 1);
            asm_str<<this->mov_byte_to_r6(a2, 0);
            asm_str<<this->mov_byte_to_r7(a2, 1);
            asm_str<<lcall("_sys_imul_byte2");
            asm_str<<this->mov_byte_r6_to(result,0);
            asm_str<<this->mov_byte_r7_to(result,1);
        }
        else if(max_bit_width==32)
        {
            ///乘法 byte4xbyte4
            /// 乘数： r0 r1 r2 r3
            /// 被乘数: r4 r5 r6 r7
            /// 结果： r4 r5 r6 r7

            asm_str<<this->mov_byte_to_r0(a1, 0);
            asm_str<<this->mov_byte_to_r1(a1, 1);
            asm_str<<this->mov_byte_to_r2(a1, 2);
            asm_str<<this->mov_byte_to_r3(a1, 3);

            asm_str<<this->mov_byte_to_r4(a2, 0);
            asm_str<<this->mov_byte_to_r5(a2, 1);
            asm_str<<this->mov_byte_to_r6(a2, 2);
            asm_str<<this->mov_byte_to_r7(a2, 3);

            if(a1->is_float32||a2->is_float32)
            {
                ///任何一个是float32,则两个数据都转换为float32，再使用float32相乘。结果为float32
                if(!a1->is_float32)
                {
                    //转换r0->r3为float32
                }
                if(!a2->is_float32)
                {
                    //转换r4-r7 为float32
                }
                asm_str<<lcall("_sys_func_mul_float_byte4");
                if(!result->is_float32)
                {
                    /// r4-r7从float32转为unsigned int

                }

                asm_str<<this->mov_byte_r4_to(result,0);
                asm_str<<this->mov_byte_r5_to(result,1);
                asm_str<<this->mov_byte_r6_to(result,2);
                asm_str<<this->mov_byte_r7_to(result,3);
            }
            else
            {
                asm_str<<lcall("_sys_lmul_byte4");
                asm_str<<this->mov_byte_r4_to(result,0);
                asm_str<<this->mov_byte_r5_to(result,1);
                asm_str<<this->mov_byte_r6_to(result,2);
                asm_str<<this->mov_byte_r7_to(result,3);
            }
        }
        else
        {
            cerr<<"ERROR: mulA -max_bit_width:"<<max_bit_width<<"\n";
            assert(0);
        }
    }

    return asm_str.str();
}

std::string icode_to_c51::bit_not(c51_addr *a1, c51_addr *result)
{
    std::stringstream asm_str;
    if(a1->m_type==DATA_TYPE_BIT)
    {
        asm_str<<"CPL 0x"<<std::hex << a1->m_addr<<";\n";
    }
    else if(a1->m_type==DATA_TYPE_J_DATA)
    {
        c51_addr a2 = *a1;
        a2.m_addr = ~a2.m_addr;
        asm_str<< this->mov(&a2, result);
    }
    else
    {
        int bit_width = a1->m_bit_width;
        int byte_shift=0;
        while(bit_width>0)
        {
            asm_str<< this->mov_byte_to_a(a1, byte_shift);
            asm_str<<"CPL A;\n";
            asm_str<<this->mov_byte_a_to(result, byte_shift);

            bit_width-=8;
            byte_shift++;
        }
    }
    return asm_str.str();
}

std::string icode_to_c51::bit_and(c51_addr *a1, c51_addr *a2, c51_addr *result)
{
    ///TODO 针对不同的指令的优化
    /// 指令选择器？？？
    ///
    int bit_width = result->m_bit_width;
    int byte_shift=0;
    std::stringstream asm_str;

    asm_str<< this->mov(a1, result);
    while(bit_width>0)
    {
        int R = m_Rn.get_reg();
        asm_str<< this->mov_byte_to_ri(a2, byte_shift,0,R);
        asm_str<< this->mov_byte_to_a(result, byte_shift);

        asm_str<<"ANL A, R"<< R<<";\n";
        m_Rn.free_reg(R);
        asm_str<<this->mov_byte_a_to(result, byte_shift);

        bit_width-=8;
        byte_shift++;
    }
    return asm_str.str();
}

std::string icode_to_c51::bit_or(c51_addr *a1, c51_addr *a2, c51_addr *result)
{
    ///TODO 针对不同的指令的优化
    /// 指令选择器？？？
    ///
    int bit_width = result->m_bit_width;
    int byte_shift=0;
    std::stringstream asm_str;

    if((a1->is_equal(result))&&(a1->m_bit_width==8)&&(a1->m_type==DATA_TYPE_DIRECT)&&(a2->m_type==DATA_TYPE_J_DATA))
    {
        //
        asm_str<<"ORL  0x"<<std::hex<<a1->m_addr<<", #0x"<<std::hex<<a2->num<<";\n";
        return asm_str.str();
    }



    asm_str<< this->mov(a1, result);
    while(bit_width>0)
    {
        int R = m_Rn.get_reg();
        asm_str<< this->mov_byte_to_ri(a2, byte_shift,0,R);
        asm_str<< this->mov_byte_to_a(result, byte_shift);

        asm_str<<"ORL A, R"<< R<<";\n";
        m_Rn.free_reg(R);
        asm_str<<this->mov_byte_a_to(result, byte_shift);

        bit_width-=8;
        byte_shift++;
    }
    return asm_str.str();}

std::string icode_to_c51::lessA(c51_addr *a1, c51_addr *a2, c51_addr *result, bool include_eq)
{

    /// a1<a2
    /// a1<=a2

    std::stringstream asm_str;
    std::string l1 = this->get_tmp_label("lessA");
    std::string l2 = this->get_tmp_label("lessA");


    /// a1<a2
    /// a1-a2
    /// 查看借位。如果a1<a2则有借位
    ///
    /// a1<=a2
    /// set c
    /// a1-a2
    /// 相当于a1-(a2+1)
    /// 如果a1<(a2+1)， 就认为是a1<=a2有借位
    asm_str<<this->sub(a1,a2, result, include_eq);

    /// 直接将C移动到A中。省略跳转
    ///
    asm_str<<"mov A, #0\n";
    asm_str<<"RLC A\n";
    asm_str<<this->mov_byte_a_to(result)<<";\n";

    #if 0

    asm_str<<"JC "<<l1<<";\n"; //a1<a2
    asm_str<<this->mov_0_to(result)<<";\n";//a1>=a2
    asm_str<<"SJMP "<<l2<<";\n";

    asm_str<<l1<<":\n";

    asm_str<<this->mov_1_to(result)<<";\n";

    asm_str<<l2<<":\n";
#endif

    return asm_str.str();
}

std::string icode_to_c51::greaterA(c51_addr *a1, c51_addr *a2, c51_addr *result, bool include_eq)
{
    std::stringstream asm_str;
    std::string l1 = this->get_tmp_label("lessA");
    std::string l2 = this->get_tmp_label("lessA");


    ///a1>=a2
    /// a1-a2
    /// 没有借位 则认为>=
    ///
    /// a1>a2
    ///
    /// set c
    /// a1-a2
    /// 相当于  a1-(a2+1)
    /// 没有借位，则认为a1>a2
    ///
    ///
    asm_str<<this->sub(a1,a2, NULL, !include_eq);


#if 0
    asm_str<<"JNC "<<l1<<";\n"; //a1<a2
    asm_str<<this->mov_0_to(result)<<";\n";//a1>=a2
    asm_str<<"SJMP "<<l2<<";\n";

    asm_str<<l1<<":\n";

    asm_str<<this->mov_1_to(result)<<";\n";

    asm_str<<l2<<":\n";
#else

    asm_str<<"MOV A, #0xff;\n";
    asm_str<<"RLC A;\n";//C->A0 A7->C
    asm_str<<"CPL A;\n";
    asm_str<<this->mov_byte_a_to(result)<<";\n";
#endif
    return asm_str.str();
}


std::string icode_to_c51::divA(c51_addr *a1, c51_addr *a2, c51_addr *result)
{
    std::stringstream asm_str;

    if((a1->m_type==DATA_TYPE_J_DATA)&&
            (a2->m_type==DATA_TYPE_J_DATA))
    {
        //此处直接计算结果
        a1->m_addr /= a2->m_addr;
        asm_str<< this->mov(a1, result);
    }
    else if((a1->m_bit_width==8)&&(a2->m_bit_width==8) &&(a1->is_signed==0)&&(a2->is_signed==0))
    {
        asm_str<<this->mov_byte_to_b(a2);
        asm_str<<this->mov_byte_to_a(a1);
        asm_str<<"DIV AB;\n";

        //此处必须先移动A，再移动B，因为移动B时会覆盖A
        asm_str<<this->mov_byte_a_to(result, 0);
    }
    else if((a1->m_bit_width==8)&&(a2->m_bit_width==8) &&(a1->is_signed==0)&&(a2->m_type==DATA_TYPE_J_DATA))
    {
        asm_str<<this->mov_byte_to_b(a2);
        asm_str<<this->mov_byte_to_a(a1);
        asm_str<<"DIV AB;\n";

        //此处必须先移动A，再移动B，因为移动B时会覆盖A
        asm_str<<this->mov_byte_a_to(result, 0);
    }
    else if((a1->m_bit_width==8)&&(a2->m_bit_width==8) &&(a2->is_signed==0)&&(a1->m_type==DATA_TYPE_J_DATA))
    {
        asm_str<<this->mov_byte_to_b(a2);
        asm_str<<this->mov_byte_to_a(a1);
        asm_str<<"DIV AB;\n";

        //此处必须先移动A，再移动B，因为移动B时会覆盖A
        asm_str<<this->mov_byte_a_to(result, 0);
    }

    #if 0
    else     if((a1->m_bit_width==8)&&(a2->m_bit_width==8) &&((a1->is_signed!=0)||(a2->is_signed!=0)))
    {
        asm_str<<this->mov_byte_to_b(a2);
        asm_str<<this->mov_byte_to_a(a1);
        asm_str<<this->lcall("_sys_func_div_byte1_signed");
        //此处必须先移动A，再移动B，因为移动B时会覆盖A
        asm_str<<this->mov_byte_a_to(result, 0);
    }
    #endif
    else
    {
        cerr<<"divA not supported\n";
        std::cout<<"left type:"<< a1->m_type<<". bw"<<a1->m_bit_width<<". s:"<< a1->is_signed <<
                   ". right_type:"<< a2->m_type<<". bw"<<a2->m_bit_width<<". s:"<< a2->is_signed <<"\n";
        asm_str<<";divA not generated ERROR. "<<"\n";
    }


    return asm_str.str();
}

std::string icode_to_c51::modA(c51_addr *a1, c51_addr *a2, c51_addr *result)
{
    std::stringstream asm_str;

    if((a1->m_type==DATA_TYPE_J_DATA)&&
            (a2->m_type==DATA_TYPE_J_DATA))
    {
        //此处直接计算结果
        a1->m_addr %= a2->m_addr;
        asm_str<< this->mov(a1, result);
    }
    else if((a1->m_bit_width==8)&&(a2->m_bit_width==8) &&(a1->is_signed==0)&&(a2->is_signed==0))
    {
        asm_str<<this->mov_byte_to_b(a2);
        asm_str<<this->mov_byte_to_a(a1);
        asm_str<<"DIV AB;\n";

        //此处必须先移动A，再移动B，因为移动B时会覆盖A
        asm_str<<this->mov_byte_b_to(result, 0);
    }
    else if((a1->m_bit_width<=8)&&(a2->m_bit_width<=8) &&(a1->is_signed==0)&&(a2->m_type==DATA_TYPE_J_DATA))
    {
        asm_str<<this->mov_byte_to_b(a2);
        asm_str<<this->mov_byte_to_a(a1);
        asm_str<<"DIV AB;\n";

        //此处必须先移动A，再移动B，因为移动B时会覆盖A
        asm_str<<this->mov_byte_b_to(result, 0);
    }
    else if((a1->m_bit_width<=8)&&(a2->m_bit_width<=8) &&(a2->is_signed==0)&&(a1->m_type==DATA_TYPE_J_DATA))
    {
        asm_str<<this->mov_byte_to_b(a2);
        asm_str<<this->mov_byte_to_a(a1);
        asm_str<<"DIV AB;\n";

        //此处必须先移动A，再移动B，因为移动B时会覆盖A
        asm_str<<this->mov_byte_b_to(result, 0);
    }
    else
    {
        cerr<<"modA not supported\n";
        std::cout<<"left type:"<< a1->m_type<<". bw"<<a1->m_bit_width<<". s:"<< a1->is_signed <<
                   ". right_type:"<< a2->m_type<<". bw"<<a2->m_bit_width<<". s:"<< a2->is_signed <<"\n";
        asm_str<<";modA not generated ERROR. "<<"\n";
    }


    return asm_str.str();

}

void icode_to_c51::shiftOneR(int byte_cnt, std::stringstream &asm_str)
{
    {
        asm_str<<"CLR C;\n";
        if(byte_cnt==1)
        {
            asm_str<<"MOV A, R4;\n";
            asm_str<<"RRC A;\n";
            asm_str<<"MOV R4, A;\n";
        }
        else if(byte_cnt==2)
        {
            asm_str<<"MOV A, R5;\n";
            asm_str<<"RRC A;\n";
            asm_str<<"MOV R5, A;\n";
            asm_str<<"MOV A, R4;\n";
            asm_str<<"RRC A;\n";
            asm_str<<"MOV R4, A;\n";
        }
        else if(byte_cnt==4)
        {
            asm_str<<"MOV A, R7;\n";
            asm_str<<"RRC A;\n";
            asm_str<<"MOV R7, A;\n";
            asm_str<<"MOV A, R6;\n";
            asm_str<<"RRC A;\n";
            asm_str<<"MOV R6, A;\n";
            asm_str<<"MOV A, R5;\n";
            asm_str<<"RRC A;\n";
            asm_str<<"MOV R5, A;\n";
            asm_str<<"MOV A, R4;\n";
            asm_str<<"RRC A;\n";
            asm_str<<"MOV R4, A;\n";
        }
    }
}

void icode_to_c51::shiftOneL(int byte_cnt, std::stringstream &asm_str)
{
    {
        asm_str<<"CLR C;\n";
        if(byte_cnt==1)
        {
            asm_str<<"MOV A, R4;\n";
            asm_str<<"RLC A;\n";
            asm_str<<"MOV R4, A;\n";
        }
        else if(byte_cnt==2)
        {
            asm_str<<"MOV A, R4;\n";
            asm_str<<"RLC A;\n";
            asm_str<<"MOV R4, A;\n";

            asm_str<<"MOV A, R5;\n";
            asm_str<<"RLC A;\n";
            asm_str<<"MOV R5, A;\n";
        }
        else if(byte_cnt==4)
        {
            asm_str<<"MOV A, R4;\n";
            asm_str<<"RLC A;\n";
            asm_str<<"MOV R4, A;\n";

            asm_str<<"MOV A, R5;\n";
            asm_str<<"RLC A;\n";
            asm_str<<"MOV R5, A;\n";

            asm_str<<"MOV A, R6;\n";
            asm_str<<"RLC A;\n";
            asm_str<<"MOV R6, A;\n";

            asm_str<<"MOV A, R7;\n";
            asm_str<<"RLC A;\n";
            asm_str<<"MOV R7, A;\n";
        }
    }
}


void icode_to_c51::rotateShiftOneR(int byte_cnt, std::stringstream &asm_str)
{
    {
        if(byte_cnt==1)
        {
            asm_str<<"MOV A, R4;\n";
            asm_str<<"RR A;\n";
            asm_str<<"MOV R4, A;\n";
        }
        else if(byte_cnt==2)
        {
            //RRC   |b7 b6 b5 b4 b3 b2 b1 b0| --->bitc->bit7 bit0->bitc

            ///先把低字节的bit0放入c。
            asm_str<<"MOV A, R4;\n";
            asm_str<<"RRC A;\n";

            //高字节右移
            asm_str<<"MOV A, R5;\n";
            asm_str<<"RRC A;\n";
            asm_str<<"MOV R5, A;\n";
            //低字节右移
            asm_str<<"MOV A, R4;\n";
            asm_str<<"RRC A;\n";
            asm_str<<"MOV R4, A;\n";
        }
        else if(byte_cnt==4)
        {
            //先把低字节的bit0放入c。 低字节本身不变
            asm_str<<"MOV A, R4;\n";
            asm_str<<"RRC A;\n";

            asm_str<<"MOV A, R7;\n";
            asm_str<<"RRC A;\n";
            asm_str<<"MOV R7, A;\n";
            asm_str<<"MOV A, R6;\n";
            asm_str<<"RRC A;\n";
            asm_str<<"MOV R6, A;\n";
            asm_str<<"MOV A, R5;\n";
            asm_str<<"RRC A;\n";
            asm_str<<"MOV R5, A;\n";
            asm_str<<"MOV A, R4;\n";
            asm_str<<"RRC A;\n";
            asm_str<<"MOV R4, A;\n";
        }
        else
        {
            assert(0);
        }
    }
}

void icode_to_c51::rotateShiftOneL(int byte_cnt, std::stringstream &asm_str)
{
    {
        if(byte_cnt==1)
        {
            asm_str<<"MOV A, R4;\n";
            asm_str<<"RL A;\n";
            asm_str<<"MOV R4, A;\n";
        }
        else if(byte_cnt==2)
        {
            ///先把最字节的bit7放入c。
            /// 最高字节本身数据不变
            asm_str<<"MOV A, R5;\n";
            asm_str<<"RLC A;\n";

            ///每个字节都左移1bit。c转入0
            asm_str<<"MOV A, R4;\n";
            asm_str<<"RLC A;\n";
            asm_str<<"MOV R4, A;\n";

            asm_str<<"MOV A, R5;\n";
            asm_str<<"RLC A;\n";
            asm_str<<"MOV R5, A;\n";
        }
        else if(byte_cnt==4)
        {
            ///先把最字节的bit7放入c。
            /// 最高字节本身数据不变
            asm_str<<"MOV A, R7;\n";
            asm_str<<"RLC A;\n";

            ///每个字节都左移1bit。c转入0
            asm_str<<"MOV A, R4;\n";
            asm_str<<"RLC A;\n";
            asm_str<<"MOV R4, A;\n";

            asm_str<<"MOV A, R5;\n";
            asm_str<<"RLC A;\n";
            asm_str<<"MOV R5, A;\n";

            asm_str<<"MOV A, R6;\n";
            asm_str<<"RLC A;\n";
            asm_str<<"MOV R6, A;\n";

            asm_str<<"MOV A, R7;\n";
            asm_str<<"RLC A;\n";
            asm_str<<"MOV R7, A;\n";
        }
        else
        {
            assert(0);
        }
    }
}



std::string icode_to_c51::shiftR(c51_addr *a1, c51_addr *a2, c51_addr *result)
{
    std::stringstream asm_str;
    if((a1->m_type==DATA_TYPE_J_DATA)&&(a2->m_type==DATA_TYPE_J_DATA))
    {
        c51_addr a3=*a1;
        a3.m_type = DATA_TYPE_J_DATA;
        a3.m_bit_width = a1->m_bit_width;
        a3.m_addr = (a1->m_addr>> a2->m_addr);
        asm_str<<this->mov(&a3, result);
    }
    else if((a1->m_bit_width<=8)&&(a2->m_type==DATA_TYPE_J_DATA))
    {
        if(a2->m_addr>=8)
        {
            asm_str<<"CLR A;\n";
        }
        else
        {
            asm_str<<this->mov_byte_to_a(a1);
            for(int i=0;i<a2->m_addr;++i)
            {
                asm_str<<"CLR C;\n";
                asm_str<<"RRC A;\n";
            }
        }
        asm_str<<this->mov_byte_a_to(result);
    }
    else if(a2->m_type==DATA_TYPE_J_DATA)
    {
        int byte_cnt=a1->m_bit_width/8;
        if(byte_cnt*8<a1->m_bit_width)
        {
            byte_cnt++;
        }

        //数据放寄存器 R4 R5 R6 R7
        asm_str<<this->mov_byte_to_r4(a1, 0);
        asm_str<<this->mov_byte_to_r5(a1, 1);
        asm_str<<this->mov_byte_to_r6(a1, 2);
        asm_str<<this->mov_byte_to_r7(a1, 3);

        for(int i=0;i<a2->m_addr;++i)
        {
            shiftOneR(byte_cnt, asm_str);
        }
        asm_str<<this->mov_byte_r4_to(result, 0);
        asm_str<<this->mov_byte_r5_to(result, 1);
        asm_str<<this->mov_byte_r6_to(result, 2);
        asm_str<<this->mov_byte_r7_to(result, 3);
    }
    else
    {
        //此处需要2层循环？

        int byte_cnt=a1->m_bit_width/8;
        if(byte_cnt*8<a1->m_bit_width)
        {
            byte_cnt++;
        }

        std::string lab_end=get_tmp_label("shiftREND");
        std::string lab0=get_tmp_label("shiftR0");

        ///循环初值


        //数据放寄存器 R4 R5 R6 R7
        asm_str<<this->mov_byte_to_r4(a1, 0);
        if(a1->m_bit_width>8){asm_str<<this->mov_byte_to_r5(a1, 1);}
        if(a1->m_bit_width>16){asm_str<<this->mov_byte_to_r6(a1, 2);}
        if(a1->m_bit_width>24){asm_str<<this->mov_byte_to_r7(a1, 3);}


        asm_str<<this->mov_byte_to_r0(a2);

        asm_str<<"MOV A, R0;\n";
        asm_str<<"JZ "<<lab_end<<";\n";//数值为0，直接退出循环

        ///循环体
        ///


        asm_str<<lab0<<":\n";

        shiftOneR(byte_cnt, asm_str);

        //循环判断语句
        asm_str<<"DJNZ R0, "<<lab0<<";\n";
        asm_str<<lab_end<<":\n";

        asm_str<<this->mov_byte_r4_to(result, 0);
        asm_str<<this->mov_byte_r5_to(result, 1);
        asm_str<<this->mov_byte_r6_to(result, 2);
        asm_str<<this->mov_byte_r7_to(result, 3);
    }
#if 0
    else if(a2->m_bit_width<=16)
    {
        //此处需要2层循环？

        int byte_cnt=a1->m_bit_width/8;
        if(byte_cnt*8<a1->m_bit_width)
        {
            byte_cnt++;
        }

        std::string lab_end=get_tmp_label("shiftREND");
        std::string lab0=get_tmp_label("shiftR0");

        ///循环初值


        //数据放寄存器 R4 R5 R6 R7
        asm_str<<this->mov_byte_to_r4(a1, 0);
        if(a1->m_bit_width>8){asm_str<<this->mov_byte_to_r5(a1, 1);}
        if(a1->m_bit_width>16){asm_str<<this->mov_byte_to_r6(a1, 2);}
        if(a1->m_bit_width>24){asm_str<<this->mov_byte_to_r7(a1, 3);}


        asm_str<<this->mov_byte_to_r0(a2);
        asm_str<<this->mov_byte_to_r1(a2, 1);

        asm_str<<"MOV A, R0;\n";
        asm_str<<"ORL A, R1;\n";
        asm_str<<"JZ "<<lab_end<<";\n";//数值为0，直接退出循环

        ///循环体
        ///


        asm_str<<lab0<<":\n";

        shiftOneR(byte_cnt, asm_str);

        //循环判断语句
        asm_str<<"DJNZ R0, "<<lab0<<";\n";
        asm_str<<"MOV A, R1;\n";
        asm_str<<"JZ "<< lab_end<<ASM_END_STR;
        asm_str<<"DEC R1;\n";
        asm_str<<"MOV R0, #0xff\n"; ///FIXME : 此处是否是少了1次？？？2020.6.30
        asm_str<<"SJMP "<<lab0<<";\n";
        asm_str<<lab_end<<":\n";

        asm_str<<this->mov_byte_r4_to(result, 0);
        asm_str<<this->mov_byte_r5_to(result, 1);
        asm_str<<this->mov_byte_r6_to(result, 2);
        asm_str<<this->mov_byte_r7_to(result, 3);
    }
    else
    {
        assert(0);
    }
#endif
    return asm_str.str();
}

std::string icode_to_c51::shiftL(c51_addr *a1, c51_addr *a2, c51_addr *result)
{
    std::stringstream asm_str;
    if((a1->m_type==DATA_TYPE_J_DATA)&&(a2->m_type==DATA_TYPE_J_DATA))
    {
        c51_addr a3=*a1;
        a3.m_type = DATA_TYPE_J_DATA;
        a3.m_bit_width = a1->m_bit_width;
        a3.m_addr = (a1->m_addr<< a2->m_addr);
        asm_str<<this->mov(&a3, result);
    }
    else if((a1->m_bit_width<=8)&&(a2->m_type==DATA_TYPE_J_DATA))
    {
        if(a2->m_addr>=8)
        {
            asm_str<<"CLR A;\n";
        }
        else
        {
            asm_str<<this->mov_byte_to_a(a1);
            for(int i=0;i<a2->m_addr;++i)
            {
                asm_str<<"CLR C;\n";
                asm_str<<"RLC A;\n";
            }
        }
        asm_str<<this->mov_byte_a_to(result);
    }
    else if(a2->m_type==DATA_TYPE_J_DATA)
    {
        int byte_cnt=a1->m_bit_width/8;
        if(byte_cnt*8<a1->m_bit_width)
        {
            byte_cnt++;
        }

        //数据放寄存器 R4 R5 R6 R7
        asm_str<<this->mov_byte_to_r4(a1, 0);
        asm_str<<this->mov_byte_to_r5(a1, 1);
        asm_str<<this->mov_byte_to_r6(a1, 2);
        asm_str<<this->mov_byte_to_r7(a1, 3);

        for(int i=0;i<a2->m_addr;++i)
        {
            shiftOneL(byte_cnt, asm_str);
        }
        asm_str<<this->mov_byte_r4_to(result, 0);
        asm_str<<this->mov_byte_r5_to(result, 1);
        asm_str<<this->mov_byte_r6_to(result, 2);
        asm_str<<this->mov_byte_r7_to(result, 3);
    }
    else //if(a2->m_bit_width<=16)  bit8=255. a2必须是<64的数值.所以只能是小于8bit位宽
    {
        //此处需要2层循环？

        int byte_cnt=a1->m_bit_width/8;
        if(byte_cnt*8<a1->m_bit_width)
        {
            byte_cnt++;
        }

        std::string lab_end=get_tmp_label("shiftLEND");
        std::string lab0=get_tmp_label("shiftL0");

        ///循环初值

        //数据放寄存器 R4 R5 R6 R7
        asm_str<<this->mov_byte_to_r4(a1, 0);
        if(a1->m_bit_width>8) {asm_str<<this->mov_byte_to_r5(a1, 1);}
        if(a1->m_bit_width>16) {asm_str<<this->mov_byte_to_r6(a1, 2);}
        if(a1->m_bit_width>24) {asm_str<<this->mov_byte_to_r7(a1, 3);}


        asm_str<<this->mov_byte_to_r0(a2);
        asm_str<<this->mov_byte_to_r1(a2, 1);
        asm_str<<"MOV A, R0;\n";
        asm_str<<"JZ "<<lab_end<<";\n";//数值为0，直接退出循环

        ///循环体
        ///

        asm_str<<lab0<<":\n";

        shiftOneL(byte_cnt, asm_str);

        //循环判断语句
        asm_str<<"DJNZ R0, "<<lab0<<";\n";
        asm_str<<lab_end<<":\n";

        asm_str<<this->mov_byte_r4_to(result, 0);
        if(a1->m_bit_width>8)
        {
            asm_str<<this->mov_byte_r5_to(result, 1);
        }
        else
        {
            asm_str<<this->mov_byte_0_to(result, 1);
        }

        if(a1->m_bit_width>16){asm_str<<this->mov_byte_r6_to(result, 2);}
        else {asm_str<<this->mov_byte_0_to(result, 2);}

        if(a1->m_bit_width>24){asm_str<<this->mov_byte_r7_to(result, 3);}
        else {asm_str<<this->mov_byte_0_to(result, 3);}
    }
#if 0
    {

        //此处需要2层循环？

        int byte_cnt=a1->m_bit_width/8;
        if(byte_cnt*8<a1->m_bit_width)
        {
            byte_cnt++;
        }

        std::string lab_end=get_tmp_label("shiftLEND");
        std::string lab0=get_tmp_label("shiftL0");

        ///循环初值

        //数据放寄存器 R4 R5 R6 R7
        asm_str<<this->mov_byte_to_r4(a1, 0);
        if(a1->m_bit_width>8) {asm_str<<this->mov_byte_to_r5(a1, 1);}
        if(a1->m_bit_width>16) {asm_str<<this->mov_byte_to_r6(a1, 2);}
        if(a1->m_bit_width>24) {asm_str<<this->mov_byte_to_r7(a1, 3);}


        asm_str<<this->mov_byte_to_r0(a2);
        asm_str<<this->mov_byte_to_r1(a2, 1);
        asm_str<<"MOV A, R0;\n";
        asm_str<<"ORL A, R1;\n";
        asm_str<<"JZ "<<lab_end<<";\n";//数值为0，直接退出循环


        ///循环体
        ///

        asm_str<<lab0<<":\n";

        shiftOneL(byte_cnt, asm_str);

        //循环判断语句
        asm_str<<"DJNZ R0, "<<lab0<<";\n";
        asm_str<<"MOV A, R1;\n";
        asm_str<<"JZ "<< lab_end<<";\n";
        asm_str<<"DEC R1;\n";
        asm_str<<"MOV R0, #0xff\n"; ///FIXME : 此处是否是少了1次？？？2020.6.30
        asm_str<<"LJMP "<<lab0<<";\n";
        asm_str<<lab_end<<":\n";

        asm_str<<this->mov_byte_r4_to(result, 0);
        if(a1->m_bit_width>8)
        {
            asm_str<<this->mov_byte_r5_to(result, 1);
        }
        else
        {
            asm_str<<this->mov_byte_0_to(result, 1);
        }

        if(a1->m_bit_width>16){asm_str<<this->mov_byte_r6_to(result, 2);}
        else {asm_str<<this->mov_byte_0_to(result, 2);}

        if(a1->m_bit_width>24){asm_str<<this->mov_byte_r7_to(result, 3);}
        else {asm_str<<this->mov_byte_0_to(result, 3);}

    }

    else
    {
        assert(0);
    }
#endif
    return asm_str.str();
}


std::string icode_to_c51::rotate_shiftR(c51_addr *a1, c51_addr *a2, c51_addr *result)
{
    std::stringstream asm_str;

    if(a1->m_bit_width==1)
    {
        //只有1个bit，怎么移动都不变
        this->mov(a1, result);
    }
    else if((a1->m_bit_width<=8)&&(a2->m_type==DATA_TYPE_J_DATA))
    {
        if(a2->m_addr>=8)
        {
            asm_str<<"CLR A;\n";
        }
        else
        {
            asm_str<<this->mov_byte_to_a(a1);
            for(int i=0;i<a2->m_addr;++i)
            {
                asm_str<<"RR A;\n";
            }
        }
        asm_str<<this->mov_byte_a_to(result);
    }
    else if(a2->m_type==DATA_TYPE_J_DATA)
    {
        int byte_cnt=a1->m_bit_width/8;
        if(byte_cnt*8<a1->m_bit_width)
        {
            byte_cnt++;
        }

        //数据放寄存器 R4 R5 R6 R7
        asm_str<<this->mov_byte_to_r4(a1, 0);
        asm_str<<this->mov_byte_to_r5(a1, 1);
        asm_str<<this->mov_byte_to_r6(a1, 2);
        asm_str<<this->mov_byte_to_r7(a1, 3);

        for(int i=0;i<a2->m_addr;++i)
        {
            rotateShiftOneR(byte_cnt, asm_str);
        }
        asm_str<<this->mov_byte_r4_to(result, 0);
        asm_str<<this->mov_byte_r5_to(result, 1);
        asm_str<<this->mov_byte_r6_to(result, 2);
        asm_str<<this->mov_byte_r7_to(result, 3);
    }
    else if(a2->m_bit_width<=16)
    {
        //此处需要2层循环？

        int byte_cnt=a1->m_bit_width/8;
        if(byte_cnt*8<a1->m_bit_width)
        {
            byte_cnt++;
        }

        std::string lab_end=get_tmp_label("shiftREND");
        std::string lab0=get_tmp_label("shiftR0");

        ///循环初值


        //数据放寄存器 R4 R5 R6 R7
        asm_str<<this->mov_byte_to_r4(a1, 0);
        if(a1->m_bit_width>8){asm_str<<this->mov_byte_to_r5(a1, 1);}
        if(a1->m_bit_width>16){asm_str<<this->mov_byte_to_r6(a1, 2);}
        if(a1->m_bit_width>24){asm_str<<this->mov_byte_to_r7(a1, 3);}


        asm_str<<this->mov_byte_to_r0(a2);
        asm_str<<this->mov_byte_to_r1(a2, 1);

        asm_str<<"MOV A, R0;\n";
        asm_str<<"ORL A, R1;\n";
        asm_str<<"JZ "<<lab_end<<";\n";//数值为0，直接退出循环

        ///循环体
        ///


        asm_str<<lab0<<":\n";

        rotateShiftOneR(byte_cnt, asm_str);

        //循环判断语句
        asm_str<<"DJNZ R0, "<<lab0<<";\n";
        asm_str<<"MOV A, R1;\n";
        asm_str<<"JZ "<< lab_end<<";\n";;
        asm_str<<"DEC R1;\n";
        asm_str<<"MOV R0, #0xff\n"; ///此处是否是少了1次？？？2020.6.30--此处已确认正确
        asm_str<<"SJMP "<<lab0<<";\n";
        asm_str<<lab_end<<":\n";

        asm_str<<this->mov_byte_r4_to(result, 0);
        asm_str<<this->mov_byte_r5_to(result, 1);
        asm_str<<this->mov_byte_r6_to(result, 2);
        asm_str<<this->mov_byte_r7_to(result, 3);
    }
    else
    {
        assert(0);
    }

    return asm_str.str();
}

std::string icode_to_c51::rotate_shiftL(c51_addr *a1, c51_addr *a2, c51_addr *result)
{
    std::stringstream asm_str;
    if(a1->m_bit_width==1)
    {
        //只有1个bit，怎么移动都不变
        this->mov(a1, result);
    }
    else if((a1->m_bit_width<=8)&&(a2->m_type==DATA_TYPE_J_DATA))
    {
        if(a2->m_addr>=8)
        {
            asm_str<<"CLR A;\n";
        }
        else
        {
            asm_str<<this->mov_byte_to_a(a1);
            for(int i=0;i<a2->m_addr;++i)
            {
                asm_str<<"RL A;\n";
            }
        }
        asm_str<<this->mov_byte_a_to(result);
    }
    else if(a2->m_type==DATA_TYPE_J_DATA)
    {
        int byte_cnt=a1->m_bit_width/8;
        if(byte_cnt*8<a1->m_bit_width)
        {
            byte_cnt++;
        }

        //数据放寄存器 R4 R5 R6 R7
        asm_str<<this->mov_byte_to_r4(a1, 0);
        asm_str<<this->mov_byte_to_r5(a1, 1);
        asm_str<<this->mov_byte_to_r6(a1, 2);
        asm_str<<this->mov_byte_to_r7(a1, 3);

        for(int i=0;i<a2->m_addr;++i)
        {
            rotateShiftOneL(byte_cnt, asm_str);
        }
        asm_str<<this->mov_byte_r4_to(result, 0);
        asm_str<<this->mov_byte_r5_to(result, 1);
        asm_str<<this->mov_byte_r6_to(result, 2);
        asm_str<<this->mov_byte_r7_to(result, 3);
    }
    else if(a2->m_bit_width<=16)
    {
        //此处需要2层循环？

        int byte_cnt=a1->m_bit_width/8;
        if(byte_cnt*8<a1->m_bit_width)
        {
            byte_cnt++;
        }

        std::string lab_end=get_tmp_label("shiftLEND");
        std::string lab0=get_tmp_label("shiftL0");

        ///循环初值

        //数据放寄存器 R4 R5 R6 R7
        asm_str<<this->mov_byte_to_r4(a1, 0);
        if(a1->m_bit_width>8) {asm_str<<this->mov_byte_to_r5(a1, 1);}
        if(a1->m_bit_width>16) {asm_str<<this->mov_byte_to_r6(a1, 2);}
        if(a1->m_bit_width>24) {asm_str<<this->mov_byte_to_r7(a1, 3);}


        asm_str<<this->mov_byte_to_r0(a2);
        asm_str<<this->mov_byte_to_r1(a2, 1);
        asm_str<<"MOV A, R0;\n";
        asm_str<<"ORL A, R1;\n";
        asm_str<<"JZ "<<lab_end<<";\n";//数值为0，直接退出循环


        ///循环体
        ///

        asm_str<<lab0<<":\n";

        rotateShiftOneL(byte_cnt, asm_str);

        //循环判断语句
        asm_str<<"DJNZ R0, "<<lab0<<";\n";
        asm_str<<"MOV A, R1;\n";
        asm_str<<"JZ "<< lab_end<<";\n";
        asm_str<<"DEC R1;\n";
        asm_str<<"MOV R0, #0xff\n"; ///FIXME : 此处是否是少了1次？？？2020.6.30
        asm_str<<"LJMP "<<lab0<<";\n";
        asm_str<<lab_end<<":\n";

        asm_str<<this->mov_byte_r4_to(result, 0);
        if(a1->m_bit_width>8)
        {
            asm_str<<this->mov_byte_r5_to(result, 1);
        }
        else
        {
            asm_str<<this->mov_byte_0_to(result, 1);
        }

        if(a1->m_bit_width>16){asm_str<<this->mov_byte_r6_to(result, 2);}
        else {asm_str<<this->mov_byte_0_to(result, 2);}

        if(a1->m_bit_width>24){asm_str<<this->mov_byte_r7_to(result, 3);}
        else {asm_str<<this->mov_byte_0_to(result, 3);}
    }
    else
    {
        assert(0);
    }
    return asm_str.str();
}

std::string icode_to_c51::xorA(c51_addr *a1, c51_addr *a2, c51_addr *result)
{
    int bit_width = result->m_bit_width;
    int byte_shift=0;
    std::stringstream asm_str;

    asm_str<< this->mov(a1, result);
    while(bit_width>0)
    {
        int R = m_Rn.get_reg();
        asm_str<< this->mov_byte_to_ri(a2, byte_shift,0,R);
        asm_str<< this->mov_byte_to_a(result, byte_shift);

        asm_str<<"XRL A, R"<< R<<";\n";
        m_Rn.free_reg(R);
        asm_str<<this->mov_byte_a_to(result, byte_shift);

        bit_width-=8;
        byte_shift++;
    }
    return asm_str.str();
}


std::string icode_to_c51::jzA(c51_addr *expr, c51_addr *labA, bool is_jnz)
{
    /// JC	rel	Jump if Carry is set
    /// JNC	rel	Jump if Carry not set
    /// JB	bit,rel	Jump if direct Bit is set
    /// JNB	bit,rel	Jump if direct Bit is Not set
    /// JBC	bit,rel	Jump if direct Bit is set & clear bit
    /// AJMP	addr11	Absolute Jump
    /// LJMP	addr16	Long Jump
    /// SJMP	rel	Short Jump (relative addr)
    /// JMP	@A+DPTR	Jump indirect relative to the DPTR
    /// JZ	rel	Jump if Accumulator is Zero
    /// JNZ	rel	Jump if Accumulator is Not Zero
    /// CJNE	A,direct,rel	Compare direct byte to Acc and Jump if Not Equal
    /// CJNE	A,#data,rel	Compare immediate to Acc and Jump if Not Equal
    /// CJNE	Rn,#data,rel	Compare immediate to register and Jump if Not Equal
    /// CJNE	@Ri,#data,rel	Compare immediate to indirect and Jump if Not Equal
    /// DJNZ	Rn,rel	Decrement register and Jump if Not Zero
    /// DJNZ	direct,rel	Decrement direct byte and Jump if Not Zero

    //ORL	A,direct	OR direct byte to Accumulator
    //ORL	A,@Ri	OR indirect RAM to Accumulator
    //ORL	A,#data	OR immediate data to Accumulator
    //ORL	direct,A	OR Accumulator to direct byte
    //ORL	direct,#data	OR immediate data to direct byte


    std::stringstream asm_str;

    if(expr->m_type==DATA_TYPE_J_DATA)
    {
        if( (is_jnz &&(expr->m_addr)) || ((!is_jnz) &&(!expr->m_addr)))
        {
            //必须跳转
            asm_str<<"sjmp " <<this->m_inline_func_label_prefix << labA->labelA<<";\n";
        }
        else
        {
            //无跳转
            asm_str<<"; jmp with const zero is ignored\n";
        }
    }
    else
    {

        asm_str<<this->mov_byte_to_a(expr);
        int bwidth = expr->m_bit_width;
        int cnti=1;
        bwidth-=8;
        while(bwidth>0)
        {
            asm_str<<this->orl_byte_with_a(expr, cnti);
            cnti++;
            bwidth-=8;
        }

        if(is_jnz)
        {
            asm_str<<"JNZ " <<this->m_inline_func_label_prefix<<  labA->labelA<<";\n";
        }
        else
        {
            asm_str<<"JZ " <<this->m_inline_func_label_prefix<<  labA->labelA<<";\n";
        }
    }
    return asm_str.str();
}


std::string icode_to_c51::is_not_equal(c51_addr *a1, c51_addr *a2, c51_addr *result)
{
    std::stringstream asm_str;


    int cmp_bitwidth = a1->m_bit_width;
    if(a1->m_bit_width!=a2->m_bit_width)
    {

        c51_addr *bigger = a1->m_bit_width>a2->m_bit_width?a1:a2;
        c51_addr *smaller = a1->m_bit_width>a2->m_bit_width?a2:a1;
        cmp_bitwidth = bigger->m_bit_width;
    }

    std::string label_set_one = get_tmp_label("is_not_equal_sz");
    std::string label_end = get_tmp_label("is_not_equal_end");


    if(cmp_bitwidth==1)
    {
        assert(0);
    }
    else
    {
        int byte_cnt=0;
        while(cmp_bitwidth>0)
        {
            asm_str<<this->mov_byte_to_a(a1, byte_cnt);
            asm_str<<xrl_byte_with_a(a2,byte_cnt);
            asm_str<<"JNZ " <<label_set_one<<";\n";
            cmp_bitwidth-=8;
            byte_cnt++;
        }

        ///此处set1
        asm_str<<this->mov_0_to(result);
        asm_str<<"JMP "<<label_end<<";\n";

        ///此处set0
        asm_str<<label_set_one<<":\n";
        asm_str<<this->mov_1_to(result);

        asm_str<<label_end<<":\n";
    }

    return asm_str.str();
}


std::string icode_to_c51::logic_or(c51_addr *a1, c51_addr *a2, c51_addr *result)
{
    std::stringstream asm_str;

    int byte_cnt=0;
    int cmp_bitwidth = a1->m_bit_width;

    std::string label_set_one = get_tmp_label("lgc_or_one");
    std::string label_end = get_tmp_label("lgc_or_end");


    while(cmp_bitwidth>0)
    {
        asm_str<<this->mov_byte_to_a(a1, byte_cnt);
        asm_str<<"JNZ " <<label_set_one<<";\n";
        cmp_bitwidth-=8;
        byte_cnt++;
    }

    byte_cnt=0;
    cmp_bitwidth = a2->m_bit_width;
    while(cmp_bitwidth>0)
    {
        asm_str<<this->mov_byte_to_a(a2, byte_cnt);
        asm_str<<"JNZ " <<label_set_one<<";\n";
        cmp_bitwidth-=8;
        byte_cnt++;
    }

    ///此处set0
    asm_str<<this->mov_0_to(result);
    asm_str<<"JMP "<<label_end<<";\n";

    ///此处set1
    asm_str<<label_set_one<<":\n";
    asm_str<<this->mov_1_to(result);

    asm_str<<label_end<<":\n";

    return asm_str.str();
}


std::string icode_to_c51::logic_and(c51_addr *a1, c51_addr *a2, c51_addr *result)
{
    std::stringstream asm_str;

    int byte_cnt=0;
    int cmp_bitwidth = a1->m_bit_width;

    std::string label_set_one1 = get_tmp_label("lgc_and_one1");
    std::string label_set_one = get_tmp_label("lgc_and_one2");
    std::string label_set_zero = get_tmp_label("lgc_and_zero");
    std::string label_end = get_tmp_label("lgc_and_end");


    while(cmp_bitwidth>0)
    {
        asm_str<<this->mov_byte_to_a(a1, byte_cnt);
        asm_str<<"JNZ " <<label_set_one1<<";\n";
        cmp_bitwidth-=8;
        byte_cnt++;
    }
    asm_str<<"SJMP "<<label_set_zero<<";\n";

    asm_str<<label_set_one1<<":\n";

    byte_cnt=0;
    cmp_bitwidth = a2->m_bit_width;
    while(cmp_bitwidth>0)
    {
        asm_str<<this->mov_byte_to_a(a2, byte_cnt);
        asm_str<<"JNZ " <<label_set_one<<";\n";
        cmp_bitwidth-=8;
        byte_cnt++;
    }

    asm_str<<label_set_zero<<":\n";
    ///此处set0
    asm_str<<this->mov_0_to(result);
    asm_str<<"SJMP "<<label_end<<";\n";

    ///此处set1
    asm_str<<label_set_one<<":\n";
    asm_str<<this->mov_1_to(result);

    asm_str<<label_end<<":\n";

    return asm_str.str();
}

std::string icode_to_c51::logic_not(c51_addr *a1, c51_addr *result)
{
    std::stringstream asm_str;

    std::string label_zero = get_tmp_label("logic_not_zero");
    std::string label_end = get_tmp_label("logic_not_end");

    int cmp_bitwidth = a1->m_bit_width;
    int byte_cnt=0;
    while(cmp_bitwidth>0)
    {
        asm_str<<this->mov_byte_to_a(a1, byte_cnt);
        asm_str<<"JNZ "<<label_zero<<ASM_END_STR;
        cmp_bitwidth-=8;
        byte_cnt++;

    }
    asm_str<<this->mov_1_to(result);
    asm_str<<"SJMP "<<label_end<<ASM_END_STR;
    asm_str<<label_zero<<":\n";
    asm_str<<this->mov_0_to(result);
    asm_str<<label_end<<":"<<ASM_END_STR;

    return asm_str.str();
}

std::string icode_to_c51::is_equal(c51_addr *a1, c51_addr *a2, c51_addr *result)
{
    std::stringstream asm_str;

    /// 判断两个数是否相等。
    /// 先看位宽，如果位宽不一致，看大的位宽的大出部分是否是0，如果不是0，则不想等
    /// 然后看位宽一致的部分，通过 xor orl 放到结果8bit寄存器中
    /// 最后 如果结果位宽8bit，则直接mov。如果结果位宽1bit，则需要？？？
    ///

    int cmp_bitwidth = a1->m_bit_width;
    if(a1->m_bit_width!=a2->m_bit_width)
    {
        c51_addr *bigger = a1->m_bit_width>a2->m_bit_width?a1:a2;
        c51_addr *smaller = a1->m_bit_width>a2->m_bit_width?a2:a1;
        cmp_bitwidth = bigger->m_bit_width;
    }

    std::string label_set_zero = get_tmp_label("is_equal_sz");
    std::string label_end = get_tmp_label("is_equal_end");


    if(cmp_bitwidth==1)
    {
        assert(0);
    }
    else
    {
        int byte_cnt=0;
        while(cmp_bitwidth>0)
        {
        ///--已修正： 此处可能会导致a被占用，而无法实现xrl_byte_with_a函数功能
#if 0
            int mR = m_Rn.get_reg();
            asm_str<<this->mov_byte_to_ri(a1, byte_cnt,0, mR);
            asm_str<<xrl_byte_with_ri(a2,byte_cnt, mR);
            m_Rn.free_reg(mR);
#else
            asm_str<<this->mov_byte_to_a(a1, byte_cnt);
            asm_str<<xrl_byte_with_a(a2,byte_cnt);
#endif
            asm_str<<"JNZ " <<label_set_zero<<";\n";
            cmp_bitwidth-=8;
            byte_cnt++;
        }

        ///此处set1
        asm_str<<this->mov_1_to(result);
        asm_str<<"JMP "<<label_end<<";\n";

        ///此处set0
        asm_str<<label_set_zero<<":\n";
        asm_str<<this->mov_0_to(result);

        asm_str<<label_end<<":\n";
    }

    return asm_str.str();
}

std::string icode_to_c51::orl_byte_with_a(c51_addr *a1, int addr_shift)
{
    std::stringstream asm_str;

    //ORL	A,direct	OR direct byte to Accumulator
    //ORL	A,@Ri	OR indirect RAM to Accumulator
    //ORL	A,#data	OR immediate data to Accumulator
    //ORL	direct,A	OR Accumulator to direct byte
    //ORL	direct,#data	OR immediate data to direct byte

    if(a1->m_type==DATA_TYPE_DIRECT)
    {
        asm_str<<"ORL A, 0x"<<std::hex<<a1->m_addr+addr_shift<<";\n"  ;
    }
    else if(a1->m_type==DATA_TYPE_IDATA)
    {
        int mR = m_Rn.get_reg(0,1);
        asm_str<<"MOV R"<<mR <<", #0x"<<std::hex<<a1->m_addr<<";\n";
        asm_str<<"ORL A, @R"<< mR <<";\n";
        m_Rn.free_reg(mR);
    }
    else if(a1->m_type==DATA_TYPE_J_DATA)
    {
        asm_str<<"ORL A, #0x"<<std::hex<<(0xff&((((0x000000ff<<(addr_shift*8)))&a1->m_addr)>>(addr_shift*8)))<<";\n";
    }
    else if(a1->m_type==DATA_TYPE_XDATA)
    {
        int mR = m_Rn.get_reg();
        asm_str<<this->mov_byte_to_ri(a1, addr_shift,0, mR);
        asm_str<<"ORL A, R"<< mR <<";\n";
        m_Rn.free_reg(mR);
    }
    else
    {
        assert(0);
    }
    return asm_str.str();
}


std::string icode_to_c51::xrl_byte_with_ri(c51_addr *a1, int addr_shift, int Rn)
{

    std::stringstream asm_str;

    //XRL	A,Rn	Exclusive-OR register to Accumulator
    //XRL	A,direct	Exclusive-OR direct byte to Accumulator
    //XRL	A,@Ri	Exclusive-OR indirect RAM to Accumulator
    //XRL	A,#data	Exclusive-OR immediate data to Accumulator
    //XRL	direct,A	Exclusive-OR Accumulator to direct byte
    //XRL	direct,#data	Exclusive-OR immediate data to direct byte

    asm_str<<this->mov_byte_to_a(a1, addr_shift);
    asm_str<<"XRL A, R"<<Rn<<";\n";

    return asm_str.str();
}

std::string icode_to_c51::xrl_byte_with_a(c51_addr *a1, int addr_shift)
{

    std::stringstream asm_str;

    //XRL	A,Rn	Exclusive-OR register to Accumulator
    //XRL	A,direct	Exclusive-OR direct byte to Accumulator
    //XRL	A,@Ri	Exclusive-OR indirect RAM to Accumulator
    //XRL	A,#data	Exclusive-OR immediate data to Accumulator
    //XRL	direct,A	Exclusive-OR Accumulator to direct byte
    //XRL	direct,#data	Exclusive-OR immediate data to direct byte


    if(a1->m_type==DATA_TYPE_DIRECT)
    {
        asm_str<<"XRL A, 0x"<<std::hex<<a1->m_addr+addr_shift<<";\n"  ;
    }
    else if(a1->m_type==DATA_TYPE_IDATA)
    {
        int mR = m_Rn.get_reg(0,1);
        asm_str<<"MOV R"<<mR <<", #0x"<<std::hex<<a1->m_addr<<";\n";
        asm_str<<"XRL A, @R"<< mR <<";\n";
        m_Rn.free_reg(mR);
    }
    else if(a1->m_type==DATA_TYPE_J_DATA)
    {
        unsigned long data1=(((0x000000ff<<(addr_shift*8)))&a1->m_addr);
        asm_str<<"XRL A, #0x"<<std::hex<<(0xff& ( data1>>(addr_shift*8)))<<";\n";
    }
    else if(a1->m_type==DATA_TYPE_J_DATA_F)
    {
        unsigned long data1=(((0x000000ff<<(addr_shift*8)))& (*(unsigned long*)(&a1->fnum)));
        asm_str<<"XRL A, #0x"<<std::hex<<(0xff& ( data1>>(addr_shift*8)))<<";\n";
    }

    else// if(a1->m_type==DATA_TYPE_XDATA)
    {
        /// 2021.1.30已修正
        /// 此处代码不对，因为A已经被占用，不能在调用mov_byte_to_ri。所以此处应该先把a放到ri中，再转移到ri
        ///
        assert(0);
        int mR = m_Rn.get_reg();
        asm_str<<"MOV R"<<mR<<", A;\n";
        asm_str<<this->mov_byte_to_a(a1, addr_shift);
        asm_str<<"XRL A, R"<< mR <<";\n";
        m_Rn.free_reg(mR);
    }
#if 0
    else
    {
        assert(0);
    }
#endif
    return asm_str.str();
}



std::string icode_to_c51::incA(c51_addr * varA)
{
    ///
    /// INC A;
    /// INC DIR;
    /// INC @Ri;
    /// INC Rn;
    ///
    static int decALabel_num=0;

    static int label_used = 0;
    std::stringstream asm_str;
    //assert(varA->m_type==DATA_TYPE_DIRECT);

    if(varA->m_type==DATA_TYPE_DIRECT)
    {
        std::string tmp_label;
        tmp_label=get_tmp_label("incA");

        if(varA->m_bit_width>=8)
        {

            asm_str<<"INC 0x"<<std::hex<<varA->m_addr<<";\n";

        }
        if(varA->m_bit_width>=16)
        {
            asm_str<<"MOV A, 0x"<<std::hex<<varA->m_addr<<";\n";

            label_used=1;
            asm_str<<"JNZ "<< tmp_label <<";\n";
            asm_str<<"INC 0x"<<std::hex<<varA->m_addr+1<<";\n";
        }
        if(varA->m_bit_width>=24)
        {
            asm_str<<"MOV A, 0x"<<std::hex<<varA->m_addr+1<<";\n";

            label_used=1;
            asm_str<<"JNZ "<< tmp_label<<";\n";
            asm_str<<"INC 0x"<<std::hex<<varA->m_addr+2<<";\n";
        }
        if(varA->m_bit_width>=32)
        {
            asm_str<<"MOV A, 0x"<<std::hex<<varA->m_addr+2<<";\n";
            label_used=1;
            asm_str<<"JNZ "<< tmp_label<<";\n";
            asm_str<<"INC 0x"<<std::hex<<varA->m_addr+3<<";\n";
            //asm_str<<"MOV A, 0x"<<std::hex<<varA->m_addr+3<<";\n";
        }

        if(label_used)
        {
            asm_str<<tmp_label<<":\n";
            decALabel_num++;
        }
    }
    else
    {
        int bitwidth = varA->m_bit_width;
        int byte_cnt=0;
        std::string tmp_label;
        tmp_label=get_tmp_label("incA");

        while(bitwidth>0)
        {
            asm_str<<this->mov_byte_to_a(varA, byte_cnt);
            asm_str<<"INC A;\n";
            asm_str<<this->mov_byte_a_to(varA, byte_cnt);
            asm_str<<"JNZ "<< tmp_label<<";\n";
            byte_cnt++;
            bitwidth-=8;
        }
        asm_str<<tmp_label<<":\n";
    }

    return asm_str.str();
    cerr<<"ERROR: unsupported inc xdata?\n";
    assert(0);

}

std::string icode_to_c51::decA(c51_addr *varA)
{
    /// DEC A;
    /// DEC dir;
    /// DEC @Ri;
    /// DEC Rn;
    ///
    ///
    ///
    static int decALabel_num=0;

    static int label_used = 0;
    std::stringstream asm_str;
    assert(varA->m_type==DATA_TYPE_DIRECT);

    if(varA->m_type==DATA_TYPE_DIRECT)
    {
        std::string tmp_label;
        tmp_label=get_tmp_label("decA");

        if(varA->m_bit_width>=8)
        {
            asm_str<<"MOV A, 0x"<<std::hex<<varA->m_addr<<";\n";
            asm_str<<"DEC 0x"<<std::hex<<varA->m_addr<<";\n";
        }
        if(varA->m_bit_width>=16)
        {
            label_used=1;
            asm_str<<"JNZ "<< tmp_label <<";\n";
            asm_str<<"MOV A, 0x"<<std::hex<<varA->m_addr+1<<";\n";
            asm_str<<"DEC 0x"<<std::hex<<varA->m_addr+1<<";\n";
        }
        if(varA->m_bit_width>=24)
        {
            label_used=1;
            asm_str<<"JNZ "<< tmp_label<<";\n";
            asm_str<<"MOV A, 0x"<<std::hex<<varA->m_addr+2<<";\n";
            asm_str<<"DEC 0x"<<std::hex<<varA->m_addr+2<<";\n";
        }
        if(varA->m_bit_width>=32)
        {
            label_used=1;
            asm_str<<"JNZ "<< tmp_label<<";\n";
            asm_str<<"MOV A, 0x"<<std::hex<<varA->m_addr+3<<";\n";
            asm_str<<"DEC 0x"<<std::hex<<varA->m_addr+3<<";\n";
        }

        if(label_used)
        {
            asm_str<<tmp_label<<":\n";
            decALabel_num++;
        }
    }
    else
    {
        int bitwidth = varA->m_bit_width;
        int byte_cnt=0;
        std::string tmp_label;
        tmp_label=get_tmp_label("decA");

        while(bitwidth>0)
        {
            int mR = this->m_Rn.get_reg();
            asm_str<<this->mov_byte_to_a(varA, byte_cnt);
            asm_str<<"MOV R"<<mR<<", A;\n";
            asm_str<<"DEC R"<<mR<<"\n";
            asm_str<<this->mov_byte_ri_to(varA, byte_cnt,0,mR);

            asm_str<<"MOV A, R"<<mR<<";\n";
            asm_str<<"JNZ "<< tmp_label<<";\n";
            m_Rn.free_reg(mR);
            byte_cnt++;
            bitwidth-=8;
        }
        asm_str<<tmp_label<<":\n";
    }

    return asm_str.str();
}



