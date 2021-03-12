#include <assert.h>
#include "icode.h"
#include "comp_context.h"
#include "token_defs.h"
#include "comp_context_gen_defs.h"
#include "asm_funcs.h"

namespace NS_AMS8051HEX{


icode *  func_IAN_FILE_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x2-file->prog_block 
	//parent:
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
icode *  func_IAN_PROG_BLOCK_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x101-prog_block->EOL 
	//parent:
	// file--> prog_block
	// prog_block--> prog_block cmd_text_line
	// prog_block--> prog_block macro_text_line
	// prog_block--> prog_block label_text_line
	// prog_block--> prog_block EOL
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
icode *  func_IAN_PROG_BLOCK_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x102-prog_block->cmd_text_line 
	//parent:
	// file--> prog_block
	// prog_block--> prog_block cmd_text_line
	// prog_block--> prog_block macro_text_line
	// prog_block--> prog_block label_text_line
	// prog_block--> prog_block EOL
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
icode *  func_IAN_PROG_BLOCK_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x103-prog_block->macro_text_line 
	//parent:
	// file--> prog_block
	// prog_block--> prog_block cmd_text_line
	// prog_block--> prog_block macro_text_line
	// prog_block--> prog_block label_text_line
	// prog_block--> prog_block EOL
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
icode *  func_IAN_PROG_BLOCK_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x104-prog_block->label_text_line 
	//parent:
	// file--> prog_block
	// prog_block--> prog_block cmd_text_line
	// prog_block--> prog_block macro_text_line
	// prog_block--> prog_block label_text_line
	// prog_block--> prog_block EOL
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
icode *  func_IAN_PROG_BLOCK_5(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x105-prog_block->prog_block cmd_text_line 
	//parent:
	// file--> prog_block
	// prog_block--> prog_block cmd_text_line
	// prog_block--> prog_block macro_text_line
	// prog_block--> prog_block label_text_line
	// prog_block--> prog_block EOL
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
    token_defs *prog_block=tdefs->m_tk_elems[0];
    token_defs *cmd_text_line=tdefs->m_tk_elems[1];
    icode *prog_block_ic=pcompi->ast_to_icode(prog_block);
    icode *cmd_text_line_ic=pcompi->ast_to_icode(cmd_text_line);
    a->merge_icode(prog_block_ic);
    a->merge_icode(cmd_text_line_ic);
	return a;
}
icode *  func_IAN_PROG_BLOCK_6(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x106-prog_block->prog_block macro_text_line 
	//parent:
	// file--> prog_block
	// prog_block--> prog_block cmd_text_line
	// prog_block--> prog_block macro_text_line
	// prog_block--> prog_block label_text_line
	// prog_block--> prog_block EOL
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
    token_defs *prog_block=tdefs->m_tk_elems[0];
    token_defs *macro_text_line=tdefs->m_tk_elems[1];
    icode *prog_block_ic=pcompi->ast_to_icode(prog_block);
    icode *macro_text_line_ic=pcompi->ast_to_icode(macro_text_line);
    a->merge_icode(prog_block_ic);
    a->merge_icode(macro_text_line_ic);
	return a;
}
icode *  func_IAN_PROG_BLOCK_7(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x107-prog_block->prog_block label_text_line 
	//parent:
	// file--> prog_block
	// prog_block--> prog_block cmd_text_line
	// prog_block--> prog_block macro_text_line
	// prog_block--> prog_block label_text_line
	// prog_block--> prog_block EOL
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
    token_defs *prog_block=tdefs->m_tk_elems[0];
    token_defs *label_text_line=tdefs->m_tk_elems[1];
    icode *prog_block_ic=pcompi->ast_to_icode(prog_block);
    icode *label_text_line_ic=pcompi->ast_to_icode(label_text_line);
    a->merge_icode(prog_block_ic);
    a->merge_icode(label_text_line_ic);
	return a;
}
icode *  func_IAN_PROG_BLOCK_8(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x108-prog_block->prog_block EOL 
	//parent:
	// file--> prog_block
	// prog_block--> prog_block cmd_text_line
	// prog_block--> prog_block macro_text_line
	// prog_block--> prog_block label_text_line
	// prog_block--> prog_block EOL
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
    token_defs *prog_block=tdefs->m_tk_elems[0];
    token_defs *EOL=tdefs->m_tk_elems[1];
    icode *prog_block_ic=pcompi->ast_to_icode(prog_block);
    icode *EOL_ic=pcompi->ast_to_icode(EOL);
    a->merge_icode(prog_block_ic);
    a->merge_icode(EOL_ic);
	return a;
}
icode *  func_IAN_CMD_TEXT_LINE_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x201-cmd_text_line->TK_CMD EOL 
	//parent:
	// prog_block--> cmd_text_line
	// prog_block--> prog_block cmd_text_line
    icode *a = pcompi->new_icode(ICODE_TYPE_ONE_CMD);
    token_defs *TK_CMD=tdefs->m_tk_elems[0];
	//token_defs *EOL=tdefs->m_tk_elems[1];
    icode *TK_CMD_ic=pcompi->ast_to_icode(TK_CMD);


	//icode *EOL_ic=pcompi->ast_to_icode(EOL);
    a->merge_icode(TK_CMD_ic);
	//a->merge_icode(EOL_ic);
	return a;
}
icode *  func_IAN_CMD_TEXT_LINE_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x202-cmd_text_line->TK_CMD opand EOL 
	//parent:
	// prog_block--> cmd_text_line
	// prog_block--> prog_block cmd_text_line
    icode *a = pcompi->new_icode(ICODE_TYPE_ONE_CMD);
    token_defs *TK_CMD=tdefs->m_tk_elems[0];
    token_defs *opand=tdefs->m_tk_elems[1];
	//token_defs *EOL=tdefs->m_tk_elems[2];
    icode *TK_CMD_ic=pcompi->ast_to_icode(TK_CMD);
    icode *opand_ic=pcompi->ast_to_icode(opand);
	//icode *EOL_ic=pcompi->ast_to_icode(EOL);
    a->merge_icode(TK_CMD_ic);
    a->merge_icode(opand_ic);
	//a->merge_icode(EOL_ic);
	return a;
}
icode *  func_IAN_CMD_TEXT_LINE_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x203-cmd_text_line->TK_CMD opand ',' opand EOL 
	//parent:
	// prog_block--> cmd_text_line
	// prog_block--> prog_block cmd_text_line
    icode *a = pcompi->new_icode(ICODE_TYPE_ONE_CMD);
    token_defs *TK_CMD=tdefs->m_tk_elems[0];
    token_defs *opand=tdefs->m_tk_elems[1];
	//token_defs *','=tdefs->m_tk_elems[2];
    token_defs *opand2=tdefs->m_tk_elems[3];
	//token_defs *EOL=tdefs->m_tk_elems[4];
    icode *TK_CMD_ic=pcompi->ast_to_icode(TK_CMD);
    icode *opand_ic=pcompi->ast_to_icode(opand);
	//icode *','_ic=pcompi->ast_to_icode(',');
    icode *opand2_ic=pcompi->ast_to_icode(opand2);
	//icode *EOL_ic=pcompi->ast_to_icode(EOL);
    a->merge_icode(TK_CMD_ic);
    a->merge_icode(opand_ic);
	//a->merge_icode(','_ic);
    a->merge_icode(opand2_ic);
	//a->merge_icode(EOL_ic);
	return a;
}
icode *  func_IAN_CMD_TEXT_LINE_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x204-cmd_text_line->TK_CMD opand ',' opand ',' opand EOL 
	//parent:
	// prog_block--> cmd_text_line
	// prog_block--> prog_block cmd_text_line
    icode *a = pcompi->new_icode(ICODE_TYPE_ONE_CMD);
    token_defs *TK_CMD=tdefs->m_tk_elems[0];
    token_defs *opand1=tdefs->m_tk_elems[1];
	//token_defs *','=tdefs->m_tk_elems[2];
    token_defs *opand2=tdefs->m_tk_elems[3];
	//token_defs *','=tdefs->m_tk_elems[4];
    token_defs *opand3=tdefs->m_tk_elems[5];
	//token_defs *EOL=tdefs->m_tk_elems[6];
    icode *TK_CMD_ic=pcompi->ast_to_icode(TK_CMD);
    icode *opand1_ic=pcompi->ast_to_icode(opand1);
	//icode *','_ic=pcompi->ast_to_icode(',');
    icode *opand2_ic=pcompi->ast_to_icode(opand2);
	//icode *','_ic=pcompi->ast_to_icode(',');
    icode *opand3_ic=pcompi->ast_to_icode(opand3);
	//icode *EOL_ic=pcompi->ast_to_icode(EOL);
    a->merge_icode(TK_CMD_ic);
    a->merge_icode(opand1_ic);
	//a->merge_icode(','_ic);
    a->merge_icode(opand2_ic);
	//a->merge_icode(','_ic);
    a->merge_icode(opand3_ic);
	//a->merge_icode(EOL_ic);
	return a;
}
icode *  func_IAN_CMD_TEXT_LINE_5(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x205-cmd_text_line->TK_CMD opand ',' opand ',' opand ',' opand EOL 
	//parent:
	// prog_block--> cmd_text_line
	// prog_block--> prog_block cmd_text_line
    icode *a = pcompi->new_icode(ICODE_TYPE_ONE_CMD);
    token_defs *TK_CMD=tdefs->m_tk_elems[0];
    token_defs *opand1=tdefs->m_tk_elems[1];
	//token_defs *','=tdefs->m_tk_elems[2];
    token_defs *opand2=tdefs->m_tk_elems[3];
	//token_defs *','=tdefs->m_tk_elems[4];
    token_defs *opand3=tdefs->m_tk_elems[5];
	//token_defs *','=tdefs->m_tk_elems[6];
    token_defs *opand4=tdefs->m_tk_elems[7];
	//token_defs *EOL=tdefs->m_tk_elems[8];
    icode *TK_CMD_ic=pcompi->ast_to_icode(TK_CMD);
    icode *opand1_ic=pcompi->ast_to_icode(opand1);
	//icode *','_ic=pcompi->ast_to_icode(',');
    icode *opand2_ic=pcompi->ast_to_icode(opand2);
	//icode *','_ic=pcompi->ast_to_icode(',');
    icode *opand3_ic=pcompi->ast_to_icode(opand3);
	//icode *','_ic=pcompi->ast_to_icode(',');
    icode *opand4_ic=pcompi->ast_to_icode(opand4);
	//icode *EOL_ic=pcompi->ast_to_icode(EOL);
    a->merge_icode(TK_CMD_ic);
    a->merge_icode(opand1_ic);
	//a->merge_icode(','_ic);
    a->merge_icode(opand2_ic);
	//a->merge_icode(','_ic);
    a->merge_icode(opand3_ic);
	//a->merge_icode(','_ic);
    a->merge_icode(opand4_ic);
	//a->merge_icode(EOL_ic);
	return a;
}
icode *  func_IAN_OPAND_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x301-opand->expr 
	//parent:
	// cmd_text_line--> TK_CMD opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand ',' opand EOL
	// macro_text_line--> TK_KEYWORD TK_MACRO opand EOL
	// db_list--> TK_DB opand
	// db_list--> db_list ',' opand
	// db_list--> db_list opand
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
icode *  func_IAN_OPAND_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x302-opand->'#' expr 
	//parent:
	// cmd_text_line--> TK_CMD opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand ',' opand EOL
	// macro_text_line--> TK_KEYWORD TK_MACRO opand EOL
	// db_list--> TK_DB opand
	// db_list--> db_list ',' opand
	// db_list--> db_list opand
    icode *a = pcompi->new_icode(TOKENI_IMM);
	//token_defs *'#'=tdefs->m_tk_elems[0];
    token_defs *expr=tdefs->m_tk_elems[1];
	//icode *'#'_ic=pcompi->ast_to_icode('#');
    icode *expr_ic=pcompi->ast_to_icode(expr);
	//a->merge_icode('#'_ic);
    a->merge_icode(expr_ic);
	return a;
}
icode *  func_IAN_OPAND_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x303-opand->'/' expr 
	//parent:
	// cmd_text_line--> TK_CMD opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand ',' opand EOL
	// macro_text_line--> TK_KEYWORD TK_MACRO opand EOL
	// db_list--> TK_DB opand
	// db_list--> db_list ',' opand
	// db_list--> db_list opand
    icode *a = pcompi->new_icode(TOKENI_NBIT);
	//token_defs *'/'=tdefs->m_tk_elems[0];
    token_defs *expr=tdefs->m_tk_elems[1];
	//icode *'/'_ic=pcompi->ast_to_icode('/');
    icode *expr_ic=pcompi->ast_to_icode(expr);
	//a->merge_icode('/'_ic);
    a->merge_icode(expr_ic);
	return a;
}
icode *  func_IAN_OPAND_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x304-opand->'/' expr '.' expr 
	//parent:
	// cmd_text_line--> TK_CMD opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand ',' opand EOL
	// macro_text_line--> TK_KEYWORD TK_MACRO opand EOL
	// db_list--> TK_DB opand
	// db_list--> db_list ',' opand
	// db_list--> db_list opand
    icode *a = pcompi->new_icode(TOKENI_NBIT);
	//token_defs *'/'=tdefs->m_tk_elems[0];
    token_defs *expr=tdefs->m_tk_elems[1];
	//token_defs *'.'=tdefs->m_tk_elems[2];
    token_defs *expr2=tdefs->m_tk_elems[3];
	//icode *'/'_ic=pcompi->ast_to_icode('/');
    icode *expr_ic=pcompi->ast_to_icode(expr);
	//icode *'.'_ic=pcompi->ast_to_icode('.');
    icode *expr2_ic=pcompi->ast_to_icode(expr2);
	//a->merge_icode('/'_ic);
    a->merge_icode(expr_ic);
	//a->merge_icode('.'_ic);
    a->merge_icode(expr2_ic);
	return a;
}
icode *  func_IAN_OPAND_5(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x305-opand->expr '.' expr 
	//parent:
	// cmd_text_line--> TK_CMD opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand ',' opand EOL
	// macro_text_line--> TK_KEYWORD TK_MACRO opand EOL
	// db_list--> TK_DB opand
	// db_list--> db_list ',' opand
	// db_list--> db_list opand
    icode *a = pcompi->new_icode(TOKENI_DOTBIT);
    token_defs *expr=tdefs->m_tk_elems[0];
	//token_defs *'.'=tdefs->m_tk_elems[1];
    token_defs *expr2=tdefs->m_tk_elems[2];
    icode *expr_ic=pcompi->ast_to_icode(expr);
	//icode *'.'_ic=pcompi->ast_to_icode('.');
    icode *expr2_ic=pcompi->ast_to_icode(expr2);
    a->merge_icode(expr_ic);
	//a->merge_icode('.'_ic);
    a->merge_icode(expr2_ic);
	return a;
}
icode *  func_IAN_OPAND_6(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x306-opand->TK_ACC 
	//parent:
	// cmd_text_line--> TK_CMD opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand ',' opand EOL
	// macro_text_line--> TK_KEYWORD TK_MACRO opand EOL
	// db_list--> TK_DB opand
	// db_list--> db_list ',' opand
	// db_list--> db_list opand
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
icode *  func_IAN_OPAND_7(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x307-opand->TK_C 
	//parent:
	// cmd_text_line--> TK_CMD opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand ',' opand EOL
	// macro_text_line--> TK_KEYWORD TK_MACRO opand EOL
	// db_list--> TK_DB opand
	// db_list--> db_list ',' opand
	// db_list--> db_list opand
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
icode *  func_IAN_OPAND_8(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x308-opand->TK_AB 
	//parent:
	// cmd_text_line--> TK_CMD opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand ',' opand EOL
	// macro_text_line--> TK_KEYWORD TK_MACRO opand EOL
	// db_list--> TK_DB opand
	// db_list--> db_list ',' opand
	// db_list--> db_list opand
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
icode *  func_IAN_OPAND_9(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x309-opand->TK_AT_DPTR 
	//parent:
	// cmd_text_line--> TK_CMD opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand ',' opand EOL
	// macro_text_line--> TK_KEYWORD TK_MACRO opand EOL
	// db_list--> TK_DB opand
	// db_list--> db_list ',' opand
	// db_list--> db_list opand
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
icode *  func_IAN_OPAND_10(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x30a-opand->TK_DPTR 
	//parent:
	// cmd_text_line--> TK_CMD opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand ',' opand EOL
	// macro_text_line--> TK_KEYWORD TK_MACRO opand EOL
	// db_list--> TK_DB opand
	// db_list--> db_list ',' opand
	// db_list--> db_list opand
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
icode *  func_IAN_OPAND_11(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x30b-opand->TK_AT_A_PLUS_PC 
	//parent:
	// cmd_text_line--> TK_CMD opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand ',' opand EOL
	// macro_text_line--> TK_KEYWORD TK_MACRO opand EOL
	// db_list--> TK_DB opand
	// db_list--> db_list ',' opand
	// db_list--> db_list opand
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
icode *  func_IAN_OPAND_12(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x30c-opand->TK_AT_A_PLUS_DPTR 
	//parent:
	// cmd_text_line--> TK_CMD opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand ',' opand EOL
	// macro_text_line--> TK_KEYWORD TK_MACRO opand EOL
	// db_list--> TK_DB opand
	// db_list--> db_list ',' opand
	// db_list--> db_list opand
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
icode *  func_IAN_OPAND_13(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x30d-opand->TK_AT_RI 
	//parent:
	// cmd_text_line--> TK_CMD opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand ',' opand EOL
	// macro_text_line--> TK_KEYWORD TK_MACRO opand EOL
	// db_list--> TK_DB opand
	// db_list--> db_list ',' opand
	// db_list--> db_list opand
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
icode *  func_IAN_OPAND_14(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x30e-opand->TK_RN 
	//parent:
	// cmd_text_line--> TK_CMD opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand EOL
	// cmd_text_line--> TK_CMD opand ',' opand ',' opand ',' opand EOL
	// macro_text_line--> TK_KEYWORD TK_MACRO opand EOL
	// db_list--> TK_DB opand
	// db_list--> db_list ',' opand
	// db_list--> db_list opand
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
icode *  func_IAN_EXPR_ELEM_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x401-expr_elem->TK_KEYWORD 
	//parent:
	// not_expr--> expr_elem
	// not_expr--> TK_NOT expr_elem
	// not_expr--> TK_HIGH expr_elem
	// not_expr--> TK_LOW expr_elem
	// not_expr--> expr_elem TK_SHL expr_elem
	// not_expr--> expr_elem TK_MOD expr_elem
	// not_expr--> expr_elem '&' expr_elem
	// not_expr--> expr_elem TK_SHIFT_RIGHT expr_elem
	// not_expr--> expr_elem TK_SHIFT_LEFT expr_elem
	// macro_text_line--> TK_MACRO expr_elem EOL
	// macro_text_line--> TK_MACRO expr_elem expr_elem EOL
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
icode *  func_IAN_EXPR_ELEM_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x402-expr_elem->I_CONSTANT 
	//parent:
	// not_expr--> expr_elem
	// not_expr--> TK_NOT expr_elem
	// not_expr--> TK_HIGH expr_elem
	// not_expr--> TK_LOW expr_elem
	// not_expr--> expr_elem TK_SHL expr_elem
	// not_expr--> expr_elem TK_MOD expr_elem
	// not_expr--> expr_elem '&' expr_elem
	// not_expr--> expr_elem TK_SHIFT_RIGHT expr_elem
	// not_expr--> expr_elem TK_SHIFT_LEFT expr_elem
	// macro_text_line--> TK_MACRO expr_elem EOL
	// macro_text_line--> TK_MACRO expr_elem expr_elem EOL
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
icode *  func_IAN_EXPR_ELEM_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x403-expr_elem->STRING_LITERAL 
	//parent:
	// not_expr--> expr_elem
	// not_expr--> TK_NOT expr_elem
	// not_expr--> TK_HIGH expr_elem
	// not_expr--> TK_LOW expr_elem
	// not_expr--> expr_elem TK_SHL expr_elem
	// not_expr--> expr_elem TK_MOD expr_elem
	// not_expr--> expr_elem '&' expr_elem
	// not_expr--> expr_elem TK_SHIFT_RIGHT expr_elem
	// not_expr--> expr_elem TK_SHIFT_LEFT expr_elem
	// macro_text_line--> TK_MACRO expr_elem EOL
	// macro_text_line--> TK_MACRO expr_elem expr_elem EOL
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
icode *  func_IAN_EXPR_ELEM_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x404-expr_elem->TK_DOLLAR 
	//parent:
	// not_expr--> expr_elem
	// not_expr--> TK_NOT expr_elem
	// not_expr--> TK_HIGH expr_elem
	// not_expr--> TK_LOW expr_elem
	// not_expr--> expr_elem TK_SHL expr_elem
	// not_expr--> expr_elem TK_MOD expr_elem
	// not_expr--> expr_elem '&' expr_elem
	// not_expr--> expr_elem TK_SHIFT_RIGHT expr_elem
	// not_expr--> expr_elem TK_SHIFT_LEFT expr_elem
	// macro_text_line--> TK_MACRO expr_elem EOL
	// macro_text_line--> TK_MACRO expr_elem expr_elem EOL
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
icode *  func_IAN_EXPR_ELEM_5(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x405-expr_elem->'(' expr ')' 
	//parent:
	// not_expr--> expr_elem
	// not_expr--> TK_NOT expr_elem
	// not_expr--> TK_HIGH expr_elem
	// not_expr--> TK_LOW expr_elem
	// not_expr--> expr_elem TK_SHL expr_elem
	// not_expr--> expr_elem TK_MOD expr_elem
	// not_expr--> expr_elem '&' expr_elem
	// not_expr--> expr_elem TK_SHIFT_RIGHT expr_elem
	// not_expr--> expr_elem TK_SHIFT_LEFT expr_elem
	// macro_text_line--> TK_MACRO expr_elem EOL
	// macro_text_line--> TK_MACRO expr_elem expr_elem EOL

    return pcompi->ast_to_icode(tdefs->m_tk_elems[1],need_result_icode, result_ic);

}
icode *  func_IAN_NOT_EXPR_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x501-not_expr->expr_elem 
	//parent:
	// multi_expr--> not_expr
	// multi_expr--> multi_expr '*' not_expr
	// multi_expr--> multi_expr '/' not_expr
	// multi_expr--> multi_expr '%' not_expr
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
icode *  func_IAN_NOT_EXPR_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x502-not_expr->TK_NOT expr_elem 
	//parent:
	// multi_expr--> not_expr
	// multi_expr--> multi_expr '*' not_expr
	// multi_expr--> multi_expr '/' not_expr
	// multi_expr--> multi_expr '%' not_expr
    icode *a = pcompi->new_icode(ICODE_TYPE_ONE_OPERATION);
    token_defs *expr_elem=tdefs->m_tk_elems[1];
    icode *expr_elem_ic=pcompi->ast_to_icode(expr_elem);
    a->name = "NOT";
    a->merge_icode(expr_elem_ic);
	return a;
}
icode *  func_IAN_NOT_EXPR_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x503-not_expr->TK_HIGH expr_elem 
	//parent:
	// multi_expr--> not_expr
	// multi_expr--> multi_expr '*' not_expr
	// multi_expr--> multi_expr '/' not_expr
	// multi_expr--> multi_expr '%' not_expr
    icode *a = pcompi->new_icode(ICODE_TYPE_ONE_OPERATION);
    token_defs *expr_elem=tdefs->m_tk_elems[1];
    icode *expr_elem_ic=pcompi->ast_to_icode(expr_elem);
    a->name = "HIGH";
    a->merge_icode(expr_elem_ic);
	return a;
}
icode *  func_IAN_NOT_EXPR_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x504-not_expr->TK_LOW expr_elem 
	//parent:
	// multi_expr--> not_expr
	// multi_expr--> multi_expr '*' not_expr
	// multi_expr--> multi_expr '/' not_expr
	// multi_expr--> multi_expr '%' not_expr
    icode *a = pcompi->new_icode(ICODE_TYPE_ONE_OPERATION);
    token_defs *expr_elem=tdefs->m_tk_elems[1];
    icode *expr_elem_ic=pcompi->ast_to_icode(expr_elem);
    a->name = "LOW";
    a->merge_icode(expr_elem_ic);
	return a;
}
icode *  func_IAN_NOT_EXPR_5(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x505-not_expr->expr_elem TK_SHL expr_elem 
	//parent:
	// multi_expr--> not_expr
	// multi_expr--> multi_expr '*' not_expr
	// multi_expr--> multi_expr '/' not_expr
	// multi_expr--> multi_expr '%' not_expr
    icode *a = pcompi->new_icode(ICODE_TYPE_ONE_OPERATION);
    token_defs *expr_elem1=tdefs->m_tk_elems[0];
    token_defs *expr_elem2=tdefs->m_tk_elems[2];
    icode *expr_elem1_ic=pcompi->ast_to_icode(expr_elem1);
    icode *expr_elem2_ic=pcompi->ast_to_icode(expr_elem2);
    a->name = "SHL";
    a->merge_icode(expr_elem1_ic);
    a->merge_icode(expr_elem2_ic);
	return a;
}
icode *  func_IAN_NOT_EXPR_6(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x506-not_expr->expr_elem TK_MOD expr_elem 
	//parent:
	// multi_expr--> not_expr
	// multi_expr--> multi_expr '*' not_expr
	// multi_expr--> multi_expr '/' not_expr
	// multi_expr--> multi_expr '%' not_expr
    icode *a = pcompi->new_icode(ICODE_TYPE_ONE_OPERATION);
    token_defs *expr_elem=tdefs->m_tk_elems[0];
	//token_defs *TK_MOD=tdefs->m_tk_elems[1];
    token_defs *expr_elem2=tdefs->m_tk_elems[2];
    icode *expr_elem_ic=pcompi->ast_to_icode(expr_elem);
	//icode *TK_MOD_ic=pcompi->ast_to_icode(TK_MOD);
    icode *expr_elem2_ic=pcompi->ast_to_icode(expr_elem2);
    a->name = "MOD";
    a->merge_icode(expr_elem_ic);
    a->merge_icode(expr_elem2_ic);
	return a;
}
icode *  func_IAN_NOT_EXPR_7(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x507-not_expr->expr_elem '&' expr_elem 
	//parent:
	// multi_expr--> not_expr
	// multi_expr--> multi_expr '*' not_expr
	// multi_expr--> multi_expr '/' not_expr
	// multi_expr--> multi_expr '%' not_expr
    icode *a = pcompi->new_icode(ICODE_TYPE_ONE_OPERATION);
    token_defs *expr_elem=tdefs->m_tk_elems[0];
	//token_defs *'&'=tdefs->m_tk_elems[1];
    token_defs *expr_elem2=tdefs->m_tk_elems[2];
    icode *expr_elem_ic=pcompi->ast_to_icode(expr_elem);
	//icode *'&'_ic=pcompi->ast_to_icode('&');
    icode *expr_elem2_ic=pcompi->ast_to_icode(expr_elem2);
    a->name = "&";
    a->merge_icode(expr_elem_ic);
    a->merge_icode(expr_elem2_ic);
	return a;
}
icode *  func_IAN_NOT_EXPR_8(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x508-not_expr->expr_elem TK_SHIFT_RIGHT expr_elem 
	//parent:
	// multi_expr--> not_expr
	// multi_expr--> multi_expr '*' not_expr
	// multi_expr--> multi_expr '/' not_expr
	// multi_expr--> multi_expr '%' not_expr
    icode *a = pcompi->new_icode(ICODE_TYPE_ONE_OPERATION);
    token_defs *expr_elem=tdefs->m_tk_elems[0];
    token_defs *expr_elem2=tdefs->m_tk_elems[2];
    icode *expr_elem_ic=pcompi->ast_to_icode(expr_elem);
    icode *expr_elem2_ic=pcompi->ast_to_icode(expr_elem2);
    a->name = ">>";
    a->merge_icode(expr_elem_ic);
    a->merge_icode(expr_elem2_ic);
	return a;
}
icode *  func_IAN_NOT_EXPR_9(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x509-not_expr->expr_elem TK_SHIFT_LEFT expr_elem 
	//parent:
	// multi_expr--> not_expr
	// multi_expr--> multi_expr '*' not_expr
	// multi_expr--> multi_expr '/' not_expr
	// multi_expr--> multi_expr '%' not_expr
    icode *a = pcompi->new_icode(ICODE_TYPE_ONE_OPERATION);
    token_defs *expr_elem=tdefs->m_tk_elems[0];
    token_defs *expr_elem2=tdefs->m_tk_elems[2];
    icode *expr_elem_ic=pcompi->ast_to_icode(expr_elem);
    icode *expr_elem2_ic=pcompi->ast_to_icode(expr_elem2);
    a->name = "<<";
    a->merge_icode(expr_elem_ic);
    a->merge_icode(expr_elem2_ic);
    return a;
}
icode *  func_IAN_MULTI_EXPR_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x601-multi_expr->not_expr 
	//parent:
	// multi_expr--> multi_expr '*' not_expr
	// multi_expr--> multi_expr '/' not_expr
	// multi_expr--> multi_expr '%' not_expr
	// additive_expr--> multi_expr
	// additive_expr--> additive_expr '+' multi_expr
	// additive_expr--> additive_expr '-' multi_expr
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
icode *  func_IAN_MULTI_EXPR_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x602-multi_expr->multi_expr '*' not_expr 
	//parent:
	// multi_expr--> multi_expr '*' not_expr
	// multi_expr--> multi_expr '/' not_expr
	// multi_expr--> multi_expr '%' not_expr
	// additive_expr--> multi_expr
	// additive_expr--> additive_expr '+' multi_expr
	// additive_expr--> additive_expr '-' multi_expr
    icode *a = pcompi->new_icode(ICODE_TYPE_ONE_OPERATION);
    token_defs *expr_elem=tdefs->m_tk_elems[0];
    token_defs *expr_elem2=tdefs->m_tk_elems[2];
    icode *expr_elem_ic=pcompi->ast_to_icode(expr_elem);
    icode *expr_elem2_ic=pcompi->ast_to_icode(expr_elem2);
    a->name = "multipy";
    a->merge_icode(expr_elem_ic);
    a->merge_icode(expr_elem2_ic);
    return a;
}
icode *  func_IAN_MULTI_EXPR_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x603-multi_expr->multi_expr '/' not_expr 
	//parent:
	// multi_expr--> multi_expr '*' not_expr
	// multi_expr--> multi_expr '/' not_expr
	// multi_expr--> multi_expr '%' not_expr
	// additive_expr--> multi_expr
	// additive_expr--> additive_expr '+' multi_expr
	// additive_expr--> additive_expr '-' multi_expr
    icode *a = pcompi->new_icode(ICODE_TYPE_ONE_OPERATION);
    token_defs *multi_expr=tdefs->m_tk_elems[0];
    token_defs *not_expr=tdefs->m_tk_elems[2];
    icode *multi_expr_ic=pcompi->ast_to_icode(multi_expr);
    icode *not_expr_ic=pcompi->ast_to_icode(not_expr);
    a->name = "div";
    a->merge_icode(multi_expr_ic);
    a->merge_icode(not_expr_ic);

	return a;
}
icode *  func_IAN_MULTI_EXPR_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x604-multi_expr->multi_expr '%' not_expr 
	//parent:
	// multi_expr--> multi_expr '*' not_expr
	// multi_expr--> multi_expr '/' not_expr
	// multi_expr--> multi_expr '%' not_expr
	// additive_expr--> multi_expr
	// additive_expr--> additive_expr '+' multi_expr
	// additive_expr--> additive_expr '-' multi_expr
    icode *a = pcompi->new_icode(ICODE_TYPE_ONE_OPERATION);
    token_defs *multi_expr=tdefs->m_tk_elems[0];
    token_defs *not_expr=tdefs->m_tk_elems[2];
    icode *multi_expr_ic=pcompi->ast_to_icode(multi_expr);
    icode *not_expr_ic=pcompi->ast_to_icode(not_expr);
    a->name = "MOD";
    a->merge_icode(multi_expr_ic);
    a->merge_icode(not_expr_ic);

    return a;
}
icode *  func_IAN_ADDITIVE_EXPR_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x701-additive_expr->multi_expr 
	//parent:
	// additive_expr--> additive_expr '+' multi_expr
	// additive_expr--> additive_expr '-' multi_expr
	// expr--> additive_expr
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
icode *  func_IAN_ADDITIVE_EXPR_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x702-additive_expr->additive_expr '+' multi_expr 
	//parent:
	// additive_expr--> additive_expr '+' multi_expr
	// additive_expr--> additive_expr '-' multi_expr
	// expr--> additive_expr
    icode *a = pcompi->new_icode(ICODE_TYPE_ONE_OPERATION);
    token_defs *additive_expr=tdefs->m_tk_elems[0];
    token_defs *multi_expr=tdefs->m_tk_elems[2];
    icode *additive_expr_ic=pcompi->ast_to_icode(additive_expr);
    icode *multi_expr_ic=pcompi->ast_to_icode(multi_expr);
    a->name="add";
    a->merge_icode(additive_expr_ic);
    a->merge_icode(multi_expr_ic);

	return a;
}
icode *  func_IAN_ADDITIVE_EXPR_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x703-additive_expr->additive_expr '-' multi_expr 
	//parent:
	// additive_expr--> additive_expr '+' multi_expr
	// additive_expr--> additive_expr '-' multi_expr
	// expr--> additive_expr
    icode *a = pcompi->new_icode(ICODE_TYPE_ONE_OPERATION);
    token_defs *additive_expr=tdefs->m_tk_elems[0];
    token_defs *multi_expr=tdefs->m_tk_elems[2];
    icode *additive_expr_ic=pcompi->ast_to_icode(additive_expr);
    icode *multi_expr_ic=pcompi->ast_to_icode(multi_expr);
    a->name="sub";
    a->merge_icode(additive_expr_ic);
    a->merge_icode(multi_expr_ic);

    return a;
}
icode *  func_IAN_EXPR_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x801-expr->additive_expr 
	//parent:
	// opand--> expr
	// opand--> '#' expr
	// opand--> '/' expr
	// opand--> '/' expr '.' expr
	// opand--> expr '.' expr
	// expr_elem--> '(' expr ')'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
icode *  func_IAN_MACRO_TEXT_LINE_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x901-macro_text_line->TK_MACRO EOL 
	//parent:
	// prog_block--> macro_text_line
	// prog_block--> prog_block macro_text_line
    icode *a = pcompi->new_icode(ICODE_TYPE_ONE_MACRO);
    token_defs *TK_MACRO=tdefs->m_tk_elems[0];
	//token_defs *EOL=tdefs->m_tk_elems[1];
    icode *TK_MACRO_ic=pcompi->ast_to_icode(TK_MACRO);
	//icode *EOL_ic=pcompi->ast_to_icode(EOL);
    a->merge_icode(TK_MACRO_ic);
	//a->merge_icode(EOL_ic);
	return a;
}
icode *  func_IAN_MACRO_TEXT_LINE_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x902-macro_text_line->TK_MACRO expr_elem EOL 
	//parent:
	// prog_block--> macro_text_line
	// prog_block--> prog_block macro_text_line
    icode *a = pcompi->new_icode(ICODE_TYPE_ONE_MACRO);
    token_defs *TK_MACRO=tdefs->m_tk_elems[0];
    token_defs *expr_elem=tdefs->m_tk_elems[1];
	//token_defs *EOL=tdefs->m_tk_elems[2];
    icode *TK_MACRO_ic=pcompi->ast_to_icode(TK_MACRO);
    icode *expr_elem_ic=pcompi->ast_to_icode(expr_elem);
	//icode *EOL_ic=pcompi->ast_to_icode(EOL);
    a->merge_icode(TK_MACRO_ic);
    a->merge_icode(expr_elem_ic);
	//a->merge_icode(EOL_ic);
	return a;
}
icode *  func_IAN_MACRO_TEXT_LINE_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x903-macro_text_line->TK_MACRO expr_elem expr_elem EOL 
	//parent:
	// prog_block--> macro_text_line
	// prog_block--> prog_block macro_text_line
    icode *a = pcompi->new_icode(ICODE_TYPE_ONE_MACRO);
    token_defs *TK_MACRO=tdefs->m_tk_elems[0];
    token_defs *expr_elem=tdefs->m_tk_elems[1];
    token_defs *expr_elem2=tdefs->m_tk_elems[2];
	//token_defs *EOL=tdefs->m_tk_elems[3];
    icode *TK_MACRO_ic=pcompi->ast_to_icode(TK_MACRO);
    icode *expr_elem_ic=pcompi->ast_to_icode(expr_elem);
    icode *expr_elem2_ic=pcompi->ast_to_icode(expr_elem);
	//icode *EOL_ic=pcompi->ast_to_icode(EOL);
    a->merge_icode(TK_MACRO_ic);
    a->merge_icode(expr_elem_ic);
    a->merge_icode(expr_elem2_ic);
	//a->merge_icode(EOL_ic);
	return a;
}
icode *  func_IAN_MACRO_TEXT_LINE_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x904-macro_text_line->TK_KEYWORD TK_MACRO opand EOL 
	//parent:
	// prog_block--> macro_text_line
	// prog_block--> prog_block macro_text_line
    icode *a = pcompi->new_icode(ICODE_TYPE_ONE_MACRO);
    token_defs *TK_KEYWORD=tdefs->m_tk_elems[0];
    token_defs *TK_MACRO=tdefs->m_tk_elems[1];
    token_defs *opand=tdefs->m_tk_elems[2];
	//token_defs *EOL=tdefs->m_tk_elems[3];
    icode *TK_KEYWORD_ic=pcompi->ast_to_icode(TK_KEYWORD);
    icode *TK_MACRO_ic=pcompi->ast_to_icode(TK_MACRO);
    icode *opand_ic=pcompi->ast_to_icode(opand);
	//icode *EOL_ic=pcompi->ast_to_icode(EOL);
    a->merge_icode(TK_MACRO_ic);
    a->merge_icode(TK_KEYWORD_ic);
    a->merge_icode(opand_ic);
	//a->merge_icode(EOL_ic);
	return a;
}
icode *  func_IAN_MACRO_TEXT_LINE_5(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0x905-macro_text_line->db_list EOL 
	//parent:
	// prog_block--> macro_text_line
	// prog_block--> prog_block macro_text_line


    return pcompi->ast_to_icode(tdefs->m_tk_elems[0],need_result_icode, result_ic);


    icode *a = pcompi->new_icode(ICODE_TYPE_ONE_MACRO);
	//token_defs *db_list=tdefs->m_tk_elems[0];
	//token_defs *EOL=tdefs->m_tk_elems[1];
	//icode *db_list_ic=pcompi->ast_to_icode(db_list);
	//icode *EOL_ic=pcompi->ast_to_icode(EOL);
	//a->merge_icode(db_list_ic);
	//a->merge_icode(EOL_ic);
	assert(0);
	return a;
}
icode *  func_IAN_DB_LIST_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0xa01-db_list->TK_DB opand 
	//parent:
	// macro_text_line--> db_list EOL
	// db_list--> db_list ',' opand
	// db_list--> db_list opand
    icode *a = pcompi->new_icode(ICODE_TYPE_ONE_MACRO);
    token_defs *TK_DB=tdefs->m_tk_elems[0];
    token_defs *opand=tdefs->m_tk_elems[1];
    icode *TK_DB_ic=pcompi->ast_to_icode(TK_DB);
    icode *opand_ic=pcompi->ast_to_icode(opand);
    a->merge_icode(TK_DB_ic);
    a->merge_icode(opand_ic);
    a->name = "DB";
	return a;
}
icode *  func_IAN_DB_LIST_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0xa02-db_list->db_list ',' opand 
	//parent:
	// macro_text_line--> db_list EOL
	// db_list--> db_list ',' opand
	// db_list--> db_list opand
    token_defs *db_list=tdefs->m_tk_elems[0];
	//token_defs *','=tdefs->m_tk_elems[1];
    token_defs *opand=tdefs->m_tk_elems[2];
    icode *db_list_ic=pcompi->ast_to_icode(db_list);
	//icode *','_ic=pcompi->ast_to_icode(',');
    icode *opand_ic=pcompi->ast_to_icode(opand);

    db_list_ic->sub_icode.push_back(opand_ic);

    return db_list_ic;
}
icode *  func_IAN_DB_LIST_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0xa03-db_list->db_list opand 
	//parent:
	// macro_text_line--> db_list EOL
	// db_list--> db_list ',' opand
	// db_list--> db_list opand
    token_defs *db_list=tdefs->m_tk_elems[0];
    token_defs *opand=tdefs->m_tk_elems[1];
    icode *db_list_ic=pcompi->ast_to_icode(db_list);
    icode *opand_ic=pcompi->ast_to_icode(opand);
    db_list_ic->sub_icode.push_back(opand_ic);

    return db_list_ic;
}
icode *  func_IAN_LABEL_TEXT_LINE_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
	//0xb01-label_text_line->TK_KEYWORD ':' 
	//parent:
	// prog_block--> label_text_line
	// prog_block--> prog_block label_text_line
    icode *a = pcompi->new_icode(ICODE_TYPE_DEFINE_LABEL);
    token_defs *TK_KEYWORD=tdefs->m_tk_elems[0];
	//token_defs *':'=tdefs->m_tk_elems[1];
    icode *TK_KEYWORD_ic=pcompi->ast_to_icode(TK_KEYWORD);
	//icode *':'_ic=pcompi->ast_to_icode(':');
    a->merge_icode(TK_KEYWORD_ic);
	//a->merge_icode(':'_ic);
	return a;
}
//cnt=3b

}//namespace NS_AMS8051HEX
