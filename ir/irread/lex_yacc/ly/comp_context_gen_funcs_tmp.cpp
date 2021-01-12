#include <assert.h>
#include "icode.h"
#include "comp_context.h"
#include "token_defs.h"
#include "ast_to_icode_gen_def.h"
namespace NS_IR2ICODE{

class icode *  func_IAN_FILE_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1-file->/*empty*/ 
	//parent:
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_FILE_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x2-file->translation_unit 
	//parent:
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_FILE_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x3-file->BLOCKS translation_unit BLOCKE 
	//parent:
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *BLOCKS=tdefs->m_tk_elems[0];
	//token_defs *translation_unit=tdefs->m_tk_elems[1];
	//token_defs *BLOCKE=tdefs->m_tk_elems[2];
	//icode *BLOCKS_ic=pcompi->ast_to_icode(BLOCKS);
	//icode *translation_unit_ic=pcompi->ast_to_icode(translation_unit);
	//icode *BLOCKE_ic=pcompi->ast_to_icode(BLOCKE);
	//a->merge_icode(BLOCKS_ic);
	//a->merge_icode(translation_unit_ic);
	//a->merge_icode(BLOCKE_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_TRANSLATION_UNIT_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x101-translation_unit->external_declaration 
	//parent:
	// file--> translation_unit
	// file--> BLOCKS translation_unit BLOCKE
	// translation_unit--> translation_unit external_declaration
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TRANSLATION_UNIT_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x102-translation_unit->translation_unit external_declaration 
	//parent:
	// file--> translation_unit
	// file--> BLOCKS translation_unit BLOCKE
	// translation_unit--> translation_unit external_declaration
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *translation_unit=tdefs->m_tk_elems[0];
	//token_defs *external_declaration=tdefs->m_tk_elems[1];
	//icode *translation_unit_ic=pcompi->ast_to_icode(translation_unit);
	//icode *external_declaration_ic=pcompi->ast_to_icode(external_declaration);
	//a->merge_icode(translation_unit_ic);
	//a->merge_icode(external_declaration_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_EXTERNAL_DECLARATION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x201-external_declaration->block_item 
	//parent:
	// translation_unit--> external_declaration
	// translation_unit--> translation_unit external_declaration
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_EXTERNAL_DECLARATION_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x202-external_declaration->function_definition 
	//parent:
	// translation_unit--> external_declaration
	// translation_unit--> translation_unit external_declaration
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_FUNCTION_DEFINITION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x301-function_definition->FUNC_START VAR_NAME_IDENTIFIER ';' ret_type compound_statement FUNC_END VAR_REF ';' 
	//parent:
	// external_declaration--> function_definition
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *FUNC_START=tdefs->m_tk_elems[0];
	//token_defs *VAR_NAME_IDENTIFIER=tdefs->m_tk_elems[1];
	//token_defs *';'=tdefs->m_tk_elems[2];
	//token_defs *ret_type=tdefs->m_tk_elems[3];
	//token_defs *compound_statement=tdefs->m_tk_elems[4];
	//token_defs *FUNC_END=tdefs->m_tk_elems[5];
	//token_defs *VAR_REF=tdefs->m_tk_elems[6];
	//token_defs *';'=tdefs->m_tk_elems[7];
	//icode *FUNC_START_ic=pcompi->ast_to_icode(FUNC_START);
	//icode *VAR_NAME_IDENTIFIER_ic=pcompi->ast_to_icode(VAR_NAME_IDENTIFIER);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//icode *ret_type_ic=pcompi->ast_to_icode(ret_type);
	//icode *compound_statement_ic=pcompi->ast_to_icode(compound_statement);
	//icode *FUNC_END_ic=pcompi->ast_to_icode(FUNC_END);
	//icode *VAR_REF_ic=pcompi->ast_to_icode(VAR_REF);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//a->merge_icode(FUNC_START_ic);
	//a->merge_icode(VAR_NAME_IDENTIFIER_ic);
	//a->merge_icode(';'_ic);
	//a->merge_icode(ret_type_ic);
	//a->merge_icode(compound_statement_ic);
	//a->merge_icode(FUNC_END_ic);
	//a->merge_icode(VAR_REF_ic);
	//a->merge_icode(';'_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_FUNCTION_DEFINITION_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x302-function_definition->FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type compound_statement FUNC_END VAR_REF ';' 
	//parent:
	// external_declaration--> function_definition
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *FUNC_START=tdefs->m_tk_elems[0];
	//token_defs *VAR_NAME_IDENTIFIER=tdefs->m_tk_elems[1];
	//token_defs *','=tdefs->m_tk_elems[2];
	//token_defs *func_attrib=tdefs->m_tk_elems[3];
	//token_defs *';'=tdefs->m_tk_elems[4];
	//token_defs *ret_type=tdefs->m_tk_elems[5];
	//token_defs *compound_statement=tdefs->m_tk_elems[6];
	//token_defs *FUNC_END=tdefs->m_tk_elems[7];
	//token_defs *VAR_REF=tdefs->m_tk_elems[8];
	//token_defs *';'=tdefs->m_tk_elems[9];
	//icode *FUNC_START_ic=pcompi->ast_to_icode(FUNC_START);
	//icode *VAR_NAME_IDENTIFIER_ic=pcompi->ast_to_icode(VAR_NAME_IDENTIFIER);
	//icode *','_ic=pcompi->ast_to_icode(',');
	//icode *func_attrib_ic=pcompi->ast_to_icode(func_attrib);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//icode *ret_type_ic=pcompi->ast_to_icode(ret_type);
	//icode *compound_statement_ic=pcompi->ast_to_icode(compound_statement);
	//icode *FUNC_END_ic=pcompi->ast_to_icode(FUNC_END);
	//icode *VAR_REF_ic=pcompi->ast_to_icode(VAR_REF);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//a->merge_icode(FUNC_START_ic);
	//a->merge_icode(VAR_NAME_IDENTIFIER_ic);
	//a->merge_icode(','_ic);
	//a->merge_icode(func_attrib_ic);
	//a->merge_icode(';'_ic);
	//a->merge_icode(ret_type_ic);
	//a->merge_icode(compound_statement_ic);
	//a->merge_icode(FUNC_END_ic);
	//a->merge_icode(VAR_REF_ic);
	//a->merge_icode(';'_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_FUNCTION_DEFINITION_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x303-function_definition->FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';' 
	//parent:
	// external_declaration--> function_definition
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *FUNC_START=tdefs->m_tk_elems[0];
	//token_defs *VAR_NAME_IDENTIFIER=tdefs->m_tk_elems[1];
	//token_defs *';'=tdefs->m_tk_elems[2];
	//token_defs *ret_type=tdefs->m_tk_elems[3];
	//token_defs *function_arg=tdefs->m_tk_elems[4];
	//token_defs *compound_statement=tdefs->m_tk_elems[5];
	//token_defs *FUNC_END=tdefs->m_tk_elems[6];
	//token_defs *VAR_REF=tdefs->m_tk_elems[7];
	//token_defs *';'=tdefs->m_tk_elems[8];
	//icode *FUNC_START_ic=pcompi->ast_to_icode(FUNC_START);
	//icode *VAR_NAME_IDENTIFIER_ic=pcompi->ast_to_icode(VAR_NAME_IDENTIFIER);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//icode *ret_type_ic=pcompi->ast_to_icode(ret_type);
	//icode *function_arg_ic=pcompi->ast_to_icode(function_arg);
	//icode *compound_statement_ic=pcompi->ast_to_icode(compound_statement);
	//icode *FUNC_END_ic=pcompi->ast_to_icode(FUNC_END);
	//icode *VAR_REF_ic=pcompi->ast_to_icode(VAR_REF);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//a->merge_icode(FUNC_START_ic);
	//a->merge_icode(VAR_NAME_IDENTIFIER_ic);
	//a->merge_icode(';'_ic);
	//a->merge_icode(ret_type_ic);
	//a->merge_icode(function_arg_ic);
	//a->merge_icode(compound_statement_ic);
	//a->merge_icode(FUNC_END_ic);
	//a->merge_icode(VAR_REF_ic);
	//a->merge_icode(';'_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_FUNCTION_DEFINITION_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x304-function_definition->FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';' 
	//parent:
	// external_declaration--> function_definition
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *FUNC_START=tdefs->m_tk_elems[0];
	//token_defs *VAR_NAME_IDENTIFIER=tdefs->m_tk_elems[1];
	//token_defs *','=tdefs->m_tk_elems[2];
	//token_defs *func_attrib=tdefs->m_tk_elems[3];
	//token_defs *';'=tdefs->m_tk_elems[4];
	//token_defs *ret_type=tdefs->m_tk_elems[5];
	//token_defs *function_arg=tdefs->m_tk_elems[6];
	//token_defs *compound_statement=tdefs->m_tk_elems[7];
	//token_defs *FUNC_END=tdefs->m_tk_elems[8];
	//token_defs *VAR_REF=tdefs->m_tk_elems[9];
	//token_defs *';'=tdefs->m_tk_elems[a];
	//icode *FUNC_START_ic=pcompi->ast_to_icode(FUNC_START);
	//icode *VAR_NAME_IDENTIFIER_ic=pcompi->ast_to_icode(VAR_NAME_IDENTIFIER);
	//icode *','_ic=pcompi->ast_to_icode(',');
	//icode *func_attrib_ic=pcompi->ast_to_icode(func_attrib);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//icode *ret_type_ic=pcompi->ast_to_icode(ret_type);
	//icode *function_arg_ic=pcompi->ast_to_icode(function_arg);
	//icode *compound_statement_ic=pcompi->ast_to_icode(compound_statement);
	//icode *FUNC_END_ic=pcompi->ast_to_icode(FUNC_END);
	//icode *VAR_REF_ic=pcompi->ast_to_icode(VAR_REF);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//a->merge_icode(FUNC_START_ic);
	//a->merge_icode(VAR_NAME_IDENTIFIER_ic);
	//a->merge_icode(','_ic);
	//a->merge_icode(func_attrib_ic);
	//a->merge_icode(';'_ic);
	//a->merge_icode(ret_type_ic);
	//a->merge_icode(function_arg_ic);
	//a->merge_icode(compound_statement_ic);
	//a->merge_icode(FUNC_END_ic);
	//a->merge_icode(VAR_REF_ic);
	//a->merge_icode(';'_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_FUNCTION_DEFINITION_5(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x305-function_definition->FUNC_START VAR_NAME_IDENTIFIER ';' ret_type FUNC_END VAR_REF ';' 
	//parent:
	// external_declaration--> function_definition
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *FUNC_START=tdefs->m_tk_elems[0];
	//token_defs *VAR_NAME_IDENTIFIER=tdefs->m_tk_elems[1];
	//token_defs *';'=tdefs->m_tk_elems[2];
	//token_defs *ret_type=tdefs->m_tk_elems[3];
	//token_defs *FUNC_END=tdefs->m_tk_elems[4];
	//token_defs *VAR_REF=tdefs->m_tk_elems[5];
	//token_defs *';'=tdefs->m_tk_elems[6];
	//icode *FUNC_START_ic=pcompi->ast_to_icode(FUNC_START);
	//icode *VAR_NAME_IDENTIFIER_ic=pcompi->ast_to_icode(VAR_NAME_IDENTIFIER);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//icode *ret_type_ic=pcompi->ast_to_icode(ret_type);
	//icode *FUNC_END_ic=pcompi->ast_to_icode(FUNC_END);
	//icode *VAR_REF_ic=pcompi->ast_to_icode(VAR_REF);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//a->merge_icode(FUNC_START_ic);
	//a->merge_icode(VAR_NAME_IDENTIFIER_ic);
	//a->merge_icode(';'_ic);
	//a->merge_icode(ret_type_ic);
	//a->merge_icode(FUNC_END_ic);
	//a->merge_icode(VAR_REF_ic);
	//a->merge_icode(';'_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_FUNCTION_DEFINITION_6(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x306-function_definition->FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type FUNC_END VAR_REF ';' 
	//parent:
	// external_declaration--> function_definition
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *FUNC_START=tdefs->m_tk_elems[0];
	//token_defs *VAR_NAME_IDENTIFIER=tdefs->m_tk_elems[1];
	//token_defs *','=tdefs->m_tk_elems[2];
	//token_defs *func_attrib=tdefs->m_tk_elems[3];
	//token_defs *';'=tdefs->m_tk_elems[4];
	//token_defs *ret_type=tdefs->m_tk_elems[5];
	//token_defs *FUNC_END=tdefs->m_tk_elems[6];
	//token_defs *VAR_REF=tdefs->m_tk_elems[7];
	//token_defs *';'=tdefs->m_tk_elems[8];
	//icode *FUNC_START_ic=pcompi->ast_to_icode(FUNC_START);
	//icode *VAR_NAME_IDENTIFIER_ic=pcompi->ast_to_icode(VAR_NAME_IDENTIFIER);
	//icode *','_ic=pcompi->ast_to_icode(',');
	//icode *func_attrib_ic=pcompi->ast_to_icode(func_attrib);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//icode *ret_type_ic=pcompi->ast_to_icode(ret_type);
	//icode *FUNC_END_ic=pcompi->ast_to_icode(FUNC_END);
	//icode *VAR_REF_ic=pcompi->ast_to_icode(VAR_REF);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//a->merge_icode(FUNC_START_ic);
	//a->merge_icode(VAR_NAME_IDENTIFIER_ic);
	//a->merge_icode(','_ic);
	//a->merge_icode(func_attrib_ic);
	//a->merge_icode(';'_ic);
	//a->merge_icode(ret_type_ic);
	//a->merge_icode(FUNC_END_ic);
	//a->merge_icode(VAR_REF_ic);
	//a->merge_icode(';'_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_FUNCTION_DEFINITION_7(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x307-function_definition->FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg FUNC_END VAR_REF ';' 
	//parent:
	// external_declaration--> function_definition
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *FUNC_START=tdefs->m_tk_elems[0];
	//token_defs *VAR_NAME_IDENTIFIER=tdefs->m_tk_elems[1];
	//token_defs *';'=tdefs->m_tk_elems[2];
	//token_defs *ret_type=tdefs->m_tk_elems[3];
	//token_defs *function_arg=tdefs->m_tk_elems[4];
	//token_defs *FUNC_END=tdefs->m_tk_elems[5];
	//token_defs *VAR_REF=tdefs->m_tk_elems[6];
	//token_defs *';'=tdefs->m_tk_elems[7];
	//icode *FUNC_START_ic=pcompi->ast_to_icode(FUNC_START);
	//icode *VAR_NAME_IDENTIFIER_ic=pcompi->ast_to_icode(VAR_NAME_IDENTIFIER);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//icode *ret_type_ic=pcompi->ast_to_icode(ret_type);
	//icode *function_arg_ic=pcompi->ast_to_icode(function_arg);
	//icode *FUNC_END_ic=pcompi->ast_to_icode(FUNC_END);
	//icode *VAR_REF_ic=pcompi->ast_to_icode(VAR_REF);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//a->merge_icode(FUNC_START_ic);
	//a->merge_icode(VAR_NAME_IDENTIFIER_ic);
	//a->merge_icode(';'_ic);
	//a->merge_icode(ret_type_ic);
	//a->merge_icode(function_arg_ic);
	//a->merge_icode(FUNC_END_ic);
	//a->merge_icode(VAR_REF_ic);
	//a->merge_icode(';'_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_FUNCTION_DEFINITION_8(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x308-function_definition->FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg FUNC_END VAR_REF ';' 
	//parent:
	// external_declaration--> function_definition
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *FUNC_START=tdefs->m_tk_elems[0];
	//token_defs *VAR_NAME_IDENTIFIER=tdefs->m_tk_elems[1];
	//token_defs *','=tdefs->m_tk_elems[2];
	//token_defs *func_attrib=tdefs->m_tk_elems[3];
	//token_defs *';'=tdefs->m_tk_elems[4];
	//token_defs *ret_type=tdefs->m_tk_elems[5];
	//token_defs *function_arg=tdefs->m_tk_elems[6];
	//token_defs *FUNC_END=tdefs->m_tk_elems[7];
	//token_defs *VAR_REF=tdefs->m_tk_elems[8];
	//token_defs *';'=tdefs->m_tk_elems[9];
	//icode *FUNC_START_ic=pcompi->ast_to_icode(FUNC_START);
	//icode *VAR_NAME_IDENTIFIER_ic=pcompi->ast_to_icode(VAR_NAME_IDENTIFIER);
	//icode *','_ic=pcompi->ast_to_icode(',');
	//icode *func_attrib_ic=pcompi->ast_to_icode(func_attrib);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//icode *ret_type_ic=pcompi->ast_to_icode(ret_type);
	//icode *function_arg_ic=pcompi->ast_to_icode(function_arg);
	//icode *FUNC_END_ic=pcompi->ast_to_icode(FUNC_END);
	//icode *VAR_REF_ic=pcompi->ast_to_icode(VAR_REF);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//a->merge_icode(FUNC_START_ic);
	//a->merge_icode(VAR_NAME_IDENTIFIER_ic);
	//a->merge_icode(','_ic);
	//a->merge_icode(func_attrib_ic);
	//a->merge_icode(';'_ic);
	//a->merge_icode(ret_type_ic);
	//a->merge_icode(function_arg_ic);
	//a->merge_icode(FUNC_END_ic);
	//a->merge_icode(VAR_REF_ic);
	//a->merge_icode(';'_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_FUNC_ATTRIB_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x401-func_attrib->func_attrib1 
	//parent:
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg FUNC_END VAR_REF ';'
	// func_attrib--> func_attrib ',' func_attrib1
	// ret_type--> RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
	// def_arg--> DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
	// def_one_var--> def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_FUNC_ATTRIB_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x402-func_attrib->func_attrib ',' func_attrib1 
	//parent:
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg FUNC_END VAR_REF ';'
	// func_attrib--> func_attrib ',' func_attrib1
	// ret_type--> RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
	// def_arg--> DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
	// def_one_var--> def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *func_attrib=tdefs->m_tk_elems[0];
	//token_defs *','=tdefs->m_tk_elems[1];
	//token_defs *func_attrib1=tdefs->m_tk_elems[2];
	//icode *func_attrib_ic=pcompi->ast_to_icode(func_attrib);
	//icode *','_ic=pcompi->ast_to_icode(',');
	//icode *func_attrib1_ic=pcompi->ast_to_icode(func_attrib1);
	//a->merge_icode(func_attrib_ic);
	//a->merge_icode(','_ic);
	//a->merge_icode(func_attrib1_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_FUNC_ATTRIB1_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x501-func_attrib1->IDENTIFIER '(' STRING_LITERAL ')' 
	//parent:
	// func_attrib--> func_attrib1
	// func_attrib--> func_attrib ',' func_attrib1
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *IDENTIFIER=tdefs->m_tk_elems[0];
	//token_defs *'('=tdefs->m_tk_elems[1];
	//token_defs *STRING_LITERAL=tdefs->m_tk_elems[2];
	//token_defs *')'=tdefs->m_tk_elems[3];
	//icode *IDENTIFIER_ic=pcompi->ast_to_icode(IDENTIFIER);
	//icode *'('_ic=pcompi->ast_to_icode('(');
	//icode *STRING_LITERAL_ic=pcompi->ast_to_icode(STRING_LITERAL);
	//icode *')'_ic=pcompi->ast_to_icode(')');
	//a->merge_icode(IDENTIFIER_ic);
	//a->merge_icode('('_ic);
	//a->merge_icode(STRING_LITERAL_ic);
	//a->merge_icode(')'_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_FUNC_ATTRIB1_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x502-func_attrib1->IDENTIFIER '(' I_CONSTANT ')' 
	//parent:
	// func_attrib--> func_attrib1
	// func_attrib--> func_attrib ',' func_attrib1
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *IDENTIFIER=tdefs->m_tk_elems[0];
	//token_defs *'('=tdefs->m_tk_elems[1];
	//token_defs *I_CONSTANT=tdefs->m_tk_elems[2];
	//token_defs *')'=tdefs->m_tk_elems[3];
	//icode *IDENTIFIER_ic=pcompi->ast_to_icode(IDENTIFIER);
	//icode *'('_ic=pcompi->ast_to_icode('(');
	//icode *I_CONSTANT_ic=pcompi->ast_to_icode(I_CONSTANT);
	//icode *')'_ic=pcompi->ast_to_icode(')');
	//a->merge_icode(IDENTIFIER_ic);
	//a->merge_icode('('_ic);
	//a->merge_icode(I_CONSTANT_ic);
	//a->merge_icode(')'_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_DECLARATIONS_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x601-declarations->def_one_var 
	//parent:
	// declarations--> declarations def_one_var
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_DECLARATIONS_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x602-declarations->declarations def_one_var 
	//parent:
	// declarations--> declarations def_one_var
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *declarations=tdefs->m_tk_elems[0];
	//token_defs *def_one_var=tdefs->m_tk_elems[1];
	//icode *declarations_ic=pcompi->ast_to_icode(declarations);
	//icode *def_one_var_ic=pcompi->ast_to_icode(def_one_var);
	//a->merge_icode(declarations_ic);
	//a->merge_icode(def_one_var_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_FUNCTION_ARG_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x701-function_arg->def_arg 
	//parent:
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg FUNC_END VAR_REF ';'
	// function_arg--> function_arg def_arg
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_FUNCTION_ARG_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x702-function_arg->function_arg def_arg 
	//parent:
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg FUNC_END VAR_REF ';'
	// function_arg--> function_arg def_arg
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *function_arg=tdefs->m_tk_elems[0];
	//token_defs *def_arg=tdefs->m_tk_elems[1];
	//icode *function_arg_ic=pcompi->ast_to_icode(function_arg);
	//icode *def_arg_ic=pcompi->ast_to_icode(def_arg);
	//a->merge_icode(function_arg_ic);
	//a->merge_icode(def_arg_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_RET_TYPE_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x801-ret_type->RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ';' 
	//parent:
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg FUNC_END VAR_REF ';'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *RET_TYPE=tdefs->m_tk_elems[0];
	//token_defs *VAR_NAME_IDENTIFIER=tdefs->m_tk_elems[1];
	//token_defs *','=tdefs->m_tk_elems[2];
	//token_defs *type_specifier=tdefs->m_tk_elems[3];
	//token_defs *';'=tdefs->m_tk_elems[4];
	//icode *RET_TYPE_ic=pcompi->ast_to_icode(RET_TYPE);
	//icode *VAR_NAME_IDENTIFIER_ic=pcompi->ast_to_icode(VAR_NAME_IDENTIFIER);
	//icode *','_ic=pcompi->ast_to_icode(',');
	//icode *type_specifier_ic=pcompi->ast_to_icode(type_specifier);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//a->merge_icode(RET_TYPE_ic);
	//a->merge_icode(VAR_NAME_IDENTIFIER_ic);
	//a->merge_icode(','_ic);
	//a->merge_icode(type_specifier_ic);
	//a->merge_icode(';'_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_RET_TYPE_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x802-ret_type->RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';' 
	//parent:
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg FUNC_END VAR_REF ';'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *RET_TYPE=tdefs->m_tk_elems[0];
	//token_defs *VAR_NAME_IDENTIFIER=tdefs->m_tk_elems[1];
	//token_defs *','=tdefs->m_tk_elems[2];
	//token_defs *type_specifier=tdefs->m_tk_elems[3];
	//token_defs *','=tdefs->m_tk_elems[4];
	//token_defs *func_attrib=tdefs->m_tk_elems[5];
	//token_defs *';'=tdefs->m_tk_elems[6];
	//icode *RET_TYPE_ic=pcompi->ast_to_icode(RET_TYPE);
	//icode *VAR_NAME_IDENTIFIER_ic=pcompi->ast_to_icode(VAR_NAME_IDENTIFIER);
	//icode *','_ic=pcompi->ast_to_icode(',');
	//icode *type_specifier_ic=pcompi->ast_to_icode(type_specifier);
	//icode *','_ic=pcompi->ast_to_icode(',');
	//icode *func_attrib_ic=pcompi->ast_to_icode(func_attrib);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//a->merge_icode(RET_TYPE_ic);
	//a->merge_icode(VAR_NAME_IDENTIFIER_ic);
	//a->merge_icode(','_ic);
	//a->merge_icode(type_specifier_ic);
	//a->merge_icode(','_ic);
	//a->merge_icode(func_attrib_ic);
	//a->merge_icode(';'_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_DEF_ARG_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x901-def_arg->DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ';' 
	//parent:
	// function_arg--> def_arg
	// function_arg--> function_arg def_arg
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *DEF_ARG=tdefs->m_tk_elems[0];
	//token_defs *VAR_NAME_IDENTIFIER=tdefs->m_tk_elems[1];
	//token_defs *','=tdefs->m_tk_elems[2];
	//token_defs *type_specifier=tdefs->m_tk_elems[3];
	//token_defs *';'=tdefs->m_tk_elems[4];
	//icode *DEF_ARG_ic=pcompi->ast_to_icode(DEF_ARG);
	//icode *VAR_NAME_IDENTIFIER_ic=pcompi->ast_to_icode(VAR_NAME_IDENTIFIER);
	//icode *','_ic=pcompi->ast_to_icode(',');
	//icode *type_specifier_ic=pcompi->ast_to_icode(type_specifier);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//a->merge_icode(DEF_ARG_ic);
	//a->merge_icode(VAR_NAME_IDENTIFIER_ic);
	//a->merge_icode(','_ic);
	//a->merge_icode(type_specifier_ic);
	//a->merge_icode(';'_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_DEF_ARG_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x902-def_arg->DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';' 
	//parent:
	// function_arg--> def_arg
	// function_arg--> function_arg def_arg
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *DEF_ARG=tdefs->m_tk_elems[0];
	//token_defs *VAR_NAME_IDENTIFIER=tdefs->m_tk_elems[1];
	//token_defs *','=tdefs->m_tk_elems[2];
	//token_defs *type_specifier=tdefs->m_tk_elems[3];
	//token_defs *','=tdefs->m_tk_elems[4];
	//token_defs *func_attrib=tdefs->m_tk_elems[5];
	//token_defs *';'=tdefs->m_tk_elems[6];
	//icode *DEF_ARG_ic=pcompi->ast_to_icode(DEF_ARG);
	//icode *VAR_NAME_IDENTIFIER_ic=pcompi->ast_to_icode(VAR_NAME_IDENTIFIER);
	//icode *','_ic=pcompi->ast_to_icode(',');
	//icode *type_specifier_ic=pcompi->ast_to_icode(type_specifier);
	//icode *','_ic=pcompi->ast_to_icode(',');
	//icode *func_attrib_ic=pcompi->ast_to_icode(func_attrib);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//a->merge_icode(DEF_ARG_ic);
	//a->merge_icode(VAR_NAME_IDENTIFIER_ic);
	//a->merge_icode(','_ic);
	//a->merge_icode(type_specifier_ic);
	//a->merge_icode(','_ic);
	//a->merge_icode(func_attrib_ic);
	//a->merge_icode(';'_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_DEF_ONE_VAR_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xa01-def_one_var->def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ';' 
	//parent:
	// declarations--> def_one_var
	// declarations--> declarations def_one_var
	// block_item--> def_one_var
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *def_var_start=tdefs->m_tk_elems[0];
	//token_defs *VAR_NAME_IDENTIFIER=tdefs->m_tk_elems[1];
	//token_defs *','=tdefs->m_tk_elems[2];
	//token_defs *type_specifier=tdefs->m_tk_elems[3];
	//token_defs *';'=tdefs->m_tk_elems[4];
	//icode *def_var_start_ic=pcompi->ast_to_icode(def_var_start);
	//icode *VAR_NAME_IDENTIFIER_ic=pcompi->ast_to_icode(VAR_NAME_IDENTIFIER);
	//icode *','_ic=pcompi->ast_to_icode(',');
	//icode *type_specifier_ic=pcompi->ast_to_icode(type_specifier);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//a->merge_icode(def_var_start_ic);
	//a->merge_icode(VAR_NAME_IDENTIFIER_ic);
	//a->merge_icode(','_ic);
	//a->merge_icode(type_specifier_ic);
	//a->merge_icode(';'_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_DEF_ONE_VAR_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xa02-def_one_var->def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';' 
	//parent:
	// declarations--> def_one_var
	// declarations--> declarations def_one_var
	// block_item--> def_one_var
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *def_var_start=tdefs->m_tk_elems[0];
	//token_defs *VAR_NAME_IDENTIFIER=tdefs->m_tk_elems[1];
	//token_defs *','=tdefs->m_tk_elems[2];
	//token_defs *type_specifier=tdefs->m_tk_elems[3];
	//token_defs *','=tdefs->m_tk_elems[4];
	//token_defs *func_attrib=tdefs->m_tk_elems[5];
	//token_defs *';'=tdefs->m_tk_elems[6];
	//icode *def_var_start_ic=pcompi->ast_to_icode(def_var_start);
	//icode *VAR_NAME_IDENTIFIER_ic=pcompi->ast_to_icode(VAR_NAME_IDENTIFIER);
	//icode *','_ic=pcompi->ast_to_icode(',');
	//icode *type_specifier_ic=pcompi->ast_to_icode(type_specifier);
	//icode *','_ic=pcompi->ast_to_icode(',');
	//icode *func_attrib_ic=pcompi->ast_to_icode(func_attrib);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//a->merge_icode(def_var_start_ic);
	//a->merge_icode(VAR_NAME_IDENTIFIER_ic);
	//a->merge_icode(','_ic);
	//a->merge_icode(type_specifier_ic);
	//a->merge_icode(','_ic);
	//a->merge_icode(func_attrib_ic);
	//a->merge_icode(';'_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_DEF_VAR_START_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xb01-def_var_start->DEF_VAR 
	//parent:
	// def_one_var--> def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_one_var--> def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_DEF_VAR_START_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xb02-def_var_start->DEF_VAR_TMP 
	//parent:
	// def_one_var--> def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_one_var--> def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xc01-type_specifier->type_specifier_basic 
	//parent:
	// ret_type--> RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// ret_type--> RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
	// def_arg--> DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_arg--> DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
	// def_one_var--> def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_one_var--> def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
	// type_specifier--> type_specifier '[' type_specifier ']'
	// type_specifier--> type_specifier '[' opr_elem ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xc02-type_specifier->type_specifier_basic '(' declarations ')' 
	//parent:
	// ret_type--> RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// ret_type--> RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
	// def_arg--> DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_arg--> DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
	// def_one_var--> def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_one_var--> def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
	// type_specifier--> type_specifier '[' type_specifier ']'
	// type_specifier--> type_specifier '[' opr_elem ']'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *type_specifier_basic=tdefs->m_tk_elems[0];
	//token_defs *'('=tdefs->m_tk_elems[1];
	//token_defs *declarations=tdefs->m_tk_elems[2];
	//token_defs *')'=tdefs->m_tk_elems[3];
	//icode *type_specifier_basic_ic=pcompi->ast_to_icode(type_specifier_basic);
	//icode *'('_ic=pcompi->ast_to_icode('(');
	//icode *declarations_ic=pcompi->ast_to_icode(declarations);
	//icode *')'_ic=pcompi->ast_to_icode(')');
	//a->merge_icode(type_specifier_basic_ic);
	//a->merge_icode('('_ic);
	//a->merge_icode(declarations_ic);
	//a->merge_icode(')'_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_TYPE_SPECIFIER_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xc03-type_specifier->type_specifier_basic '(' '(' declarations ')' ')' 
	//parent:
	// ret_type--> RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// ret_type--> RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
	// def_arg--> DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_arg--> DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
	// def_one_var--> def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_one_var--> def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
	// type_specifier--> type_specifier '[' type_specifier ']'
	// type_specifier--> type_specifier '[' opr_elem ']'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *type_specifier_basic=tdefs->m_tk_elems[0];
	//token_defs *'('=tdefs->m_tk_elems[1];
	//token_defs *'('=tdefs->m_tk_elems[2];
	//token_defs *declarations=tdefs->m_tk_elems[3];
	//token_defs *')'=tdefs->m_tk_elems[4];
	//token_defs *')'=tdefs->m_tk_elems[5];
	//icode *type_specifier_basic_ic=pcompi->ast_to_icode(type_specifier_basic);
	//icode *'('_ic=pcompi->ast_to_icode('(');
	//icode *'('_ic=pcompi->ast_to_icode('(');
	//icode *declarations_ic=pcompi->ast_to_icode(declarations);
	//icode *')'_ic=pcompi->ast_to_icode(')');
	//icode *')'_ic=pcompi->ast_to_icode(')');
	//a->merge_icode(type_specifier_basic_ic);
	//a->merge_icode('('_ic);
	//a->merge_icode('('_ic);
	//a->merge_icode(declarations_ic);
	//a->merge_icode(')'_ic);
	//a->merge_icode(')'_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_TYPE_SPECIFIER_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xc04-type_specifier->type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']' 
	//parent:
	// ret_type--> RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// ret_type--> RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
	// def_arg--> DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_arg--> DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
	// def_one_var--> def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_one_var--> def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
	// type_specifier--> type_specifier '[' type_specifier ']'
	// type_specifier--> type_specifier '[' opr_elem ']'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *type_specifier_basic=tdefs->m_tk_elems[0];
	//token_defs *'*'=tdefs->m_tk_elems[1];
	//token_defs *I_CONSTANT=tdefs->m_tk_elems[2];
	//token_defs *'*'=tdefs->m_tk_elems[3];
	//token_defs *'['=tdefs->m_tk_elems[4];
	//token_defs *type_specifier=tdefs->m_tk_elems[5];
	//token_defs *']'=tdefs->m_tk_elems[6];
	//icode *type_specifier_basic_ic=pcompi->ast_to_icode(type_specifier_basic);
	//icode *'*'_ic=pcompi->ast_to_icode('*');
	//icode *I_CONSTANT_ic=pcompi->ast_to_icode(I_CONSTANT);
	//icode *'*'_ic=pcompi->ast_to_icode('*');
	//icode *'['_ic=pcompi->ast_to_icode('[');
	//icode *type_specifier_ic=pcompi->ast_to_icode(type_specifier);
	//icode *']'_ic=pcompi->ast_to_icode(']');
	//a->merge_icode(type_specifier_basic_ic);
	//a->merge_icode('*'_ic);
	//a->merge_icode(I_CONSTANT_ic);
	//a->merge_icode('*'_ic);
	//a->merge_icode('['_ic);
	//a->merge_icode(type_specifier_ic);
	//a->merge_icode(']'_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_TYPE_SPECIFIER_5(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xc05-type_specifier->type_specifier '[' type_specifier ']' 
	//parent:
	// ret_type--> RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// ret_type--> RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
	// def_arg--> DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_arg--> DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
	// def_one_var--> def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_one_var--> def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
	// type_specifier--> type_specifier '[' type_specifier ']'
	// type_specifier--> type_specifier '[' opr_elem ']'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *type_specifier=tdefs->m_tk_elems[0];
	//token_defs *'['=tdefs->m_tk_elems[1];
	//token_defs *type_specifier=tdefs->m_tk_elems[2];
	//token_defs *']'=tdefs->m_tk_elems[3];
	//icode *type_specifier_ic=pcompi->ast_to_icode(type_specifier);
	//icode *'['_ic=pcompi->ast_to_icode('[');
	//icode *type_specifier_ic=pcompi->ast_to_icode(type_specifier);
	//icode *']'_ic=pcompi->ast_to_icode(']');
	//a->merge_icode(type_specifier_ic);
	//a->merge_icode('['_ic);
	//a->merge_icode(type_specifier_ic);
	//a->merge_icode(']'_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_TYPE_SPECIFIER_6(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xc06-type_specifier->type_specifier '[' opr_elem ']' 
	//parent:
	// ret_type--> RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// ret_type--> RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
	// def_arg--> DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_arg--> DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
	// def_one_var--> def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_one_var--> def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
	// type_specifier--> type_specifier '[' type_specifier ']'
	// type_specifier--> type_specifier '[' opr_elem ']'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *type_specifier=tdefs->m_tk_elems[0];
	//token_defs *'['=tdefs->m_tk_elems[1];
	//token_defs *opr_elem=tdefs->m_tk_elems[2];
	//token_defs *']'=tdefs->m_tk_elems[3];
	//icode *type_specifier_ic=pcompi->ast_to_icode(type_specifier);
	//icode *'['_ic=pcompi->ast_to_icode('[');
	//icode *opr_elem_ic=pcompi->ast_to_icode(opr_elem);
	//icode *']'_ic=pcompi->ast_to_icode(']');
	//a->merge_icode(type_specifier_ic);
	//a->merge_icode('['_ic);
	//a->merge_icode(opr_elem_ic);
	//a->merge_icode(']'_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xd01-type_specifier_basic->VOID 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xd02-type_specifier_basic->U1 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xd03-type_specifier_basic->U8 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xd04-type_specifier_basic->U16 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_5(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xd05-type_specifier_basic->U24 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_6(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xd06-type_specifier_basic->U32 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_7(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xd07-type_specifier_basic->U64 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_8(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xd08-type_specifier_basic->F16 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_9(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xd09-type_specifier_basic->F32 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_10(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xd0a-type_specifier_basic->F64 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_11(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xd0b-type_specifier_basic->I1 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_12(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xd0c-type_specifier_basic->I8 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_13(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xd0d-type_specifier_basic->I16 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_14(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xd0e-type_specifier_basic->I24 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_15(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xd0f-type_specifier_basic->I32 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_16(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xd10-type_specifier_basic->I64 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_17(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xd11-type_specifier_basic->U_NUM 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_COMPOUND_STATEMENT_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xe01-compound_statement->SCOPES SCOPEE 
	//parent:
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';'
	// statement--> compound_statement
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *SCOPES=tdefs->m_tk_elems[0];
	//token_defs *SCOPEE=tdefs->m_tk_elems[1];
	//icode *SCOPES_ic=pcompi->ast_to_icode(SCOPES);
	//icode *SCOPEE_ic=pcompi->ast_to_icode(SCOPEE);
	//a->merge_icode(SCOPES_ic);
	//a->merge_icode(SCOPEE_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_COMPOUND_STATEMENT_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xe02-compound_statement->SCOPES block_item_list SCOPEE 
	//parent:
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';'
	// statement--> compound_statement
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *SCOPES=tdefs->m_tk_elems[0];
	//token_defs *block_item_list=tdefs->m_tk_elems[1];
	//token_defs *SCOPEE=tdefs->m_tk_elems[2];
	//icode *SCOPES_ic=pcompi->ast_to_icode(SCOPES);
	//icode *block_item_list_ic=pcompi->ast_to_icode(block_item_list);
	//icode *SCOPEE_ic=pcompi->ast_to_icode(SCOPEE);
	//a->merge_icode(SCOPES_ic);
	//a->merge_icode(block_item_list_ic);
	//a->merge_icode(SCOPEE_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_BLOCK_ITEM_LIST_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xf01-block_item_list->block_item 
	//parent:
	// compound_statement--> SCOPES block_item_list SCOPEE
	// block_item_list--> block_item_list block_item
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_BLOCK_ITEM_LIST_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xf02-block_item_list->block_item_list block_item 
	//parent:
	// compound_statement--> SCOPES block_item_list SCOPEE
	// block_item_list--> block_item_list block_item
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *block_item_list=tdefs->m_tk_elems[0];
	//token_defs *block_item=tdefs->m_tk_elems[1];
	//icode *block_item_list_ic=pcompi->ast_to_icode(block_item_list);
	//icode *block_item_ic=pcompi->ast_to_icode(block_item);
	//a->merge_icode(block_item_list_ic);
	//a->merge_icode(block_item_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_BLOCK_ITEM_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1001-block_item->def_one_var 
	//parent:
	// external_declaration--> block_item
	// block_item_list--> block_item
	// block_item_list--> block_item_list block_item
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_BLOCK_ITEM_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1002-block_item->statement 
	//parent:
	// external_declaration--> block_item
	// block_item_list--> block_item
	// block_item_list--> block_item_list block_item
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_STATEMENT_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1101-statement->opr_statement 
	//parent:
	// block_item--> statement
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_STATEMENT_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1102-statement->call_statement 
	//parent:
	// block_item--> statement
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_STATEMENT_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1103-statement->FUNC_RETURN 
	//parent:
	// block_item--> statement
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_STATEMENT_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1104-statement->label_def 
	//parent:
	// block_item--> statement
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_STATEMENT_5(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1105-statement->inline_asm 
	//parent:
	// block_item--> statement
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_STATEMENT_6(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1106-statement->compound_statement 
	//parent:
	// block_item--> statement
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_OPR_STATEMENT_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1201-opr_statement->OPR_START STRING_LITERAL ',' opr_elem ';' ',' opr_elem ';' ',' opr_elem ';' 
	//parent:
	// statement--> opr_statement
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *OPR_START=tdefs->m_tk_elems[0];
	//token_defs *STRING_LITERAL=tdefs->m_tk_elems[1];
	//token_defs *','=tdefs->m_tk_elems[2];
	//token_defs *opr_elem=tdefs->m_tk_elems[3];
	//token_defs *';'=tdefs->m_tk_elems[4];
	//token_defs *','=tdefs->m_tk_elems[5];
	//token_defs *opr_elem=tdefs->m_tk_elems[6];
	//token_defs *';'=tdefs->m_tk_elems[7];
	//token_defs *','=tdefs->m_tk_elems[8];
	//token_defs *opr_elem=tdefs->m_tk_elems[9];
	//token_defs *';'=tdefs->m_tk_elems[a];
	//icode *OPR_START_ic=pcompi->ast_to_icode(OPR_START);
	//icode *STRING_LITERAL_ic=pcompi->ast_to_icode(STRING_LITERAL);
	//icode *','_ic=pcompi->ast_to_icode(',');
	//icode *opr_elem_ic=pcompi->ast_to_icode(opr_elem);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//icode *','_ic=pcompi->ast_to_icode(',');
	//icode *opr_elem_ic=pcompi->ast_to_icode(opr_elem);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//icode *','_ic=pcompi->ast_to_icode(',');
	//icode *opr_elem_ic=pcompi->ast_to_icode(opr_elem);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//a->merge_icode(OPR_START_ic);
	//a->merge_icode(STRING_LITERAL_ic);
	//a->merge_icode(','_ic);
	//a->merge_icode(opr_elem_ic);
	//a->merge_icode(';'_ic);
	//a->merge_icode(','_ic);
	//a->merge_icode(opr_elem_ic);
	//a->merge_icode(';'_ic);
	//a->merge_icode(','_ic);
	//a->merge_icode(opr_elem_ic);
	//a->merge_icode(';'_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_OPR_ELEM_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1301-opr_elem->VAR_NULL 
	//parent:
	// type_specifier--> type_specifier '[' opr_elem ']'
	// opr_statement--> OPR_START STRING_LITERAL ',' opr_elem ';' ',' opr_elem ';' ',' opr_elem ';'
	// var_in_ref_array--> var_in_start VAR_REF '[' opr_elem ']'
	// var_in_ref_array--> var_in_ref_array '[' opr_elem ']'
	// opr_elem_seq--> opr_elem ';'
	// opr_elem_seq--> opr_elem_seq opr_elem ';'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_OPR_ELEM_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1302-opr_elem->VAR_REF 
	//parent:
	// type_specifier--> type_specifier '[' opr_elem ']'
	// opr_statement--> OPR_START STRING_LITERAL ',' opr_elem ';' ',' opr_elem ';' ',' opr_elem ';'
	// var_in_ref_array--> var_in_start VAR_REF '[' opr_elem ']'
	// var_in_ref_array--> var_in_ref_array '[' opr_elem ']'
	// opr_elem_seq--> opr_elem ';'
	// opr_elem_seq--> opr_elem_seq opr_elem ';'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_OPR_ELEM_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1303-opr_elem->constant 
	//parent:
	// type_specifier--> type_specifier '[' opr_elem ']'
	// opr_statement--> OPR_START STRING_LITERAL ',' opr_elem ';' ',' opr_elem ';' ',' opr_elem ';'
	// var_in_ref_array--> var_in_start VAR_REF '[' opr_elem ']'
	// var_in_ref_array--> var_in_ref_array '[' opr_elem ']'
	// opr_elem_seq--> opr_elem ';'
	// opr_elem_seq--> opr_elem_seq opr_elem ';'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_OPR_ELEM_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1304-opr_elem->var_in_ref 
	//parent:
	// type_specifier--> type_specifier '[' opr_elem ']'
	// opr_statement--> OPR_START STRING_LITERAL ',' opr_elem ';' ',' opr_elem ';' ',' opr_elem ';'
	// var_in_ref_array--> var_in_start VAR_REF '[' opr_elem ']'
	// var_in_ref_array--> var_in_ref_array '[' opr_elem ']'
	// opr_elem_seq--> opr_elem ';'
	// opr_elem_seq--> opr_elem_seq opr_elem ';'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_OPR_ELEM_5(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1305-opr_elem->label_ref 
	//parent:
	// type_specifier--> type_specifier '[' opr_elem ']'
	// opr_statement--> OPR_START STRING_LITERAL ',' opr_elem ';' ',' opr_elem ';' ',' opr_elem ';'
	// var_in_ref_array--> var_in_start VAR_REF '[' opr_elem ']'
	// var_in_ref_array--> var_in_ref_array '[' opr_elem ']'
	// opr_elem_seq--> opr_elem ';'
	// opr_elem_seq--> opr_elem_seq opr_elem ';'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_CONSTANT_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1401-constant->i_const 
	//parent:
	// opr_elem--> constant
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_CONSTANT_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1402-constant->f_const 
	//parent:
	// opr_elem--> constant
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_CONSTANT_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1403-constant->string 
	//parent:
	// opr_elem--> constant
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_CONSTANT_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1404-constant->const_list 
	//parent:
	// opr_elem--> constant
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_I_CONST_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1501-i_const->I_CONST_ID I_CONSTANT 
	//parent:
	// constant--> i_const
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *I_CONST_ID=tdefs->m_tk_elems[0];
	//token_defs *I_CONSTANT=tdefs->m_tk_elems[1];
	//icode *I_CONST_ID_ic=pcompi->ast_to_icode(I_CONST_ID);
	//icode *I_CONSTANT_ic=pcompi->ast_to_icode(I_CONSTANT);
	//a->merge_icode(I_CONST_ID_ic);
	//a->merge_icode(I_CONSTANT_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_F_CONST_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1601-f_const->F_CONST_ID F_CONSTANT 
	//parent:
	// constant--> f_const
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *F_CONST_ID=tdefs->m_tk_elems[0];
	//token_defs *F_CONSTANT=tdefs->m_tk_elems[1];
	//icode *F_CONST_ID_ic=pcompi->ast_to_icode(F_CONST_ID);
	//icode *F_CONSTANT_ic=pcompi->ast_to_icode(F_CONSTANT);
	//a->merge_icode(F_CONST_ID_ic);
	//a->merge_icode(F_CONSTANT_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_F_CONST_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1602-f_const->F_CONST_ID I_CONSTANT 
	//parent:
	// constant--> f_const
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *F_CONST_ID=tdefs->m_tk_elems[0];
	//token_defs *I_CONSTANT=tdefs->m_tk_elems[1];
	//icode *F_CONST_ID_ic=pcompi->ast_to_icode(F_CONST_ID);
	//icode *I_CONSTANT_ic=pcompi->ast_to_icode(I_CONSTANT);
	//a->merge_icode(F_CONST_ID_ic);
	//a->merge_icode(I_CONSTANT_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_STRING_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1701-string->STRING_ID STRING_LITERAL 
	//parent:
	// constant--> string
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *STRING_ID=tdefs->m_tk_elems[0];
	//token_defs *STRING_LITERAL=tdefs->m_tk_elems[1];
	//icode *STRING_ID_ic=pcompi->ast_to_icode(STRING_ID);
	//icode *STRING_LITERAL_ic=pcompi->ast_to_icode(STRING_LITERAL);
	//a->merge_icode(STRING_ID_ic);
	//a->merge_icode(STRING_LITERAL_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_VAR_IN_REF_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1801-var_in_ref->var_in_ref_ptr 
	//parent:
	// opr_elem--> var_in_ref
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_VAR_IN_REF_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1802-var_in_ref->var_in_ref_array 
	//parent:
	// opr_elem--> var_in_ref
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_VAR_IN_REF_PTR_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1901-var_in_ref_ptr->var_in_start VAR_REF '*' I_CONSTANT 
	//parent:
	// var_in_ref--> var_in_ref_ptr
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *var_in_start=tdefs->m_tk_elems[0];
	//token_defs *VAR_REF=tdefs->m_tk_elems[1];
	//token_defs *'*'=tdefs->m_tk_elems[2];
	//token_defs *I_CONSTANT=tdefs->m_tk_elems[3];
	//icode *var_in_start_ic=pcompi->ast_to_icode(var_in_start);
	//icode *VAR_REF_ic=pcompi->ast_to_icode(VAR_REF);
	//icode *'*'_ic=pcompi->ast_to_icode('*');
	//icode *I_CONSTANT_ic=pcompi->ast_to_icode(I_CONSTANT);
	//a->merge_icode(var_in_start_ic);
	//a->merge_icode(VAR_REF_ic);
	//a->merge_icode('*'_ic);
	//a->merge_icode(I_CONSTANT_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_VAR_IN_REF_ARRAY_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1a01-var_in_ref_array->var_in_start VAR_REF '[' opr_elem ']' 
	//parent:
	// var_in_ref--> var_in_ref_array
	// var_in_ref_array--> var_in_ref_array '[' opr_elem ']'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *var_in_start=tdefs->m_tk_elems[0];
	//token_defs *VAR_REF=tdefs->m_tk_elems[1];
	//token_defs *'['=tdefs->m_tk_elems[2];
	//token_defs *opr_elem=tdefs->m_tk_elems[3];
	//token_defs *']'=tdefs->m_tk_elems[4];
	//icode *var_in_start_ic=pcompi->ast_to_icode(var_in_start);
	//icode *VAR_REF_ic=pcompi->ast_to_icode(VAR_REF);
	//icode *'['_ic=pcompi->ast_to_icode('[');
	//icode *opr_elem_ic=pcompi->ast_to_icode(opr_elem);
	//icode *']'_ic=pcompi->ast_to_icode(']');
	//a->merge_icode(var_in_start_ic);
	//a->merge_icode(VAR_REF_ic);
	//a->merge_icode('['_ic);
	//a->merge_icode(opr_elem_ic);
	//a->merge_icode(']'_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_VAR_IN_REF_ARRAY_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1a02-var_in_ref_array->var_in_ref_array '[' opr_elem ']' 
	//parent:
	// var_in_ref--> var_in_ref_array
	// var_in_ref_array--> var_in_ref_array '[' opr_elem ']'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *var_in_ref_array=tdefs->m_tk_elems[0];
	//token_defs *'['=tdefs->m_tk_elems[1];
	//token_defs *opr_elem=tdefs->m_tk_elems[2];
	//token_defs *']'=tdefs->m_tk_elems[3];
	//icode *var_in_ref_array_ic=pcompi->ast_to_icode(var_in_ref_array);
	//icode *'['_ic=pcompi->ast_to_icode('[');
	//icode *opr_elem_ic=pcompi->ast_to_icode(opr_elem);
	//icode *']'_ic=pcompi->ast_to_icode(']');
	//a->merge_icode(var_in_ref_array_ic);
	//a->merge_icode('['_ic);
	//a->merge_icode(opr_elem_ic);
	//a->merge_icode(']'_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_CONST_LIST_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1b01-const_list->CONST_LIST_ID '[' opr_elem_seq ']' 
	//parent:
	// constant--> const_list
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *CONST_LIST_ID=tdefs->m_tk_elems[0];
	//token_defs *'['=tdefs->m_tk_elems[1];
	//token_defs *opr_elem_seq=tdefs->m_tk_elems[2];
	//token_defs *']'=tdefs->m_tk_elems[3];
	//icode *CONST_LIST_ID_ic=pcompi->ast_to_icode(CONST_LIST_ID);
	//icode *'['_ic=pcompi->ast_to_icode('[');
	//icode *opr_elem_seq_ic=pcompi->ast_to_icode(opr_elem_seq);
	//icode *']'_ic=pcompi->ast_to_icode(']');
	//a->merge_icode(CONST_LIST_ID_ic);
	//a->merge_icode('['_ic);
	//a->merge_icode(opr_elem_seq_ic);
	//a->merge_icode(']'_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_VAR_IN_START_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1c01-var_in_start->VAR_IN 
	//parent:
	// var_in_ref_ptr--> var_in_start VAR_REF '*' I_CONSTANT
	// var_in_ref_array--> var_in_start VAR_REF '[' opr_elem ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_VAR_IN_START_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1c02-var_in_start->VAR_IN_TMP 
	//parent:
	// var_in_ref_ptr--> var_in_start VAR_REF '*' I_CONSTANT
	// var_in_ref_array--> var_in_start VAR_REF '[' opr_elem ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_CALL_STATEMENT_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1d01-call_statement->CALL_START VAR_REF ';' opr_elem_seq CALL_END VAR_REF ';' 
	//parent:
	// statement--> call_statement
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *CALL_START=tdefs->m_tk_elems[0];
	//token_defs *VAR_REF=tdefs->m_tk_elems[1];
	//token_defs *';'=tdefs->m_tk_elems[2];
	//token_defs *opr_elem_seq=tdefs->m_tk_elems[3];
	//token_defs *CALL_END=tdefs->m_tk_elems[4];
	//token_defs *VAR_REF=tdefs->m_tk_elems[5];
	//token_defs *';'=tdefs->m_tk_elems[6];
	//icode *CALL_START_ic=pcompi->ast_to_icode(CALL_START);
	//icode *VAR_REF_ic=pcompi->ast_to_icode(VAR_REF);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//icode *opr_elem_seq_ic=pcompi->ast_to_icode(opr_elem_seq);
	//icode *CALL_END_ic=pcompi->ast_to_icode(CALL_END);
	//icode *VAR_REF_ic=pcompi->ast_to_icode(VAR_REF);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//a->merge_icode(CALL_START_ic);
	//a->merge_icode(VAR_REF_ic);
	//a->merge_icode(';'_ic);
	//a->merge_icode(opr_elem_seq_ic);
	//a->merge_icode(CALL_END_ic);
	//a->merge_icode(VAR_REF_ic);
	//a->merge_icode(';'_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_CALL_STATEMENT_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1d02-call_statement->CALL_START VAR_REF ';' CALL_END VAR_REF ';' 
	//parent:
	// statement--> call_statement
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *CALL_START=tdefs->m_tk_elems[0];
	//token_defs *VAR_REF=tdefs->m_tk_elems[1];
	//token_defs *';'=tdefs->m_tk_elems[2];
	//token_defs *CALL_END=tdefs->m_tk_elems[3];
	//token_defs *VAR_REF=tdefs->m_tk_elems[4];
	//token_defs *';'=tdefs->m_tk_elems[5];
	//icode *CALL_START_ic=pcompi->ast_to_icode(CALL_START);
	//icode *VAR_REF_ic=pcompi->ast_to_icode(VAR_REF);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//icode *CALL_END_ic=pcompi->ast_to_icode(CALL_END);
	//icode *VAR_REF_ic=pcompi->ast_to_icode(VAR_REF);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//a->merge_icode(CALL_START_ic);
	//a->merge_icode(VAR_REF_ic);
	//a->merge_icode(';'_ic);
	//a->merge_icode(CALL_END_ic);
	//a->merge_icode(VAR_REF_ic);
	//a->merge_icode(';'_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_OPR_ELEM_SEQ_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1e01-opr_elem_seq->opr_elem ';' 
	//parent:
	// const_list--> CONST_LIST_ID '[' opr_elem_seq ']'
	// call_statement--> CALL_START VAR_REF ';' opr_elem_seq CALL_END VAR_REF ';'
	// opr_elem_seq--> opr_elem_seq opr_elem ';'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *opr_elem=tdefs->m_tk_elems[0];
	//token_defs *';'=tdefs->m_tk_elems[1];
	//icode *opr_elem_ic=pcompi->ast_to_icode(opr_elem);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//a->merge_icode(opr_elem_ic);
	//a->merge_icode(';'_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_OPR_ELEM_SEQ_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1e02-opr_elem_seq->opr_elem_seq opr_elem ';' 
	//parent:
	// const_list--> CONST_LIST_ID '[' opr_elem_seq ']'
	// call_statement--> CALL_START VAR_REF ';' opr_elem_seq CALL_END VAR_REF ';'
	// opr_elem_seq--> opr_elem_seq opr_elem ';'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *opr_elem_seq=tdefs->m_tk_elems[0];
	//token_defs *opr_elem=tdefs->m_tk_elems[1];
	//token_defs *';'=tdefs->m_tk_elems[2];
	//icode *opr_elem_seq_ic=pcompi->ast_to_icode(opr_elem_seq);
	//icode *opr_elem_ic=pcompi->ast_to_icode(opr_elem);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//a->merge_icode(opr_elem_seq_ic);
	//a->merge_icode(opr_elem_ic);
	//a->merge_icode(';'_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_LABEL_DEF_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1f01-label_def->LABEL_START I_CONSTANT ';' 
	//parent:
	// statement--> label_def
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *LABEL_START=tdefs->m_tk_elems[0];
	//token_defs *I_CONSTANT=tdefs->m_tk_elems[1];
	//token_defs *';'=tdefs->m_tk_elems[2];
	//icode *LABEL_START_ic=pcompi->ast_to_icode(LABEL_START);
	//icode *I_CONSTANT_ic=pcompi->ast_to_icode(I_CONSTANT);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//a->merge_icode(LABEL_START_ic);
	//a->merge_icode(I_CONSTANT_ic);
	//a->merge_icode(';'_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_LABEL_REF_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x2001-label_ref->LABEL_REF I_CONSTANT 
	//parent:
	// opr_elem--> label_ref
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *LABEL_REF=tdefs->m_tk_elems[0];
	//token_defs *I_CONSTANT=tdefs->m_tk_elems[1];
	//icode *LABEL_REF_ic=pcompi->ast_to_icode(LABEL_REF);
	//icode *I_CONSTANT_ic=pcompi->ast_to_icode(I_CONSTANT);
	//a->merge_icode(LABEL_REF_ic);
	//a->merge_icode(I_CONSTANT_ic);
	assert(0);
	return a;
}
class icode *  func_IAN_INLINE_ASM_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x2101-inline_asm->INLINE_ASM STRING_LITERAL ';' 
	//parent:
	// statement--> inline_asm
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *INLINE_ASM=tdefs->m_tk_elems[0];
	//token_defs *STRING_LITERAL=tdefs->m_tk_elems[1];
	//token_defs *';'=tdefs->m_tk_elems[2];
	//icode *INLINE_ASM_ic=pcompi->ast_to_icode(INLINE_ASM);
	//icode *STRING_LITERAL_ic=pcompi->ast_to_icode(STRING_LITERAL);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//a->merge_icode(INLINE_ASM_ic);
	//a->merge_icode(STRING_LITERAL_ic);
	//a->merge_icode(';'_ic);
	assert(0);
	return a;
}
 class icode *func_token_END(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//END
	//parent:
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_EOL(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//EOL
	//parent:
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_BLOCKS(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//BLOCKS
	//parent:
	// file--> BLOCKS translation_unit BLOCKE
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_BLOCKE(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//BLOCKE
	//parent:
	// file--> BLOCKS translation_unit BLOCKE
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_SCOPES(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//SCOPES
	//parent:
	// compound_statement--> SCOPES SCOPEE
	// compound_statement--> SCOPES block_item_list SCOPEE
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_SCOPEE(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//SCOPEE
	//parent:
	// compound_statement--> SCOPES SCOPEE
	// compound_statement--> SCOPES block_item_list SCOPEE
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_DEF_VAR(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//DEF_VAR
	//parent:
	// def_var_start--> DEF_VAR
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_DEF_VAR_TMP(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//DEF_VAR_TMP
	//parent:
	// def_var_start--> DEF_VAR_TMP
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_VAR_IN(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//VAR_IN
	//parent:
	// var_in_start--> VAR_IN
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_VAR_IN_TMP(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//VAR_IN_TMP
	//parent:
	// var_in_start--> VAR_IN_TMP
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_DEF_ARG(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//DEF_ARG
	//parent:
	// def_arg--> DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_arg--> DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_VOID(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//VOID
	//parent:
	// type_specifier_basic--> VOID
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_U1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//U1
	//parent:
	// type_specifier_basic--> U1
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_U8(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//U8
	//parent:
	// type_specifier_basic--> U8
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_U16(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//U16
	//parent:
	// type_specifier_basic--> U16
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_U24(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//U24
	//parent:
	// type_specifier_basic--> U24
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_U32(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//U32
	//parent:
	// type_specifier_basic--> U32
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_U64(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//U64
	//parent:
	// type_specifier_basic--> U64
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_F16(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//F16
	//parent:
	// type_specifier_basic--> F16
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_F32(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//F32
	//parent:
	// type_specifier_basic--> F32
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_F64(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//F64
	//parent:
	// type_specifier_basic--> F64
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_I1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//I1
	//parent:
	// type_specifier_basic--> I1
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_I8(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//I8
	//parent:
	// type_specifier_basic--> I8
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_I16(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//I16
	//parent:
	// type_specifier_basic--> I16
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_I24(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//I24
	//parent:
	// type_specifier_basic--> I24
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_I32(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//I32
	//parent:
	// type_specifier_basic--> I32
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_I64(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//I64
	//parent:
	// type_specifier_basic--> I64
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_U_NUM(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//U_NUM
	//parent:
	// type_specifier_basic--> U_NUM
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_LABEL_START(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//LABEL_START
	//parent:
	// label_def--> LABEL_START I_CONSTANT ';'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_LABEL_REF(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//LABEL_REF
	//parent:
	// label_ref--> LABEL_REF I_CONSTANT
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_VAR_REF(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//VAR_REF
	//parent:
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg FUNC_END VAR_REF ';'
	// opr_elem--> VAR_REF
	// var_in_ref_ptr--> var_in_start VAR_REF '*' I_CONSTANT
	// var_in_ref_array--> var_in_start VAR_REF '[' opr_elem ']'
	// call_statement--> CALL_START VAR_REF ';' opr_elem_seq CALL_END VAR_REF ';'
	// call_statement--> CALL_START VAR_REF ';' CALL_END VAR_REF ';'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_VAR_NULL(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//VAR_NULL
	//parent:
	// opr_elem--> VAR_NULL
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_FUNC_START(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//FUNC_START
	//parent:
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg FUNC_END VAR_REF ';'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_FUNC_END(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//FUNC_END
	//parent:
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg FUNC_END VAR_REF ';'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_FUNC_RETURN(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//FUNC_RETURN
	//parent:
	// statement--> FUNC_RETURN
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_CALL_START(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//CALL_START
	//parent:
	// call_statement--> CALL_START VAR_REF ';' opr_elem_seq CALL_END VAR_REF ';'
	// call_statement--> CALL_START VAR_REF ';' CALL_END VAR_REF ';'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_CALL_END(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//CALL_END
	//parent:
	// call_statement--> CALL_START VAR_REF ';' opr_elem_seq CALL_END VAR_REF ';'
	// call_statement--> CALL_START VAR_REF ';' CALL_END VAR_REF ';'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_RET_TYPE(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//RET_TYPE
	//parent:
	// ret_type--> RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// ret_type--> RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_IDENTIFIER(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//IDENTIFIER
	//parent:
	// func_attrib1--> IDENTIFIER '(' STRING_LITERAL ')'
	// func_attrib1--> IDENTIFIER '(' I_CONSTANT ')'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_VAR_NAME_IDENTIFIER(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//VAR_NAME_IDENTIFIER
	//parent:
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg FUNC_END VAR_REF ';'
	// ret_type--> RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// ret_type--> RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
	// def_arg--> DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_arg--> DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
	// def_one_var--> def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_one_var--> def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_I_CONST_ID(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//I_CONST_ID
	//parent:
	// i_const--> I_CONST_ID I_CONSTANT
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_F_CONST_ID(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//F_CONST_ID
	//parent:
	// f_const--> F_CONST_ID F_CONSTANT
	// f_const--> F_CONST_ID I_CONSTANT
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_STRING_ID(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//STRING_ID
	//parent:
	// string--> STRING_ID STRING_LITERAL
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_CONST_LIST_ID(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//CONST_LIST_ID
	//parent:
	// const_list--> CONST_LIST_ID '[' opr_elem_seq ']'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_I_CONSTANT(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//I_CONSTANT
	//parent:
	// func_attrib1--> IDENTIFIER '(' I_CONSTANT ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
	// i_const--> I_CONST_ID I_CONSTANT
	// f_const--> F_CONST_ID I_CONSTANT
	// var_in_ref_ptr--> var_in_start VAR_REF '*' I_CONSTANT
	// label_def--> LABEL_START I_CONSTANT ';'
	// label_ref--> LABEL_REF I_CONSTANT
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_F_CONSTANT(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//F_CONSTANT
	//parent:
	// f_const--> F_CONST_ID F_CONSTANT
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_STRING_LITERAL(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//STRING_LITERAL
	//parent:
	// func_attrib1--> IDENTIFIER '(' STRING_LITERAL ')'
	// opr_statement--> OPR_START STRING_LITERAL ',' opr_elem ';' ',' opr_elem ';' ',' opr_elem ';'
	// string--> STRING_ID STRING_LITERAL
	// inline_asm--> INLINE_ASM STRING_LITERAL ';'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_OPR_START(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//OPR_START
	//parent:
	// opr_statement--> OPR_START STRING_LITERAL ',' opr_elem ';' ',' opr_elem ';' ',' opr_elem ';'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_INLINE_ASM(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//INLINE_ASM
	//parent:
	// inline_asm--> INLINE_ASM STRING_LITERAL ';'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}

}//namespace NS_IR2ICODE
