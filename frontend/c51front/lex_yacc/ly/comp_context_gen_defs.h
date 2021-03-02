#ifndef AST_TO_ICODE_GEN_DEF_H
#define AST_TO_ICODE_GEN_DEF_H



class icode;
namespace NS_C512IR{

class comp_context;
class token_defs;

enum E_AST_TO_ICODE_GEN_DEF{
IAN_PRIMARY_EXPRESSION_1=0x1, //primary_expression->identifier 
IAN_PRIMARY_EXPRESSION_2=0x2, //primary_expression->constant 
IAN_PRIMARY_EXPRESSION_3=0x3, //primary_expression->string 
IAN_PRIMARY_EXPRESSION_4=0x4, //primary_expression->'(' expression ')' 
IAN_PRIMARY_EXPRESSION_5=0x5, //primary_expression->generic_selection 
IAN_CONSTANT_1=0x101, //constant->I_CONSTANT 
IAN_CONSTANT_2=0x102, //constant->F_CONSTANT 
IAN_CONSTANT_3=0x103, //constant->ENUMERATION_CONSTANT 
IAN_ENUMERATION_CONSTANT_1=0x201, //enumeration_constant->identifier 
IAN_STRING_1=0x301, //string->STRING_LITERAL 
IAN_STRING_2=0x302, //string->FUNC_NAME 
IAN_GENERIC_SELECTION_1=0x401, //generic_selection->GENERIC '(' assignment_expression ',' generic_assoc_list ')' 
IAN_GENERIC_ASSOC_LIST_1=0x501, //generic_assoc_list->generic_association 
IAN_GENERIC_ASSOC_LIST_2=0x502, //generic_assoc_list->generic_assoc_list ',' generic_association 
IAN_GENERIC_ASSOCIATION_1=0x601, //generic_association->type_name ':' assignment_expression 
IAN_GENERIC_ASSOCIATION_2=0x602, //generic_association->DEFAULT ':' assignment_expression 
IAN_POSTFIX_EXPRESSION_1=0x701, //postfix_expression->primary_expression 
IAN_POSTFIX_EXPRESSION_2=0x702, //postfix_expression->postfix_expression '[' expression ']' 
IAN_POSTFIX_EXPRESSION_3=0x703, //postfix_expression->postfix_expression '(' ')' 
IAN_POSTFIX_EXPRESSION_4=0x704, //postfix_expression->postfix_expression '(' argument_expression_list ')' 
IAN_POSTFIX_EXPRESSION_5=0x705, //postfix_expression->postfix_expression '.' identifier 
IAN_POSTFIX_EXPRESSION_6=0x706, //postfix_expression->postfix_expression PTR_OP identifier 
IAN_POSTFIX_EXPRESSION_7=0x707, //postfix_expression->postfix_expression INC_OP 
IAN_POSTFIX_EXPRESSION_8=0x708, //postfix_expression->postfix_expression DEC_OP 
IAN_POSTFIX_EXPRESSION_9=0x709, //postfix_expression->'(' type_name ')' '{' initializer_list '}' 
IAN_POSTFIX_EXPRESSION_10=0x70a, //postfix_expression->'(' type_name ')' '{' initializer_list ',' '}' 
IAN_ARGUMENT_EXPRESSION_LIST_1=0x801, //argument_expression_list->assignment_expression 
IAN_ARGUMENT_EXPRESSION_LIST_2=0x802, //argument_expression_list->argument_expression_list ',' assignment_expression 
IAN_UNARY_EXPRESSION_1=0x901, //unary_expression->postfix_expression 
IAN_UNARY_EXPRESSION_2=0x902, //unary_expression->INC_OP unary_expression 
IAN_UNARY_EXPRESSION_3=0x903, //unary_expression->DEC_OP unary_expression 
IAN_UNARY_EXPRESSION_4=0x904, //unary_expression->unary_operator cast_expression 
IAN_UNARY_EXPRESSION_5=0x905, //unary_expression->SIZEOF unary_expression 
IAN_UNARY_EXPRESSION_6=0x906, //unary_expression->SIZEOF '(' type_name ')' 
IAN_UNARY_EXPRESSION_7=0x907, //unary_expression->ALIGNOF '(' type_name ')' 
IAN_UNARY_OPERATOR_1=0xa01, //unary_operator->'&' 
IAN_UNARY_OPERATOR_2=0xa02, //unary_operator->'*' 
IAN_UNARY_OPERATOR_3=0xa03, //unary_operator->'+' 
IAN_UNARY_OPERATOR_4=0xa04, //unary_operator->'-' 
IAN_UNARY_OPERATOR_5=0xa05, //unary_operator->'~' 
IAN_UNARY_OPERATOR_6=0xa06, //unary_operator->'!' 
IAN_CAST_EXPRESSION_1=0xb01, //cast_expression->unary_expression 
IAN_CAST_EXPRESSION_2=0xb02, //cast_expression->'(' type_name ')' cast_expression 
IAN_MULTIPLICATIVE_EXPRESSION_1=0xc01, //multiplicative_expression->cast_expression 
IAN_MULTIPLICATIVE_EXPRESSION_2=0xc02, //multiplicative_expression->multiplicative_expression '*' cast_expression 
IAN_MULTIPLICATIVE_EXPRESSION_3=0xc03, //multiplicative_expression->multiplicative_expression '/' cast_expression 
IAN_MULTIPLICATIVE_EXPRESSION_4=0xc04, //multiplicative_expression->multiplicative_expression '%' cast_expression 
IAN_ADDITIVE_EXPRESSION_1=0xd01, //additive_expression->multiplicative_expression 
IAN_ADDITIVE_EXPRESSION_2=0xd02, //additive_expression->additive_expression '+' multiplicative_expression 
IAN_ADDITIVE_EXPRESSION_3=0xd03, //additive_expression->additive_expression '-' multiplicative_expression 
IAN_SHIFT_EXPRESSION_1=0xe01, //shift_expression->additive_expression 
IAN_SHIFT_EXPRESSION_2=0xe02, //shift_expression->shift_expression LEFT_OP additive_expression 
IAN_SHIFT_EXPRESSION_3=0xe03, //shift_expression->shift_expression RIGHT_OP additive_expression 
IAN_SHIFT_EXPRESSION_4=0xe04, //shift_expression->shift_expression ROTATE_LEFT_OP additive_expression 
IAN_SHIFT_EXPRESSION_5=0xe05, //shift_expression->shift_expression ROTATE_RIGHT_OP additive_expression 
IAN_RELATIONAL_EXPRESSION_1=0xf01, //relational_expression->shift_expression 
IAN_RELATIONAL_EXPRESSION_2=0xf02, //relational_expression->relational_expression '<' shift_expression 
IAN_RELATIONAL_EXPRESSION_3=0xf03, //relational_expression->relational_expression '>' shift_expression 
IAN_RELATIONAL_EXPRESSION_4=0xf04, //relational_expression->relational_expression LE_OP shift_expression 
IAN_RELATIONAL_EXPRESSION_5=0xf05, //relational_expression->relational_expression GE_OP shift_expression 
IAN_EQUALITY_EXPRESSION_1=0x1001, //equality_expression->relational_expression 
IAN_EQUALITY_EXPRESSION_2=0x1002, //equality_expression->equality_expression EQ_OP relational_expression 
IAN_EQUALITY_EXPRESSION_3=0x1003, //equality_expression->equality_expression NE_OP relational_expression 
IAN_AND_EXPRESSION_1=0x1101, //and_expression->equality_expression 
IAN_AND_EXPRESSION_2=0x1102, //and_expression->and_expression '&' equality_expression 
IAN_EXCLUSIVE_OR_EXPRESSION_1=0x1201, //exclusive_or_expression->and_expression 
IAN_EXCLUSIVE_OR_EXPRESSION_2=0x1202, //exclusive_or_expression->exclusive_or_expression '^' and_expression 
IAN_INCLUSIVE_OR_EXPRESSION_1=0x1301, //inclusive_or_expression->exclusive_or_expression 
IAN_INCLUSIVE_OR_EXPRESSION_2=0x1302, //inclusive_or_expression->inclusive_or_expression '|' exclusive_or_expression 
IAN_LOGICAL_AND_EXPRESSION_1=0x1401, //logical_and_expression->inclusive_or_expression 
IAN_LOGICAL_AND_EXPRESSION_2=0x1402, //logical_and_expression->logical_and_expression AND_OP inclusive_or_expression 
IAN_LOGICAL_OR_EXPRESSION_1=0x1501, //logical_or_expression->logical_and_expression 
IAN_LOGICAL_OR_EXPRESSION_2=0x1502, //logical_or_expression->logical_or_expression OR_OP logical_and_expression 
IAN_CONDITIONAL_EXPRESSION_1=0x1601, //conditional_expression->logical_or_expression 
IAN_CONDITIONAL_EXPRESSION_2=0x1602, //conditional_expression->logical_or_expression '?' expression ':' conditional_expression 
IAN_ASSIGNMENT_EXPRESSION_1=0x1701, //assignment_expression->conditional_expression 
IAN_ASSIGNMENT_EXPRESSION_2=0x1702, //assignment_expression->unary_expression assignment_operator assignment_expression 
IAN_ASSIGNMENT_OPERATOR_1=0x1801, //assignment_operator->'=' 
IAN_ASSIGNMENT_OPERATOR_2=0x1802, //assignment_operator->MUL_ASSIGN 
IAN_ASSIGNMENT_OPERATOR_3=0x1803, //assignment_operator->DIV_ASSIGN 
IAN_ASSIGNMENT_OPERATOR_4=0x1804, //assignment_operator->MOD_ASSIGN 
IAN_ASSIGNMENT_OPERATOR_5=0x1805, //assignment_operator->ADD_ASSIGN 
IAN_ASSIGNMENT_OPERATOR_6=0x1806, //assignment_operator->SUB_ASSIGN 
IAN_ASSIGNMENT_OPERATOR_7=0x1807, //assignment_operator->LEFT_ASSIGN 
IAN_ASSIGNMENT_OPERATOR_8=0x1808, //assignment_operator->RIGHT_ASSIGN 
IAN_ASSIGNMENT_OPERATOR_9=0x1809, //assignment_operator->AND_ASSIGN 
IAN_ASSIGNMENT_OPERATOR_10=0x180a, //assignment_operator->XOR_ASSIGN 
IAN_ASSIGNMENT_OPERATOR_11=0x180b, //assignment_operator->OR_ASSIGN 
IAN_EXPRESSION_1=0x1901, //expression->assignment_expression 
IAN_EXPRESSION_2=0x1902, //expression->expression ',' assignment_expression 
IAN_CONSTANT_EXPRESSION_1=0x1a01, //constant_expression->conditional_expression 
IAN_DECLARATION_1=0x1b01, //declaration->declaration_specifiers ';' 
IAN_DECLARATION_2=0x1b02, //declaration->declaration_specifiers init_declarator_list ';' 
IAN_DECLARATION_3=0x1b03, //declaration->static_assert_declaration 
IAN_DECLARATION_SPECIFIERS_1=0x1c01, //declaration_specifiers->declaration_specifiers_ 
IAN_DECLARATION_SPECIFIERS__1=0x1d01, //declaration_specifiers_->storage_class_specifier declaration_specifiers_ 
IAN_DECLARATION_SPECIFIERS__2=0x1d02, //declaration_specifiers_->storage_class_specifier 
IAN_DECLARATION_SPECIFIERS__3=0x1d03, //declaration_specifiers_->type_specifier declaration_specifiers_ 
IAN_DECLARATION_SPECIFIERS__4=0x1d04, //declaration_specifiers_->type_specifier 
IAN_DECLARATION_SPECIFIERS__5=0x1d05, //declaration_specifiers_->type_qualifier declaration_specifiers_ 
IAN_DECLARATION_SPECIFIERS__6=0x1d06, //declaration_specifiers_->type_qualifier 
IAN_DECLARATION_SPECIFIERS__7=0x1d07, //declaration_specifiers_->function_specifier declaration_specifiers_ 
IAN_DECLARATION_SPECIFIERS__8=0x1d08, //declaration_specifiers_->function_specifier 
IAN_DECLARATION_SPECIFIERS__9=0x1d09, //declaration_specifiers_->alignment_specifier declaration_specifiers_ 
IAN_DECLARATION_SPECIFIERS__10=0x1d0a, //declaration_specifiers_->alignment_specifier 
IAN_INIT_DECLARATOR_LIST_1=0x1e01, //init_declarator_list->init_declarator 
IAN_INIT_DECLARATOR_LIST_2=0x1e02, //init_declarator_list->init_declarator_list ',' init_declarator 
IAN_INIT_DECLARATOR_1=0x1f01, //init_declarator->declarator '=' initializer 
IAN_INIT_DECLARATOR_2=0x1f02, //init_declarator->declarator 
IAN_STORAGE_CLASS_SPECIFIER_1=0x2001, //storage_class_specifier->TYPEDEF 
IAN_STORAGE_CLASS_SPECIFIER_2=0x2002, //storage_class_specifier->EXTERN 
IAN_STORAGE_CLASS_SPECIFIER_3=0x2003, //storage_class_specifier->STATIC 
IAN_STORAGE_CLASS_SPECIFIER_4=0x2004, //storage_class_specifier->THREAD_LOCAL 
IAN_STORAGE_CLASS_SPECIFIER_5=0x2005, //storage_class_specifier->AUTO 
IAN_STORAGE_CLASS_SPECIFIER_6=0x2006, //storage_class_specifier->REGISTER 
IAN_STORAGE_CLASS_SPECIFIER_7=0x2007, //storage_class_specifier->STORAGE_SPEC_C51 
IAN_TYPE_SPECIFIER_1=0x2101, //type_specifier->VOID 
IAN_TYPE_SPECIFIER_2=0x2102, //type_specifier->CHAR 
IAN_TYPE_SPECIFIER_3=0x2103, //type_specifier->SHORT 
IAN_TYPE_SPECIFIER_4=0x2104, //type_specifier->INT 
IAN_TYPE_SPECIFIER_5=0x2105, //type_specifier->LONG 
IAN_TYPE_SPECIFIER_6=0x2106, //type_specifier->FLOAT 
IAN_TYPE_SPECIFIER_7=0x2107, //type_specifier->DOUBLE 
IAN_TYPE_SPECIFIER_8=0x2108, //type_specifier->SIGNED 
IAN_TYPE_SPECIFIER_9=0x2109, //type_specifier->UNSIGNED 
IAN_TYPE_SPECIFIER_10=0x210a, //type_specifier->BOOL 
IAN_TYPE_SPECIFIER_11=0x210b, //type_specifier->COMPLEX 
IAN_TYPE_SPECIFIER_12=0x210c, //type_specifier->IMAGINARY 
IAN_TYPE_SPECIFIER_13=0x210d, //type_specifier->atomic_type_specifier 
IAN_TYPE_SPECIFIER_14=0x210e, //type_specifier->struct_or_union_specifier 
IAN_TYPE_SPECIFIER_15=0x210f, //type_specifier->enum_specifier 
IAN_TYPE_SPECIFIER_16=0x2110, //type_specifier->TYPEDEF_NAME 
IAN_TYPE_SPECIFIER_17=0x2111, //type_specifier->SFR 
IAN_TYPE_SPECIFIER_18=0x2112, //type_specifier->BIT 
IAN_TYPE_SPECIFIER_19=0x2113, //type_specifier->SBIT 
IAN_TYPE_SPECIFIER_20=0x2114, //type_specifier->SFR16 
IAN_TYPE_SPECIFIER_21=0x2115, //type_specifier->SFR32 
IAN_STRUCT_OR_UNION_SPECIFIER_1=0x2201, //struct_or_union_specifier->struct_or_union '{' struct_declaration_list '}' 
IAN_STRUCT_OR_UNION_SPECIFIER_2=0x2202, //struct_or_union_specifier->struct_or_union identifier '{' struct_declaration_list '}' 
IAN_STRUCT_OR_UNION_SPECIFIER_3=0x2203, //struct_or_union_specifier->struct_or_union identifier 
IAN_STRUCT_OR_UNION_1=0x2301, //struct_or_union->STRUCT 
IAN_STRUCT_OR_UNION_2=0x2302, //struct_or_union->UNION 
IAN_STRUCT_DECLARATION_LIST_1=0x2401, //struct_declaration_list->struct_declaration 
IAN_STRUCT_DECLARATION_LIST_2=0x2402, //struct_declaration_list->struct_declaration_list struct_declaration 
IAN_STRUCT_DECLARATION_1=0x2501, //struct_declaration->specifier_qualifier_list ';' 
IAN_STRUCT_DECLARATION_2=0x2502, //struct_declaration->specifier_qualifier_list struct_declarator_list ';' 
IAN_STRUCT_DECLARATION_3=0x2503, //struct_declaration->static_assert_declaration 
IAN_SPECIFIER_QUALIFIER_LIST_1=0x2601, //specifier_qualifier_list->type_specifier specifier_qualifier_list 
IAN_SPECIFIER_QUALIFIER_LIST_2=0x2602, //specifier_qualifier_list->type_specifier 
IAN_SPECIFIER_QUALIFIER_LIST_3=0x2603, //specifier_qualifier_list->type_qualifier specifier_qualifier_list 
IAN_SPECIFIER_QUALIFIER_LIST_4=0x2604, //specifier_qualifier_list->type_qualifier 
IAN_STRUCT_DECLARATOR_LIST_1=0x2701, //struct_declarator_list->struct_declarator 
IAN_STRUCT_DECLARATOR_LIST_2=0x2702, //struct_declarator_list->struct_declarator_list ',' struct_declarator 
IAN_STRUCT_DECLARATOR_1=0x2801, //struct_declarator->':' constant_expression 
IAN_STRUCT_DECLARATOR_2=0x2802, //struct_declarator->declarator ':' constant_expression 
IAN_STRUCT_DECLARATOR_3=0x2803, //struct_declarator->declarator 
IAN_ENUM_SPECIFIER_1=0x2901, //enum_specifier->ENUM '{' enumerator_list '}' 
IAN_ENUM_SPECIFIER_2=0x2902, //enum_specifier->ENUM '{' enumerator_list ',' '}' 
IAN_ENUM_SPECIFIER_3=0x2903, //enum_specifier->ENUM identifier '{' enumerator_list '}' 
IAN_ENUM_SPECIFIER_4=0x2904, //enum_specifier->ENUM identifier '{' enumerator_list ',' '}' 
IAN_ENUM_SPECIFIER_5=0x2905, //enum_specifier->ENUM identifier 
IAN_ENUMERATOR_LIST_1=0x2a01, //enumerator_list->enumerator 
IAN_ENUMERATOR_LIST_2=0x2a02, //enumerator_list->enumerator_list ',' enumerator 
IAN_ENUMERATOR_1=0x2b01, //enumerator->enumeration_constant '=' constant_expression 
IAN_ENUMERATOR_2=0x2b02, //enumerator->enumeration_constant 
IAN_ATOMIC_TYPE_SPECIFIER_1=0x2c01, //atomic_type_specifier->ATOMIC '(' type_name ')' 
IAN_TYPE_QUALIFIER_1=0x2d01, //type_qualifier->CONST 
IAN_TYPE_QUALIFIER_2=0x2d02, //type_qualifier->RESTRICT 
IAN_TYPE_QUALIFIER_3=0x2d03, //type_qualifier->VOLATILE 
IAN_TYPE_QUALIFIER_4=0x2d04, //type_qualifier->ATOMIC 
IAN_FUNCTION_SPECIFIER_1=0x2e01, //function_specifier->INLINE 
IAN_FUNCTION_SPECIFIER_2=0x2e02, //function_specifier->NORETURN 
IAN_ALIGNMENT_SPECIFIER_1=0x2f01, //alignment_specifier->ALIGNAS '(' type_name ')' 
IAN_ALIGNMENT_SPECIFIER_2=0x2f02, //alignment_specifier->ALIGNAS '(' constant_expression ')' 
IAN_DECLARATOR_1=0x3001, //declarator->pointer direct_declarator 
IAN_DECLARATOR_2=0x3002, //declarator->direct_declarator 
IAN_DIRECT_DECLARATOR_BASE_1=0x3101, //direct_declarator_base->identifier 
IAN_DIRECT_DECLARATOR_BASE_2=0x3102, //direct_declarator_base->'(' declarator ')' 
IAN_DIRECT_DECLARATOR_ARRAY_1=0x3201, //direct_declarator_array->direct_declarator_base 
IAN_DIRECT_DECLARATOR_ARRAY_2=0x3202, //direct_declarator_array->direct_declarator_array '[' ']' 
IAN_DIRECT_DECLARATOR_ARRAY_3=0x3203, //direct_declarator_array->direct_declarator_array '[' '*' ']' 
IAN_DIRECT_DECLARATOR_ARRAY_4=0x3204, //direct_declarator_array->direct_declarator_array '[' STATIC type_qualifier_list assignment_expression ']' 
IAN_DIRECT_DECLARATOR_ARRAY_5=0x3205, //direct_declarator_array->direct_declarator_array '[' STATIC assignment_expression ']' 
IAN_DIRECT_DECLARATOR_ARRAY_6=0x3206, //direct_declarator_array->direct_declarator_array '[' type_qualifier_list '*' ']' 
IAN_DIRECT_DECLARATOR_ARRAY_7=0x3207, //direct_declarator_array->direct_declarator_array '[' type_qualifier_list STATIC assignment_expression ']' 
IAN_DIRECT_DECLARATOR_ARRAY_8=0x3208, //direct_declarator_array->direct_declarator_array '[' type_qualifier_list assignment_expression ']' 
IAN_DIRECT_DECLARATOR_ARRAY_9=0x3209, //direct_declarator_array->direct_declarator_array '[' type_qualifier_list ']' 
IAN_DIRECT_DECLARATOR_ARRAY_10=0x320a, //direct_declarator_array->direct_declarator_array '[' assignment_expression ']' 
IAN_DIRECT_DECLARATOR_FUNCTION1_1=0x3301, //direct_declarator_function1->direct_declarator_array 
IAN_DIRECT_DECLARATOR_FUNCTION1_2=0x3302, //direct_declarator_function1->direct_declarator_function1 '(' parameter_type_list ')' 
IAN_DIRECT_DECLARATOR_FUNCTION1_3=0x3303, //direct_declarator_function1->direct_declarator_function1 '(' ')' 
IAN_DIRECT_DECLARATOR_FUNCTION1_4=0x3304, //direct_declarator_function1->direct_declarator_function1 '(' identifier_list ')' 
IAN_DIRECT_DECLARATOR_FUNCTION2_1=0x3401, //direct_declarator_function2->direct_declarator_function1 
IAN_DIRECT_DECLARATOR_FUNCTION2_2=0x3402, //direct_declarator_function2->direct_declarator_function1 function_attribute 
IAN_DIRECT_DECLARATOR_FUNCTION_1=0x3501, //direct_declarator_function->direct_declarator_function2 
IAN_DIRECT_DECLARATOR_1=0x3601, //direct_declarator->direct_declarator_function 
IAN_POINTER_1=0x3701, //pointer->'*' type_qualifier_list pointer 
IAN_POINTER_2=0x3702, //pointer->'*' type_qualifier_list 
IAN_POINTER_3=0x3703, //pointer->'*' pointer 
IAN_POINTER_4=0x3704, //pointer->'*' 
IAN_TYPE_QUALIFIER_LIST_1=0x3801, //type_qualifier_list->type_qualifier 
IAN_TYPE_QUALIFIER_LIST_2=0x3802, //type_qualifier_list->type_qualifier_list type_qualifier 
IAN_PARAMETER_TYPE_LIST_1=0x3901, //parameter_type_list->parameter_list ',' ELLIPSIS 
IAN_PARAMETER_TYPE_LIST_2=0x3902, //parameter_type_list->parameter_list 
IAN_PARAMETER_LIST_1=0x3a01, //parameter_list->parameter_declaration 
IAN_PARAMETER_LIST_2=0x3a02, //parameter_list->parameter_list ',' parameter_declaration 
IAN_PARAMETER_DECLARATION_1=0x3b01, //parameter_declaration->declaration_specifiers declarator 
IAN_PARAMETER_DECLARATION_2=0x3b02, //parameter_declaration->declaration_specifiers abstract_declarator 
IAN_PARAMETER_DECLARATION_3=0x3b03, //parameter_declaration->declaration_specifiers 
IAN_IDENTIFIER_LIST_1=0x3c01, //identifier_list->identifier 
IAN_IDENTIFIER_LIST_2=0x3c02, //identifier_list->identifier_list ',' identifier 
IAN_TYPE_NAME_1=0x3d01, //type_name->specifier_qualifier_list abstract_declarator 
IAN_TYPE_NAME_2=0x3d02, //type_name->specifier_qualifier_list 
IAN_ABSTRACT_DECLARATOR_1=0x3e01, //abstract_declarator->pointer direct_abstract_declarator 
IAN_ABSTRACT_DECLARATOR_2=0x3e02, //abstract_declarator->pointer 
IAN_ABSTRACT_DECLARATOR_3=0x3e03, //abstract_declarator->direct_abstract_declarator 
IAN_DIRECT_ABSTRACT_DECLARATOR_1=0x3f01, //direct_abstract_declarator->'(' abstract_declarator ')' 
IAN_DIRECT_ABSTRACT_DECLARATOR_2=0x3f02, //direct_abstract_declarator->'[' ']' 
IAN_DIRECT_ABSTRACT_DECLARATOR_3=0x3f03, //direct_abstract_declarator->'[' '*' ']' 
IAN_DIRECT_ABSTRACT_DECLARATOR_4=0x3f04, //direct_abstract_declarator->'[' STATIC type_qualifier_list assignment_expression ']' 
IAN_DIRECT_ABSTRACT_DECLARATOR_5=0x3f05, //direct_abstract_declarator->'[' STATIC assignment_expression ']' 
IAN_DIRECT_ABSTRACT_DECLARATOR_6=0x3f06, //direct_abstract_declarator->'[' type_qualifier_list STATIC assignment_expression ']' 
IAN_DIRECT_ABSTRACT_DECLARATOR_7=0x3f07, //direct_abstract_declarator->'[' type_qualifier_list assignment_expression ']' 
IAN_DIRECT_ABSTRACT_DECLARATOR_8=0x3f08, //direct_abstract_declarator->'[' type_qualifier_list ']' 
IAN_DIRECT_ABSTRACT_DECLARATOR_9=0x3f09, //direct_abstract_declarator->'[' assignment_expression ']' 
IAN_DIRECT_ABSTRACT_DECLARATOR_10=0x3f0a, //direct_abstract_declarator->direct_abstract_declarator '[' ']' 
IAN_DIRECT_ABSTRACT_DECLARATOR_11=0x3f0b, //direct_abstract_declarator->direct_abstract_declarator '[' '*' ']' 
IAN_DIRECT_ABSTRACT_DECLARATOR_12=0x3f0c, //direct_abstract_declarator->direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']' 
IAN_DIRECT_ABSTRACT_DECLARATOR_13=0x3f0d, //direct_abstract_declarator->direct_abstract_declarator '[' STATIC assignment_expression ']' 
IAN_DIRECT_ABSTRACT_DECLARATOR_14=0x3f0e, //direct_abstract_declarator->direct_abstract_declarator '[' type_qualifier_list assignment_expression ']' 
IAN_DIRECT_ABSTRACT_DECLARATOR_15=0x3f0f, //direct_abstract_declarator->direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']' 
IAN_DIRECT_ABSTRACT_DECLARATOR_16=0x3f10, //direct_abstract_declarator->direct_abstract_declarator '[' type_qualifier_list ']' 
IAN_DIRECT_ABSTRACT_DECLARATOR_17=0x3f11, //direct_abstract_declarator->direct_abstract_declarator '[' assignment_expression ']' 
IAN_DIRECT_ABSTRACT_DECLARATOR_18=0x3f12, //direct_abstract_declarator->'(' ')' 
IAN_DIRECT_ABSTRACT_DECLARATOR_19=0x3f13, //direct_abstract_declarator->'(' parameter_type_list ')' 
IAN_DIRECT_ABSTRACT_DECLARATOR_20=0x3f14, //direct_abstract_declarator->direct_abstract_declarator '(' ')' 
IAN_DIRECT_ABSTRACT_DECLARATOR_21=0x3f15, //direct_abstract_declarator->direct_abstract_declarator '(' parameter_type_list ')' 
IAN_INITIALIZER_1=0x4001, //initializer->'{' initializer_list '}' 
IAN_INITIALIZER_2=0x4002, //initializer->'{' initializer_list ',' '}' 
IAN_INITIALIZER_3=0x4003, //initializer->assignment_expression 
IAN_INITIALIZER_LIST_1=0x4101, //initializer_list->designation initializer 
IAN_INITIALIZER_LIST_2=0x4102, //initializer_list->initializer 
IAN_INITIALIZER_LIST_3=0x4103, //initializer_list->initializer_list ',' designation initializer 
IAN_INITIALIZER_LIST_4=0x4104, //initializer_list->initializer_list ',' initializer 
IAN_DESIGNATION_1=0x4201, //designation->designator_list '=' 
IAN_DESIGNATOR_LIST_1=0x4301, //designator_list->designator 
IAN_DESIGNATOR_LIST_2=0x4302, //designator_list->designator_list designator 
IAN_DESIGNATOR_1=0x4401, //designator->'[' constant_expression ']' 
IAN_DESIGNATOR_2=0x4402, //designator->'.' identifier 
IAN_STATIC_ASSERT_DECLARATION_1=0x4501, //static_assert_declaration->STATIC_ASSERT '(' constant_expression ',' STRING_LITERAL ')' ';' 
IAN_STATEMENT_1=0x4601, //statement->labeled_statement 
IAN_STATEMENT_2=0x4602, //statement->compound_statement 
IAN_STATEMENT_3=0x4603, //statement->expression_statement 
IAN_STATEMENT_4=0x4604, //statement->selection_statement 
IAN_STATEMENT_5=0x4605, //statement->iteration_statement 
IAN_STATEMENT_6=0x4606, //statement->jump_statement 
IAN_LABELED_STATEMENT_1=0x4701, //labeled_statement->identifier ':' statement 
IAN_LABELED_STATEMENT_2=0x4702, //labeled_statement->CASE constant_expression ':' statement 
IAN_LABELED_STATEMENT_3=0x4703, //labeled_statement->DEFAULT ':' statement 
IAN_COMPOUND_STATEMENT_1=0x4801, //compound_statement->'{' '}' 
IAN_COMPOUND_STATEMENT_2=0x4802, //compound_statement->'{' block_item_list '}' 
IAN_BLOCK_ITEM_LIST_1=0x4901, //block_item_list->block_item 
IAN_BLOCK_ITEM_LIST_2=0x4902, //block_item_list->block_item_list block_item 
IAN_BLOCK_ITEM_1=0x4a01, //block_item->declaration 
IAN_BLOCK_ITEM_2=0x4a02, //block_item->statement 
IAN_EXPRESSION_STATEMENT_1=0x4b01, //expression_statement->';' 
IAN_EXPRESSION_STATEMENT_2=0x4b02, //expression_statement->expression ';' 
IAN_SELECTION_STATEMENT_1=0x4c01, //selection_statement->IF '(' expression ')' statement ELSE statement 
IAN_SELECTION_STATEMENT_2=0x4c02, //selection_statement->IF '(' expression ')' statement 
IAN_SELECTION_STATEMENT_3=0x4c03, //selection_statement->SWITCH '(' expression ')' statement 
IAN_ITERATION_STATEMENT_1=0x4d01, //iteration_statement->WHILE '(' expression ')' statement 
IAN_ITERATION_STATEMENT_2=0x4d02, //iteration_statement->DO statement WHILE '(' expression ')' ';' 
IAN_ITERATION_STATEMENT_3=0x4d03, //iteration_statement->FOR '(' expression_statement expression_statement ')' statement 
IAN_ITERATION_STATEMENT_4=0x4d04, //iteration_statement->FOR '(' expression_statement expression_statement expression ')' statement 
IAN_ITERATION_STATEMENT_5=0x4d05, //iteration_statement->FOR '(' declaration expression_statement ')' statement 
IAN_ITERATION_STATEMENT_6=0x4d06, //iteration_statement->FOR '(' declaration expression_statement expression ')' statement 
IAN_JUMP_STATEMENT_1=0x4e01, //jump_statement->GOTO identifier ';' 
IAN_JUMP_STATEMENT_2=0x4e02, //jump_statement->CONTINUE ';' 
IAN_JUMP_STATEMENT_3=0x4e03, //jump_statement->BREAK ';' 
IAN_JUMP_STATEMENT_4=0x4e04, //jump_statement->RETURN ';' 
IAN_JUMP_STATEMENT_5=0x4e05, //jump_statement->RETURN expression ';' 
IAN_TRANSLATION_UNIT_1=0x4f01, //translation_unit->external_declaration 
IAN_TRANSLATION_UNIT_2=0x4f02, //translation_unit->translation_unit external_declaration 
IAN_FILE_1=0x5001, //file->/*empty*/ 
IAN_FILE_2=0x5002, //file->translation_unit 
IAN_EXTERNAL_DECLARATION_1=0x5101, //external_declaration->function_definition 
IAN_EXTERNAL_DECLARATION_2=0x5102, //external_declaration->declaration 
IAN_FUNCTION_DEFINITION_1=0x5201, //function_definition->declaration_specifiers declarator declaration_list compound_statement 
IAN_FUNCTION_DEFINITION_2=0x5202, //function_definition->declaration_specifiers declarator compound_statement 
IAN_DECLARATION_LIST_1=0x5301, //declaration_list->declaration 
IAN_DECLARATION_LIST_2=0x5302, //declaration_list->declaration_list declaration 
IAN_IDENTIFIER_1=0x5401, //identifier->IDENTIFIER 
IAN_FUNCTION_ATTRIBUTE1_1=0x5501, //function_attribute1->USING constant_expression 
IAN_FUNCTION_ATTRIBUTE1_2=0x5502, //function_attribute1->REENTRANT 
IAN_FUNCTION_ATTRIBUTE1_3=0x5503, //function_attribute1->INTERRUPT constant_expression 
IAN_FUNCTION_ATTRIBUTE1_4=0x5504, //function_attribute1->REGPARAMS string 
IAN_FUNCTION_ATTRIBUTE2_1=0x5601, //function_attribute2->function_attribute1 
IAN_FUNCTION_ATTRIBUTE2_2=0x5602, //function_attribute2->function_attribute1 function_attribute2 
IAN_FUNCTION_ATTRIBUTE_1=0x5701, //function_attribute->function_attribute2 
};

icode *  func_IAN_PRIMARY_EXPRESSION_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_PRIMARY_EXPRESSION_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_PRIMARY_EXPRESSION_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_PRIMARY_EXPRESSION_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_PRIMARY_EXPRESSION_5(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_CONSTANT_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_CONSTANT_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_CONSTANT_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ENUMERATION_CONSTANT_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_STRING_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_STRING_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_GENERIC_SELECTION_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_GENERIC_ASSOC_LIST_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_GENERIC_ASSOC_LIST_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_GENERIC_ASSOCIATION_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_GENERIC_ASSOCIATION_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_POSTFIX_EXPRESSION_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_POSTFIX_EXPRESSION_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_POSTFIX_EXPRESSION_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_POSTFIX_EXPRESSION_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_POSTFIX_EXPRESSION_5(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_POSTFIX_EXPRESSION_6(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_POSTFIX_EXPRESSION_7(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_POSTFIX_EXPRESSION_8(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_POSTFIX_EXPRESSION_9(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_POSTFIX_EXPRESSION_10(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ARGUMENT_EXPRESSION_LIST_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ARGUMENT_EXPRESSION_LIST_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_UNARY_EXPRESSION_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_UNARY_EXPRESSION_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_UNARY_EXPRESSION_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_UNARY_EXPRESSION_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_UNARY_EXPRESSION_5(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_UNARY_EXPRESSION_6(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_UNARY_EXPRESSION_7(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_UNARY_OPERATOR_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_UNARY_OPERATOR_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_UNARY_OPERATOR_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_UNARY_OPERATOR_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_UNARY_OPERATOR_5(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_UNARY_OPERATOR_6(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_CAST_EXPRESSION_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_CAST_EXPRESSION_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_MULTIPLICATIVE_EXPRESSION_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_MULTIPLICATIVE_EXPRESSION_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_MULTIPLICATIVE_EXPRESSION_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_MULTIPLICATIVE_EXPRESSION_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ADDITIVE_EXPRESSION_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ADDITIVE_EXPRESSION_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ADDITIVE_EXPRESSION_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_SHIFT_EXPRESSION_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_SHIFT_EXPRESSION_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_SHIFT_EXPRESSION_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_SHIFT_EXPRESSION_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_SHIFT_EXPRESSION_5(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_RELATIONAL_EXPRESSION_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_RELATIONAL_EXPRESSION_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_RELATIONAL_EXPRESSION_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_RELATIONAL_EXPRESSION_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_RELATIONAL_EXPRESSION_5(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_EQUALITY_EXPRESSION_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_EQUALITY_EXPRESSION_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_EQUALITY_EXPRESSION_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_AND_EXPRESSION_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_AND_EXPRESSION_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_EXCLUSIVE_OR_EXPRESSION_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_EXCLUSIVE_OR_EXPRESSION_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_INCLUSIVE_OR_EXPRESSION_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_INCLUSIVE_OR_EXPRESSION_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_LOGICAL_AND_EXPRESSION_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_LOGICAL_AND_EXPRESSION_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_LOGICAL_OR_EXPRESSION_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_LOGICAL_OR_EXPRESSION_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_CONDITIONAL_EXPRESSION_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_CONDITIONAL_EXPRESSION_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ASSIGNMENT_EXPRESSION_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ASSIGNMENT_EXPRESSION_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ASSIGNMENT_OPERATOR_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ASSIGNMENT_OPERATOR_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ASSIGNMENT_OPERATOR_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ASSIGNMENT_OPERATOR_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ASSIGNMENT_OPERATOR_5(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ASSIGNMENT_OPERATOR_6(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ASSIGNMENT_OPERATOR_7(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ASSIGNMENT_OPERATOR_8(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ASSIGNMENT_OPERATOR_9(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ASSIGNMENT_OPERATOR_10(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ASSIGNMENT_OPERATOR_11(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_EXPRESSION_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_EXPRESSION_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_CONSTANT_EXPRESSION_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DECLARATION_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DECLARATION_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DECLARATION_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DECLARATION_SPECIFIERS_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DECLARATION_SPECIFIERS__1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DECLARATION_SPECIFIERS__2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DECLARATION_SPECIFIERS__3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DECLARATION_SPECIFIERS__4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DECLARATION_SPECIFIERS__5(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DECLARATION_SPECIFIERS__6(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DECLARATION_SPECIFIERS__7(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DECLARATION_SPECIFIERS__8(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DECLARATION_SPECIFIERS__9(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DECLARATION_SPECIFIERS__10(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_INIT_DECLARATOR_LIST_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_INIT_DECLARATOR_LIST_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_INIT_DECLARATOR_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_INIT_DECLARATOR_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_STORAGE_CLASS_SPECIFIER_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_STORAGE_CLASS_SPECIFIER_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_STORAGE_CLASS_SPECIFIER_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_STORAGE_CLASS_SPECIFIER_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_STORAGE_CLASS_SPECIFIER_5(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_STORAGE_CLASS_SPECIFIER_6(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_STORAGE_CLASS_SPECIFIER_7(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_TYPE_SPECIFIER_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_TYPE_SPECIFIER_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_TYPE_SPECIFIER_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_TYPE_SPECIFIER_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_TYPE_SPECIFIER_5(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_TYPE_SPECIFIER_6(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_TYPE_SPECIFIER_7(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_TYPE_SPECIFIER_8(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_TYPE_SPECIFIER_9(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_TYPE_SPECIFIER_10(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_TYPE_SPECIFIER_11(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_TYPE_SPECIFIER_12(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_TYPE_SPECIFIER_13(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_TYPE_SPECIFIER_14(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_TYPE_SPECIFIER_15(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_TYPE_SPECIFIER_16(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_TYPE_SPECIFIER_17(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_TYPE_SPECIFIER_18(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_TYPE_SPECIFIER_19(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_TYPE_SPECIFIER_20(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_TYPE_SPECIFIER_21(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_STRUCT_OR_UNION_SPECIFIER_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_STRUCT_OR_UNION_SPECIFIER_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_STRUCT_OR_UNION_SPECIFIER_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_STRUCT_OR_UNION_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_STRUCT_OR_UNION_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_STRUCT_DECLARATION_LIST_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_STRUCT_DECLARATION_LIST_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_STRUCT_DECLARATION_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_STRUCT_DECLARATION_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_STRUCT_DECLARATION_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_SPECIFIER_QUALIFIER_LIST_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_SPECIFIER_QUALIFIER_LIST_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_SPECIFIER_QUALIFIER_LIST_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_SPECIFIER_QUALIFIER_LIST_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_STRUCT_DECLARATOR_LIST_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_STRUCT_DECLARATOR_LIST_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_STRUCT_DECLARATOR_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_STRUCT_DECLARATOR_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_STRUCT_DECLARATOR_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ENUM_SPECIFIER_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ENUM_SPECIFIER_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ENUM_SPECIFIER_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ENUM_SPECIFIER_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ENUM_SPECIFIER_5(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ENUMERATOR_LIST_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ENUMERATOR_LIST_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ENUMERATOR_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ENUMERATOR_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ATOMIC_TYPE_SPECIFIER_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_TYPE_QUALIFIER_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_TYPE_QUALIFIER_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_TYPE_QUALIFIER_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_TYPE_QUALIFIER_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_FUNCTION_SPECIFIER_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_FUNCTION_SPECIFIER_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ALIGNMENT_SPECIFIER_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ALIGNMENT_SPECIFIER_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DECLARATOR_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DECLARATOR_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_DECLARATOR_BASE_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_DECLARATOR_BASE_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_DECLARATOR_ARRAY_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_DECLARATOR_ARRAY_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_DECLARATOR_ARRAY_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_DECLARATOR_ARRAY_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_DECLARATOR_ARRAY_5(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_DECLARATOR_ARRAY_6(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_DECLARATOR_ARRAY_7(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_DECLARATOR_ARRAY_8(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_DECLARATOR_ARRAY_9(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_DECLARATOR_ARRAY_10(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_DECLARATOR_FUNCTION1_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_DECLARATOR_FUNCTION1_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_DECLARATOR_FUNCTION1_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_DECLARATOR_FUNCTION1_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_DECLARATOR_FUNCTION2_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_DECLARATOR_FUNCTION2_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_DECLARATOR_FUNCTION_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_DECLARATOR_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_POINTER_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_POINTER_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_POINTER_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_POINTER_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_TYPE_QUALIFIER_LIST_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_TYPE_QUALIFIER_LIST_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_PARAMETER_TYPE_LIST_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_PARAMETER_TYPE_LIST_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_PARAMETER_LIST_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_PARAMETER_LIST_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_PARAMETER_DECLARATION_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_PARAMETER_DECLARATION_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_PARAMETER_DECLARATION_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_IDENTIFIER_LIST_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_IDENTIFIER_LIST_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_TYPE_NAME_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_TYPE_NAME_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ABSTRACT_DECLARATOR_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ABSTRACT_DECLARATOR_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ABSTRACT_DECLARATOR_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_5(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_6(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_7(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_8(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_9(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_10(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_11(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_12(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_13(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_14(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_15(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_16(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_17(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_18(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_19(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_20(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DIRECT_ABSTRACT_DECLARATOR_21(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_INITIALIZER_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_INITIALIZER_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_INITIALIZER_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_INITIALIZER_LIST_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_INITIALIZER_LIST_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_INITIALIZER_LIST_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_INITIALIZER_LIST_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DESIGNATION_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DESIGNATOR_LIST_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DESIGNATOR_LIST_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DESIGNATOR_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DESIGNATOR_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_STATIC_ASSERT_DECLARATION_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_STATEMENT_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_STATEMENT_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_STATEMENT_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_STATEMENT_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_STATEMENT_5(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_STATEMENT_6(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_LABELED_STATEMENT_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_LABELED_STATEMENT_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_LABELED_STATEMENT_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_COMPOUND_STATEMENT_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_COMPOUND_STATEMENT_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_BLOCK_ITEM_LIST_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_BLOCK_ITEM_LIST_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_BLOCK_ITEM_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_BLOCK_ITEM_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_EXPRESSION_STATEMENT_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_EXPRESSION_STATEMENT_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_SELECTION_STATEMENT_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_SELECTION_STATEMENT_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_SELECTION_STATEMENT_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ITERATION_STATEMENT_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ITERATION_STATEMENT_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ITERATION_STATEMENT_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ITERATION_STATEMENT_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ITERATION_STATEMENT_5(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_ITERATION_STATEMENT_6(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_JUMP_STATEMENT_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_JUMP_STATEMENT_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_JUMP_STATEMENT_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_JUMP_STATEMENT_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_JUMP_STATEMENT_5(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_TRANSLATION_UNIT_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_TRANSLATION_UNIT_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_FILE_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_FILE_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_EXTERNAL_DECLARATION_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_EXTERNAL_DECLARATION_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_FUNCTION_DEFINITION_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_FUNCTION_DEFINITION_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DECLARATION_LIST_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_DECLARATION_LIST_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_IDENTIFIER_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_FUNCTION_ATTRIBUTE1_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_FUNCTION_ATTRIBUTE1_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_FUNCTION_ATTRIBUTE1_3(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_FUNCTION_ATTRIBUTE1_4(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_FUNCTION_ATTRIBUTE2_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_FUNCTION_ATTRIBUTE2_2(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
icode *  func_IAN_FUNCTION_ATTRIBUTE_1(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
//ast func cout:299
 icode *func_token_IDENTIFIER(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_I_CONSTANT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_F_CONSTANT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_STRING_LITERAL(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_FUNC_NAME(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_SIZEOF(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_PTR_OP(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_INC_OP(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_DEC_OP(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_LEFT_OP(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_RIGHT_OP(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_ROTATE_RIGHT_OP(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_ROTATE_LEFT_OP(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_LE_OP(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_GE_OP(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_EQ_OP(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_NE_OP(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_AND_OP(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_OR_OP(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_MUL_ASSIGN(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_DIV_ASSIGN(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_MOD_ASSIGN(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_ADD_ASSIGN(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_SUB_ASSIGN(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_LEFT_ASSIGN(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_RIGHT_ASSIGN(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_AND_ASSIGN(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_XOR_ASSIGN(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_OR_ASSIGN(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TYPEDEF_NAME(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_ENUMERATION_CONSTANT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_TYPEDEF(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_EXTERN(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_STATIC(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_AUTO(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_REGISTER(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_INLINE(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_CONST(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_RESTRICT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_VOLATILE(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_BOOL(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_CHAR(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_SHORT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_INT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_LONG(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_SIGNED(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_UNSIGNED(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_FLOAT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_DOUBLE(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_VOID(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_COMPLEX(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_IMAGINARY(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_STRUCT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_UNION(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_ENUM(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_ELLIPSIS(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_CASE(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_DEFAULT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_IF(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_ELSE(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_SWITCH(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_WHILE(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_DO(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_FOR(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_GOTO(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_CONTINUE(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_BREAK(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_RETURN(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_ALIGNAS(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_ALIGNOF(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_ATOMIC(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_GENERIC(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_NORETURN(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_STATIC_ASSERT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_THREAD_LOCAL(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_SFR(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_BIT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_SBIT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_SFR16(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_SFR32(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_INTERRUPT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_USING(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_REENTRANT(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_REGPARAMS(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
 icode *func_token_STORAGE_SPEC_C51(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic);
//elem func cout:85


}//namespace NS_C2IR
#endif
