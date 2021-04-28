/**
2001.1.7 添加 var_attrib 变量属性


*/
/* start symbol is named "start" */
%start file

%token			END	
%token			EOL	


%token BLOCKS BLOCKE SCOPES SCOPEE
%token DEF_VAR DEF_VAR_TMP
%token VAR_IN VAR_IN_TMP
%token DEF_ARG
%token VOID U1 U8 U16 U24 U32 U64
%token F16 F32 F64
%token I1 I8 I16 I24 I32 I64
%token U_NUM
%token LABEL_START  LABEL_REF
%token VAR_REF
%token VAR_NULL
%token FUNC_START FUNC_END FUNC_RETURN
%token CALL_START CALL_END
%token RET_TYPE

%token  IDENTIFIER VAR_NAME_IDENTIFIER
%token  I_CONST_ID  F_CONST_ID  STRING_ID CONST_LIST_ID
%token	I_CONSTANT F_CONSTANT STRING_LITERAL
%token OPR_START
%token INLINE_ASM
/*
%token	TYPEDEF EXTERN STATIC AUTO REGISTER INLINE
%token	CONST RESTRICT VOLATILE
%token	BOOL CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE VOID
%token	COMPLEX IMAGINARY
%token	STRUCT UNION ENUM ELLIPSIS

%token	CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%token	ALIGNAS ALIGNOF ATOMIC GENERIC NORETURN STATIC_ASSERT THREAD_LOCAL

%token 	 SFR BIT SBIT SFR16 SFR32
%token  INTERRUPT USING REENTRANT REGPARAMS
%token STORAGE_SPEC_C51
*/

%% 
file
        : /*empty*/
        | translation_unit
        | BLOCKS translation_unit BLOCKE
        ;

translation_unit
        : external_declaration
        | translation_unit external_declaration
        ;

external_declaration
        : block_item
        | function_definition
        ;



function_decl
        : FUNC_START VAR_NAME_IDENTIFIER ';' ret_type   FUNC_END VAR_REF ';'
        | FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib  ';' ret_type   FUNC_END VAR_REF ';'
        | FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg    FUNC_END VAR_REF ';'
        | FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib  ';' ret_type function_arg   FUNC_END VAR_REF ';'
        ;

/* first4 is function definition. last4 is function declaration*/
function_definition
        : FUNC_START VAR_NAME_IDENTIFIER ';' ret_type compound_statement  FUNC_END VAR_REF ';'
        | FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib  ';' ret_type compound_statement  FUNC_END VAR_REF ';'
        | FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg  compound_statement  FUNC_END VAR_REF ';'
        | FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib  ';' ret_type function_arg  compound_statement  FUNC_END VAR_REF ';'
        | function_decl
        ;

/* func_attrib 和 var_attrib 合并为1个*/

func_attrib : func_attrib1
            | func_attrib ',' func_attrib1
            ;

func_attrib1 : IDENTIFIER '('  STRING_LITERAL  ')'
            | IDENTIFIER '('  I_CONSTANT  ')'
            ;

declarations
        : def_one_var
        | declarations def_one_var
        ;


function_arg : def_arg
            | function_arg def_arg
            ;


ret_type :  RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier  ';'
          ;
def_arg :  DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier  ';'
        ;


def_one_var : def_var_start  VAR_NAME_IDENTIFIER ','  type_specifier  ';'
        ;


def_var_start : DEF_VAR
            | DEF_VAR_TMP
            ;


type_specifier : type_specifier_basic
                | type_specifier_basic '(' declarations   ')' /* struct: def_var: $c,u24(def_var: $c.a,i16;def_var: $c.b,u8;); */
                | type_specifier_basic '(' '(' declarations   ')' ')'  /* union */
                |  type_specifier_basic '*' I_CONSTANT '*' '['  type_specifier ']'   /* ptr */
                |  type_specifier  '['  type_specifier ']'   /* array: def_var: $a,u80[i16][iconst:0x5:0x8]; */
                |  type_specifier   '['  opr_elem ']'
                | type_specifier ','  func_attrib
                | function_decl
                ;

type_specifier_basic : VOID
            | U1
            | U8
            | U16
            | U24
            | U32
            | U64
            | F16
            | F32
            | F64
            | I1
            | I8
            | I16
            | I24
            | I32
            | I64
            | U_NUM
            ;


compound_statement
        : SCOPES SCOPEE
        | SCOPES  block_item_list  SCOPEE
        ;



block_item_list
        : block_item
        | block_item_list block_item
        ;


block_item
        : def_one_var
        | statement
        ;


statement
        : opr_statement
        | call_statement
        | FUNC_RETURN
        | label_def
        | inline_asm
        | compound_statement
        ;

opr_statement
            : OPR_START STRING_LITERAL ',' opr_elem ';' ',' opr_elem ';' ',' opr_elem ';'
            ;

opr_elem : VAR_NULL
            | VAR_REF
            | constant
            | var_in_ref
            | label_ref
            ;

constant
        : i_const
        | f_const
        | string
        | const_list
        ;

i_const : I_CONST_ID I_CONSTANT
        | I_CONST_ID I_CONSTANT ':' I_CONSTANT
        | I_CONST_ID '-' I_CONSTANT ':' I_CONSTANT
        ;

f_const : F_CONST_ID F_CONSTANT
        | F_CONST_ID I_CONSTANT
        | F_CONST_ID I_CONSTANT ':' I_CONSTANT
        | F_CONST_ID F_CONSTANT ':' I_CONSTANT
        | F_CONST_ID '-' I_CONSTANT ':' I_CONSTANT
        | F_CONST_ID '-' F_CONSTANT ':' I_CONSTANT
    ;

string :   STRING_ID STRING_LITERAL
    ;

var_in_ref : var_in_ref_ptr
            | var_in_ref_array
            ;



var_in_ref_ptr : var_in_start VAR_REF '*'  I_CONSTANT
            ;

var_in_ref_array : var_in_start VAR_REF '[' opr_elem  ']'
                    | var_in_ref_array  '[' opr_elem  ']'
                    ;


const_list : CONST_LIST_ID '[' opr_elem_seq  ']'
        ;

var_in_start : VAR_IN
            | VAR_IN_TMP
            ;



call_statement : CALL_START  VAR_REF ';' opr_elem_seq CALL_END  VAR_REF ';'
             | CALL_START  VAR_REF ';'  CALL_END  VAR_REF ';'
    ;

opr_elem_seq :   opr_elem ';'
                | opr_elem_seq opr_elem ';'
                ;

label_def : LABEL_START IDENTIFIER ';'
            ;

label_ref : LABEL_REF  IDENTIFIER
        ;

inline_asm : INLINE_ASM STRING_LITERAL ';'

