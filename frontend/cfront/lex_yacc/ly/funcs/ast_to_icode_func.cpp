/************************************
 *
 * 未实现：旧的函数声明： direct_declarator_function1 '(' identifier_list ')'
 *
 *
 *direct_declarator_function、
 *  输入：tdefs
 *  输出：a->result{ICODE_TYPE_FUNC}  返回的func有name,属性，参数列表在sub_ic中，其中sub_ic[0]是返回值的站位
 *
 * function_attribute:
 *  输入：tdefs result_ic
 *  输出：result_ic
 *
 *
 *
 *
 *
 *function_specifier
    : INLINE
    | NORETURN
    ;

function_attribute1
    :  USING constant_expression
    | REENTRANT
    | INTERRUPT constant_expression
    | REGPARAMS string
    ;

function_attribute2
                : function_attribute1
                | function_attribute1  function_attribute2
                ;
function_attribute
                    : function_attribute2
        ;

direct_declarator_function1
                        : direct_declarator_array
                        | direct_declarator_function1 '(' parameter_type_list ')'
                        | direct_declarator_function1 '(' ')'
                        | direct_declarator_function1 '(' identifier_list ')'
                        ;



direct_declarator_function2
                        : direct_declarator_function1
                        | direct_declarator_function1 function_attribute
                                                 ;
direct_declarator_function
                            : direct_declarator_function2
                            ;
 *
 *
 *
 *
 * ********/

#include "ast_to_icode_common.h"

#include "parser.h"
#include "comp_context_gen_defs.h"
#include <assert.h>
#include "icode.h"
#include "comp_context.h"
#include "token_defs.h"
#include "mylog.h"
#include "str2number.h"
using mylog::cerr;
using mylog::cout;


#include "ast_to_icode_func.h"



namespace NS_C2IR{



class icode *  func_IAN_FUNCTION_ATTRIBUTE1_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x5501-function_attribute1->USING constant_expression
    //parent:
    // function_attribute2--> function_attribute1
    // function_attribute2--> function_attribute1 function_attribute2

    if(result_ic==NULL)
    {
        icode *a = pcompi->new_icode();

        result_ic=a;
        a->m_type=ICODE_TYPE_DEF_VAR;
    }

    result_ic->is_using_group = 1;
    icode *num1  = pcompi->ast_to_icode(tdefs->m_tk_elems[1]);
    result_ic->m_using_group_num = num1->result->num;
    return result_ic;
}

class icode *  func_IAN_FUNCTION_ATTRIBUTE1_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x5502-function_attribute1->REENTRANT
    //parent:
    // function_attribute2--> function_attribute1
    // function_attribute2--> function_attribute1 function_attribute2
    //return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);

    if(result_ic==NULL)
    {
        icode *a = pcompi->new_icode();
        a->m_type=ICODE_TYPE_DEF_VAR;
        result_ic=a;
    }
    result_ic->is_reentrant = 1;
    return result_ic;
}

class icode *  func_IAN_FUNCTION_ATTRIBUTE1_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x5503-function_attribute1->INTERRUPT constant_expression
    //parent:
    // function_attribute2--> function_attribute1
    // function_attribute2--> function_attribute1 function_attribute2

    if(result_ic==NULL)
    {
        icode *a = pcompi->new_icode();
        a->m_type=ICODE_TYPE_DEF_VAR;
        result_ic=a;
    }
    result_ic->is_interrupt = 1;
    icode *num1  = pcompi->ast_to_icode(tdefs->m_tk_elems[1], 1);
    result_ic->m_interrupt_num = num1->result->num;
    return result_ic;
}

class icode *  func_IAN_FUNCTION_ATTRIBUTE1_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x5504-function_attribute1->REGPARAMS string
    //parent:
    // function_attribute2--> function_attribute1
    // function_attribute2--> function_attribute1 function_attribute2

    if(result_ic==NULL)
    {
        icode *a = pcompi->new_icode();
        a->m_type=ICODE_TYPE_DEF_VAR;
        result_ic=a;
    }
    result_ic->is_regparams = 1;


    ///str_ret->result_ic 为字符串引用
    icode * str_ret = pcompi->ast_to_icode(tdefs->m_tk_elems[1], 1);


    result_ic->m_reg_params_desc = pcompi->get_def_var(str_ret->result)->name;
    return result_ic;
}

class icode *  func_IAN_FUNCTION_ATTRIBUTE2_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x5601-function_attribute2->function_attribute1
    //parent:
    // function_attribute2--> function_attribute1 function_attribute2
    // function_attribute--> function_attribute2
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_FUNCTION_ATTRIBUTE2_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x5602-function_attribute2->function_attribute1 function_attribute2
    //parent:
    // function_attribute2--> function_attribute1 function_attribute2
    // function_attribute--> function_attribute2

    if(result_ic==NULL)
    {
        icode *a = pcompi->new_icode();
        a->m_type=ICODE_TYPE_DEF_VAR;
        result_ic=a;
    }

    pcompi->ast_to_icode(tdefs->m_tk_elems[0],0, result_ic);
    pcompi->ast_to_icode(tdefs->m_tk_elems[1],0, result_ic);
    return result_ic;
}

class icode *  func_IAN_FUNCTION_ATTRIBUTE_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x5701-function_attribute->function_attribute2
    //parent:
    // direct_declarator_function2--> direct_declarator_function1 function_attribute
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}

class icode *  func_IAN_DIRECT_DECLARATOR_FUNCTION1_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3301-direct_declarator_function1->direct_declarator_array
    //parent:
    // direct_declarator_function1--> direct_declarator_function1 '(' parameter_type_list ')'
    // direct_declarator_function1--> direct_declarator_function1 '(' ')'
    // direct_declarator_function1--> direct_declarator_function1 '(' identifier_list ')'
    // direct_declarator_function2--> direct_declarator_function1
    // direct_declarator_function2--> direct_declarator_function1 function_attribute
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}

class icode *  func_IAN_DIRECT_DECLARATOR_FUNCTION1_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3302-direct_declarator_function1->direct_declarator_function1 '(' parameter_type_list ')'
    //parent:
    // direct_declarator_function1--> direct_declarator_function1 '(' parameter_type_list ')'
    // direct_declarator_function1--> direct_declarator_function1 '(' ')'
    // direct_declarator_function1--> direct_declarator_function1 '(' identifier_list ')'
    // direct_declarator_function2--> direct_declarator_function1
    // direct_declarator_function2--> direct_declarator_function1 function_attribute
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    a->name = tdefs->m_tk_elems[0]->val_str;

    a->result = pcompi->new_icode();
    a->result->m_type=ICODE_TYPE_FUNC;
    a->result->name = a->name;

    ///添加返回值
    /// 现在无法确定返回值类型，所以只是放一个空的站位
    a->result->sub_icode.push_back(pcompi->new_icode());
    a->result->merge_icode(pcompi->ast_to_icode(tdefs->m_tk_elems[2]));

    ///2020.7.30 返回值类型修改：
    /// 原来是a中直接是sub_ic包含参数。现在改为添加到result中


    return a;
}

class icode *  func_IAN_DIRECT_DECLARATOR_FUNCTION1_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3303-direct_declarator_function1->direct_declarator_function1 '(' ')'
    //parent:
    // direct_declarator_function1--> direct_declarator_function1 '(' parameter_type_list ')'
    // direct_declarator_function1--> direct_declarator_function1 '(' ')'
    // direct_declarator_function1--> direct_declarator_function1 '(' identifier_list ')'
    // direct_declarator_function2--> direct_declarator_function1
    // direct_declarator_function2--> direct_declarator_function1 function_attribute
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;


    ///这是一个声明，此处要说明是一个函数？
    ///
    ///

    ///是否定义，不在此处判断，而是在type_specifier declarator时判断。
#if 0
    sym* s = pcompi->find_symbol(tdefs->m_tk_elems[0]->val_str);
    if(s==NULL)
    {
    }
    else
    {
    }
#endif
    //没有提前定义此函数
    //extern?



    a->name = tdefs->m_tk_elems[0]->val_str;

    a->result = pcompi->new_icode();
    a->result->m_type=ICODE_TYPE_FUNC;
    a->result->name = a->name;
    ///添加返回值
    /// 现在无法确定返回值类型，所以只是放一个空的站位
    a->result->sub_icode.push_back(pcompi->new_icode());

    return a;
}

class icode *  func_IAN_DIRECT_DECLARATOR_FUNCTION1_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3304-direct_declarator_function1->direct_declarator_function1 '(' identifier_list ')'
    //parent:
    // direct_declarator_function1--> direct_declarator_function1 '(' parameter_type_list ')'
    // direct_declarator_function1--> direct_declarator_function1 '(' ')'
    // direct_declarator_function1--> direct_declarator_function1 '(' identifier_list ')'
    // direct_declarator_function2--> direct_declarator_function1
    // direct_declarator_function2--> direct_declarator_function1 function_attribute
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *direct_declarator_function1=tdefs->m_tk_elems[0];
    //token_defs *'('=tdefs->m_tk_elems[1];
    //token_defs *identifier_list=tdefs->m_tk_elems[2];
    //token_defs *')'=tdefs->m_tk_elems[3];
    //icode *direct_declarator_function1_ic=pcompi->ast_to_icode(direct_declarator_function1);
    //icode *'('_ic=pcompi->ast_to_icode('(');
    //icode *identifier_list_ic=pcompi->ast_to_icode(identifier_list);
    //icode *')'_ic=pcompi->ast_to_icode(')');
    //a->merge_icode(direct_declarator_function1_ic);
    //a->merge_icode('('_ic);
    //a->merge_icode(identifier_list_ic);
    //a->merge_icode(')'_ic);
    assert(0);
    return a;
}

class icode *  func_IAN_DIRECT_DECLARATOR_FUNCTION2_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3401-direct_declarator_function2->direct_declarator_function1
    //parent:
    // direct_declarator_function--> direct_declarator_function2
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}

class icode *  func_IAN_DIRECT_DECLARATOR_FUNCTION2_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3402-direct_declarator_function2->direct_declarator_function1 function_attribute
    //parent:
    // direct_declarator_function--> direct_declarator_function2

    token_defs *fi = tdefs->m_tk_elems[0];
    token_defs *fi_attr = tdefs->m_tk_elems[1];
    icode * fi_ic = pcompi->ast_to_icode(fi, 1);
    pcompi->ast_to_icode(fi_attr, 0, fi_ic->result);

    return fi_ic;

}

class icode *  func_IAN_DIRECT_DECLARATOR_FUNCTION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3501-direct_declarator_function->direct_declarator_function2
    //parent:
    // direct_declarator--> direct_declarator_function
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}

}//namespace end
