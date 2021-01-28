
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
	:  /*empty*/ 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_FILE_1);
		}
	|  translation_unit 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_FILE_2);
		}
	|  BLOCKS  translation_unit  BLOCKE 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_FILE_3;
		$$.m_tk_type_int_list.push_back(IAN_FILE_3);
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
external_declaration
	:  block_item 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_EXTERNAL_DECLARATION_1);
		}
	|  function_definition 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_EXTERNAL_DECLARATION_2);
		}
	;
function_definition
	:  FUNC_START  VAR_NAME_IDENTIFIER  ';'  ret_type  compound_statement  FUNC_END  VAR_REF  ';' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_FUNCTION_DEFINITION_1;
		$$.m_tk_type_int_list.push_back(IAN_FUNCTION_DEFINITION_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		$$.m_tk_elems.push_back(parser_ntoken($6));
		$$.m_tk_elems.push_back(parser_ntoken($7));
		$$.m_tk_elems.push_back(parser_ntoken($8));
		}
	|  FUNC_START  VAR_NAME_IDENTIFIER  ','  func_attrib  ';'  ret_type  compound_statement  FUNC_END  VAR_REF  ';' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_FUNCTION_DEFINITION_2;
		$$.m_tk_type_int_list.push_back(IAN_FUNCTION_DEFINITION_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		$$.m_tk_elems.push_back(parser_ntoken($6));
		$$.m_tk_elems.push_back(parser_ntoken($7));
		$$.m_tk_elems.push_back(parser_ntoken($8));
		$$.m_tk_elems.push_back(parser_ntoken($9));
		$$.m_tk_elems.push_back(parser_ntoken($10));
		}
	|  FUNC_START  VAR_NAME_IDENTIFIER  ';'  ret_type  function_arg  compound_statement  FUNC_END  VAR_REF  ';' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_FUNCTION_DEFINITION_3;
		$$.m_tk_type_int_list.push_back(IAN_FUNCTION_DEFINITION_3);
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
	|  FUNC_START  VAR_NAME_IDENTIFIER  ','  func_attrib  ';'  ret_type  function_arg  compound_statement  FUNC_END  VAR_REF  ';' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_FUNCTION_DEFINITION_4;
		$$.m_tk_type_int_list.push_back(IAN_FUNCTION_DEFINITION_4);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		$$.m_tk_elems.push_back(parser_ntoken($6));
		$$.m_tk_elems.push_back(parser_ntoken($7));
		$$.m_tk_elems.push_back(parser_ntoken($8));
		$$.m_tk_elems.push_back(parser_ntoken($9));
		$$.m_tk_elems.push_back(parser_ntoken($10));
		$$.m_tk_elems.push_back(parser_ntoken($11));
		}
	|  FUNC_START  VAR_NAME_IDENTIFIER  ';'  ret_type  FUNC_END  VAR_REF  ';' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_FUNCTION_DEFINITION_5;
		$$.m_tk_type_int_list.push_back(IAN_FUNCTION_DEFINITION_5);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		$$.m_tk_elems.push_back(parser_ntoken($6));
		$$.m_tk_elems.push_back(parser_ntoken($7));
		}
	|  FUNC_START  VAR_NAME_IDENTIFIER  ','  func_attrib  ';'  ret_type  FUNC_END  VAR_REF  ';' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_FUNCTION_DEFINITION_6;
		$$.m_tk_type_int_list.push_back(IAN_FUNCTION_DEFINITION_6);
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
	|  FUNC_START  VAR_NAME_IDENTIFIER  ';'  ret_type  function_arg  FUNC_END  VAR_REF  ';' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_FUNCTION_DEFINITION_7;
		$$.m_tk_type_int_list.push_back(IAN_FUNCTION_DEFINITION_7);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		$$.m_tk_elems.push_back(parser_ntoken($6));
		$$.m_tk_elems.push_back(parser_ntoken($7));
		$$.m_tk_elems.push_back(parser_ntoken($8));
		}
	|  FUNC_START  VAR_NAME_IDENTIFIER  ','  func_attrib  ';'  ret_type  function_arg  FUNC_END  VAR_REF  ';' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_FUNCTION_DEFINITION_8;
		$$.m_tk_type_int_list.push_back(IAN_FUNCTION_DEFINITION_8);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		$$.m_tk_elems.push_back(parser_ntoken($6));
		$$.m_tk_elems.push_back(parser_ntoken($7));
		$$.m_tk_elems.push_back(parser_ntoken($8));
		$$.m_tk_elems.push_back(parser_ntoken($9));
		$$.m_tk_elems.push_back(parser_ntoken($10));
		}
	;
func_attrib
	:  func_attrib1 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_FUNC_ATTRIB_1);
		}
	|  func_attrib  ','  func_attrib1 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_FUNC_ATTRIB_2;
		$$.m_tk_type_int_list.push_back(IAN_FUNC_ATTRIB_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
func_attrib1
	:  IDENTIFIER  '('  STRING_LITERAL  ')' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_FUNC_ATTRIB1_1;
		$$.m_tk_type_int_list.push_back(IAN_FUNC_ATTRIB1_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	|  IDENTIFIER  '('  I_CONSTANT  ')' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_FUNC_ATTRIB1_2;
		$$.m_tk_type_int_list.push_back(IAN_FUNC_ATTRIB1_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	;
declarations
	:  def_one_var 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_DECLARATIONS_1);
		}
	|  declarations  def_one_var 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DECLARATIONS_2;
		$$.m_tk_type_int_list.push_back(IAN_DECLARATIONS_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	;
function_arg
	:  def_arg 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_FUNCTION_ARG_1);
		}
	|  function_arg  def_arg 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_FUNCTION_ARG_2;
		$$.m_tk_type_int_list.push_back(IAN_FUNCTION_ARG_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	;
ret_type
	:  RET_TYPE  VAR_NAME_IDENTIFIER  ','  type_specifier  ';' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_RET_TYPE_1;
		$$.m_tk_type_int_list.push_back(IAN_RET_TYPE_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		}
	;
def_arg
	:  DEF_ARG  VAR_NAME_IDENTIFIER  ','  type_specifier  ';' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DEF_ARG_1;
		$$.m_tk_type_int_list.push_back(IAN_DEF_ARG_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		}
	;
def_one_var
	:  def_var_start  VAR_NAME_IDENTIFIER  ','  type_specifier  ';' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_DEF_ONE_VAR_1;
		$$.m_tk_type_int_list.push_back(IAN_DEF_ONE_VAR_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		}
	;
def_var_start
	:  DEF_VAR 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_DEF_VAR_START_1);
		}
	|  DEF_VAR_TMP 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_DEF_VAR_START_2);
		}
	;
type_specifier
	:  type_specifier_basic 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_1);
		}
	|  type_specifier_basic  '('  declarations  ')' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_TYPE_SPECIFIER_2;
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	|  type_specifier_basic  '('  '('  declarations  ')'  ')' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_TYPE_SPECIFIER_3;
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_3);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		$$.m_tk_elems.push_back(parser_ntoken($6));
		}
	|  type_specifier_basic  '*'  I_CONSTANT  '*'  '['  type_specifier  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_TYPE_SPECIFIER_4;
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_4);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		$$.m_tk_elems.push_back(parser_ntoken($6));
		$$.m_tk_elems.push_back(parser_ntoken($7));
		}
	|  type_specifier  '['  type_specifier  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_TYPE_SPECIFIER_5;
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_5);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	|  type_specifier  '['  opr_elem  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_TYPE_SPECIFIER_6;
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_6);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	|  type_specifier  ','  func_attrib 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_TYPE_SPECIFIER_7;
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_7);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
type_specifier_basic
	:  VOID 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_BASIC_1);
		}
	|  U1 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_BASIC_2);
		}
	|  U8 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_BASIC_3);
		}
	|  U16 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_BASIC_4);
		}
	|  U24 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_BASIC_5);
		}
	|  U32 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_BASIC_6);
		}
	|  U64 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_BASIC_7);
		}
	|  F16 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_BASIC_8);
		}
	|  F32 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_BASIC_9);
		}
	|  F64 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_BASIC_10);
		}
	|  I1 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_BASIC_11);
		}
	|  I8 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_BASIC_12);
		}
	|  I16 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_BASIC_13);
		}
	|  I24 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_BASIC_14);
		}
	|  I32 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_BASIC_15);
		}
	|  I64 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_BASIC_16);
		}
	|  U_NUM 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_TYPE_SPECIFIER_BASIC_17);
		}
	;
compound_statement
	:  SCOPES  SCOPEE 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_COMPOUND_STATEMENT_1;
		$$.m_tk_type_int_list.push_back(IAN_COMPOUND_STATEMENT_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  SCOPES  block_item_list  SCOPEE 	{
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
	:  def_one_var 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_BLOCK_ITEM_1);
		}
	|  statement 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_BLOCK_ITEM_2);
		}
	;
statement
	:  opr_statement 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_STATEMENT_1);
		}
	|  call_statement 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_STATEMENT_2);
		}
	|  FUNC_RETURN 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_STATEMENT_3);
		}
	|  label_def 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_STATEMENT_4);
		}
	|  inline_asm 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_STATEMENT_5);
		}
	|  compound_statement 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_STATEMENT_6);
		}
	;
opr_statement
	:  OPR_START  STRING_LITERAL  ','  opr_elem  ';'  ','  opr_elem  ';'  ','  opr_elem  ';' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_OPR_STATEMENT_1;
		$$.m_tk_type_int_list.push_back(IAN_OPR_STATEMENT_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		$$.m_tk_elems.push_back(parser_ntoken($6));
		$$.m_tk_elems.push_back(parser_ntoken($7));
		$$.m_tk_elems.push_back(parser_ntoken($8));
		$$.m_tk_elems.push_back(parser_ntoken($9));
		$$.m_tk_elems.push_back(parser_ntoken($10));
		$$.m_tk_elems.push_back(parser_ntoken($11));
		}
	;
opr_elem
	:  VAR_NULL 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_OPR_ELEM_1);
		}
	|  VAR_REF 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_OPR_ELEM_2);
		}
	|  constant 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_OPR_ELEM_3);
		}
	|  var_in_ref 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_OPR_ELEM_4);
		}
	|  label_ref 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_OPR_ELEM_5);
		}
	;
constant
	:  i_const 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_CONSTANT_1);
		}
	|  f_const 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_CONSTANT_2);
		}
	|  string 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_CONSTANT_3);
		}
	|  const_list 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_CONSTANT_4);
		}
	;
i_const
	:  I_CONST_ID  I_CONSTANT 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_I_CONST_1;
		$$.m_tk_type_int_list.push_back(IAN_I_CONST_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	;
f_const
	:  F_CONST_ID  F_CONSTANT 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_F_CONST_1;
		$$.m_tk_type_int_list.push_back(IAN_F_CONST_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  F_CONST_ID  I_CONSTANT 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_F_CONST_2;
		$$.m_tk_type_int_list.push_back(IAN_F_CONST_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	;
string
	:  STRING_ID  STRING_LITERAL 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_STRING_1;
		$$.m_tk_type_int_list.push_back(IAN_STRING_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	;
var_in_ref
	:  var_in_ref_ptr 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_VAR_IN_REF_1);
		}
	|  var_in_ref_array 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_VAR_IN_REF_2);
		}
	;
var_in_ref_ptr
	:  var_in_start  VAR_REF  '*'  I_CONSTANT 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_VAR_IN_REF_PTR_1;
		$$.m_tk_type_int_list.push_back(IAN_VAR_IN_REF_PTR_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	;
var_in_ref_array
	:  var_in_start  VAR_REF  '['  opr_elem  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_VAR_IN_REF_ARRAY_1;
		$$.m_tk_type_int_list.push_back(IAN_VAR_IN_REF_ARRAY_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		}
	|  var_in_ref_array  '['  opr_elem  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_VAR_IN_REF_ARRAY_2;
		$$.m_tk_type_int_list.push_back(IAN_VAR_IN_REF_ARRAY_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	;
const_list
	:  CONST_LIST_ID  '['  opr_elem_seq  ']' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_CONST_LIST_1;
		$$.m_tk_type_int_list.push_back(IAN_CONST_LIST_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		}
	;
var_in_start
	:  VAR_IN 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_VAR_IN_START_1);
		}
	|  VAR_IN_TMP 	{
		$$=$1; 
		$$.m_tk_type_int_list.push_back(IAN_VAR_IN_START_2);
		}
	;
call_statement
	:  CALL_START  VAR_REF  ';'  opr_elem_seq  CALL_END  VAR_REF  ';' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_CALL_STATEMENT_1;
		$$.m_tk_type_int_list.push_back(IAN_CALL_STATEMENT_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		$$.m_tk_elems.push_back(parser_ntoken($6));
		$$.m_tk_elems.push_back(parser_ntoken($7));
		}
	|  CALL_START  VAR_REF  ';'  CALL_END  VAR_REF  ';' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_CALL_STATEMENT_2;
		$$.m_tk_type_int_list.push_back(IAN_CALL_STATEMENT_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		$$.m_tk_elems.push_back(parser_ntoken($4));
		$$.m_tk_elems.push_back(parser_ntoken($5));
		$$.m_tk_elems.push_back(parser_ntoken($6));
		}
	;
opr_elem_seq
	:  opr_elem  ';' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_OPR_ELEM_SEQ_1;
		$$.m_tk_type_int_list.push_back(IAN_OPR_ELEM_SEQ_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	|  opr_elem_seq  opr_elem  ';' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_OPR_ELEM_SEQ_2;
		$$.m_tk_type_int_list.push_back(IAN_OPR_ELEM_SEQ_2);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
label_def
	:  LABEL_START  IDENTIFIER  ';' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_LABEL_DEF_1;
		$$.m_tk_type_int_list.push_back(IAN_LABEL_DEF_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
label_ref
	:  LABEL_REF  IDENTIFIER 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_LABEL_REF_1;
		$$.m_tk_type_int_list.push_back(IAN_LABEL_REF_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		}
	;
inline_asm
	:  INLINE_ASM  STRING_LITERAL  ';' 	{
		$$=gempty_token();
		$$.m_type=TOKEN_DEFS_TYPE_AST;
		$$.m_tk_type_int = IAN_INLINE_ASM_1;
		$$.m_tk_type_int_list.push_back(IAN_INLINE_ASM_1);
		$$.m_tk_elems.push_back(parser_ntoken($1));
		$$.m_tk_elems.push_back(parser_ntoken($2));
		$$.m_tk_elems.push_back(parser_ntoken($3));
		}
	;
%%
