/***************************************
 *
 * 输入： tdefs result_ic
 * 输出： 结果放入result_ic. 返回值为NULL
 * 此语法返回NULL。 只修改result_ic中内容。 result_ic必须存在，并默认为DEF_VAR
 *
 *
type_specifier
    : VOID
    | CHAR
    | SHORT
    | INT
    | LONG
    | FLOAT
    | DOUBLE
    | SIGNED
    | UNSIGNED
    | BOOL
    | COMPLEX
    | IMAGINARY
    | atomic_type_specifier
    | struct_or_union_specifier
    | enum_specifier
    | TYPEDEF_NAME
    | SFR
    | BIT
    | SBIT
    | SFR16
    | SFR32
    ;
 *
 *
 * ******************************************/
#include "ast_to_icode_type_specifier.h"
#include "parser.h"
#include "comp_context_gen_defs.h"
#include <assert.h>
#include "icode.h"
#include "comp_context.h"
#include "token_defs.h"
#include "mylog.h"
#include "str2number.h"
#include "driver.h"
#include "target_base.h"
using mylog::cerr;
using mylog::cout;



namespace NS_C2IR{



class icode *  func_IAN_TYPE_SPECIFIER_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2101-type_specifier->VOID
    //parent:
    // declaration_specifiers_--> type_specifier declaration_specifiers_
    // declaration_specifiers_--> type_specifier
    // specifier_qualifier_list--> type_specifier specifier_qualifier_list
    // specifier_qualifier_list--> type_specifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2102-type_specifier->CHAR
    //parent:
    // declaration_specifiers_--> type_specifier declaration_specifiers_
    // declaration_specifiers_--> type_specifier
    // specifier_qualifier_list--> type_specifier specifier_qualifier_list
    // specifier_qualifier_list--> type_specifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2103-type_specifier->SHORT
    //parent:
    // declaration_specifiers_--> type_specifier declaration_specifiers_
    // declaration_specifiers_--> type_specifier
    // specifier_qualifier_list--> type_specifier specifier_qualifier_list
    // specifier_qualifier_list--> type_specifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2104-type_specifier->INT
    //parent:
    // declaration_specifiers_--> type_specifier declaration_specifiers_
    // declaration_specifiers_--> type_specifier
    // specifier_qualifier_list--> type_specifier specifier_qualifier_list
    // specifier_qualifier_list--> type_specifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_5(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2105-type_specifier->LONG
    //parent:
    // declaration_specifiers_--> type_specifier declaration_specifiers_
    // declaration_specifiers_--> type_specifier
    // specifier_qualifier_list--> type_specifier specifier_qualifier_list
    // specifier_qualifier_list--> type_specifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_6(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2106-type_specifier->FLOAT
    //parent:
    // declaration_specifiers_--> type_specifier declaration_specifiers_
    // declaration_specifiers_--> type_specifier
    // specifier_qualifier_list--> type_specifier specifier_qualifier_list
    // specifier_qualifier_list--> type_specifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_7(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2107-type_specifier->DOUBLE
    //parent:
    // declaration_specifiers_--> type_specifier declaration_specifiers_
    // declaration_specifiers_--> type_specifier
    // specifier_qualifier_list--> type_specifier specifier_qualifier_list
    // specifier_qualifier_list--> type_specifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_8(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2108-type_specifier->SIGNED
    //parent:
    // declaration_specifiers_--> type_specifier declaration_specifiers_
    // declaration_specifiers_--> type_specifier
    // specifier_qualifier_list--> type_specifier specifier_qualifier_list
    // specifier_qualifier_list--> type_specifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_9(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2109-type_specifier->UNSIGNED
    //parent:
    // declaration_specifiers_--> type_specifier declaration_specifiers_
    // declaration_specifiers_--> type_specifier
    // specifier_qualifier_list--> type_specifier specifier_qualifier_list
    // specifier_qualifier_list--> type_specifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_10(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x210a-type_specifier->BOOL
    //parent:
    // declaration_specifiers_--> type_specifier declaration_specifiers_
    // declaration_specifiers_--> type_specifier
    // specifier_qualifier_list--> type_specifier specifier_qualifier_list
    // specifier_qualifier_list--> type_specifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_11(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x210b-type_specifier->COMPLEX
    //parent:
    // declaration_specifiers_--> type_specifier declaration_specifiers_
    // declaration_specifiers_--> type_specifier
    // specifier_qualifier_list--> type_specifier specifier_qualifier_list
    // specifier_qualifier_list--> type_specifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_12(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x210c-type_specifier->IMAGINARY
    //parent:
    // declaration_specifiers_--> type_specifier declaration_specifiers_
    // declaration_specifiers_--> type_specifier
    // specifier_qualifier_list--> type_specifier specifier_qualifier_list
    // specifier_qualifier_list--> type_specifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_13(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x210d-type_specifier->atomic_type_specifier
    //parent:
    // declaration_specifiers_--> type_specifier declaration_specifiers_
    // declaration_specifiers_--> type_specifier
    // specifier_qualifier_list--> type_specifier specifier_qualifier_list
    // specifier_qualifier_list--> type_specifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_14(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x210e-type_specifier->struct_or_union_specifier
    //parent:
    // declaration_specifiers_--> type_specifier declaration_specifiers_
    // declaration_specifiers_--> type_specifier
    // specifier_qualifier_list--> type_specifier specifier_qualifier_list
    // specifier_qualifier_list--> type_specifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_15(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x210f-type_specifier->enum_specifier
    //parent:
    // declaration_specifiers_--> type_specifier declaration_specifiers_
    // declaration_specifiers_--> type_specifier
    // specifier_qualifier_list--> type_specifier specifier_qualifier_list
    // specifier_qualifier_list--> type_specifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_16(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2110-type_specifier->TYPEDEF_NAME
    //parent:
    // declaration_specifiers_--> type_specifier declaration_specifiers_
    // declaration_specifiers_--> type_specifier
    // specifier_qualifier_list--> type_specifier specifier_qualifier_list
    // specifier_qualifier_list--> type_specifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_17(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2111-type_specifier->SFR
    //parent:
    // declaration_specifiers_--> type_specifier declaration_specifiers_
    // declaration_specifiers_--> type_specifier
    // specifier_qualifier_list--> type_specifier specifier_qualifier_list
    // specifier_qualifier_list--> type_specifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_18(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2112-type_specifier->BIT
    //parent:
    // declaration_specifiers_--> type_specifier declaration_specifiers_
    // declaration_specifiers_--> type_specifier
    // specifier_qualifier_list--> type_specifier specifier_qualifier_list
    // specifier_qualifier_list--> type_specifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_19(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2113-type_specifier->SBIT
    //parent:
    // declaration_specifiers_--> type_specifier declaration_specifiers_
    // declaration_specifiers_--> type_specifier
    // specifier_qualifier_list--> type_specifier specifier_qualifier_list
    // specifier_qualifier_list--> type_specifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_20(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2114-type_specifier->SFR16
    //parent:
    // declaration_specifiers_--> type_specifier declaration_specifiers_
    // declaration_specifiers_--> type_specifier
    // specifier_qualifier_list--> type_specifier specifier_qualifier_list
    // specifier_qualifier_list--> type_specifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_21(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2115-type_specifier->SFR32
    //parent:
    // declaration_specifiers_--> type_specifier declaration_specifiers_
    // declaration_specifiers_--> type_specifier
    // specifier_qualifier_list--> type_specifier specifier_qualifier_list
    // specifier_qualifier_list--> type_specifier
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}




/*************************
 *
 *tokens:
 *
 *
 *
 *
 *
 *
 *
 * */

icode *func_common_basic_type(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    icode *a=result_ic;

    //a->m_type = ICODE_TYPE_DEF_VAR;
    a->m_bit_width = pcompi->m_target->get_basic_type_bit_width(tdefs->val_str);
    a->m_type_str = a->m_type_str+" "+ tdefs->val_str;

    return NULL;
}


class icode *func_token_TYPEDEF_NAME(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //TYPEDEF_NAME
    //parent:
    // type_specifier--> TYPEDEF_NAME

    sym* s = pcompi->find_symbol(tdefs->val_str);
    unsigned long tmp = result_ic->m_icode_number;
    std::string tmp_type_name = result_ic->m_type_str;


    *result_ic = *s->def_icode;
    result_ic->m_icode_number = tmp;
    //result_ic->m_bit_width = s->def_icode->m_bit_width;
    result_ic->m_type_str = tmp_type_name + s->def_icode->name;
    //result_ic->name = s->def_icode->name;


    result_ic->m_dir_line_no = tdefs->line_no;
    result_ic->m_dir_source = tdefs->m_file_name;
    result_ic->m_line_no = result_ic->m_dir_line_no;
    result_ic->m_source = pcompi->mp_driver->streamname;

    //result_ic->result = pcompi->new_ref_icode( s->def_icode);

    return NULL;
}

class icode *func_token_VOID(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //VOID
    //parent:
    // type_specifier--> VOID

    icode *ret = func_common_basic_type(pcompi, tdefs, need_result_icode, result_ic);
    result_ic->is_signed = 0;
    return ret;

}
class icode *func_token_BOOL(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //BOOL
    //parent:
    // type_specifier--> BOOL

    icode *ret= func_common_basic_type(pcompi, tdefs, need_result_icode, result_ic);

    result_ic->is_signed = 0;
    return ret;
}
class icode *func_token_CHAR(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //CHAR
    //parent:
    // type_specifier--> CHAR
    icode *ret= func_common_basic_type(pcompi, tdefs, need_result_icode, result_ic);

    if(!result_ic->is_signed_force)
    {
        result_ic->is_signed = 0;
    }
    return ret;

}
class icode *func_token_SHORT(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //SHORT
    //parent:
    // type_specifier--> SHORT
    return func_common_basic_type(pcompi, tdefs, need_result_icode, result_ic);

}
class icode *func_token_INT(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //INT
    //parent:
    // type_specifier--> INT
    return func_common_basic_type(pcompi, tdefs, need_result_icode, result_ic);

}
class icode *func_token_LONG(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //LONG
    //parent:
    // type_specifier--> LONG
    return func_common_basic_type(pcompi, tdefs, need_result_icode, result_ic);

}
class icode *func_token_SIGNED(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //SIGNED
    //parent:
    // type_specifier--> SIGNED
    icode *ret= func_common_basic_type(pcompi, tdefs, need_result_icode, result_ic);
    result_ic->is_signed = 1;
    result_ic->is_signed_force = 1;

    return ret;
}
class icode *func_token_UNSIGNED(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //UNSIGNED
    //parent:
    // type_specifier--> UNSIGNED
    icode *ret= func_common_basic_type(pcompi, tdefs, need_result_icode, result_ic);
    result_ic->is_signed = 0;
    result_ic->is_signed_force = 0;

    return ret;
}
class icode *func_token_FLOAT(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //FLOAT
    //parent:
    // type_specifier--> FLOAT

    icode *ret= func_common_basic_type(pcompi, tdefs, need_result_icode, result_ic);
    result_ic->is_float32 = 1;

    return ret;
}



class icode *func_token_SFR(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //SFR
    //parent:
    // type_specifier--> SFR

    icode *ret= func_common_basic_type(pcompi, tdefs, need_result_icode, result_ic);
    result_ic->is_sfr=1;

    return ret;
}
class icode *func_token_BIT(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //BIT
    //parent:
    // type_specifier--> BIT
    icode *ret= func_common_basic_type(pcompi, tdefs, need_result_icode, result_ic);

    return ret;

}
class icode *func_token_SBIT(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //SBIT
    //parent:
    // type_specifier--> SBIT
    icode *ret= func_common_basic_type(pcompi, tdefs, need_result_icode, result_ic);
    result_ic->is_sbit=1;

    return ret;
}
class icode *func_token_SFR16(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //SFR16
    //parent:
    // type_specifier--> SFR16
    icode *ret= func_common_basic_type(pcompi, tdefs, need_result_icode, result_ic);
    result_ic->is_sfr16=1;

    return ret;
}
class icode *func_token_SFR32(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //SFR32
    //parent:
    // type_specifier--> SFR32
    icode *ret= func_common_basic_type(pcompi, tdefs, need_result_icode, result_ic);
    result_ic->is_sfr32=1;

    return ret;
}






/*TODO*/

class icode *func_token_DOUBLE(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //DOUBLE
    //parent:
    // type_specifier--> DOUBLE

    icode *ret= func_common_basic_type(pcompi, tdefs, need_result_icode, result_ic);
    result_ic->is_float32 = 1;

    return ret;
}

class icode *func_token_COMPLEX(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //COMPLEX
    //parent:
    // type_specifier--> COMPLEX
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}
class icode *func_token_IMAGINARY(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //IMAGINARY
    //parent:
    // type_specifier--> IMAGINARY
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    assert(0);
    return a;
}





}//namespace end










