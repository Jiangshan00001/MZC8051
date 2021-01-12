/* $Id: parser.yy 48 2009-09-05 08:07:10Z tb $ -*- mode: c++ -*- */
/** \file parser.yy Contains the example Bison parser source */

%{ /*** C/C++ Declarations ***/

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include "../asm_token.h"
#include "../asm8051_lex.h"
#define YYSTYPE asm_token


#include "driver.h"

%}

/*** yacc/bison Declarations ***/

/* Require bison 2.3 or later */
%require "2.3"

/* add debug output code to generated parser. disable this for release
 * versions. */
%debug

/* start symbol is named "start" */
%start startA

/* write out a header file containing the token defines */
%defines

/* use newer C++ skeleton file */
%skeleton "lalr1.cc"

/* namespace to enclose parser in */
%name-prefix="asm_lex_stuff"

/* set the parser's class identifier */
%define "parser_class_name" "Parser"

/* keep track of the current position within the input */
%locations
%initial-action
{
    // initialize the initial location object
    @$.begin.filename = @$.end.filename = &pdriver->m_stream_name;
};

/* The driver is passed by reference to the parser and to the scanner. This
 * provides a simple but effective pure interface, not relying on global
 * variables. */
%parse-param { class driver* pdriver }

/* verbose error messages */
%error-verbose

 /*** BEGIN EXAMPLE - Change the example grammar's tokens below ***/



%token	END	     0	"end of file"
%token	EOL	/**	"end of line"*/
%token TK_ACC  TK_C  TK_AB  TK_AT_DPTR  TK_DPTR  TK_AT_A_PLUS_PC TK_AT_A_PLUS_DPTR  TK_AT_RI  TK_RN
%token I_CONSTANT  F_CONSTANT  STRING_LITERAL
%token TK_CMD  TK_MACRO TK_KEYWORD TK_DOLLAR
%token TK_NOT TK_HIGH TK_LOW TK_SHL TK_MOD
%token TK_BIT_PT TK_DB TK_SHIFT_LEFT TK_SHIFT_RIGHT


 /*** END EXAMPLE - Change the example grammar's tokens above ***/

%{

#include "scanner.h"

/* this "connects" the bison parser in the driver to the flex scanner class
 * object. it defines the yylex() function call to pull the next token from the
 * current lexer object of the driver context. */
#undef yylex
#define yylex pdriver->m_lexer->lex

%}

%% /*** Grammar Rules ***/

 /*** BEGIN EXAMPLE - Change the example grammar rules below ***/

startA	:/* empty */
        | prog_block {$$=$1; pdriver->m_token_result=$$; pdriver->m_parse_success=1;}
		


prog_block : cmd_text_line  {$$=$1;}
            | macro_text_line {$$=$1;}
            | label_text_line {$$=$1;}
            | prog_block cmd_text_line  {$$.type=TOKEN_PARENT; $$.child_type=TOKEN_PARENT; $$.m_childs.push_back($1);$$.m_childs.push_back($2); }
            | prog_block macro_text_line {$$.type=TOKEN_PARENT; $$.child_type=TOKEN_PARENT; $$.m_childs.push_back($1);$$.m_childs.push_back($2); }
            | prog_block label_text_line {$$.type=TOKEN_PARENT; $$.child_type=TOKEN_PARENT; $$.m_childs.push_back($1);$$.m_childs.push_back($2); }
        ;

cmd_text_line: TK_CMD EOL  { $$=$1;$$.type=TOKEN_CMD;   }
            | TK_CMD opand  EOL { $$=$1;$$.type=TOKEN_PARENT; $$.child_type=TOKEN_CMD; $1.type=TOKEN_CMD; $$.m_childs.push_back($1); $$.m_childs.push_back($2);   }
            | TK_CMD opand ',' opand  EOL  {$$=$1;$$.type=TOKEN_PARENT; $$.child_type=TOKEN_CMD;$1.type=TOKEN_CMD; $$.m_childs.push_back($1); $$.m_childs.push_back($2); $$.m_childs.push_back($4);   }
            | TK_CMD opand ',' opand ',' opand   EOL {$$=$1;
                                                        $$.type=TOKEN_PARENT;
                                                        $$.child_type=TOKEN_CMD;
                                                        $1.type=TOKEN_CMD;
                                                        $$.m_childs.push_back($1);
                                                        $$.m_childs.push_back($2);
                                                        $$.m_childs.push_back($4);
                                                        $$.m_childs.push_back($6);
                                                        }
            | TK_CMD opand ',' opand ',' opand ',' opand   EOL {$$=$1;
                                                            $$.type=TOKEN_PARENT;
                                                            $$.child_type=TOKEN_CMD;
                                                            $1.type=TOKEN_CMD;
                                                            $$.m_childs.push_back($1);
                                                            $$.m_childs.push_back($2);
                                                            $$.m_childs.push_back($4);
                                                            $$.m_childs.push_back($6);
                                                            $$.m_childs.push_back($8);
                                                            }
        ;


opand: expr
        | '#' expr  {
                        $$.type=TOKEN_J_DATA;
                        $$.val_str="#"+$2.val_str;
                        $$.m_childs.push_back($2);
                        $$.m_resolved=0;
                    }
        | '/' expr  {
                        $$.type=TOKEN_DIV_NUM;
                        $$.val_str="/"+$2.val_str;
                        $$.m_childs.clear();
                        $$.m_childs.push_back($2);
                        $$.m_resolved=0;
                    }
        ;



expr_elem: TK_KEYWORD  {$$.type=TOKEN_KEYWORD;$$.val_str=$1.val_str; $$.m_resolved=0;}
        | I_CONSTANT   {$$.type=TOKEN_NUM;$$.val_str=$1.val_str; $$.num = StrToNumber($1.val_str); $$.m_resolved=1;}
        | STRING_LITERAL {$$.type=TOKEN_NUM;$$.val_str=$1.val_str;  $$.m_resolved=1;}
        | TK_ACC         {$$.type=TOKEN_ACC;$$.val_str=$1.val_str; $$.m_resolved=1;}
        | TK_C           {$$.type=TOKEN_C;$$.val_str=$1.val_str; $$.m_resolved=1;}
        | TK_AB          {$$.type=TOKEN_AB;$$.val_str=$1.val_str; $$.m_resolved=1;}
        | TK_AT_DPTR     {$$.type=TOKEN_AT_DPTR;$$.val_str=$1.val_str; $$.m_resolved=1;}
        | TK_DPTR        {$$.type=TOKEN_DPTR;$$.val_str=$1.val_str; $$.m_resolved=1;}
        | TK_AT_A_PLUS_PC {$$.type=TOKEN_AT_A_PLUS_PC;$$.val_str=$1.val_str; $$.m_resolved=1;}
        | TK_AT_A_PLUS_DPTR {$$.type=TOKEN_AT_A_PLUS_DPTR;$$.val_str=$1.val_str; $$.m_resolved=1;}
        | TK_AT_RI          {$$=$1; $$.type=TOKEN_AT_RI;$$.val_str=$1.val_str; $$.m_resolved=1;}
        | TK_RN             {$$=$1; $$.type=TOKEN_RN;$$.val_str=$1.val_str; $$.m_resolved=1;}
        | TK_DOLLAR                        {$$.type=TOKEN_KEYWORD;$$.val_str="$"; $$.m_resolved=0;}
        | '('  expr ')'     {
                            $$.type=TOKEN_PARENT;
                            $$.child_type=TOKEN_OPR;
                            $$.val_str="(" + $2.val_str +")";
                            $$.m_childs.clear();
                            $$.m_childs.push_back($1);
                            $$.m_childs.push_back($2);
                            $$.m_resolved=0;
                            }
        ;

not_expr: expr_elem           {$$=$1;}
         | TK_NOT expr_elem {
                             $$.type=TOKEN_PARENT;
                             $$.child_type=TOKEN_OPR;
                             $$.val_str=+"NOT " + $2.val_str;
                             $1.type=TOKEN_OPR;
                             $$.m_childs.push_back($1);
                             $$.m_childs.push_back($2);
                             $$.m_resolved=0;
                             }
        | TK_HIGH expr_elem {
                            $$.type=TOKEN_PARENT;
                            $$.child_type=TOKEN_OPR;
                            $$.val_str=+"HIGH " + $2.val_str;
                            $1.type=TOKEN_OPR;
                            $$.m_childs.push_back($1);
                            $$.m_childs.push_back($2);
                            $$.m_resolved=0;
                            }
        | TK_LOW expr_elem {
                            $$.type=TOKEN_PARENT;
                            $$.child_type=TOKEN_OPR;
                            $$.val_str=+"LOW " + $2.val_str;
                            $1.type=TOKEN_OPR;
                            $$.m_childs.push_back($1);
                            $$.m_childs.push_back($2);
                            $$.m_resolved=0;
                            }
        | expr_elem TK_SHL expr_elem {

                            $$.type=TOKEN_PARENT;
                            $$.child_type=TOKEN_OPR;
                            $$.val_str=$1.val_str + " SHL " + $3.val_str;
                            $2.type=TOKEN_OPR;
                            $$.m_childs.push_back($2);
                            $$.m_childs.push_back($1);
                            $$.m_childs.push_back($3);
                            $$.m_resolved=0;
                            }
        | expr_elem TK_MOD expr_elem {
                                $$.type=TOKEN_PARENT;
                                $$.child_type=TOKEN_OPR;
                                $$.val_str= $1.val_str +" MOD " + $3.val_str;
                                $2.type=TOKEN_OPR;
                                $$.m_childs.push_back($2);
                                $$.m_childs.push_back($1);
                                $$.m_childs.push_back($3);
                                $$.m_resolved=0;
                            }
        | expr_elem '.'  expr_elem {
                                    $$.type=TOKEN_PARENT;
                                    $$.child_type=TOKEN_OPR;
                                    $$.m_childs.push_back($2);
                                    $$.m_childs.push_back($1);
                                    $$.m_childs.push_back($3);
                                    $$.m_resolved=0;
                                    $$.val_str=$1.val_str+"."+$3.val_str;
                                    }
        | expr_elem '&'  expr_elem {
                                    $$.type=TOKEN_PARENT;
                                    $$.child_type=TOKEN_OPR;
                                    $$.m_childs.clear();
                                    $$.m_childs.push_back($2);
                                    $$.m_childs.push_back($1);
                                    $$.m_childs.push_back($3);
                                    $$.m_resolved=0;
                                    $$.val_str=$1.val_str+" & "+$3.val_str;
                                    }

        | expr_elem TK_SHIFT_RIGHT expr_elem {
                                    $$.type=TOKEN_PARENT;
                                    $$.child_type=TOKEN_OPR;
                                    $$.m_childs.clear();
                                    $$.m_childs.push_back($2);
                                    $$.m_childs.push_back($1);
                                    $$.m_childs.push_back($3);
                                    $$.m_resolved=0;
                                    $$.val_str=$1.val_str+" >> "+$3.val_str;
                                    }
        | expr_elem TK_SHIFT_LEFT expr_elem {
                                    $$.type=TOKEN_PARENT;
                                    $$.child_type=TOKEN_OPR;
                                    $$.m_childs.clear();
                                    $$.m_childs.push_back($2);
                                    $$.m_childs.push_back($1);
                                    $$.m_childs.push_back($3);
                                    $$.m_resolved=0;
                                    $$.val_str=$1.val_str+" << "+$3.val_str;
                                    }
                                    ;


multi_expr: not_expr                     {$$=$1;}
            | multi_expr '*' not_expr   {
                                        $$.type=TOKEN_PARENT;
                                        $$.child_type=TOKEN_OPR;
                                        $$.val_str=$1.val_str+"*" + $3.val_str;
                                        $2.type=TOKEN_OPR;
                                        $$.m_childs.push_back($2);
                                        $$.m_childs.push_back($1);
                                        $$.m_childs.push_back($3);
                                        $$.m_resolved=0;

                                        }
            | multi_expr '/' not_expr    {
                                        $$.type=TOKEN_PARENT;
                                        $$.child_type=TOKEN_OPR;
                                        $$.val_str=$1.val_str+"/" + $3.val_str;
                                        $2.type=TOKEN_OPR;
                                        $$.m_childs.push_back($2);
                                        $$.m_childs.push_back($1);
                                        $$.m_childs.push_back($3);
                                        $$.m_resolved=0;

                                        }
            | multi_expr '%' not_expr   {
                                    $$.type=TOKEN_PARENT;
                                    $$.child_type=TOKEN_OPR;
                                    $$.val_str=$1.val_str+"%" + $3.val_str;
                                    $2.type=TOKEN_OPR;
                                    $$.m_childs.push_back($2);
                                    $$.m_childs.push_back($1);
                                    $$.m_childs.push_back($3);
                                    $$.m_resolved=0;

                                    }
            ;


additive_expr:multi_expr  {$$=$1;}
            |  additive_expr '+' multi_expr {
                                        $$.type=TOKEN_PARENT;
                                        $$.child_type=TOKEN_OPR;
                                        $$.val_str=$1.val_str+"+" + $3.val_str;
                                        $2.type=TOKEN_OPR;
                                        $$.m_childs.push_back($2);
                                        $$.m_childs.push_back($1);
                                        $$.m_childs.push_back($3);
                                        $$.m_resolved=0;
                                        }
            |  additive_expr '-' multi_expr{
                                $$.type=TOKEN_PARENT;
                                $$.child_type=TOKEN_OPR;
                                $$.val_str=$1.val_str+"-" + $3.val_str;
                                $2.type=TOKEN_OPR;
                                $$.m_childs.push_back($2);
                                $$.m_childs.push_back($1);
                                $$.m_childs.push_back($3);
                                $$.m_resolved=0;

                                }
           ;


expr: additive_expr  {$$=$1;}
        ;



macro_text_line: TK_MACRO EOL  { $$.type=TOKEN_MACRO; $$.val_str = $1.val_str;  }
                | TK_MACRO expr_elem EOL {
                                            $$.type=TOKEN_PARENT;
                                            $$.child_type = TOKEN_MACRO;
                                            $1.type=TOKEN_MACRO;
                                            $$.m_childs.push_back($1);
                                            $$.m_childs.push_back($2);
                                            }
                | TK_MACRO expr_elem expr_elem EOL {
                                            $$.type=TOKEN_PARENT;
                                            $$.child_type = TOKEN_MACRO;
                                            $1.type=TOKEN_MACRO;
                                            $$.m_childs.push_back($1);
                                            $$.m_childs.push_back($2);
                                            $$.m_childs.push_back($3);
                                            }
                | TK_KEYWORD  TK_MACRO opand EOL {
                                            $$.type=TOKEN_PARENT;
                                            $$.child_type = TOKEN_MACRO;
                                            $1.type=TOKEN_KEYWORD;
                                            $2.type=TOKEN_MACRO;
                                            $$.m_childs.push_back($1);
                                            $$.m_childs.push_back($2);
                                            $$.m_childs.push_back($3);
                                            }
                | db_list  EOL            {
                                                $$=$1;
                                            }
                ;


db_list: TK_DB opand                    { $$.type=TOKEN_DB; $$.m_childs.push_back($2); }
        | db_list ',' opand              { $$=$1; $$.m_childs.push_back($3); }
        | db_list   opand              { $$=$1; $$.m_childs.push_back($2); }
        ;


label_text_line: TK_KEYWORD ':'   {$$.type = TOKEN_LABEL; $$.val_str = $1.val_str; $$.m_resolved=1; }
                | label_text_line EOL {$$=$1;}
                ;

 /*** END EXAMPLE - Change the example grammar rules above ***/

%% /*** Additional Code ***/

void asm_lex_stuff::Parser::error(const Parser::location_type& l,
			    const std::string& m)
{
    std::cout<<"ERROR:"<<l<<m<<std::endl;
}
