#include <assert.h>
#include "icode.h"
#include "comp_context.h"
#include "token_defs.h"
#include "comp_context_gen_defs.h"
#include "str2number.h"
#include "parser.h"
namespace NS_AMS8051HEX{

 icode *func_token_TK_EXTERN(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_EXTERN
	//parent:
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 icode *func_token_TK_CODE(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_CODE
	//parent:
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 icode *func_token_TK_DATA(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_DATA
	//parent:
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 icode *func_token_TK_BIT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_BIT
	//parent:
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 icode *func_token_TK_XDATA(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_XDATA
	//parent:
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 icode *func_token_TK_NUMBER(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_NUMBER
	//parent:
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 icode *func_token_TK_PUBLIC(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_PUBLIC
	//parent:
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 icode *func_token_TK_SEGMENT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_SEGMENT
	//parent:
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 icode *func_token_TK_EJECT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_EJECT
	//parent:
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 icode *func_token_TK_XSEG(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_XSEG
	//parent:
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 icode *func_token_TK_RSEG(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_RSEG
	//parent:
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 icode *func_token_TK_AT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_AT
	//parent:
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 icode *func_token_TK_CSEG(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_CSEG
	//parent:
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 icode *func_token_TK_DS(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_DS
	//parent:
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 icode *func_token_TK_DBIG(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_DBIG
	//parent:
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 icode *func_token_TK_EQU(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_EQU
	//parent:
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 icode *func_token_TK_USING(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_USING
	//parent:
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 icode *func_token_TK_DB(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_DB
	//parent:
	// db_list--> TK_DB opand
    icode *a = pcompi->new_icode(Parser::token_type::TK_DB);
    a->name="DB";
	return a;
}
 icode *func_token_TK_DW(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_DW
	//parent:
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 icode *func_token_EOL(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//EOL
	//parent:
	// prog_block--> EOL
	// prog_block--> prog_block EOL
	// cmd_text_line--> TK_CMD EOL
	// cmd_text_line--> TK_CMD opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand ',' opand EOL
	// macro_text_line--> TK_MACRO EOL
	// macro_text_line--> TK_MACRO expr_elem EOL
	// macro_text_line--> TK_MACRO expr_elem expr_elem EOL
	// macro_text_line--> TK_KEYWORD TK_MACRO opand EOL
	// macro_text_line--> db_list EOL
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);


	return a;
}
 icode *func_token_TK_ACC(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_ACC
	//parent:
	// opand--> TK_ACC
    icode *a = pcompi->new_icode(Parser::token_type::TK_ACC);
    a->name = tdefs->val_str;
    return a;
}
 icode *func_token_TK_C(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_C
	//parent:
	// opand--> TK_C
    icode *a = pcompi->new_icode(Parser::token_type::TK_C);
    a->name = tdefs->val_str;
    return a;
}
 icode *func_token_TK_AB(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_AB
	//parent:
	// opand--> TK_AB
    icode *a = pcompi->new_icode(Parser::token_type::TK_AB);
    a->name = tdefs->val_str;
    return a;
}
 icode *func_token_TK_AT_DPTR(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_AT_DPTR
	//parent:
	// opand--> TK_AT_DPTR
    icode *a = pcompi->new_icode(Parser::token_type::TK_AT_DPTR);
    a->name = tdefs->val_str;
	return a;
}
 icode *func_token_TK_DPTR(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_DPTR
	//parent:
	// opand--> TK_DPTR
    icode *a = pcompi->new_icode(Parser::token_type::TK_DPTR);
    a->name = tdefs->val_str;

	return a;
}
 icode *func_token_TK_AT_A_PLUS_PC(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_AT_A_PLUS_PC
	//parent:
    // opand-->
    icode *a = pcompi->new_icode( Parser::token_type::TK_AT_A_PLUS_PC);
    a->name = tdefs->val_str;
	return a;
}
 icode *func_token_TK_AT_A_PLUS_DPTR(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_AT_A_PLUS_DPTR
	//parent:
	// opand--> TK_AT_A_PLUS_DPTR
    icode *a = pcompi->new_icode(Parser::token_type::TK_AT_A_PLUS_DPTR);
    a->name = tdefs->val_str;
    return a;
}
 icode *func_token_TK_AT_RI(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_AT_RI
	//parent:
	// opand--> TK_AT_RI
    icode *a = pcompi->new_icode(Parser::token_type::TK_AT_RI);
    a->num = StrToNumber(tdefs->val_str.substr(2));//FIXME
    a->name = tdefs->val_str;
    return a;
}
 icode *func_token_TK_RN(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_RN
	//parent:
	// opand--> TK_RN
    icode *a = pcompi->new_icode(Parser::token_type::TK_RN );
    a->num = tdefs->num;//FIXME
    a->name = tdefs->val_str;
	return a;
}
 icode *func_token_I_CONSTANT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//I_CONSTANT
	//parent:
	// expr_elem--> I_CONSTANT
     icode *a = pcompi->new_icode(ICODE_TOKEN_ICONST);
     a->name = tdefs->val_str;
     a->num = StrToNumber(tdefs->val_str);

     return a;
}
 icode *func_token_F_CONSTANT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//F_CONSTANT
	//parent:
    icode *a = pcompi->new_icode(ICODE_TOKEN_FCONST);
    a->name = tdefs->val_str;
	return a;
}
 icode *func_token_STRING_LITERAL(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//STRING_LITERAL
	//parent:
	// expr_elem--> STRING_LITERAL
    icode *a = pcompi->new_icode(ICODE_TOKEN_STR);
    a->name = tdefs->val_str;
	return a;
}
 icode *func_token_TK_CMD(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_CMD
	//parent:
	// cmd_text_line--> TK_CMD EOL
	// cmd_text_line--> TK_CMD opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand ',' opand EOL
    icode *a = pcompi->new_icode(ICODE_TOKEN_CMD);
    a->name = tdefs->val_str;
    return a;
}
 icode *func_token_TK_MACRO(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_MACRO
	//parent:
	// macro_text_line--> TK_MACRO EOL
	// macro_text_line--> TK_MACRO expr_elem EOL
	// macro_text_line--> TK_MACRO expr_elem expr_elem EOL
	// macro_text_line--> TK_KEYWORD TK_MACRO opand EOL
    icode *a = pcompi->new_icode(ICODE_TOKEN_MACRO);
    a->name = tdefs->val_str;
	return a;
}
 icode *func_token_TK_KEYWORD(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_KEYWORD
	//parent:
	// expr_elem--> TK_KEYWORD
	// macro_text_line--> TK_KEYWORD TK_MACRO opand EOL
	// label_text_line--> TK_KEYWORD ':'
    icode *a = pcompi->new_icode(ICODE_TOKEN_KEYWORD);
    a->name = tdefs->val_str;
    return a;
}
 icode *func_token_TK_DOLLAR(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_DOLLAR
	//parent:
	// expr_elem--> TK_DOLLAR
     icode *a = pcompi->new_icode(Parser::token_type::TK_DOLLAR);
     a->name = tdefs->val_str;
     return a;
}
 icode *func_token_TK_NOT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_NOT
	//parent:
	// not_expr--> TK_NOT expr_elem
     icode *a = pcompi->new_icode(ICODE_TOKEN_OPR);
     a->name = tdefs->val_str;
     return a;
}
 icode *func_token_TK_HIGH(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_HIGH
	//parent:
	// not_expr--> TK_HIGH expr_elem
     icode *a = pcompi->new_icode(ICODE_TOKEN_OPR);
     a->name = tdefs->val_str;
     return a;
}
 icode *func_token_TK_LOW(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_LOW
	//parent:
	// not_expr--> TK_LOW expr_elem
     icode *a = pcompi->new_icode(ICODE_TOKEN_OPR);
     a->name = tdefs->val_str;
     return a;
}
 icode *func_token_TK_SHL(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_SHL
	//parent:
	// not_expr--> expr_elem TK_SHL expr_elem
     icode *a = pcompi->new_icode(ICODE_TOKEN_OPR);
     a->name = tdefs->val_str;
     return a;
}
 icode *func_token_TK_MOD(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_MOD
	//parent:
	// not_expr--> expr_elem TK_MOD expr_elem
     icode *a = pcompi->new_icode(ICODE_TOKEN_OPR);
     a->name = tdefs->val_str;
     return a;
}
 icode *func_token_TK_BIT_PT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_BIT_PT
	//parent:
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 icode *func_token_TK_SHIFT_LEFT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_SHIFT_LEFT
	//parent:
	// not_expr--> expr_elem TK_SHIFT_LEFT expr_elem
    icode *a = pcompi->new_icode(ICODE_TOKEN_OPR);
    a->name = tdefs->val_str;
	return a;
}
 icode *func_token_TK_SHIFT_RIGHT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//TK_SHIFT_RIGHT
	//parent:
	// not_expr--> expr_elem TK_SHIFT_RIGHT expr_elem
     icode *a = pcompi->new_icode(ICODE_TOKEN_OPR);
     a->name = tdefs->val_str;
     return a;
}

}//namespace NS_AMS8051HEX
