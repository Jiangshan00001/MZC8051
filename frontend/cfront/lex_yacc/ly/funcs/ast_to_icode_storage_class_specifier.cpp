/*****************************************************
 *
 * 输入： tdefs result_ic
 * 输出： 结果放入result_ic. 返回值为NULL
 *
 *

storage_class_specifier
    : TYPEDEF
    | EXTERN
    | STATIC
    | THREAD_LOCAL
    | AUTO
    | REGISTER
    | STORAGE_SPEC_C51
    ;

type_qualifier
    : CONST
    | RESTRICT
    | VOLATILE
    | ATOMIC
    ;

function_specifier
    : INLINE
    | NORETURN
    ;

alignment_specifier
    : ALIGNAS '(' type_name ')'
    | ALIGNAS '(' constant_expression ')'
    ;

 *
 * ********************************/


#include "ast_to_icode_storage_class_specifier.h"
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



namespace NS_C2IR{




class icode *  func_IAN_STORAGE_CLASS_SPECIFIER_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2001-storage_class_specifier->TYPEDEF
    //parent:
    // declaration_specifiers_--> storage_class_specifier declaration_specifiers_
    // declaration_specifiers_--> storage_class_specifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_STORAGE_CLASS_SPECIFIER_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2002-storage_class_specifier->EXTERN
    //parent:
    // declaration_specifiers_--> storage_class_specifier declaration_specifiers_
    // declaration_specifiers_--> storage_class_specifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_STORAGE_CLASS_SPECIFIER_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2003-storage_class_specifier->STATIC
    //parent:
    // declaration_specifiers_--> storage_class_specifier declaration_specifiers_
    // declaration_specifiers_--> storage_class_specifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_STORAGE_CLASS_SPECIFIER_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2004-storage_class_specifier->THREAD_LOCAL
    //parent:
    // declaration_specifiers_--> storage_class_specifier declaration_specifiers_
    // declaration_specifiers_--> storage_class_specifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_STORAGE_CLASS_SPECIFIER_5(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2005-storage_class_specifier->AUTO
    //parent:
    // declaration_specifiers_--> storage_class_specifier declaration_specifiers_
    // declaration_specifiers_--> storage_class_specifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_STORAGE_CLASS_SPECIFIER_6(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2006-storage_class_specifier->REGISTER
    //parent:
    // declaration_specifiers_--> storage_class_specifier declaration_specifiers_
    // declaration_specifiers_--> storage_class_specifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_STORAGE_CLASS_SPECIFIER_7(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2007-storage_class_specifier->STORAGE_SPEC_C51
    //parent:
    // declaration_specifiers_--> storage_class_specifier declaration_specifiers_
    // declaration_specifiers_--> storage_class_specifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}




class icode *func_token_TYPEDEF(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //TYPEDEF
    //parent:
    // storage_class_specifier--> TYPEDEF

    if(result_ic)
    {
        result_ic->m_type_str = result_ic->m_type_str+" "+tdefs->val_str ;

        //此处是定义一个typedef
        result_ic->is_typedef = 1;
    }

    return NULL;
}
class icode *func_token_EXTERN(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //EXTERN
    //parent:
    // storage_class_specifier--> EXTERN

    if(result_ic)
    {
        result_ic->m_type_str = result_ic->m_type_str+" "+tdefs->val_str ;

        result_ic->is_extern = 1;
    }

    return NULL;
}
class icode *func_token_STATIC(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //STATIC
    //parent:
    // storage_class_specifier--> STATIC
    // direct_declarator_array--> direct_declarator_array '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' STATIC assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_abstract_declarator--> '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> '[' STATIC assignment_expression ']'
    // direct_abstract_declarator--> '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'


    if(result_ic)
    {
        result_ic->m_type_str = result_ic->m_type_str+" "+tdefs->val_str ;

        result_ic->is_static=1;
    }

    return NULL;
}


class icode *func_token_AUTO(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //AUTO
    //parent:
    // storage_class_specifier--> AUTO
    if(result_ic)
    {
        result_ic->m_type_str = result_ic->m_type_str+" "+tdefs->val_str ;

        result_ic->is_auto=1;
    }

    return NULL;
}
class icode *func_token_REGISTER(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //REGISTER
    //parent:
    // storage_class_specifier--> REGISTER

    if(result_ic)
    {
        result_ic->m_type_str = result_ic->m_type_str+" "+tdefs->val_str ;

        result_ic->is_register=1;
    }

    return NULL;
}

class icode *func_token_THREAD_LOCAL(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //THREAD_LOCAL
    //parent:
    // storage_class_specifier--> THREAD_LOCAL
    if(result_ic)
    {
        result_ic->m_type_str = result_ic->m_type_str+" "+tdefs->val_str ;

        result_ic->is_thread_local=1;
    }

    return NULL;
}


class icode *func_token_STORAGE_SPEC_C51(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //STORAGE_SPEC_C51
    //parent:
    // storage_class_specifier--> STORAGE_SPEC_C51
    if(result_ic)
    {
        result_ic->m_type_str = result_ic->m_type_str+" "+tdefs->val_str ;

        if(tdefs->val_str=="xdata")
        {
            result_ic->is_xdata = 1;
        }
        if(tdefs->val_str=="data")
        {
            result_ic->is_data = 1;
        }
        if(tdefs->val_str=="idata")
        {
            result_ic->is_idata = 1;
        }
        if(tdefs->val_str=="pdata")
        {
            result_ic->is_pdata = 1;
        }
        if(tdefs->val_str=="code")
        {
            result_ic->is_code = 1;
        }

        return NULL;
    }

    assert(0);
    return NULL;
}



class icode *func_token_INLINE(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //INLINE
    //parent:
    // function_specifier--> INLINE

    result_ic->m_type_str = result_ic->m_type_str+" "+tdefs->val_str ;

        result_ic->is_inline=1;

    return NULL;
}

class icode *func_token_NORETURN(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //NORETURN
    //parent:
    // function_specifier--> NORETURN
    result_ic->m_type_str = result_ic->m_type_str+" "+tdefs->val_str ;

    result_ic->is_noreturn = 1;
    return NULL;
}


class icode *func_token_CONST(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //CONST
    //parent:
    // type_qualifier--> CONST
        //const属性暂时不起作用
        //result_ic->is_code = 1;
    result_ic->m_type_str = result_ic->m_type_str+" "+tdefs->val_str ;
    result_ic->is_const = 1;

    return NULL;
}
class icode *func_token_RESTRICT(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //RESTRICT
    //parent:
    // type_qualifier--> RESTRICT
    result_ic->m_type_str = result_ic->m_type_str+" "+tdefs->val_str ;
    result_ic->is_restrict = 1;

    return NULL;
}
class icode *func_token_VOLATILE(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //VOLATILE
    //parent:
    // type_qualifier--> VOLATILE
    result_ic->m_type_str = result_ic->m_type_str+" "+tdefs->val_str ;
    result_ic->is_volatile = 1;

    return NULL;
}
class icode *func_token_ATOMIC(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //ATOMIC
    //parent:
    // atomic_type_specifier--> ATOMIC '(' type_name ')'
    // type_qualifier--> ATOMIC

    result_ic->m_type_str = result_ic->m_type_str+" "+tdefs->val_str ;
    result_ic->is_atomic = 1;

    return NULL;
}






class icode *  func_IAN_FUNCTION_SPECIFIER_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2e01-function_specifier->INLINE
    //parent:
    // declaration_specifiers_--> function_specifier declaration_specifiers_
    // declaration_specifiers_--> function_specifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_FUNCTION_SPECIFIER_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2e02-function_specifier->NORETURN
    //parent:
    // declaration_specifiers_--> function_specifier declaration_specifiers_
    // declaration_specifiers_--> function_specifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}



class icode *  func_IAN_TYPE_QUALIFIER_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2d01-type_qualifier->CONST
    //parent:
    // declaration_specifiers_--> type_qualifier declaration_specifiers_
    // declaration_specifiers_--> type_qualifier
    // specifier_qualifier_list--> type_qualifier specifier_qualifier_list
    // specifier_qualifier_list--> type_qualifier
    // type_qualifier_list--> type_qualifier
    // type_qualifier_list--> type_qualifier_list type_qualifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_QUALIFIER_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2d02-type_qualifier->RESTRICT
    //parent:
    // declaration_specifiers_--> type_qualifier declaration_specifiers_
    // declaration_specifiers_--> type_qualifier
    // specifier_qualifier_list--> type_qualifier specifier_qualifier_list
    // specifier_qualifier_list--> type_qualifier
    // type_qualifier_list--> type_qualifier
    // type_qualifier_list--> type_qualifier_list type_qualifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_QUALIFIER_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2d03-type_qualifier->VOLATILE
    //parent:
    // declaration_specifiers_--> type_qualifier declaration_specifiers_
    // declaration_specifiers_--> type_qualifier
    // specifier_qualifier_list--> type_qualifier specifier_qualifier_list
    // specifier_qualifier_list--> type_qualifier
    // type_qualifier_list--> type_qualifier
    // type_qualifier_list--> type_qualifier_list type_qualifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_QUALIFIER_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2d04-type_qualifier->ATOMIC
    //parent:
    // declaration_specifiers_--> type_qualifier declaration_specifiers_
    // declaration_specifiers_--> type_qualifier
    // specifier_qualifier_list--> type_qualifier specifier_qualifier_list
    // specifier_qualifier_list--> type_qualifier
    // type_qualifier_list--> type_qualifier
    // type_qualifier_list--> type_qualifier_list type_qualifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}


/** TODO  **/


class icode *  func_IAN_ALIGNMENT_SPECIFIER_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2f01-alignment_specifier->ALIGNAS '(' type_name ')'
    //parent:
    // declaration_specifiers_--> alignment_specifier declaration_specifiers_
    // declaration_specifiers_--> alignment_specifier
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *ALIGNAS=tdefs->m_tk_elems[0];
    //token_defs *'('=tdefs->m_tk_elems[1];
    //token_defs *type_name=tdefs->m_tk_elems[2];
    //token_defs *')'=tdefs->m_tk_elems[3];
    //icode *ALIGNAS_ic=pcompi->ast_to_icode(ALIGNAS);
    //icode *'('_ic=pcompi->ast_to_icode('(');
    //icode *type_name_ic=pcompi->ast_to_icode(type_name);
    //icode *')'_ic=pcompi->ast_to_icode(')');
    //a->merge_icode(ALIGNAS_ic);
    //a->merge_icode('('_ic);
    //a->merge_icode(type_name_ic);
    //a->merge_icode(')'_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_ALIGNMENT_SPECIFIER_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2f02-alignment_specifier->ALIGNAS '(' constant_expression ')'
    //parent:
    // declaration_specifiers_--> alignment_specifier declaration_specifiers_
    // declaration_specifiers_--> alignment_specifier
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *ALIGNAS=tdefs->m_tk_elems[0];
    //token_defs *'('=tdefs->m_tk_elems[1];
    //token_defs *constant_expression=tdefs->m_tk_elems[2];
    //token_defs *')'=tdefs->m_tk_elems[3];
    //icode *ALIGNAS_ic=pcompi->ast_to_icode(ALIGNAS);
    //icode *'('_ic=pcompi->ast_to_icode('(');
    //icode *constant_expression_ic=pcompi->ast_to_icode(constant_expression);
    //icode *')'_ic=pcompi->ast_to_icode(')');
    //a->merge_icode(ALIGNAS_ic);
    //a->merge_icode('('_ic);
    //a->merge_icode(constant_expression_ic);
    //a->merge_icode(')'_ic);
    assert(0);
    return a;
}





}//namespace end




