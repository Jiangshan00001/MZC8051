#include <assert.h>
#include "comp_context.h"
#include "parser.h"
#include "token_defs.h"
#include "icode.h"
#include "str2number.h"
#include "comp_context_gen_defs.h"
#include "mylog.h"
#include "replace.h"
using mylog::cerr;
using mylog::cout;
namespace NS_AMS8051HEX{

icode * comp_context::ast_to_icode_elem(token_defs* tdefs, bool need_result_icode, icode *result_ic)
{
switch(tdefs->m_token_type)
{
case Parser::token::TK_EXTERN:
{
 icode *a= func_token_TK_EXTERN(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_CODE:
{
 icode *a= func_token_TK_CODE(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_DATA:
{
 icode *a= func_token_TK_DATA(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_BIT:
{
 icode *a= func_token_TK_BIT(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_XDATA:
{
 icode *a= func_token_TK_XDATA(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_NUMBER:
{
 icode *a= func_token_TK_NUMBER(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_PUBLIC:
{
 icode *a= func_token_TK_PUBLIC(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_SEGMENT:
{
 icode *a= func_token_TK_SEGMENT(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_EJECT:
{
 icode *a= func_token_TK_EJECT(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_XSEG:
{
 icode *a= func_token_TK_XSEG(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_RSEG:
{
 icode *a= func_token_TK_RSEG(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_AT:
{
 icode *a= func_token_TK_AT(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_CSEG:
{
 icode *a= func_token_TK_CSEG(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_DS:
{
 icode *a= func_token_TK_DS(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_DBIG:
{
 icode *a= func_token_TK_DBIG(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_EQU:
{
 icode *a= func_token_TK_EQU(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_USING:
{
 icode *a= func_token_TK_USING(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_DB:
{
 icode *a= func_token_TK_DB(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_DW:
{
 icode *a= func_token_TK_DW(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::EOL:
{
 icode *a= func_token_EOL(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_ACC:
{
 icode *a= func_token_TK_ACC(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_C:
{
 icode *a= func_token_TK_C(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_AB:
{
 icode *a= func_token_TK_AB(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_AT_DPTR:
{
 icode *a= func_token_TK_AT_DPTR(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_DPTR:
{
 icode *a= func_token_TK_DPTR(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_AT_A_PLUS_PC:
{
 icode *a= func_token_TK_AT_A_PLUS_PC(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_AT_A_PLUS_DPTR:
{
 icode *a= func_token_TK_AT_A_PLUS_DPTR(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_AT_RI:
{
 icode *a= func_token_TK_AT_RI(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_RN:
{
 icode *a= func_token_TK_RN(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::I_CONSTANT:
{
 icode *a= func_token_I_CONSTANT(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::F_CONSTANT:
{
 icode *a= func_token_F_CONSTANT(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::STRING_LITERAL:
{
 icode *a= func_token_STRING_LITERAL(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_CMD:
{
 icode *a= func_token_TK_CMD(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_MACRO:
{
 icode *a= func_token_TK_MACRO(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_KEYWORD:
{
 icode *a= func_token_TK_KEYWORD(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_DOLLAR:
{
 icode *a= func_token_TK_DOLLAR(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_NOT:
{
 icode *a= func_token_TK_NOT(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_HIGH:
{
 icode *a= func_token_TK_HIGH(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_LOW:
{
 icode *a= func_token_TK_LOW(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_SHL:
{
 icode *a= func_token_TK_SHL(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_MOD:
{
 icode *a= func_token_TK_MOD(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_SHIFT_LEFT:
{
 icode *a= func_token_TK_SHIFT_LEFT(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TK_SHIFT_RIGHT:
{
 icode *a= func_token_TK_SHIFT_RIGHT(this, tdefs, need_result_icode, result_ic);
return a;
}
break;

}//switch end. case_cnt=43
    return NULL;
}
icode * comp_context::ast_to_icode_ast(token_defs* tdefs, bool need_result_icode, icode *result_ic)
{
int top_type=tdefs->m_tk_type_int;
if(tdefs->m_tk_type_int_list.size()>0)
{
	top_type=tdefs->m_tk_type_int_list[tdefs->m_tk_type_int_list.size()-1];
tdefs->m_tk_type_int_list.pop_back();

}
switch(top_type)
{
case IAN_FILE_2: //0x2-file->prog_block 
{
	icode *a= func_IAN_FILE_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_PROG_BLOCK_1: //0x101-prog_block->EOL 
{
	icode *a= func_IAN_PROG_BLOCK_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_PROG_BLOCK_2: //0x102-prog_block->cmd_text_line 
{
	icode *a= func_IAN_PROG_BLOCK_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_PROG_BLOCK_3: //0x103-prog_block->macro_text_line 
{
	icode *a= func_IAN_PROG_BLOCK_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_PROG_BLOCK_4: //0x104-prog_block->label_text_line 
{
	icode *a= func_IAN_PROG_BLOCK_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_PROG_BLOCK_5: //0x105-prog_block->prog_block cmd_text_line 
{
	icode *a= func_IAN_PROG_BLOCK_5(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_PROG_BLOCK_6: //0x106-prog_block->prog_block macro_text_line 
{
	icode *a= func_IAN_PROG_BLOCK_6(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_PROG_BLOCK_7: //0x107-prog_block->prog_block label_text_line 
{
	icode *a= func_IAN_PROG_BLOCK_7(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_PROG_BLOCK_8: //0x108-prog_block->prog_block EOL 
{
	icode *a= func_IAN_PROG_BLOCK_8(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_CMD_TEXT_LINE_1: //0x201-cmd_text_line->TK_CMD EOL 
{
	icode *a= func_IAN_CMD_TEXT_LINE_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_CMD_TEXT_LINE_2: //0x202-cmd_text_line->TK_CMD opand EOL 
{
	icode *a= func_IAN_CMD_TEXT_LINE_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_CMD_TEXT_LINE_3: //0x203-cmd_text_line->TK_CMD opand ',' opand EOL 
{
	icode *a= func_IAN_CMD_TEXT_LINE_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_CMD_TEXT_LINE_4: //0x204-cmd_text_line->TK_CMD opand ',' opand ',' opand EOL 
{
	icode *a= func_IAN_CMD_TEXT_LINE_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_CMD_TEXT_LINE_5: //0x205-cmd_text_line->TK_CMD opand ',' opand ',' opand ',' opand EOL 
{
	icode *a= func_IAN_CMD_TEXT_LINE_5(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_OPAND_1: //0x301-opand->expr 
{
	icode *a= func_IAN_OPAND_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_OPAND_2: //0x302-opand->'#' expr 
{
	icode *a= func_IAN_OPAND_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_OPAND_3: //0x303-opand->'/' expr 
{
	icode *a= func_IAN_OPAND_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_OPAND_4: //0x304-opand->'/' expr '.' expr 
{
	icode *a= func_IAN_OPAND_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_OPAND_5: //0x305-opand->expr '.' expr 
{
	icode *a= func_IAN_OPAND_5(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_OPAND_6: //0x306-opand->TK_ACC 
{
	icode *a= func_IAN_OPAND_6(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_OPAND_7: //0x307-opand->TK_C 
{
	icode *a= func_IAN_OPAND_7(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_OPAND_8: //0x308-opand->TK_AB 
{
	icode *a= func_IAN_OPAND_8(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_OPAND_9: //0x309-opand->TK_AT_DPTR 
{
	icode *a= func_IAN_OPAND_9(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_OPAND_10: //0x30a-opand->TK_DPTR 
{
	icode *a= func_IAN_OPAND_10(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_OPAND_11: //0x30b-opand->TK_AT_A_PLUS_PC 
{
	icode *a= func_IAN_OPAND_11(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_OPAND_12: //0x30c-opand->TK_AT_A_PLUS_DPTR 
{
	icode *a= func_IAN_OPAND_12(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_OPAND_13: //0x30d-opand->TK_AT_RI 
{
	icode *a= func_IAN_OPAND_13(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_OPAND_14: //0x30e-opand->TK_RN 
{
	icode *a= func_IAN_OPAND_14(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_EXPR_ELEM_1: //0x401-expr_elem->TK_KEYWORD 
{
	icode *a= func_IAN_EXPR_ELEM_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_EXPR_ELEM_2: //0x402-expr_elem->I_CONSTANT 
{
	icode *a= func_IAN_EXPR_ELEM_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_EXPR_ELEM_3: //0x403-expr_elem->STRING_LITERAL 
{
	icode *a= func_IAN_EXPR_ELEM_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_EXPR_ELEM_4: //0x404-expr_elem->TK_DOLLAR 
{
	icode *a= func_IAN_EXPR_ELEM_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_EXPR_ELEM_5: //0x405-expr_elem->'(' expr ')' 
{
	icode *a= func_IAN_EXPR_ELEM_5(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_NOT_EXPR_1: //0x501-not_expr->expr_elem 
{
	icode *a= func_IAN_NOT_EXPR_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_NOT_EXPR_2: //0x502-not_expr->TK_NOT expr_elem 
{
	icode *a= func_IAN_NOT_EXPR_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_NOT_EXPR_3: //0x503-not_expr->TK_HIGH expr_elem 
{
	icode *a= func_IAN_NOT_EXPR_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_NOT_EXPR_4: //0x504-not_expr->TK_LOW expr_elem 
{
	icode *a= func_IAN_NOT_EXPR_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_NOT_EXPR_5: //0x505-not_expr->expr_elem TK_SHL expr_elem 
{
	icode *a= func_IAN_NOT_EXPR_5(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_NOT_EXPR_6: //0x506-not_expr->expr_elem TK_MOD expr_elem 
{
	icode *a= func_IAN_NOT_EXPR_6(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_NOT_EXPR_7: //0x507-not_expr->expr_elem '&' expr_elem 
{
	icode *a= func_IAN_NOT_EXPR_7(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_NOT_EXPR_8: //0x508-not_expr->expr_elem TK_SHIFT_RIGHT expr_elem 
{
	icode *a= func_IAN_NOT_EXPR_8(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_NOT_EXPR_9: //0x509-not_expr->expr_elem TK_SHIFT_LEFT expr_elem 
{
	icode *a= func_IAN_NOT_EXPR_9(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_MULTI_EXPR_1: //0x601-multi_expr->not_expr 
{
	icode *a= func_IAN_MULTI_EXPR_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_MULTI_EXPR_2: //0x602-multi_expr->multi_expr '*' not_expr 
{
	icode *a= func_IAN_MULTI_EXPR_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_MULTI_EXPR_3: //0x603-multi_expr->multi_expr '/' not_expr 
{
	icode *a= func_IAN_MULTI_EXPR_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_MULTI_EXPR_4: //0x604-multi_expr->multi_expr '%' not_expr 
{
	icode *a= func_IAN_MULTI_EXPR_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ADDITIVE_EXPR_1: //0x701-additive_expr->multi_expr 
{
	icode *a= func_IAN_ADDITIVE_EXPR_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ADDITIVE_EXPR_2: //0x702-additive_expr->additive_expr '+' multi_expr 
{
	icode *a= func_IAN_ADDITIVE_EXPR_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ADDITIVE_EXPR_3: //0x703-additive_expr->additive_expr '-' multi_expr 
{
	icode *a= func_IAN_ADDITIVE_EXPR_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_EXPR_1: //0x801-expr->additive_expr 
{
	icode *a= func_IAN_EXPR_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_MACRO_TEXT_LINE_1: //0x901-macro_text_line->TK_MACRO EOL 
{
	icode *a= func_IAN_MACRO_TEXT_LINE_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_MACRO_TEXT_LINE_2: //0x902-macro_text_line->TK_MACRO expr_elem EOL 
{
	icode *a= func_IAN_MACRO_TEXT_LINE_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_MACRO_TEXT_LINE_3: //0x903-macro_text_line->TK_MACRO expr_elem expr_elem EOL 
{
	icode *a= func_IAN_MACRO_TEXT_LINE_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_MACRO_TEXT_LINE_4: //0x904-macro_text_line->TK_KEYWORD TK_MACRO opand EOL 
{
	icode *a= func_IAN_MACRO_TEXT_LINE_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_MACRO_TEXT_LINE_5: //0x905-macro_text_line->db_list EOL 
{
	icode *a= func_IAN_MACRO_TEXT_LINE_5(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DB_LIST_1: //0xa01-db_list->TK_DB opand 
{
	icode *a= func_IAN_DB_LIST_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DB_LIST_2: //0xa02-db_list->db_list ',' opand 
{
	icode *a= func_IAN_DB_LIST_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DB_LIST_3: //0xa03-db_list->db_list opand 
{
	icode *a= func_IAN_DB_LIST_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_LABEL_TEXT_LINE_1: //0xb01-label_text_line->TK_KEYWORD ':' 
{
	icode *a= func_IAN_LABEL_TEXT_LINE_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;

}//switch end. case_cnt=3b

return NULL;
}

icode * comp_context::ast_to_icode(token_defs* tdefs, bool need_result_icode, icode *result_ic)
{
if(tdefs==NULL){assert(0); return new_icode();}
if((tdefs->m_type==TOKEN_DEFS_TYPE_AST)||(tdefs->m_tk_type_int_list.size()>0))
{
return ast_to_icode_ast(tdefs, need_result_icode, result_ic);
}
else if(tdefs->m_type==TOKEN_DEFS_TYPE_ELEM)
{
return ast_to_icode_elem(tdefs, need_result_icode, result_ic);
}
else
{
assert(0);
}
return new_icode();

}

}//namespace NS_AMS8051HEX
