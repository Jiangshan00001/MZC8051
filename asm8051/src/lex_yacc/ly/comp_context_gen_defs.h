#ifndef AST_TO_ICODE_GEN_DEF_H
#define AST_TO_ICODE_GEN_DEF_H
namespace NS_AMS8051HEX{

enum E_AST_TO_ICODE_GEN_DEF{
IAN_FILE_1=0x1, //file->
IAN_FILE_2=0x2, //file->prog_block 
IAN_PROG_BLOCK_1=0x101, //prog_block->EOL 
IAN_PROG_BLOCK_2=0x102, //prog_block->cmd_text_line 
IAN_PROG_BLOCK_3=0x103, //prog_block->macro_text_line 
IAN_PROG_BLOCK_4=0x104, //prog_block->label_text_line 
IAN_PROG_BLOCK_5=0x105, //prog_block->prog_block cmd_text_line 
IAN_PROG_BLOCK_6=0x106, //prog_block->prog_block macro_text_line 
IAN_PROG_BLOCK_7=0x107, //prog_block->prog_block label_text_line 
IAN_PROG_BLOCK_8=0x108, //prog_block->prog_block EOL 
IAN_CMD_TEXT_LINE_1=0x201, //cmd_text_line->TK_CMD EOL 
IAN_CMD_TEXT_LINE_2=0x202, //cmd_text_line->TK_CMD opand EOL 
IAN_CMD_TEXT_LINE_3=0x203, //cmd_text_line->TK_CMD opand ',' opand EOL 
IAN_CMD_TEXT_LINE_4=0x204, //cmd_text_line->TK_CMD opand ',' opand ',' opand EOL 
IAN_CMD_TEXT_LINE_5=0x205, //cmd_text_line->TK_CMD opand ',' opand ',' opand ',' opand EOL 
IAN_OPAND_1=0x301, //opand->expr 
IAN_OPAND_2=0x302, //opand->'#' expr 
IAN_OPAND_3=0x303, //opand->'/' expr 
IAN_OPAND_4=0x304, //opand->'/' expr '.' expr 
IAN_OPAND_5=0x305, //opand->expr '.' expr 
IAN_OPAND_6=0x306, //opand->TK_ACC 
IAN_OPAND_7=0x307, //opand->TK_C 
IAN_OPAND_8=0x308, //opand->TK_AB 
IAN_OPAND_9=0x309, //opand->TK_AT_DPTR 
IAN_OPAND_10=0x30a, //opand->TK_DPTR 
IAN_OPAND_11=0x30b, //opand->TK_AT_A_PLUS_PC 
IAN_OPAND_12=0x30c, //opand->TK_AT_A_PLUS_DPTR 
IAN_OPAND_13=0x30d, //opand->TK_AT_RI 
IAN_OPAND_14=0x30e, //opand->TK_RN 
IAN_EXPR_ELEM_1=0x401, //expr_elem->TK_KEYWORD 
IAN_EXPR_ELEM_2=0x402, //expr_elem->I_CONSTANT 
IAN_EXPR_ELEM_3=0x403, //expr_elem->STRING_LITERAL 
IAN_EXPR_ELEM_4=0x404, //expr_elem->TK_DOLLAR 
IAN_EXPR_ELEM_5=0x405, //expr_elem->'(' expr ')' 
IAN_NOT_EXPR_1=0x501, //not_expr->expr_elem 
IAN_NOT_EXPR_2=0x502, //not_expr->TK_NOT expr_elem 
IAN_NOT_EXPR_3=0x503, //not_expr->TK_HIGH expr_elem 
IAN_NOT_EXPR_4=0x504, //not_expr->TK_LOW expr_elem 
IAN_NOT_EXPR_5=0x505, //not_expr->expr_elem TK_SHL expr_elem 
IAN_NOT_EXPR_6=0x506, //not_expr->expr_elem TK_MOD expr_elem 
IAN_NOT_EXPR_7=0x507, //not_expr->expr_elem '&' expr_elem 
IAN_NOT_EXPR_8=0x508, //not_expr->expr_elem TK_SHIFT_RIGHT expr_elem 
IAN_NOT_EXPR_9=0x509, //not_expr->expr_elem TK_SHIFT_LEFT expr_elem 
IAN_MULTI_EXPR_1=0x601, //multi_expr->not_expr 
IAN_MULTI_EXPR_2=0x602, //multi_expr->multi_expr '*' not_expr 
IAN_MULTI_EXPR_3=0x603, //multi_expr->multi_expr '/' not_expr 
IAN_MULTI_EXPR_4=0x604, //multi_expr->multi_expr '%' not_expr 
IAN_ADDITIVE_EXPR_1=0x701, //additive_expr->multi_expr 
IAN_ADDITIVE_EXPR_2=0x702, //additive_expr->additive_expr '+' multi_expr 
IAN_ADDITIVE_EXPR_3=0x703, //additive_expr->additive_expr '-' multi_expr 
IAN_EXPR_1=0x801, //expr->additive_expr 
IAN_MACRO_TEXT_LINE_1=0x901, //macro_text_line->TK_MACRO EOL 
IAN_MACRO_TEXT_LINE_2=0x902, //macro_text_line->TK_MACRO expr_elem EOL 
IAN_MACRO_TEXT_LINE_3=0x903, //macro_text_line->TK_MACRO expr_elem expr_elem EOL 
IAN_MACRO_TEXT_LINE_4=0x904, //macro_text_line->TK_KEYWORD TK_MACRO opand EOL 
IAN_MACRO_TEXT_LINE_5=0x905, //macro_text_line->db_list EOL 
IAN_DB_LIST_1=0xa01, //db_list->TK_DB opand 
IAN_DB_LIST_2=0xa02, //db_list->db_list ',' opand 
IAN_DB_LIST_3=0xa03, //db_list->db_list opand 
IAN_LABEL_TEXT_LINE_1=0xb01, //label_text_line->TK_KEYWORD ':' 
};

icode *  func_IAN_FILE_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_PROG_BLOCK_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_PROG_BLOCK_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_PROG_BLOCK_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_PROG_BLOCK_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_PROG_BLOCK_5(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_PROG_BLOCK_6(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_PROG_BLOCK_7(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_PROG_BLOCK_8(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_CMD_TEXT_LINE_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_CMD_TEXT_LINE_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_CMD_TEXT_LINE_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_CMD_TEXT_LINE_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_CMD_TEXT_LINE_5(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_OPAND_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_OPAND_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_OPAND_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_OPAND_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_OPAND_5(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_OPAND_6(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_OPAND_7(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_OPAND_8(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_OPAND_9(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_OPAND_10(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_OPAND_11(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_OPAND_12(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_OPAND_13(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_OPAND_14(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_EXPR_ELEM_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_EXPR_ELEM_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_EXPR_ELEM_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_EXPR_ELEM_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_EXPR_ELEM_5(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_NOT_EXPR_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_NOT_EXPR_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_NOT_EXPR_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_NOT_EXPR_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_NOT_EXPR_5(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_NOT_EXPR_6(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_NOT_EXPR_7(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_NOT_EXPR_8(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_NOT_EXPR_9(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_MULTI_EXPR_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_MULTI_EXPR_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_MULTI_EXPR_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_MULTI_EXPR_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ADDITIVE_EXPR_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ADDITIVE_EXPR_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ADDITIVE_EXPR_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_EXPR_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_MACRO_TEXT_LINE_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_MACRO_TEXT_LINE_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_MACRO_TEXT_LINE_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_MACRO_TEXT_LINE_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_MACRO_TEXT_LINE_5(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DB_LIST_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DB_LIST_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DB_LIST_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_LABEL_TEXT_LINE_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
//ast func cout:59
 icode *func_token_TK_EXTERN(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_CODE(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_DATA(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_BIT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_XDATA(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_NUMBER(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_PUBLIC(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_SEGMENT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_EJECT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_XSEG(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_RSEG(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_AT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_CSEG(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_DS(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_DBIG(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_EQU(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_USING(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_DB(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_DW(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_EOL(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_ACC(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_C(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_AB(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_AT_DPTR(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_DPTR(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_AT_A_PLUS_PC(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_AT_A_PLUS_DPTR(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_AT_RI(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_RN(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_I_CONSTANT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_F_CONSTANT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_STRING_LITERAL(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_CMD(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_MACRO(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_KEYWORD(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_DOLLAR(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_NOT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_HIGH(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_LOW(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_SHL(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_MOD(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_SHIFT_LEFT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TK_SHIFT_RIGHT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
//elem func cout:43


}//namespace NS_AMS8051HEX
#endif
