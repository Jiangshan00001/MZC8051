

#include "comp_context_gen_defs.h"
#include "comp_context_yy_debug.h"
#include "parser.h"
using namespace NS_C2IR;

std::vector<T_DEBUG_LIST>g_ast_debug_str=

{
{IAN_PRIMARY_EXPRESSION_1, "primary_expression->identifier " },
{IAN_PRIMARY_EXPRESSION_2, "primary_expression->constant " },
{IAN_PRIMARY_EXPRESSION_3, "primary_expression->string " },
{IAN_PRIMARY_EXPRESSION_4, "primary_expression->'(' expression ')' " },
{IAN_PRIMARY_EXPRESSION_5, "primary_expression->generic_selection " },
{IAN_CONSTANT_1, "constant->I_CONSTANT " },
{IAN_CONSTANT_2, "constant->F_CONSTANT " },
{IAN_CONSTANT_3, "constant->ENUMERATION_CONSTANT " },
{IAN_ENUMERATION_CONSTANT_1, "enumeration_constant->identifier " },
{IAN_STRING_1, "string->STRING_LITERAL " },
{IAN_STRING_2, "string->FUNC_NAME " },
{IAN_GENERIC_SELECTION_1, "generic_selection->GENERIC '(' assignment_expression ',' generic_assoc_list ')' " },
{IAN_GENERIC_ASSOC_LIST_1, "generic_assoc_list->generic_association " },
{IAN_GENERIC_ASSOC_LIST_2, "generic_assoc_list->generic_assoc_list ',' generic_association " },
{IAN_GENERIC_ASSOCIATION_1, "generic_association->type_name ':' assignment_expression " },
{IAN_GENERIC_ASSOCIATION_2, "generic_association->DEFAULT ':' assignment_expression " },
{IAN_POSTFIX_EXPRESSION_1, "postfix_expression->primary_expression " },
{IAN_POSTFIX_EXPRESSION_2, "postfix_expression->postfix_expression '[' expression ']' " },
{IAN_POSTFIX_EXPRESSION_3, "postfix_expression->postfix_expression '(' ')' " },
{IAN_POSTFIX_EXPRESSION_4, "postfix_expression->postfix_expression '(' argument_expression_list ')' " },
{IAN_POSTFIX_EXPRESSION_5, "postfix_expression->postfix_expression '.' identifier " },
{IAN_POSTFIX_EXPRESSION_6, "postfix_expression->postfix_expression PTR_OP identifier " },
{IAN_POSTFIX_EXPRESSION_7, "postfix_expression->postfix_expression INC_OP " },
{IAN_POSTFIX_EXPRESSION_8, "postfix_expression->postfix_expression DEC_OP " },
{IAN_POSTFIX_EXPRESSION_9, "postfix_expression->'(' type_name ')' '{' initializer_list '}' " },
{IAN_POSTFIX_EXPRESSION_10, "postfix_expression->'(' type_name ')' '{' initializer_list ',' '}' " },
{IAN_ARGUMENT_EXPRESSION_LIST_1, "argument_expression_list->assignment_expression " },
{IAN_ARGUMENT_EXPRESSION_LIST_2, "argument_expression_list->argument_expression_list ',' assignment_expression " },
{IAN_UNARY_EXPRESSION_1, "unary_expression->postfix_expression " },
{IAN_UNARY_EXPRESSION_2, "unary_expression->INC_OP unary_expression " },
{IAN_UNARY_EXPRESSION_3, "unary_expression->DEC_OP unary_expression " },
{IAN_UNARY_EXPRESSION_4, "unary_expression->unary_operator cast_expression " },
{IAN_UNARY_EXPRESSION_5, "unary_expression->SIZEOF unary_expression " },
{IAN_UNARY_EXPRESSION_6, "unary_expression->SIZEOF '(' type_name ')' " },
{IAN_UNARY_EXPRESSION_7, "unary_expression->ALIGNOF '(' type_name ')' " },
{IAN_UNARY_OPERATOR_1, "unary_operator->'&' " },
{IAN_UNARY_OPERATOR_2, "unary_operator->'*' " },
{IAN_UNARY_OPERATOR_3, "unary_operator->'+' " },
{IAN_UNARY_OPERATOR_4, "unary_operator->'-' " },
{IAN_UNARY_OPERATOR_5, "unary_operator->'~' " },
{IAN_UNARY_OPERATOR_6, "unary_operator->'!' " },
{IAN_CAST_EXPRESSION_1, "cast_expression->unary_expression " },
{IAN_CAST_EXPRESSION_2, "cast_expression->'(' type_name ')' cast_expression " },
{IAN_MULTIPLICATIVE_EXPRESSION_1, "multiplicative_expression->cast_expression " },
{IAN_MULTIPLICATIVE_EXPRESSION_2, "multiplicative_expression->multiplicative_expression '*' cast_expression " },
{IAN_MULTIPLICATIVE_EXPRESSION_3, "multiplicative_expression->multiplicative_expression '/' cast_expression " },
{IAN_MULTIPLICATIVE_EXPRESSION_4, "multiplicative_expression->multiplicative_expression '%' cast_expression " },
{IAN_ADDITIVE_EXPRESSION_1, "additive_expression->multiplicative_expression " },
{IAN_ADDITIVE_EXPRESSION_2, "additive_expression->additive_expression '+' multiplicative_expression " },
{IAN_ADDITIVE_EXPRESSION_3, "additive_expression->additive_expression '-' multiplicative_expression " },
{IAN_SHIFT_EXPRESSION_1, "shift_expression->additive_expression " },
{IAN_SHIFT_EXPRESSION_2, "shift_expression->shift_expression LEFT_OP additive_expression " },
{IAN_SHIFT_EXPRESSION_3, "shift_expression->shift_expression RIGHT_OP additive_expression " },
{IAN_SHIFT_EXPRESSION_4, "shift_expression->shift_expression ROTATE_LEFT_OP additive_expression " },
{IAN_SHIFT_EXPRESSION_5, "shift_expression->shift_expression ROTATE_RIGHT_OP additive_expression " },
{IAN_RELATIONAL_EXPRESSION_1, "relational_expression->shift_expression " },
{IAN_RELATIONAL_EXPRESSION_2, "relational_expression->relational_expression '<' shift_expression " },
{IAN_RELATIONAL_EXPRESSION_3, "relational_expression->relational_expression '>' shift_expression " },
{IAN_RELATIONAL_EXPRESSION_4, "relational_expression->relational_expression LE_OP shift_expression " },
{IAN_RELATIONAL_EXPRESSION_5, "relational_expression->relational_expression GE_OP shift_expression " },
{IAN_EQUALITY_EXPRESSION_1, "equality_expression->relational_expression " },
{IAN_EQUALITY_EXPRESSION_2, "equality_expression->equality_expression EQ_OP relational_expression " },
{IAN_EQUALITY_EXPRESSION_3, "equality_expression->equality_expression NE_OP relational_expression " },
{IAN_AND_EXPRESSION_1, "and_expression->equality_expression " },
{IAN_AND_EXPRESSION_2, "and_expression->and_expression '&' equality_expression " },
{IAN_EXCLUSIVE_OR_EXPRESSION_1, "exclusive_or_expression->and_expression " },
{IAN_EXCLUSIVE_OR_EXPRESSION_2, "exclusive_or_expression->exclusive_or_expression '^' and_expression " },
{IAN_INCLUSIVE_OR_EXPRESSION_1, "inclusive_or_expression->exclusive_or_expression " },
{IAN_INCLUSIVE_OR_EXPRESSION_2, "inclusive_or_expression->inclusive_or_expression '|' exclusive_or_expression " },
{IAN_LOGICAL_AND_EXPRESSION_1, "logical_and_expression->inclusive_or_expression " },
{IAN_LOGICAL_AND_EXPRESSION_2, "logical_and_expression->logical_and_expression AND_OP inclusive_or_expression " },
{IAN_LOGICAL_OR_EXPRESSION_1, "logical_or_expression->logical_and_expression " },
{IAN_LOGICAL_OR_EXPRESSION_2, "logical_or_expression->logical_or_expression OR_OP logical_and_expression " },
{IAN_CONDITIONAL_EXPRESSION_1, "conditional_expression->logical_or_expression " },
{IAN_CONDITIONAL_EXPRESSION_2, "conditional_expression->logical_or_expression '?' expression ':' conditional_expression " },
{IAN_ASSIGNMENT_EXPRESSION_1, "assignment_expression->conditional_expression " },
{IAN_ASSIGNMENT_EXPRESSION_2, "assignment_expression->unary_expression assignment_operator assignment_expression " },
{IAN_ASSIGNMENT_OPERATOR_1, "assignment_operator->'=' " },
{IAN_ASSIGNMENT_OPERATOR_2, "assignment_operator->MUL_ASSIGN " },
{IAN_ASSIGNMENT_OPERATOR_3, "assignment_operator->DIV_ASSIGN " },
{IAN_ASSIGNMENT_OPERATOR_4, "assignment_operator->MOD_ASSIGN " },
{IAN_ASSIGNMENT_OPERATOR_5, "assignment_operator->ADD_ASSIGN " },
{IAN_ASSIGNMENT_OPERATOR_6, "assignment_operator->SUB_ASSIGN " },
{IAN_ASSIGNMENT_OPERATOR_7, "assignment_operator->LEFT_ASSIGN " },
{IAN_ASSIGNMENT_OPERATOR_8, "assignment_operator->RIGHT_ASSIGN " },
{IAN_ASSIGNMENT_OPERATOR_9, "assignment_operator->AND_ASSIGN " },
{IAN_ASSIGNMENT_OPERATOR_10, "assignment_operator->XOR_ASSIGN " },
{IAN_ASSIGNMENT_OPERATOR_11, "assignment_operator->OR_ASSIGN " },
{IAN_EXPRESSION_1, "expression->assignment_expression " },
{IAN_EXPRESSION_2, "expression->expression ',' assignment_expression " },
{IAN_CONSTANT_EXPRESSION_1, "constant_expression->conditional_expression " },
{IAN_DECLARATION_1, "declaration->declaration_specifiers ';' " },
{IAN_DECLARATION_2, "declaration->declaration_specifiers init_declarator_list ';' " },
{IAN_DECLARATION_3, "declaration->static_assert_declaration " },
{IAN_DECLARATION_SPECIFIERS_1, "declaration_specifiers->declaration_specifiers_ " },
{IAN_DECLARATION_SPECIFIERS__1, "declaration_specifiers_->storage_class_specifier declaration_specifiers_ " },
{IAN_DECLARATION_SPECIFIERS__2, "declaration_specifiers_->storage_class_specifier " },
{IAN_DECLARATION_SPECIFIERS__3, "declaration_specifiers_->type_specifier declaration_specifiers_ " },
{IAN_DECLARATION_SPECIFIERS__4, "declaration_specifiers_->type_specifier " },
{IAN_DECLARATION_SPECIFIERS__5, "declaration_specifiers_->type_qualifier declaration_specifiers_ " },
{IAN_DECLARATION_SPECIFIERS__6, "declaration_specifiers_->type_qualifier " },
{IAN_DECLARATION_SPECIFIERS__7, "declaration_specifiers_->function_specifier declaration_specifiers_ " },
{IAN_DECLARATION_SPECIFIERS__8, "declaration_specifiers_->function_specifier " },
{IAN_DECLARATION_SPECIFIERS__9, "declaration_specifiers_->alignment_specifier declaration_specifiers_ " },
{IAN_DECLARATION_SPECIFIERS__10, "declaration_specifiers_->alignment_specifier " },
{IAN_INIT_DECLARATOR_LIST_1, "init_declarator_list->init_declarator " },
{IAN_INIT_DECLARATOR_LIST_2, "init_declarator_list->init_declarator_list ',' init_declarator " },
{IAN_INIT_DECLARATOR_1, "init_declarator->declarator '=' initializer " },
{IAN_INIT_DECLARATOR_2, "init_declarator->declarator " },
{IAN_STORAGE_CLASS_SPECIFIER_1, "storage_class_specifier->TYPEDEF " },
{IAN_STORAGE_CLASS_SPECIFIER_2, "storage_class_specifier->EXTERN " },
{IAN_STORAGE_CLASS_SPECIFIER_3, "storage_class_specifier->STATIC " },
{IAN_STORAGE_CLASS_SPECIFIER_4, "storage_class_specifier->THREAD_LOCAL " },
{IAN_STORAGE_CLASS_SPECIFIER_5, "storage_class_specifier->AUTO " },
{IAN_STORAGE_CLASS_SPECIFIER_6, "storage_class_specifier->REGISTER " },
{IAN_STORAGE_CLASS_SPECIFIER_7, "storage_class_specifier->STORAGE_SPEC_C51 " },
{IAN_TYPE_SPECIFIER_1, "type_specifier->VOID " },
{IAN_TYPE_SPECIFIER_2, "type_specifier->CHAR " },
{IAN_TYPE_SPECIFIER_3, "type_specifier->SHORT " },
{IAN_TYPE_SPECIFIER_4, "type_specifier->INT " },
{IAN_TYPE_SPECIFIER_5, "type_specifier->LONG " },
{IAN_TYPE_SPECIFIER_6, "type_specifier->FLOAT " },
{IAN_TYPE_SPECIFIER_7, "type_specifier->DOUBLE " },
{IAN_TYPE_SPECIFIER_8, "type_specifier->SIGNED " },
{IAN_TYPE_SPECIFIER_9, "type_specifier->UNSIGNED " },
{IAN_TYPE_SPECIFIER_10, "type_specifier->BOOL " },
{IAN_TYPE_SPECIFIER_11, "type_specifier->COMPLEX " },
{IAN_TYPE_SPECIFIER_12, "type_specifier->IMAGINARY " },
{IAN_TYPE_SPECIFIER_13, "type_specifier->atomic_type_specifier " },
{IAN_TYPE_SPECIFIER_14, "type_specifier->struct_or_union_specifier " },
{IAN_TYPE_SPECIFIER_15, "type_specifier->enum_specifier " },
{IAN_TYPE_SPECIFIER_16, "type_specifier->TYPEDEF_NAME " },
{IAN_TYPE_SPECIFIER_17, "type_specifier->SFR " },
{IAN_TYPE_SPECIFIER_18, "type_specifier->BIT " },
{IAN_TYPE_SPECIFIER_19, "type_specifier->SBIT " },
{IAN_TYPE_SPECIFIER_20, "type_specifier->SFR16 " },
{IAN_TYPE_SPECIFIER_21, "type_specifier->SFR32 " },
{IAN_STRUCT_OR_UNION_SPECIFIER_1, "struct_or_union_specifier->struct_or_union '{' struct_declaration_list '}' " },
{IAN_STRUCT_OR_UNION_SPECIFIER_2, "struct_or_union_specifier->struct_or_union identifier '{' struct_declaration_list '}' " },
{IAN_STRUCT_OR_UNION_SPECIFIER_3, "struct_or_union_specifier->struct_or_union identifier " },
{IAN_STRUCT_OR_UNION_1, "struct_or_union->STRUCT " },
{IAN_STRUCT_OR_UNION_2, "struct_or_union->UNION " },
{IAN_STRUCT_DECLARATION_LIST_1, "struct_declaration_list->struct_declaration " },
{IAN_STRUCT_DECLARATION_LIST_2, "struct_declaration_list->struct_declaration_list struct_declaration " },
{IAN_STRUCT_DECLARATION_1, "struct_declaration->specifier_qualifier_list ';' " },
{IAN_STRUCT_DECLARATION_2, "struct_declaration->specifier_qualifier_list struct_declarator_list ';' " },
{IAN_STRUCT_DECLARATION_3, "struct_declaration->static_assert_declaration " },
{IAN_SPECIFIER_QUALIFIER_LIST_1, "specifier_qualifier_list->type_specifier specifier_qualifier_list " },
{IAN_SPECIFIER_QUALIFIER_LIST_2, "specifier_qualifier_list->type_specifier " },
{IAN_SPECIFIER_QUALIFIER_LIST_3, "specifier_qualifier_list->type_qualifier specifier_qualifier_list " },
{IAN_SPECIFIER_QUALIFIER_LIST_4, "specifier_qualifier_list->type_qualifier " },
{IAN_STRUCT_DECLARATOR_LIST_1, "struct_declarator_list->struct_declarator " },
{IAN_STRUCT_DECLARATOR_LIST_2, "struct_declarator_list->struct_declarator_list ',' struct_declarator " },
{IAN_STRUCT_DECLARATOR_1, "struct_declarator->':' constant_expression " },
{IAN_STRUCT_DECLARATOR_2, "struct_declarator->declarator ':' constant_expression " },
{IAN_STRUCT_DECLARATOR_3, "struct_declarator->declarator " },
{IAN_ENUM_SPECIFIER_1, "enum_specifier->ENUM '{' enumerator_list '}' " },
{IAN_ENUM_SPECIFIER_2, "enum_specifier->ENUM '{' enumerator_list ',' '}' " },
{IAN_ENUM_SPECIFIER_3, "enum_specifier->ENUM identifier '{' enumerator_list '}' " },
{IAN_ENUM_SPECIFIER_4, "enum_specifier->ENUM identifier '{' enumerator_list ',' '}' " },
{IAN_ENUM_SPECIFIER_5, "enum_specifier->ENUM identifier " },
{IAN_ENUMERATOR_LIST_1, "enumerator_list->enumerator " },
{IAN_ENUMERATOR_LIST_2, "enumerator_list->enumerator_list ',' enumerator " },
{IAN_ENUMERATOR_1, "enumerator->enumeration_constant '=' constant_expression " },
{IAN_ENUMERATOR_2, "enumerator->enumeration_constant " },
{IAN_ATOMIC_TYPE_SPECIFIER_1, "atomic_type_specifier->ATOMIC '(' type_name ')' " },
{IAN_TYPE_QUALIFIER_1, "type_qualifier->CONST " },
{IAN_TYPE_QUALIFIER_2, "type_qualifier->RESTRICT " },
{IAN_TYPE_QUALIFIER_3, "type_qualifier->VOLATILE " },
{IAN_TYPE_QUALIFIER_4, "type_qualifier->ATOMIC " },
{IAN_FUNCTION_SPECIFIER_1, "function_specifier->INLINE " },
{IAN_FUNCTION_SPECIFIER_2, "function_specifier->NORETURN " },
{IAN_ALIGNMENT_SPECIFIER_1, "alignment_specifier->ALIGNAS '(' type_name ')' " },
{IAN_ALIGNMENT_SPECIFIER_2, "alignment_specifier->ALIGNAS '(' constant_expression ')' " },
{IAN_DECLARATOR_1, "declarator->pointer direct_declarator " },
{IAN_DECLARATOR_2, "declarator->direct_declarator " },
{IAN_DIRECT_DECLARATOR_BASE_1, "direct_declarator_base->identifier " },
{IAN_DIRECT_DECLARATOR_BASE_2, "direct_declarator_base->'(' declarator ')' " },
{IAN_DIRECT_DECLARATOR_ARRAY_1, "direct_declarator_array->direct_declarator_base " },
{IAN_DIRECT_DECLARATOR_ARRAY_2, "direct_declarator_array->direct_declarator_array '[' ']' " },
{IAN_DIRECT_DECLARATOR_ARRAY_3, "direct_declarator_array->direct_declarator_array '[' '*' ']' " },
{IAN_DIRECT_DECLARATOR_ARRAY_4, "direct_declarator_array->direct_declarator_array '[' STATIC type_qualifier_list assignment_expression ']' " },
{IAN_DIRECT_DECLARATOR_ARRAY_5, "direct_declarator_array->direct_declarator_array '[' STATIC assignment_expression ']' " },
{IAN_DIRECT_DECLARATOR_ARRAY_6, "direct_declarator_array->direct_declarator_array '[' type_qualifier_list '*' ']' " },
{IAN_DIRECT_DECLARATOR_ARRAY_7, "direct_declarator_array->direct_declarator_array '[' type_qualifier_list STATIC assignment_expression ']' " },
{IAN_DIRECT_DECLARATOR_ARRAY_8, "direct_declarator_array->direct_declarator_array '[' type_qualifier_list assignment_expression ']' " },
{IAN_DIRECT_DECLARATOR_ARRAY_9, "direct_declarator_array->direct_declarator_array '[' type_qualifier_list ']' " },
{IAN_DIRECT_DECLARATOR_ARRAY_10, "direct_declarator_array->direct_declarator_array '[' assignment_expression ']' " },
{IAN_DIRECT_DECLARATOR_FUNCTION1_1, "direct_declarator_function1->direct_declarator_array " },
{IAN_DIRECT_DECLARATOR_FUNCTION1_2, "direct_declarator_function1->direct_declarator_function1 '(' parameter_type_list ')' " },
{IAN_DIRECT_DECLARATOR_FUNCTION1_3, "direct_declarator_function1->direct_declarator_function1 '(' ')' " },
{IAN_DIRECT_DECLARATOR_FUNCTION1_4, "direct_declarator_function1->direct_declarator_function1 '(' identifier_list ')' " },
{IAN_DIRECT_DECLARATOR_FUNCTION2_1, "direct_declarator_function2->direct_declarator_function1 " },
{IAN_DIRECT_DECLARATOR_FUNCTION2_2, "direct_declarator_function2->direct_declarator_function1 function_attribute " },
{IAN_DIRECT_DECLARATOR_FUNCTION_1, "direct_declarator_function->direct_declarator_function2 " },
{IAN_DIRECT_DECLARATOR_1, "direct_declarator->direct_declarator_function " },
{IAN_POINTER_1, "pointer->'*' type_qualifier_list pointer " },
{IAN_POINTER_2, "pointer->'*' type_qualifier_list " },
{IAN_POINTER_3, "pointer->'*' pointer " },
{IAN_POINTER_4, "pointer->'*' " },
{IAN_TYPE_QUALIFIER_LIST_1, "type_qualifier_list->type_qualifier " },
{IAN_TYPE_QUALIFIER_LIST_2, "type_qualifier_list->type_qualifier_list type_qualifier " },
{IAN_PARAMETER_TYPE_LIST_1, "parameter_type_list->parameter_list ',' ELLIPSIS " },
{IAN_PARAMETER_TYPE_LIST_2, "parameter_type_list->parameter_list " },
{IAN_PARAMETER_LIST_1, "parameter_list->parameter_declaration " },
{IAN_PARAMETER_LIST_2, "parameter_list->parameter_list ',' parameter_declaration " },
{IAN_PARAMETER_DECLARATION_1, "parameter_declaration->declaration_specifiers declarator " },
{IAN_PARAMETER_DECLARATION_2, "parameter_declaration->declaration_specifiers abstract_declarator " },
{IAN_PARAMETER_DECLARATION_3, "parameter_declaration->declaration_specifiers " },
{IAN_IDENTIFIER_LIST_1, "identifier_list->identifier " },
{IAN_IDENTIFIER_LIST_2, "identifier_list->identifier_list ',' identifier " },
{IAN_TYPE_NAME_1, "type_name->specifier_qualifier_list abstract_declarator " },
{IAN_TYPE_NAME_2, "type_name->specifier_qualifier_list " },
{IAN_ABSTRACT_DECLARATOR_1, "abstract_declarator->pointer direct_abstract_declarator " },
{IAN_ABSTRACT_DECLARATOR_2, "abstract_declarator->pointer " },
{IAN_ABSTRACT_DECLARATOR_3, "abstract_declarator->direct_abstract_declarator " },
{IAN_DIRECT_ABSTRACT_DECLARATOR_1, "direct_abstract_declarator->'(' abstract_declarator ')' " },
{IAN_DIRECT_ABSTRACT_DECLARATOR_2, "direct_abstract_declarator->'[' ']' " },
{IAN_DIRECT_ABSTRACT_DECLARATOR_3, "direct_abstract_declarator->'[' '*' ']' " },
{IAN_DIRECT_ABSTRACT_DECLARATOR_4, "direct_abstract_declarator->'[' STATIC type_qualifier_list assignment_expression ']' " },
{IAN_DIRECT_ABSTRACT_DECLARATOR_5, "direct_abstract_declarator->'[' STATIC assignment_expression ']' " },
{IAN_DIRECT_ABSTRACT_DECLARATOR_6, "direct_abstract_declarator->'[' type_qualifier_list STATIC assignment_expression ']' " },
{IAN_DIRECT_ABSTRACT_DECLARATOR_7, "direct_abstract_declarator->'[' type_qualifier_list assignment_expression ']' " },
{IAN_DIRECT_ABSTRACT_DECLARATOR_8, "direct_abstract_declarator->'[' type_qualifier_list ']' " },
{IAN_DIRECT_ABSTRACT_DECLARATOR_9, "direct_abstract_declarator->'[' assignment_expression ']' " },
{IAN_DIRECT_ABSTRACT_DECLARATOR_10, "direct_abstract_declarator->direct_abstract_declarator '[' ']' " },
{IAN_DIRECT_ABSTRACT_DECLARATOR_11, "direct_abstract_declarator->direct_abstract_declarator '[' '*' ']' " },
{IAN_DIRECT_ABSTRACT_DECLARATOR_12, "direct_abstract_declarator->direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']' " },
{IAN_DIRECT_ABSTRACT_DECLARATOR_13, "direct_abstract_declarator->direct_abstract_declarator '[' STATIC assignment_expression ']' " },
{IAN_DIRECT_ABSTRACT_DECLARATOR_14, "direct_abstract_declarator->direct_abstract_declarator '[' type_qualifier_list assignment_expression ']' " },
{IAN_DIRECT_ABSTRACT_DECLARATOR_15, "direct_abstract_declarator->direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']' " },
{IAN_DIRECT_ABSTRACT_DECLARATOR_16, "direct_abstract_declarator->direct_abstract_declarator '[' type_qualifier_list ']' " },
{IAN_DIRECT_ABSTRACT_DECLARATOR_17, "direct_abstract_declarator->direct_abstract_declarator '[' assignment_expression ']' " },
{IAN_DIRECT_ABSTRACT_DECLARATOR_18, "direct_abstract_declarator->'(' ')' " },
{IAN_DIRECT_ABSTRACT_DECLARATOR_19, "direct_abstract_declarator->'(' parameter_type_list ')' " },
{IAN_DIRECT_ABSTRACT_DECLARATOR_20, "direct_abstract_declarator->direct_abstract_declarator '(' ')' " },
{IAN_DIRECT_ABSTRACT_DECLARATOR_21, "direct_abstract_declarator->direct_abstract_declarator '(' parameter_type_list ')' " },
{IAN_INITIALIZER_1, "initializer->'{' initializer_list '}' " },
{IAN_INITIALIZER_2, "initializer->'{' initializer_list ',' '}' " },
{IAN_INITIALIZER_3, "initializer->assignment_expression " },
{IAN_INITIALIZER_LIST_1, "initializer_list->designation initializer " },
{IAN_INITIALIZER_LIST_2, "initializer_list->initializer " },
{IAN_INITIALIZER_LIST_3, "initializer_list->initializer_list ',' designation initializer " },
{IAN_INITIALIZER_LIST_4, "initializer_list->initializer_list ',' initializer " },
{IAN_DESIGNATION_1, "designation->designator_list '=' " },
{IAN_DESIGNATOR_LIST_1, "designator_list->designator " },
{IAN_DESIGNATOR_LIST_2, "designator_list->designator_list designator " },
{IAN_DESIGNATOR_1, "designator->'[' constant_expression ']' " },
{IAN_DESIGNATOR_2, "designator->'.' identifier " },
{IAN_STATIC_ASSERT_DECLARATION_1, "static_assert_declaration->STATIC_ASSERT '(' constant_expression ',' STRING_LITERAL ')' ';' " },
{IAN_STATEMENT_1, "statement->labeled_statement " },
{IAN_STATEMENT_2, "statement->compound_statement " },
{IAN_STATEMENT_3, "statement->expression_statement " },
{IAN_STATEMENT_4, "statement->selection_statement " },
{IAN_STATEMENT_5, "statement->iteration_statement " },
{IAN_STATEMENT_6, "statement->jump_statement " },
{IAN_LABELED_STATEMENT_1, "labeled_statement->identifier ':' statement " },
{IAN_LABELED_STATEMENT_2, "labeled_statement->CASE constant_expression ':' statement " },
{IAN_LABELED_STATEMENT_3, "labeled_statement->DEFAULT ':' statement " },
{IAN_COMPOUND_STATEMENT_1, "compound_statement->'{' '}' " },
{IAN_COMPOUND_STATEMENT_2, "compound_statement->'{' block_item_list '}' " },
{IAN_BLOCK_ITEM_LIST_1, "block_item_list->block_item " },
{IAN_BLOCK_ITEM_LIST_2, "block_item_list->block_item_list block_item " },
{IAN_BLOCK_ITEM_1, "block_item->declaration " },
{IAN_BLOCK_ITEM_2, "block_item->statement " },
{IAN_EXPRESSION_STATEMENT_1, "expression_statement->';' " },
{IAN_EXPRESSION_STATEMENT_2, "expression_statement->expression ';' " },
{IAN_SELECTION_STATEMENT_1, "selection_statement->IF '(' expression ')' statement ELSE statement " },
{IAN_SELECTION_STATEMENT_2, "selection_statement->IF '(' expression ')' statement " },
{IAN_SELECTION_STATEMENT_3, "selection_statement->SWITCH '(' expression ')' statement " },
{IAN_ITERATION_STATEMENT_1, "iteration_statement->WHILE '(' expression ')' statement " },
{IAN_ITERATION_STATEMENT_2, "iteration_statement->DO statement WHILE '(' expression ')' ';' " },
{IAN_ITERATION_STATEMENT_3, "iteration_statement->FOR '(' expression_statement expression_statement ')' statement " },
{IAN_ITERATION_STATEMENT_4, "iteration_statement->FOR '(' expression_statement expression_statement expression ')' statement " },
{IAN_ITERATION_STATEMENT_5, "iteration_statement->FOR '(' declaration expression_statement ')' statement " },
{IAN_ITERATION_STATEMENT_6, "iteration_statement->FOR '(' declaration expression_statement expression ')' statement " },
{IAN_JUMP_STATEMENT_1, "jump_statement->GOTO identifier ';' " },
{IAN_JUMP_STATEMENT_2, "jump_statement->CONTINUE ';' " },
{IAN_JUMP_STATEMENT_3, "jump_statement->BREAK ';' " },
{IAN_JUMP_STATEMENT_4, "jump_statement->RETURN ';' " },
{IAN_JUMP_STATEMENT_5, "jump_statement->RETURN expression ';' " },
{IAN_TRANSLATION_UNIT_1, "translation_unit->external_declaration " },
{IAN_TRANSLATION_UNIT_2, "translation_unit->translation_unit external_declaration " },
{IAN_FILE_1, "file->/*empty*/ " },
{IAN_FILE_2, "file->translation_unit " },
{IAN_EXTERNAL_DECLARATION_1, "external_declaration->function_definition " },
{IAN_EXTERNAL_DECLARATION_2, "external_declaration->declaration " },
{IAN_FUNCTION_DEFINITION_1, "function_definition->declaration_specifiers declarator declaration_list compound_statement " },
{IAN_FUNCTION_DEFINITION_2, "function_definition->declaration_specifiers declarator compound_statement " },
{IAN_DECLARATION_LIST_1, "declaration_list->declaration " },
{IAN_DECLARATION_LIST_2, "declaration_list->declaration_list declaration " },
{IAN_IDENTIFIER_1, "identifier->IDENTIFIER " },
{IAN_FUNCTION_ATTRIBUTE1_1, "function_attribute1->USING constant_expression " },
{IAN_FUNCTION_ATTRIBUTE1_2, "function_attribute1->REENTRANT " },
{IAN_FUNCTION_ATTRIBUTE1_3, "function_attribute1->INTERRUPT constant_expression " },
{IAN_FUNCTION_ATTRIBUTE1_4, "function_attribute1->REGPARAMS string " },
{IAN_FUNCTION_ATTRIBUTE2_1, "function_attribute2->function_attribute1 " },
{IAN_FUNCTION_ATTRIBUTE2_2, "function_attribute2->function_attribute1 function_attribute2 " },
{IAN_FUNCTION_ATTRIBUTE_1, "function_attribute->function_attribute2 " },
};


std::vector<T_DEBUG_LIST>g_elem_debug_str=
{
{Parser::token::IDENTIFIER, "IDENTIFIER"},
{Parser::token::I_CONSTANT, "I_CONSTANT"},
{Parser::token::F_CONSTANT, "F_CONSTANT"},
{Parser::token::STRING_LITERAL, "STRING_LITERAL"},
{Parser::token::FUNC_NAME, "FUNC_NAME"},
{Parser::token::SIZEOF, "SIZEOF"},
{Parser::token::PTR_OP, "PTR_OP"},
{Parser::token::INC_OP, "INC_OP"},
{Parser::token::DEC_OP, "DEC_OP"},
{Parser::token::LEFT_OP, "LEFT_OP"},
{Parser::token::RIGHT_OP, "RIGHT_OP"},
{Parser::token::ROTATE_RIGHT_OP, "ROTATE_RIGHT_OP"},
{Parser::token::ROTATE_LEFT_OP, "ROTATE_LEFT_OP"},
{Parser::token::LE_OP, "LE_OP"},
{Parser::token::GE_OP, "GE_OP"},
{Parser::token::EQ_OP, "EQ_OP"},
{Parser::token::NE_OP, "NE_OP"},
{Parser::token::AND_OP, "AND_OP"},
{Parser::token::OR_OP, "OR_OP"},
{Parser::token::MUL_ASSIGN, "MUL_ASSIGN"},
{Parser::token::DIV_ASSIGN, "DIV_ASSIGN"},
{Parser::token::MOD_ASSIGN, "MOD_ASSIGN"},
{Parser::token::ADD_ASSIGN, "ADD_ASSIGN"},
{Parser::token::SUB_ASSIGN, "SUB_ASSIGN"},
{Parser::token::LEFT_ASSIGN, "LEFT_ASSIGN"},
{Parser::token::RIGHT_ASSIGN, "RIGHT_ASSIGN"},
{Parser::token::AND_ASSIGN, "AND_ASSIGN"},
{Parser::token::XOR_ASSIGN, "XOR_ASSIGN"},
{Parser::token::OR_ASSIGN, "OR_ASSIGN"},
{Parser::token::TYPEDEF_NAME, "TYPEDEF_NAME"},
{Parser::token::ENUMERATION_CONSTANT, "ENUMERATION_CONSTANT"},
{Parser::token::TYPEDEF, "TYPEDEF"},
{Parser::token::EXTERN, "EXTERN"},
{Parser::token::STATIC, "STATIC"},
{Parser::token::AUTO, "AUTO"},
{Parser::token::REGISTER, "REGISTER"},
{Parser::token::INLINE, "INLINE"},
{Parser::token::CONST, "CONST"},
{Parser::token::RESTRICT, "RESTRICT"},
{Parser::token::VOLATILE, "VOLATILE"},
{Parser::token::BOOL, "BOOL"},
{Parser::token::CHAR, "CHAR"},
{Parser::token::SHORT, "SHORT"},
{Parser::token::INT, "INT"},
{Parser::token::LONG, "LONG"},
{Parser::token::SIGNED, "SIGNED"},
{Parser::token::UNSIGNED, "UNSIGNED"},
{Parser::token::FLOAT, "FLOAT"},
{Parser::token::DOUBLE, "DOUBLE"},
{Parser::token::VOID, "VOID"},
{Parser::token::COMPLEX, "COMPLEX"},
{Parser::token::IMAGINARY, "IMAGINARY"},
{Parser::token::STRUCT, "STRUCT"},
{Parser::token::UNION, "UNION"},
{Parser::token::ENUM, "ENUM"},
{Parser::token::ELLIPSIS, "ELLIPSIS"},
{Parser::token::CASE, "CASE"},
{Parser::token::DEFAULT, "DEFAULT"},
{Parser::token::IF, "IF"},
{Parser::token::ELSE, "ELSE"},
{Parser::token::SWITCH, "SWITCH"},
{Parser::token::WHILE, "WHILE"},
{Parser::token::DO, "DO"},
{Parser::token::FOR, "FOR"},
{Parser::token::GOTO, "GOTO"},
{Parser::token::CONTINUE, "CONTINUE"},
{Parser::token::BREAK, "BREAK"},
{Parser::token::RETURN, "RETURN"},
{Parser::token::ALIGNAS, "ALIGNAS"},
{Parser::token::ALIGNOF, "ALIGNOF"},
{Parser::token::ATOMIC, "ATOMIC"},
{Parser::token::GENERIC, "GENERIC"},
{Parser::token::NORETURN, "NORETURN"},
{Parser::token::STATIC_ASSERT, "STATIC_ASSERT"},
{Parser::token::THREAD_LOCAL, "THREAD_LOCAL"},
{Parser::token::SFR, "SFR"},
{Parser::token::BIT, "BIT"},
{Parser::token::SBIT, "SBIT"},
{Parser::token::SFR16, "SFR16"},
{Parser::token::SFR32, "SFR32"},
{Parser::token::INTERRUPT, "INTERRUPT"},
{Parser::token::USING, "USING"},
{Parser::token::REENTRANT, "REENTRANT"},
{Parser::token::REGPARAMS, "REGPARAMS"},
{Parser::token::STORAGE_SPEC_C51, "STORAGE_SPEC_C51"},
};
