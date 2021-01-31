#include <assert.h>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stack>
#include <algorithm>
#include <fstream>
#include <time.h>

#include <sstream>
#include "icode_to_c51.h"
#include "icode.h"
#include "icodes.h"
#include "c51_var_manage.h"
#include "mylog.h"
#include "icode_collect_str.h"


using mylog::cerr;
using mylog::cout;



icode_to_c51::icode_to_c51(icodes *mpcompi)
{
    this->pcompi = pcompi;

    // int vector init
    interrupt_addr[-1] = 0x00;
    for(int i=0;i<35;++i)
    {
        if(i%2==0)
        {
            interrupt_addr[i] = 0x03 + i/2 * 16;
        }
        else
        {
            interrupt_addr[i] = 0x0B + ((int)(i/2))*16;
        }
    }


    //从大到小的顺序，保证了申请空间从7开始
    std::vector<int> reg_num={7,6,5,4,3,2,1,0};
    m_Rn.init_reg(reg_num);

    load_sys_func_def();
}

icode_to_c51::~icode_to_c51()
{

}


std::string icode_to_c51::const_to_db(std::vector<class icode *>& ic)
{
    std::stringstream asm_str;

    for(unsigned i=0;i<ic.size();++i)
    {
        icode *curr_ic = ic[i];
        if(curr_ic->m_type==ICODE_TYPE_CONST_LIST)
        {
            asm_str<<curr_ic->target->labelA<<":\n";
            asm_str<<"DB ";
            for(unsigned db_index=0;db_index<curr_ic->sub_icode.size();++db_index)
            {
                int bit_cnt=curr_ic->sub_icode[db_index]->m_bit_width;
                int byte_cnt=0;
                while(bit_cnt>0)
                {
                    asm_str<<"0x"<< std::hex<<(0xff& ( ( (0x000000ff<<(byte_cnt*8)) &curr_ic->sub_icode[db_index]->num)>>(byte_cnt*8) ) )  <<" ";
                    bit_cnt-=8;
                    byte_cnt++;
                }
            }
            asm_str<<";\n";
        }
        else if(curr_ic->m_type==ICODE_TYPE_CONST_STRING)
        {
            asm_str<<curr_ic->target->labelA<<":\n";
            asm_str<<"DB ";
            for(unsigned db_index=0;db_index<curr_ic->name.size();++db_index)
            {
                asm_str<<"0x"<<std::hex<< (unsigned int)(unsigned char)(curr_ic->name[db_index])<<" ";
            }
            //字符串最后添加0
            asm_str<<" 0x00;\n";
        }
        else
        {
            assert(0);
        }
    }

    return asm_str.str();
}


std::string icode_to_c51::to_asm(std::vector<class icode *>& ic, std::vector<class icode *>&str_ic)
{
    std::stringstream asm_str;

    asm_str<<"ORG "<<std::setfill ('0') << std::setw(4)<<std::hex<< interrupt_addr[-1] << "H; program entry" <<std::endl;
    asm_str<<"LJMP "<<"__main_before;"<<std::endl;

    asm_str<<generate_interrupt_ljmp(ic);

    asm_str<<"__main_before:\n";
    asm_str<<"MOV 0x81, #0x7f; sp<-#0x7f\n";//设置默认的sp位置

    asm_str<<"NOP;\n";
    asm_str<<"NOP;\n";
    asm_str<<"NOP;\n";
    asm_str<<"LCALL "<<icode::get_func_label("__init_global_var") << ";\n";
    asm_str<<"LJMP "<< icode::get_func_label("main")<<  ";\n";

    ///=====================================
    ///此处进行变量空间分配
    c51_var_manage m_var(this->pcompi);
    m_var.m_context = this->pcompi;
    m_var.process(ic);
    m_sym = m_var.m_sym;
    ///=====================================


    ///=====================================
    /// 代码转asm
    for(unsigned i=0;i<ic.size();++i)
    {
        if((ic[i]->m_type==ICODE_TYPE_FUNC)&&
                (ic[i]->is_inline))
        {
            //内嵌函数，此处不生成代码，在调用的地方直接嵌入代码
            continue;
        }
        asm_str<<icode_to_asm(ic[i]);
    }
    ///=====================================


    ///=====================================
    ///系统函数添加
    ///
    for(auto it=m_inline_sys_func_needed.begin();it!=m_inline_sys_func_needed.end();++it)
    {
        asm_str<<*it<<":\n";
        asm_str<<m_inline_sys_func[*it];
        asm_str<<"\n";
    }

    ///=====================================

    ///此处进行常量代码生成。 因为初始值 通过赋值语句来实现，所以此处必须放在代码生成之后否则会出现错误：
    /// eg: code int a[5]={1,2,3,4,5};
    /// 在编译赋值语句之前a 和 {1,2,3,4,5}有自己的label。
    /// 编译复制语句时，将a的标签赋值给常量串的标签
    //std::vector<icode *> m_const_list = str_ic;
    asm_str<<const_to_db(str_ic);
    ///=====================================

    return asm_str.str();
}

std::string icode_to_c51::to_asm(icodes *ics)
{
    std::stringstream asm_str;

    asm_str<<"ORG "<<std::setfill ('0') << std::setw(4)<<std::hex<< interrupt_addr[-1] << "H; program entry" <<std::endl;
    asm_str<<"LJMP "<<"__main_before;"<<std::endl;

    asm_str<<generate_interrupt_ljmp(ics->m_top_icodes->sub_icode);

    asm_str<<"__main_before:\n";
    asm_str<<"MOV 0x81, #0x7f; sp<-#0x7f\n";//设置默认的sp位置

    asm_str<<"NOP;\n";
    asm_str<<"NOP;\n";
    asm_str<<"NOP;\n";
    asm_str<<"LCALL "<<icode::get_func_label("__init_global_var") << ";\n";
    asm_str<<"LJMP "<< icode::get_func_label("main")<<  ";\n";

    ///=====================================
    ///此处进行变量空间分配
    c51_var_manage m_var(this->pcompi);
    m_var.m_context = this->pcompi;
    m_var.process(ics->m_top_icodes->sub_icode);
    m_sym = m_var.m_sym;
    ///=====================================


    ///=====================================
    /// 代码转asm
    for(unsigned i=0;i<ics->m_top_icodes->sub_icode.size();++i)
    {
        if((ics->m_top_icodes->sub_icode[i]->m_type==ICODE_TYPE_FUNC)&&
                (ics->m_top_icodes->sub_icode[i]->is_inline))
        {
            //内嵌函数，此处不生成代码，在调用的地方直接嵌入代码
            continue;
        }
        asm_str<<icode_to_asm(ics->m_top_icodes->sub_icode[i]);
    }
    ///=====================================


    ///=====================================
    ///系统函数添加
    ///
    for(auto it=m_inline_sys_func_needed.begin();it!=m_inline_sys_func_needed.end();++it)
    {
        asm_str<<*it<<":\n";
        asm_str<<m_inline_sys_func[*it];
        asm_str<<"\n";
    }

    ///=====================================

    ///=====================================
    ///
    ///
    /// get str_ic
    std::vector<icode *> str_ic;
    icode_collect_str m_collect_str;
    m_collect_str.pcompi = ics;
    m_collect_str.process_topcode(ics->m_top_icodes);
    str_ic = m_collect_str.m_icodes;

    ///=====================================

    ///此处进行常量代码生成。 因为初始值 通过赋值语句来实现，所以此处必须放在代码生成之后否则会出现错误：
    /// eg: code int a[5]={1,2,3,4,5};
    /// 在编译赋值语句之前a 和 {1,2,3,4,5}有自己的label。
    /// 编译复制语句时，将a的标签赋值给常量串的标签
    //std::vector<icode *> m_const_list = str_ic;
    asm_str<<const_to_db(str_ic);
    ///=====================================

    return asm_str.str();
}


std::string icode_to_c51::generate_interrupt_ljmp(std::vector<icode *> &ic)
{
    std::stringstream asm_str;
    for(unsigned i=0;i<ic.size();++i)
    {
        icode * cic = ic[i];
        if(cic->m_type!=ICODE_TYPE_FUNC)
        {
            continue;
        }
        if(cic->is_interrupt)
        {
            interrupts[cic->m_interrupt_num] = cic->get_func_label();
        }
    }

    ///generate interrupt asm
    for(auto it=interrupts.begin();it!=interrupts.end();++it)
    {
        ///0003H 001BH

        asm_str<<"ORG "<<std::setfill ('0') << std::setw(4)<<std::hex<< interrupt_addr[it->first] << "H; interrupt " << it->first<<std::endl;;
        asm_str<<"LJMP"<<" "<< it->second <<";"<<std::endl;
    }

    return asm_str.str();
}

void icode_to_c51::to_asm_call(icode *ic, std::stringstream &asm_str)
{
    /// 函数调用
    /// left 是对函数的sym_ref.
    /// sub_icode 是函数参数
    /// left->result是函数本身。
    ///     其中left->result->subicode[0] 是函数返回值
    ///     其中left->result->subicode[1] 开始，是函数参数

    icode *func_to_call_ref = ic->result;

    if((func_to_call_ref->m_type==ICODE_TYPE_SYMBOL_REF)&& (func_to_call_ref->result==NULL))
    {
        cerr<<"ERROR: function used before define. "<< func_to_call_ref->name<<"\n";
        return;
    }

    icode *func_to_call = pcompi->get_def_var(ic->result) ;


    ///------------------
    /// 填入函数参数
    for(unsigned i=0;i<ic->sub_icode.size();++i)
    {
        if(func_to_call->sub_icode.size()<=i+1){
            break;
        }


        if(!func_to_call->sub_icode[i+1]->is_def_var()){
            cerr<<"ERROR: function parameter number does not match:"<< func_to_call->name<< "index:"<< i<<"\n";
            break;
        }

        if(this->get_def_var( ic->sub_icode[i])->m_bit_width==0)
        {
            //void等0长度位宽参数，不需要传递
            continue;
        }

        if(func_to_call->is_regparams)
        {
            ///通过寄存器传递参数： 每个分号代表一个变量。一次为： 返回值;第一个参数;第二个参数;第三个参数;
            /// 暂时只支持1个参数，传递到A中
            asm_str<<this->mov_byte_to_a(ic->sub_icode[i]->target);
            //asm_str <<this->mov(ic->sub_icode[i]->target, func_to_call->sub_icode[i+1]->target);
        }
        else
        {
            asm_str <<this->mov(ic->sub_icode[i]->target, func_to_call->sub_icode[i+1]->target);
        }
    }
    asm_str<<lcall( func_to_call->get_func_label(), func_to_call )<<"\n";
    ///------------------

}

std::string icode_to_c51::icode_to_asm(icode *ic)
{
    std::stringstream asm_str;
    switch(ic->m_type)
    {
    case ICODE_TYPE_ASM:
    {
        asm_str<<";_inline_asm_start\n";
        asm_str<<ic->name<<"\n";
        asm_str<<";_inline_asm_end\n";
    }
        break;
    case ICODE_TYPE_DEF_VAR:/*变量定义*/
    case ICODE_TYPE_DEF_VAR_TMP:/*中间临时变量*/
    case ICODE_TYPE_DEF_VAR_IN_VAR:/*指针变量间接寻址*/
    case ICODE_TYPE_DEF_VAR_IN_VAR_TMP:
    {
        asm_str<<";" <<ic->to_str();
        asm_str<<";addr: 0x"<<std::hex<<ic->target->m_addr<<"\n";
    }
         break;
    case ICODE_TYPE_FUNC_RET_TYPE:
    case ICODE_TYPE_FUNC_DEF_ARG:
    case ICODE_TYPE_CONST_STRING:
    case ICODE_TYPE_I_CONST:
    case ICODE_TYPE_F_CONST:
        break;



    case ICODE_TYPE_SYMBOL_REF:
        break;


    case ICODE_TYPE_FUNC:
    {
        ///------------------

        m_curr_func = ic;
        ///------------------
        ///
        ///
        ///
        if(ic->is_inline)
        {
            m_inline_vec.push_back(get_tmp_label_nake("_infun_"+ic->name));
        }
        else
        {
            m_inline_vec.push_back(get_tmp_label_nake("_fun_"+ic->name));
        }

        refresh_label_prefix();

        /// 函数标签是全局的，但是内嵌的函数标签是局部的
        if(ic->is_inline)
        {
            asm_str <<this->m_inline_func_label_prefix<< ic->get_func_label()<<":\n";
        }
        else
        {
            asm_str <<ic->get_func_label()<<":\n";
        }


        if(ic->is_interrupt)
        {
            asm_str<<"PUSH 0x"<<std::hex<<REG_ADDR_ACC<<  ";\n";
            asm_str<<"PUSH 0x"<<std::hex<<REG_ADDR_PSW<<  ";\n";
        }
        if(ic->is_using_group)
        {
            switch(ic->m_using_group_num)
            {
            case 0:
                asm_str<<"MOV 0x"<<std::hex<<REG_ADDR_PSW<<", #0x00;\n";
                break;
            case 1:
                asm_str<<"MOV 0x"<<std::hex<<REG_ADDR_PSW<<", #0x08;\n";
                break;
            case 2:
                asm_str<<"MOV 0x"<<std::hex<<REG_ADDR_PSW<<", #0x10;\n";
                break;
            case 3:
                asm_str<<"MOV 0x"<<std::hex<<REG_ADDR_PSW<<", #0x18;\n";
                break;
            default:
                asm_str<<"ERROR: using group number error:"<< ic->m_using_group_num<<";\n";
                cerr<<"using group number error. in function "<< ic->name<<"\n";
                break;

            }
        }


        for(unsigned i=0;i<ic->sub_icode.size();++i)
        {
            asm_str<<icode_to_asm(ic->sub_icode[i]);
        }


        ///如果一个函数没有RET，就要加上RET。此处暂时不管有没有，都加上RET
        if(ic->is_inline)
        {
            asm_str<<this->m_inline_func_label_prefix<<ic->get_func_ret_label()<<":\n";
            asm_str <<this->m_inline_func_label_prefix<<ic->get_func_end_label()<<":\n";
        }
        else
        {
            asm_str<<ic->get_func_ret_label()<<":\n";

            if(ic->is_interrupt)
            {
                asm_str<<"POP 0x"<<std::hex<<REG_ADDR_PSW<<  ";\n";
                asm_str<<"POP 0x"<<std::hex<<REG_ADDR_ACC<<  ";\n";
                asm_str<<"RETI;\n";
            }
            else
            {
                asm_str<<"RET;\n";
            }
            asm_str <<ic->get_func_end_label()<<":\n";
        }

        m_inline_vec.pop_back();
        refresh_label_prefix();
    }
        break;

    case ICODE_TYPE_EXP_OP:
        asm_str<<";"<<ic->to_str()<<"\n";
        asm_str<<icode_to_asm_op(ic);
        break;
    case ICODE_TYPE_FUNC_RETURN:
        if(m_curr_func->is_inline)
        {
            asm_str<<"SJMP "<<  this->m_inline_func_label_prefix<<m_curr_func->get_func_ret_label()<<";\n";
        }
        else
        {
            asm_str<<"SJMP "<< m_curr_func->get_func_ret_label()<<";\n";
        }
        break;

    case ICODE_TYPE_SCOPE:
    case ICODE_TYPE_BLOCK://只是将多个icode顺序组合在一起
        for(unsigned i=0;i<ic->sub_icode.size();++i)
        {
            asm_str<<icode_to_asm(ic->sub_icode[i]);
        }
        break;
    case  ICODE_TYPE_LABELED_BLOCK:// 此处是一个特殊的block，前后可以有2个标签，用于跳转语句
    {
        asm_str<<this->m_inline_func_label_prefix<<ic->get_block_start_label()  <<":\n";
        for(unsigned i=0;i<ic->sub_icode.size();++i)
        {
            asm_str<<icode_to_asm(ic->sub_icode[i]);
        }
        asm_str<<this->m_inline_func_label_prefix<<ic->get_block_end_label()  <<":\n";
    }
        break;

    case ICODE_TYPE_LABELED_BLOCK_START_REF://代表result中的icode的起始位置
            break;
    case ICODE_TYPE_LABELED_BLOCK_END_REF:
        break;
    case ICODE_TYPE_CALL:
        {
            //函数调用
            to_asm_call(ic, asm_str);
        }

        break;


    case ICODE_TYPE_UNKNOWN:
    default:
    {

        cerr<<"ERROR: icode type unknown. "<< ic->m_type<< "\n";
        cerr<<"ic:"<< *ic<<"\n";
    }
        break;
    }

    return asm_str.str();
}

std::string icode_to_c51::icode_to_asm_op(icode *ic)
{
    std::stringstream asm_str;

    if(ic->name=="init")
    {
        asm_str <<to_asm_opr_init(ic);
    }
    else if(ic->name=="=")
    {
        //=号算符
        asm_str <<to_asm_opr_mov(ic);
    }
    else if(ic->name=="==")
    {
        //is_equal
        asm_str <<to_asm_opr_is_equal(ic);
    }
    else if(ic->name=="!=")
    {
        asm_str <<to_asm_opr_is_not_equal(ic);
    }
    else if(ic->name=="+")
    {
        asm_str <<to_asm_opr_plus(ic);
    }
    else if(ic->name=="+=")
    {
        asm_str <<to_asm_opr_plus_eq(ic);
    }
    else if(ic->name=="-")
    {
        asm_str << to_asm_opr_sub(ic);
    }
    else if(ic->name=="-=")
    {
        asm_str << to_asm_opr_sub_eq(ic);
    }
    else if(ic->name=="*")
    {
        asm_str << to_asm_opr_mul(ic);
    }
    else if(ic->name=="*=")
    {
        asm_str << to_asm_opr_mul_eq(ic);
    }
    else if(ic->name=="/")
    {
        asm_str << to_asm_opr_div(ic);
    }
    else if(ic->name=="/=")
    {
        asm_str << to_asm_opr_div(ic);
    }
    else if(ic->name=="%")
    {
        asm_str<<to_asm_opr_mod(ic);
    }
    else if(ic->name=="%=")
    {
        asm_str<<to_asm_opr_mod(ic);
    }
    else if(ic->name=="|")
    {
        asm_str<<to_asm_opr_bit_or(ic);

    }
    else if(ic->name=="|=")
    {
        asm_str<<to_asm_opr_bit_or(ic);
    }
    else if(ic->name=="&")
    {
        asm_str<<to_asm_opr_bit_and(ic);
    }
    else if(ic->name=="&=")
    {
        asm_str<<to_asm_opr_bit_and(ic);
    }
    else if(ic->name=="^")
    {
        asm_str << to_asm_opr_xor(ic);
    }
    else if(ic->name=="^=")
    {
        asm_str << to_asm_opr_xor(ic);
    }
    else if(ic->name=="<")
    {
        asm_str << to_asm_opr_less(ic);
    }
    else if(ic->name=="<=")
    {
        asm_str << to_asm_opr_less_eq(ic);
    }
    else if(ic->name==">")
    {
        asm_str << to_asm_opr_greater(ic);
    }
    else if(ic->name==">=")
    {
        asm_str << to_asm_opr_greater_eq(ic);
    }
    else if(ic->name==">>")
    {
        asm_str << to_asm_opr_shiftr(ic);
    }
    else if(ic->name==">><")
    {
        asm_str << to_asm_opr_rotate_shiftr(ic);
    }
    else if(ic->name==">>=")
    {
        asm_str << to_asm_opr_shiftr_eq(ic);
    }
    else if(ic->name=="<<")
    {
        asm_str << to_asm_opr_shiftl(ic);
    }
    else if(ic->name=="><<")
    {
        asm_str << to_asm_opr_rotate_shiftl(ic);
    }
    else if(ic->name=="<<=")
    {
        asm_str << to_asm_opr_shiftl_eq(ic);
    }
    else if(ic->name=="!")
    {
        asm_str<<to_asm_opr_logic_not(ic);
    }
    else if(ic->name=="&&")
    {
        asm_str<<to_asm_opr_logic_and(ic);
    }
    else if(ic->name=="||")
    {
        asm_str<<to_asm_opr_logic_or(ic);
    }
    else if(ic->name=="~")
    {
        asm_str << to_asm_opr_bit_not(ic);
    }
    else if(ic->name=="JMP")
    {
        asm_str << to_asm_opr_jmp(ic);
    }
    else if(ic->name=="JNZ")
    {
        asm_str << to_asm_opr_jnz(ic);
    }
    else if(ic->name=="JZ")
    {
        asm_str << to_asm_opr_jz(ic);
    }
    else if(ic->name=="--")
    {
        asm_str << to_asm_opr_mm(ic);
    }
    else if(ic->name=="++")
    {
        asm_str<<to_asm_opr_pp(ic);
    }
    else if(ic->name=="address_of")
    {
        /// 获取变量的地址

        asm_str<<to_asm_opr_address_of(ic);
    }
    else if(ic->name=="negative")
    {
        asm_str<<to_asm_opr_negative(ic);
    }
    else
    {
        cerr<<"ERROR:unknown opr:"<< ic->name<<". could not to asm code\n";
        asm_str<<";unknown opr:"<< ic->name<<". could not to asm code\n";
    }

    return asm_str.str();
}


std::string icode_to_c51::mov(c51_addr *from, c51_addr *to)
{
    /// 等号，赋值语句，
    /// bit读写：必须经过c寄存器位
    /// mov c, bit
    /// mov bit, c
    ///
    /// 立即数：
    /// mov A, #data
    /// mov Rn, #data
    /// mov direct, #data
    /// mov @Ri, #data
    /// mov dptr, #data16
    ///
    /// data数据的读写：
    /// mov direct, A
    /// mov A, direct
    /// mov direct, Rn
    /// mov Rn, direct
    /// mov direct, direct
    /// mov A, Rn
    /// mov Rn, A

    ///
    /// idata的读写：
    /// mov direct, @Ri
    /// mov @Ri, A
    /// mov A, @Ri
    /// mov @Ri, direct

    /// code区:
    /// movc A,@A+DPTR
    /// movc A,@A+PC
    ///
    /// 内部扩展ram，pdata
    /// movx A, @Ri
    /// movx @Ri, A
    ///
    /// 内部扩展ram, xdata
    /// movx A, @DPTR
    /// movx @DPTR, A
    ///
    std::stringstream asm_str;

    if(from->is_equal(to))
    {
        return ";mov self to. just ignore\n";
    }


#if 1
    //if(to->is_array || to->is_ptr || from->is_array || from->is_ptr)
    if((to->m_type==DATA_TYPE_IN_GENRIC_PTR) || (from->m_type==DATA_TYPE_IN_GENRIC_PTR))
    {
        //只要是有指针，都没有优化
        int mov_bit=to->m_bit_width;
        int mov_byte_shift=0;
        while(mov_bit>0)
        {
            asm_str<<mov_byte_to_a(from, mov_byte_shift);
            asm_str<<mov_byte_a_to(to, mov_byte_shift);
            mov_byte_shift++;
            mov_bit-=8;
        }

        return asm_str.str();
    }
#endif

    /// 下面是非指针数据的处理
    /// =========================================
    ///

    if(to->is_float32 || from->is_float32)
    {
        ///有一个字段是float的，则需要转为float，进行float计算
        ///

        if((to->is_float32)&&(!from->is_float32))
        {
            //from不是float，to是float。需要转换from为float
            asm_str<<this->mov_byte_to_r4(from, 0);
            asm_str<<this->mov_byte_to_r5(from, 1);
            asm_str<<this->mov_byte_to_r6(from, 2);
            asm_str<<this->mov_byte_to_r7(from, 3);

            asm_str<< this->lcall("_sys_fcast");

            asm_str<<this->mov_byte_r4_to(to, 0);
            asm_str<<this->mov_byte_r5_to(to, 1);
            asm_str<<this->mov_byte_r6_to(to, 2);
            asm_str<<this->mov_byte_r7_to(to, 3);




            return asm_str.str();
        }
        else if((!to->is_float32)&&(from->is_float32))
        {


            asm_str<<this->mov_byte_to_r4(from, 0);
            asm_str<<this->mov_byte_to_r5(from, 1);
            asm_str<<this->mov_byte_to_r6(from, 2);
            asm_str<<this->mov_byte_to_r7(from, 3);

            //此处肯定会有问题，此代码应该不会被调用到
            /// 因为在icode_float_func_opr中会处理此问题
            /// 如果在这里处理，函数应用此处问题无法解决，_sys_castf 会被dead_code模块认为是无用函数而删除，导致函数unresolved
            ///
            assert(0);

            asm_str<< this->lcall("_sys_castf");

            asm_str<<this->mov_byte_r4_to(to, 0);
            asm_str<<this->mov_byte_r5_to(to, 1);
            asm_str<<this->mov_byte_r6_to(to, 2);
            asm_str<<this->mov_byte_r7_to(to, 3);

            return asm_str.str();
        }
        else
        {
            //2个数据都是float，直接mov
            int mov_bit=to->m_bit_width;
            int mov_byte_shift=0;
            while(mov_bit>0)
            {
                asm_str<<mov_byte_to_a(from, mov_byte_shift);
                asm_str<<mov_byte_a_to(to, mov_byte_shift);
                mov_byte_shift++;
                mov_bit-=8;
            }
            return asm_str.str();
        }
    }




    if((to->m_type==DATA_TYPE_BIT)&&(from->m_type==DATA_TYPE_J_DATA))
    {
        if(from->m_addr)
        {
            asm_str<<"SETB 0x"<<std::hex<<to->m_addr<<";\n";
        }
        else
        {
            asm_str<<"CLR 0x"<<std::hex<<to->m_addr<<";\n";
        }
    }
    else if ((to->m_type==DATA_TYPE_BIT)&&(from->m_type==DATA_TYPE_BIT))
    {
        asm_str<<"MOV C, 0x" <<std::hex<<from->m_addr<<";\n";
        asm_str<<"MOV 0x" <<std::hex<< to->m_addr<<", C;\n";
    }
    else if(to->m_type==DATA_TYPE_BIT)
    {   
        //通过转移数据到A，
        //带借位右移，将最低位移动到C中
        //C位移动到目标bit中
        asm_str<<this->mov_byte_to_a(from);
        asm_str<<this->mov_byte_a_to(to);
        //asm_str<<"RRC A;\n";
        //asm_str<<"MOV 0" <<std::hex<< to->m_addr<<"H, C;\n";
    }
    else if(to->m_type==DATA_TYPE_RN)
    {
        int mov_bit=to->m_bit_width;
        int mov_byte_shift=0;
        while(mov_bit>0)
        {
            asm_str<<mov_byte_to_ri(from, mov_byte_shift, 0,to->m_addr + mov_byte_shift);
            mov_byte_shift++;
            mov_bit-=8;
        }
    }
    else if(((to->m_type==DATA_TYPE_DIRECT)&&(from->m_type==DATA_TYPE_J_DATA)) ||
            ((to->m_type==DATA_TYPE_DIRECT)&&(from->m_type==DATA_TYPE_DIRECT))||
            ((to->m_type==DATA_TYPE_DIRECT)&&(from->m_type==DATA_TYPE_IDATA))||
            ((to->m_type==DATA_TYPE_DIRECT)&&(from->m_type==DATA_TYPE_J_DATA_LABEL)))
    {

        int mov_bit=to->m_bit_width;
        int mov_byte_shift=0;
        while(mov_bit>0)
        {
            asm_str<<mov_byte_to_direct(from, mov_byte_shift, to->m_addr+mov_byte_shift);
            mov_byte_shift++;
            mov_bit-=8;
        }
    }
    else// if((to->m_type==DATA_TYPE_XDATA)||(from->m_type==DATA_TYPE_XDATA))
    {
        int mov_bit=to->m_bit_width;
        int mov_byte_shift=0;
        while(mov_bit>0)
        {
            asm_str<<mov_byte_to_a(from, mov_byte_shift);
            asm_str<<mov_byte_a_to(to, mov_byte_shift);
            mov_byte_shift++;
            mov_bit-=8;
        }
    }


    return asm_str.str();
}


c51_addr *icode_to_c51::get_target(icode *ic)
{
    if(ic==NULL)return NULL;
#if 0
    //此处是获取目标地址如果是SYM_REF，可能是指针
    if((ic->m_type!=ICODE_TYPE_SYMBOL_REF)||
            ((ic->m_type==ICODE_TYPE_SYMBOL_REF) &&(ic->is_array==0) &&(ic->is_ptr==0)))
    {
            //不涉及指针数组问题
            ic = get_def_var(ic);
            return ic->target;
    }
#endif
    ///ic->m_type==ICODE_TYPE_SYMBOL_REF and ic->is_array!=0
    /// 数组引用。此处需要
    return ic->target;
}

icode *icode_to_c51::get_def_var(icode *ic)
{
    if(ic==NULL)return NULL;
    if(ic->m_type==ICODE_TYPE_SYMBOL_REF)
    {
        ic=ic->result;
    }
    return ic;
}

std::string icode_to_c51::lcall(std::string func_full_name, icode *func)
{
    if(m_inline_sys_func.find( func_full_name)!=m_inline_sys_func.end())
    {
        m_inline_sys_func_needed.insert(func_full_name);
    }

    std::stringstream asm_str;


    ///正常函数调用
    if((func==NULL)||
            (!func->is_inline))
    {
        asm_str<<"LCALL "<<func_full_name<<";\n";
        return asm_str.str();
    }


    ///内嵌函数调用
    ///
    ///
    ///
    ///
    ///

    if(func->name=="_inline_asm_")
    {
        /// extern inline __inline_asm__(char * asm_str);
        // this is a compile patch for insert asm
        // 将字符串插入汇编代码
        // 将字符串从代码中去除


        return asm_str.str();
    }




    asm_str<< icode_to_asm(func);

    return asm_str.str();
}

std::string icode_to_c51::get_tmp_label_nake(std::string comment)
{
    static unsigned long tmp_label = 0;
    std::stringstream asm_str;
    asm_str<< comment<<"_"<< time(NULL)<<"_"<<  tmp_label;

    tmp_label++;
    return asm_str.str();
}

std::string icode_to_c51::get_tmp_label(std::string comment)
{
    static unsigned long tmp_label = 0;
    std::stringstream asm_str;
    asm_str<<m_inline_func_label_prefix<<"_"<< comment<<"_"<< time(NULL)<<"_"<<  tmp_label<<"_";

    tmp_label++;
    return asm_str.str();
}

int icode_to_c51::refresh_label_prefix()
{
    m_inline_func_label_prefix="";
    for(unsigned i=0;i<m_inline_vec.size();++i)
    {
        m_inline_func_label_prefix=m_inline_func_label_prefix+ m_inline_vec[i];
    }
    return 0;
}



