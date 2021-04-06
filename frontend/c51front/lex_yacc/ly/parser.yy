
%{ /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>

#include "comp_context.h"
#include "comp_context_gen_defs.h"
#include "token_defs.h"
#define YYSTYPE NS_C512IR::token_defs


%}

/*** yacc/bison Declarations ***/

/* Require bison 2.3 or later */
%require "2.3"

/* add debug output code to generated parser. disable this for release
 * versions. */
%debug

/* start symbol is named "start" */
%start file

/* write out a header file containing the token defines */
%defines

/* use newer C++ skeleton file */
%skeleton "lalr1.cc"

/* namespace to enclose parser in */
%name-prefix="NS_C512IR"

/* set the parser's class identifier */
%define "parser_class_name" "Parser"

/* keep track of the current position within the input */
%locations
%initial-action
{
    // initialize the initial location object
    @$.begin.filename = @$.end.filename = &driver.streamname;
};

/* The driver is passed by reference to the parser and to the scanner. This
 * provides a simple but effective pure interface, not relying on global
 * variables. */
%parse-param { class Driver& driver }

/* verbose error messages */
%error-verbose

 /*** BEGIN EXAMPLE - Change the example grammar's tokens below ***/


%token			END	     0	/**"end of file"**/
%token			EOL		/*"end of line"**/


%token  IDENTIFIER
%token	I_CONSTANT F_CONSTANT STRING_LITERAL FUNC_NAME SIZEOF
%token	PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP ROTATE_RIGHT_OP ROTATE_LEFT_OP LE_OP GE_OP EQ_OP NE_OP
%token	AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token	SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token	XOR_ASSIGN OR_ASSIGN
%token	TYPEDEF_NAME ENUMERATION_CONSTANT

%token	TYPEDEF EXTERN STATIC AUTO REGISTER INLINE
%token	CONST RESTRICT VOLATILE
%token	BOOL CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE VOID
%token	COMPLEX IMAGINARY
%token	STRUCT UNION ENUM ELLIPSIS

%token	CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%token	ALIGNAS ALIGNOF ATOMIC GENERIC NORETURN STATIC_ASSERT THREAD_LOCAL

/*added token--songjiangshan */
/** %token CAST INIT_DEEP INIT_NODE BLOCK CALL PARAM */
%token   SFR  BIT  SBIT  SFR16  SFR32 
/** %token  LINE_NUM */
%token INTERRUPT USING REENTRANT  REGPARAMS STORAGE_SPEC_C51
 /*** END EXAMPLE - Change the example grammar's tokens above ***/

%{

#include "driver.h"
#include "scanner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex driver.lexer->lex

%}

%% /*** Grammar Rules ***/

 /*** BEGIN EXAMPLE - Change the example grammar rules below ***/
primary_expression
	:  identifier 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_PRIMARY_EXPRESSION_1);
		}
	|  constant 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_PRIMARY_EXPRESSION_2);
		}
	|  string 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_PRIMARY_EXPRESSION_3);
		}
	|  '('  expression  ')' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_PRIMARY_EXPRESSION_4;
		$$.m_tk_type_int_list.push_back(IAN_PRIMARY_EXPRESSION_4);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  generic_selection 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_PRIMARY_EXPRESSION_5);
		}
	;
constant
	:  I_CONSTANT 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_CONSTANT_1);
		}
	|  F_CONSTANT 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_CONSTANT_2);
		}
	|  ENUMERATION_CONSTANT 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_CONSTANT_3);
		}
	;
enumeration_constant
	:  identifier 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_ENUMERATION_CONSTANT_1);
		}
	;
string
	:  STRING_LITERAL 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_STRING_1);
		}
	|  FUNC_NAME 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_STRING_2);
		}
	;
generic_selection
	:  GENERIC  '('  assignment_expression  ','  generic_assoc_list  ')' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_GENERIC_SELECTION_1;
		$$.m_tk_type_int_list.push_back(IAN_GENERIC_SELECTION_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		$$.m_tk_elems.push_back(parser_ntoken($6));
		}
	;
generic_assoc_list
	:  generic_association 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_GENERIC_ASSOC_LIST_1);
		}
	|  generic_assoc_list  ','  generic_association 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_GENERIC_ASSOC_LIST_2;
		$$.m_tk_type_int_list.push_back(IAN_GENERIC_ASSOC_LIST_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
generic_association
	:  type_name  ':'  assignment_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_GENERIC_ASSOCIATION_1;
		$$.m_tk_type_int_list.push_back(IAN_GENERIC_ASSOCIATION_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  DEFAULT  ':'  assignment_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_GENERIC_ASSOCIATION_2;
		$$.m_tk_type_int_list.push_back(IAN_GENERIC_ASSOCIATION_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
postfix_expression
	:  primary_expression 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_POSTFIX_EXPRESSION_1);
		}
	|  postfix_expression  '['  expression  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_POSTFIX_EXPRESSION_2;
		$$.m_tk_type_int_list.push_back(IAN_POSTFIX_EXPRESSION_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	|  postfix_expression  '('  ')' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_POSTFIX_EXPRESSION_3;
		$$.m_tk_type_int_list.push_back(IAN_POSTFIX_EXPRESSION_3);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  postfix_expression  '('  argument_expression_list  ')' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_POSTFIX_EXPRESSION_4;
		$$.m_tk_type_int_list.push_back(IAN_POSTFIX_EXPRESSION_4);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	|  postfix_expression  '.'  identifier 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_POSTFIX_EXPRESSION_5;
		$$.m_tk_type_int_list.push_back(IAN_POSTFIX_EXPRESSION_5);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  postfix_expression  PTR_OP  identifier 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_POSTFIX_EXPRESSION_6;
		$$.m_tk_type_int_list.push_back(IAN_POSTFIX_EXPRESSION_6);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  postfix_expression  INC_OP 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_POSTFIX_EXPRESSION_7;
		$$.m_tk_type_int_list.push_back(IAN_POSTFIX_EXPRESSION_7);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  postfix_expression  DEC_OP 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_POSTFIX_EXPRESSION_8;
		$$.m_tk_type_int_list.push_back(IAN_POSTFIX_EXPRESSION_8);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  '('  type_name  ')'  '{'  initializer_list  '}' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_POSTFIX_EXPRESSION_9;
		$$.m_tk_type_int_list.push_back(IAN_POSTFIX_EXPRESSION_9);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		$$.m_tk_elems.push_back(parser_ntoken($6));
		}
	|  '('  type_name  ')'  '{'  initializer_list  ','  '}' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_POSTFIX_EXPRESSION_10;
		$$.m_tk_type_int_list.push_back(IAN_POSTFIX_EXPRESSION_10);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		$$.m_tk_elems.push_back(parser_ntoken($6));
		$$.m_tk_elems.push_back(parser_ntoken($7));
		}
	;
argument_expression_list
	:  assignment_expression 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_ARGUMENT_EXPRESSION_LIST_1);
		}
	|  argument_expression_list  ','  assignment_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_ARGUMENT_EXPRESSION_LIST_2;
		$$.m_tk_type_int_list.push_back(IAN_ARGUMENT_EXPRESSION_LIST_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
unary_expression
	:  postfix_expression 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_UNARY_EXPRESSION_1);
		}
	|  INC_OP  unary_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_UNARY_EXPRESSION_2;
		$$.m_tk_type_int_list.push_back(IAN_UNARY_EXPRESSION_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  DEC_OP  unary_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_UNARY_EXPRESSION_3;
		$$.m_tk_type_int_list.push_back(IAN_UNARY_EXPRESSION_3);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  unary_operator  cast_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_UNARY_EXPRESSION_4;
		$$.m_tk_type_int_list.push_back(IAN_UNARY_EXPRESSION_4);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  SIZEOF  unary_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_UNARY_EXPRESSION_5;
		$$.m_tk_type_int_list.push_back(IAN_UNARY_EXPRESSION_5);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  SIZEOF  '('  type_name  ')' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_UNARY_EXPRESSION_6;
		$$.m_tk_type_int_list.push_back(IAN_UNARY_EXPRESSION_6);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	|  ALIGNOF  '('  type_name  ')' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_UNARY_EXPRESSION_7;
		$$.m_tk_type_int_list.push_back(IAN_UNARY_EXPRESSION_7);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	;
unary_operator
	:  '&' 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_UNARY_OPERATOR_1);
		}
	|  '*' 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_UNARY_OPERATOR_2);
		}
	|  '+' 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_UNARY_OPERATOR_3);
		}
	|  '-' 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_UNARY_OPERATOR_4);
		}
	|  '~' 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_UNARY_OPERATOR_5);
		}
	|  '!' 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_UNARY_OPERATOR_6);
		}
	;
cast_expression
	:  unary_expression 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_CAST_EXPRESSION_1);
		}
	|  '('  type_name  ')'  cast_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_CAST_EXPRESSION_2;
		$$.m_tk_type_int_list.push_back(IAN_CAST_EXPRESSION_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	;
multiplicative_expression
	:  cast_expression 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_MULTIPLICATIVE_EXPRESSION_1);
		}
	|  multiplicative_expression  '*'  cast_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_MULTIPLICATIVE_EXPRESSION_2;
		$$.m_tk_type_int_list.push_back(IAN_MULTIPLICATIVE_EXPRESSION_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  multiplicative_expression  '/'  cast_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_MULTIPLICATIVE_EXPRESSION_3;
		$$.m_tk_type_int_list.push_back(IAN_MULTIPLICATIVE_EXPRESSION_3);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  multiplicative_expression  '%'  cast_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_MULTIPLICATIVE_EXPRESSION_4;
		$$.m_tk_type_int_list.push_back(IAN_MULTIPLICATIVE_EXPRESSION_4);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
additive_expression
	:  multiplicative_expression 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_ADDITIVE_EXPRESSION_1);
		}
	|  additive_expression  '+'  multiplicative_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_ADDITIVE_EXPRESSION_2;
		$$.m_tk_type_int_list.push_back(IAN_ADDITIVE_EXPRESSION_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  additive_expression  '-'  multiplicative_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_ADDITIVE_EXPRESSION_3;
		$$.m_tk_type_int_list.push_back(IAN_ADDITIVE_EXPRESSION_3);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
shift_expression
	:  additive_expression 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_SHIFT_EXPRESSION_1);
		}
	|  shift_expression  LEFT_OP  additive_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_SHIFT_EXPRESSION_2;
		$$.m_tk_type_int_list.push_back(IAN_SHIFT_EXPRESSION_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  shift_expression  RIGHT_OP  additive_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_SHIFT_EXPRESSION_3;
		$$.m_tk_type_int_list.push_back(IAN_SHIFT_EXPRESSION_3);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  shift_expression  ROTATE_LEFT_OP  additive_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_SHIFT_EXPRESSION_4;
		$$.m_tk_type_int_list.push_back(IAN_SHIFT_EXPRESSION_4);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  shift_expression  ROTATE_RIGHT_OP  additive_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_SHIFT_EXPRESSION_5;
		$$.m_tk_type_int_list.push_back(IAN_SHIFT_EXPRESSION_5);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
relational_expression
	:  shift_expression 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_RELATIONAL_EXPRESSION_1);
		}
	|  relational_expression  '<'  shift_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_RELATIONAL_EXPRESSION_2;
		$$.m_tk_type_int_list.push_back(IAN_RELATIONAL_EXPRESSION_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  relational_expression  '>'  shift_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_RELATIONAL_EXPRESSION_3;
		$$.m_tk_type_int_list.push_back(IAN_RELATIONAL_EXPRESSION_3);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  relational_expression  LE_OP  shift_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_RELATIONAL_EXPRESSION_4;
		$$.m_tk_type_int_list.push_back(IAN_RELATIONAL_EXPRESSION_4);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  relational_expression  GE_OP  shift_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_RELATIONAL_EXPRESSION_5;
		$$.m_tk_type_int_list.push_back(IAN_RELATIONAL_EXPRESSION_5);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
equality_expression
	:  relational_expression 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_EQUALITY_EXPRESSION_1);
		}
	|  equality_expression  EQ_OP  relational_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_EQUALITY_EXPRESSION_2;
		$$.m_tk_type_int_list.push_back(IAN_EQUALITY_EXPRESSION_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  equality_expression  NE_OP  relational_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_EQUALITY_EXPRESSION_3;
		$$.m_tk_type_int_list.push_back(IAN_EQUALITY_EXPRESSION_3);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
and_expression
	:  equality_expression 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_AND_EXPRESSION_1);
		}
	|  and_expression  '&'  equality_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_AND_EXPRESSION_2;
		$$.m_tk_type_int_list.push_back(IAN_AND_EXPRESSION_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
exclusive_or_expression
	:  and_expression 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_EXCLUSIVE_OR_EXPRESSION_1);
		}
	|  exclusive_or_expression  '^'  and_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_EXCLUSIVE_OR_EXPRESSION_2;
		$$.m_tk_type_int_list.push_back(IAN_EXCLUSIVE_OR_EXPRESSION_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
inclusive_or_expression
	:  exclusive_or_expression 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_INCLUSIVE_OR_EXPRESSION_1);
		}
	|  inclusive_or_expression  '|'  exclusive_or_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_INCLUSIVE_OR_EXPRESSION_2;
		$$.m_tk_type_int_list.push_back(IAN_INCLUSIVE_OR_EXPRESSION_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
logical_and_expression
	:  inclusive_or_expression 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_LOGICAL_AND_EXPRESSION_1);
		}
	|  logical_and_expression  AND_OP  inclusive_or_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_LOGICAL_AND_EXPRESSION_2;
		$$.m_tk_type_int_list.push_back(IAN_LOGICAL_AND_EXPRESSION_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
logical_or_expression
	:  logical_and_expression 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_LOGICAL_OR_EXPRESSION_1);
		}
	|  logical_or_expression  OR_OP  logical_and_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_LOGICAL_OR_EXPRESSION_2;
		$$.m_tk_type_int_list.push_back(IAN_LOGICAL_OR_EXPRESSION_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
conditional_expression
	:  logical_or_expression 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_CONDITIONAL_EXPRESSION_1);
		}
	|  logical_or_expression  '?'  expression  ':'  conditional_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_CONDITIONAL_EXPRESSION_2;
		$$.m_tk_type_int_list.push_back(IAN_CONDITIONAL_EXPRESSION_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		}
	;
assignment_expression
	:  conditional_expression 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_ASSIGNMENT_EXPRESSION_1);
		}
	|  unary_expression  assignment_operator  assignment_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_ASSIGNMENT_EXPRESSION_2;
		$$.m_tk_type_int_list.push_back(IAN_ASSIGNMENT_EXPRESSION_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
assignment_operator
	:  '=' 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_ASSIGNMENT_OPERATOR_1);
		}
	|  MUL_ASSIGN 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_ASSIGNMENT_OPERATOR_2);
		}
	|  DIV_ASSIGN 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_ASSIGNMENT_OPERATOR_3);
		}
	|  MOD_ASSIGN 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_ASSIGNMENT_OPERATOR_4);
		}
	|  ADD_ASSIGN 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_ASSIGNMENT_OPERATOR_5);
		}
	|  SUB_ASSIGN 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_ASSIGNMENT_OPERATOR_6);
		}
	|  LEFT_ASSIGN 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_ASSIGNMENT_OPERATOR_7);
		}
	|  RIGHT_ASSIGN 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_ASSIGNMENT_OPERATOR_8);
		}
	|  AND_ASSIGN 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_ASSIGNMENT_OPERATOR_9);
		}
	|  XOR_ASSIGN 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_ASSIGNMENT_OPERATOR_10);
		}
	|  OR_ASSIGN 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_ASSIGNMENT_OPERATOR_11);
		}
	;
expression
	:  assignment_expression 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_EXPRESSION_1);
		}
	|  expression  ','  assignment_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_EXPRESSION_2;
		$$.m_tk_type_int_list.push_back(IAN_EXPRESSION_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
constant_expression
	:  conditional_expression 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_CONSTANT_EXPRESSION_1);
		}
	;
declaration
	:  declaration_specifiers  ';' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DECLARATION_1;
		$$.m_tk_type_int_list.push_back(IAN_DECLARATION_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  declaration_specifiers  init_declarator_list  ';' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DECLARATION_2;
		$$.m_tk_type_int_list.push_back(IAN_DECLARATION_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  static_assert_declaration 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_DECLARATION_3);
		}
	;
declaration_specifiers
	:  declaration_specifiers_ 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_DECLARATION_SPECIFIERS_1);
		}
	;
declaration_specifiers_
	:  storage_class_specifier  declaration_specifiers_ 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DECLARATION_SPECIFIERS__1;
		$$.m_tk_type_int_list.push_back(IAN_DECLARATION_SPECIFIERS__1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  storage_class_specifier 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_DECLARATION_SPECIFIERS__2);
		}
	|  type_specifier  declaration_specifiers_ 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DECLARATION_SPECIFIERS__3;
		$$.m_tk_type_int_list.push_back(IAN_DECLARATION_SPECIFIERS__3);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  type_specifier 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_DECLARATION_SPECIFIERS__4);
		}
	|  type_qualifier  declaration_specifiers_ 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DECLARATION_SPECIFIERS__5;
		$$.m_tk_type_int_list.push_back(IAN_DECLARATION_SPECIFIERS__5);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  type_qualifier 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_DECLARATION_SPECIFIERS__6);
		}
	|  function_specifier  declaration_specifiers_ 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DECLARATION_SPECIFIERS__7;
		$$.m_tk_type_int_list.push_back(IAN_DECLARATION_SPECIFIERS__7);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  function_specifier 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_DECLARATION_SPECIFIERS__8);
		}
	|  alignment_specifier  declaration_specifiers_ 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DECLARATION_SPECIFIERS__9;
		$$.m_tk_type_int_list.push_back(IAN_DECLARATION_SPECIFIERS__9);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  alignment_specifier 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_DECLARATION_SPECIFIERS__10);
		}
	;
init_declarator_list
	:  init_declarator 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_INIT_DECLARATOR_LIST_1);
		}
	|  init_declarator_list  ','  init_declarator 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_INIT_DECLARATOR_LIST_2;
		$$.m_tk_type_int_list.push_back(IAN_INIT_DECLARATOR_LIST_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
init_declarator
	:  declarator  '='  initializer 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_INIT_DECLARATOR_1;
		$$.m_tk_type_int_list.push_back(IAN_INIT_DECLARATOR_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  declarator 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_INIT_DECLARATOR_2);
		}
	;
storage_class_specifier
	:  TYPEDEF 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_STORAGE_CLASS_SPECIFIER_1);
		}
	|  EXTERN 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_STORAGE_CLASS_SPECIFIER_2);
		}
	|  STATIC 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_STORAGE_CLASS_SPECIFIER_3);
		}
	|  THREAD_LOCAL 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_STORAGE_CLASS_SPECIFIER_4);
		}
	|  AUTO 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_STORAGE_CLASS_SPECIFIER_5);
		}
	|  REGISTER 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_STORAGE_CLASS_SPECIFIER_6);
		}
	|  STORAGE_SPEC_C51 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_STORAGE_CLASS_SPECIFIER_7);
		}
	;
type_specifier
	:  VOID 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_1);
		}
	|  CHAR 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_2);
		}
	|  SHORT 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_3);
		}
	|  INT 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_4);
		}
	|  LONG 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_5);
		}
	|  FLOAT 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_6);
		}
	|  DOUBLE 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_7);
		}
	|  SIGNED 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_8);
		}
	|  UNSIGNED 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_9);
		}
	|  BOOL 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_10);
		}
	|  COMPLEX 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_11);
		}
	|  IMAGINARY 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_12);
		}
	|  atomic_type_specifier 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_13);
		}
	|  struct_or_union_specifier 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_14);
		}
	|  enum_specifier 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_15);
		}
	|  TYPEDEF_NAME 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_16);
		}
	|  SFR 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_17);
		}
	|  BIT 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_18);
		}
	|  SBIT 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_19);
		}
	|  SFR16 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_20);
		}
	|  SFR32 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_21);
		}
	;
struct_or_union_specifier
	:  struct_or_union  '{'  struct_declaration_list  '}' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_STRUCT_OR_UNION_SPECIFIER_1;
		$$.m_tk_type_int_list.push_back(IAN_STRUCT_OR_UNION_SPECIFIER_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	|  struct_or_union  identifier  '{'  struct_declaration_list  '}' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_STRUCT_OR_UNION_SPECIFIER_2;
		$$.m_tk_type_int_list.push_back(IAN_STRUCT_OR_UNION_SPECIFIER_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		}
	|  struct_or_union  identifier 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_STRUCT_OR_UNION_SPECIFIER_3;
		$$.m_tk_type_int_list.push_back(IAN_STRUCT_OR_UNION_SPECIFIER_3);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	;
struct_or_union
	:  STRUCT 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_STRUCT_OR_UNION_1);
		}
	|  UNION 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_STRUCT_OR_UNION_2);
		}
	;
struct_declaration_list
	:  struct_declaration 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_STRUCT_DECLARATION_LIST_1);
		}
	|  struct_declaration_list  struct_declaration 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_STRUCT_DECLARATION_LIST_2;
		$$.m_tk_type_int_list.push_back(IAN_STRUCT_DECLARATION_LIST_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	;
struct_declaration
	:  specifier_qualifier_list  ';' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_STRUCT_DECLARATION_1;
		$$.m_tk_type_int_list.push_back(IAN_STRUCT_DECLARATION_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  specifier_qualifier_list  struct_declarator_list  ';' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_STRUCT_DECLARATION_2;
		$$.m_tk_type_int_list.push_back(IAN_STRUCT_DECLARATION_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  static_assert_declaration 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_STRUCT_DECLARATION_3);
		}
	;
specifier_qualifier_list
	:  type_specifier  specifier_qualifier_list 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_SPECIFIER_QUALIFIER_LIST_1;
		$$.m_tk_type_int_list.push_back(IAN_SPECIFIER_QUALIFIER_LIST_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  type_specifier 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_SPECIFIER_QUALIFIER_LIST_2);
		}
	|  type_qualifier  specifier_qualifier_list 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_SPECIFIER_QUALIFIER_LIST_3;
		$$.m_tk_type_int_list.push_back(IAN_SPECIFIER_QUALIFIER_LIST_3);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  type_qualifier 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_SPECIFIER_QUALIFIER_LIST_4);
		}
	;
struct_declarator_list
	:  struct_declarator 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_STRUCT_DECLARATOR_LIST_1);
		}
	|  struct_declarator_list  ','  struct_declarator 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_STRUCT_DECLARATOR_LIST_2;
		$$.m_tk_type_int_list.push_back(IAN_STRUCT_DECLARATOR_LIST_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
struct_declarator
	:  ':'  constant_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_STRUCT_DECLARATOR_1;
		$$.m_tk_type_int_list.push_back(IAN_STRUCT_DECLARATOR_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  declarator  ':'  constant_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_STRUCT_DECLARATOR_2;
		$$.m_tk_type_int_list.push_back(IAN_STRUCT_DECLARATOR_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  declarator 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_STRUCT_DECLARATOR_3);
		}
	;
enum_specifier
	:  ENUM  '{'  enumerator_list  '}' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_ENUM_SPECIFIER_1;
		$$.m_tk_type_int_list.push_back(IAN_ENUM_SPECIFIER_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	|  ENUM  '{'  enumerator_list  ','  '}' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_ENUM_SPECIFIER_2;
		$$.m_tk_type_int_list.push_back(IAN_ENUM_SPECIFIER_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		}
	|  ENUM  identifier  '{'  enumerator_list  '}' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_ENUM_SPECIFIER_3;
		$$.m_tk_type_int_list.push_back(IAN_ENUM_SPECIFIER_3);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		}
	|  ENUM  identifier  '{'  enumerator_list  ','  '}' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_ENUM_SPECIFIER_4;
		$$.m_tk_type_int_list.push_back(IAN_ENUM_SPECIFIER_4);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		$$.m_tk_elems.push_back(parser_ntoken($6));
		}
	|  ENUM  identifier 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_ENUM_SPECIFIER_5;
		$$.m_tk_type_int_list.push_back(IAN_ENUM_SPECIFIER_5);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	;
enumerator_list
	:  enumerator 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_ENUMERATOR_LIST_1);
		}
	|  enumerator_list  ','  enumerator 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_ENUMERATOR_LIST_2;
		$$.m_tk_type_int_list.push_back(IAN_ENUMERATOR_LIST_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
enumerator
	:  enumeration_constant  '='  constant_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_ENUMERATOR_1;
		$$.m_tk_type_int_list.push_back(IAN_ENUMERATOR_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  enumeration_constant 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_ENUMERATOR_2);
		}
	;
atomic_type_specifier
	:  ATOMIC  '('  type_name  ')' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_ATOMIC_TYPE_SPECIFIER_1;
		$$.m_tk_type_int_list.push_back(IAN_ATOMIC_TYPE_SPECIFIER_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	;
type_qualifier
	:  CONST 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_QUALIFIER_1);
		}
	|  RESTRICT 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_QUALIFIER_2);
		}
	|  VOLATILE 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_QUALIFIER_3);
		}
	|  ATOMIC 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_QUALIFIER_4);
		}
	;
function_specifier
	:  INLINE 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_FUNCTION_SPECIFIER_1);
		}
	|  NORETURN 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_FUNCTION_SPECIFIER_2);
		}
	;
alignment_specifier
	:  ALIGNAS  '('  type_name  ')' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_ALIGNMENT_SPECIFIER_1;
		$$.m_tk_type_int_list.push_back(IAN_ALIGNMENT_SPECIFIER_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	|  ALIGNAS  '('  constant_expression  ')' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_ALIGNMENT_SPECIFIER_2;
		$$.m_tk_type_int_list.push_back(IAN_ALIGNMENT_SPECIFIER_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	;
declarator
	:  pointer  direct_declarator 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DECLARATOR_1;
		$$.m_tk_type_int_list.push_back(IAN_DECLARATOR_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  direct_declarator 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_DECLARATOR_2);
		}
	;
direct_declarator_base
	:  identifier 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_DECLARATOR_BASE_1);
		}
	|  '('  declarator  ')' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_DECLARATOR_BASE_2;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_DECLARATOR_BASE_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
direct_declarator_array
	:  direct_declarator_base 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_DECLARATOR_ARRAY_1);
		}
	|  direct_declarator_array  '['  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_DECLARATOR_ARRAY_2;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_DECLARATOR_ARRAY_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  direct_declarator_array  '['  '*'  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_DECLARATOR_ARRAY_3;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_DECLARATOR_ARRAY_3);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	|  direct_declarator_array  '['  STATIC  type_qualifier_list  assignment_expression  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_DECLARATOR_ARRAY_4;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_DECLARATOR_ARRAY_4);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		$$.m_tk_elems.push_back(parser_ntoken($6));
		}
	|  direct_declarator_array  '['  STATIC  assignment_expression  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_DECLARATOR_ARRAY_5;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_DECLARATOR_ARRAY_5);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		}
	|  direct_declarator_array  '['  type_qualifier_list  '*'  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_DECLARATOR_ARRAY_6;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_DECLARATOR_ARRAY_6);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		}
	|  direct_declarator_array  '['  type_qualifier_list  STATIC  assignment_expression  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_DECLARATOR_ARRAY_7;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_DECLARATOR_ARRAY_7);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		$$.m_tk_elems.push_back(parser_ntoken($6));
		}
	|  direct_declarator_array  '['  type_qualifier_list  assignment_expression  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_DECLARATOR_ARRAY_8;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_DECLARATOR_ARRAY_8);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		}
	|  direct_declarator_array  '['  type_qualifier_list  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_DECLARATOR_ARRAY_9;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_DECLARATOR_ARRAY_9);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	|  direct_declarator_array  '['  assignment_expression  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_DECLARATOR_ARRAY_10;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_DECLARATOR_ARRAY_10);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	;
direct_declarator_function1
	:  direct_declarator_array 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_DECLARATOR_FUNCTION1_1);
		}
	|  direct_declarator_function1  '('  parameter_type_list  ')' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_DECLARATOR_FUNCTION1_2;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_DECLARATOR_FUNCTION1_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	|  direct_declarator_function1  '('  ')' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_DECLARATOR_FUNCTION1_3;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_DECLARATOR_FUNCTION1_3);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  direct_declarator_function1  '('  identifier_list  ')' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_DECLARATOR_FUNCTION1_4;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_DECLARATOR_FUNCTION1_4);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	;
direct_declarator_function2
	:  direct_declarator_function1 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_DECLARATOR_FUNCTION2_1);
		}
	|  direct_declarator_function1  function_attribute 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_DECLARATOR_FUNCTION2_2;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_DECLARATOR_FUNCTION2_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	;
direct_declarator_function
	:  direct_declarator_function2 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_DECLARATOR_FUNCTION_1);
		}
	;
direct_declarator
	:  direct_declarator_function 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_DECLARATOR_1);
		}
	;
pointer
	:  '*'  type_qualifier_list  pointer 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_POINTER_1;
		$$.m_tk_type_int_list.push_back(IAN_POINTER_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  '*'  type_qualifier_list 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_POINTER_2;
		$$.m_tk_type_int_list.push_back(IAN_POINTER_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  '*'  pointer 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_POINTER_3;
		$$.m_tk_type_int_list.push_back(IAN_POINTER_3);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  '*' 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_POINTER_4);
		}
	;
type_qualifier_list
	:  type_qualifier 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_QUALIFIER_LIST_1);
		}
	|  type_qualifier_list  type_qualifier 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_TYPE_QUALIFIER_LIST_2;
		$$.m_tk_type_int_list.push_back(IAN_TYPE_QUALIFIER_LIST_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	;
parameter_type_list
	:  parameter_list  ','  ELLIPSIS 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_PARAMETER_TYPE_LIST_1;
		$$.m_tk_type_int_list.push_back(IAN_PARAMETER_TYPE_LIST_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  parameter_list 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_PARAMETER_TYPE_LIST_2);
		}
	;
parameter_list
	:  parameter_declaration 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_PARAMETER_LIST_1);
		}
	|  parameter_list  ','  parameter_declaration 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_PARAMETER_LIST_2;
		$$.m_tk_type_int_list.push_back(IAN_PARAMETER_LIST_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
parameter_declaration
	:  declaration_specifiers  declarator 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_PARAMETER_DECLARATION_1;
		$$.m_tk_type_int_list.push_back(IAN_PARAMETER_DECLARATION_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  declaration_specifiers  abstract_declarator 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_PARAMETER_DECLARATION_2;
		$$.m_tk_type_int_list.push_back(IAN_PARAMETER_DECLARATION_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  declaration_specifiers 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_PARAMETER_DECLARATION_3);
		}
	;
identifier_list
	:  identifier 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_IDENTIFIER_LIST_1);
		}
	|  identifier_list  ','  identifier 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_IDENTIFIER_LIST_2;
		$$.m_tk_type_int_list.push_back(IAN_IDENTIFIER_LIST_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
type_name
	:  specifier_qualifier_list  abstract_declarator 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_TYPE_NAME_1;
		$$.m_tk_type_int_list.push_back(IAN_TYPE_NAME_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  specifier_qualifier_list 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_NAME_2);
		}
	;
abstract_declarator
	:  pointer  direct_abstract_declarator 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_ABSTRACT_DECLARATOR_1;
		$$.m_tk_type_int_list.push_back(IAN_ABSTRACT_DECLARATOR_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  pointer 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_ABSTRACT_DECLARATOR_2);
		}
	|  direct_abstract_declarator 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_ABSTRACT_DECLARATOR_3);
		}
	;
direct_abstract_declarator
	:  '('  abstract_declarator  ')' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_ABSTRACT_DECLARATOR_1;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_ABSTRACT_DECLARATOR_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  '['  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_ABSTRACT_DECLARATOR_2;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_ABSTRACT_DECLARATOR_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  '['  '*'  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_ABSTRACT_DECLARATOR_3;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_ABSTRACT_DECLARATOR_3);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  '['  STATIC  type_qualifier_list  assignment_expression  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_ABSTRACT_DECLARATOR_4;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_ABSTRACT_DECLARATOR_4);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		}
	|  '['  STATIC  assignment_expression  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_ABSTRACT_DECLARATOR_5;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_ABSTRACT_DECLARATOR_5);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	|  '['  type_qualifier_list  STATIC  assignment_expression  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_ABSTRACT_DECLARATOR_6;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_ABSTRACT_DECLARATOR_6);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		}
	|  '['  type_qualifier_list  assignment_expression  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_ABSTRACT_DECLARATOR_7;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_ABSTRACT_DECLARATOR_7);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	|  '['  type_qualifier_list  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_ABSTRACT_DECLARATOR_8;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_ABSTRACT_DECLARATOR_8);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  '['  assignment_expression  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_ABSTRACT_DECLARATOR_9;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_ABSTRACT_DECLARATOR_9);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  direct_abstract_declarator  '['  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_ABSTRACT_DECLARATOR_10;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_ABSTRACT_DECLARATOR_10);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  direct_abstract_declarator  '['  '*'  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_ABSTRACT_DECLARATOR_11;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_ABSTRACT_DECLARATOR_11);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	|  direct_abstract_declarator  '['  STATIC  type_qualifier_list  assignment_expression  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_ABSTRACT_DECLARATOR_12;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_ABSTRACT_DECLARATOR_12);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		$$.m_tk_elems.push_back(parser_ntoken($6));
		}
	|  direct_abstract_declarator  '['  STATIC  assignment_expression  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_ABSTRACT_DECLARATOR_13;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_ABSTRACT_DECLARATOR_13);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		}
	|  direct_abstract_declarator  '['  type_qualifier_list  assignment_expression  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_ABSTRACT_DECLARATOR_14;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_ABSTRACT_DECLARATOR_14);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		}
	|  direct_abstract_declarator  '['  type_qualifier_list  STATIC  assignment_expression  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_ABSTRACT_DECLARATOR_15;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_ABSTRACT_DECLARATOR_15);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		$$.m_tk_elems.push_back(parser_ntoken($6));
		}
	|  direct_abstract_declarator  '['  type_qualifier_list  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_ABSTRACT_DECLARATOR_16;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_ABSTRACT_DECLARATOR_16);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	|  direct_abstract_declarator  '['  assignment_expression  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_ABSTRACT_DECLARATOR_17;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_ABSTRACT_DECLARATOR_17);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	|  '('  ')' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_ABSTRACT_DECLARATOR_18;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_ABSTRACT_DECLARATOR_18);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  '('  parameter_type_list  ')' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_ABSTRACT_DECLARATOR_19;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_ABSTRACT_DECLARATOR_19);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  direct_abstract_declarator  '('  ')' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_ABSTRACT_DECLARATOR_20;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_ABSTRACT_DECLARATOR_20);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  direct_abstract_declarator  '('  parameter_type_list  ')' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DIRECT_ABSTRACT_DECLARATOR_21;
		$$.m_tk_type_int_list.push_back(IAN_DIRECT_ABSTRACT_DECLARATOR_21);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	;
initializer
	:  '{'  initializer_list  '}' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_INITIALIZER_1;
		$$.m_tk_type_int_list.push_back(IAN_INITIALIZER_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  '{'  initializer_list  ','  '}' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_INITIALIZER_2;
		$$.m_tk_type_int_list.push_back(IAN_INITIALIZER_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	|  assignment_expression 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_INITIALIZER_3);
		}
	;
initializer_list
	:  designation  initializer 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_INITIALIZER_LIST_1;
		$$.m_tk_type_int_list.push_back(IAN_INITIALIZER_LIST_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  initializer 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_INITIALIZER_LIST_2);
		}
	|  initializer_list  ','  designation  initializer 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_INITIALIZER_LIST_3;
		$$.m_tk_type_int_list.push_back(IAN_INITIALIZER_LIST_3);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	|  initializer_list  ','  initializer 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_INITIALIZER_LIST_4;
		$$.m_tk_type_int_list.push_back(IAN_INITIALIZER_LIST_4);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
designation
	:  designator_list  '=' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DESIGNATION_1;
		$$.m_tk_type_int_list.push_back(IAN_DESIGNATION_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	;
designator_list
	:  designator 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_DESIGNATOR_LIST_1);
		}
	|  designator_list  designator 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DESIGNATOR_LIST_2;
		$$.m_tk_type_int_list.push_back(IAN_DESIGNATOR_LIST_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	;
designator
	:  '['  constant_expression  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DESIGNATOR_1;
		$$.m_tk_type_int_list.push_back(IAN_DESIGNATOR_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  '.'  identifier 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DESIGNATOR_2;
		$$.m_tk_type_int_list.push_back(IAN_DESIGNATOR_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	;
static_assert_declaration
	:  STATIC_ASSERT  '('  constant_expression  ','  STRING_LITERAL  ')'  ';' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_STATIC_ASSERT_DECLARATION_1;
		$$.m_tk_type_int_list.push_back(IAN_STATIC_ASSERT_DECLARATION_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		$$.m_tk_elems.push_back(parser_ntoken($6));
		$$.m_tk_elems.push_back(parser_ntoken($7));
		}
	;
statement
	:  labeled_statement 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_STATEMENT_1);
		}
	|  compound_statement 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_STATEMENT_2);
		}
	|  expression_statement 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_STATEMENT_3);
		}
	|  selection_statement 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_STATEMENT_4);
		}
	|  iteration_statement 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_STATEMENT_5);
		}
	|  jump_statement 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_STATEMENT_6);
		}
	;
labeled_statement
	:  identifier  ':'  statement 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_LABELED_STATEMENT_1;
		$$.m_tk_type_int_list.push_back(IAN_LABELED_STATEMENT_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  CASE  constant_expression  ':'  statement 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_LABELED_STATEMENT_2;
		$$.m_tk_type_int_list.push_back(IAN_LABELED_STATEMENT_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	|  DEFAULT  ':'  statement 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_LABELED_STATEMENT_3;
		$$.m_tk_type_int_list.push_back(IAN_LABELED_STATEMENT_3);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
compound_statement
	:  '{'  '}' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_COMPOUND_STATEMENT_1;
		$$.m_tk_type_int_list.push_back(IAN_COMPOUND_STATEMENT_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  '{'  block_item_list  '}' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_COMPOUND_STATEMENT_2;
		$$.m_tk_type_int_list.push_back(IAN_COMPOUND_STATEMENT_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
block_item_list
	:  block_item 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_BLOCK_ITEM_LIST_1);
		}
	|  block_item_list  block_item 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_BLOCK_ITEM_LIST_2;
		$$.m_tk_type_int_list.push_back(IAN_BLOCK_ITEM_LIST_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	;
block_item
	:  declaration 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_BLOCK_ITEM_1);
		}
	|  statement 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_BLOCK_ITEM_2);
		}
	;
expression_statement
	:  ';' 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_EXPRESSION_STATEMENT_1);
		}
	|  expression  ';' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_EXPRESSION_STATEMENT_2;
		$$.m_tk_type_int_list.push_back(IAN_EXPRESSION_STATEMENT_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	;
selection_statement
	:  IF  '('  expression  ')'  statement  ELSE  statement 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_SELECTION_STATEMENT_1;
		$$.m_tk_type_int_list.push_back(IAN_SELECTION_STATEMENT_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		$$.m_tk_elems.push_back(parser_ntoken($6));
		$$.m_tk_elems.push_back(parser_ntoken($7));
		}
	|  IF  '('  expression  ')'  statement 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_SELECTION_STATEMENT_2;
		$$.m_tk_type_int_list.push_back(IAN_SELECTION_STATEMENT_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		}
	|  SWITCH  '('  expression  ')'  statement 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_SELECTION_STATEMENT_3;
		$$.m_tk_type_int_list.push_back(IAN_SELECTION_STATEMENT_3);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		}
	;
iteration_statement
	:  WHILE  '('  expression  ')'  statement 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_ITERATION_STATEMENT_1;
		$$.m_tk_type_int_list.push_back(IAN_ITERATION_STATEMENT_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		}
	|  DO  statement  WHILE  '('  expression  ')'  ';' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_ITERATION_STATEMENT_2;
		$$.m_tk_type_int_list.push_back(IAN_ITERATION_STATEMENT_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		$$.m_tk_elems.push_back(parser_ntoken($6));
		$$.m_tk_elems.push_back(parser_ntoken($7));
		}
	|  FOR  '('  expression_statement  expression_statement  ')'  statement 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_ITERATION_STATEMENT_3;
		$$.m_tk_type_int_list.push_back(IAN_ITERATION_STATEMENT_3);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		$$.m_tk_elems.push_back(parser_ntoken($6));
		}
	|  FOR  '('  expression_statement  expression_statement  expression  ')'  statement 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_ITERATION_STATEMENT_4;
		$$.m_tk_type_int_list.push_back(IAN_ITERATION_STATEMENT_4);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		$$.m_tk_elems.push_back(parser_ntoken($6));
		$$.m_tk_elems.push_back(parser_ntoken($7));
		}
	|  FOR  '('  declaration  expression_statement  ')'  statement 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_ITERATION_STATEMENT_5;
		$$.m_tk_type_int_list.push_back(IAN_ITERATION_STATEMENT_5);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		$$.m_tk_elems.push_back(parser_ntoken($6));
		}
	|  FOR  '('  declaration  expression_statement  expression  ')'  statement 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_ITERATION_STATEMENT_6;
		$$.m_tk_type_int_list.push_back(IAN_ITERATION_STATEMENT_6);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		$$.m_tk_elems.push_back(parser_ntoken($6));
		$$.m_tk_elems.push_back(parser_ntoken($7));
		}
	;
jump_statement
	:  GOTO  identifier  ';' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_JUMP_STATEMENT_1;
		$$.m_tk_type_int_list.push_back(IAN_JUMP_STATEMENT_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  CONTINUE  ';' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_JUMP_STATEMENT_2;
		$$.m_tk_type_int_list.push_back(IAN_JUMP_STATEMENT_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  BREAK  ';' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_JUMP_STATEMENT_3;
		$$.m_tk_type_int_list.push_back(IAN_JUMP_STATEMENT_3);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  RETURN  ';' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_JUMP_STATEMENT_4;
		$$.m_tk_type_int_list.push_back(IAN_JUMP_STATEMENT_4);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  RETURN  expression  ';' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_JUMP_STATEMENT_5;
		$$.m_tk_type_int_list.push_back(IAN_JUMP_STATEMENT_5);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
translation_unit
	:  external_declaration 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TRANSLATION_UNIT_1);
		}
	|  translation_unit  external_declaration 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_TRANSLATION_UNIT_2;
		$$.m_tk_type_int_list.push_back(IAN_TRANSLATION_UNIT_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	;
file
	:  /*empty*/ 	{
                driver.error("ERROR:empty source file");
		}
	|  translation_unit 	{
		}
	;
external_declaration
	:  function_definition 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_EXTERNAL_DECLARATION_1);
                driver.calc.add_function( & $$);
		}
	|  declaration 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_EXTERNAL_DECLARATION_2);
                driver.calc.add_declaration( & $$);
		}
	;
function_definition
	:  declaration_specifiers  declarator  declaration_list  compound_statement 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_FUNCTION_DEFINITION_1;
		$$.m_tk_type_int_list.push_back(IAN_FUNCTION_DEFINITION_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	|  declaration_specifiers  declarator  compound_statement 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_FUNCTION_DEFINITION_2;
		$$.m_tk_type_int_list.push_back(IAN_FUNCTION_DEFINITION_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
declaration_list
	:  declaration 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_DECLARATION_LIST_1);
		}
	|  declaration_list  declaration 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DECLARATION_LIST_2;
		$$.m_tk_type_int_list.push_back(IAN_DECLARATION_LIST_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	;
identifier
	:  IDENTIFIER 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_IDENTIFIER_1);
		}
	;
function_attribute1
	:  USING  constant_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_FUNCTION_ATTRIBUTE1_1;
		$$.m_tk_type_int_list.push_back(IAN_FUNCTION_ATTRIBUTE1_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  REENTRANT 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_FUNCTION_ATTRIBUTE1_2);
		}
	|  INTERRUPT  constant_expression 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_FUNCTION_ATTRIBUTE1_3;
		$$.m_tk_type_int_list.push_back(IAN_FUNCTION_ATTRIBUTE1_3);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  REGPARAMS  string 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_FUNCTION_ATTRIBUTE1_4;
		$$.m_tk_type_int_list.push_back(IAN_FUNCTION_ATTRIBUTE1_4);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	;
function_attribute2
	:  function_attribute1 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_FUNCTION_ATTRIBUTE2_1);
		}
	|  function_attribute1  function_attribute2 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_FUNCTION_ATTRIBUTE2_2;
		$$.m_tk_type_int_list.push_back(IAN_FUNCTION_ATTRIBUTE2_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	;
function_attribute
	:  function_attribute2 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_FUNCTION_ATTRIBUTE_1);
		}
	;


 /*** END EXAMPLE - Change the example grammar rules above ***/

%% /*** Additional Code ***/

void NS_C512IR::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    driver.error(l, m);
}
