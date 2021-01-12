/* $Id: scanner.ll 44 2008-10-23 09:03:19Z tb $ -*- mode: c++ -*- */
/** \file scanner.ll Define the example Flex lexical scanner */


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

#include "../asm_token.h"
#define YYSTYPE asm_token


#include "scanner.h"

/* import the parser's token type into a local typedef */
typedef asm_lex_stuff::Parser::token token;
typedef asm_lex_stuff::Parser::token_type token_type;

/* By default yylex returns int, we use token_type. Unfortunately yyterminate
 * by default returns 0, which is not of token_type. */
#define yyterminate() return token::END

/* This disables inclusion of unistd.h, which is not available under Visual C++
 * on Win32. The C++ scanner uses STL streams instead. */
#define YY_NO_UNISTD_H


#define TOKEN_DEFAULT_AC(tp,resv,vnum )   \
    { \
       yylval->m_resolved=resv; \
       yylval->num = vnum; \
       yylval->val_str=yytext; \
       yylval->line_no=yylloc->begin.line; \
       yylval->column_no=yylloc->begin.column; \
       yylval->type=tp; \
       return tp;\
    }

%}

/*** Flex Declarations and Options ***/

/* enable c++ scanner class generation */
%option c++

/* change the name of the scanner class. results in "ExampleFlexLexer" */
%option prefix="ASM"

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


";"         { skip_comment(); TOKEN_DEFAULT_AC( token::EOL,1,0);}

"A"         { TOKEN_DEFAULT_AC(token::TK_ACC,1,0);}
"C"         { TOKEN_DEFAULT_AC( token::TK_C,1,0);}
"AB"        { TOKEN_DEFAULT_AC( token::TK_AB,1,0);}
"@DPTR"     { TOKEN_DEFAULT_AC( token::TK_AT_DPTR,1,0);}
"DPTR"      { TOKEN_DEFAULT_AC( token::TK_DPTR,1,0);}
"@A+PC"     { TOKEN_DEFAULT_AC( token::TK_AT_A_PLUS_PC,1,0);}
"@A+DPTR"   { TOKEN_DEFAULT_AC( token::TK_AT_A_PLUS_DPTR,1,0);}
"@R0"       { yylval->num = 0;  TOKEN_DEFAULT_AC( token::TK_AT_RI,1,0);}
"@R1"       { yylval->num = 1; TOKEN_DEFAULT_AC( token::TK_AT_RI,1,1);}
"R0"     {yylval->num = 0; TOKEN_DEFAULT_AC( token::TK_RN,1,0);}
"R1"     {yylval->num = 1; TOKEN_DEFAULT_AC( token::TK_RN,1,1);}
"R2"     {yylval->num = 2; TOKEN_DEFAULT_AC( token::TK_RN,1,2);}
"R3"     {yylval->num = 3; TOKEN_DEFAULT_AC( token::TK_RN,1,3);}
"R4"     {yylval->num = 4; TOKEN_DEFAULT_AC( token::TK_RN,1,4);}
"R5"     {yylval->num = 5; TOKEN_DEFAULT_AC( token::TK_RN,1,5);}
"R6"     {yylval->num = 6; TOKEN_DEFAULT_AC( token::TK_RN,1,6);}
"R7"     {yylval->num = 7; TOKEN_DEFAULT_AC( token::TK_RN,1,7);}



"ACALL" {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"ADD"   {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"ADDC"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"AJMP"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"ANL"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"CJNE"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"CLR"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"CPL"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"DA"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"DEC"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"DIV"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"DJNZ"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"INC"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"JB"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"JBC"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"JC"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"JMP"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"JNB"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"JNC"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"JNZ"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"JZ"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"LCALL"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"LJMP"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"MOV"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"MOVC"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"MOVX"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"MUL"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"NOP"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"ORL"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"POP"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"PUSH"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"RET"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"RETI"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"RL"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"RLC"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"RR"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"RRC"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"SETB"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"SJMP"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"SUBB"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"SWAP"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"XCH"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"XCHD"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"XRL"  {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"CALL" {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}
"SIMTRAP"        {TOKEN_DEFAULT_AC( token::TK_CMD,1,0);}

"DB" {TOKEN_DEFAULT_AC( token::TK_DB,1,0);}
"DATA" {TOKEN_DEFAULT_AC( token::TK_MACRO,1,0);}
"XDATA" {TOKEN_DEFAULT_AC( token::TK_MACRO,1,0);}
"EQU" {TOKEN_DEFAULT_AC( token::TK_MACRO,1,0);}
"END" {TOKEN_DEFAULT_AC( token::TK_MACRO,1,0);}
"BIT" {TOKEN_DEFAULT_AC( token::TK_MACRO,1,0);}
"SBIT" {TOKEN_DEFAULT_AC( token::TK_MACRO,1,0);}
"ORG" {TOKEN_DEFAULT_AC( token::TK_MACRO,1,0);}
"SFR" {TOKEN_DEFAULT_AC( token::TK_MACRO,1,0);}
"$NOMOD51" {TOKEN_DEFAULT_AC( token::TK_MACRO,1,0);}
"USING" {TOKEN_DEFAULT_AC( token::TK_MACRO,1,0);}


"$"    { TOKEN_DEFAULT_AC( token::TK_DOLLAR,1,0);}
"NOT"    { TOKEN_DEFAULT_AC( token::TK_NOT,1,0);}
"HIGH"   { TOKEN_DEFAULT_AC( token::TK_HIGH,1,0);}
"LOW"   { TOKEN_DEFAULT_AC( token::TK_LOW,1,0);}
"SHL"   { TOKEN_DEFAULT_AC( token::TK_SHL,1,0);}
"MOD"   { TOKEN_DEFAULT_AC( token::TK_MOD,1,0);}

">>"     { TOKEN_DEFAULT_AC( token::TK_SHIFT_RIGHT,1,0);}
"<<"     { TOKEN_DEFAULT_AC( token::TK_SHIFT_LEFT,1,0);}

"\n" {TOKEN_DEFAULT_AC( token::EOL,1,0);}

{L}{A}*					{ /*各种标识符，修饰符等*/   TOKEN_DEFAULT_AC( token::TK_KEYWORD,0,0);



                            //{D}+{E}{FS}?				{ TOKEN_DEFAULT_AC( token::F_CONSTANT,0,0); }
                            //{D}*"."{D}+{E}?{FS}?			{ TOKEN_DEFAULT_AC( token::F_CONSTANT,0,0); }
                            //{D}+"."{E}?{FS}?			{ TOKEN_DEFAULT_AC( token::F_CONSTANT,0,0); }
                            //{HP}{H}+{P}{FS}?			{ TOKEN_DEFAULT_AC( token::F_CONSTANT,0,0); }
                            //{HP}{H}*"."{H}+{P}{FS}?			{ TOKEN_DEFAULT_AC( token::F_CONSTANT,0,0); }
                            //{HP}{H}+"."{P}{FS}?			{ TOKEN_DEFAULT_AC( token::F_CONSTANT,0,0); }


                            //({H}+{IS}?("H"|"h"))*"."{D}+{E}?{FS}?			{ TOKEN_DEFAULT_AC( token::TK_BIT_PT,0,0); }
                            //({H}+{IS}?("H"|"h"))+"."{E}?{FS}?			{ TOKEN_DEFAULT_AC( token::TK_BIT_PT,0,0); }
                            //({H}+{IS}?("H"|"h"))*"."{H}+{P}{FS}?			{ TOKEN_DEFAULT_AC( token::TK_BIT_PT,0,0); }
                            //({H}+{IS}?("H"|"h"))*"."{P}{FS}?			{ TOKEN_DEFAULT_AC( token::TK_BIT_PT,0,0); }


                            //([0-1]+{IS}?("B"|"b"))*"."{D}+{E}?{FS}?			{ TOKEN_DEFAULT_AC( token::TK_BIT_PT,0,0); }
                            //([0-1]+{IS}?("B"|"b"))+"."{E}?{FS}?			{ TOKEN_DEFAULT_AC( token::TK_BIT_PT,0,0); }
                            //([0-1]+{IS}?("B"|"b"))*"."{H}+{P}{FS}?			{ TOKEN_DEFAULT_AC( token::TK_BIT_PT,0,0); }
                            //([0-1]+{IS}?("B"|"b"))*"."{P}{FS}?			{ TOKEN_DEFAULT_AC( token::TK_BIT_PT,0,0); }

                            //{L}{A}*"."{D}+{E}?{FS}?			{ TOKEN_DEFAULT_AC( token::TK_BIT_PT,0,0); }
                            //{L}{A}+"."{E}?{FS}?				{ TOKEN_DEFAULT_AC( token::TK_BIT_PT,0,0); }
                            //{L}{A}*"."{H}+{P}{FS}?			{ TOKEN_DEFAULT_AC( token::TK_BIT_PT,0,0); }
                            //{L}{A}*"."{P}{FS}?			{ TOKEN_DEFAULT_AC( token::TK_BIT_PT,0,0); }

                            }




{HP}{H}+{IS}?				{  TOKEN_DEFAULT_AC( token::I_CONSTANT,1,0); }
{NZ}{D}*{IS}?				{  TOKEN_DEFAULT_AC( token::I_CONSTANT,1,0); }
"0"{O}*{IS}?				{ TOKEN_DEFAULT_AC( token::I_CONSTANT,1,0); }
{CP}?"'"([^'\\\n]|{ES})+"'"		{ TOKEN_DEFAULT_AC( token::I_CONSTANT,1,0); }
{H}+{IS}?("H"|"h")				{  TOKEN_DEFAULT_AC( token::I_CONSTANT,1,0); }
[0-1]+{IS}?("B"|"b")				{  TOKEN_DEFAULT_AC( token::I_CONSTANT,1,0); }



({SP}?\"([^"\\\n]|{ES})*\"{WS}*)+	{ TOKEN_DEFAULT_AC( token::STRING_LITERAL,1,0); }



"."					{ TOKEN_DEFAULT_AC( static_cast<token_type>('.'),1,0); }
"&"					{ TOKEN_DEFAULT_AC( static_cast<token_type>('&'),1,0); }
"!"					{ TOKEN_DEFAULT_AC( static_cast<token_type>('!'),1,0); }
"~"					{ TOKEN_DEFAULT_AC( static_cast<token_type>('~'),1,0); }

"-"					{ TOKEN_DEFAULT_AC( static_cast<token_type>('-'),1,0); }
"+"					{ TOKEN_DEFAULT_AC( static_cast<token_type>('+'),1,0); }
"*"					{ TOKEN_DEFAULT_AC( static_cast<token_type>('*'),1,0); }
"/"					{ TOKEN_DEFAULT_AC( static_cast<token_type>('/'),1,0); }

"%"					{ TOKEN_DEFAULT_AC( static_cast<token_type>('%'),1,0); }
"<"					{ TOKEN_DEFAULT_AC( static_cast<token_type>('<'),1,0); }
">"					{ TOKEN_DEFAULT_AC( static_cast<token_type>('>'),1,0); }
"^"					{ TOKEN_DEFAULT_AC( static_cast<token_type>('^'),1,0); }
"|"					{ TOKEN_DEFAULT_AC( static_cast<token_type>('|'),1,0); }
"?"					{ TOKEN_DEFAULT_AC( static_cast<token_type>('?'),1,0); }

"("				{ TOKEN_DEFAULT_AC( static_cast<token_type>('('),1,0); }
")"				{ TOKEN_DEFAULT_AC( static_cast<token_type>(')'),1,0); }

","					{ TOKEN_DEFAULT_AC( static_cast<token_type>(','),1,0); }
":"					{ TOKEN_DEFAULT_AC( static_cast<token_type>(':'),1,0); }
"="					{ TOKEN_DEFAULT_AC( static_cast<token_type>('='),1,0); }
"#"					{ TOKEN_DEFAULT_AC( static_cast<token_type>('#'),1,0); }

{WS}+					{ /* whitespace separates tokens */ }



 /* pass all other characters up to bison */
. {/* discard bad characters */
    //return static_cast<token_type>(*yytext);
}

 /*** END EXAMPLE - Change the example lexer rules above ***/

%% /*** Additional Code ***/

namespace asm_lex_stuff {

Scanner::Scanner(std::istream* in,
		 std::ostream* out)
    : ASMFlexLexer(in, out)
{
}

Scanner::~Scanner()
{
}

void Scanner::set_debug(bool b)
{
    yy_flex_debug = b;
}


void Scanner::skip_comment(void)
{
    int c;

    while ((c = yyinput()) != 0)
	{
        if (c == '\n')
        {
            
                return;
		}
	}
    std::cout<<"ERROR:"<<"unterminated comment"<<"line:"<<lineno();
}


}

/* This implementation of ASMFlexLexer::yylex() is required to fill the
 * vtable of the class ASMFlexLexer. We define the scanner's main yylex
 * function via YY_DECL to reside in the Scanner class instead. */

#ifdef yylex
#undef yylex
#endif

int ASMFlexLexer::yylex()
{
    std::cerr << "in ASMFlexLexer::yylex() !" << std::endl;
    return 0;
}

/* When the scanner receives an end-of-file indication from YY_INPUT, it then
 * checks the yywrap() function. If yywrap() returns false (zero), then it is
 * assumed that the function has gone ahead and set up `yyin' to point to
 * another input file, and scanning continues. If it returns true (non-zero),
 * then the scanner terminates, returning 0 to its caller. */

int ASMFlexLexer::yywrap()
{
    return 1;
}
