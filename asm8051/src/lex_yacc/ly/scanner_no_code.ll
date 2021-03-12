
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

%%

";"         { skip_comment(yylloc); TKEY_DEF( token::EOL,1,0);}
"\n" {TKEY_DEF( token::EOL,1,0);}

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


