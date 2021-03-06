#ifndef ICODE_HIGH_TO_LOW_H
#define ICODE_HIGH_TO_LOW_H

#include "icodes.h"

/// 将高级ir转为低级ir
///
class icode_high_to_low
{
public:
    icode_high_to_low();

    int execute(icodes* ics);


    ///将全局变量的初始化代码放到一个函数中。
    /// 如果此函数名称为空，则不作此操作
    std::string m_collect_var_init_code_func;

    ///将数组的读取，改为计算和指针指向内容读写
    int m_array_to_ptr;

    std::string m_negative_func;//_sys_negative

    std::string m_float_to_int_func;
    std::string m_int_to_float_func;


    ///----------------
    std::string m_float_add_func;
    std::string m_float_sub_func;
    std::string m_float_mul_func;
    std::string m_float_div_func;

    std::string m_i16_mul_func;//_sys_imul_byte2
    std::string m_i32_mul_func;//
    std::string m_i32_div_func;//
    std::string m_i16_idiv_func;//
    std::string m_u16_udiv_func;//
    std::string m_i32_idiv_func;//
    std::string m_u32_udiv_func;//
    ///----------------


    std::string m_copy_func;
    int m_inline_ext;
    int m_remove_dead;



};

#endif // ICODE_HIGH_TO_LOW_H
