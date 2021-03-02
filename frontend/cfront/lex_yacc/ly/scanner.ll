/* $Id$ -*- mode: c++ -*- */
/** \file scanner.ll Define the example Flex lexical scanner */


/*octal--8进制数*/
/*dec--10进制数*/
/*non-zero 非零整数--10进制数*/
/*letter */
/*alpha*/
/*hex --16进制*/
/*HP hex prefix*/
/*E 1e100*/
/*P */
/*1234L*/


O   [0-7]
D   [0-9]
NZ  [1-9]
L   [a-zA-Z_]
A   [a-zA-Z_0-9]
H   [a-fA-F0-9]
HP  (0[xX])
E   ([Ee][+-]?{D}+)
P   ([Pp][+-]?{D}+)
FS  (f|F|l|L)
IS  (((u|U)(l|L|ll|LL)?)|((l|L|ll|LL)(u|U)?))
CP  (u|U|L)
SP  (u8|u|U|L)
ES  (\\(['"\?\\abfnrtv]|[0-7]{1,3}|x[a-fA-F0-9]+))
WS  [ \t\v\n\f]

%{ /*** C/C++ Declarations ***/

#include <string>

#include "comp_context.h"
#include "token_defs.h"
#include "driver.h"
#define YYSTYPE token_defs

#include "scanner.h"
#include "str2number.h"
#include "replace.h"
#include "mylog.h"

using mylog::cerr;

/* import the parser's token type into a local typedef */
typedef NS_C2IR::Parser::token token;
typedef NS_C2IR::Parser::token_type token_type;



/* By default yylex returns int, we use token_type. Unfortunately yyterminate
 * by default returns 0, which is not of token_type. */
#define yyterminate() return token::END

/* This disables inclusion of unistd.h, which is not available under Visual C++
 * on Win32. The C++ scanner uses STL streams instead. */
#define YY_NO_UNISTD_H

%}

/*** Flex Declarations and Options ***/

/* enable c++ scanner class generation */
%option c++

/* change the name of the scanner class. results in "ExampleFlexLexer" */
%option prefix="Example"

/* the manual says "somewhat more optimized" */
%option batch

/* enable scanner to generate debug output. disable this for release
 * versions. */
%option debug

/* no support for include files is planned */
%option yywrap nounput 

/* enables the use of start condition stacks */
%option stack

/* The following paragraph suffices to track locations accurately. Each time
 * yylex is invoked, the begin position is moved onto the end position. */
%{
#define YY_USER_ACTION  yylloc->columns(yyleng);
%}

%% /*** Regular Expressions Part ***/

 /* code to place at the beginning of yylex() */
%{
    // reset location
    yylloc->step();
%}

 /*** BEGIN EXAMPLE - Change the example lexer rules below ***/

"/*"                                    { this->skip_comment(yylloc); }
"//".*                                    { /* consume //-comment */ }


"auto"					{ TKEY_DEF(token::AUTO,1, 0); }
"break"					{ TKEY_DEF(token::BREAK,1, 0); }
"case"					{ TKEY_DEF(token::CASE,1, 0); }
"char"					{ TKEY_DEF(token::CHAR,1, 0); }
"const"					{ TKEY_DEF(token::CONST,1, 0); }
"continue"				{ TKEY_DEF(token::CONTINUE,1, 0); }
"default"				{ TKEY_DEF(token::DEFAULT,1,0); }
"do"					{ TKEY_DEF(token::DO,1, 0); }
"double"				{ TKEY_DEF(token::DOUBLE,1, 0); }
"else"					{ TKEY_DEF(token::ELSE,1, 0); }
"enum"					{ TKEY_DEF(token::ENUM,1, 0); }
"extern"				{ TKEY_DEF(token::EXTERN,1, 0); }
"float"					{ TKEY_DEF(token::FLOAT,1, 0); }
"for"					{ TKEY_DEF(token::FOR,1, 0); }
"goto"					{ TKEY_DEF(token::GOTO,1, 0); }
"if"					{ TKEY_DEF(token::IF,1, 0); }
"inline"				{ TKEY_DEF(token::INLINE,1, 0); }
"int"					{ TKEY_DEF(token::INT,1, 0); }
"long"					{ TKEY_DEF(token::LONG,1, 0); }
"register"				{ TKEY_DEF(token::REGISTER,1, 0); }
"restrict"				{ TKEY_DEF(token::RESTRICT,1, 0); }
"return"				{ TKEY_DEF(token::RETURN,1, 0); }
"short"					{ TKEY_DEF(token::SHORT,1, 0); }
"signed"				{ TKEY_DEF(token::SIGNED,1, 0); }
"sizeof"				{ TKEY_DEF(token::SIZEOF,1, 0); }
"static"				{ TKEY_DEF(token::STATIC,1, 0); }
"struct"				{ TKEY_DEF(token::STRUCT,1, 0); }
"switch"				{ TKEY_DEF(token::SWITCH,1, 0); }
"typedef"				{ TKEY_DEF(token::TYPEDEF,1, 0); }
"union"					{ TKEY_DEF(token::UNION,1, 0); }
"unsigned"				{ TKEY_DEF(token::UNSIGNED,1, 0); }
"void"					{ TKEY_DEF(token::VOID,1, 0); }
"volatile"				{ TKEY_DEF(token::VOLATILE,1, 0); }
"while"					{ TKEY_DEF(token::WHILE,1, 0); }
"_Alignas"                              { TKEY_DEF( token::ALIGNAS  ,1, 0)    ; }
"_Alignof"                              { TKEY_DEF( token::ALIGNOF ,1, 0 )    ; }
"_Atomic"                               { TKEY_DEF( token::ATOMIC  ,1, 0  )   ; }
"_Bool"                                 { TKEY_DEF( token::BOOL    ,1, 0   )  ;    }
"_Complex"                              { TKEY_DEF( token::COMPLEX ,1, 0    ) ; }
"_Generic"                              { TKEY_DEF( token::GENERIC   ,1, 0   ); }
"_Imaginary"                            { TKEY_DEF( token::IMAGINARY ,1, 0  )     ; }
"_Noreturn"                             { TKEY_DEF( token::NORETURN   ,1, 0 ) ; }
"_Static_assert"                        { TKEY_DEF( token::STATIC_ASSERT,1, 0 )   ; }
"_Thread_local"                         { TKEY_DEF( token::THREAD_LOCAL,1, 0 ); }
"__func__"                              { TKEY_DEF( token::FUNC_NAME ,1, 0   ); }



"#line".*                           { /*reset line and file_name here*/
                                        // #line 6 "C:/Program Files (x86)/Notepad++/plugins/MZC8051/inc/c8051/reg52.h"
                                        std::string yytext_str = yytext;
                                        replace(yytext_str, "#line ", "");

                                        std::string line_num_str = yytext_str.substr(0,yytext_str.find(' '));


                                        unsigned lineNum = StrToNumber(line_num_str);
                                        yytext_str = yytext_str.substr(yytext_str.find(' ')+1);

                                        //int file_start=5;
                                        //while((yytext[file_start]!=0)&&(yytext[file_start]!='\"')&&(file_start<20))file_start++;

                                        static std::string s_filename;
                                        s_filename= yytext_str;

                                        yylloc->initialize(&s_filename);
                                        yylloc->lines(lineNum);
                                        yylloc->step();
                                        //2020.6.30 去掉LINE_NUM的token。此处后期change_line_num函数就没用了
                                        //TKEY_DEF( token::LINE_NUM ,1, 0   );
                                        }

{L}{A}*					{ /*各种标识符，修饰符等*/ TKEY_DEF( static_cast<token_type> (driver.calc.check_type(std::string(yytext, yyleng))), 0, 0);}

{HP}{H}+{IS}?				{ TKEY_DEF( token::I_CONSTANT ,0, 0   ); }
{NZ}{D}*{IS}?				{ TKEY_DEF( token::I_CONSTANT ,0, 0   ); }
"0"{O}*{IS}?				{ TKEY_DEF( token::I_CONSTANT ,0, 0   ); }
{CP}?"'"([^'\\\n]|{ES})+"'"		{ TKEY_DEF( token::I_CONSTANT ,1, 0   ); }

{D}+{E}{FS}?				{ TKEY_DEF( token::F_CONSTANT ,0, 0   ); }
{D}*"."{D}+{E}?{FS}?			{ TKEY_DEF( token::F_CONSTANT ,0, 0   );  }
{D}+"."{E}?{FS}?			{ TKEY_DEF( token::F_CONSTANT ,0, 0   );  }
{HP}{H}+{P}{FS}?			{ TKEY_DEF( token::F_CONSTANT ,0, 0   );  }
{HP}{H}*"."{H}+{P}{FS}?			{ TKEY_DEF( token::F_CONSTANT ,0, 0   ); }
{HP}{H}+"."{P}{FS}?			{ TKEY_DEF( token::F_CONSTANT ,0, 0   );  }

({SP}?\"([^"\\\n]|{ES})*\"{WS}*)+	{  TKEY_DEF( token::STRING_LITERAL ,0, 0   );   }
"\"\"\""                            {  return multi_line_string(yylval, yylloc); }

"..."					{ TKEY_DEF(token::ELLIPSIS,1, 0   ); }
">>="					{ TKEY_DEF(token::RIGHT_ASSIGN,1, 0   ); }
"<<="					{ TKEY_DEF(token::LEFT_ASSIGN,1, 0   ); }
"+="					{ TKEY_DEF(token::ADD_ASSIGN,1, 0   ); }
"-="					{ TKEY_DEF(token::SUB_ASSIGN,1, 0   ); }
"*="					{ TKEY_DEF(token::MUL_ASSIGN,1, 0   ); }
"/="					{ TKEY_DEF(token::DIV_ASSIGN,1, 0   ); }
"%="					{ TKEY_DEF(token::MOD_ASSIGN,1, 0   ); }
"&="					{ TKEY_DEF(token::AND_ASSIGN,1, 0   ); }
"^="					{ TKEY_DEF(token::XOR_ASSIGN,1, 0   ); }
"|="					{ TKEY_DEF(token::OR_ASSIGN,1, 0   ); }
"><<"					{ TKEY_DEF(token::ROTATE_LEFT_OP,1, 0   ); }
">><"					{ TKEY_DEF(token::ROTATE_RIGHT_OP,1, 0   ); }
">>"					{ TKEY_DEF(token::RIGHT_OP,1, 0   ); }
"<<"					{ TKEY_DEF(token::LEFT_OP,1, 0   ); }
"++"					{ TKEY_DEF(token::INC_OP,1, 0   ); }
"--"					{ TKEY_DEF(token::DEC_OP,1, 0   ); }
"->"					{ TKEY_DEF(token::PTR_OP,1, 0   ); }
"&&"					{ TKEY_DEF(token::AND_OP,1, 0   ); }
"||"					{ TKEY_DEF(token::OR_OP,1, 0   ); }
"<="					{ TKEY_DEF(token::LE_OP,1, 0   ); }
">="					{ TKEY_DEF(token::GE_OP,1, 0   ); }
"=="					{ TKEY_DEF(token::EQ_OP,1, 0   ); }
"!="					{ TKEY_DEF(token::NE_OP,1, 0   ); }
";"                     { TKEY_DEF(static_cast<token_type>(';'), 1,0); }
("{"|"<%")				{ TKEY_DEF(static_cast<token_type>('{'), 1,0); }
("}"|"%>")				{ TKEY_DEF(static_cast<token_type>('}'), 1,0); }
","                     { TKEY_DEF(static_cast<token_type>(','), 1,0); }
":"                     { TKEY_DEF(static_cast<token_type>(':'), 1,0); }
"="                     { TKEY_DEF(static_cast<token_type>('='), 1,0); }
"("                     { TKEY_DEF(static_cast<token_type>('('), 1,0); }
")"                     { TKEY_DEF(static_cast<token_type>(')'), 1,0); }
("["|"<:")				{ TKEY_DEF(static_cast<token_type>('['), 1,0); }
("]"|":>")				{ TKEY_DEF(static_cast<token_type>(']'), 1,0); }
"."                     { TKEY_DEF(static_cast<token_type>('.'), 1,0); }
"&"                     { TKEY_DEF(static_cast<token_type>('&'), 1,0); }
"!"                     { TKEY_DEF(static_cast<token_type>('!'), 1,0); }
"~"                     { TKEY_DEF(static_cast<token_type>('~'), 1,0); }
"-"                     { TKEY_DEF(static_cast<token_type>('-'), 1,0); }
"+"                     { TKEY_DEF(static_cast<token_type>('+'), 1,0); }
"*"                     { TKEY_DEF(static_cast<token_type>('*'), 1,0); }
"/"                     { TKEY_DEF(static_cast<token_type>('/'), 1,0); }
"%"                     { TKEY_DEF(static_cast<token_type>('%'), 1,0); }
"<"                     { TKEY_DEF(static_cast<token_type>('<'), 1,0); }
">"                     { TKEY_DEF(static_cast<token_type>('>'), 1,0); }
"^"                     { TKEY_DEF(static_cast<token_type>('^'), 1,0); }
"|"                     { TKEY_DEF(static_cast<token_type>('|'), 1,0); }
"?"                     { TKEY_DEF(static_cast<token_type>('?'), 1,0); }





"\n" {
yylloc->lines(yyleng); yylloc->step();
}
{WS}+					{ /* whitespace separates tokens */ }



 /* gobble up end-of-lines
"\n" {
    yylloc->lines(yyleng); yylloc->step();
    return token::EOL;
}
*/



 /* pass all other characters up to bison */
. {/* discard bad characters */
    //return static_cast<token_type>(*yytext);
}

 /*** END EXAMPLE - Change the example lexer rules above ***/

%% /*** Additional Code ***/

namespace NS_C2IR {

Scanner::Scanner(class Driver &drv, std::istream* in,
		 std::ostream* out)
    : ExampleFlexLexer(in, out)
, driver(drv)
{
}

Scanner::~Scanner()
{
}

void Scanner::set_debug(bool b)
{
    yy_flex_debug = b;
}





void Scanner::skip_comment(Parser::location_type* yylloc)
{
    int c;

    while ((c = yyinput()) != 0)
    {
        if(c=='\n')
        {
            yylloc->lines();
            yylloc->step();
        }

        std::cout<<c;
        if (c == '*')
        {
            while ((c = yyinput()) == '*')
                ;

            if(c=='\n')
            {
                yylloc->lines();
               yylloc->step();
            }

            if (c == '/')
                return;

            if (c == 0)
                break;
        }
    }

    cerr<<"ERROR:"<<"unterminated comment"<<"line:"<<lineno();
}
Parser::token_type Scanner::multi_line_string(Parser::semantic_type* yylval, Parser::location_type* yylloc)
{
    std::string strA;
    strA = yytext;

    int quote_cnt=0;
    int c;
    int skip_next=0;

    while ((c = yyinput()) != 0)
    {
        strA.push_back(c);

        if(c!='\"')
        {
            quote_cnt=0;
        }

        if(skip_next)
        {
            skip_next=0;
            continue;
        }


        if(c=='\\')
        {
            skip_next=1;
        }
        else if(c=='\"')
        {
            quote_cnt++;
            if(quote_cnt==3)
            {
                //结束。返回
                yylval->val_str = strA;
                //yylval->m_tk_type.clear();
                yylval->num = 0;
                yylval->m_resolved = 1;
                yylval->line_no=yylloc->begin.line;
                yylval->column_no=yylloc->begin.column;
                yylval->m_token_type=token::STRING_LITERAL;
                yylval->m_type=TOKEN_DEFS_TYPE_ELEM;
                return token::STRING_LITERAL;
            }
        }
        else if(c=='\n')
        {
            yylloc->lines();
            yylloc->step();
        }
    }

    cerr<<"ERROR:"<<"unterminated comment"<<"line:"<<lineno()<<"\n";
    return (Parser::token_type)-1;
}

}

/* This implementation of ExampleFlexLexer::yylex() is required to fill the
 * vtable of the class ExampleFlexLexer. We define the scanner's main yylex
 * function via YY_DECL to reside in the Scanner class instead. */

#ifdef yylex
#undef yylex
#endif

int ExampleFlexLexer::yylex()
{
    std::cerr << "in ExampleFlexLexer::yylex() !" << std::endl;
    return 0;
}

/* When the scanner receives an end-of-file indication from YY_INPUT, it then
 * checks the yywrap() function. If yywrap() returns false (zero), then it is
 * assumed that the function has gone ahead and set up `yyin' to point to
 * another input file, and scanning continues. If it returns true (non-zero),
 * then the scanner terminates, returning 0 to its caller. */

int ExampleFlexLexer::yywrap()
{
    return 1;
}
