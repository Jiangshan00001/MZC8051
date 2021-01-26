
%token  END  EOL  BLOCKS  BLOCKE  SCOPES 
%token  SCOPEE  DEF_VAR  DEF_VAR_TMP  VAR_IN  VAR_IN_TMP 
%token  DEF_ARG  VOID  U1  U8  U16 
%token  U24  U32  U64  F16  F32 
%token  F64  I1  I8  I16  I24 
%token  I32  I64  U_NUM  LABEL_START  LABEL_REF 
%token  VAR_REF  VAR_NULL  FUNC_START  FUNC_END  FUNC_RETURN 
%token  CALL_START  CALL_END  RET_TYPE  IDENTIFIER  VAR_NAME_IDENTIFIER 
%token  I_CONST_ID  F_CONST_ID  STRING_ID  CONST_LIST_ID  I_CONSTANT 
%token  F_CONSTANT  STRING_LITERAL  OPR_START  INLINE_ASM 



%start file
%%
file
	:  /*empty*/ 
	|  translation_unit 
	|  BLOCKS  translation_unit  BLOCKE 
	;
translation_unit
	:  external_declaration 
	|  translation_unit  external_declaration 
	;
external_declaration
	:  block_item 
	|  function_definition 
	;
function_definition
	:  FUNC_START  VAR_NAME_IDENTIFIER  ';'  ret_type  compound_statement  FUNC_END  VAR_REF  ';' 
	|  FUNC_START  VAR_NAME_IDENTIFIER  ','  func_attrib  ';'  ret_type  compound_statement  FUNC_END  VAR_REF  ';' 
	|  FUNC_START  VAR_NAME_IDENTIFIER  ';'  ret_type  function_arg  compound_statement  FUNC_END  VAR_REF  ';' 
	|  FUNC_START  VAR_NAME_IDENTIFIER  ','  func_attrib  ';'  ret_type  function_arg  compound_statement  FUNC_END  VAR_REF  ';' 
	|  FUNC_START  VAR_NAME_IDENTIFIER  ';'  ret_type  FUNC_END  VAR_REF  ';' 
	|  FUNC_START  VAR_NAME_IDENTIFIER  ','  func_attrib  ';'  ret_type  FUNC_END  VAR_REF  ';' 
	|  FUNC_START  VAR_NAME_IDENTIFIER  ';'  ret_type  function_arg  FUNC_END  VAR_REF  ';' 
	|  FUNC_START  VAR_NAME_IDENTIFIER  ','  func_attrib  ';'  ret_type  function_arg  FUNC_END  VAR_REF  ';' 
	;
func_attrib
	:  func_attrib1 
	|  func_attrib  ','  func_attrib1 
	;
func_attrib1
	:  IDENTIFIER  '('  STRING_LITERAL  ')' 
	|  IDENTIFIER  '('  I_CONSTANT  ')' 
	;
declarations
	:  def_one_var 
	|  declarations  def_one_var 
	;
function_arg
	:  def_arg 
	|  function_arg  def_arg 
	;
ret_type
	:  RET_TYPE  VAR_NAME_IDENTIFIER  ','  type_specifier  ';' 
	;
def_arg
	:  DEF_ARG  VAR_NAME_IDENTIFIER  ','  type_specifier  ';' 
	;
def_one_var
	:  def_var_start  VAR_NAME_IDENTIFIER  ','  type_specifier  ';' 
	;
def_var_start
	:  DEF_VAR 
	|  DEF_VAR_TMP 
	;
type_specifier
	:  type_specifier_basic 
	|  type_specifier_basic  '('  declarations  ')' 
	|  type_specifier_basic  '('  '('  declarations  ')'  ')' 
	|  type_specifier_basic  '*'  I_CONSTANT  '*'  '['  type_specifier  ']' 
	|  type_specifier  '['  type_specifier  ']' 
	|  type_specifier  '['  opr_elem  ']' 
	|  type_specifier  ','  func_attrib 
	;
type_specifier_basic
	:  VOID 
	|  U1 
	|  U8 
	|  U16 
	|  U24 
	|  U32 
	|  U64 
	|  F16 
	|  F32 
	|  F64 
	|  I1 
	|  I8 
	|  I16 
	|  I24 
	|  I32 
	|  I64 
	|  U_NUM 
	;
compound_statement
	:  SCOPES  SCOPEE 
	|  SCOPES  block_item_list  SCOPEE 
	;
block_item_list
	:  block_item 
	|  block_item_list  block_item 
	;
block_item
	:  def_one_var 
	|  statement 
	;
statement
	:  opr_statement 
	|  call_statement 
	|  FUNC_RETURN 
	|  label_def 
	|  inline_asm 
	|  compound_statement 
	;
opr_statement
	:  OPR_START  STRING_LITERAL  ','  opr_elem  ';'  ','  opr_elem  ';'  ','  opr_elem  ';' 
	;
opr_elem
	:  VAR_NULL 
	|  VAR_REF 
	|  constant 
	|  var_in_ref 
	|  label_ref 
	;
constant
	:  i_const 
	|  f_const 
	|  string 
	|  const_list 
	;
i_const
	:  I_CONST_ID  I_CONSTANT 
	;
f_const
	:  F_CONST_ID  F_CONSTANT 
	|  F_CONST_ID  I_CONSTANT 
	;
string
	:  STRING_ID  STRING_LITERAL 
	;
var_in_ref
	:  var_in_ref_ptr 
	|  var_in_ref_array 
	;
var_in_ref_ptr
	:  var_in_start  VAR_REF  '*'  I_CONSTANT 
	;
var_in_ref_array
	:  var_in_start  VAR_REF  '['  opr_elem  ']' 
	|  var_in_ref_array  '['  opr_elem  ']' 
	;
const_list
	:  CONST_LIST_ID  '['  opr_elem_seq  ']' 
	;
var_in_start
	:  VAR_IN 
	|  VAR_IN_TMP 
	;
call_statement
	:  CALL_START  VAR_REF  ';'  opr_elem_seq  CALL_END  VAR_REF  ';' 
	|  CALL_START  VAR_REF  ';'  CALL_END  VAR_REF  ';' 
	;
opr_elem_seq
	:  opr_elem  ';' 
	|  opr_elem_seq  opr_elem  ';' 
	;
label_def
	:  LABEL_START  I_CONSTANT  ';' 
	;
label_ref
	:  LABEL_REF  I_CONSTANT 
	;
inline_asm
	:  INLINE_ASM  STRING_LITERAL  ';' 
	;
%%
