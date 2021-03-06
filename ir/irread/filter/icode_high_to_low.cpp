#include "icode_high_to_low.h"

#include "icode_global_func.h"
#include "icode_ptr_calc.h"
#include "icode_collect_str.h"
#include "icode_unresolved.h"
#include "icode_inline.h"
#include "icode_ref_number.h"
#include "icode_const_folder.h"
#include "icode_dead_func.h"
#include "icode_float_func_opr.h"
#include "icode_func_var_register.h"
#include "icode_positive_opr.h"
#include "icode_float_cast.h"
#include "icode_ptr_copy.h"
#include "icode_var_scope.h"
#include "icode_merge_same_number.h"
#include "icode_renumber.h"
#include "icode_sym_rebuild.h"
#include "icode_replace.h"
#include "icode_refresh_number_dict.h"
#include "icode_ptr_in_calc.h"
#include "icode_tmp_var_opt1.h"


icode_high_to_low::icode_high_to_low()
{
    m_array_to_ptr = 1;
    m_inline_ext = 1;
    m_remove_dead = 1;
}

int icode_high_to_low::execute(icodes *ics)
{
    icode * m_top_icodes = ics->m_top_icodes;

    ///临时变量去除
    icode_tmp_var_opt1 tmp_var_opt1;
    tmp_var_opt1.execute(ics);

    ///常量折叠
    icode_const_folder m_const_folder;
    m_const_folder.execute(ics);



    /// 0-未实现检查
    icode_unresolved unresolved_check;
    unresolved_check.pcompi = ics;
    unresolved_check.process_topcode(m_top_icodes);

    if(!m_collect_var_init_code_func.empty())
    {

        /// 1- 将全局变量的初始化收集到函数中。作为第一个运行和编译的函数
        icode_global_func m_global_func;
        m_global_func.g_INIT_FUNC_NAME = m_collect_var_init_code_func;
        m_global_func.execute(ics);
    }


    /// 3-将函数的参数寄存器指定属性，转移为变量的寄存器属性
    icode_func_var_register func_var_register;
    func_var_register.pcompi = ics;
    func_var_register.process_topcode(m_top_icodes);


    if(m_array_to_ptr)
    {
        /// 10-指针计算
        icode_ptr_calc ptr_calc;
        ptr_calc.pcompi = ics;
        ptr_calc.process_topcode(m_top_icodes);


        icode_ptr_in_calc ptr_in_calc;
        ptr_in_calc.execute(ics);
    }


    /// 6-正号翻译，将正号翻译转移为=号. negative翻译为函数 a=+3;---> right=3;result=a; opr=+.
    /// 翻译需要在常量折叠之后，因为负号 会被翻译为函数调用，例如-3 --》func_negative(3); 就没法常量折叠了
    icode_positive_opr positive_opr;
    positive_opr.m_negative_func = m_negative_func;
    positive_opr.pcompi = ics;
    positive_opr.process_topcode(m_top_icodes);


    if(!m_float_to_int_func.empty())
    {
        /// 浮点数和整数的混合运算，需要先将整数转为浮点数
        /// 浮点数赋值给整数，需要先将浮点数转为整数
        icode_float_cast float_cast;
        float_cast.m_float_to_int = m_float_to_int_func;
        float_cast.m_int_to_float = m_int_to_float_func;
        float_cast.execute(ics);
    }

    if(!m_float_add_func.empty())
    {

        /// 8-浮点数计算函数的使用
        /// 此处使用完成系统函数后，才能将dead code删除
        /// 否则，就会将需要的函数删除
        /// 浮点数运算转为函数运算.
        /// 包含：浮点数的+-*/ 。 浮点&整形的隐式转换. int/long的*/运算
        ///
        icode_float_func_opr float_func_opr;


        float_func_opr.m_float_add_func = m_float_add_func;
        float_func_opr.m_float_sub_func = m_float_sub_func;
        float_func_opr.m_float_mul_func = m_float_mul_func;
        float_func_opr.m_float_div_func  = m_float_div_func;

        float_func_opr.m_i16_mul_func = m_i16_mul_func;
        float_func_opr.m_i16_idiv_func = m_i16_idiv_func;
        float_func_opr.m_u16_udiv_func = m_u16_udiv_func;

        float_func_opr.m_i32_mul_func = m_i32_mul_func;
        float_func_opr.m_i32_idiv_func = m_i32_idiv_func;
        float_func_opr.m_u32_udiv_func = m_u32_udiv_func;

        float_func_opr.pcompi = ics;
        float_func_opr.process_topcode(m_top_icodes);
        int clean_up_folder_tmp=1;
        float_func_opr.process_topcode(m_top_icodes, &clean_up_folder_tmp);
    }


    if(!m_copy_func.empty())
    {
        icode_ptr_copy ptr_copy;
        ptr_copy.m_copy_func = m_copy_func;
        ptr_copy.pcompi = ics;
        ptr_copy.process_topcode(m_top_icodes);
    }



    if(m_inline_ext)
    {
        /// 7-将inline函数进行扩展到调用地点
        icode_inline inline_proc;
        inline_proc.pcompi = ics;
        inline_proc.process_topcode(m_top_icodes);
    }

    if(m_remove_dead)
    {
        /// 9-计算函数调用次数，去掉调用不到的函数
        icode_dead_func dead_func;
        dead_func.execute(ics);
    }
    return 0;
}
