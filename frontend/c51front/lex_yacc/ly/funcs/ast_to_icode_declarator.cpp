
/***************************************************************************
 *
 *
 * 输入：tdefs need_result=1
 * 输出： block a->result -->ICODE_TYPE_SYM_REF 如果是未定义的变量，则result=NULL. 如果已经定义
 *         则result为定义的变量
 *
 *
 *declarator
    : pointer direct_declarator
    | direct_declarator
    ;

direct_declarator_base
                : identifier
                | '(' declarator ')'
                ;


direct_declarator_array
                    : direct_declarator_base
                     | direct_declarator_array '[' ']'
                    | direct_declarator_array '[' '*' ']'
                    | direct_declarator_array '[' STATIC type_qualifier_list assignment_expression ']'
                    | direct_declarator_array '[' STATIC assignment_expression ']'
                    | direct_declarator_array '[' type_qualifier_list '*' ']'
                    | direct_declarator_array '[' type_qualifier_list STATIC assignment_expression ']'
                    | direct_declarator_array '[' type_qualifier_list assignment_expression ']'
                    | direct_declarator_array '[' type_qualifier_list ']'
                    | direct_declarator_array '[' assignment_expression ']'
                    ;


direct_declarator
    : direct_declarator_function
    ;

pointer
    : '*' type_qualifier_list pointer
    | '*' type_qualifier_list
    | '*' pointer
    | '*'
    ;

    declarator parent:
    // init_declarator--> declarator '=' initializer
    // init_declarator--> declarator
    // struct_declarator--> declarator ':' constant_expression
    // struct_declarator--> declarator
    // direct_declarator_base--> '(' declarator ')'
    // parameter_declaration--> declaration_specifiers declarator
    // function_definition--> declaration_specifiers declarator declaration_list compound_statement
    // function_definition--> declaration_specifiers declarator compound_statement
 *
 *
 * ************************************************************************/

#include "ast_to_icode_declarator.h"

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



namespace NS_C512IR{




/// 指针变量在a->result中
///
class icode *  func_IAN_DECLARATOR_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3001-declarator->pointer direct_declarator
    //parent:
    // init_declarator--> declarator '=' initializer
    // init_declarator--> declarator
    // struct_declarator--> declarator ':' constant_expression
    // struct_declarator--> declarator
    // direct_declarator_base--> '(' declarator ')'
    // parameter_declaration--> declaration_specifiers declarator
    // function_definition--> declaration_specifiers declarator declaration_list compound_statement
    // function_definition--> declaration_specifiers declarator compound_statement
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    //int *a; pointer="*" direct_declarator=a;

    token_defs *pointer =  tdefs->m_tk_elems[0];
    token_defs *direct_declarator = tdefs->m_tk_elems[1];

    /// direct->result是变量。
    icode * direct = pcompi->ast_to_icode(direct_declarator, 1);
    //icode * pointer_ic = pcompi->ast_to_icode(pointer);


    /// 此处给direct变量，添加指针属性
    pcompi->ast_to_icode(pointer, 0, pcompi->get_def_var( direct->result));
    //pcompi->pointer_parse(pointer, pcompi->get_def_var( direct->result));


    //变量引用
    /// 20208.23 此处不能添加：pcompi->new_ref_icode。 否则会导致错误
    /// 因为变量没有还定义，此处使用了ref内容保存变量内容
    a->result = direct->result;
    a->merge_icode(direct);

    return a;
}
class icode *  func_IAN_DECLARATOR_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3002-declarator->direct_declarator
    //parent:
    // init_declarator--> declarator '=' initializer
    // init_declarator--> declarator
    // struct_declarator--> declarator ':' constant_expression
    // struct_declarator--> declarator
    // direct_declarator_base--> '(' declarator ')'
    // parameter_declaration--> declaration_specifiers declarator
    // function_definition--> declaration_specifiers declarator declaration_list compound_statement
    // function_definition--> declaration_specifiers declarator compound_statement
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}



///
/// \brief func_IAN_POINTER_1 函数只修改result_ic。 is_ptr++
/// \param pcompi
/// \param tdefs
/// \param need_result_icode
/// \param result_ic
/// \return NULL
///
class icode *  func_IAN_POINTER_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3701-pointer->'*' type_qualifier_list pointer
    //parent:
    // declarator--> pointer direct_declarator
    // pointer--> '*' type_qualifier_list pointer
    // pointer--> '*' pointer
    // abstract_declarator--> pointer direct_abstract_declarator
    // abstract_declarator--> pointer



    assert(need_result_icode==0);
    result_ic->is_ptr++;
    token_defs *type_qualifier_list=tdefs->m_tk_elems[1];
    token_defs *pointer=tdefs->m_tk_elems[2];


    pcompi->ast_to_icode(type_qualifier_list, need_result_icode, result_ic);
    pcompi->ast_to_icode(pointer, need_result_icode, result_ic);
    return NULL;


    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *'*'=tdefs->m_tk_elems[0];
    //token_defs *type_qualifier_list=tdefs->m_tk_elems[1];
    //token_defs *pointer=tdefs->m_tk_elems[2];
    //icode *'*'_ic=pcompi->ast_to_icode('*');
    //icode *type_qualifier_list_ic=pcompi->ast_to_icode(type_qualifier_list);
    //icode *pointer_ic=pcompi->ast_to_icode(pointer);
    //a->merge_icode('*'_ic);
    //a->merge_icode(type_qualifier_list_ic);
    //a->merge_icode(pointer_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_POINTER_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3702-pointer->'*' type_qualifier_list
    //parent:
    // declarator--> pointer direct_declarator
    // pointer--> '*' type_qualifier_list pointer
    // pointer--> '*' pointer
    // abstract_declarator--> pointer direct_abstract_declarator
    // abstract_declarator--> pointer

    //icode *a = pcompi->new_icode();
    //a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *'*'=tdefs->m_tk_elems[0];
    //icode *'*'_ic=pcompi->ast_to_icode('*');
    //icode *type_qualifier_list_ic=pcompi->ast_to_icode(type_qualifier_list);
    //a->merge_icode('*'_ic);
    //a->merge_icode(type_qualifier_list_ic);


    assert(need_result_icode==0);
    result_ic->is_ptr++;
    token_defs *type_qualifier_list=tdefs->m_tk_elems[1];

    pcompi->ast_to_icode(type_qualifier_list, need_result_icode, result_ic);
    return NULL;
}
class icode *  func_IAN_POINTER_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3703-pointer->'*' pointer
    //parent:
    // declarator--> pointer direct_declarator
    // pointer--> '*' type_qualifier_list pointer
    // pointer--> '*' pointer
    // abstract_declarator--> pointer direct_abstract_declarator
    // abstract_declarator--> pointer

    assert(need_result_icode==0);
    result_ic->is_ptr++;

    pcompi->ast_to_icode(tdefs->m_tk_elems[1], need_result_icode, result_ic);
    return NULL;

    //icode *a = pcompi->new_icode();
    //a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *'*'=tdefs->m_tk_elems[0];
    //token_defs *pointer=tdefs->m_tk_elems[1];
    //icode *'*'_ic=pcompi->ast_to_icode('*');
    //icode *pointer_ic=pcompi->ast_to_icode(pointer);
    //a->merge_icode('*'_ic);
    //a->merge_icode(pointer_ic);
    //assert(0);
    //return a;
}
class icode *  func_IAN_POINTER_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3704-pointer->'*'
    //parent:
    // declarator--> pointer direct_declarator
    // pointer--> '*' type_qualifier_list pointer
    // pointer--> '*' pointer
    // abstract_declarator--> pointer direct_abstract_declarator
    // abstract_declarator--> pointer

    assert(need_result_icode==0);
    result_ic->is_ptr++;

    return NULL;

    /// 2020.12.5 此处应解析pointer的 *。 生成变量？ /todo
    //return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}


class icode *  func_IAN_DIRECT_DECLARATOR_BASE_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3101-direct_declarator_base->identifier
    //parent:
    // direct_declarator_array--> direct_declarator_base
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_DIRECT_DECLARATOR_BASE_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3102-direct_declarator_base->'(' declarator ')'
    //parent:
    // direct_declarator_array--> direct_declarator_base
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *'('=tdefs->m_tk_elems[0];
    //token_defs *declarator=tdefs->m_tk_elems[1];
    //token_defs *')'=tdefs->m_tk_elems[2];
    //icode *'('_ic=pcompi->ast_to_icode('(');
    //icode *declarator_ic=pcompi->ast_to_icode(declarator);
    //icode *')'_ic=pcompi->ast_to_icode(')');
    //a->merge_icode('('_ic);
    //a->merge_icode(declarator_ic);
    //a->merge_icode(')'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_DIRECT_DECLARATOR_ARRAY_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3201-direct_declarator_array->direct_declarator_base
    //parent:
    // direct_declarator_array--> direct_declarator_array '[' ']'
    // direct_declarator_array--> direct_declarator_array '[' '*' ']'
    // direct_declarator_array--> direct_declarator_array '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' STATIC assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list '*' ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list ']'
    // direct_declarator_array--> direct_declarator_array '[' assignment_expression ']'
    // direct_declarator_function1--> direct_declarator_array
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_DIRECT_DECLARATOR_ARRAY_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3202-direct_declarator_array->direct_declarator_array '[' ']'
    //parent:
    // direct_declarator_array--> direct_declarator_array '[' ']'
    // direct_declarator_array--> direct_declarator_array '[' '*' ']'
    // direct_declarator_array--> direct_declarator_array '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' STATIC assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list '*' ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list ']'
    // direct_declarator_array--> direct_declarator_array '[' assignment_expression ']'
    // direct_declarator_function1--> direct_declarator_array
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    /// int a[]={1,2,3};
    /// 数组大小是由后面的初始值决定。
    ///
    /// 此处生成0大小的数组，后期通过后面初始进行修改

    token_defs *direct_declarator_array =  tdefs->m_tk_elems[0];

    icode * direct_array = pcompi->ast_to_icode(direct_declarator_array, 1);
    icode * expr = pcompi->new_icode(ICODE_TYPE_I_CONST);
    expr->num = 0;

    ///-----------------
    //2021.1.12 数组，添加类型到in_ptr_type
    //direct_array->result->m_in_ptr_type = pcompi->new_icode(* direct_array->result);
    // 此处添加无用，需要在new_var函数中添加。new_var函数中已经添加。
    // direct_array->result 是一个ref. result=NULL.代表未定义的变量
    // 需要在  declarator 中用 new_var定义
    ///-----------------


    //变量引用
    a->result = direct_array->result;
    a->result->is_array++;
    a->result->array_cnt.push_back(expr);
    a->merge_icode(direct_array);

    return a;
}
class icode *  func_IAN_DIRECT_DECLARATOR_ARRAY_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3203-direct_declarator_array->direct_declarator_array '[' '*' ']'
    //parent:
    // direct_declarator_array--> direct_declarator_array '[' ']'
    // direct_declarator_array--> direct_declarator_array '[' '*' ']'
    // direct_declarator_array--> direct_declarator_array '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' STATIC assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list '*' ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list ']'
    // direct_declarator_array--> direct_declarator_array '[' assignment_expression ']'
    // direct_declarator_function1--> direct_declarator_array
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *direct_declarator_array=tdefs->m_tk_elems[0];
    //token_defs *'['=tdefs->m_tk_elems[1];
    //token_defs *'*'=tdefs->m_tk_elems[2];
    //token_defs *']'=tdefs->m_tk_elems[3];
    //icode *direct_declarator_array_ic=pcompi->ast_to_icode(direct_declarator_array);
    //icode *'['_ic=pcompi->ast_to_icode('[');
    //icode *'*'_ic=pcompi->ast_to_icode('*');
    //icode *']'_ic=pcompi->ast_to_icode(']');
    //a->merge_icode(direct_declarator_array_ic);
    //a->merge_icode('['_ic);
    //a->merge_icode('*'_ic);
    //a->merge_icode(']'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_DIRECT_DECLARATOR_ARRAY_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3204-direct_declarator_array->direct_declarator_array '[' STATIC type_qualifier_list assignment_expression ']'
    //parent:
    // direct_declarator_array--> direct_declarator_array '[' ']'
    // direct_declarator_array--> direct_declarator_array '[' '*' ']'
    // direct_declarator_array--> direct_declarator_array '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' STATIC assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list '*' ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list ']'
    // direct_declarator_array--> direct_declarator_array '[' assignment_expression ']'
    // direct_declarator_function1--> direct_declarator_array
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *direct_declarator_array=tdefs->m_tk_elems[0];
    //token_defs *'['=tdefs->m_tk_elems[1];
    //token_defs *STATIC=tdefs->m_tk_elems[2];
    //token_defs *type_qualifier_list=tdefs->m_tk_elems[3];
    //token_defs *assignment_expression=tdefs->m_tk_elems[4];
    //token_defs *']'=tdefs->m_tk_elems[5];
    //icode *direct_declarator_array_ic=pcompi->ast_to_icode(direct_declarator_array);
    //icode *'['_ic=pcompi->ast_to_icode('[');
    //icode *STATIC_ic=pcompi->ast_to_icode(STATIC);
    //icode *type_qualifier_list_ic=pcompi->ast_to_icode(type_qualifier_list);
    //icode *assignment_expression_ic=pcompi->ast_to_icode(assignment_expression);
    //icode *']'_ic=pcompi->ast_to_icode(']');
    //a->merge_icode(direct_declarator_array_ic);
    //a->merge_icode('['_ic);
    //a->merge_icode(STATIC_ic);
    //a->merge_icode(type_qualifier_list_ic);
    //a->merge_icode(assignment_expression_ic);
    //a->merge_icode(']'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_DIRECT_DECLARATOR_ARRAY_5(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3205-direct_declarator_array->direct_declarator_array '[' STATIC assignment_expression ']'
    //parent:
    // direct_declarator_array--> direct_declarator_array '[' ']'
    // direct_declarator_array--> direct_declarator_array '[' '*' ']'
    // direct_declarator_array--> direct_declarator_array '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' STATIC assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list '*' ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list ']'
    // direct_declarator_array--> direct_declarator_array '[' assignment_expression ']'
    // direct_declarator_function1--> direct_declarator_array
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *direct_declarator_array=tdefs->m_tk_elems[0];
    //token_defs *'['=tdefs->m_tk_elems[1];
    //token_defs *STATIC=tdefs->m_tk_elems[2];
    //token_defs *assignment_expression=tdefs->m_tk_elems[3];
    //token_defs *']'=tdefs->m_tk_elems[4];
    //icode *direct_declarator_array_ic=pcompi->ast_to_icode(direct_declarator_array);
    //icode *'['_ic=pcompi->ast_to_icode('[');
    //icode *STATIC_ic=pcompi->ast_to_icode(STATIC);
    //icode *assignment_expression_ic=pcompi->ast_to_icode(assignment_expression);
    //icode *']'_ic=pcompi->ast_to_icode(']');
    //a->merge_icode(direct_declarator_array_ic);
    //a->merge_icode('['_ic);
    //a->merge_icode(STATIC_ic);
    //a->merge_icode(assignment_expression_ic);
    //a->merge_icode(']'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_DIRECT_DECLARATOR_ARRAY_6(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3206-direct_declarator_array->direct_declarator_array '[' type_qualifier_list '*' ']'
    //parent:
    // direct_declarator_array--> direct_declarator_array '[' ']'
    // direct_declarator_array--> direct_declarator_array '[' '*' ']'
    // direct_declarator_array--> direct_declarator_array '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' STATIC assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list '*' ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list ']'
    // direct_declarator_array--> direct_declarator_array '[' assignment_expression ']'
    // direct_declarator_function1--> direct_declarator_array
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *direct_declarator_array=tdefs->m_tk_elems[0];
    //token_defs *'['=tdefs->m_tk_elems[1];
    //token_defs *type_qualifier_list=tdefs->m_tk_elems[2];
    //token_defs *'*'=tdefs->m_tk_elems[3];
    //token_defs *']'=tdefs->m_tk_elems[4];
    //icode *direct_declarator_array_ic=pcompi->ast_to_icode(direct_declarator_array);
    //icode *'['_ic=pcompi->ast_to_icode('[');
    //icode *type_qualifier_list_ic=pcompi->ast_to_icode(type_qualifier_list);
    //icode *'*'_ic=pcompi->ast_to_icode('*');
    //icode *']'_ic=pcompi->ast_to_icode(']');
    //a->merge_icode(direct_declarator_array_ic);
    //a->merge_icode('['_ic);
    //a->merge_icode(type_qualifier_list_ic);
    //a->merge_icode('*'_ic);
    //a->merge_icode(']'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_DIRECT_DECLARATOR_ARRAY_7(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3207-direct_declarator_array->direct_declarator_array '[' type_qualifier_list STATIC assignment_expression ']'
    //parent:
    // direct_declarator_array--> direct_declarator_array '[' ']'
    // direct_declarator_array--> direct_declarator_array '[' '*' ']'
    // direct_declarator_array--> direct_declarator_array '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' STATIC assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list '*' ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list ']'
    // direct_declarator_array--> direct_declarator_array '[' assignment_expression ']'
    // direct_declarator_function1--> direct_declarator_array
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *direct_declarator_array=tdefs->m_tk_elems[0];
    //token_defs *'['=tdefs->m_tk_elems[1];
    //token_defs *type_qualifier_list=tdefs->m_tk_elems[2];
    //token_defs *STATIC=tdefs->m_tk_elems[3];
    //token_defs *assignment_expression=tdefs->m_tk_elems[4];
    //token_defs *']'=tdefs->m_tk_elems[5];
    //icode *direct_declarator_array_ic=pcompi->ast_to_icode(direct_declarator_array);
    //icode *'['_ic=pcompi->ast_to_icode('[');
    //icode *type_qualifier_list_ic=pcompi->ast_to_icode(type_qualifier_list);
    //icode *STATIC_ic=pcompi->ast_to_icode(STATIC);
    //icode *assignment_expression_ic=pcompi->ast_to_icode(assignment_expression);
    //icode *']'_ic=pcompi->ast_to_icode(']');
    //a->merge_icode(direct_declarator_array_ic);
    //a->merge_icode('['_ic);
    //a->merge_icode(type_qualifier_list_ic);
    //a->merge_icode(STATIC_ic);
    //a->merge_icode(assignment_expression_ic);
    //a->merge_icode(']'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_DIRECT_DECLARATOR_ARRAY_8(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3208-direct_declarator_array->direct_declarator_array '[' type_qualifier_list assignment_expression ']'
    //parent:
    // direct_declarator_array--> direct_declarator_array '[' ']'
    // direct_declarator_array--> direct_declarator_array '[' '*' ']'
    // direct_declarator_array--> direct_declarator_array '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' STATIC assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list '*' ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list ']'
    // direct_declarator_array--> direct_declarator_array '[' assignment_expression ']'
    // direct_declarator_function1--> direct_declarator_array
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *direct_declarator_array=tdefs->m_tk_elems[0];
    //token_defs *'['=tdefs->m_tk_elems[1];
    //token_defs *type_qualifier_list=tdefs->m_tk_elems[2];
    //token_defs *assignment_expression=tdefs->m_tk_elems[3];
    //token_defs *']'=tdefs->m_tk_elems[4];
    //icode *direct_declarator_array_ic=pcompi->ast_to_icode(direct_declarator_array);
    //icode *'['_ic=pcompi->ast_to_icode('[');
    //icode *type_qualifier_list_ic=pcompi->ast_to_icode(type_qualifier_list);
    //icode *assignment_expression_ic=pcompi->ast_to_icode(assignment_expression);
    //icode *']'_ic=pcompi->ast_to_icode(']');
    //a->merge_icode(direct_declarator_array_ic);
    //a->merge_icode('['_ic);
    //a->merge_icode(type_qualifier_list_ic);
    //a->merge_icode(assignment_expression_ic);
    //a->merge_icode(']'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_DIRECT_DECLARATOR_ARRAY_9(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3209-direct_declarator_array->direct_declarator_array '[' type_qualifier_list ']'
    //parent:
    // direct_declarator_array--> direct_declarator_array '[' ']'
    // direct_declarator_array--> direct_declarator_array '[' '*' ']'
    // direct_declarator_array--> direct_declarator_array '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' STATIC assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list '*' ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list ']'
    // direct_declarator_array--> direct_declarator_array '[' assignment_expression ']'
    // direct_declarator_function1--> direct_declarator_array
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *direct_declarator_array=tdefs->m_tk_elems[0];
    //token_defs *'['=tdefs->m_tk_elems[1];
    //token_defs *type_qualifier_list=tdefs->m_tk_elems[2];
    //token_defs *']'=tdefs->m_tk_elems[3];
    //icode *direct_declarator_array_ic=pcompi->ast_to_icode(direct_declarator_array);
    //icode *'['_ic=pcompi->ast_to_icode('[');
    //icode *type_qualifier_list_ic=pcompi->ast_to_icode(type_qualifier_list);
    //icode *']'_ic=pcompi->ast_to_icode(']');
    //a->merge_icode(direct_declarator_array_ic);
    //a->merge_icode('['_ic);
    //a->merge_icode(type_qualifier_list_ic);
    //a->merge_icode(']'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_DIRECT_DECLARATOR_ARRAY_10(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x320a-direct_declarator_array->direct_declarator_array '[' assignment_expression ']'
    //parent:
    // direct_declarator_array--> direct_declarator_array '[' ']'
    // direct_declarator_array--> direct_declarator_array '[' '*' ']'
    // direct_declarator_array--> direct_declarator_array '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' STATIC assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list '*' ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list ']'
    // direct_declarator_array--> direct_declarator_array '[' assignment_expression ']'
    // direct_declarator_function1--> direct_declarator_array
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    /// int a[10];
    /// int a[10]={1,2,3};
    token_defs *direct_declarator_array =  tdefs->m_tk_elems[0];
    token_defs *assignment_expression = tdefs->m_tk_elems[2];

    icode * direct_array = pcompi->ast_to_icode(direct_declarator_array, 1);
    icode * expr = pcompi->ast_to_icode(assignment_expression, 1);


    ///=================
    //2021.1.12 数组，添加类型到in_ptr_type
    //direct_array->result->m_in_ptr_type = pcompi->new_icode(* direct_array->result);
    // 此处添加无用，需要在new_var函数中添加。new_var函数中已经添加。
    // direct_array->result 是一个ref. result=NULL.代表未定义的变量
    // 需要在  declarator 中用 new_var定义
    ///=================

    a->result = (pcompi->new_ref_icode( direct_array->result));
    a->result->is_array++;
    a->result->array_cnt.push_back(expr->result);
    a->merge_icode(direct_array);
    a->merge_icode(expr);

    return a;
}


class icode *  func_IAN_DIRECT_DECLARATOR_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3601-direct_declarator->direct_declarator_function
    //parent:
    // declarator--> pointer direct_declarator
    // declarator--> direct_declarator
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}







}//namespace end

