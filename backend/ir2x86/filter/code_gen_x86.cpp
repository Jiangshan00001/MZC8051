#include <sstream>
#include "number2str.h"
#include "code_gen_x86.h"
#include "var_manage_x86.h"
#include "string_eval.h"

code_gen_x86::code_gen_x86()
{
    m_ebp = 0;
    m_esp = 0;

    m_Reg.add_reg("eax");
    m_Reg.add_reg("ebx");
    m_Reg.add_reg("ecx");
    m_Reg.add_reg("edx");




}

int code_gen_x86::execute(icodes *ics, std::stringstream &istr)
{
    this->pcompi = ics;


    var_manage_x86 m_var_manage;

    //icode_collect_global_var m_collect_global_var;
    m_var_manage.execute(ics);

    istr<<";;format: win32\n\n";

    ///初始化全局变量/静态变量放入.data
    ///
    istr<<"\n";
    istr<<"section .data\n";
    for(int i=0;i<m_var_manage.m_init_gvar.size();++i)
    {
        icode * var = m_var_manage.m_init_gvar[i];
        icode * var_init_opr = m_var_manage.m_init_gvar_opr[i];

        code_gen_db_init(var, var_init_opr, istr);
    }

    for(int i=0;i<m_var_manage.m_const_string.size();++i)
    {
        icode * var = m_var_manage.m_const_string[i];
        istr<<var->m_var_info.m_name<<" db \"" <<string_pack(var->name)<<"\"\n";
    }
    for(int i=0;i<m_var_manage.m_const_list.size();++i)
    {
        icode * var = m_var_manage.m_const_list[i];
        istr<<var->m_var_info.m_name<<" "<< get_var_size_qualifier(var->m_in_ptr_type->m_bit_width)<< "  ";
        for(int j=0;j<var->sub_icode.size();++j)
        {
            if(j>0)istr<<",";
            istr<<" "<< var->sub_icode[j]->name;
        }
        istr<<"\n";
        //<<string_pack(var->name)<<"\n";
    }



    /// 未初始化全局变量/静态变量放入 .bss
    istr<<"section .bss\n";
    for(int i=0;i<m_var_manage.m_uninit_gvar.size();++i)
    {
        icode * var = m_var_manage.m_uninit_gvar[i];
        code_gen_resb_init(var, istr);
    }
    if(m_var_manage.m_uninit_gvar.size()==0)
    {
        istr<<"dummy               resd 1\n";
    }

    istr<<"section .text\n";
    istr<<"global _main\n";  //gnu ld (native/cygwin/mingw)
    istr<<"global start\n";  //golink


    istr<<"main:\n";
    istr<<"start:\n";

    //istr<<"call _?db_init\n";
    istr<<"call _main\n";
    istr<<"ret\n";
    ///----------------------------------------------
    ///
    /// 函数代码生成
    /// 局部变量都放入堆栈
    /// 调用约定暂时只使用win32的
    /// 每个函数中变量的作用域，暂时使用scope确定
    ///
    ///
    /// 操作： 动作+数据
    ///
    /// 数据类型：bss，data， 堆栈中，寄存器?
    /// 操作类型：+-*/%jmptest...
    ///
    this->reset();
    this->process_topcode(ics->m_top_icodes, &istr);


    return 0;
}

void code_gen_x86::code_gen_db_init(icode *var, icode *var_init_opr, std::stringstream &istr)
{

    if(var->is_float32)
    {
        istr<<var->name<<" dd "<<var_init_opr->right->fnum<<"\n";;
    }
    else if(var->m_bit_width==8)
    {
        istr<<var->name<<" db "<<var_init_opr->right->fnum<<"\n";;
    }
    else if(var->m_bit_width==16)
    {
        istr<<var->name<<" dw "<<var_init_opr->right->fnum<<"\n";;
    }
    else if(var->m_bit_width==24)
    {
        istr<<var->name<<" ASSERT24 "<<var_init_opr->right->fnum<<"\n";;
    }
    else if(var->m_bit_width==32)
    {
        istr<<var->name<<" dd "<<var_init_opr->right->fnum<<"\n";;
    }
    else if(var->m_bit_width==64)
    {
        istr<<var->name<<" dq "<<var_init_opr->right->fnum<<"\n";;
    }
}

void code_gen_x86::code_gen_resb_init(icode *var, std::stringstream &istr)
{
    istr<<var->name<<" resb "<< var->m_bit_width/8<<"\n";
}


#if 0
void main()
{
int a;
a=4;
}

func:$main;
    ret_type: $__main_ret,u0;
    {:
def_var: $a,i32;
opr: "=", null;, iconst:0x4:0x8;, %a;
};
func_end:%main;


#endif

///
/// \brief code_gen_x86::process_one_icode_start
/// \param ic
/// \param user_data
/// \param iparent
/// \return
/// https://docs.microsoft.com/en-us/cpp/cpp/cdecl?view=msvc-160
/// _cdecl 默认使用的 cdecl函数调用约定：
/// __CDECL
/// Element	Implementation
/// Argument-passing order	Right to left.
/// Stack-maintenance responsibility	Calling function pops the arguments from the stack.
/// Name-decoration convention	Underscore character (_) is prefixed to names, except when __cdecl functions that use C linkage are exported.
/// Case-translation convention	No case translation performed.
///
///
/// https://blog.csdn.net/u010608283/article/details/52900442
/// https://blog.csdn.net/qq_33921804/article/details/52663212
/// 函数返回值：
///  32bit及以下：eax
///  64bit: edx:eax
///  浮点数：st0
///  更长的结构体：调用方在堆栈中申请内存，
///     将内存首地址作为最后一个参数压栈
///     被调用方执行初始化和赋值，最后通过eax将地址返回
///
void code_gen_x86::code_gen_cdecl_func(icode *ic, std::stringstream&  istr)
{
    assert(ic->sub_icode.size()>0);

    /// =========================
    ///函数名称:
    ///
    ///
    istr<<"_"<<ic->name<<":\n";


    /// =========================
    /// 函数参数模拟放入堆栈中
    /// 不需要生成实际代码，因为参数是由调用者放入堆栈中的
    ///

    icode *ret_ic = ic->sub_icode[0];

    ///函数返回值bitwidth<=32. >32时暂时未实现
    /// <=32 eax传递返回值
    assert(ret_ic->m_bit_width<=32);
    ret_ic->m_var_info.m_type =X86_VAR_TYPE_REG;
    ret_ic->m_var_info.m_name = "eax";


    /// ret arg0 arg1. arg_cnt=3
    /// arg个个数，包含返回值
    int arg_cnt=1;
    for(int i=1;i<ic->sub_icode.size();++i)
    {
        icode * arg_ic = ic->sub_icode[i];

        if(arg_ic->m_type==ICODE_TYPE_FUNC_DEF_ARG)
        {
            arg_cnt++;
            arg_ic->m_var_info.m_type = X86_VAR_TYPE_STACK;
            continue;
        }
        break;
    }

    /// 将arg右到左的方式入栈
    ///
    for(int i=arg_cnt-1;i>=1;--i)
    {
        m_func_stack.push_back(ic->sub_icode[i]);
        m_func_stack_byte_width.push_back(((ic->sub_icode[i]->m_bit_width+31)/32)*4);
    }


    ///参数压入完成后，在调用call时，会放入eip
    ///
    m_func_stack.push_back(0);
    m_func_stack_byte_width.push_back(4);

    /// =========================
    ///

    istr<<";enter\n";
    istr<<"push ebp;\n";
    istr<<"mov ebp, esp;\n";

    ///ebp
    m_func_stack.push_back(0);
    m_func_stack_byte_width.push_back(4);

    this->m_esp = this->m_func_stack.size()-1;
    this->m_ebp = this->m_esp;
}

void code_gen_x86::code_gen_cdecl_func_call(icode *ic, std::stringstream &istr)
{
    ///这是一个函数调用，使用cdecl约定：
    /// 将arg右到左的方式入栈
    /// 函数返回值：
    ///  32bit及以下：eax
    ///  64bit: edx:eax
    ///  浮点数：st0
    ///  更长的结构体：调用方在堆栈中申请内存，
    ///     将内存首地址作为最后一个参数压栈
    ///     被调用方执行初始化和赋值，最后通过eax将地址返回
    ///

    icode * func = NULL;
    if(ic->result==NULL)
        func = ic->result;
    else
        func = ic->result->result;

    for(int i=ic->sub_icode.size();i>0;--i)
    {
        std::string opr1 = opr_get( ic->sub_icode[i-1], istr, 0);
        istr<<"push dword "<<opr1<<"\n";
    }

    istr<<"call _"<<func->name<<"\n";
}

#if 0
int func1(int a)
{
return a+1;
}
void main()
{
int b = func1(3);
}

func:$func1;
    ret_type: $__func1_ret,i32;
    def_arg: $a,i32;
    {:
def_var_tmp: $TMP_14600970,i32;
opr: "+", %a;, iconst:0x1:0x8;, %TMP_14600970;
opr: "=", null;, %TMP_14600970;, %__func1_ret;
return;
};
func_end:%func1;
func:$main;
    ret_type: $__main_ret,u0;
    {:
def_var: $b,i32;
call:%func1;
iconst:0x3:0x8;
call_end:%func1;
opr: "init", null;, %__func1_ret;, %b;
};
func_end:%main;

int main()
{
    int a=4;
}

func:$main;
    ret_type: $__main_ret,i32;
    {:
def_var: $a,i32;
opr: "init", null;, iconst:0x4:0x20;, %a;
};
func_end:%main;


#endif




std::string code_gen_x86::get_var_size_qualifier(int ibitwidth)
{
    std::string size_comment_str = "byte";
    //byte、word、dword、qword
    if(ibitwidth<=8)
    {
        size_comment_str = "byte";
    }
    else if(ibitwidth<=16)
    {
        size_comment_str = "word";
    }
    else if(ibitwidth<=32)
    {
        size_comment_str="dword";

    }
    else
    {
        size_comment_str="qword";
    }
    return size_comment_str;
}



int code_gen_x86::get_stack_pos(icode *var)
{
    assert(var->m_var_info.m_type==X86_VAR_TYPE_STACK);

    ///堆栈参数
    /// 找到参数所在堆栈位置
    /// 通过sp访问
    ///
    auto it1 = std::find(m_func_stack.begin(), m_func_stack.end(), var);
    assert(it1!=m_func_stack.end());

    //这个是第几个
    int dist = it1 -m_func_stack.begin() ;
    if(m_ebp>=dist)
    {
        int cnt = std::accumulate(m_func_stack_byte_width.begin()+dist,m_func_stack_byte_width.begin()+m_ebp, 0);
        //return size_qualifier+std::string(" [")+"ebp+" + NumberToStr(cnt) +"]";
        return cnt;
    }
    //m_ebp<dist

    int cnt = std::accumulate(m_func_stack_byte_width.begin()+m_ebp,m_func_stack_byte_width.begin()+dist, 0);
    //return size_qualifier+std::string(" [")+"ebp-" + NumberToStr(cnt) +"]";
    return -cnt;

}



std::string code_gen_x86::opr_get(icode *ic, std::stringstream &istr, bool add_size_quali)
{
    if(ic->m_type==ICODE_TYPE_SYMBOL_REF)
    {
        if(ic->result==NULL)
        {
            ///外部符号？
            return "["+ic->name+"]";
        }
        else
        {
            icode * var = ic->result;
            if(var->m_var_info.m_type==X86_VAR_TYPE_STACK)
            {
                int pos = get_stack_pos(var);
                std::string size_qualifier = get_var_size_qualifier(var->m_bit_width);
                if(add_size_quali)
                {
                    return size_qualifier+std::string(" [")+"ebp+(" + NumberToStrDec(pos) +")]";
                }
                else
                {
                    return std::string(" [")+"ebp+(" + NumberToStrDec(pos) +")] ";
                }

            }
            else if(var->m_var_info.m_type==X86_VAR_TYPE_REG)
            {
                return var->m_var_info.m_name;
            }
            else
            {
                assert(0);
            }
        }
    }
    else if(ic->m_type==ICODE_TYPE_I_CONST)
    {
        return ic->name;
    }
    else if((ic->m_type==ICODE_TYPE_DEF_VAR_IN_VAR)||
            (ic->m_type==ICODE_TYPE_DEF_VAR_IN_VAR_TMP)
            )
    {
        std::string opr1;
        if(ic->result==NULL)
        {
            opr1=ic->name;
        }
        else
        {
            icode * var = ic->result;
            if(var->m_var_info.m_type==X86_VAR_TYPE_STACK)
            {
                int pos = get_stack_pos(var);
                std::string size_qualifier = get_var_size_qualifier(var->m_bit_width);
                opr1 = size_qualifier+std::string(" [")+"ebp+(" + NumberToStrDec(pos) +")]";

            }
            else if(var->m_var_info.m_type==X86_VAR_TYPE_REG)
            {
                opr1 = var->m_var_info.m_name;
            }
            else
            {
                assert(0);
            }
        }
        istr<<"mov ebx,"<< opr1 <<"\n";
        if(add_size_quali)
        {
            return get_var_size_qualifier(ic->result->m_bit_width)+ " [ebx]";
        }
        else
        {
            return " [ebx] ";
        }

    }
    else if(ic->m_type==ICODE_TYPE_LABELED_BLOCK_START_REF)
    {
        return ic->result->name;
    }
    else if((ic->m_type==ICODE_TYPE_CONST_STRING)||
            (ic->m_type==ICODE_TYPE_CONST_LIST) )
    {
        return ic->m_var_info.m_name;
    }

    return std::string("");
}

int code_gen_x86::get_bitwidth(icode *ic)
{
    if(ic->m_type==ICODE_TYPE_SYMBOL_REF)
    {
        if(ic->result==NULL)
        {
            ///外部符号？
            return 32;
        }
        else
        {
            icode * var = ic->result;
            return var->m_bit_width;
        }
    }
    else if(ic->m_type==ICODE_TYPE_I_CONST)
    {
        return ic->m_bit_width;
    }
    else if((ic->m_type==ICODE_TYPE_DEF_VAR_IN_VAR)||
            (ic->m_type==ICODE_TYPE_DEF_VAR_IN_VAR_TMP)
            )
    {
        std::string opr1;
        if(ic->result==NULL)
        {
            return 32;
        }
        else
        {
            icode * var = ic->result;
            return var->m_bit_width;
        }
        return 32;
    }
    else if(ic->m_type==ICODE_TYPE_LABELED_BLOCK_START_REF)
    {
        return 32;
    }
    else if((ic->m_type==ICODE_TYPE_CONST_STRING)||
            (ic->m_type==ICODE_TYPE_CONST_LIST) )
    {
        return 32;
    }

    return 32;
}



int code_gen_x86::process_one_icode_start(icode *ic, void *user_data, icode *iparent)
{
    std::stringstream &istr = *(std::stringstream *)user_data;
    if((m_level==0)&& (ic->m_type!=ICODE_TYPE_FUNC))
    {
        /// 全局变量和静态变量代码已经生成
        //此处只生成函数代码
        return 0;
    }

    switch(ic->m_type)
    {
    case ICODE_TYPE_FUNC:
    {
        if(ic->is_extern)
        {
            ///外部函数，从处不处理
            return 0;
        }

        /// 根据函数调用约定，进行指令生成

        /// 压入堆栈
        /// 返回值放入eax，或者最后一个参数
        ///

        ///函数至少有返回值
        code_gen_cdecl_func(ic, istr);

        /// 此处生成代码
        ///
        return 0;
    }
        break;
    case ICODE_TYPE_FUNC_RET_TYPE:
    case ICODE_TYPE_FUNC_DEF_ARG:
    {
        ///参数放在func类型时处理，此处不再处理
        return 0;
    }
        break;

    case ICODE_TYPE_CALL:
    {
        //函数调用,参数入栈
        code_gen_cdecl_func_call(ic, istr);

        return 0;
    }
        break;
    case ICODE_TYPE_EXP_OP:
    {
        ///函数内部的操作
        ///
        istr<<";opr:"<<ic->name<<";\n";
        if(ic->name=="init")
        {
            std::string opr1 = opr_get(ic->right, istr);
            std::string opr2 = opr_get(ic->result, istr);
            istr<<"mov eax, "<< opr1<<";\n";
            istr<<"mov "<< opr2 <<", eax;\n";
            return 0;
        }
        else if(ic->name=="=")
        {
            std::string right_str = opr_get(ic->right, istr);
            std::string result_str = opr_get(ic->result, istr);
            istr<<"mov eax, "<< right_str<<";\n";

            if(get_bitwidth(ic->result)==32)
            {
                istr<<"mov "<< result_str<<", eax;\n";
            }
            else if(get_bitwidth(ic->result)==16)
            {
                istr<<"mov "<< result_str<<", ax;\n";
            }
            else if(get_bitwidth(ic->result)==8)
            {
                istr<<"mov "<< result_str<<", al;\n";
            }
            else
            {
                assert(0);
            }
            return 0;
        }
        else if(ic->name=="+")
        {
            std::string right_str = opr_get(ic->right, istr);
            std::string left_str = opr_get(ic->left, istr);
            std::string result_str = opr_get(ic->result, istr);

            istr<<"mov eax,"<<right_str<<"\n";
            istr<<"add eax,"<<left_str<<"\n";
            istr<<"mov "<<result_str<<",eax\n";
        }
        else if(ic->name=="!=")
        {
            std::string right_str = opr_get(ic->right, istr);
            std::string left_str = opr_get(ic->left, istr);
            std::string result_str = opr_get(ic->result, istr);


            int opr_width =get_bitwidth(ic->right);
            std::string rx = "eax";
            if(opr_width==8)
            {
                rx = "al";
            }
            else if(opr_width==16)
            {
                rx = "ax";
            }
            else if(opr_width==32)
            {
                rx = "eax";
            }

            istr<<"mov eax"<<", 0;\n";
            istr<<"mov "<<rx<<", "<<right_str<<"\n";
            istr<<"cmp eax,"<<left_str<<"\n";
            istr<<"LAHF\n";
            istr<<"SHR EAX,14\n";
            istr<<"not EAX\n";
            istr<<"and EAX,1\n";

            opr_width =get_bitwidth(ic->result);
            if(opr_width==8)
            {
                rx = "al";
            }
            else if(opr_width==16)
            {
                rx = "ax";
            }
            else if(opr_width==32)
            {
                rx = "eax";
            }
            istr<<"mov "<< result_str<< ","<<rx<<"\n";
        }
        else if(ic->name=="JZ")
        {
            std::string left_str = opr_get(ic->left, istr);
            std::string result_str = opr_get(ic->result, istr);

            int opr_width =get_bitwidth(ic->left);
            std::string rx = "eax";
            if(opr_width==8)
            {
                rx = "al";
            }
            else if(opr_width==16)
            {
                rx = "ax";
            }
            else if(opr_width==32)
            {
                rx = "eax";
            }
                istr<<"mov "<<rx<<","<<left_str<<"\n";
                istr<<"cmp "<<rx<<",0\n";
                istr<<"je "<<result_str<<"\n";

        }
        else if(ic->name=="JMP")
        {
            std::string result_str = opr_get(ic->result, istr);

            istr<<"jmp "<<result_str<<"\n";
        }
        else if(ic->name=="++")
        {
            std::string result_str = opr_get(ic->result, istr);
            istr<<"mov eax, "<<result_str<<"\n";
            istr<<"add eax, 1\n";
            istr<<"mov "<< result_str<<", eax\n";
        }
        else
        {
            assert(0);
        }
    }
        break;
    case ICODE_TYPE_LABELED_BLOCK:
    {
        //此处添加标签
        istr<<ic->name<<  ":\n";
    }
        break;
    case ICODE_TYPE_FUNC_RETURN:
    {

        if((this->m_curr_func!=NULL)&&(this->m_curr_func->name=="main"))
        {
            istr<<"extern _ExitProcess@4\n";
            istr<<"push    0\n";
            istr<<"call    _ExitProcess@4\n";
        }
        else
        {
            //函数返回
            istr<<";leave\n";
            istr<<"mov esp, ebp\n";
            istr<<"pop ebp\n";
            istr<<"ret;\n";
            this->m_ebp = 0;
            this->m_esp = 0;
        }
    }
        break;
    case ICODE_TYPE_DEF_VAR:
    case ICODE_TYPE_DEF_VAR_TMP:
    {
        //此变量放入堆栈
        int var_byte_width = ((ic->m_bit_width+31)/32)*4;
        m_func_stack.push_back(ic);
        m_func_stack_byte_width.push_back(var_byte_width);
        ic->m_var_info.m_type=X86_VAR_TYPE_STACK;
        for(int i=0;i<var_byte_width;i+=4){
            istr<<"push dword 0; var:"<< ic->name << "\n";
        }
    }
        break;
    case ICODE_TYPE_ASM:
    {
        istr<<";in_asm\n";
        istr<<ic->name<<"\n";
    }
        break;

    }


    return 0;
}

int code_gen_x86::process_one_icode_end(icode *ic, void *user_data, icode *iparent)
{
    std::stringstream &istr = *(std::stringstream *)user_data;

    if(ic->m_type==ICODE_TYPE_FUNC)
    {
        istr<<";leave\n";
        istr<<"mov esp, ebp\n";
        istr<<"pop ebp\n";
        istr<<"ret;\n";
        this->m_ebp = 0;
        this->m_esp = 0;
    }
    return 0;
}

