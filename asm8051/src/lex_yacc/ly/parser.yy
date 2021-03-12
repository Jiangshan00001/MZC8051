

%{ /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include "token_defs.h"

#include "comp_context.h"
#include "comp_context_gen_defs.h"
#define YYSTYPE token_defs

%}

/*** yacc/bison Declarations ***/

/* Require bison 2.3 or later */
%require "2.3"

/* add debug output code to generated parser. disable this for release
* versions. */
%debug

/* write out a header file containing the token defines */
%defines

/* use newer C++ skeleton file */
%skeleton "lalr1.cc"


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

            
%name-prefix="NS_AMS8051HEX"

%define "parser_class_name"  "Parser"


%token  TK_EXTERN  TK_CODE  TK_DATA  TK_BIT  TK_XDATA 
%token  TK_NUMBER  TK_PUBLIC  TK_SEGMENT  TK_EJECT  TK_XSEG 
%token  TK_RSEG  TK_AT  TK_CSEG  TK_DS  TK_DBIG 
%token  TK_EQU  TK_USING  TK_DB  TK_DW  EOL 
%token  TK_ACC  TK_C  TK_AB  TK_AT_DPTR  TK_DPTR 
%token  TK_AT_A_PLUS_PC  TK_AT_A_PLUS_DPTR  TK_AT_RI  TK_RN  I_CONSTANT 
%token  F_CONSTANT  STRING_LITERAL  TK_CMD  TK_MACRO  TK_KEYWORD 
%token  TK_DOLLAR  TK_NOT  TK_HIGH  TK_LOW  TK_SHL 
%token  TK_MOD  TK_SHIFT_LEFT  TK_SHIFT_RIGHT 
%token END 0 "end of file"




%start file

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

            
file
	: 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_FILE_1;
		$$.m_tk_type_int_list.push_back(IAN_FILE_1);
		driver.calc.parse_start_token($$);
		}
	|  prog_block 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_FILE_2);
		driver.calc.parse_start_token($$);
		}
	;
prog_block
	:  EOL 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_PROG_BLOCK_1);
		}
	|  cmd_text_line 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_PROG_BLOCK_2);
		}
	|  macro_text_line 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_PROG_BLOCK_3);
		}
	|  label_text_line 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_PROG_BLOCK_4);
		}
	|  prog_block  cmd_text_line 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_PROG_BLOCK_5;
		$$.m_tk_type_int_list.push_back(IAN_PROG_BLOCK_5);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  prog_block  macro_text_line 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_PROG_BLOCK_6;
		$$.m_tk_type_int_list.push_back(IAN_PROG_BLOCK_6);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  prog_block  label_text_line 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_PROG_BLOCK_7;
		$$.m_tk_type_int_list.push_back(IAN_PROG_BLOCK_7);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  prog_block  EOL 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_PROG_BLOCK_8;
		$$.m_tk_type_int_list.push_back(IAN_PROG_BLOCK_8);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	;
cmd_text_line
	:  TK_CMD  EOL 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_CMD_TEXT_LINE_1;
		$$.m_tk_type_int_list.push_back(IAN_CMD_TEXT_LINE_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  TK_CMD  opand  EOL 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_CMD_TEXT_LINE_2;
		$$.m_tk_type_int_list.push_back(IAN_CMD_TEXT_LINE_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  TK_CMD  opand  ','  opand  EOL 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_CMD_TEXT_LINE_3;
		$$.m_tk_type_int_list.push_back(IAN_CMD_TEXT_LINE_3);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		}
	|  TK_CMD  opand  ','  opand  ','  opand  EOL 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_CMD_TEXT_LINE_4;
		$$.m_tk_type_int_list.push_back(IAN_CMD_TEXT_LINE_4);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		$$.m_tk_elems.push_back(parser_ntoken($6));
		$$.m_tk_elems.push_back(parser_ntoken($7));
		}
	|  TK_CMD  opand  ','  opand  ','  opand  ','  opand  EOL 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_CMD_TEXT_LINE_5;
		$$.m_tk_type_int_list.push_back(IAN_CMD_TEXT_LINE_5);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		$$.m_tk_elems.push_back(parser_ntoken($6));
		$$.m_tk_elems.push_back(parser_ntoken($7));
		$$.m_tk_elems.push_back(parser_ntoken($8));
		$$.m_tk_elems.push_back(parser_ntoken($9));
		}
	;
opand
	:  expr 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_OPAND_1);
		}
	|  '#'  expr 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_OPAND_2;
		$$.m_tk_type_int_list.push_back(IAN_OPAND_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  '/'  expr 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_OPAND_3;
		$$.m_tk_type_int_list.push_back(IAN_OPAND_3);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  '/'  expr  '.'  expr 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_OPAND_4;
		$$.m_tk_type_int_list.push_back(IAN_OPAND_4);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	|  expr  '.'  expr 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_OPAND_5;
		$$.m_tk_type_int_list.push_back(IAN_OPAND_5);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  TK_ACC 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_OPAND_6);
		}
	|  TK_C 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_OPAND_7);
		}
	|  TK_AB 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_OPAND_8);
		}
	|  TK_AT_DPTR 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_OPAND_9);
		}
	|  TK_DPTR 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_OPAND_10);
		}
	|  TK_AT_A_PLUS_PC 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_OPAND_11);
		}
	|  TK_AT_A_PLUS_DPTR 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_OPAND_12);
		}
	|  TK_AT_RI 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_OPAND_13);
		}
	|  TK_RN 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_OPAND_14);
		}
	;
expr_elem
	:  TK_KEYWORD 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_EXPR_ELEM_1);
		}
	|  I_CONSTANT 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_EXPR_ELEM_2);
		}
	|  STRING_LITERAL 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_EXPR_ELEM_3);
		}
	|  TK_DOLLAR 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_EXPR_ELEM_4);
		}
	|  '('  expr  ')' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_EXPR_ELEM_5;
		$$.m_tk_type_int_list.push_back(IAN_EXPR_ELEM_5);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
not_expr
	:  expr_elem 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_NOT_EXPR_1);
		}
	|  TK_NOT  expr_elem 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_NOT_EXPR_2;
		$$.m_tk_type_int_list.push_back(IAN_NOT_EXPR_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  TK_HIGH  expr_elem 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_NOT_EXPR_3;
		$$.m_tk_type_int_list.push_back(IAN_NOT_EXPR_3);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  TK_LOW  expr_elem 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_NOT_EXPR_4;
		$$.m_tk_type_int_list.push_back(IAN_NOT_EXPR_4);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  expr_elem  TK_SHL  expr_elem 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_NOT_EXPR_5;
		$$.m_tk_type_int_list.push_back(IAN_NOT_EXPR_5);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  expr_elem  TK_MOD  expr_elem 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_NOT_EXPR_6;
		$$.m_tk_type_int_list.push_back(IAN_NOT_EXPR_6);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  expr_elem  '&'  expr_elem 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_NOT_EXPR_7;
		$$.m_tk_type_int_list.push_back(IAN_NOT_EXPR_7);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  expr_elem  TK_SHIFT_RIGHT  expr_elem 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_NOT_EXPR_8;
		$$.m_tk_type_int_list.push_back(IAN_NOT_EXPR_8);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  expr_elem  TK_SHIFT_LEFT  expr_elem 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_NOT_EXPR_9;
		$$.m_tk_type_int_list.push_back(IAN_NOT_EXPR_9);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
multi_expr
	:  not_expr 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_MULTI_EXPR_1);
		}
	|  multi_expr  '*'  not_expr 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_MULTI_EXPR_2;
		$$.m_tk_type_int_list.push_back(IAN_MULTI_EXPR_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  multi_expr  '/'  not_expr 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_MULTI_EXPR_3;
		$$.m_tk_type_int_list.push_back(IAN_MULTI_EXPR_3);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  multi_expr  '%'  not_expr 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_MULTI_EXPR_4;
		$$.m_tk_type_int_list.push_back(IAN_MULTI_EXPR_4);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
additive_expr
	:  multi_expr 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_ADDITIVE_EXPR_1);
		}
	|  additive_expr  '+'  multi_expr 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_ADDITIVE_EXPR_2;
		$$.m_tk_type_int_list.push_back(IAN_ADDITIVE_EXPR_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  additive_expr  '-'  multi_expr 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_ADDITIVE_EXPR_3;
		$$.m_tk_type_int_list.push_back(IAN_ADDITIVE_EXPR_3);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
expr
	:  additive_expr 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_EXPR_1);
		}
	;
macro_text_line
	:  TK_MACRO  EOL 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_MACRO_TEXT_LINE_1;
		$$.m_tk_type_int_list.push_back(IAN_MACRO_TEXT_LINE_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  TK_MACRO  expr_elem  EOL 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_MACRO_TEXT_LINE_2;
		$$.m_tk_type_int_list.push_back(IAN_MACRO_TEXT_LINE_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  TK_MACRO  expr_elem  expr_elem  EOL 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_MACRO_TEXT_LINE_3;
		$$.m_tk_type_int_list.push_back(IAN_MACRO_TEXT_LINE_3);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	|  TK_KEYWORD  TK_MACRO  opand  EOL 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_MACRO_TEXT_LINE_4;
		$$.m_tk_type_int_list.push_back(IAN_MACRO_TEXT_LINE_4);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	|  db_list  EOL 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_MACRO_TEXT_LINE_5;
		$$.m_tk_type_int_list.push_back(IAN_MACRO_TEXT_LINE_5);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	;
db_list
	:  TK_DB  opand 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DB_LIST_1;
		$$.m_tk_type_int_list.push_back(IAN_DB_LIST_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  db_list  ','  opand 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DB_LIST_2;
		$$.m_tk_type_int_list.push_back(IAN_DB_LIST_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	|  db_list  opand 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DB_LIST_3;
		$$.m_tk_type_int_list.push_back(IAN_DB_LIST_3);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	;
label_text_line
	:  TK_KEYWORD  ':' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_LABEL_TEXT_LINE_1;
		$$.m_tk_type_int_list.push_back(IAN_LABEL_TEXT_LINE_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	;

%% /*** Additional Code ***/
void  NS_AMS8051HEX::Parser::error
(const Parser::location_type& l,
            const std::string& m)
    {
        std::cout<<"ERROR:"<<l<<m<<std::endl;
    }

