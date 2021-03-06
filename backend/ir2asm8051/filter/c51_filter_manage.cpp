#include "c51_filter_manage.h"
#include "icode_high_to_low.h"

c51_filter_manage::c51_filter_manage()
{
}

void c51_filter_manage::do_filter(icodes *ics)
{

    icode_high_to_low m_high_low;
    m_high_low.m_collect_var_init_code_func = "__init_global_var";

    m_high_low.m_array_to_ptr = 1;
    m_high_low.m_negative_func = "_sys_negative";
    m_high_low.m_float_to_int_func = "_sys_castf";
    m_high_low.m_int_to_float_func = "_sys_fcast";

    m_high_low.m_float_add_func = "_sys_fpadd";
    m_high_low.m_float_sub_func = "_sys_fpsub";
    m_high_low.m_float_mul_func = "_sys_fpmul";
    m_high_low.m_float_div_func = "_sys_fpdiv";

    m_high_low.m_i16_mul_func = "_sys_imul_byte2";
    m_high_low.m_i32_mul_func = "_sys_lmul_byte4";

    m_high_low.m_i16_idiv_func = "_sys_idiv_byte2";
    m_high_low.m_u16_udiv_func = "_sys_udiv_byte2";
    m_high_low.m_i32_idiv_func  = "_sys_ldiv_byte4";
    m_high_low.m_u32_udiv_func  = "_sys_uldiv_byte4";

    m_high_low.m_copy_func = "__byte_copy";

    m_high_low.m_inline_ext = 1;
    m_high_low.m_remove_dead = 1;



    m_high_low.execute(ics);

#if 0
    icode * m_top_icodes = ics->m_top_icodes;

    icode_tmp_var_opt1 tmp_var_opt1;
    tmp_var_opt1.execute(ics);


    icode_const_folder m_const_folder;
    m_const_folder.execute(ics);



    /// 0-未实现检查
    icode_unresolved unresolved_check;
    unresolved_check.pcompi = ics;
    unresolved_check.process_topcode(m_top_icodes);


    /// 1- 将全局变量的初始化收集到函数中。作为第一个运行和编译的函数
    icode_global_func m_global_func;
    m_global_func.execute(ics);


    /// 3-将函数的参数寄存器指定属性，转移为变量的寄存器属性
    icode_func_var_register func_var_register;
    func_var_register.pcompi = ics;
    func_var_register.process_topcode(m_top_icodes);


    /// 10-指针计算
    icode_ptr_calc ptr_calc;
    ptr_calc.pcompi = ics;
    ptr_calc.process_topcode(m_top_icodes);


    icode_ptr_in_calc ptr_in_calc;
    ptr_in_calc.execute(ics);


    /// 6-正号翻译，将正号翻译转移为=号. negative翻译为函数 a=+3;---> right=3;result=a; opr=+.
    /// 翻译需要在常量折叠之后，因为负号 会被翻译为函数调用，例如-3 --》func_negative(3); 就没法常量折叠了
    icode_positive_opr positive_opr;
    positive_opr.pcompi = ics;
    positive_opr.process_topcode(m_top_icodes);


    /// 浮点数和整数的混合运算，需要先将整数转为浮点数
    /// 浮点数赋值给整数，需要先将浮点数转为整数
    icode_float_cast float_cast;
    float_cast.execute(ics);




    /// 8-浮点数计算函数的使用
    /// 此处使用完成系统函数后，才能将dead code删除
    /// 否则，就会将需要的函数删除
    /// 浮点数运算转为函数运算.
    /// 包含：浮点数的+-*/ 。 浮点&整形的隐式转换. int/long的*/运算
    ///
    icode_float_func_opr float_func_opr;
    float_func_opr.pcompi = ics;
    float_func_opr.process_topcode(m_top_icodes);
    int clean_up_folder_tmp=1;
    float_func_opr.process_topcode(m_top_icodes, &clean_up_folder_tmp);



    icode_ptr_copy ptr_copy;
    ptr_copy.pcompi = ics;
    ptr_copy.process_topcode(m_top_icodes);



    /// 7-将inline函数进行扩展到调用地点
    icode_inline inline_proc;
    inline_proc.pcompi = ics;
    inline_proc.process_topcode(m_top_icodes);

    /// 9-计算函数调用次数，去掉调用不到的函数
    icode_dead_func dead_func;
    dead_func.execute(ics);
#endif
}
