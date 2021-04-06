#include "../lex_yacc/parser.h"
#include "comp_context_gen_defs.h"
#include <assert.h>
#include "icode.h"
#include "comp_context.h"
#include "token_defs.h"
#include "mylog.h"
#include "str2number.h"
using mylog::cerr;
using mylog::cout;


namespace NS_C2IR{




class icode *  func_IAN_GENERIC_SELECTION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x401-generic_selection->GENERIC '(' assignment_expression ',' generic_assoc_list ')'
    //parent:
    // primary_expression--> generic_selection
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *GENERIC=tdefs->m_tk_elems[0];
    //token_defs *'('=tdefs->m_tk_elems[1];
    //token_defs *assignment_expression=tdefs->m_tk_elems[2];
    //token_defs *','=tdefs->m_tk_elems[3];
    //token_defs *generic_assoc_list=tdefs->m_tk_elems[4];
    //token_defs *')'=tdefs->m_tk_elems[5];
    //icode *GENERIC_ic=pcompi->ast_to_icode(GENERIC);
    //icode *'('_ic=pcompi->ast_to_icode('(');
    //icode *assignment_expression_ic=pcompi->ast_to_icode(assignment_expression);
    //icode *','_ic=pcompi->ast_to_icode(',');
    //icode *generic_assoc_list_ic=pcompi->ast_to_icode(generic_assoc_list);
    //icode *')'_ic=pcompi->ast_to_icode(')');
    //a->merge_icode(GENERIC_ic);
    //a->merge_icode('('_ic);
    //a->merge_icode(assignment_expression_ic);
    //a->merge_icode(','_ic);
    //a->merge_icode(generic_assoc_list_ic);
    //a->merge_icode(')'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_GENERIC_ASSOC_LIST_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x501-generic_assoc_list->generic_association
    //parent:
    // generic_selection--> GENERIC '(' assignment_expression ',' generic_assoc_list ')'
    // generic_assoc_list--> generic_assoc_list ',' generic_association
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_GENERIC_ASSOC_LIST_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x502-generic_assoc_list->generic_assoc_list ',' generic_association
    //parent:
    // generic_selection--> GENERIC '(' assignment_expression ',' generic_assoc_list ')'
    // generic_assoc_list--> generic_assoc_list ',' generic_association
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *generic_assoc_list=tdefs->m_tk_elems[0];
    //token_defs *','=tdefs->m_tk_elems[1];
    //token_defs *generic_association=tdefs->m_tk_elems[2];
    //icode *generic_assoc_list_ic=pcompi->ast_to_icode(generic_assoc_list);
    //icode *','_ic=pcompi->ast_to_icode(',');
    //icode *generic_association_ic=pcompi->ast_to_icode(generic_association);
    //a->merge_icode(generic_assoc_list_ic);
    //a->merge_icode(','_ic);
    //a->merge_icode(generic_association_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_GENERIC_ASSOCIATION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x601-generic_association->type_name ':' assignment_expression
    //parent:
    // generic_assoc_list--> generic_association
    // generic_assoc_list--> generic_assoc_list ',' generic_association
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *type_name=tdefs->m_tk_elems[0];
    //token_defs *':'=tdefs->m_tk_elems[1];
    //token_defs *assignment_expression=tdefs->m_tk_elems[2];
    //icode *type_name_ic=pcompi->ast_to_icode(type_name);
    //icode *':'_ic=pcompi->ast_to_icode(':');
    //icode *assignment_expression_ic=pcompi->ast_to_icode(assignment_expression);
    //a->merge_icode(type_name_ic);
    //a->merge_icode(':'_ic);
    //a->merge_icode(assignment_expression_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_GENERIC_ASSOCIATION_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x602-generic_association->DEFAULT ':' assignment_expression
    //parent:
    // generic_assoc_list--> generic_association
    // generic_assoc_list--> generic_assoc_list ',' generic_association
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *DEFAULT=tdefs->m_tk_elems[0];
    //token_defs *':'=tdefs->m_tk_elems[1];
    //token_defs *assignment_expression=tdefs->m_tk_elems[2];
    //icode *DEFAULT_ic=pcompi->ast_to_icode(DEFAULT);
    //icode *':'_ic=pcompi->ast_to_icode(':');
    //icode *assignment_expression_ic=pcompi->ast_to_icode(assignment_expression);
    //a->merge_icode(DEFAULT_ic);
    //a->merge_icode(':'_ic);
    //a->merge_icode(assignment_expression_ic);
    assert(0);
    return a;
}





class icode *  func_IAN_ATOMIC_TYPE_SPECIFIER_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2c01-atomic_type_specifier->ATOMIC '(' type_name ')'
    //parent:
    // type_specifier--> atomic_type_specifier
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *ATOMIC=tdefs->m_tk_elems[0];
    //token_defs *'('=tdefs->m_tk_elems[1];
    //token_defs *type_name=tdefs->m_tk_elems[2];
    //token_defs *')'=tdefs->m_tk_elems[3];
    //icode *ATOMIC_ic=pcompi->ast_to_icode(ATOMIC);
    //icode *'('_ic=pcompi->ast_to_icode('(');
    //icode *type_name_ic=pcompi->ast_to_icode(type_name);
    //icode *')'_ic=pcompi->ast_to_icode(')');
    //a->merge_icode(ATOMIC_ic);
    //a->merge_icode('('_ic);
    //a->merge_icode(type_name_ic);
    //a->merge_icode(')'_ic);
    assert(0);
    return a;
}



class icode *  func_IAN_TYPE_QUALIFIER_LIST_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3801-type_qualifier_list->type_qualifier
    //parent:
    // direct_declarator_array--> direct_declarator_array '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list '*' ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list ']'
    // pointer--> '*' type_qualifier_list pointer
    // pointer--> '*' type_qualifier_list
    // type_qualifier_list--> type_qualifier_list type_qualifier
    // direct_abstract_declarator--> '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_abstract_declarator--> '[' type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> '[' type_qualifier_list ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list ']'
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_QUALIFIER_LIST_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3802-type_qualifier_list->type_qualifier_list type_qualifier
    //parent:
    // direct_declarator_array--> direct_declarator_array '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list '*' ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list ']'
    // pointer--> '*' type_qualifier_list pointer
    // pointer--> '*' type_qualifier_list
    // type_qualifier_list--> type_qualifier_list type_qualifier
    // direct_abstract_declarator--> '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_abstract_declarator--> '[' type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> '[' type_qualifier_list ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list ']'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *type_qualifier_list=tdefs->m_tk_elems[0];
    //token_defs *type_qualifier=tdefs->m_tk_elems[1];
    //icode *type_qualifier_list_ic=pcompi->ast_to_icode(type_qualifier_list);
    //icode *type_qualifier_ic=pcompi->ast_to_icode(type_qualifier);
    //a->merge_icode(type_qualifier_list_ic);
    //a->merge_icode(type_qualifier_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_PARAMETER_TYPE_LIST_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3901-parameter_type_list->parameter_list ',' ELLIPSIS
    //parent:
    // direct_declarator_function1--> direct_declarator_function1 '(' parameter_type_list ')'
    // direct_abstract_declarator--> '(' parameter_type_list ')'
    // direct_abstract_declarator--> direct_abstract_declarator '(' parameter_type_list ')'
    icode *a = pcompi->new_icode();
    a->m_type = ICODE_TYPE_BLOCK;
    token_defs *parameter_list=tdefs->m_tk_elems[0];
    //token_defs *','=tdefs->m_tk_elems[1];
    token_defs *ELLIPSIS=tdefs->m_tk_elems[2];
    icode *parameter_list_ic=pcompi->ast_to_icode(parameter_list);
    //icode *','_ic=pcompi->ast_to_icode(',');
    icode *ELLIPSIS_ic=pcompi->ast_to_icode(ELLIPSIS);
    a->merge_icode(parameter_list_ic);
    //a->merge_icode(','_ic);
    a->merge_icode(ELLIPSIS_ic);


    return a;
}
class icode *  func_IAN_PARAMETER_TYPE_LIST_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3902-parameter_type_list->parameter_list
    //parent:
    // direct_declarator_function1--> direct_declarator_function1 '(' parameter_type_list ')'
    // direct_abstract_declarator--> '(' parameter_type_list ')'
    // direct_abstract_declarator--> direct_abstract_declarator '(' parameter_type_list ')'
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_PARAMETER_LIST_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3a01-parameter_list->parameter_declaration
    //parent:
    // parameter_type_list--> parameter_list ',' ELLIPSIS
    // parameter_type_list--> parameter_list
    // parameter_list--> parameter_list ',' parameter_declaration

    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    icode *b = pcompi->ast_to_icode(tdefs, 1);
    a->merge_icode(b);
    return a;
}
class icode *  func_IAN_PARAMETER_LIST_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3a02-parameter_list->parameter_list ',' parameter_declaration
    //parent:
    // parameter_type_list--> parameter_list ',' ELLIPSIS
    // parameter_type_list--> parameter_list
    // parameter_list--> parameter_list ',' parameter_declaration
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    icode *b = pcompi->ast_to_icode(tdefs->m_tk_elems[0]);
    a->merge_icode(b);
    icode *c = pcompi->ast_to_icode(tdefs->m_tk_elems[2]);
    a->merge_icode(c);


    return a;
}
class icode *  func_IAN_PARAMETER_DECLARATION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3b01-parameter_declaration->declaration_specifiers declarator
    //parent:
    // parameter_list--> parameter_declaration
    // parameter_list--> parameter_list ',' parameter_declaration
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    token_defs *declaration_specifiers = tdefs->m_tk_elems[0];
    token_defs *declarator = tdefs->m_tk_elems[1];
    icode * type_ic=pcompi->new_icode();
    type_ic->m_type=ICODE_TYPE_DEF_VAR;
    pcompi->ast_to_icode(declaration_specifiers,0, type_ic);

    type_ic->m_level = pcompi->get_level();

    icode *b = pcompi->ast_to_icode(declarator, 1);
    a->merge_icode(b);


    // 添加对数组的支持
    //添加新变量。名称b->result
    int is_already_exist=0;
    icode * asym = pcompi->new_var(b->result, type_ic, is_already_exist);//

    if(!is_already_exist)
    {
        ///添加变量定义
        a->merge_icode(asym);
    }

    ///===================================
    ///
    return a;
}

class icode *  func_IAN_PARAMETER_DECLARATION_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3b02-parameter_declaration->declaration_specifiers abstract_declarator
    //parent:
    // parameter_list--> parameter_declaration
    // parameter_list--> parameter_list ',' parameter_declaration

    return func_IAN_PARAMETER_DECLARATION_1(pcompi, tdefs, need_result_icode, result_ic);

}
class icode *  func_IAN_PARAMETER_DECLARATION_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3b03-parameter_declaration->declaration_specifiers
    //parent:
    // parameter_list--> parameter_declaration
    // parameter_list--> parameter_list ',' parameter_declaration

    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    token_defs *declaration_specifiers = tdefs;
    icode * type_ic=pcompi->new_icode();
    type_ic->m_type=ICODE_TYPE_DEF_VAR;
    pcompi->ast_to_icode(declaration_specifiers,0, type_ic);

    type_ic->m_level = pcompi->get_level();

    int is_already_exist=0;
    icode * asym = pcompi->new_var(pcompi->get_temp_name("uname_param"), type_ic, is_already_exist);//

    if(!is_already_exist)
    {
        ///添加变量定义
        a->merge_icode(asym);
    }

    ///===================================
    ///
    return a;


    //return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}

class icode *  func_IAN_TYPE_NAME_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3d01-type_name->specifier_qualifier_list abstract_declarator
    //parent:
    // generic_association--> type_name ':' assignment_expression
    // postfix_expression--> '(' type_name ')' '{' initializer_list '}'
    // postfix_expression--> '(' type_name ')' '{' initializer_list ',' '}'
    // unary_expression--> SIZEOF '(' type_name ')'
    // unary_expression--> ALIGNOF '(' type_name ')'
    // cast_expression--> '(' type_name ')' cast_expression
    // atomic_type_specifier--> ATOMIC '(' type_name ')'
    // alignment_specifier--> ALIGNAS '(' type_name ')'


    //这是一个type_name. char*.  -->specifier_qualifier_list(char) abstract_declarator(*)
    // 代码参考： func_IAN_DECLARATION_SPECIFIERS__1

    token_defs *specifier_qualifier_list = tdefs->m_tk_elems[0];
    token_defs *abstract_declarator = tdefs->m_tk_elems[1];


    icode* b = NULL;
    if(result_ic)
    {
        b=result_ic;
    }
    else
    {
        b=pcompi->new_icode();
        b->m_type=ICODE_TYPE_DEF_VAR;
    }

    //此处改为先解析左边的，再解析右边的，如果长度不一致，则右边会覆盖左边的。
    // unsigned short;--->unsigned-->bw=4. short-->bw=2
    // signed char
    // long long
    //
    pcompi->ast_to_icode(specifier_qualifier_list,0, b);
    pcompi->ast_to_icode(abstract_declarator, 0, b);

    return NULL;
}
class icode *  func_IAN_TYPE_NAME_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3d02-type_name->specifier_qualifier_list
    //parent:
    // generic_association--> type_name ':' assignment_expression
    // postfix_expression--> '(' type_name ')' '{' initializer_list '}'
    // postfix_expression--> '(' type_name ')' '{' initializer_list ',' '}'
    // unary_expression--> SIZEOF '(' type_name ')'
    // unary_expression--> ALIGNOF '(' type_name ')'
    // cast_expression--> '(' type_name ')' cast_expression
    // atomic_type_specifier--> ATOMIC '(' type_name ')'
    // alignment_specifier--> ALIGNAS '(' type_name ')'
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_ABSTRACT_DECLARATOR_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3e01-abstract_declarator->pointer direct_abstract_declarator
    //parent:
    // parameter_declaration--> declaration_specifiers abstract_declarator
    // type_name--> specifier_qualifier_list abstract_declarator
    // direct_abstract_declarator--> '(' abstract_declarator ')'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *pointer=tdefs->m_tk_elems[0];
    //token_defs *direct_abstract_declarator=tdefs->m_tk_elems[1];
    //icode *pointer_ic=pcompi->ast_to_icode(pointer);
    //icode *direct_abstract_declarator_ic=pcompi->ast_to_icode(direct_abstract_declarator);
    //a->merge_icode(pointer_ic);
    //a->merge_icode(direct_abstract_declarator_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_ABSTRACT_DECLARATOR_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3e02-abstract_declarator->pointer
    //parent:
    // parameter_declaration--> declaration_specifiers abstract_declarator
    // type_name--> specifier_qualifier_list abstract_declarator
    // direct_abstract_declarator--> '(' abstract_declarator ')'
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_ABSTRACT_DECLARATOR_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3e03-abstract_declarator->direct_abstract_declarator
    //parent:
    // parameter_declaration--> declaration_specifiers abstract_declarator
    // type_name--> specifier_qualifier_list abstract_declarator
    // direct_abstract_declarator--> '(' abstract_declarator ')'
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3f01-direct_abstract_declarator->'(' abstract_declarator ')'
    //parent:
    // abstract_declarator--> pointer direct_abstract_declarator
    // abstract_declarator--> direct_abstract_declarator
    // direct_abstract_declarator--> direct_abstract_declarator '[' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' '*' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '(' ')'
    // direct_abstract_declarator--> direct_abstract_declarator '(' parameter_type_list ')'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *'('=tdefs->m_tk_elems[0];
    //token_defs *abstract_declarator=tdefs->m_tk_elems[1];
    //token_defs *')'=tdefs->m_tk_elems[2];
    //icode *'('_ic=pcompi->ast_to_icode('(');
    //icode *abstract_declarator_ic=pcompi->ast_to_icode(abstract_declarator);
    //icode *')'_ic=pcompi->ast_to_icode(')');
    //a->merge_icode('('_ic);
    //a->merge_icode(abstract_declarator_ic);
    //a->merge_icode(')'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3f02-direct_abstract_declarator->'[' ']'
    //parent:
    // abstract_declarator--> pointer direct_abstract_declarator
    // abstract_declarator--> direct_abstract_declarator
    // direct_abstract_declarator--> direct_abstract_declarator '[' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' '*' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '(' ')'
    // direct_abstract_declarator--> direct_abstract_declarator '(' parameter_type_list ')'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *'['=tdefs->m_tk_elems[0];
    //token_defs *']'=tdefs->m_tk_elems[1];
    //icode *'['_ic=pcompi->ast_to_icode('[');
    //icode *']'_ic=pcompi->ast_to_icode(']');
    //a->merge_icode('['_ic);
    //a->merge_icode(']'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3f03-direct_abstract_declarator->'[' '*' ']'
    //parent:
    // abstract_declarator--> pointer direct_abstract_declarator
    // abstract_declarator--> direct_abstract_declarator
    // direct_abstract_declarator--> direct_abstract_declarator '[' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' '*' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '(' ')'
    // direct_abstract_declarator--> direct_abstract_declarator '(' parameter_type_list ')'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *'['=tdefs->m_tk_elems[0];
    //token_defs *'*'=tdefs->m_tk_elems[1];
    //token_defs *']'=tdefs->m_tk_elems[2];
    //icode *'['_ic=pcompi->ast_to_icode('[');
    //icode *'*'_ic=pcompi->ast_to_icode('*');
    //icode *']'_ic=pcompi->ast_to_icode(']');
    //a->merge_icode('['_ic);
    //a->merge_icode('*'_ic);
    //a->merge_icode(']'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3f04-direct_abstract_declarator->'[' STATIC type_qualifier_list assignment_expression ']'
    //parent:
    // abstract_declarator--> pointer direct_abstract_declarator
    // abstract_declarator--> direct_abstract_declarator
    // direct_abstract_declarator--> direct_abstract_declarator '[' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' '*' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '(' ')'
    // direct_abstract_declarator--> direct_abstract_declarator '(' parameter_type_list ')'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *'['=tdefs->m_tk_elems[0];
    //token_defs *STATIC=tdefs->m_tk_elems[1];
    //token_defs *type_qualifier_list=tdefs->m_tk_elems[2];
    //token_defs *assignment_expression=tdefs->m_tk_elems[3];
    //token_defs *']'=tdefs->m_tk_elems[4];
    //icode *'['_ic=pcompi->ast_to_icode('[');
    //icode *STATIC_ic=pcompi->ast_to_icode(STATIC);
    //icode *type_qualifier_list_ic=pcompi->ast_to_icode(type_qualifier_list);
    //icode *assignment_expression_ic=pcompi->ast_to_icode(assignment_expression);
    //icode *']'_ic=pcompi->ast_to_icode(']');
    //a->merge_icode('['_ic);
    //a->merge_icode(STATIC_ic);
    //a->merge_icode(type_qualifier_list_ic);
    //a->merge_icode(assignment_expression_ic);
    //a->merge_icode(']'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_5(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3f05-direct_abstract_declarator->'[' STATIC assignment_expression ']'
    //parent:
    // abstract_declarator--> pointer direct_abstract_declarator
    // abstract_declarator--> direct_abstract_declarator
    // direct_abstract_declarator--> direct_abstract_declarator '[' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' '*' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '(' ')'
    // direct_abstract_declarator--> direct_abstract_declarator '(' parameter_type_list ')'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *'['=tdefs->m_tk_elems[0];
    //token_defs *STATIC=tdefs->m_tk_elems[1];
    //token_defs *assignment_expression=tdefs->m_tk_elems[2];
    //token_defs *']'=tdefs->m_tk_elems[3];
    //icode *'['_ic=pcompi->ast_to_icode('[');
    //icode *STATIC_ic=pcompi->ast_to_icode(STATIC);
    //icode *assignment_expression_ic=pcompi->ast_to_icode(assignment_expression);
    //icode *']'_ic=pcompi->ast_to_icode(']');
    //a->merge_icode('['_ic);
    //a->merge_icode(STATIC_ic);
    //a->merge_icode(assignment_expression_ic);
    //a->merge_icode(']'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_6(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3f06-direct_abstract_declarator->'[' type_qualifier_list STATIC assignment_expression ']'
    //parent:
    // abstract_declarator--> pointer direct_abstract_declarator
    // abstract_declarator--> direct_abstract_declarator
    // direct_abstract_declarator--> direct_abstract_declarator '[' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' '*' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '(' ')'
    // direct_abstract_declarator--> direct_abstract_declarator '(' parameter_type_list ')'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *'['=tdefs->m_tk_elems[0];
    //token_defs *type_qualifier_list=tdefs->m_tk_elems[1];
    //token_defs *STATIC=tdefs->m_tk_elems[2];
    //token_defs *assignment_expression=tdefs->m_tk_elems[3];
    //token_defs *']'=tdefs->m_tk_elems[4];
    //icode *'['_ic=pcompi->ast_to_icode('[');
    //icode *type_qualifier_list_ic=pcompi->ast_to_icode(type_qualifier_list);
    //icode *STATIC_ic=pcompi->ast_to_icode(STATIC);
    //icode *assignment_expression_ic=pcompi->ast_to_icode(assignment_expression);
    //icode *']'_ic=pcompi->ast_to_icode(']');
    //a->merge_icode('['_ic);
    //a->merge_icode(type_qualifier_list_ic);
    //a->merge_icode(STATIC_ic);
    //a->merge_icode(assignment_expression_ic);
    //a->merge_icode(']'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_7(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3f07-direct_abstract_declarator->'[' type_qualifier_list assignment_expression ']'
    //parent:
    // abstract_declarator--> pointer direct_abstract_declarator
    // abstract_declarator--> direct_abstract_declarator
    // direct_abstract_declarator--> direct_abstract_declarator '[' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' '*' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '(' ')'
    // direct_abstract_declarator--> direct_abstract_declarator '(' parameter_type_list ')'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *'['=tdefs->m_tk_elems[0];
    //token_defs *type_qualifier_list=tdefs->m_tk_elems[1];
    //token_defs *assignment_expression=tdefs->m_tk_elems[2];
    //token_defs *']'=tdefs->m_tk_elems[3];
    //icode *'['_ic=pcompi->ast_to_icode('[');
    //icode *type_qualifier_list_ic=pcompi->ast_to_icode(type_qualifier_list);
    //icode *assignment_expression_ic=pcompi->ast_to_icode(assignment_expression);
    //icode *']'_ic=pcompi->ast_to_icode(']');
    //a->merge_icode('['_ic);
    //a->merge_icode(type_qualifier_list_ic);
    //a->merge_icode(assignment_expression_ic);
    //a->merge_icode(']'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_8(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3f08-direct_abstract_declarator->'[' type_qualifier_list ']'
    //parent:
    // abstract_declarator--> pointer direct_abstract_declarator
    // abstract_declarator--> direct_abstract_declarator
    // direct_abstract_declarator--> direct_abstract_declarator '[' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' '*' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '(' ')'
    // direct_abstract_declarator--> direct_abstract_declarator '(' parameter_type_list ')'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *'['=tdefs->m_tk_elems[0];
    //token_defs *type_qualifier_list=tdefs->m_tk_elems[1];
    //token_defs *']'=tdefs->m_tk_elems[2];
    //icode *'['_ic=pcompi->ast_to_icode('[');
    //icode *type_qualifier_list_ic=pcompi->ast_to_icode(type_qualifier_list);
    //icode *']'_ic=pcompi->ast_to_icode(']');
    //a->merge_icode('['_ic);
    //a->merge_icode(type_qualifier_list_ic);
    //a->merge_icode(']'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_9(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3f09-direct_abstract_declarator->'[' assignment_expression ']'
    //parent:
    // abstract_declarator--> pointer direct_abstract_declarator
    // abstract_declarator--> direct_abstract_declarator
    // direct_abstract_declarator--> direct_abstract_declarator '[' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' '*' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '(' ')'
    // direct_abstract_declarator--> direct_abstract_declarator '(' parameter_type_list ')'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *'['=tdefs->m_tk_elems[0];
    //token_defs *assignment_expression=tdefs->m_tk_elems[1];
    //token_defs *']'=tdefs->m_tk_elems[2];
    //icode *'['_ic=pcompi->ast_to_icode('[');
    //icode *assignment_expression_ic=pcompi->ast_to_icode(assignment_expression);
    //icode *']'_ic=pcompi->ast_to_icode(']');
    //a->merge_icode('['_ic);
    //a->merge_icode(assignment_expression_ic);
    //a->merge_icode(']'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_10(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3f0a-direct_abstract_declarator->direct_abstract_declarator '[' ']'
    //parent:
    // abstract_declarator--> pointer direct_abstract_declarator
    // abstract_declarator--> direct_abstract_declarator
    // direct_abstract_declarator--> direct_abstract_declarator '[' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' '*' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '(' ')'
    // direct_abstract_declarator--> direct_abstract_declarator '(' parameter_type_list ')'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *direct_abstract_declarator=tdefs->m_tk_elems[0];
    //token_defs *'['=tdefs->m_tk_elems[1];
    //token_defs *']'=tdefs->m_tk_elems[2];
    //icode *direct_abstract_declarator_ic=pcompi->ast_to_icode(direct_abstract_declarator);
    //icode *'['_ic=pcompi->ast_to_icode('[');
    //icode *']'_ic=pcompi->ast_to_icode(']');
    //a->merge_icode(direct_abstract_declarator_ic);
    //a->merge_icode('['_ic);
    //a->merge_icode(']'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_11(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3f0b-direct_abstract_declarator->direct_abstract_declarator '[' '*' ']'
    //parent:
    // abstract_declarator--> pointer direct_abstract_declarator
    // abstract_declarator--> direct_abstract_declarator
    // direct_abstract_declarator--> direct_abstract_declarator '[' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' '*' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '(' ')'
    // direct_abstract_declarator--> direct_abstract_declarator '(' parameter_type_list ')'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *direct_abstract_declarator=tdefs->m_tk_elems[0];
    //token_defs *'['=tdefs->m_tk_elems[1];
    //token_defs *'*'=tdefs->m_tk_elems[2];
    //token_defs *']'=tdefs->m_tk_elems[3];
    //icode *direct_abstract_declarator_ic=pcompi->ast_to_icode(direct_abstract_declarator);
    //icode *'['_ic=pcompi->ast_to_icode('[');
    //icode *'*'_ic=pcompi->ast_to_icode('*');
    //icode *']'_ic=pcompi->ast_to_icode(']');
    //a->merge_icode(direct_abstract_declarator_ic);
    //a->merge_icode('['_ic);
    //a->merge_icode('*'_ic);
    //a->merge_icode(']'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_12(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3f0c-direct_abstract_declarator->direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'
    //parent:
    // abstract_declarator--> pointer direct_abstract_declarator
    // abstract_declarator--> direct_abstract_declarator
    // direct_abstract_declarator--> direct_abstract_declarator '[' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' '*' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '(' ')'
    // direct_abstract_declarator--> direct_abstract_declarator '(' parameter_type_list ')'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *direct_abstract_declarator=tdefs->m_tk_elems[0];
    //token_defs *'['=tdefs->m_tk_elems[1];
    //token_defs *STATIC=tdefs->m_tk_elems[2];
    //token_defs *type_qualifier_list=tdefs->m_tk_elems[3];
    //token_defs *assignment_expression=tdefs->m_tk_elems[4];
    //token_defs *']'=tdefs->m_tk_elems[5];
    //icode *direct_abstract_declarator_ic=pcompi->ast_to_icode(direct_abstract_declarator);
    //icode *'['_ic=pcompi->ast_to_icode('[');
    //icode *STATIC_ic=pcompi->ast_to_icode(STATIC);
    //icode *type_qualifier_list_ic=pcompi->ast_to_icode(type_qualifier_list);
    //icode *assignment_expression_ic=pcompi->ast_to_icode(assignment_expression);
    //icode *']'_ic=pcompi->ast_to_icode(']');
    //a->merge_icode(direct_abstract_declarator_ic);
    //a->merge_icode('['_ic);
    //a->merge_icode(STATIC_ic);
    //a->merge_icode(type_qualifier_list_ic);
    //a->merge_icode(assignment_expression_ic);
    //a->merge_icode(']'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_13(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3f0d-direct_abstract_declarator->direct_abstract_declarator '[' STATIC assignment_expression ']'
    //parent:
    // abstract_declarator--> pointer direct_abstract_declarator
    // abstract_declarator--> direct_abstract_declarator
    // direct_abstract_declarator--> direct_abstract_declarator '[' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' '*' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '(' ')'
    // direct_abstract_declarator--> direct_abstract_declarator '(' parameter_type_list ')'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *direct_abstract_declarator=tdefs->m_tk_elems[0];
    //token_defs *'['=tdefs->m_tk_elems[1];
    //token_defs *STATIC=tdefs->m_tk_elems[2];
    //token_defs *assignment_expression=tdefs->m_tk_elems[3];
    //token_defs *']'=tdefs->m_tk_elems[4];
    //icode *direct_abstract_declarator_ic=pcompi->ast_to_icode(direct_abstract_declarator);
    //icode *'['_ic=pcompi->ast_to_icode('[');
    //icode *STATIC_ic=pcompi->ast_to_icode(STATIC);
    //icode *assignment_expression_ic=pcompi->ast_to_icode(assignment_expression);
    //icode *']'_ic=pcompi->ast_to_icode(']');
    //a->merge_icode(direct_abstract_declarator_ic);
    //a->merge_icode('['_ic);
    //a->merge_icode(STATIC_ic);
    //a->merge_icode(assignment_expression_ic);
    //a->merge_icode(']'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_14(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3f0e-direct_abstract_declarator->direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
    //parent:
    // abstract_declarator--> pointer direct_abstract_declarator
    // abstract_declarator--> direct_abstract_declarator
    // direct_abstract_declarator--> direct_abstract_declarator '[' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' '*' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '(' ')'
    // direct_abstract_declarator--> direct_abstract_declarator '(' parameter_type_list ')'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *direct_abstract_declarator=tdefs->m_tk_elems[0];
    //token_defs *'['=tdefs->m_tk_elems[1];
    //token_defs *type_qualifier_list=tdefs->m_tk_elems[2];
    //token_defs *assignment_expression=tdefs->m_tk_elems[3];
    //token_defs *']'=tdefs->m_tk_elems[4];
    //icode *direct_abstract_declarator_ic=pcompi->ast_to_icode(direct_abstract_declarator);
    //icode *'['_ic=pcompi->ast_to_icode('[');
    //icode *type_qualifier_list_ic=pcompi->ast_to_icode(type_qualifier_list);
    //icode *assignment_expression_ic=pcompi->ast_to_icode(assignment_expression);
    //icode *']'_ic=pcompi->ast_to_icode(']');
    //a->merge_icode(direct_abstract_declarator_ic);
    //a->merge_icode('['_ic);
    //a->merge_icode(type_qualifier_list_ic);
    //a->merge_icode(assignment_expression_ic);
    //a->merge_icode(']'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_15(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3f0f-direct_abstract_declarator->direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'
    //parent:
    // abstract_declarator--> pointer direct_abstract_declarator
    // abstract_declarator--> direct_abstract_declarator
    // direct_abstract_declarator--> direct_abstract_declarator '[' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' '*' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '(' ')'
    // direct_abstract_declarator--> direct_abstract_declarator '(' parameter_type_list ')'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *direct_abstract_declarator=tdefs->m_tk_elems[0];
    //token_defs *'['=tdefs->m_tk_elems[1];
    //token_defs *type_qualifier_list=tdefs->m_tk_elems[2];
    //token_defs *STATIC=tdefs->m_tk_elems[3];
    //token_defs *assignment_expression=tdefs->m_tk_elems[4];
    //token_defs *']'=tdefs->m_tk_elems[5];
    //icode *direct_abstract_declarator_ic=pcompi->ast_to_icode(direct_abstract_declarator);
    //icode *'['_ic=pcompi->ast_to_icode('[');
    //icode *type_qualifier_list_ic=pcompi->ast_to_icode(type_qualifier_list);
    //icode *STATIC_ic=pcompi->ast_to_icode(STATIC);
    //icode *assignment_expression_ic=pcompi->ast_to_icode(assignment_expression);
    //icode *']'_ic=pcompi->ast_to_icode(']');
    //a->merge_icode(direct_abstract_declarator_ic);
    //a->merge_icode('['_ic);
    //a->merge_icode(type_qualifier_list_ic);
    //a->merge_icode(STATIC_ic);
    //a->merge_icode(assignment_expression_ic);
    //a->merge_icode(']'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_16(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3f10-direct_abstract_declarator->direct_abstract_declarator '[' type_qualifier_list ']'
    //parent:
    // abstract_declarator--> pointer direct_abstract_declarator
    // abstract_declarator--> direct_abstract_declarator
    // direct_abstract_declarator--> direct_abstract_declarator '[' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' '*' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '(' ')'
    // direct_abstract_declarator--> direct_abstract_declarator '(' parameter_type_list ')'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *direct_abstract_declarator=tdefs->m_tk_elems[0];
    //token_defs *'['=tdefs->m_tk_elems[1];
    //token_defs *type_qualifier_list=tdefs->m_tk_elems[2];
    //token_defs *']'=tdefs->m_tk_elems[3];
    //icode *direct_abstract_declarator_ic=pcompi->ast_to_icode(direct_abstract_declarator);
    //icode *'['_ic=pcompi->ast_to_icode('[');
    //icode *type_qualifier_list_ic=pcompi->ast_to_icode(type_qualifier_list);
    //icode *']'_ic=pcompi->ast_to_icode(']');
    //a->merge_icode(direct_abstract_declarator_ic);
    //a->merge_icode('['_ic);
    //a->merge_icode(type_qualifier_list_ic);
    //a->merge_icode(']'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_17(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3f11-direct_abstract_declarator->direct_abstract_declarator '[' assignment_expression ']'
    //parent:
    // abstract_declarator--> pointer direct_abstract_declarator
    // abstract_declarator--> direct_abstract_declarator
    // direct_abstract_declarator--> direct_abstract_declarator '[' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' '*' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '(' ')'
    // direct_abstract_declarator--> direct_abstract_declarator '(' parameter_type_list ')'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *direct_abstract_declarator=tdefs->m_tk_elems[0];
    //token_defs *'['=tdefs->m_tk_elems[1];
    //token_defs *assignment_expression=tdefs->m_tk_elems[2];
    //token_defs *']'=tdefs->m_tk_elems[3];
    //icode *direct_abstract_declarator_ic=pcompi->ast_to_icode(direct_abstract_declarator);
    //icode *'['_ic=pcompi->ast_to_icode('[');
    //icode *assignment_expression_ic=pcompi->ast_to_icode(assignment_expression);
    //icode *']'_ic=pcompi->ast_to_icode(']');
    //a->merge_icode(direct_abstract_declarator_ic);
    //a->merge_icode('['_ic);
    //a->merge_icode(assignment_expression_ic);
    //a->merge_icode(']'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_18(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3f12-direct_abstract_declarator->'(' ')'
    //parent:
    // abstract_declarator--> pointer direct_abstract_declarator
    // abstract_declarator--> direct_abstract_declarator
    // direct_abstract_declarator--> direct_abstract_declarator '[' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' '*' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '(' ')'
    // direct_abstract_declarator--> direct_abstract_declarator '(' parameter_type_list ')'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *'('=tdefs->m_tk_elems[0];
    //token_defs *')'=tdefs->m_tk_elems[1];
    //icode *'('_ic=pcompi->ast_to_icode('(');
    //icode *')'_ic=pcompi->ast_to_icode(')');
    //a->merge_icode('('_ic);
    //a->merge_icode(')'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_19(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3f13-direct_abstract_declarator->'(' parameter_type_list ')'
    //parent:
    // abstract_declarator--> pointer direct_abstract_declarator
    // abstract_declarator--> direct_abstract_declarator
    // direct_abstract_declarator--> direct_abstract_declarator '[' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' '*' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '(' ')'
    // direct_abstract_declarator--> direct_abstract_declarator '(' parameter_type_list ')'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *'('=tdefs->m_tk_elems[0];
    //token_defs *parameter_type_list=tdefs->m_tk_elems[1];
    //token_defs *')'=tdefs->m_tk_elems[2];
    //icode *'('_ic=pcompi->ast_to_icode('(');
    //icode *parameter_type_list_ic=pcompi->ast_to_icode(parameter_type_list);
    //icode *')'_ic=pcompi->ast_to_icode(')');
    //a->merge_icode('('_ic);
    //a->merge_icode(parameter_type_list_ic);
    //a->merge_icode(')'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_20(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3f14-direct_abstract_declarator->direct_abstract_declarator '(' ')'
    //parent:
    // abstract_declarator--> pointer direct_abstract_declarator
    // abstract_declarator--> direct_abstract_declarator
    // direct_abstract_declarator--> direct_abstract_declarator '[' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' '*' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '(' ')'
    // direct_abstract_declarator--> direct_abstract_declarator '(' parameter_type_list ')'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *direct_abstract_declarator=tdefs->m_tk_elems[0];
    //token_defs *'('=tdefs->m_tk_elems[1];
    //token_defs *')'=tdefs->m_tk_elems[2];
    //icode *direct_abstract_declarator_ic=pcompi->ast_to_icode(direct_abstract_declarator);
    //icode *'('_ic=pcompi->ast_to_icode('(');
    //icode *')'_ic=pcompi->ast_to_icode(')');
    //a->merge_icode(direct_abstract_declarator_ic);
    //a->merge_icode('('_ic);
    //a->merge_icode(')'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_21(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3f15-direct_abstract_declarator->direct_abstract_declarator '(' parameter_type_list ')'
    //parent:
    // abstract_declarator--> pointer direct_abstract_declarator
    // abstract_declarator--> direct_abstract_declarator
    // direct_abstract_declarator--> direct_abstract_declarator '[' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' '*' ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '(' ')'
    // direct_abstract_declarator--> direct_abstract_declarator '(' parameter_type_list ')'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *direct_abstract_declarator=tdefs->m_tk_elems[0];
    //token_defs *'('=tdefs->m_tk_elems[1];
    //token_defs *parameter_type_list=tdefs->m_tk_elems[2];
    //token_defs *')'=tdefs->m_tk_elems[3];
    //icode *direct_abstract_declarator_ic=pcompi->ast_to_icode(direct_abstract_declarator);
    //icode *'('_ic=pcompi->ast_to_icode('(');
    //icode *parameter_type_list_ic=pcompi->ast_to_icode(parameter_type_list);
    //icode *')'_ic=pcompi->ast_to_icode(')');
    //a->merge_icode(direct_abstract_declarator_ic);
    //a->merge_icode('('_ic);
    //a->merge_icode(parameter_type_list_ic);
    //a->merge_icode(')'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_INITIALIZER_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4001-initializer->'{' initializer_list '}'
    //parent:
    // init_declarator--> declarator '=' initializer
    // initializer_list--> designation initializer
    // initializer_list--> initializer
    // initializer_list--> initializer_list ',' designation initializer
    // initializer_list--> initializer_list ',' initializer
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    //初始值 int a[10]={1,2,3,4,5};


    token_defs * initializer_list = tdefs->m_tk_elems[1];
    icode *initializer_list_ic = pcompi->ast_to_icode(initializer_list, need_result_icode, result_ic);

    icode *scope  =  pcompi->new_icode(ICODE_TYPE_SCOPE);
    scope->merge_icode(initializer_list_ic->result);


    a->merge_icode(initializer_list_ic);
    if(need_result_icode)
    {
        a->result = scope;//initializer_list_ic->result;
    }

    return a;
}
class icode *  func_IAN_INITIALIZER_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4002-initializer->'{' initializer_list ',' '}'
    //parent:
    // init_declarator--> declarator '=' initializer
    // initializer_list--> designation initializer
    // initializer_list--> initializer
    // initializer_list--> initializer_list ',' designation initializer
    // initializer_list--> initializer_list ',' initializer
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    //初始值 int a[10]={1,2,3,4,5, };

    token_defs * initializer_list = tdefs->m_tk_elems[1];
    icode *initializer_list_ic = pcompi->ast_to_icode(initializer_list, need_result_icode, result_ic);

    icode *scope  =  pcompi->new_icode(ICODE_TYPE_SCOPE);
    scope->merge_icode(initializer_list_ic->result);


    a->merge_icode(initializer_list_ic);
    if(need_result_icode)
    {
        a->result = scope;//initializer_list_ic->result;
    }

    return a;
}
class icode *  func_IAN_INITIALIZER_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4003-initializer->assignment_expression
    //parent:
    // init_declarator--> declarator '=' initializer
    // initializer_list--> designation initializer
    // initializer_list--> initializer
    // initializer_list--> initializer_list ',' designation initializer
    // initializer_list--> initializer_list ',' initializer
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_INITIALIZER_LIST_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4101-initializer_list->designation initializer
    //parent:
    // postfix_expression--> '(' type_name ')' '{' initializer_list '}'
    // postfix_expression--> '(' type_name ')' '{' initializer_list ',' '}'
    // initializer--> '{' initializer_list '}'
    // initializer--> '{' initializer_list ',' '}'
    // initializer_list--> initializer_list ',' designation initializer
    // initializer_list--> initializer_list ',' initializer
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *designation=tdefs->m_tk_elems[0];
    //token_defs *initializer=tdefs->m_tk_elems[1];
    //icode *designation_ic=pcompi->ast_to_icode(designation);
    //icode *initializer_ic=pcompi->ast_to_icode(initializer);
    //a->merge_icode(designation_ic);
    //a->merge_icode(initializer_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_INITIALIZER_LIST_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4102-initializer_list->initializer
    //parent:
    // postfix_expression--> '(' type_name ')' '{' initializer_list '}'
    // postfix_expression--> '(' type_name ')' '{' initializer_list ',' '}'
    // initializer--> '{' initializer_list '}'
    // initializer--> '{' initializer_list ',' '}'
    // initializer_list--> initializer_list ',' designation initializer
    // initializer_list--> initializer_list ',' initializer
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_INITIALIZER_LIST_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4103-initializer_list->initializer_list ',' designation initializer
    //parent:
    // postfix_expression--> '(' type_name ')' '{' initializer_list '}'
    // postfix_expression--> '(' type_name ')' '{' initializer_list ',' '}'
    // initializer--> '{' initializer_list '}'
    // initializer--> '{' initializer_list ',' '}'
    // initializer_list--> initializer_list ',' designation initializer
    // initializer_list--> initializer_list ',' initializer
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *initializer_list=tdefs->m_tk_elems[0];
    //token_defs *','=tdefs->m_tk_elems[1];
    //token_defs *designation=tdefs->m_tk_elems[2];
    //token_defs *initializer=tdefs->m_tk_elems[3];
    //icode *initializer_list_ic=pcompi->ast_to_icode(initializer_list);
    //icode *','_ic=pcompi->ast_to_icode(',');
    //icode *designation_ic=pcompi->ast_to_icode(designation);
    //icode *initializer_ic=pcompi->ast_to_icode(initializer);
    //a->merge_icode(initializer_list_ic);
    //a->merge_icode(','_ic);
    //a->merge_icode(designation_ic);
    //a->merge_icode(initializer_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_INITIALIZER_LIST_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4104-initializer_list->initializer_list ',' initializer
    //parent:
    // postfix_expression--> '(' type_name ')' '{' initializer_list '}'
    // postfix_expression--> '(' type_name ')' '{' initializer_list ',' '}'
    // initializer--> '{' initializer_list '}'
    // initializer--> '{' initializer_list ',' '}'
    // initializer_list--> initializer_list ',' designation initializer
    // initializer_list--> initializer_list ',' initializer
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    /// 此处的result 应该学习函数参数，采用result里面传递 多个值的方式？？？？？？？？？？？？
    /// 2020.6.30
    token_defs *initializer_list=tdefs->m_tk_elems[0];
    token_defs *initializer=tdefs->m_tk_elems[2];

    icode * ic1  = pcompi->ast_to_icode(initializer_list, 1);
    icode * ic2 = pcompi->ast_to_icode(initializer, 1);

    a->merge_icode(ic1);
    a->merge_icode(ic2);
    if(need_result_icode)
    {
        if(ic1->result->m_type!=ICODE_TYPE_CONST_LIST)
        {
            a->result = pcompi->new_icode(ICODE_TYPE_CONST_LIST);
            a->result->merge_icode(ic1->result);
        }
        else
        {
            a->result = ic1->result;
        }
        a->result->merge_icode(ic2->result);
    }

    return a;
}
class icode *  func_IAN_DESIGNATION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4201-designation->designator_list '='
    //parent:
    // initializer_list--> designation initializer
    // initializer_list--> initializer_list ',' designation initializer
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *designator_list=tdefs->m_tk_elems[0];
    //token_defs *'='=tdefs->m_tk_elems[1];
    //icode *designator_list_ic=pcompi->ast_to_icode(designator_list);
    //icode *'='_ic=pcompi->ast_to_icode('=');
    //a->merge_icode(designator_list_ic);
    //a->merge_icode('='_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_DESIGNATOR_LIST_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4301-designator_list->designator
    //parent:
    // designation--> designator_list '='
    // designator_list--> designator_list designator
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_DESIGNATOR_LIST_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4302-designator_list->designator_list designator
    //parent:
    // designation--> designator_list '='
    // designator_list--> designator_list designator
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *designator_list=tdefs->m_tk_elems[0];
    //token_defs *designator=tdefs->m_tk_elems[1];
    //icode *designator_list_ic=pcompi->ast_to_icode(designator_list);
    //icode *designator_ic=pcompi->ast_to_icode(designator);
    //a->merge_icode(designator_list_ic);
    //a->merge_icode(designator_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_DESIGNATOR_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4401-designator->'[' constant_expression ']'
    //parent:
    // designator_list--> designator
    // designator_list--> designator_list designator
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *'['=tdefs->m_tk_elems[0];
    //token_defs *constant_expression=tdefs->m_tk_elems[1];
    //token_defs *']'=tdefs->m_tk_elems[2];
    //icode *'['_ic=pcompi->ast_to_icode('[');
    //icode *constant_expression_ic=pcompi->ast_to_icode(constant_expression);
    //icode *']'_ic=pcompi->ast_to_icode(']');
    //a->merge_icode('['_ic);
    //a->merge_icode(constant_expression_ic);
    //a->merge_icode(']'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_DESIGNATOR_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4402-designator->'.' identifier
    //parent:
    // designator_list--> designator
    // designator_list--> designator_list designator
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *'.'=tdefs->m_tk_elems[0];
    //token_defs *identifier=tdefs->m_tk_elems[1];
    //icode *'.'_ic=pcompi->ast_to_icode('.');
    //icode *identifier_ic=pcompi->ast_to_icode(identifier);
    //a->merge_icode('.'_ic);
    //a->merge_icode(identifier_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_STATIC_ASSERT_DECLARATION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4501-static_assert_declaration->STATIC_ASSERT '(' constant_expression ',' STRING_LITERAL ')' ';'
    //parent:
    // declaration--> static_assert_declaration
    // struct_declaration--> static_assert_declaration
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *STATIC_ASSERT=tdefs->m_tk_elems[0];
    //token_defs *'('=tdefs->m_tk_elems[1];
    //token_defs *constant_expression=tdefs->m_tk_elems[2];
    //token_defs *','=tdefs->m_tk_elems[3];
    //token_defs *STRING_LITERAL=tdefs->m_tk_elems[4];
    //token_defs *')'=tdefs->m_tk_elems[5];
    //token_defs *';'=tdefs->m_tk_elems[6];
    //icode *STATIC_ASSERT_ic=pcompi->ast_to_icode(STATIC_ASSERT);
    //icode *'('_ic=pcompi->ast_to_icode('(');
    //icode *constant_expression_ic=pcompi->ast_to_icode(constant_expression);
    //icode *','_ic=pcompi->ast_to_icode(',');
    //icode *STRING_LITERAL_ic=pcompi->ast_to_icode(STRING_LITERAL);
    //icode *')'_ic=pcompi->ast_to_icode(')');
    //icode *';'_ic=pcompi->ast_to_icode(';');
    //a->merge_icode(STATIC_ASSERT_ic);
    //a->merge_icode('('_ic);
    //a->merge_icode(constant_expression_ic);
    //a->merge_icode(','_ic);
    //a->merge_icode(STRING_LITERAL_ic);
    //a->merge_icode(')'_ic);
    //a->merge_icode(';'_ic);
    assert(0);
    return a;
}


class icode *  func_IAN_DECLARATION_LIST_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x5301-declaration_list->declaration
    //parent:
    // function_definition--> declaration_specifiers declarator declaration_list compound_statement
    // declaration_list--> declaration_list declaration
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_DECLARATION_LIST_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x5302-declaration_list->declaration_list declaration
    //parent:
    // function_definition--> declaration_specifiers declarator declaration_list compound_statement
    // declaration_list--> declaration_list declaration
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *declaration_list=tdefs->m_tk_elems[0];
    //token_defs *declaration=tdefs->m_tk_elems[1];
    //icode *declaration_list_ic=pcompi->ast_to_icode(declaration_list);
    //icode *declaration_ic=pcompi->ast_to_icode(declaration);
    //a->merge_icode(declaration_list_ic);
    //a->merge_icode(declaration_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_IDENTIFIER_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x5401-identifier->IDENTIFIER 
	//parent:
	// primary_expression--> identifier
	// enumeration_constant--> identifier
	// postfix_expression--> postfix_expression '.' identifier
	// postfix_expression--> postfix_expression PTR_OP identifier
	// struct_or_union_specifier--> struct_or_union identifier '{' struct_declaration_list '}'
	// struct_or_union_specifier--> struct_or_union identifier
	// enum_specifier--> ENUM identifier '{' enumerator_list '}'
	// enum_specifier--> ENUM identifier '{' enumerator_list ',' '}'
	// enum_specifier--> ENUM identifier
	// direct_declarator_base--> identifier
	// identifier_list--> identifier
	// identifier_list--> identifier_list ',' identifier
	// designator--> '.' identifier
	// labeled_statement--> identifier ':' statement
	// jump_statement--> GOTO identifier ';'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}



class icode *func_token_SIZEOF(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //SIZEOF
    //parent:
    // unary_expression--> SIZEOF unary_expression
    // unary_expression--> SIZEOF '(' type_name ')'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_PTR_OP(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //PTR_OP
    //parent:
    // postfix_expression--> postfix_expression PTR_OP identifier
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_INC_OP(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //INC_OP
    //parent:
    // postfix_expression--> postfix_expression INC_OP
    // unary_expression--> INC_OP unary_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_DEC_OP(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //DEC_OP
    //parent:
    // postfix_expression--> postfix_expression DEC_OP
    // unary_expression--> DEC_OP unary_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_LEFT_OP(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //LEFT_OP
    //parent:
    // shift_expression--> shift_expression LEFT_OP additive_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_RIGHT_OP(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //RIGHT_OP
    //parent:
    // shift_expression--> shift_expression RIGHT_OP additive_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_ROTATE_RIGHT_OP(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //ROTATE_RIGHT_OP
    //parent:
    // shift_expression--> shift_expression ROTATE_RIGHT_OP additive_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_ROTATE_LEFT_OP(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //ROTATE_LEFT_OP
    //parent:
    // shift_expression--> shift_expression ROTATE_LEFT_OP additive_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_LE_OP(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //LE_OP
    //parent:
    // relational_expression--> relational_expression LE_OP shift_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_GE_OP(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //GE_OP
    //parent:
    // relational_expression--> relational_expression GE_OP shift_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_EQ_OP(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //EQ_OP
    //parent:
    // equality_expression--> equality_expression EQ_OP relational_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_NE_OP(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //NE_OP
    //parent:
    // equality_expression--> equality_expression NE_OP relational_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_AND_OP(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //AND_OP
    //parent:
    // logical_and_expression--> logical_and_expression AND_OP inclusive_or_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_OR_OP(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //OR_OP
    //parent:
    // logical_or_expression--> logical_or_expression OR_OP logical_and_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_MUL_ASSIGN(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //MUL_ASSIGN
    //parent:
    // assignment_operator--> MUL_ASSIGN
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_DIV_ASSIGN(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //DIV_ASSIGN
    //parent:
    // assignment_operator--> DIV_ASSIGN
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_MOD_ASSIGN(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //MOD_ASSIGN
    //parent:
    // assignment_operator--> MOD_ASSIGN
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_ADD_ASSIGN(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //ADD_ASSIGN
    //parent:
    // assignment_operator--> ADD_ASSIGN
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_SUB_ASSIGN(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //SUB_ASSIGN
    //parent:
    // assignment_operator--> SUB_ASSIGN
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_LEFT_ASSIGN(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //LEFT_ASSIGN
    //parent:
    // assignment_operator--> LEFT_ASSIGN
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_RIGHT_ASSIGN(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //RIGHT_ASSIGN
    //parent:
    // assignment_operator--> RIGHT_ASSIGN
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_AND_ASSIGN(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //AND_ASSIGN
    //parent:
    // assignment_operator--> AND_ASSIGN
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_XOR_ASSIGN(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //XOR_ASSIGN
    //parent:
    // assignment_operator--> XOR_ASSIGN
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_OR_ASSIGN(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //OR_ASSIGN
    //parent:
    // assignment_operator--> OR_ASSIGN
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}


class icode *func_token_ELLIPSIS(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //ELLIPSIS
    //parent:
    // parameter_type_list--> parameter_list ',' ELLIPSIS
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_FUNC_DEF_ARG;
    a->name="ellipsis";
    a->m_bit_width = 8;
    //assert(0);
    return a;
}
class icode *func_token_CASE(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //CASE
    //parent:
    // labeled_statement--> CASE constant_expression ':' statement
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_DEFAULT(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //DEFAULT
    //parent:
    // generic_association--> DEFAULT ':' assignment_expression
    // labeled_statement--> DEFAULT ':' statement
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_IF(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //IF
    //parent:
    // selection_statement--> IF '(' expression ')' statement ELSE statement
    // selection_statement--> IF '(' expression ')' statement
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_ELSE(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //ELSE
    //parent:
    // selection_statement--> IF '(' expression ')' statement ELSE statement
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_SWITCH(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //SWITCH
    //parent:
    // selection_statement--> SWITCH '(' expression ')' statement
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_WHILE(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //WHILE
    //parent:
    // iteration_statement--> WHILE '(' expression ')' statement
    // iteration_statement--> DO statement WHILE '(' expression ')' ';'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_DO(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //DO
    //parent:
    // iteration_statement--> DO statement WHILE '(' expression ')' ';'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_FOR(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //FOR
    //parent:
    // iteration_statement--> FOR '(' expression_statement expression_statement ')' statement
    // iteration_statement--> FOR '(' expression_statement expression_statement expression ')' statement
    // iteration_statement--> FOR '(' declaration expression_statement ')' statement
    // iteration_statement--> FOR '(' declaration expression_statement expression ')' statement
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_GOTO(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //GOTO
    //parent:
    // jump_statement--> GOTO identifier ';'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_CONTINUE(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //CONTINUE
    //parent:
    // jump_statement--> CONTINUE ';'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_BREAK(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //BREAK
    //parent:
    // jump_statement--> BREAK ';'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_RETURN(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //RETURN
    //parent:
    // jump_statement--> RETURN ';'
    // jump_statement--> RETURN expression ';'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_ALIGNAS(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //ALIGNAS
    //parent:
    // alignment_specifier--> ALIGNAS '(' type_name ')'
    // alignment_specifier--> ALIGNAS '(' constant_expression ')'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_ALIGNOF(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //ALIGNOF
    //parent:
    // unary_expression--> ALIGNOF '(' type_name ')'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}

class icode *func_token_GENERIC(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //GENERIC
    //parent:
    // generic_selection--> GENERIC '(' assignment_expression ',' generic_assoc_list ')'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}

class icode *func_token_STATIC_ASSERT(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //STATIC_ASSERT
    //parent:
    // static_assert_declaration--> STATIC_ASSERT '(' constant_expression ',' STRING_LITERAL ')' ';'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}

class icode *func_token_CAST(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //CAST
    //parent:
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_INIT_DEEP(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //INIT_DEEP
    //parent:
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_INIT_NODE(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //INIT_NODE
    //parent:
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_BLOCK(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //BLOCK
    //parent:
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_CALL(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //CALL
    //parent:
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_PARAM(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //PARAM
    //parent:
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}

class icode *func_token_LINE_NUM(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //LINE_NUM
    //parent:
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_INTERRUPT(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //INTERRUPT
    //parent:
    // function_attribute1--> INTERRUPT constant_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_USING(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //USING
    //parent:
    // function_attribute1--> USING constant_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_REENTRANT(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //REENTRANT
    //parent:
    // function_attribute1--> REENTRANT
    if(result_ic==NULL)
    {
        icode *a = pcompi->new_icode();
        a->m_type=ICODE_TYPE_BLOCK;

        result_ic=a;
        a->m_type=ICODE_TYPE_DEF_VAR;
    }
    result_ic->is_reentrant = 1;
    return result_ic;
}
class icode *func_token_REGPARAMS(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //REGPARAMS
    //parent:
    // function_attribute1--> REGPARAMS string
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}

}//namespace end
