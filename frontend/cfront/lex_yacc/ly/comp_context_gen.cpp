#include <assert.h>
#include "comp_context.h"
#include "parser.h"
#include "token_defs.h"
#include "icode.h"
#include "comp_context_gen_defs.h"

namespace NS_C2IR{

icode * comp_context::ast_to_icode_elem(token_defs* tdefs, bool need_result_icode, icode *result_ic)
{
switch(tdefs->m_token_type)
{
case Parser::token::IDENTIFIER:
{
 icode *a= func_token_IDENTIFIER(this, tdefs, need_result_icode, result_ic);
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
case Parser::token::FUNC_NAME:
{
 icode *a= func_token_FUNC_NAME(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::SIZEOF:
{
 icode *a= func_token_SIZEOF(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::PTR_OP:
{
 icode *a= func_token_PTR_OP(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::INC_OP:
{
 icode *a= func_token_INC_OP(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::DEC_OP:
{
 icode *a= func_token_DEC_OP(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::LEFT_OP:
{
 icode *a= func_token_LEFT_OP(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::RIGHT_OP:
{
 icode *a= func_token_RIGHT_OP(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::ROTATE_RIGHT_OP:
{
 icode *a= func_token_ROTATE_RIGHT_OP(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::ROTATE_LEFT_OP:
{
 icode *a= func_token_ROTATE_LEFT_OP(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::LE_OP:
{
 icode *a= func_token_LE_OP(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::GE_OP:
{
 icode *a= func_token_GE_OP(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::EQ_OP:
{
 icode *a= func_token_EQ_OP(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::NE_OP:
{
 icode *a= func_token_NE_OP(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::AND_OP:
{
 icode *a= func_token_AND_OP(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::OR_OP:
{
 icode *a= func_token_OR_OP(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::MUL_ASSIGN:
{
 icode *a= func_token_MUL_ASSIGN(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::DIV_ASSIGN:
{
 icode *a= func_token_DIV_ASSIGN(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::MOD_ASSIGN:
{
 icode *a= func_token_MOD_ASSIGN(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::ADD_ASSIGN:
{
 icode *a= func_token_ADD_ASSIGN(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::SUB_ASSIGN:
{
 icode *a= func_token_SUB_ASSIGN(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::LEFT_ASSIGN:
{
 icode *a= func_token_LEFT_ASSIGN(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::RIGHT_ASSIGN:
{
 icode *a= func_token_RIGHT_ASSIGN(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::AND_ASSIGN:
{
 icode *a= func_token_AND_ASSIGN(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::XOR_ASSIGN:
{
 icode *a= func_token_XOR_ASSIGN(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::OR_ASSIGN:
{
 icode *a= func_token_OR_ASSIGN(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TYPEDEF_NAME:
{
 icode *a= func_token_TYPEDEF_NAME(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::ENUMERATION_CONSTANT:
{
 icode *a= func_token_ENUMERATION_CONSTANT(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::TYPEDEF:
{
 icode *a= func_token_TYPEDEF(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::EXTERN:
{
 icode *a= func_token_EXTERN(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::STATIC:
{
 icode *a= func_token_STATIC(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::AUTO:
{
 icode *a= func_token_AUTO(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::REGISTER:
{
 icode *a= func_token_REGISTER(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::INLINE:
{
 icode *a= func_token_INLINE(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::CONST:
{
 icode *a= func_token_CONST(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::RESTRICT:
{
 icode *a= func_token_RESTRICT(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::VOLATILE:
{
 icode *a= func_token_VOLATILE(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::BOOL:
{
 icode *a= func_token_BOOL(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::CHAR:
{
 icode *a= func_token_CHAR(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::SHORT:
{
 icode *a= func_token_SHORT(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::INT:
{
 icode *a= func_token_INT(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::LONG:
{
 icode *a= func_token_LONG(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::SIGNED:
{
 icode *a= func_token_SIGNED(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::UNSIGNED:
{
 icode *a= func_token_UNSIGNED(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::FLOAT:
{
 icode *a= func_token_FLOAT(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::DOUBLE:
{
 icode *a= func_token_DOUBLE(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::VOID:
{
 icode *a= func_token_VOID(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::COMPLEX:
{
 icode *a= func_token_COMPLEX(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::IMAGINARY:
{
 icode *a= func_token_IMAGINARY(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::STRUCT:
{
 icode *a= func_token_STRUCT(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::UNION:
{
 icode *a= func_token_UNION(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::ENUM:
{
 icode *a= func_token_ENUM(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::ELLIPSIS:
{
 icode *a= func_token_ELLIPSIS(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::CASE:
{
 icode *a= func_token_CASE(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::DEFAULT:
{
 icode *a= func_token_DEFAULT(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::IF:
{
 icode *a= func_token_IF(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::ELSE:
{
 icode *a= func_token_ELSE(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::SWITCH:
{
 icode *a= func_token_SWITCH(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::WHILE:
{
 icode *a= func_token_WHILE(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::DO:
{
 icode *a= func_token_DO(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::FOR:
{
 icode *a= func_token_FOR(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::GOTO:
{
 icode *a= func_token_GOTO(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::CONTINUE:
{
 icode *a= func_token_CONTINUE(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::BREAK:
{
 icode *a= func_token_BREAK(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::RETURN:
{
 icode *a= func_token_RETURN(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::ALIGNAS:
{
 icode *a= func_token_ALIGNAS(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::ALIGNOF:
{
 icode *a= func_token_ALIGNOF(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::ATOMIC:
{
 icode *a= func_token_ATOMIC(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::GENERIC:
{
 icode *a= func_token_GENERIC(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::NORETURN:
{
 icode *a= func_token_NORETURN(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::STATIC_ASSERT:
{
 icode *a= func_token_STATIC_ASSERT(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::THREAD_LOCAL:
{
 icode *a= func_token_THREAD_LOCAL(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::SFR:
{
 icode *a= func_token_SFR(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::BIT:
{
 icode *a= func_token_BIT(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::SBIT:
{
 icode *a= func_token_SBIT(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::SFR16:
{
 icode *a= func_token_SFR16(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::SFR32:
{
 icode *a= func_token_SFR32(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::INTERRUPT:
{
 icode *a= func_token_INTERRUPT(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::USING:
{
 icode *a= func_token_USING(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::REENTRANT:
{
 icode *a= func_token_REENTRANT(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::REGPARAMS:
{
 icode *a= func_token_REGPARAMS(this, tdefs, need_result_icode, result_ic);
return a;
}
break;
case Parser::token::STORAGE_SPEC_C51:
{
 icode *a= func_token_STORAGE_SPEC_C51(this, tdefs, need_result_icode, result_ic);
return a;
}
break;

}//switch end. case_cnt=85

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
case IAN_PRIMARY_EXPRESSION_1: //0x1-primary_expression->identifier 
{
	icode *a= func_IAN_PRIMARY_EXPRESSION_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_PRIMARY_EXPRESSION_2: //0x2-primary_expression->constant 
{
	icode *a= func_IAN_PRIMARY_EXPRESSION_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_PRIMARY_EXPRESSION_3: //0x3-primary_expression->string 
{
	icode *a= func_IAN_PRIMARY_EXPRESSION_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_PRIMARY_EXPRESSION_4: //0x4-primary_expression->'(' expression ')' 
{
	icode *a= func_IAN_PRIMARY_EXPRESSION_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_PRIMARY_EXPRESSION_5: //0x5-primary_expression->generic_selection 
{
	icode *a= func_IAN_PRIMARY_EXPRESSION_5(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_CONSTANT_1: //0x101-constant->I_CONSTANT 
{
	icode *a= func_IAN_CONSTANT_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_CONSTANT_2: //0x102-constant->F_CONSTANT 
{
	icode *a= func_IAN_CONSTANT_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_CONSTANT_3: //0x103-constant->ENUMERATION_CONSTANT 
{
	icode *a= func_IAN_CONSTANT_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ENUMERATION_CONSTANT_1: //0x201-enumeration_constant->identifier 
{
	icode *a= func_IAN_ENUMERATION_CONSTANT_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STRING_1: //0x301-string->STRING_LITERAL 
{
	icode *a= func_IAN_STRING_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STRING_2: //0x302-string->FUNC_NAME 
{
	icode *a= func_IAN_STRING_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_GENERIC_SELECTION_1: //0x401-generic_selection->GENERIC '(' assignment_expression ',' generic_assoc_list ')' 
{
	icode *a= func_IAN_GENERIC_SELECTION_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_GENERIC_ASSOC_LIST_1: //0x501-generic_assoc_list->generic_association 
{
	icode *a= func_IAN_GENERIC_ASSOC_LIST_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_GENERIC_ASSOC_LIST_2: //0x502-generic_assoc_list->generic_assoc_list ',' generic_association 
{
	icode *a= func_IAN_GENERIC_ASSOC_LIST_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_GENERIC_ASSOCIATION_1: //0x601-generic_association->type_name ':' assignment_expression 
{
	icode *a= func_IAN_GENERIC_ASSOCIATION_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_GENERIC_ASSOCIATION_2: //0x602-generic_association->DEFAULT ':' assignment_expression 
{
	icode *a= func_IAN_GENERIC_ASSOCIATION_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_POSTFIX_EXPRESSION_1: //0x701-postfix_expression->primary_expression 
{
	icode *a= func_IAN_POSTFIX_EXPRESSION_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_POSTFIX_EXPRESSION_2: //0x702-postfix_expression->postfix_expression '[' expression ']' 
{
	icode *a= func_IAN_POSTFIX_EXPRESSION_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_POSTFIX_EXPRESSION_3: //0x703-postfix_expression->postfix_expression '(' ')' 
{
	icode *a= func_IAN_POSTFIX_EXPRESSION_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_POSTFIX_EXPRESSION_4: //0x704-postfix_expression->postfix_expression '(' argument_expression_list ')' 
{
	icode *a= func_IAN_POSTFIX_EXPRESSION_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_POSTFIX_EXPRESSION_5: //0x705-postfix_expression->postfix_expression '.' identifier 
{
	icode *a= func_IAN_POSTFIX_EXPRESSION_5(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_POSTFIX_EXPRESSION_6: //0x706-postfix_expression->postfix_expression PTR_OP identifier 
{
	icode *a= func_IAN_POSTFIX_EXPRESSION_6(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_POSTFIX_EXPRESSION_7: //0x707-postfix_expression->postfix_expression INC_OP 
{
	icode *a= func_IAN_POSTFIX_EXPRESSION_7(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_POSTFIX_EXPRESSION_8: //0x708-postfix_expression->postfix_expression DEC_OP 
{
	icode *a= func_IAN_POSTFIX_EXPRESSION_8(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_POSTFIX_EXPRESSION_9: //0x709-postfix_expression->'(' type_name ')' '{' initializer_list '}' 
{
	icode *a= func_IAN_POSTFIX_EXPRESSION_9(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_POSTFIX_EXPRESSION_10: //0x70a-postfix_expression->'(' type_name ')' '{' initializer_list ',' '}' 
{
	icode *a= func_IAN_POSTFIX_EXPRESSION_10(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ARGUMENT_EXPRESSION_LIST_1: //0x801-argument_expression_list->assignment_expression 
{
	icode *a= func_IAN_ARGUMENT_EXPRESSION_LIST_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ARGUMENT_EXPRESSION_LIST_2: //0x802-argument_expression_list->argument_expression_list ',' assignment_expression 
{
	icode *a= func_IAN_ARGUMENT_EXPRESSION_LIST_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_UNARY_EXPRESSION_1: //0x901-unary_expression->postfix_expression 
{
	icode *a= func_IAN_UNARY_EXPRESSION_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_UNARY_EXPRESSION_2: //0x902-unary_expression->INC_OP unary_expression 
{
	icode *a= func_IAN_UNARY_EXPRESSION_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_UNARY_EXPRESSION_3: //0x903-unary_expression->DEC_OP unary_expression 
{
	icode *a= func_IAN_UNARY_EXPRESSION_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_UNARY_EXPRESSION_4: //0x904-unary_expression->unary_operator cast_expression 
{
	icode *a= func_IAN_UNARY_EXPRESSION_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_UNARY_EXPRESSION_5: //0x905-unary_expression->SIZEOF unary_expression 
{
	icode *a= func_IAN_UNARY_EXPRESSION_5(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_UNARY_EXPRESSION_6: //0x906-unary_expression->SIZEOF '(' type_name ')' 
{
	icode *a= func_IAN_UNARY_EXPRESSION_6(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_UNARY_EXPRESSION_7: //0x907-unary_expression->ALIGNOF '(' type_name ')' 
{
	icode *a= func_IAN_UNARY_EXPRESSION_7(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_UNARY_OPERATOR_1: //0xa01-unary_operator->'&' 
{
	icode *a= func_IAN_UNARY_OPERATOR_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_UNARY_OPERATOR_2: //0xa02-unary_operator->'*' 
{
	icode *a= func_IAN_UNARY_OPERATOR_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_UNARY_OPERATOR_3: //0xa03-unary_operator->'+' 
{
	icode *a= func_IAN_UNARY_OPERATOR_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_UNARY_OPERATOR_4: //0xa04-unary_operator->'-' 
{
	icode *a= func_IAN_UNARY_OPERATOR_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_UNARY_OPERATOR_5: //0xa05-unary_operator->'~' 
{
	icode *a= func_IAN_UNARY_OPERATOR_5(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_UNARY_OPERATOR_6: //0xa06-unary_operator->'!' 
{
	icode *a= func_IAN_UNARY_OPERATOR_6(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_CAST_EXPRESSION_1: //0xb01-cast_expression->unary_expression 
{
	icode *a= func_IAN_CAST_EXPRESSION_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_CAST_EXPRESSION_2: //0xb02-cast_expression->'(' type_name ')' cast_expression 
{
	icode *a= func_IAN_CAST_EXPRESSION_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_MULTIPLICATIVE_EXPRESSION_1: //0xc01-multiplicative_expression->cast_expression 
{
	icode *a= func_IAN_MULTIPLICATIVE_EXPRESSION_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_MULTIPLICATIVE_EXPRESSION_2: //0xc02-multiplicative_expression->multiplicative_expression '*' cast_expression 
{
	icode *a= func_IAN_MULTIPLICATIVE_EXPRESSION_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_MULTIPLICATIVE_EXPRESSION_3: //0xc03-multiplicative_expression->multiplicative_expression '/' cast_expression 
{
	icode *a= func_IAN_MULTIPLICATIVE_EXPRESSION_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_MULTIPLICATIVE_EXPRESSION_4: //0xc04-multiplicative_expression->multiplicative_expression '%' cast_expression 
{
	icode *a= func_IAN_MULTIPLICATIVE_EXPRESSION_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ADDITIVE_EXPRESSION_1: //0xd01-additive_expression->multiplicative_expression 
{
	icode *a= func_IAN_ADDITIVE_EXPRESSION_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ADDITIVE_EXPRESSION_2: //0xd02-additive_expression->additive_expression '+' multiplicative_expression 
{
	icode *a= func_IAN_ADDITIVE_EXPRESSION_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ADDITIVE_EXPRESSION_3: //0xd03-additive_expression->additive_expression '-' multiplicative_expression 
{
	icode *a= func_IAN_ADDITIVE_EXPRESSION_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_SHIFT_EXPRESSION_1: //0xe01-shift_expression->additive_expression 
{
	icode *a= func_IAN_SHIFT_EXPRESSION_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_SHIFT_EXPRESSION_2: //0xe02-shift_expression->shift_expression LEFT_OP additive_expression 
{
	icode *a= func_IAN_SHIFT_EXPRESSION_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_SHIFT_EXPRESSION_3: //0xe03-shift_expression->shift_expression RIGHT_OP additive_expression 
{
	icode *a= func_IAN_SHIFT_EXPRESSION_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_SHIFT_EXPRESSION_4: //0xe04-shift_expression->shift_expression ROTATE_LEFT_OP additive_expression 
{
	icode *a= func_IAN_SHIFT_EXPRESSION_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_SHIFT_EXPRESSION_5: //0xe05-shift_expression->shift_expression ROTATE_RIGHT_OP additive_expression 
{
	icode *a= func_IAN_SHIFT_EXPRESSION_5(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_RELATIONAL_EXPRESSION_1: //0xf01-relational_expression->shift_expression 
{
	icode *a= func_IAN_RELATIONAL_EXPRESSION_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_RELATIONAL_EXPRESSION_2: //0xf02-relational_expression->relational_expression '<' shift_expression 
{
	icode *a= func_IAN_RELATIONAL_EXPRESSION_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_RELATIONAL_EXPRESSION_3: //0xf03-relational_expression->relational_expression '>' shift_expression 
{
	icode *a= func_IAN_RELATIONAL_EXPRESSION_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_RELATIONAL_EXPRESSION_4: //0xf04-relational_expression->relational_expression LE_OP shift_expression 
{
	icode *a= func_IAN_RELATIONAL_EXPRESSION_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_RELATIONAL_EXPRESSION_5: //0xf05-relational_expression->relational_expression GE_OP shift_expression 
{
	icode *a= func_IAN_RELATIONAL_EXPRESSION_5(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_EQUALITY_EXPRESSION_1: //0x1001-equality_expression->relational_expression 
{
	icode *a= func_IAN_EQUALITY_EXPRESSION_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_EQUALITY_EXPRESSION_2: //0x1002-equality_expression->equality_expression EQ_OP relational_expression 
{
	icode *a= func_IAN_EQUALITY_EXPRESSION_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_EQUALITY_EXPRESSION_3: //0x1003-equality_expression->equality_expression NE_OP relational_expression 
{
	icode *a= func_IAN_EQUALITY_EXPRESSION_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_AND_EXPRESSION_1: //0x1101-and_expression->equality_expression 
{
	icode *a= func_IAN_AND_EXPRESSION_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_AND_EXPRESSION_2: //0x1102-and_expression->and_expression '&' equality_expression 
{
	icode *a= func_IAN_AND_EXPRESSION_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_EXCLUSIVE_OR_EXPRESSION_1: //0x1201-exclusive_or_expression->and_expression 
{
	icode *a= func_IAN_EXCLUSIVE_OR_EXPRESSION_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_EXCLUSIVE_OR_EXPRESSION_2: //0x1202-exclusive_or_expression->exclusive_or_expression '^' and_expression 
{
	icode *a= func_IAN_EXCLUSIVE_OR_EXPRESSION_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_INCLUSIVE_OR_EXPRESSION_1: //0x1301-inclusive_or_expression->exclusive_or_expression 
{
	icode *a= func_IAN_INCLUSIVE_OR_EXPRESSION_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_INCLUSIVE_OR_EXPRESSION_2: //0x1302-inclusive_or_expression->inclusive_or_expression '|' exclusive_or_expression 
{
	icode *a= func_IAN_INCLUSIVE_OR_EXPRESSION_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_LOGICAL_AND_EXPRESSION_1: //0x1401-logical_and_expression->inclusive_or_expression 
{
	icode *a= func_IAN_LOGICAL_AND_EXPRESSION_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_LOGICAL_AND_EXPRESSION_2: //0x1402-logical_and_expression->logical_and_expression AND_OP inclusive_or_expression 
{
	icode *a= func_IAN_LOGICAL_AND_EXPRESSION_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_LOGICAL_OR_EXPRESSION_1: //0x1501-logical_or_expression->logical_and_expression 
{
	icode *a= func_IAN_LOGICAL_OR_EXPRESSION_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_LOGICAL_OR_EXPRESSION_2: //0x1502-logical_or_expression->logical_or_expression OR_OP logical_and_expression 
{
	icode *a= func_IAN_LOGICAL_OR_EXPRESSION_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_CONDITIONAL_EXPRESSION_1: //0x1601-conditional_expression->logical_or_expression 
{
	icode *a= func_IAN_CONDITIONAL_EXPRESSION_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_CONDITIONAL_EXPRESSION_2: //0x1602-conditional_expression->logical_or_expression '?' expression ':' conditional_expression 
{
	icode *a= func_IAN_CONDITIONAL_EXPRESSION_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ASSIGNMENT_EXPRESSION_1: //0x1701-assignment_expression->conditional_expression 
{
	icode *a= func_IAN_ASSIGNMENT_EXPRESSION_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ASSIGNMENT_EXPRESSION_2: //0x1702-assignment_expression->unary_expression assignment_operator assignment_expression 
{
	icode *a= func_IAN_ASSIGNMENT_EXPRESSION_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ASSIGNMENT_OPERATOR_1: //0x1801-assignment_operator->'=' 
{
	icode *a= func_IAN_ASSIGNMENT_OPERATOR_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ASSIGNMENT_OPERATOR_2: //0x1802-assignment_operator->MUL_ASSIGN 
{
	icode *a= func_IAN_ASSIGNMENT_OPERATOR_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ASSIGNMENT_OPERATOR_3: //0x1803-assignment_operator->DIV_ASSIGN 
{
	icode *a= func_IAN_ASSIGNMENT_OPERATOR_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ASSIGNMENT_OPERATOR_4: //0x1804-assignment_operator->MOD_ASSIGN 
{
	icode *a= func_IAN_ASSIGNMENT_OPERATOR_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ASSIGNMENT_OPERATOR_5: //0x1805-assignment_operator->ADD_ASSIGN 
{
	icode *a= func_IAN_ASSIGNMENT_OPERATOR_5(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ASSIGNMENT_OPERATOR_6: //0x1806-assignment_operator->SUB_ASSIGN 
{
	icode *a= func_IAN_ASSIGNMENT_OPERATOR_6(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ASSIGNMENT_OPERATOR_7: //0x1807-assignment_operator->LEFT_ASSIGN 
{
	icode *a= func_IAN_ASSIGNMENT_OPERATOR_7(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ASSIGNMENT_OPERATOR_8: //0x1808-assignment_operator->RIGHT_ASSIGN 
{
	icode *a= func_IAN_ASSIGNMENT_OPERATOR_8(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ASSIGNMENT_OPERATOR_9: //0x1809-assignment_operator->AND_ASSIGN 
{
	icode *a= func_IAN_ASSIGNMENT_OPERATOR_9(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ASSIGNMENT_OPERATOR_10: //0x180a-assignment_operator->XOR_ASSIGN 
{
	icode *a= func_IAN_ASSIGNMENT_OPERATOR_10(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ASSIGNMENT_OPERATOR_11: //0x180b-assignment_operator->OR_ASSIGN 
{
	icode *a= func_IAN_ASSIGNMENT_OPERATOR_11(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_EXPRESSION_1: //0x1901-expression->assignment_expression 
{
	icode *a= func_IAN_EXPRESSION_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_EXPRESSION_2: //0x1902-expression->expression ',' assignment_expression 
{
	icode *a= func_IAN_EXPRESSION_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_CONSTANT_EXPRESSION_1: //0x1a01-constant_expression->conditional_expression 
{
	icode *a= func_IAN_CONSTANT_EXPRESSION_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DECLARATION_1: //0x1b01-declaration->declaration_specifiers ';' 
{
	icode *a= func_IAN_DECLARATION_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DECLARATION_2: //0x1b02-declaration->declaration_specifiers init_declarator_list ';' 
{
	icode *a= func_IAN_DECLARATION_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DECLARATION_3: //0x1b03-declaration->static_assert_declaration 
{
	icode *a= func_IAN_DECLARATION_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DECLARATION_SPECIFIERS_1: //0x1c01-declaration_specifiers->declaration_specifiers_ 
{
	icode *a= func_IAN_DECLARATION_SPECIFIERS_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DECLARATION_SPECIFIERS__1: //0x1d01-declaration_specifiers_->storage_class_specifier declaration_specifiers_ 
{
	icode *a= func_IAN_DECLARATION_SPECIFIERS__1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DECLARATION_SPECIFIERS__2: //0x1d02-declaration_specifiers_->storage_class_specifier 
{
	icode *a= func_IAN_DECLARATION_SPECIFIERS__2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DECLARATION_SPECIFIERS__3: //0x1d03-declaration_specifiers_->type_specifier declaration_specifiers_ 
{
	icode *a= func_IAN_DECLARATION_SPECIFIERS__3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DECLARATION_SPECIFIERS__4: //0x1d04-declaration_specifiers_->type_specifier 
{
	icode *a= func_IAN_DECLARATION_SPECIFIERS__4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DECLARATION_SPECIFIERS__5: //0x1d05-declaration_specifiers_->type_qualifier declaration_specifiers_ 
{
	icode *a= func_IAN_DECLARATION_SPECIFIERS__5(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DECLARATION_SPECIFIERS__6: //0x1d06-declaration_specifiers_->type_qualifier 
{
	icode *a= func_IAN_DECLARATION_SPECIFIERS__6(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DECLARATION_SPECIFIERS__7: //0x1d07-declaration_specifiers_->function_specifier declaration_specifiers_ 
{
	icode *a= func_IAN_DECLARATION_SPECIFIERS__7(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DECLARATION_SPECIFIERS__8: //0x1d08-declaration_specifiers_->function_specifier 
{
	icode *a= func_IAN_DECLARATION_SPECIFIERS__8(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DECLARATION_SPECIFIERS__9: //0x1d09-declaration_specifiers_->alignment_specifier declaration_specifiers_ 
{
	icode *a= func_IAN_DECLARATION_SPECIFIERS__9(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DECLARATION_SPECIFIERS__10: //0x1d0a-declaration_specifiers_->alignment_specifier 
{
	icode *a= func_IAN_DECLARATION_SPECIFIERS__10(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_INIT_DECLARATOR_LIST_1: //0x1e01-init_declarator_list->init_declarator 
{
	icode *a= func_IAN_INIT_DECLARATOR_LIST_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_INIT_DECLARATOR_LIST_2: //0x1e02-init_declarator_list->init_declarator_list ',' init_declarator 
{
	icode *a= func_IAN_INIT_DECLARATOR_LIST_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_INIT_DECLARATOR_1: //0x1f01-init_declarator->declarator '=' initializer 
{
	icode *a= func_IAN_INIT_DECLARATOR_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_INIT_DECLARATOR_2: //0x1f02-init_declarator->declarator 
{
	icode *a= func_IAN_INIT_DECLARATOR_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STORAGE_CLASS_SPECIFIER_1: //0x2001-storage_class_specifier->TYPEDEF 
{
	icode *a= func_IAN_STORAGE_CLASS_SPECIFIER_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STORAGE_CLASS_SPECIFIER_2: //0x2002-storage_class_specifier->EXTERN 
{
	icode *a= func_IAN_STORAGE_CLASS_SPECIFIER_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STORAGE_CLASS_SPECIFIER_3: //0x2003-storage_class_specifier->STATIC 
{
	icode *a= func_IAN_STORAGE_CLASS_SPECIFIER_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STORAGE_CLASS_SPECIFIER_4: //0x2004-storage_class_specifier->THREAD_LOCAL 
{
	icode *a= func_IAN_STORAGE_CLASS_SPECIFIER_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STORAGE_CLASS_SPECIFIER_5: //0x2005-storage_class_specifier->AUTO 
{
	icode *a= func_IAN_STORAGE_CLASS_SPECIFIER_5(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STORAGE_CLASS_SPECIFIER_6: //0x2006-storage_class_specifier->REGISTER 
{
	icode *a= func_IAN_STORAGE_CLASS_SPECIFIER_6(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STORAGE_CLASS_SPECIFIER_7: //0x2007-storage_class_specifier->STORAGE_SPEC_C51 
{
	icode *a= func_IAN_STORAGE_CLASS_SPECIFIER_7(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_1: //0x2101-type_specifier->VOID 
{
	icode *a= func_IAN_TYPE_SPECIFIER_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_2: //0x2102-type_specifier->CHAR 
{
	icode *a= func_IAN_TYPE_SPECIFIER_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_3: //0x2103-type_specifier->SHORT 
{
	icode *a= func_IAN_TYPE_SPECIFIER_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_4: //0x2104-type_specifier->INT 
{
	icode *a= func_IAN_TYPE_SPECIFIER_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_5: //0x2105-type_specifier->LONG 
{
	icode *a= func_IAN_TYPE_SPECIFIER_5(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_6: //0x2106-type_specifier->FLOAT 
{
	icode *a= func_IAN_TYPE_SPECIFIER_6(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_7: //0x2107-type_specifier->DOUBLE 
{
	icode *a= func_IAN_TYPE_SPECIFIER_7(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_8: //0x2108-type_specifier->SIGNED 
{
	icode *a= func_IAN_TYPE_SPECIFIER_8(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_9: //0x2109-type_specifier->UNSIGNED 
{
	icode *a= func_IAN_TYPE_SPECIFIER_9(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_10: //0x210a-type_specifier->BOOL 
{
	icode *a= func_IAN_TYPE_SPECIFIER_10(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_11: //0x210b-type_specifier->COMPLEX 
{
	icode *a= func_IAN_TYPE_SPECIFIER_11(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_12: //0x210c-type_specifier->IMAGINARY 
{
	icode *a= func_IAN_TYPE_SPECIFIER_12(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_13: //0x210d-type_specifier->atomic_type_specifier 
{
	icode *a= func_IAN_TYPE_SPECIFIER_13(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_14: //0x210e-type_specifier->struct_or_union_specifier 
{
	icode *a= func_IAN_TYPE_SPECIFIER_14(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_15: //0x210f-type_specifier->enum_specifier 
{
	icode *a= func_IAN_TYPE_SPECIFIER_15(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_16: //0x2110-type_specifier->TYPEDEF_NAME 
{
	icode *a= func_IAN_TYPE_SPECIFIER_16(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_17: //0x2111-type_specifier->SFR 
{
	icode *a= func_IAN_TYPE_SPECIFIER_17(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_18: //0x2112-type_specifier->BIT 
{
	icode *a= func_IAN_TYPE_SPECIFIER_18(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_19: //0x2113-type_specifier->SBIT 
{
	icode *a= func_IAN_TYPE_SPECIFIER_19(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_20: //0x2114-type_specifier->SFR16 
{
	icode *a= func_IAN_TYPE_SPECIFIER_20(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_SPECIFIER_21: //0x2115-type_specifier->SFR32 
{
	icode *a= func_IAN_TYPE_SPECIFIER_21(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STRUCT_OR_UNION_SPECIFIER_1: //0x2201-struct_or_union_specifier->struct_or_union '{' struct_declaration_list '}' 
{
	icode *a= func_IAN_STRUCT_OR_UNION_SPECIFIER_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STRUCT_OR_UNION_SPECIFIER_2: //0x2202-struct_or_union_specifier->struct_or_union identifier '{' struct_declaration_list '}' 
{
	icode *a= func_IAN_STRUCT_OR_UNION_SPECIFIER_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STRUCT_OR_UNION_SPECIFIER_3: //0x2203-struct_or_union_specifier->struct_or_union identifier 
{
	icode *a= func_IAN_STRUCT_OR_UNION_SPECIFIER_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STRUCT_OR_UNION_1: //0x2301-struct_or_union->STRUCT 
{
	icode *a= func_IAN_STRUCT_OR_UNION_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STRUCT_OR_UNION_2: //0x2302-struct_or_union->UNION 
{
	icode *a= func_IAN_STRUCT_OR_UNION_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STRUCT_DECLARATION_LIST_1: //0x2401-struct_declaration_list->struct_declaration 
{
	icode *a= func_IAN_STRUCT_DECLARATION_LIST_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STRUCT_DECLARATION_LIST_2: //0x2402-struct_declaration_list->struct_declaration_list struct_declaration 
{
	icode *a= func_IAN_STRUCT_DECLARATION_LIST_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STRUCT_DECLARATION_1: //0x2501-struct_declaration->specifier_qualifier_list ';' 
{
	icode *a= func_IAN_STRUCT_DECLARATION_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STRUCT_DECLARATION_2: //0x2502-struct_declaration->specifier_qualifier_list struct_declarator_list ';' 
{
	icode *a= func_IAN_STRUCT_DECLARATION_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STRUCT_DECLARATION_3: //0x2503-struct_declaration->static_assert_declaration 
{
	icode *a= func_IAN_STRUCT_DECLARATION_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_SPECIFIER_QUALIFIER_LIST_1: //0x2601-specifier_qualifier_list->type_specifier specifier_qualifier_list 
{
	icode *a= func_IAN_SPECIFIER_QUALIFIER_LIST_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_SPECIFIER_QUALIFIER_LIST_2: //0x2602-specifier_qualifier_list->type_specifier 
{
	icode *a= func_IAN_SPECIFIER_QUALIFIER_LIST_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_SPECIFIER_QUALIFIER_LIST_3: //0x2603-specifier_qualifier_list->type_qualifier specifier_qualifier_list 
{
	icode *a= func_IAN_SPECIFIER_QUALIFIER_LIST_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_SPECIFIER_QUALIFIER_LIST_4: //0x2604-specifier_qualifier_list->type_qualifier 
{
	icode *a= func_IAN_SPECIFIER_QUALIFIER_LIST_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STRUCT_DECLARATOR_LIST_1: //0x2701-struct_declarator_list->struct_declarator 
{
	icode *a= func_IAN_STRUCT_DECLARATOR_LIST_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STRUCT_DECLARATOR_LIST_2: //0x2702-struct_declarator_list->struct_declarator_list ',' struct_declarator 
{
	icode *a= func_IAN_STRUCT_DECLARATOR_LIST_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STRUCT_DECLARATOR_1: //0x2801-struct_declarator->':' constant_expression 
{
	icode *a= func_IAN_STRUCT_DECLARATOR_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STRUCT_DECLARATOR_2: //0x2802-struct_declarator->declarator ':' constant_expression 
{
	icode *a= func_IAN_STRUCT_DECLARATOR_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STRUCT_DECLARATOR_3: //0x2803-struct_declarator->declarator 
{
	icode *a= func_IAN_STRUCT_DECLARATOR_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ENUM_SPECIFIER_1: //0x2901-enum_specifier->ENUM '{' enumerator_list '}' 
{
	icode *a= func_IAN_ENUM_SPECIFIER_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ENUM_SPECIFIER_2: //0x2902-enum_specifier->ENUM '{' enumerator_list ',' '}' 
{
	icode *a= func_IAN_ENUM_SPECIFIER_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ENUM_SPECIFIER_3: //0x2903-enum_specifier->ENUM identifier '{' enumerator_list '}' 
{
	icode *a= func_IAN_ENUM_SPECIFIER_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ENUM_SPECIFIER_4: //0x2904-enum_specifier->ENUM identifier '{' enumerator_list ',' '}' 
{
	icode *a= func_IAN_ENUM_SPECIFIER_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ENUM_SPECIFIER_5: //0x2905-enum_specifier->ENUM identifier 
{
	icode *a= func_IAN_ENUM_SPECIFIER_5(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ENUMERATOR_LIST_1: //0x2a01-enumerator_list->enumerator 
{
	icode *a= func_IAN_ENUMERATOR_LIST_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ENUMERATOR_LIST_2: //0x2a02-enumerator_list->enumerator_list ',' enumerator 
{
	icode *a= func_IAN_ENUMERATOR_LIST_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ENUMERATOR_1: //0x2b01-enumerator->enumeration_constant '=' constant_expression 
{
	icode *a= func_IAN_ENUMERATOR_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ENUMERATOR_2: //0x2b02-enumerator->enumeration_constant 
{
	icode *a= func_IAN_ENUMERATOR_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ATOMIC_TYPE_SPECIFIER_1: //0x2c01-atomic_type_specifier->ATOMIC '(' type_name ')' 
{
	icode *a= func_IAN_ATOMIC_TYPE_SPECIFIER_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_QUALIFIER_1: //0x2d01-type_qualifier->CONST 
{
	icode *a= func_IAN_TYPE_QUALIFIER_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_QUALIFIER_2: //0x2d02-type_qualifier->RESTRICT 
{
	icode *a= func_IAN_TYPE_QUALIFIER_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_QUALIFIER_3: //0x2d03-type_qualifier->VOLATILE 
{
	icode *a= func_IAN_TYPE_QUALIFIER_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_QUALIFIER_4: //0x2d04-type_qualifier->ATOMIC 
{
	icode *a= func_IAN_TYPE_QUALIFIER_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_FUNCTION_SPECIFIER_1: //0x2e01-function_specifier->INLINE 
{
	icode *a= func_IAN_FUNCTION_SPECIFIER_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_FUNCTION_SPECIFIER_2: //0x2e02-function_specifier->NORETURN 
{
	icode *a= func_IAN_FUNCTION_SPECIFIER_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ALIGNMENT_SPECIFIER_1: //0x2f01-alignment_specifier->ALIGNAS '(' type_name ')' 
{
	icode *a= func_IAN_ALIGNMENT_SPECIFIER_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ALIGNMENT_SPECIFIER_2: //0x2f02-alignment_specifier->ALIGNAS '(' constant_expression ')' 
{
	icode *a= func_IAN_ALIGNMENT_SPECIFIER_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DECLARATOR_1: //0x3001-declarator->pointer direct_declarator 
{
	icode *a= func_IAN_DECLARATOR_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DECLARATOR_2: //0x3002-declarator->direct_declarator 
{
	icode *a= func_IAN_DECLARATOR_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_DECLARATOR_BASE_1: //0x3101-direct_declarator_base->identifier 
{
	icode *a= func_IAN_DIRECT_DECLARATOR_BASE_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_DECLARATOR_BASE_2: //0x3102-direct_declarator_base->'(' declarator ')' 
{
	icode *a= func_IAN_DIRECT_DECLARATOR_BASE_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_DECLARATOR_ARRAY_1: //0x3201-direct_declarator_array->direct_declarator_base 
{
	icode *a= func_IAN_DIRECT_DECLARATOR_ARRAY_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_DECLARATOR_ARRAY_2: //0x3202-direct_declarator_array->direct_declarator_array '[' ']' 
{
	icode *a= func_IAN_DIRECT_DECLARATOR_ARRAY_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_DECLARATOR_ARRAY_3: //0x3203-direct_declarator_array->direct_declarator_array '[' '*' ']' 
{
	icode *a= func_IAN_DIRECT_DECLARATOR_ARRAY_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_DECLARATOR_ARRAY_4: //0x3204-direct_declarator_array->direct_declarator_array '[' STATIC type_qualifier_list assignment_expression ']' 
{
	icode *a= func_IAN_DIRECT_DECLARATOR_ARRAY_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_DECLARATOR_ARRAY_5: //0x3205-direct_declarator_array->direct_declarator_array '[' STATIC assignment_expression ']' 
{
	icode *a= func_IAN_DIRECT_DECLARATOR_ARRAY_5(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_DECLARATOR_ARRAY_6: //0x3206-direct_declarator_array->direct_declarator_array '[' type_qualifier_list '*' ']' 
{
	icode *a= func_IAN_DIRECT_DECLARATOR_ARRAY_6(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_DECLARATOR_ARRAY_7: //0x3207-direct_declarator_array->direct_declarator_array '[' type_qualifier_list STATIC assignment_expression ']' 
{
	icode *a= func_IAN_DIRECT_DECLARATOR_ARRAY_7(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_DECLARATOR_ARRAY_8: //0x3208-direct_declarator_array->direct_declarator_array '[' type_qualifier_list assignment_expression ']' 
{
	icode *a= func_IAN_DIRECT_DECLARATOR_ARRAY_8(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_DECLARATOR_ARRAY_9: //0x3209-direct_declarator_array->direct_declarator_array '[' type_qualifier_list ']' 
{
	icode *a= func_IAN_DIRECT_DECLARATOR_ARRAY_9(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_DECLARATOR_ARRAY_10: //0x320a-direct_declarator_array->direct_declarator_array '[' assignment_expression ']' 
{
	icode *a= func_IAN_DIRECT_DECLARATOR_ARRAY_10(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_DECLARATOR_FUNCTION1_1: //0x3301-direct_declarator_function1->direct_declarator_array 
{
	icode *a= func_IAN_DIRECT_DECLARATOR_FUNCTION1_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_DECLARATOR_FUNCTION1_2: //0x3302-direct_declarator_function1->direct_declarator_function1 '(' parameter_type_list ')' 
{
	icode *a= func_IAN_DIRECT_DECLARATOR_FUNCTION1_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_DECLARATOR_FUNCTION1_3: //0x3303-direct_declarator_function1->direct_declarator_function1 '(' ')' 
{
	icode *a= func_IAN_DIRECT_DECLARATOR_FUNCTION1_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_DECLARATOR_FUNCTION1_4: //0x3304-direct_declarator_function1->direct_declarator_function1 '(' identifier_list ')' 
{
	icode *a= func_IAN_DIRECT_DECLARATOR_FUNCTION1_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_DECLARATOR_FUNCTION2_1: //0x3401-direct_declarator_function2->direct_declarator_function1 
{
	icode *a= func_IAN_DIRECT_DECLARATOR_FUNCTION2_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_DECLARATOR_FUNCTION2_2: //0x3402-direct_declarator_function2->direct_declarator_function1 function_attribute 
{
	icode *a= func_IAN_DIRECT_DECLARATOR_FUNCTION2_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_DECLARATOR_FUNCTION_1: //0x3501-direct_declarator_function->direct_declarator_function2 
{
	icode *a= func_IAN_DIRECT_DECLARATOR_FUNCTION_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_DECLARATOR_1: //0x3601-direct_declarator->direct_declarator_function 
{
	icode *a= func_IAN_DIRECT_DECLARATOR_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_POINTER_1: //0x3701-pointer->'*' type_qualifier_list pointer 
{
	icode *a= func_IAN_POINTER_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_POINTER_2: //0x3702-pointer->'*' type_qualifier_list 
{
	icode *a= func_IAN_POINTER_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_POINTER_3: //0x3703-pointer->'*' pointer 
{
	icode *a= func_IAN_POINTER_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_POINTER_4: //0x3704-pointer->'*' 
{
	icode *a= func_IAN_POINTER_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_QUALIFIER_LIST_1: //0x3801-type_qualifier_list->type_qualifier 
{
	icode *a= func_IAN_TYPE_QUALIFIER_LIST_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_QUALIFIER_LIST_2: //0x3802-type_qualifier_list->type_qualifier_list type_qualifier 
{
	icode *a= func_IAN_TYPE_QUALIFIER_LIST_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_PARAMETER_TYPE_LIST_1: //0x3901-parameter_type_list->parameter_list ',' ELLIPSIS 
{
	icode *a= func_IAN_PARAMETER_TYPE_LIST_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_PARAMETER_TYPE_LIST_2: //0x3902-parameter_type_list->parameter_list 
{
	icode *a= func_IAN_PARAMETER_TYPE_LIST_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_PARAMETER_LIST_1: //0x3a01-parameter_list->parameter_declaration 
{
	icode *a= func_IAN_PARAMETER_LIST_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_PARAMETER_LIST_2: //0x3a02-parameter_list->parameter_list ',' parameter_declaration 
{
	icode *a= func_IAN_PARAMETER_LIST_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_PARAMETER_DECLARATION_1: //0x3b01-parameter_declaration->declaration_specifiers declarator 
{
	icode *a= func_IAN_PARAMETER_DECLARATION_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_PARAMETER_DECLARATION_2: //0x3b02-parameter_declaration->declaration_specifiers abstract_declarator 
{
	icode *a= func_IAN_PARAMETER_DECLARATION_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_PARAMETER_DECLARATION_3: //0x3b03-parameter_declaration->declaration_specifiers 
{
	icode *a= func_IAN_PARAMETER_DECLARATION_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_IDENTIFIER_LIST_1: //0x3c01-identifier_list->identifier 
{
	icode *a= func_IAN_IDENTIFIER_LIST_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_IDENTIFIER_LIST_2: //0x3c02-identifier_list->identifier_list ',' identifier 
{
	icode *a= func_IAN_IDENTIFIER_LIST_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_NAME_1: //0x3d01-type_name->specifier_qualifier_list abstract_declarator 
{
	icode *a= func_IAN_TYPE_NAME_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TYPE_NAME_2: //0x3d02-type_name->specifier_qualifier_list 
{
	icode *a= func_IAN_TYPE_NAME_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ABSTRACT_DECLARATOR_1: //0x3e01-abstract_declarator->pointer direct_abstract_declarator 
{
	icode *a= func_IAN_ABSTRACT_DECLARATOR_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ABSTRACT_DECLARATOR_2: //0x3e02-abstract_declarator->pointer 
{
	icode *a= func_IAN_ABSTRACT_DECLARATOR_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ABSTRACT_DECLARATOR_3: //0x3e03-abstract_declarator->direct_abstract_declarator 
{
	icode *a= func_IAN_ABSTRACT_DECLARATOR_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_ABSTRACT_DECLARATOR_1: //0x3f01-direct_abstract_declarator->'(' abstract_declarator ')' 
{
	icode *a= func_IAN_DIRECT_ABSTRACT_DECLARATOR_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_ABSTRACT_DECLARATOR_2: //0x3f02-direct_abstract_declarator->'[' ']' 
{
	icode *a= func_IAN_DIRECT_ABSTRACT_DECLARATOR_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_ABSTRACT_DECLARATOR_3: //0x3f03-direct_abstract_declarator->'[' '*' ']' 
{
	icode *a= func_IAN_DIRECT_ABSTRACT_DECLARATOR_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_ABSTRACT_DECLARATOR_4: //0x3f04-direct_abstract_declarator->'[' STATIC type_qualifier_list assignment_expression ']' 
{
	icode *a= func_IAN_DIRECT_ABSTRACT_DECLARATOR_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_ABSTRACT_DECLARATOR_5: //0x3f05-direct_abstract_declarator->'[' STATIC assignment_expression ']' 
{
	icode *a= func_IAN_DIRECT_ABSTRACT_DECLARATOR_5(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_ABSTRACT_DECLARATOR_6: //0x3f06-direct_abstract_declarator->'[' type_qualifier_list STATIC assignment_expression ']' 
{
	icode *a= func_IAN_DIRECT_ABSTRACT_DECLARATOR_6(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_ABSTRACT_DECLARATOR_7: //0x3f07-direct_abstract_declarator->'[' type_qualifier_list assignment_expression ']' 
{
	icode *a= func_IAN_DIRECT_ABSTRACT_DECLARATOR_7(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_ABSTRACT_DECLARATOR_8: //0x3f08-direct_abstract_declarator->'[' type_qualifier_list ']' 
{
	icode *a= func_IAN_DIRECT_ABSTRACT_DECLARATOR_8(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_ABSTRACT_DECLARATOR_9: //0x3f09-direct_abstract_declarator->'[' assignment_expression ']' 
{
	icode *a= func_IAN_DIRECT_ABSTRACT_DECLARATOR_9(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_ABSTRACT_DECLARATOR_10: //0x3f0a-direct_abstract_declarator->direct_abstract_declarator '[' ']' 
{
	icode *a= func_IAN_DIRECT_ABSTRACT_DECLARATOR_10(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_ABSTRACT_DECLARATOR_11: //0x3f0b-direct_abstract_declarator->direct_abstract_declarator '[' '*' ']' 
{
	icode *a= func_IAN_DIRECT_ABSTRACT_DECLARATOR_11(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_ABSTRACT_DECLARATOR_12: //0x3f0c-direct_abstract_declarator->direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']' 
{
	icode *a= func_IAN_DIRECT_ABSTRACT_DECLARATOR_12(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_ABSTRACT_DECLARATOR_13: //0x3f0d-direct_abstract_declarator->direct_abstract_declarator '[' STATIC assignment_expression ']' 
{
	icode *a= func_IAN_DIRECT_ABSTRACT_DECLARATOR_13(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_ABSTRACT_DECLARATOR_14: //0x3f0e-direct_abstract_declarator->direct_abstract_declarator '[' type_qualifier_list assignment_expression ']' 
{
	icode *a= func_IAN_DIRECT_ABSTRACT_DECLARATOR_14(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_ABSTRACT_DECLARATOR_15: //0x3f0f-direct_abstract_declarator->direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']' 
{
	icode *a= func_IAN_DIRECT_ABSTRACT_DECLARATOR_15(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_ABSTRACT_DECLARATOR_16: //0x3f10-direct_abstract_declarator->direct_abstract_declarator '[' type_qualifier_list ']' 
{
	icode *a= func_IAN_DIRECT_ABSTRACT_DECLARATOR_16(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_ABSTRACT_DECLARATOR_17: //0x3f11-direct_abstract_declarator->direct_abstract_declarator '[' assignment_expression ']' 
{
	icode *a= func_IAN_DIRECT_ABSTRACT_DECLARATOR_17(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_ABSTRACT_DECLARATOR_18: //0x3f12-direct_abstract_declarator->'(' ')' 
{
	icode *a= func_IAN_DIRECT_ABSTRACT_DECLARATOR_18(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_ABSTRACT_DECLARATOR_19: //0x3f13-direct_abstract_declarator->'(' parameter_type_list ')' 
{
	icode *a= func_IAN_DIRECT_ABSTRACT_DECLARATOR_19(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_ABSTRACT_DECLARATOR_20: //0x3f14-direct_abstract_declarator->direct_abstract_declarator '(' ')' 
{
	icode *a= func_IAN_DIRECT_ABSTRACT_DECLARATOR_20(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DIRECT_ABSTRACT_DECLARATOR_21: //0x3f15-direct_abstract_declarator->direct_abstract_declarator '(' parameter_type_list ')' 
{
	icode *a= func_IAN_DIRECT_ABSTRACT_DECLARATOR_21(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_INITIALIZER_1: //0x4001-initializer->'{' initializer_list '}' 
{
	icode *a= func_IAN_INITIALIZER_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_INITIALIZER_2: //0x4002-initializer->'{' initializer_list ',' '}' 
{
	icode *a= func_IAN_INITIALIZER_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_INITIALIZER_3: //0x4003-initializer->assignment_expression 
{
	icode *a= func_IAN_INITIALIZER_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_INITIALIZER_LIST_1: //0x4101-initializer_list->designation initializer 
{
	icode *a= func_IAN_INITIALIZER_LIST_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_INITIALIZER_LIST_2: //0x4102-initializer_list->initializer 
{
	icode *a= func_IAN_INITIALIZER_LIST_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_INITIALIZER_LIST_3: //0x4103-initializer_list->initializer_list ',' designation initializer 
{
	icode *a= func_IAN_INITIALIZER_LIST_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_INITIALIZER_LIST_4: //0x4104-initializer_list->initializer_list ',' initializer 
{
	icode *a= func_IAN_INITIALIZER_LIST_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DESIGNATION_1: //0x4201-designation->designator_list '=' 
{
	icode *a= func_IAN_DESIGNATION_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DESIGNATOR_LIST_1: //0x4301-designator_list->designator 
{
	icode *a= func_IAN_DESIGNATOR_LIST_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DESIGNATOR_LIST_2: //0x4302-designator_list->designator_list designator 
{
	icode *a= func_IAN_DESIGNATOR_LIST_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DESIGNATOR_1: //0x4401-designator->'[' constant_expression ']' 
{
	icode *a= func_IAN_DESIGNATOR_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DESIGNATOR_2: //0x4402-designator->'.' identifier 
{
	icode *a= func_IAN_DESIGNATOR_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STATIC_ASSERT_DECLARATION_1: //0x4501-static_assert_declaration->STATIC_ASSERT '(' constant_expression ',' STRING_LITERAL ')' ';' 
{
	icode *a= func_IAN_STATIC_ASSERT_DECLARATION_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STATEMENT_1: //0x4601-statement->labeled_statement 
{
	icode *a= func_IAN_STATEMENT_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STATEMENT_2: //0x4602-statement->compound_statement 
{
	icode *a= func_IAN_STATEMENT_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STATEMENT_3: //0x4603-statement->expression_statement 
{
	icode *a= func_IAN_STATEMENT_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STATEMENT_4: //0x4604-statement->selection_statement 
{
	icode *a= func_IAN_STATEMENT_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STATEMENT_5: //0x4605-statement->iteration_statement 
{
	icode *a= func_IAN_STATEMENT_5(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_STATEMENT_6: //0x4606-statement->jump_statement 
{
	icode *a= func_IAN_STATEMENT_6(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_LABELED_STATEMENT_1: //0x4701-labeled_statement->identifier ':' statement 
{
	icode *a= func_IAN_LABELED_STATEMENT_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_LABELED_STATEMENT_2: //0x4702-labeled_statement->CASE constant_expression ':' statement 
{
	icode *a= func_IAN_LABELED_STATEMENT_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_LABELED_STATEMENT_3: //0x4703-labeled_statement->DEFAULT ':' statement 
{
	icode *a= func_IAN_LABELED_STATEMENT_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_COMPOUND_STATEMENT_1: //0x4801-compound_statement->'{' '}' 
{
	icode *a= func_IAN_COMPOUND_STATEMENT_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_COMPOUND_STATEMENT_2: //0x4802-compound_statement->'{' block_item_list '}' 
{
	icode *a= func_IAN_COMPOUND_STATEMENT_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_BLOCK_ITEM_LIST_1: //0x4901-block_item_list->block_item 
{
	icode *a= func_IAN_BLOCK_ITEM_LIST_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_BLOCK_ITEM_LIST_2: //0x4902-block_item_list->block_item_list block_item 
{
	icode *a= func_IAN_BLOCK_ITEM_LIST_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_BLOCK_ITEM_1: //0x4a01-block_item->declaration 
{
	icode *a= func_IAN_BLOCK_ITEM_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_BLOCK_ITEM_2: //0x4a02-block_item->statement 
{
	icode *a= func_IAN_BLOCK_ITEM_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_EXPRESSION_STATEMENT_1: //0x4b01-expression_statement->';' 
{
	icode *a= func_IAN_EXPRESSION_STATEMENT_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_EXPRESSION_STATEMENT_2: //0x4b02-expression_statement->expression ';' 
{
	icode *a= func_IAN_EXPRESSION_STATEMENT_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_SELECTION_STATEMENT_1: //0x4c01-selection_statement->IF '(' expression ')' statement ELSE statement 
{
	icode *a= func_IAN_SELECTION_STATEMENT_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_SELECTION_STATEMENT_2: //0x4c02-selection_statement->IF '(' expression ')' statement 
{
	icode *a= func_IAN_SELECTION_STATEMENT_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_SELECTION_STATEMENT_3: //0x4c03-selection_statement->SWITCH '(' expression ')' statement 
{
	icode *a= func_IAN_SELECTION_STATEMENT_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ITERATION_STATEMENT_1: //0x4d01-iteration_statement->WHILE '(' expression ')' statement 
{
	icode *a= func_IAN_ITERATION_STATEMENT_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ITERATION_STATEMENT_2: //0x4d02-iteration_statement->DO statement WHILE '(' expression ')' ';' 
{
	icode *a= func_IAN_ITERATION_STATEMENT_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ITERATION_STATEMENT_3: //0x4d03-iteration_statement->FOR '(' expression_statement expression_statement ')' statement 
{
	icode *a= func_IAN_ITERATION_STATEMENT_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ITERATION_STATEMENT_4: //0x4d04-iteration_statement->FOR '(' expression_statement expression_statement expression ')' statement 
{
	icode *a= func_IAN_ITERATION_STATEMENT_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ITERATION_STATEMENT_5: //0x4d05-iteration_statement->FOR '(' declaration expression_statement ')' statement 
{
	icode *a= func_IAN_ITERATION_STATEMENT_5(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_ITERATION_STATEMENT_6: //0x4d06-iteration_statement->FOR '(' declaration expression_statement expression ')' statement 
{
	icode *a= func_IAN_ITERATION_STATEMENT_6(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_JUMP_STATEMENT_1: //0x4e01-jump_statement->GOTO identifier ';' 
{
	icode *a= func_IAN_JUMP_STATEMENT_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_JUMP_STATEMENT_2: //0x4e02-jump_statement->CONTINUE ';' 
{
	icode *a= func_IAN_JUMP_STATEMENT_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_JUMP_STATEMENT_3: //0x4e03-jump_statement->BREAK ';' 
{
	icode *a= func_IAN_JUMP_STATEMENT_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_JUMP_STATEMENT_4: //0x4e04-jump_statement->RETURN ';' 
{
	icode *a= func_IAN_JUMP_STATEMENT_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_JUMP_STATEMENT_5: //0x4e05-jump_statement->RETURN expression ';' 
{
	icode *a= func_IAN_JUMP_STATEMENT_5(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TRANSLATION_UNIT_1: //0x4f01-translation_unit->external_declaration 
{
	icode *a= func_IAN_TRANSLATION_UNIT_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_TRANSLATION_UNIT_2: //0x4f02-translation_unit->translation_unit external_declaration 
{
	icode *a= func_IAN_TRANSLATION_UNIT_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_FILE_1: //0x5001-file->/*empty*/ 
{
	icode *a= func_IAN_FILE_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_FILE_2: //0x5002-file->translation_unit 
{
	icode *a= func_IAN_FILE_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_EXTERNAL_DECLARATION_1: //0x5101-external_declaration->function_definition 
{
	icode *a= func_IAN_EXTERNAL_DECLARATION_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_EXTERNAL_DECLARATION_2: //0x5102-external_declaration->declaration 
{
	icode *a= func_IAN_EXTERNAL_DECLARATION_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_FUNCTION_DEFINITION_1: //0x5201-function_definition->declaration_specifiers declarator declaration_list compound_statement 
{
	icode *a= func_IAN_FUNCTION_DEFINITION_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_FUNCTION_DEFINITION_2: //0x5202-function_definition->declaration_specifiers declarator compound_statement 
{
	icode *a= func_IAN_FUNCTION_DEFINITION_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DECLARATION_LIST_1: //0x5301-declaration_list->declaration 
{
	icode *a= func_IAN_DECLARATION_LIST_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_DECLARATION_LIST_2: //0x5302-declaration_list->declaration_list declaration 
{
	icode *a= func_IAN_DECLARATION_LIST_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_IDENTIFIER_1: //0x5401-identifier->IDENTIFIER 
{
	icode *a= func_IAN_IDENTIFIER_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_FUNCTION_ATTRIBUTE1_1: //0x5501-function_attribute1->USING constant_expression 
{
	icode *a= func_IAN_FUNCTION_ATTRIBUTE1_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_FUNCTION_ATTRIBUTE1_2: //0x5502-function_attribute1->REENTRANT 
{
	icode *a= func_IAN_FUNCTION_ATTRIBUTE1_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_FUNCTION_ATTRIBUTE1_3: //0x5503-function_attribute1->INTERRUPT constant_expression 
{
	icode *a= func_IAN_FUNCTION_ATTRIBUTE1_3(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_FUNCTION_ATTRIBUTE1_4: //0x5504-function_attribute1->REGPARAMS string 
{
	icode *a= func_IAN_FUNCTION_ATTRIBUTE1_4(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_FUNCTION_ATTRIBUTE2_1: //0x5601-function_attribute2->function_attribute1 
{
	icode *a= func_IAN_FUNCTION_ATTRIBUTE2_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_FUNCTION_ATTRIBUTE2_2: //0x5602-function_attribute2->function_attribute1 function_attribute2 
{
	icode *a= func_IAN_FUNCTION_ATTRIBUTE2_2(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;
case IAN_FUNCTION_ATTRIBUTE_1: //0x5701-function_attribute->function_attribute2 
{
	icode *a= func_IAN_FUNCTION_ATTRIBUTE_1(this, tdefs, need_result_icode, result_ic);
	return a;
}
break;

}//switch end. case_cnt=12b

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

}//namespace NS_C2IR
