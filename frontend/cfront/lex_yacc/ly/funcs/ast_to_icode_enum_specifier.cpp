/****************************************
 *
 *、
 * 输入： tdefs result_ic
 * 输出： 结果放入result_ic. 返回值为NULL
 *
 * 未完成：无（所有已完成）
 *
 *
enum_specifier
        : ENUM '{' enumerator_list '}'
        | ENUM '{' enumerator_list ',' '}'
        | ENUM identifier '{' enumerator_list '}'
        | ENUM identifier '{' enumerator_list ',' '}'
        | ENUM identifier
        ;

enumerator_list
    : enumerator
    | enumerator_list ',' enumerator
    ;

enumerator
    : enumeration_constant '=' constant_expression
    | enumeration_constant
    ;
enumeration_constant
        : identifier
        ;
 *
 *
 * 使用的context变量
 * pcompi->m_curr_enum_name
 * pcompi->m_curr_enum_index
 * pcompi->m_enum_bitwidth
 *
 * pcompi->m_enum_items
 * pcompi->m_enum_def
 *
 * *****************************************/

#include "ast_to_icode_enum_specifier.h"
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




///
/// \brief enum_get_define
/// \param enum_name
/// \param result_ic
/// \return
/// 通过枚举类型名字，获取变量类型
int enum_get_define(comp_context* pcompi, std::string enum_name, class icode *result_ic)
{
    //enum的位宽已经预先计算并存入m_enum_bitwidth中
    result_ic->m_bit_width = pcompi->m_enum_bitwidth[enum_name];
    result_ic->m_type_str = result_ic->m_type_str+" enum "+ enum_name;

    return 0;
}

class icode *  enum_define(class comp_context* pcompi, token_defs* enumerator_list,std::string enum_name, bool need_result_icode, class icode* result_ic)
{

    pcompi->m_curr_enum_name=enum_name;
    pcompi->m_curr_enum_index =0;

    pcompi->ast_to_icode(enumerator_list);

    if(pcompi->m_curr_enum_index > 65535)
    {
        pcompi->m_enum_bitwidth[enum_name] = 32;
    }
    else if(pcompi->m_curr_enum_index>255)
    {
        pcompi->m_enum_bitwidth[enum_name] = 16;
    }
    else
    {
        pcompi->m_enum_bitwidth[enum_name] = 8;
    }

    //enum定义完成后。将名称清空
    pcompi->m_curr_enum_name="";
    pcompi->m_curr_enum_index = 0;


    //枚举类型定义完成后，修改result_ic为指定的类型
    enum_get_define(pcompi, enum_name, result_ic);

    return NULL;
}



class icode *  func_IAN_ENUM_SPECIFIER_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2901-enum_specifier->ENUM '{' enumerator_list '}'
    //parent:
    // type_specifier--> enum_specifier


    //新生成一个enum。返回enum的名称icode
    token_defs * enumerator_list = tdefs->m_tk_elems[2];
    std::string enum_name = pcompi->get_temp_name("unname_enum_");

    return enum_define(pcompi, enumerator_list, enum_name, need_result_icode, result_ic );
}

class icode *  func_IAN_ENUM_SPECIFIER_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2902-enum_specifier->ENUM '{' enumerator_list ',' '}'
    //parent:
    // type_specifier--> enum_specifier
    return func_IAN_ENUM_SPECIFIER_1(pcompi, tdefs, need_result_icode, result_ic);
}

class icode *  func_IAN_ENUM_SPECIFIER_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2903-enum_specifier->ENUM identifier '{' enumerator_list '}'
    //parent:
    // type_specifier--> enum_specifier

    token_defs * enumerator_list = tdefs->m_tk_elems[3];
    token_defs * enum_name_tk = tdefs->m_tk_elems[1];

    icode *name_ic = pcompi->ast_to_icode(enum_name_tk, 1);

    assert(name_ic->result->m_type==ICODE_TYPE_SYMBOL_REF);
    if(name_ic->result->result!=NULL)
    {
        //name already defined error;
        cerr<<"ERROR: name already defined error:" << name_ic->result->name<<"\n";
        return NULL;
    }

    std::string enum_name = name_ic->result->name;
    return enum_define(pcompi, enumerator_list, enum_name, need_result_icode, result_ic );
}

class icode *  func_IAN_ENUM_SPECIFIER_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2904-enum_specifier->ENUM identifier '{' enumerator_list ',' '}'
    //parent:
    // type_specifier--> enum_specifier
    return func_IAN_ENUM_SPECIFIER_3(pcompi, tdefs, need_result_icode, result_ic);
}

class icode *  func_IAN_ENUMERATOR_LIST_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2a01-enumerator_list->enumerator
    //parent:
    // enum_specifier--> ENUM '{' enumerator_list '}'
    // enum_specifier--> ENUM '{' enumerator_list ',' '}'
    // enum_specifier--> ENUM identifier '{' enumerator_list '}'
    // enum_specifier--> ENUM identifier '{' enumerator_list ',' '}'
    // enumerator_list--> enumerator_list ',' enumerator
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}

class icode *  func_IAN_ENUMERATOR_LIST_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2a02-enumerator_list->enumerator_list ',' enumerator
    //parent:
    // enum_specifier--> ENUM '{' enumerator_list '}'
    // enum_specifier--> ENUM '{' enumerator_list ',' '}'
    // enum_specifier--> ENUM identifier '{' enumerator_list '}'
    // enum_specifier--> ENUM identifier '{' enumerator_list ',' '}'
    // enumerator_list--> enumerator_list ',' enumerator


    token_defs * elist = tdefs->m_tk_elems[0];
    token_defs * eor = tdefs->m_tk_elems[2];

    assert(pcompi->m_curr_enum_name.size()>0);

    pcompi->ast_to_icode(elist);
    pcompi->ast_to_icode(eor);


    return NULL;
}

class icode *  func_IAN_ENUMERATOR_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2b01-enumerator->enumeration_constant '=' constant_expression
    //parent:
    // enumerator_list--> enumerator
    // enumerator_list--> enumerator_list ',' enumerator


    token_defs * econst = tdefs->m_tk_elems[0];
    token_defs * econst_expr = tdefs->m_tk_elems[2];

    assert(pcompi->m_curr_enum_name.size()>0);


    icode * e_const_ic = pcompi->ast_to_icode(econst, 1);
    icode * e_const_expr_ic = pcompi->ast_to_icode(econst_expr, 1);

    //此处添加枚举类型内容
    //m_enum_items;
    //m_enum_def;
    pcompi->m_enum_items[e_const_ic->result->name] = e_const_expr_ic->result->num;
    pcompi->m_enum_def[pcompi->m_curr_enum_name].push_back(e_const_ic->result->name);
    pcompi->m_curr_enum_index = e_const_expr_ic->result->num;
    pcompi->m_curr_enum_index++;

    return NULL;
}

class icode *  func_IAN_ENUMERATOR_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2b02-enumerator->enumeration_constant
    //parent:
    // enumerator_list--> enumerator
    // enumerator_list--> enumerator_list ',' enumerator
    icode *e_const_ic = pcompi->ast_to_icode(tdefs,1);

    pcompi->m_enum_items[e_const_ic->result->name] = pcompi->m_curr_enum_index;
    pcompi->m_enum_def[pcompi->m_curr_enum_name].push_back(e_const_ic->result->name);
    pcompi->m_curr_enum_index++;

    return NULL;
}

class icode *  func_IAN_ENUMERATION_CONSTANT_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x201-enumeration_constant->identifier
    //parent:
    // enumerator--> enumeration_constant '=' constant_expression
    // enumerator--> enumeration_constant
    icode * a = pcompi->ast_to_icode(tdefs,1);


    assert(a->result->m_type==ICODE_TYPE_SYMBOL_REF);
    if(a->result->result)
    {
        cerr<<"ERROR: const already defined error. "<< a->result->name<<"\n";
        return a;
    }
    return a;
}

class icode *func_token_ENUM(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //ENUM
    //parent:
    // enum_specifier--> ENUM '{' enumerator_list '}'
    // enum_specifier--> ENUM '{' enumerator_list ',' '}'
    // enum_specifier--> ENUM identifier '{' enumerator_list '}'
    // enum_specifier--> ENUM identifier '{' enumerator_list ',' '}'
    // enum_specifier--> ENUM identifier

    cerr<<"this should never be called\n";

    assert(0);

}

class icode *func_token_ENUMERATION_CONSTANT(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //ENUMERATION_CONSTANT
    //parent:
    // constant--> ENUMERATION_CONSTANT

    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    icode *b = pcompi->new_icode();
    b->m_type = ICODE_TYPE_I_CONST;
    b->name = tdefs->val_str;

    assert(pcompi->m_enum_items.find(tdefs->val_str)!=pcompi->m_enum_items.end());

    b->num = pcompi->m_enum_items[tdefs->val_str];
    b->fnum = b->num;
    b->const_refresh_width();
    //a->sub_icode.push_back(b);
    a->result = (b) ;
    return a;
}


class icode *  func_IAN_ENUM_SPECIFIER_5(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2905-enum_specifier->ENUM identifier
    //parent:
    // type_specifier--> enum_specifier

    std::string enum_name = tdefs->m_tk_elems[1]->val_str;
    enum_get_define(pcompi, enum_name, result_ic);

    return NULL;
}

}//namespace end
