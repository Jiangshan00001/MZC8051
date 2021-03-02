/****************
 *
 * 未实现列表：旧的函数声明： func1(a,b):int a, int b{}
 *
 *
 *
 *
 *
constant
        : I_CONSTANT
        | F_CONSTANT
        | ENUMERATION_CONSTANT
        ;

enumeration_constant
        : identifier
        ;

string
        : STRING_LITERAL
        | FUNC_NAME
        ;
**/

#include "ast_to_icode_common.h"

#include "parser.h"
#include "comp_context_gen_defs.h"
#include <assert.h>
#include "icode.h"
#include "comp_context.h"
#include "token_defs.h"
#include "mylog.h"
#include "str2number.h"
#include "string_eval.h"
#include "target_base.h"
using mylog::cerr;
using mylog::cout;


namespace NS_C512IR{



class icode *  func_IAN_IDENTIFIER_LIST_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3c01-identifier_list->identifier
    //parent:
    // direct_declarator_function1--> direct_declarator_function1 '(' identifier_list ')'
    // identifier_list--> identifier_list ',' identifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}

class icode *  func_IAN_IDENTIFIER_LIST_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 旧的函数声明： func(a, b,c): int a, int b, float c{}
    /// 不再支持


    //0x3c02-identifier_list->identifier_list ',' identifier
    //parent:
    // direct_declarator_function1--> direct_declarator_function1 '(' identifier_list ')'
    // identifier_list--> identifier_list ',' identifier
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *identifier_list=tdefs->m_tk_elems[0];
    //token_defs *','=tdefs->m_tk_elems[1];
    //token_defs *identifier=tdefs->m_tk_elems[2];
    //icode *identifier_list_ic=pcompi->ast_to_icode(identifier_list);
    //icode *','_ic=pcompi->ast_to_icode(',');
    //icode *identifier_ic=pcompi->ast_to_icode(identifier);
    //a->merge_icode(identifier_list_ic);
    //a->merge_icode(','_ic);
    //a->merge_icode(identifier_ic);
    assert(0);
    return a;
}

class icode *func_token_FUNC_NAME(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //FUNC_NAME

    /// 此处要放入所在的函数名称

    icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);

    icode *b = pcompi->new_icode(ICODE_TYPE_CONST_STRING);
    b->name = pcompi->m_curr_func->name;
    b->const_refresh_width();

    //b->name = pcompi->string_eval(b->name); 函数名称，不需要转义
    a->result = pcompi->new_ref_icode(b);
    a->result->m_bit_width = b->name.size()*8+8;

    a->merge_icode(b);

    return a;
}

class icode *func_token_STRING_LITERAL(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //STRING_LITERAL
    //parent:
    // string--> STRING_LITERAL
    // static_assert_declaration--> STATIC_ASSERT '(' constant_expression ',' STRING_LITERAL ')' ';'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    icode *b = pcompi->new_icode();
    b->m_type = ICODE_TYPE_CONST_STRING;
    b->name = tdefs->val_str;
    b->const_refresh_width();

    b->name = string_eval(b->name);
    a->result = pcompi->new_ref_icode(b);
    a->result->m_bit_width = b->name.size()*8+8;

    //2021.1.7 string不再放在block中，只在result中
    //a->merge_icode(b);

    return a;
}

class icode *func_token_IDENTIFIER(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //IDENTIFIER
    //parent:
    // identifier--> IDENTIFIER
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    ///查找符号表，如果找到，则返回REF，
    /// 如果未找到，则返回ref，但是result=NULL

    sym * s = pcompi->find_symbol(tdefs->val_str);

    a->result = pcompi->new_icode();
    a->result->name = tdefs->val_str;
    a->result->m_type = ICODE_TYPE_SYMBOL_REF;

    if((s==NULL))
    {
        a->result->result = NULL;
        return a;
    }
    /// 2020.8.23 pcompi->new_ref_icode( 添加引用导致错误？？？
    a->result = pcompi->new_ref_icode(s->def_icode);
    return a;
}

///
/// \brief func_token_I_CONSTANT
/// \param pcompi
/// \param tdefs
/// \param need_result_icode
/// \param result_ic
/// \return
/// \todo 此处如果是转义字符，则会报错： '\x23' '\t' 等
class icode *func_token_I_CONSTANT(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //I_CONSTANT
    //parent:
    // constant--> I_CONSTANT
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    icode *b = pcompi->new_icode();
    b->m_type = ICODE_TYPE_I_CONST;
    b->name = tdefs->val_str;
    b->num = StrToNumber(tdefs->val_str);
    b->const_refresh_width();
    //a->sub_icode.push_back(b);
    a->result = b;
    return a;
}

class icode *func_token_F_CONSTANT(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //F_CONSTANT
    //parent:
    // constant--> F_CONSTANT
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    icode *b = pcompi->new_icode();
    b->m_type = ICODE_TYPE_F_CONST;
    b->name = tdefs->val_str;
    b->fnum = StrToFloat(tdefs->val_str);
    b->m_bit_width = pcompi->m_top_icodes->m_target->get_basic_type_bit_width("float");
    //a->sub_icode.push_back(b);
    b->is_float32 = 1;
    b->const_refresh_width();
    a->result = b;

    return a;
}

class icode *  func_IAN_CONSTANT_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x101-constant->I_CONSTANT
    //parent:
    // primary_expression--> constant
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}

class icode *  func_IAN_CONSTANT_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x102-constant->F_CONSTANT
    //parent:
    // primary_expression--> constant
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}

class icode *  func_IAN_CONSTANT_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x103-constant->ENUMERATION_CONSTANT
    //parent:
    // primary_expression--> constant
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}

class icode *  func_IAN_STRING_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x301-string->STRING_LITERAL
    //parent:
    // primary_expression--> string
    // function_attribute1--> REGPARAMS string
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}


class icode *  func_IAN_STRING_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x302-string->FUNC_NAME
    //parent:
    // primary_expression--> string
    // function_attribute1--> REGPARAMS string
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}

}//namespace end

