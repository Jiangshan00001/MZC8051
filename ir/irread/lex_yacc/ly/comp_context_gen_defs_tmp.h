#ifndef AST_TO_ICODE_GEN_DEF_H
#define AST_TO_ICODE_GEN_DEF_H
namespace NS_IR2ICODE{

enum E_AST_TO_ICODE_GEN_DEF{
IAN_FILE_1=0x1, //file->/*empty*/ 
IAN_FILE_2=0x2, //file->translation_unit 
IAN_FILE_3=0x3, //file->BLOCKS translation_unit BLOCKE 
IAN_TRANSLATION_UNIT_1=0x101, //translation_unit->external_declaration 
IAN_TRANSLATION_UNIT_2=0x102, //translation_unit->translation_unit external_declaration 
IAN_EXTERNAL_DECLARATION_1=0x201, //external_declaration->block_item 
IAN_EXTERNAL_DECLARATION_2=0x202, //external_declaration->function_definition 
IAN_FUNCTION_DEFINITION_1=0x301, //function_definition->FUNC_START VAR_NAME_IDENTIFIER ';' ret_type compound_statement FUNC_END VAR_REF ';' 
IAN_FUNCTION_DEFINITION_2=0x302, //function_definition->FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type compound_statement FUNC_END VAR_REF ';' 
IAN_FUNCTION_DEFINITION_3=0x303, //function_definition->FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';' 
IAN_FUNCTION_DEFINITION_4=0x304, //function_definition->FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';' 
IAN_FUNCTION_DEFINITION_5=0x305, //function_definition->FUNC_START VAR_NAME_IDENTIFIER ';' ret_type FUNC_END VAR_REF ';' 
IAN_FUNCTION_DEFINITION_6=0x306, //function_definition->FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type FUNC_END VAR_REF ';' 
IAN_FUNCTION_DEFINITION_7=0x307, //function_definition->FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg FUNC_END VAR_REF ';' 
IAN_FUNCTION_DEFINITION_8=0x308, //function_definition->FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg FUNC_END VAR_REF ';' 
IAN_FUNC_ATTRIB_1=0x401, //func_attrib->func_attrib1 
IAN_FUNC_ATTRIB_2=0x402, //func_attrib->func_attrib ',' func_attrib1 
IAN_FUNC_ATTRIB1_1=0x501, //func_attrib1->IDENTIFIER '(' STRING_LITERAL ')' 
IAN_FUNC_ATTRIB1_2=0x502, //func_attrib1->IDENTIFIER '(' I_CONSTANT ')' 
IAN_DECLARATIONS_1=0x601, //declarations->def_one_var 
IAN_DECLARATIONS_2=0x602, //declarations->declarations def_one_var 
IAN_FUNCTION_ARG_1=0x701, //function_arg->def_arg 
IAN_FUNCTION_ARG_2=0x702, //function_arg->function_arg def_arg 
IAN_RET_TYPE_1=0x801, //ret_type->RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ';' 
IAN_RET_TYPE_2=0x802, //ret_type->RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';' 
IAN_DEF_ARG_1=0x901, //def_arg->DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ';' 
IAN_DEF_ARG_2=0x902, //def_arg->DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';' 
IAN_DEF_ONE_VAR_1=0xa01, //def_one_var->def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ';' 
IAN_DEF_ONE_VAR_2=0xa02, //def_one_var->def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';' 
IAN_DEF_VAR_START_1=0xb01, //def_var_start->DEF_VAR 
IAN_DEF_VAR_START_2=0xb02, //def_var_start->DEF_VAR_TMP 
IAN_TYPE_SPECIFIER_1=0xc01, //type_specifier->type_specifier_basic 
IAN_TYPE_SPECIFIER_2=0xc02, //type_specifier->type_specifier_basic '(' declarations ')' 
IAN_TYPE_SPECIFIER_3=0xc03, //type_specifier->type_specifier_basic '(' '(' declarations ')' ')' 
IAN_TYPE_SPECIFIER_4=0xc04, //type_specifier->type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']' 
IAN_TYPE_SPECIFIER_5=0xc05, //type_specifier->type_specifier '[' type_specifier ']' 
IAN_TYPE_SPECIFIER_6=0xc06, //type_specifier->type_specifier '[' opr_elem ']' 
IAN_TYPE_SPECIFIER_BASIC_1=0xd01, //type_specifier_basic->VOID 
IAN_TYPE_SPECIFIER_BASIC_2=0xd02, //type_specifier_basic->U1 
IAN_TYPE_SPECIFIER_BASIC_3=0xd03, //type_specifier_basic->U8 
IAN_TYPE_SPECIFIER_BASIC_4=0xd04, //type_specifier_basic->U16 
IAN_TYPE_SPECIFIER_BASIC_5=0xd05, //type_specifier_basic->U24 
IAN_TYPE_SPECIFIER_BASIC_6=0xd06, //type_specifier_basic->U32 
IAN_TYPE_SPECIFIER_BASIC_7=0xd07, //type_specifier_basic->U64 
IAN_TYPE_SPECIFIER_BASIC_8=0xd08, //type_specifier_basic->F16 
IAN_TYPE_SPECIFIER_BASIC_9=0xd09, //type_specifier_basic->F32 
IAN_TYPE_SPECIFIER_BASIC_10=0xd0a, //type_specifier_basic->F64 
IAN_TYPE_SPECIFIER_BASIC_11=0xd0b, //type_specifier_basic->I1 
IAN_TYPE_SPECIFIER_BASIC_12=0xd0c, //type_specifier_basic->I8 
IAN_TYPE_SPECIFIER_BASIC_13=0xd0d, //type_specifier_basic->I16 
IAN_TYPE_SPECIFIER_BASIC_14=0xd0e, //type_specifier_basic->I24 
IAN_TYPE_SPECIFIER_BASIC_15=0xd0f, //type_specifier_basic->I32 
IAN_TYPE_SPECIFIER_BASIC_16=0xd10, //type_specifier_basic->I64 
IAN_TYPE_SPECIFIER_BASIC_17=0xd11, //type_specifier_basic->U_NUM 
IAN_COMPOUND_STATEMENT_1=0xe01, //compound_statement->SCOPES SCOPEE 
IAN_COMPOUND_STATEMENT_2=0xe02, //compound_statement->SCOPES block_item_list SCOPEE 
IAN_BLOCK_ITEM_LIST_1=0xf01, //block_item_list->block_item 
IAN_BLOCK_ITEM_LIST_2=0xf02, //block_item_list->block_item_list block_item 
IAN_BLOCK_ITEM_1=0x1001, //block_item->def_one_var 
IAN_BLOCK_ITEM_2=0x1002, //block_item->statement 
IAN_STATEMENT_1=0x1101, //statement->opr_statement 
IAN_STATEMENT_2=0x1102, //statement->call_statement 
IAN_STATEMENT_3=0x1103, //statement->FUNC_RETURN 
IAN_STATEMENT_4=0x1104, //statement->label_def 
IAN_STATEMENT_5=0x1105, //statement->inline_asm 
IAN_STATEMENT_6=0x1106, //statement->compound_statement 
IAN_OPR_STATEMENT_1=0x1201, //opr_statement->OPR_START STRING_LITERAL ',' opr_elem ';' ',' opr_elem ';' ',' opr_elem ';' 
IAN_OPR_ELEM_1=0x1301, //opr_elem->VAR_NULL 
IAN_OPR_ELEM_2=0x1302, //opr_elem->VAR_REF 
IAN_OPR_ELEM_3=0x1303, //opr_elem->constant 
IAN_OPR_ELEM_4=0x1304, //opr_elem->var_in_ref 
IAN_OPR_ELEM_5=0x1305, //opr_elem->label_ref 
IAN_CONSTANT_1=0x1401, //constant->i_const 
IAN_CONSTANT_2=0x1402, //constant->f_const 
IAN_CONSTANT_3=0x1403, //constant->string 
IAN_CONSTANT_4=0x1404, //constant->const_list 
IAN_I_CONST_1=0x1501, //i_const->I_CONST_ID I_CONSTANT 
IAN_F_CONST_1=0x1601, //f_const->F_CONST_ID F_CONSTANT 
IAN_F_CONST_2=0x1602, //f_const->F_CONST_ID I_CONSTANT 
IAN_STRING_1=0x1701, //string->STRING_ID STRING_LITERAL 
IAN_VAR_IN_REF_1=0x1801, //var_in_ref->var_in_ref_ptr 
IAN_VAR_IN_REF_2=0x1802, //var_in_ref->var_in_ref_array 
IAN_VAR_IN_REF_PTR_1=0x1901, //var_in_ref_ptr->var_in_start VAR_REF '*' I_CONSTANT 
IAN_VAR_IN_REF_ARRAY_1=0x1a01, //var_in_ref_array->var_in_start VAR_REF '[' opr_elem ']' 
IAN_VAR_IN_REF_ARRAY_2=0x1a02, //var_in_ref_array->var_in_ref_array '[' opr_elem ']' 
IAN_CONST_LIST_1=0x1b01, //const_list->CONST_LIST_ID '[' opr_elem_seq ']' 
IAN_VAR_IN_START_1=0x1c01, //var_in_start->VAR_IN 
IAN_VAR_IN_START_2=0x1c02, //var_in_start->VAR_IN_TMP 
IAN_CALL_STATEMENT_1=0x1d01, //call_statement->CALL_START VAR_REF ';' opr_elem_seq CALL_END VAR_REF ';' 
IAN_CALL_STATEMENT_2=0x1d02, //call_statement->CALL_START VAR_REF ';' CALL_END VAR_REF ';' 
IAN_OPR_ELEM_SEQ_1=0x1e01, //opr_elem_seq->opr_elem ';' 
IAN_OPR_ELEM_SEQ_2=0x1e02, //opr_elem_seq->opr_elem_seq opr_elem ';' 
IAN_LABEL_DEF_1=0x1f01, //label_def->LABEL_START I_CONSTANT ';' 
IAN_LABEL_REF_1=0x2001, //label_ref->LABEL_REF I_CONSTANT 
IAN_INLINE_ASM_1=0x2101, //inline_asm->INLINE_ASM STRING_LITERAL ';' 
};

class icode *  func_IAN_FILE_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_FILE_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_FILE_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_TRANSLATION_UNIT_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_TRANSLATION_UNIT_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_EXTERNAL_DECLARATION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_EXTERNAL_DECLARATION_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_FUNCTION_DEFINITION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_FUNCTION_DEFINITION_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_FUNCTION_DEFINITION_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_FUNCTION_DEFINITION_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_FUNCTION_DEFINITION_5(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_FUNCTION_DEFINITION_6(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_FUNCTION_DEFINITION_7(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_FUNCTION_DEFINITION_8(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_FUNC_ATTRIB_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_FUNC_ATTRIB_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_FUNC_ATTRIB1_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_FUNC_ATTRIB1_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_DECLARATIONS_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_DECLARATIONS_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_FUNCTION_ARG_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_FUNCTION_ARG_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_RET_TYPE_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_RET_TYPE_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_DEF_ARG_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_DEF_ARG_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_DEF_ONE_VAR_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_DEF_ONE_VAR_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_DEF_VAR_START_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_DEF_VAR_START_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_TYPE_SPECIFIER_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_TYPE_SPECIFIER_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_TYPE_SPECIFIER_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_TYPE_SPECIFIER_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_TYPE_SPECIFIER_5(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_TYPE_SPECIFIER_6(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_5(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_6(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_7(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_8(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_9(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_10(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_11(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_12(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_13(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_14(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_15(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_16(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_17(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_COMPOUND_STATEMENT_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_COMPOUND_STATEMENT_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_BLOCK_ITEM_LIST_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_BLOCK_ITEM_LIST_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_BLOCK_ITEM_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_BLOCK_ITEM_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_STATEMENT_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_STATEMENT_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_STATEMENT_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_STATEMENT_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_STATEMENT_5(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_STATEMENT_6(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_OPR_STATEMENT_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_OPR_ELEM_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_OPR_ELEM_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_OPR_ELEM_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_OPR_ELEM_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_OPR_ELEM_5(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_CONSTANT_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_CONSTANT_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_CONSTANT_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_CONSTANT_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_I_CONST_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_F_CONST_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_F_CONST_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_STRING_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_VAR_IN_REF_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_VAR_IN_REF_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_VAR_IN_REF_PTR_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_VAR_IN_REF_ARRAY_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_VAR_IN_REF_ARRAY_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_CONST_LIST_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_VAR_IN_START_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_VAR_IN_START_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_CALL_STATEMENT_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_CALL_STATEMENT_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_OPR_ELEM_SEQ_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_OPR_ELEM_SEQ_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_LABEL_DEF_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_LABEL_REF_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
class icode *  func_IAN_INLINE_ASM_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
//ast func cout:95
 class icode *func_token_END(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_EOL(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_BLOCKS(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_BLOCKE(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_SCOPES(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_SCOPEE(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_DEF_VAR(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_DEF_VAR_TMP(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_VAR_IN(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_VAR_IN_TMP(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_DEF_ARG(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_VOID(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_U1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_U8(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_U16(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_U24(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_U32(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_U64(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_F16(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_F32(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_F64(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_I1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_I8(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_I16(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_I24(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_I32(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_I64(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_U_NUM(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_LABEL_START(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_LABEL_REF(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_VAR_REF(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_VAR_NULL(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_FUNC_START(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_FUNC_END(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_FUNC_RETURN(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_CALL_START(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_CALL_END(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_RET_TYPE(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_IDENTIFIER(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_VAR_NAME_IDENTIFIER(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_I_CONST_ID(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_F_CONST_ID(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_STRING_ID(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_CONST_LIST_ID(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_I_CONSTANT(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_F_CONSTANT(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_STRING_LITERAL(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_OPR_START(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
 class icode *func_token_INLINE_ASM(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic);
//elem func cout:49


}//namespace NS_IR2ICODE
#endif
