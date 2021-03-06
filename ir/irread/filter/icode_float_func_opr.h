#ifndef ICODE_FLOAT_FUNC_OPR_H
#define ICODE_FLOAT_FUNC_OPR_H

#include <vector>
#include <map>

#include "icode_visitor.h"

///
/// \brief The icode_float_func_opr class
/// 浮点数运算转为函数运算.
/// 包含：浮点数的+-*/ 。 浮点&整形的隐式转换. int/long的*/%运算
///
///
/// float 变量，如果是对float变量的操作，都通过函数进行
///
class icode_float_func_opr : public icode_visitor
{
public:
    icode_float_func_opr();


    virtual int process_topcode(class icode *top_ic, void *user_data=NULL, class icode *iparent=NULL);
    virtual int process_one_icode(class icode *ic, std::vector<class icode *> &parent, int index, void *user_data, class icode *iparent);


    int second_cleanup(std::vector<icode *> &top_icodes);


    int opr_1_func_ex(std::string func_name, class icode *ic, std::vector<class icode *> &parent, int index);
    int opr_1_func_ex_assign(std::string func_name, class icode *ic, std::vector<class icode *> &parent, int index);



    /// 将函数功能 和参数分离出来，3个算符 * / % 改为3个函数
    /// 1说明被处理。0 说明未处理

    int process_imul(icode *ic, std::vector<icode *> &parent, int index);
    int process_idiv(icode *ic, std::vector<icode *> &parent, int index);
    int process_imod(icode *ic, std::vector<icode *> &parent, int index);

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
};

#endif // ICODE_FLOAT_FUNC_OPR_H

