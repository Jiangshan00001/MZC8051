
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
WS  [ \t\v\f]
/*remove \n from WS*/




%{ /*** C/C++ Declarations ***/

#include <string>

#include "token_defs.h"
#define YYSTYPE token_defs

#include "scanner.h"

/* import the parser's token type into a local typedef */
typedef NS_AMS8051HEX::Parser::token token;
typedef NS_AMS8051HEX::Parser::token_type token_type;

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

/* change the name of the scanner class. results in "ExampleFlexLexer" --Example */
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
#define YY_USER_ACTION  {yylloc->step();yylloc->columns(yyleng);}
%}

/* code to place at the beginning of yylex() */
%{
// reset location
//yylloc->step();
%}

/*** BEGIN EXAMPLE - Change the example lexer rules below ***/

%% /*** Regular Expressions Part ***/

            
"//"         { skip_comment(yylloc); yylloc->lines(1); TKEY_DEF( token::EOL,1,0);}
";"         { skip_comment(yylloc); yylloc->lines(1); TKEY_DEF( token::EOL,1,0);}
"\n" {yylloc->lines(1); TKEY_DEF( token::EOL,1,0);}

"A"         { TKEY_DEF(token::TK_ACC,1,0);}
"C"         { TKEY_DEF( token::TK_C,1,0);}
"AB"        { TKEY_DEF( token::TK_AB,1,0);}
"@DPTR"     { TKEY_DEF( token::TK_AT_DPTR,1,0);}
"DPTR"      { TKEY_DEF( token::TK_DPTR,1,0);}
"@A+PC"     { TKEY_DEF( token::TK_AT_A_PLUS_PC,1,0);}
"@A+DPTR"   { TKEY_DEF( token::TK_AT_A_PLUS_DPTR,1,0);}
"@R0"       { TKEY_DEF( token::TK_AT_RI,1,0);}
"@R1"       { TKEY_DEF( token::TK_AT_RI,1,1);}
"R0"     {TKEY_DEF( token::TK_RN,1,0);}
"R1"     {TKEY_DEF( token::TK_RN,1,1);}
"R2"     {TKEY_DEF( token::TK_RN,1,2);}
"R3"     {TKEY_DEF( token::TK_RN,1,3);}
"R4"     {TKEY_DEF( token::TK_RN,1,4);}
"R5"     {TKEY_DEF( token::TK_RN,1,5);}
"R6"     {TKEY_DEF( token::TK_RN,1,6);}
"R7"     {TKEY_DEF( token::TK_RN,1,7);}


"ACALL" {TKEY_DEF( token::TK_CMD,1,0);}
"ADD"   {TKEY_DEF( token::TK_CMD,1,0);}
"ADDC"  {TKEY_DEF( token::TK_CMD,1,0);}
"AJMP"  {TKEY_DEF( token::TK_CMD,1,0);}
"ANL"  {TKEY_DEF( token::TK_CMD,1,0);}
"CJNE"  {TKEY_DEF( token::TK_CMD,1,0);}
"CLR"  {TKEY_DEF( token::TK_CMD,1,0);}
"CPL"  {TKEY_DEF( token::TK_CMD,1,0);}
"DA"  {TKEY_DEF( token::TK_CMD,1,0);}
"DEC"  {TKEY_DEF( token::TK_CMD,1,0);}
"DIV"  {TKEY_DEF( token::TK_CMD,1,0);}
"DJNZ"  {TKEY_DEF( token::TK_CMD,1,0);}
"INC"  {TKEY_DEF( token::TK_CMD,1,0);}
"JB"  {TKEY_DEF( token::TK_CMD,1,0);}
"JBC"  {TKEY_DEF( token::TK_CMD,1,0);}
"JC"  {TKEY_DEF( token::TK_CMD,1,0);}
"JMP"  {TKEY_DEF( token::TK_CMD,1,0);}
"JNB"  {TKEY_DEF( token::TK_CMD,1,0);}
"JNC"  {TKEY_DEF( token::TK_CMD,1,0);}
"JNZ"  {TKEY_DEF( token::TK_CMD,1,0);}
"JZ"  {TKEY_DEF( token::TK_CMD,1,0);}
"LCALL"  {TKEY_DEF( token::TK_CMD,1,0);}
"LJMP"  {TKEY_DEF( token::TK_CMD,1,0);}
"MOV"  {TKEY_DEF( token::TK_CMD,1,0);}
"MOVC"  {TKEY_DEF( token::TK_CMD,1,0);}
"MOVX"  {TKEY_DEF( token::TK_CMD,1,0);}
"MUL"  {TKEY_DEF( token::TK_CMD,1,0);}
"NOP"  {TKEY_DEF( token::TK_CMD,1,0);}
"ORL"  {TKEY_DEF( token::TK_CMD,1,0);}
"POP"  {TKEY_DEF( token::TK_CMD,1,0);}
"PUSH"  {TKEY_DEF( token::TK_CMD,1,0);}
"RET"  {TKEY_DEF( token::TK_CMD,1,0);}
"RETI"  {TKEY_DEF( token::TK_CMD,1,0);}
"RL"  {TKEY_DEF( token::TK_CMD,1,0);}
"RLC"  {TKEY_DEF( token::TK_CMD,1,0);}
"RR"  {TKEY_DEF( token::TK_CMD,1,0);}
"RRC"  {TKEY_DEF( token::TK_CMD,1,0);}
"SETB"  {TKEY_DEF( token::TK_CMD,1,0);}
"SJMP"  {TKEY_DEF( token::TK_CMD,1,0);}
"SUBB"  {TKEY_DEF( token::TK_CMD,1,0);}
"SWAP"  {TKEY_DEF( token::TK_CMD,1,0);}
"XCH"  {TKEY_DEF( token::TK_CMD,1,0);}
"XCHD"  {TKEY_DEF( token::TK_CMD,1,0);}
"XRL"  {TKEY_DEF( token::TK_CMD,1,0);}
"CALL" {TKEY_DEF( token::TK_CMD,1,0);}
"SIMTRAP"        {TKEY_DEF( token::TK_CMD,1,0);}




"acall" {TKEY_DEF( token::TK_CMD,1,0);}
"add"   {TKEY_DEF( token::TK_CMD,1,0);}
"addc"  {TKEY_DEF( token::TK_CMD,1,0);}
"ajmp"  {TKEY_DEF( token::TK_CMD,1,0);}
"anl"  {TKEY_DEF( token::TK_CMD,1,0);}
"cjne"  {TKEY_DEF( token::TK_CMD,1,0);}
"clr"  {TKEY_DEF( token::TK_CMD,1,0);}
"cpl"  {TKEY_DEF( token::TK_CMD,1,0);}
"da"  {TKEY_DEF( token::TK_CMD,1,0);}
"dec"  {TKEY_DEF( token::TK_CMD,1,0);}
"div"  {TKEY_DEF( token::TK_CMD,1,0);}
"djnz"  {TKEY_DEF( token::TK_CMD,1,0);}
"inc"  {TKEY_DEF( token::TK_CMD,1,0);}
"jb"  {TKEY_DEF( token::TK_CMD,1,0);}
"jbc"  {TKEY_DEF( token::TK_CMD,1,0);}
"jc"  {TKEY_DEF( token::TK_CMD,1,0);}
"jmp"  {TKEY_DEF( token::TK_CMD,1,0);}
"jnb"  {TKEY_DEF( token::TK_CMD,1,0);}
"jnc"  {TKEY_DEF( token::TK_CMD,1,0);}
"jnz"  {TKEY_DEF( token::TK_CMD,1,0);}
"jz"  {TKEY_DEF( token::TK_CMD,1,0);}
"lcall"  {TKEY_DEF( token::TK_CMD,1,0);}
"ljmp"  {TKEY_DEF( token::TK_CMD,1,0);}
"mov"  {TKEY_DEF( token::TK_CMD,1,0);}
"movc"  {TKEY_DEF( token::TK_CMD,1,0);}
"movx"  {TKEY_DEF( token::TK_CMD,1,0);}
"mul"  {TKEY_DEF( token::TK_CMD,1,0);}
"nop"  {TKEY_DEF( token::TK_CMD,1,0);}
"orl"  {TKEY_DEF( token::TK_CMD,1,0);}
"pop"  {TKEY_DEF( token::TK_CMD,1,0);}
"push"  {TKEY_DEF( token::TK_CMD,1,0);}
"ret"  {TKEY_DEF( token::TK_CMD,1,0);}
"reti"  {TKEY_DEF( token::TK_CMD,1,0);}
"rl"  {TKEY_DEF( token::TK_CMD,1,0);}
"rlc"  {TKEY_DEF( token::TK_CMD,1,0);}
"rr"  {TKEY_DEF( token::TK_CMD,1,0);}
"rrc"  {TKEY_DEF( token::TK_CMD,1,0);}
"setb"  {TKEY_DEF( token::TK_CMD,1,0);}
"sjmp"  {TKEY_DEF( token::TK_CMD,1,0);}
"subb"  {TKEY_DEF( token::TK_CMD,1,0);}
"swap"  {TKEY_DEF( token::TK_CMD,1,0);}
"xch"  {TKEY_DEF( token::TK_CMD,1,0);}
"xchd"  {TKEY_DEF( token::TK_CMD,1,0);}
"xrl"  {TKEY_DEF( token::TK_CMD,1,0);}
"call" {TKEY_DEF( token::TK_CMD,1,0);}
"simtrap"        {TKEY_DEF( token::TK_CMD,1,0);}



"DB" {TKEY_DEF( token::TK_DB,1,0);}
"USING" {TKEY_DEF( token::TK_MACRO,1,0);}
"DATA" {TKEY_DEF( token::TK_MACRO,1,0);}
"XDATA" {TKEY_DEF( token::TK_MACRO,1,0);}
"EQU" {TKEY_DEF( token::TK_MACRO,1,0);}
"END" {TKEY_DEF( token::TK_MACRO,1,0);}
"BIT" {TKEY_DEF( token::TK_MACRO,1,0);}
"SBIT" {TKEY_DEF( token::TK_MACRO,1,0);}
"ORG" {TKEY_DEF( token::TK_MACRO,1,0);}
"SFR" {TKEY_DEF( token::TK_MACRO,1,0);}
"$NOMOD51" {TKEY_DEF( token::TK_MACRO,1,0);}

"db" {TKEY_DEF( token::TK_DB,1,0);}
"using" {TKEY_DEF( token::TK_MACRO,1,0);}
"data" {TKEY_DEF( token::TK_MACRO,1,0);}
"xdata" {TKEY_DEF( token::TK_MACRO,1,0);}
"equ" {TKEY_DEF( token::TK_MACRO,1,0);}
"end" {TKEY_DEF( token::TK_MACRO,1,0);}
"bit" {TKEY_DEF( token::TK_MACRO,1,0);}
"sbit" {TKEY_DEF( token::TK_MACRO,1,0);}
"org" {TKEY_DEF( token::TK_MACRO,1,0);}
"sfr" {TKEY_DEF( token::TK_MACRO,1,0);}
"$nomod51" {TKEY_DEF( token::TK_MACRO,1,0);}






"$"    { TKEY_DEF( token::TK_DOLLAR,1,0);}
"NOT"    { TKEY_DEF( token::TK_NOT,1,0);}
"HIGH"   { TKEY_DEF( token::TK_HIGH,1,0);}
"LOW"   { TKEY_DEF( token::TK_LOW,1,0);}
"SHL"   { TKEY_DEF( token::TK_SHL,1,0);}
"MOD"   { TKEY_DEF( token::TK_MOD,1,0);}

">>"     { TKEY_DEF( token::TK_SHIFT_RIGHT,1,0);}
"<<"     { TKEY_DEF( token::TK_SHIFT_LEFT,1,0);}




"EXTERN" { TKEY_DEF( token::TK_EXTERN,1,0);}
"CODE" { TKEY_DEF( token::TK_CODE,1,0);}


{L}{A}*					{ /*各种标识符，修饰符等*/   TKEY_DEF( token::TK_KEYWORD,0,0);
}


{HP}{H}+{IS}?				{  TKEY_DEF( token::I_CONSTANT,1,0); }
{NZ}{D}*{IS}?				{  TKEY_DEF( token::I_CONSTANT,1,0); }
"0"{O}*{IS}?				{ TKEY_DEF( token::I_CONSTANT,1,0); }
{CP}?"'"([^'\\\n]|{ES})+"'"		{ TKEY_DEF( token::I_CONSTANT,1,0); }
{H}+{IS}?("H"|"h")				{  TKEY_DEF( token::I_CONSTANT,1,0); }
[0-1]+{IS}?("B"|"b")				{  TKEY_DEF( token::I_CONSTANT,1,0); }



({SP}?\"([^"\\\n]|{ES})*\"{WS}*)+	{ TKEY_DEF( token::STRING_LITERAL,1,0); }


"."					{ TKEY_DEF( static_cast<token_type>('.'),1,0); }
"&"					{ TKEY_DEF( static_cast<token_type>('&'),1,0); }
"!"					{ TKEY_DEF( static_cast<token_type>('!'),1,0); }
"~"					{ TKEY_DEF( static_cast<token_type>('~'),1,0); }

"-"					{ TKEY_DEF( static_cast<token_type>('-'),1,0); }
"+"					{ TKEY_DEF( static_cast<token_type>('+'),1,0); }
"*"					{ TKEY_DEF( static_cast<token_type>('*'),1,0); }
"/"					{ TKEY_DEF( static_cast<token_type>('/'),1,0); }

"%"					{ TKEY_DEF( static_cast<token_type>('%'),1,0); }
"<"					{ TKEY_DEF( static_cast<token_type>('<'),1,0); }
">"					{ TKEY_DEF( static_cast<token_type>('>'),1,0); }
"^"					{ TKEY_DEF( static_cast<token_type>('^'),1,0); }
"|"					{ TKEY_DEF( static_cast<token_type>('|'),1,0); }
"?"					{ TKEY_DEF( static_cast<token_type>('?'),1,0); }

"("				{ TKEY_DEF( static_cast<token_type>('('),1,0); }
")"				{ TKEY_DEF( static_cast<token_type>(')'),1,0); }

","					{ TKEY_DEF( static_cast<token_type>(','),1,0); }
":"					{ TKEY_DEF( static_cast<token_type>(':'),1,0); }
"="					{ TKEY_DEF( static_cast<token_type>('='),1,0); }
"#"					{ TKEY_DEF( static_cast<token_type>('#'),1,0); }

{WS}+					{ /* whitespace separates tokens */ }



%%
namespace NS_AMS8051HEX
             {


            Scanner::Scanner(class Driver &drv, std::istream* in,
                     std::ostream* out)
                : ASMFlexLexer(in, out)
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
            