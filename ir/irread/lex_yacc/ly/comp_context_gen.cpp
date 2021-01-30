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
namespace NS_IR2ICODE{

icode * comp_context::ast_to_icode_elem(token_defs* tdefs, bool need_result_icode, icode *result_ic)
{
switch(tdefs->m_token_type)
{
case Parser::token::END:
{
 icode *a= func_token_END(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::EOL:
{
 icode *a= func_token_EOL(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::BLOCKS:
{
 icode *a= func_token_BLOCKS(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::BLOCKE:
{
 icode *a= func_token_BLOCKE(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::SCOPES:
{
 icode *a= func_token_SCOPES(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::SCOPEE:
{
 icode *a= func_token_SCOPEE(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::DEF_VAR:
{
 icode *a= func_token_DEF_VAR(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::DEF_VAR_TMP:
{
 icode *a= func_token_DEF_VAR_TMP(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::VAR_IN:
{
 icode *a= func_token_VAR_IN(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::VAR_IN_TMP:
{
 icode *a= func_token_VAR_IN_TMP(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::DEF_ARG:
{
 icode *a= func_token_DEF_ARG(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::VOID:
{
 icode *a= func_token_VOID(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::U1:
{
 icode *a= func_token_U1(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::U8:
{
 icode *a= func_token_U8(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::U16:
{
 icode *a= func_token_U16(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::U24:
{
 icode *a= func_token_U24(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::U32:
{
 icode *a= func_token_U32(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::U64:
{
 icode *a= func_token_U64(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::F16:
{
 icode *a= func_token_F16(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::F32:
{
 icode *a= func_token_F32(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::F64:
{
 icode *a= func_token_F64(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::I1:
{
 icode *a= func_token_I1(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::I8:
{
 icode *a= func_token_I8(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::I16:
{
 icode *a= func_token_I16(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::I24:
{
 icode *a= func_token_I24(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::I32:
{
 icode *a= func_token_I32(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::I64:
{
 icode *a= func_token_I64(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::U_NUM:
{
 icode *a= func_token_U_NUM(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::LABEL_START:
{
 icode *a= func_token_LABEL_START(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::LABEL_REF:
{
 icode *a= func_token_LABEL_REF(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::VAR_REF:
{
 icode *a= func_token_VAR_REF(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::VAR_NULL:
{
 icode *a= func_token_VAR_NULL(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::FUNC_START:
{
 icode *a= func_token_FUNC_START(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::FUNC_END:
{
 icode *a= func_token_FUNC_END(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::FUNC_RETURN:
{
 icode *a= func_token_FUNC_RETURN(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::CALL_START:
{
 icode *a= func_token_CALL_START(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::CALL_END:
{
 icode *a= func_token_CALL_END(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::RET_TYPE:
{
 icode *a= func_token_RET_TYPE(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::IDENTIFIER:
{
 icode *a= func_token_IDENTIFIER(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::VAR_NAME_IDENTIFIER:
{
 icode *a= func_token_VAR_NAME_IDENTIFIER(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::I_CONST_ID:
{
 icode *a= func_token_I_CONST_ID(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::F_CONST_ID:
{
 icode *a= func_token_F_CONST_ID(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::STRING_ID:
{
 icode *a= func_token_STRING_ID(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::CONST_LIST_ID:
{
 icode *a= func_token_CONST_LIST_ID(this, tdefs, need_result_icode, result_ic);
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
case Parser::token::OPR_START:
{
 icode *a= func_token_OPR_START(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::INLINE_ASM:
{
 icode *a= func_token_INLINE_ASM(this, tdefs, need_result_icode, result_ic);
return a;
}
break;

}//switch end. case_cnt=49

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
case IAN_FILE_1: //0x1-file->/*empty*/ 
{
	icode *a= func_IAN_FILE_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_FILE_2: //0x2-file->translation_unit 
{
	icode *a= func_IAN_FILE_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_FILE_3: //0x3-file->BLOCKS translation_unit BLOCKE 
{
	icode *a= func_IAN_FILE_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TRANSLATION_UNIT_1: //0x101-translation_unit->external_declaration 
{
	icode *a= func_IAN_TRANSLATION_UNIT_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TRANSLATION_UNIT_2: //0x102-translation_unit->translation_unit external_declaration 
{
	icode *a= func_IAN_TRANSLATION_UNIT_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_EXTERNAL_DECLARATION_1: //0x201-external_declaration->block_item 
{
	icode *a= func_IAN_EXTERNAL_DECLARATION_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_EXTERNAL_DECLARATION_2: //0x202-external_declaration->function_definition 
{
	icode *a= func_IAN_EXTERNAL_DECLARATION_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_FUNCTION_DEFINITION_1: //0x301-function_definition->FUNC_START VAR_NAME_IDENTIFIER ';' ret_type compound_statement FUNC_END VAR_REF ';' 
{
	icode *a= func_IAN_FUNCTION_DEFINITION_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_FUNCTION_DEFINITION_2: //0x302-function_definition->FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type compound_statement FUNC_END VAR_REF ';' 
{
	icode *a= func_IAN_FUNCTION_DEFINITION_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_FUNCTION_DEFINITION_3: //0x303-function_definition->FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';' 
{
	icode *a= func_IAN_FUNCTION_DEFINITION_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_FUNCTION_DEFINITION_4: //0x304-function_definition->FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';' 
{
	icode *a= func_IAN_FUNCTION_DEFINITION_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_FUNCTION_DEFINITION_5: //0x305-function_definition->FUNC_START VAR_NAME_IDENTIFIER ';' ret_type FUNC_END VAR_REF ';' 
{
	icode *a= func_IAN_FUNCTION_DEFINITION_5(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_FUNCTION_DEFINITION_6: //0x306-function_definition->FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type FUNC_END VAR_REF ';' 
{
	icode *a= func_IAN_FUNCTION_DEFINITION_6(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_FUNCTION_DEFINITION_7: //0x307-function_definition->FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg FUNC_END VAR_REF ';' 
{
	icode *a= func_IAN_FUNCTION_DEFINITION_7(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_FUNCTION_DEFINITION_8: //0x308-function_definition->FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg FUNC_END VAR_REF ';' 
{
	icode *a= func_IAN_FUNCTION_DEFINITION_8(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_FUNC_ATTRIB_1: //0x401-func_attrib->func_attrib1 
{
	icode *a= func_IAN_FUNC_ATTRIB_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_FUNC_ATTRIB_2: //0x402-func_attrib->func_attrib ',' func_attrib1 
{
	icode *a= func_IAN_FUNC_ATTRIB_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_FUNC_ATTRIB1_1: //0x501-func_attrib1->IDENTIFIER '(' STRING_LITERAL ')' 
{
	icode *a= func_IAN_FUNC_ATTRIB1_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_FUNC_ATTRIB1_2: //0x502-func_attrib1->IDENTIFIER '(' I_CONSTANT ')' 
{
	icode *a= func_IAN_FUNC_ATTRIB1_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DECLARATIONS_1: //0x601-declarations->def_one_var 
{
	icode *a= func_IAN_DECLARATIONS_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DECLARATIONS_2: //0x602-declarations->declarations def_one_var 
{
	icode *a= func_IAN_DECLARATIONS_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_FUNCTION_ARG_1: //0x701-function_arg->def_arg 
{
	icode *a= func_IAN_FUNCTION_ARG_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_FUNCTION_ARG_2: //0x702-function_arg->function_arg def_arg 
{
	icode *a= func_IAN_FUNCTION_ARG_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_RET_TYPE_1: //0x801-ret_type->RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ';' 
{
	icode *a= func_IAN_RET_TYPE_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DEF_ARG_1: //0x901-def_arg->DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ';' 
{
	icode *a= func_IAN_DEF_ARG_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DEF_ONE_VAR_1: //0xa01-def_one_var->def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ';' 
{
	icode *a= func_IAN_DEF_ONE_VAR_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DEF_VAR_START_1: //0xb01-def_var_start->DEF_VAR 
{
	icode *a= func_IAN_DEF_VAR_START_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DEF_VAR_START_2: //0xb02-def_var_start->DEF_VAR_TMP 
{
	icode *a= func_IAN_DEF_VAR_START_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_1: //0xc01-type_specifier->type_specifier_basic 
{
	icode *a= func_IAN_TYPE_SPECIFIER_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_2: //0xc02-type_specifier->type_specifier_basic '(' declarations ')' 
{
	icode *a= func_IAN_TYPE_SPECIFIER_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_3: //0xc03-type_specifier->type_specifier_basic '(' '(' declarations ')' ')' 
{
	icode *a= func_IAN_TYPE_SPECIFIER_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_4: //0xc04-type_specifier->type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']' 
{
	icode *a= func_IAN_TYPE_SPECIFIER_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_5: //0xc05-type_specifier->type_specifier '[' type_specifier ']' 
{
	icode *a= func_IAN_TYPE_SPECIFIER_5(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_6: //0xc06-type_specifier->type_specifier '[' opr_elem ']' 
{
	icode *a= func_IAN_TYPE_SPECIFIER_6(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_7: //0xc07-type_specifier->type_specifier ',' func_attrib 
{
	icode *a= func_IAN_TYPE_SPECIFIER_7(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_BASIC_1: //0xd01-type_specifier_basic->VOID 
{
	icode *a= func_IAN_TYPE_SPECIFIER_BASIC_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_BASIC_2: //0xd02-type_specifier_basic->U1 
{
	icode *a= func_IAN_TYPE_SPECIFIER_BASIC_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_BASIC_3: //0xd03-type_specifier_basic->U8 
{
	icode *a= func_IAN_TYPE_SPECIFIER_BASIC_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_BASIC_4: //0xd04-type_specifier_basic->U16 
{
	icode *a= func_IAN_TYPE_SPECIFIER_BASIC_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_BASIC_5: //0xd05-type_specifier_basic->U24 
{
	icode *a= func_IAN_TYPE_SPECIFIER_BASIC_5(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_BASIC_6: //0xd06-type_specifier_basic->U32 
{
	icode *a= func_IAN_TYPE_SPECIFIER_BASIC_6(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_BASIC_7: //0xd07-type_specifier_basic->U64 
{
	icode *a= func_IAN_TYPE_SPECIFIER_BASIC_7(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_BASIC_8: //0xd08-type_specifier_basic->F16 
{
	icode *a= func_IAN_TYPE_SPECIFIER_BASIC_8(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_BASIC_9: //0xd09-type_specifier_basic->F32 
{
	icode *a= func_IAN_TYPE_SPECIFIER_BASIC_9(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_BASIC_10: //0xd0a-type_specifier_basic->F64 
{
	icode *a= func_IAN_TYPE_SPECIFIER_BASIC_10(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_BASIC_11: //0xd0b-type_specifier_basic->I1 
{
	icode *a= func_IAN_TYPE_SPECIFIER_BASIC_11(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_BASIC_12: //0xd0c-type_specifier_basic->I8 
{
	icode *a= func_IAN_TYPE_SPECIFIER_BASIC_12(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_BASIC_13: //0xd0d-type_specifier_basic->I16 
{
	icode *a= func_IAN_TYPE_SPECIFIER_BASIC_13(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_BASIC_14: //0xd0e-type_specifier_basic->I24 
{
	icode *a= func_IAN_TYPE_SPECIFIER_BASIC_14(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_BASIC_15: //0xd0f-type_specifier_basic->I32 
{
	icode *a= func_IAN_TYPE_SPECIFIER_BASIC_15(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_BASIC_16: //0xd10-type_specifier_basic->I64 
{
	icode *a= func_IAN_TYPE_SPECIFIER_BASIC_16(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_BASIC_17: //0xd11-type_specifier_basic->U_NUM 
{
	icode *a= func_IAN_TYPE_SPECIFIER_BASIC_17(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_COMPOUND_STATEMENT_1: //0xe01-compound_statement->SCOPES SCOPEE 
{
	icode *a= func_IAN_COMPOUND_STATEMENT_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_COMPOUND_STATEMENT_2: //0xe02-compound_statement->SCOPES block_item_list SCOPEE 
{
	icode *a= func_IAN_COMPOUND_STATEMENT_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_BLOCK_ITEM_LIST_1: //0xf01-block_item_list->block_item 
{
	icode *a= func_IAN_BLOCK_ITEM_LIST_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_BLOCK_ITEM_LIST_2: //0xf02-block_item_list->block_item_list block_item 
{
	icode *a= func_IAN_BLOCK_ITEM_LIST_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_BLOCK_ITEM_1: //0x1001-block_item->def_one_var 
{
	icode *a= func_IAN_BLOCK_ITEM_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_BLOCK_ITEM_2: //0x1002-block_item->statement 
{
	icode *a= func_IAN_BLOCK_ITEM_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STATEMENT_1: //0x1101-statement->opr_statement 
{
	icode *a= func_IAN_STATEMENT_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STATEMENT_2: //0x1102-statement->call_statement 
{
	icode *a= func_IAN_STATEMENT_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STATEMENT_3: //0x1103-statement->FUNC_RETURN 
{
	icode *a= func_IAN_STATEMENT_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STATEMENT_4: //0x1104-statement->label_def 
{
	icode *a= func_IAN_STATEMENT_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STATEMENT_5: //0x1105-statement->inline_asm 
{
	icode *a= func_IAN_STATEMENT_5(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STATEMENT_6: //0x1106-statement->compound_statement 
{
	icode *a= func_IAN_STATEMENT_6(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_OPR_STATEMENT_1: //0x1201-opr_statement->OPR_START STRING_LITERAL ',' opr_elem ';' ',' opr_elem ';' ',' opr_elem ';' 
{
	icode *a= func_IAN_OPR_STATEMENT_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_OPR_ELEM_1: //0x1301-opr_elem->VAR_NULL 
{
	icode *a= func_IAN_OPR_ELEM_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_OPR_ELEM_2: //0x1302-opr_elem->VAR_REF 
{
	icode *a= func_IAN_OPR_ELEM_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_OPR_ELEM_3: //0x1303-opr_elem->constant 
{
	icode *a= func_IAN_OPR_ELEM_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_OPR_ELEM_4: //0x1304-opr_elem->var_in_ref 
{
	icode *a= func_IAN_OPR_ELEM_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_OPR_ELEM_5: //0x1305-opr_elem->label_ref 
{
	icode *a= func_IAN_OPR_ELEM_5(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_CONSTANT_1: //0x1401-constant->i_const 
{
	icode *a= func_IAN_CONSTANT_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_CONSTANT_2: //0x1402-constant->f_const 
{
	icode *a= func_IAN_CONSTANT_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_CONSTANT_3: //0x1403-constant->string 
{
	icode *a= func_IAN_CONSTANT_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_CONSTANT_4: //0x1404-constant->const_list 
{
	icode *a= func_IAN_CONSTANT_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_I_CONST_1: //0x1501-i_const->I_CONST_ID I_CONSTANT 
{
	icode *a= func_IAN_I_CONST_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_I_CONST_2: //0x1502-i_const->I_CONST_ID I_CONSTANT ':' I_CONSTANT 
{
	icode *a= func_IAN_I_CONST_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_I_CONST_3: //0x1503-i_const->I_CONST_ID '-' I_CONSTANT ':' I_CONSTANT 
{
	icode *a= func_IAN_I_CONST_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_F_CONST_1: //0x1601-f_const->F_CONST_ID F_CONSTANT 
{
	icode *a= func_IAN_F_CONST_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_F_CONST_2: //0x1602-f_const->F_CONST_ID I_CONSTANT 
{
	icode *a= func_IAN_F_CONST_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_F_CONST_3: //0x1603-f_const->F_CONST_ID I_CONSTANT ':' I_CONSTANT 
{
	icode *a= func_IAN_F_CONST_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_F_CONST_4: //0x1604-f_const->F_CONST_ID F_CONSTANT ':' I_CONSTANT 
{
	icode *a= func_IAN_F_CONST_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_F_CONST_5: //0x1605-f_const->F_CONST_ID '-' I_CONSTANT ':' I_CONSTANT 
{
	icode *a= func_IAN_F_CONST_5(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_F_CONST_6: //0x1606-f_const->F_CONST_ID '-' F_CONSTANT ':' I_CONSTANT 
{
	icode *a= func_IAN_F_CONST_6(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STRING_1: //0x1701-string->STRING_ID STRING_LITERAL 
{
	icode *a= func_IAN_STRING_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_VAR_IN_REF_1: //0x1801-var_in_ref->var_in_ref_ptr 
{
	icode *a= func_IAN_VAR_IN_REF_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_VAR_IN_REF_2: //0x1802-var_in_ref->var_in_ref_array 
{
	icode *a= func_IAN_VAR_IN_REF_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_VAR_IN_REF_PTR_1: //0x1901-var_in_ref_ptr->var_in_start VAR_REF '*' I_CONSTANT 
{
	icode *a= func_IAN_VAR_IN_REF_PTR_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_VAR_IN_REF_ARRAY_1: //0x1a01-var_in_ref_array->var_in_start VAR_REF '[' opr_elem ']' 
{
	icode *a= func_IAN_VAR_IN_REF_ARRAY_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_VAR_IN_REF_ARRAY_2: //0x1a02-var_in_ref_array->var_in_ref_array '[' opr_elem ']' 
{
	icode *a= func_IAN_VAR_IN_REF_ARRAY_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_CONST_LIST_1: //0x1b01-const_list->CONST_LIST_ID '[' opr_elem_seq ']' 
{
	icode *a= func_IAN_CONST_LIST_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_VAR_IN_START_1: //0x1c01-var_in_start->VAR_IN 
{
	icode *a= func_IAN_VAR_IN_START_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_VAR_IN_START_2: //0x1c02-var_in_start->VAR_IN_TMP 
{
	icode *a= func_IAN_VAR_IN_START_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_CALL_STATEMENT_1: //0x1d01-call_statement->CALL_START VAR_REF ';' opr_elem_seq CALL_END VAR_REF ';' 
{
	icode *a= func_IAN_CALL_STATEMENT_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_CALL_STATEMENT_2: //0x1d02-call_statement->CALL_START VAR_REF ';' CALL_END VAR_REF ';' 
{
	icode *a= func_IAN_CALL_STATEMENT_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_OPR_ELEM_SEQ_1: //0x1e01-opr_elem_seq->opr_elem ';' 
{
	icode *a= func_IAN_OPR_ELEM_SEQ_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_OPR_ELEM_SEQ_2: //0x1e02-opr_elem_seq->opr_elem_seq opr_elem ';' 
{
	icode *a= func_IAN_OPR_ELEM_SEQ_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_LABEL_DEF_1: //0x1f01-label_def->LABEL_START IDENTIFIER ';' 
{
	icode *a= func_IAN_LABEL_DEF_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_LABEL_REF_1: //0x2001-label_ref->LABEL_REF IDENTIFIER 
{
	icode *a= func_IAN_LABEL_REF_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_INLINE_ASM_1: //0x2101-inline_asm->INLINE_ASM STRING_LITERAL ';' 
{
	icode *a= func_IAN_INLINE_ASM_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;

}//switch end. case_cnt=63

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

}//namespace NS_IR2ICODE
