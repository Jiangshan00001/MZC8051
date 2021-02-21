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
AANDDOT [a-zA-Z_0-9_.]
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
typedef NS_IR2ICODE::Parser::token token;
typedef NS_IR2ICODE::Parser::token_type token_type;



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
%option prefix="IR2ICODE_"

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


"+{:"					{ TKEY_DEF(token::BLOCKS,1, 0); }
"+};"					{ TKEY_DEF(token::BLOCKE,1, 0); }
"{:"					{ TKEY_DEF(token::SCOPES,1, 0); }
"};"					{ TKEY_DEF(token::SCOPEE,1, 0); }
"def_var:"					{ TKEY_DEF(token::DEF_VAR,1, 0); }
"def_var_tmp:"				{ TKEY_DEF(token::DEF_VAR_TMP,1, 0); }
"def_arg:"				{ TKEY_DEF(token::DEF_ARG,1, 0); }

"#BS:"  { TKEY_DEF(token::LABEL_START, 1, 0); }
"@BS:"  { TKEY_DEF(token::LABEL_REF, 1, 0); }


"#line".*    { /*reset line and file_name here*/
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

"$"{L}{AANDDOT}*        { /*以$开头，是变量名字*/  TKEY_DEF(token::VAR_NAME_IDENTIFIER,1,0);  }
"%"{L}{AANDDOT}*        { /*以$开头，是变量名字*/  TKEY_DEF(token::VAR_REF,1,0);  }

"clist:"   			{ TKEY_DEF(token::CONST_LIST_ID, 1, 0); }
"iconst:"				{ TKEY_DEF(token::I_CONST_ID, 1, 0); }
"fconst:"				{ TKEY_DEF(token::F_CONST_ID, 1, 0); }
"cstring:"				{ TKEY_DEF(token::STRING_ID, 1, 0); }
"func:"					{ TKEY_DEF(token::FUNC_START, 1, 0); }
"func_end:"				{ TKEY_DEF(token::FUNC_END, 1, 0); }
"call:"					{ TKEY_DEF(token::CALL_START, 1, 0); }
"call_end:"				{ TKEY_DEF(token::CALL_END, 1, 0); }

"ret_type:"				{ TKEY_DEF(token::RET_TYPE, 1, 0); }
"opr:"					{ TKEY_DEF(token::OPR_START, 1, 0); }
"var_in:" 		{ TKEY_DEF(token::VAR_IN, 1, 0); }
"var_in_tmp:" 		{ TKEY_DEF(token::VAR_IN_TMP, 1, 0); }
"return;\n"     		{ TKEY_DEF(token::FUNC_RETURN, 1, 0); }
"asm:" {TKEY_DEF(token::INLINE_ASM, 1, 0);}


"null"		{ TKEY_DEF(token::VAR_NULL, 1, 0); }
"u0"  { TKEY_DEF(token::VOID,1,0); }
"void"  { TKEY_DEF(token::VOID,1,0); }
"u1"    { TKEY_DEF(token::U1,1,0); }
"u8"    { TKEY_DEF(token::U8,1,0); }
"u16"   { TKEY_DEF(token::U16,1,0); }
"u24"   { TKEY_DEF(token::U24,1,0); }
"u32"   { TKEY_DEF(token::U32,1,0); }
"u64"   { TKEY_DEF(token::U64,1,0); }
"i1"    { TKEY_DEF(token::I1,1,0); }
"i8"    { TKEY_DEF(token::I8,1,0); }
"i16"    { TKEY_DEF(token::I16,1,0); }
"i24"    { TKEY_DEF(token::I24,1,0); }
"i32"    { TKEY_DEF(token::I32,1,0); }
"i64"    { TKEY_DEF(token::I64,1,0); }
"f16"    { TKEY_DEF(token::F16,1,0); }
"f32"    { TKEY_DEF(token::F32,1,0); }
"f64"    { TKEY_DEF(token::F64,1,0); }


({SP}?\"([^"\\\n]|{ES})*\"{WS}*)+	{  TKEY_DEF( token::STRING_LITERAL ,0, 0   );   }
"\"\"\""                            {  return multi_line_string(yylval, yylloc); }


"u"{NZ}{D}* { TKEY_DEF(token::U_NUM,0,0); }



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

"*"    { TKEY_DEF( static_cast<token_type>('*') ,1, 0   );  }
"["    { TKEY_DEF( static_cast<token_type>('[') ,1, 0   );  }
"]"    { TKEY_DEF( static_cast<token_type>(']') ,1, 0   );  }
"-"    { TKEY_DEF( static_cast<token_type>('-') ,1, 0   );  }
{L}{A}*	{ /*各种标识符，修饰符等*/ TKEY_DEF( static_cast<token_type> (token::IDENTIFIER), 0, 0);}


                            /* gobble up end-of-lines*/
"\n" {
yylloc->lines(yyleng); yylloc->step();
}
{WS}+					{ /* whitespace separates tokens */ }


 /* pass all other characters up to bison */
. {/* discard bad characters */
    return static_cast<token_type>(*yytext);
}

 /*** END EXAMPLE - Change the example lexer rules above ***/

%% /*** Additional Code ***/

namespace NS_IR2ICODE {

Scanner::Scanner(class Driver &drv, std::istream* in,
		 std::ostream* out)
    : IR2ICODE_FlexLexer(in, out)
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

        //std::cout<<c;
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

int IR2ICODE_FlexLexer::yylex()
{
    std::cerr << "in ExampleFlexLexer::yylex() !" << std::endl;
    return 0;
}

/* When the scanner receives an end-of-file indication from YY_INPUT, it then
 * checks the yywrap() function. If yywrap() returns false (zero), then it is
 * assumed that the function has gone ahead and set up `yyin' to point to
 * another input file, and scanning continues. If it returns true (non-zero),
 * then the scanner terminates, returning 0 to its caller. */

int IR2ICODE_FlexLexer::yywrap()
{
    return 1;
}
