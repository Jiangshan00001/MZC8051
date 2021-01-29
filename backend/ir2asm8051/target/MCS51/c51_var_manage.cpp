#include <assert.h>
#include <iostream>
#include <sstream>
#include "c51_addr.h"

#include "c51_var_manage.h"
#include "icode.h"
#include "icode_to_c51.h"
#include "mylog.h"
#include "icode_manage.h"


using mylog::cout;
using mylog::cerr;
using mylog::csummary;


c51_var_manage::c51_var_manage(icodes *mcontext)
{

    m_context = mcontext;


    ///TODO: 如果有人使用了using 寄存器组，则起始地址就不是8了
    m_low_data.init_mem(8, 0x80, 1);//0-128
    m_idata.init_mem(0x80, 0x100, 1);//128-256
    m_xdata.init_mem(0, 0x10000,1);//0-0x10000

    m_const_label_cnt = 0;
}

int c51_var_manage::print_usage()
{
    csummary<<"data memory used:"<< this->m_low_data.usage() <<"+"<<8<<  "\n";
    csummary<<"idata memory used:"<< this->m_idata.usage() <<"\n";
    csummary<<"xdata memory used:"<< this->m_xdata.usage() <<"\n";

    return 0;
}

std::string c51_var_manage::new_const_label()
{
    std::stringstream strA;
    strA<<"__const_label_"<<m_const_label_cnt;
    m_const_label_cnt++;
    return strA.str();
}


int c51_var_manage::process(std::vector<icode *> &ic)
{
    for(unsigned i=0;i<ic.size();++i)
    {
        process_one(ic[i]);
    }

    print_usage();

    return 0;
}


c51_addr* c51_var_manage::alloc_variable(icode* ic)
{
    if(ic==NULL){return NULL;}

    if(ic->target)
    {
        return NULL;
    }

    if(ic->is_array)
    {
        return alloc_variable_array(ic);
    }
    if(ic->is_ptr)
    {
        return alloc_variable_ptr(ic);
    }

    return alloc_variable_not_ptr(ic);
}

c51_addr *c51_var_manage::alloc_variable_not_ptr(icode *ic)
{

    c51_addr* ad = NULL;

    ad = new c51_addr();
    ic->target = ad;

    ad->is_float32 = ic->is_float32;
    ad->is_signed = ic->is_signed;


    if(ic->m_bit_width==0)
    {
        //should not alloc memory for void var
        ad->m_type=DATA_TYPE_DIRECT;
        ad->m_addr= UNKNOWN_ADDR;
        ad->m_bit_width = 0;
        return ad;
    }



    if((ic->is_sfr))
    {
        //sfr
        ad->m_type = DATA_TYPE_DIRECT;
        ad->m_addr = UNKNOWN_ADDR;
        ad->m_bit_width = 8;
        return ad;
    }
    if((ic->is_sfr16))
    {
        //sfr16
        ad->m_type = DATA_TYPE_DIRECT;
        ad->m_addr = UNKNOWN_ADDR;
        ad->m_bit_width = 16;
        return ad;
    }

    if((ic->is_sfr32))
    {
        //sfr32
        ad->m_type = DATA_TYPE_DIRECT;
        ad->m_addr = UNKNOWN_ADDR;
        ad->m_bit_width = 32;
        return ad;
    }
    if((ic->is_sbit))
    {
        ad->m_type = DATA_TYPE_BIT;
        ad->m_addr = UNKNOWN_ADDR;
        ad->m_bit_width = 1;
        return ad;
    }

    if((ic->is_code))
    {
        ad->m_type = DATA_TYPE_CODE;
        ad->m_addr = UNKNOWN_ADDR;
        ad->labelA = new_const_label();

        if(ad->m_bit_width<8)
        {
            ad->m_bit_width=8;
        }
        return ad;
    }


    if((ic->is_register)&& (ic->m_register_desc.size()>0))
    {
        ad->m_bit_width = ic->m_bit_width;

        if(ic->m_register_desc[0]=='R')
        {
            int reg_index = ic->m_register_desc[1];
            reg_index  -= '0';
            if((reg_index<0)||(reg_index>7))
            {
                //错误
                reg_index = 0;
                assert(0);
            }
            //寄存器
            ad->m_type = DATA_TYPE_RN;
            ad->m_addr = reg_index;
        }
        else if(ic->m_register_desc[0]=='A')\
        {

            //寄存器ACC
            ad->m_type = DATA_TYPE_DIRECT;
            ad->m_addr = REG_ADDR_ACC;
        }
        else
        {
            cerr<<"m_register_desc: "<<ic->m_register_desc<<"\n";

            assert(0);
        }

        return ad;
    }





    ///------------------------------------------
    ///非特殊类型存储器。
    /// 申请普通的存储器空间

    ad->m_addr = UNKNOWN_ADDR;
    ad->m_bit_width = ic->m_bit_width;
    alloc_memory(ad, ic);
    ///------------------------------------------

    /// 添加调试信息
    m_sym[ic->name] = *ad;

    ///------------------------------------------

    /// 对于结构体或共用体，是在申请的空间中，添加不同的变量访问
    if(ic->is_struct)
    {
        //如果是结构体，
        int mbitwidth = 0;
        for(unsigned i=0;i<ic->m_struct_type.size();++i)
        {
            c51_addr* adi = NULL;
            adi = new c51_addr();
            ic->m_struct_type[i]->target = adi;

            adi->is_signed = ic->m_struct_type[i]->is_signed;
            adi->is_float32 = ic->m_struct_type[i]->is_float32;

            adi->m_bit_width = ic->m_struct_type[i]->m_bit_width;

            adi->m_addr =  ad->m_addr + mbitwidth/8;

            adi->m_type = ad->m_type;
            //FIXME 此处label无法使用。因为结构多个字节，每个字节的label需要单独的？
            adi->labelA = ad->labelA;

            mbitwidth += ic->m_struct_type[i]->m_bit_width;

        }
    }

    if(ic->is_union)
    {
        for(unsigned i=0;i<ic->m_struct_type.size();++i)
        {
            c51_addr* adi = NULL;
            adi = new c51_addr();
            ic->m_struct_type[i]->target = adi;

            adi->is_signed = ic->m_struct_type[i]->is_signed;
            adi->is_float32 = ic->m_struct_type[i]->is_float32;

            adi->m_bit_width = ic->m_struct_type[i]->m_bit_width;
            adi->m_addr =  ad->m_addr;
            adi->m_type = ad->m_type;
            adi->labelA = ad->labelA;
        }
    }

    return ad;
}

c51_addr *c51_var_manage::alloc_variable_array(icode *ic)
{
    ///数组。 面值位宽是一个指针宽度
    ///
    c51_addr* ad = NULL;

    ad = new c51_addr();
    ic->target = ad;

    ad->ptr_target = new c51_addr();
    ad->ptr_target->is_array = ic->is_array;
    ad->ptr_target->m_bit_width = ic->get_array_bit_width();
    ad->ptr_target->m_bit_width_array_comp = ic->m_bit_width;

    alloc_memory(ad->ptr_target, ic);

    /// 添加调试信息
    m_sym[ic->name] = *(ad->ptr_target);


    ad->is_array = ic->is_array;
    ad->m_bit_width = VAR_PTR_BIT_WIDTH;

    if(ad->ptr_target->m_type==DATA_TYPE_CODE)
    {
        ad->m_type = DATA_TYPE_J_DATA_LABEL;
        ad->labelA = ad->ptr_target->labelA;
    }
    else if((ad->ptr_target->m_type==DATA_TYPE_DIRECT) ||
            (ad->ptr_target->m_type==DATA_TYPE_XDATA) ||
            (ad->ptr_target->m_type==DATA_TYPE_IDATA) ||
            (ad->ptr_target->m_type==DATA_TYPE_PDATA)
            )
    {
        ad->m_type = DATA_TYPE_J_DATA;
        ad->m_addr =  ((ad->ptr_target->m_type)<<16) | (ad->ptr_target->m_addr&0xffff);
    }
    else
    {
        assert(0);
    }

    return ad;
}

c51_addr *c51_var_manage::alloc_variable_ptr(icode *ic)
{
    ///指针宽度肯定是常量。
    /// 但是指针指向的数据宽度，保存在哪里？
    c51_addr* ad = NULL;

    ad = new_c51_addr();
    ic->target = ad;

    ad->m_bit_width = VAR_PTR_BIT_WIDTH;
    ad->is_ptr = ic->is_ptr;

    alloc_memory(ad, ic);

    /// 添加调试信息
    m_sym[ic->name] = *(ad);
#if 1
    ///此处无用，因为指向的类型信息在icode处有用，在2c51处已经不需要了？？？？？
    /// 2020.8.24 songjiangshan

    ad->ptr_target = new_c51_addr(ic);
    ad->ptr_target->m_bit_width = ic->m_bit_width;
#endif

    return ad;
}

c51_addr *c51_var_manage::alloc_variable_str(icode *ic)
{
    c51_addr* ad = NULL;

    ad = new_c51_addr();
    ic->target = ad;

    ad->ptr_target = new_c51_addr();
    ad->ptr_target->is_array = 1;
    ad->ptr_target->m_bit_width = (ic->name.size()+1)*8;
    ad->ptr_target->m_bit_width_array_comp = 8;

    ///--------------------
    ///FIXME 此处是补丁
    /// 将str放入code区
    ///--------------------

    ic->is_code = 1;
    ///--------------------
    ///--------------------

    alloc_memory(ad->ptr_target, ic);

    ad->is_array = 1;
    ad->m_bit_width = VAR_PTR_BIT_WIDTH;

    if(ad->ptr_target->m_type==DATA_TYPE_CODE)
    {
        ad->m_type = DATA_TYPE_J_DATA_LABEL;
        ad->labelA = ad->ptr_target->labelA;
    }
    else if((ad->ptr_target->m_type==DATA_TYPE_DIRECT) ||
            (ad->ptr_target->m_type==DATA_TYPE_XDATA) ||
            (ad->ptr_target->m_type==DATA_TYPE_IDATA) ||
            (ad->ptr_target->m_type==DATA_TYPE_PDATA)
            )
    {
        ad->m_type = DATA_TYPE_J_DATA;
        ad->m_addr =  ((ad->ptr_target->m_type)<<16) | (ad->ptr_target->m_addr&0xffff);
    }
    else
    {
        assert(0);
    }

    return ad;
}

void c51_var_manage::alloc_xdata(c51_addr *ad, icode *ic)
{
    ///xdata
    ///
    //data已经使用完了
    //或者带有xdata 标记

    ad->m_type = DATA_TYPE_XDATA;

    long addr=-1;
    int byte_cnt = ad->m_bit_width/8;

    this->m_xdata.set_stack_num(ic->m_var_scope);
    bool alloc_success = this->m_xdata.try_get_mem(addr, byte_cnt);

    if(!alloc_success)
    {
        cerr<<"ERROR: data alloc out of memory\n";
        print_usage();
        assert(0);
    }
    ad->m_addr = addr;
}

bool c51_var_manage::alloc_low_data(c51_addr *ad, icode *ic)
{

    int byte_cnt = ad->m_bit_width/8;
    long addr=-1;

    this->m_low_data.set_stack_num(ic->m_var_scope);
    bool alloc_success = this->m_low_data.try_get_mem(addr, byte_cnt);
    if(!alloc_success)
    {
        return alloc_success;
    }

    ad->m_type = DATA_TYPE_DIRECT;
    ad->m_addr = addr;

    return alloc_success;
}

int c51_var_manage::alloc_memory(c51_addr *ad, icode *ic)
{

    if(((ic->is_code)||(ic->is_const))||
            ((ic->is_array )&&(ic->m_in_ptr_type->is_code))||
            ((ic->is_array )&&(ic->m_in_ptr_type->is_const))
            )
    {
        //code代码区，不需要实际申请空间

        ad->m_type = DATA_TYPE_CODE;
        ad->labelA = new_const_label();
        ad->m_bit_width = ic->m_bit_width;
        return 0;
    }


    {
        //不是特殊寄存器，也不是常量JDATA
        //需要分配到data 或者xdata中

        ///===================
        ///
        if(ad->m_bit_width<8)
        {
            ad->m_bit_width=8;
        }

        ///===================

        if(ic->is_xdata)
        {
            alloc_xdata(ad, ic);
            return 0;
        }
        else if(alloc_low_data(ad, ic))
        {
            return 0;
        }
        else
        {
            alloc_xdata(ad, ic);
            return 0;
        }
    }
    return 0;
}

int c51_var_manage::parse_ptr(icode *ic)
{
    /// ic的类型是DEF_VAR_IN
    /// ic->result的类型是SYMBOL_REF
    /// ic->result->result的类型是DEF_VAR
    /// ic->result->result->m_in_ptr_type 是指针指向的类型
    ///


    /// 此处是读写指针指向的数值
    ///
    ///
    process_one(ic->result);
    //读写内部数据
    ic->target = new_c51_addr(ic);
    ic->target->m_type = DATA_TYPE_IN_GENRIC_PTR;

    if(ic->is_ptr+ic->result->is_ptr + ic->result->is_array>0)
    {
        ///仍然是读写指针
        /// 读出3个字节，作为指针变量内容
        /// int a;
        /// int *b;
        /// int **c;
        /// b = &a;
        /// c= &b;
        /// (*c) <---?
        ///
        ic->target->m_bit_width = 3*8;// FIXME 此处是指针的长度 this->m_context->;
        ic->target->is_signed = 0;
        ic->target->is_float32 = 0;
        ic->target->ptr_target = ic->result->target;
        ic->target->is_ptr = ic->is_ptr;

    }
    else
    {
        /// 读写的数据宽度
        /// 指针的数据类型，数据宽度，float，sign等标记
        ///
        ///////icode *type_ic = this->m_context->get_def_var( ic)->result->m_in_ptr_type;
        //2020.12.7 error: char*a; *a=3;
        icode *type_ic = this->m_context->get_def_var( ic)->result->m_in_ptr_type;
        ic->target->m_bit_width = type_ic->m_bit_width;
        ic->target->is_signed = type_ic->is_signed;
        ic->target->is_float32 = type_ic->is_float32;
        ic->target->ptr_target = ic->result->target;
    }
    return 0;
}

c51_addr *c51_var_manage::new_c51_addr()
{
    return new c51_addr();
}

c51_addr *c51_var_manage::new_c51_addr(icode *ic)
{
    c51_addr * ret = new c51_addr();

    if(ic->is_signed)ret->is_signed=1;
    if(ic->is_float32)ret->is_float32 = 1;
    ret->m_bit_width = ic->m_bit_width;

    return ret;
}

int c51_var_manage::process_one(icode *ic)
{
    if(ic==NULL)return 0;

    switch(ic->m_type)
    {
    case ICODE_TYPE_DEF_VAR_IN_VAR:
    case ICODE_TYPE_DEF_VAR_IN_VAR_TMP:
    {
        process_one(ic->result);
        if(ic->is_array)
        {
            /// 已经将所有对array的引用，转换为对ptr的引用？？？
            assert(0);
        }
        else if(ic->is_ptr)
        {
            parse_ptr(ic);
        }
        else {
            assert(0);
        }

    }
        break;
    case ICODE_TYPE_DEF_VAR:/*变量定义*/
    case ICODE_TYPE_DEF_VAR_TMP:/*中间临时变量*/
    case ICODE_TYPE_FUNC_RET_TYPE:
    case ICODE_TYPE_FUNC_DEF_ARG:


        //申请变量空间
        this->alloc_variable(ic);
        break;
    case ICODE_TYPE_I_CONST:
        //常量
    {
        ic->target = new c51_addr();

        ic->target->m_type =DATA_TYPE_J_DATA;
        ic->const_refresh_width();
        ic->target->m_bit_width = ic->m_bit_width;
        ic->target->is_signed = ic->is_signed;
        ///此处后期想废弃，JDATA时，只使用num变量，
        /// 现在num 和 m_addr 的数值是一样的
        ic->target->m_addr = ic->num;
        ic->target->num = ic->num;
    }
        break;
    case ICODE_TYPE_F_CONST:
        //常量
    {
        ic->target = new c51_addr();

        ic->target->m_type =DATA_TYPE_J_DATA_F;
        ic->target->m_bit_width = ic->m_bit_width;
        ic->target->fnum = ic->fnum;
        ic->target->is_float32 = 1;
    }
        break;


    case ICODE_TYPE_LABELED_BLOCK_START_REF://代表result中的icode的起始位置
    {
        c51_addr * ad = new c51_addr();
        ad->m_type=DATA_TYPE_CODE;
        ad->labelA = ic->result->get_block_start_label();
        ic->target = ad;
    }
        break;
    case ICODE_TYPE_LABELED_BLOCK_END_REF:
    {
        c51_addr * ad = new c51_addr();
        ad->m_type=DATA_TYPE_CODE;
        ad->labelA = ic->result->get_block_end_label();
        ic->target = ad;
    }
        break;

    case ICODE_TYPE_CONST_STRING:
    {
        ///字符串和常亮列表，需要单独在代码中申请空间，放入数据段。
        /// 数据段单独存放
        ///
        alloc_variable_str(ic);
    }
        break;
    case ICODE_TYPE_CONST_LIST:
    {

        c51_addr * ad = new c51_addr();
        ad->m_type=DATA_TYPE_CODE;
        ad->labelA = new_const_label();
        ad->m_bit_width=ic->m_bit_width;
        ad->m_bit_width_array_comp = 8;//元素的bitwidth不用关心，因为最后都转换为8bit的数字
        ic->target = ad;
    }
        break;



    case ICODE_TYPE_SYMBOL_REF:
    {

        if(ic->is_array)
        {
            /// 已经将所有对array的引用，转换为对ptr的引用？？？
            assert(0);
        }
        else if(ic->is_ptr)
        {
            parse_ptr(ic);
        }
        else
        {
            /// 非指针和数组的ref，和数值是一样的
            process_one(ic->result);
            ic->target = ic->result->target;
        }
    }
        break;




    case ICODE_TYPE_FUNC:
    case ICODE_TYPE_CALL:
    {
        for(unsigned i=0;i<ic->sub_icode.size();++i)
        {
            process_one(ic->sub_icode[i]);
        }
    }
        break;

    case ICODE_TYPE_EXP_OP:
        process_one(ic->left);
        process_one(ic->right);
        process_one(ic->result);
        break;
    case ICODE_TYPE_FUNC_RETURN:
        break;

    case ICODE_TYPE_SCOPE:
    case ICODE_TYPE_BLOCK://只是将多个icode顺序组合在一起
    case  ICODE_TYPE_LABELED_BLOCK:// 此处是一个特殊的block，前后可以有2个标签，用于跳转语句
    {
        this->m_low_data.stack_enter(ic->m_icode_number);
        this->m_idata.stack_enter(ic->m_icode_number);
        this->m_xdata.stack_enter(ic->m_icode_number);
        for(unsigned i=0;i<ic->sub_icode.size();++i)
        {
            process_one(ic->sub_icode[i]);
        }

        this->m_low_data.stack_leave(ic->m_icode_number);
        this->m_idata.stack_leave(ic->m_icode_number);
        this->m_xdata.stack_leave(ic->m_icode_number);
    }
    break;

    case ICODE_TYPE_ASM:
        break;

    case ICODE_TYPE_UNKNOWN:
    default:
        cerr<<"c51_var_manage: unknown type:"<<ic->m_type<<". "<< ic->to_str()<<"\n";
        break;
    }
    return 0;
}


