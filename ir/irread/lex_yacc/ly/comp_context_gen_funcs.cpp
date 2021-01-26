/*
 *
 *
 * 未实现列表：
 * 旧的函数声明： func1(a,b):int a, int b{}--func_IAN_IDENTIFIER_LIST_2
 *
 *
 *
 *
 *
 *
 *
 *
 * */









#include <assert.h>
#include <iostream>
#include "icode.h"
#include "comp_context.h"
#include "token_defs.h"
#include "comp_context_gen_defs.h"
#include "driver.h"

#include "icode_manage.h"
#include "target_base.h"

#include "mylog.h"
#include "str2number.h"
#include "string_eval.h"
#include "number2str.h"
using mylog::cerr;
using mylog::cout;



namespace NS_IR2ICODE{

/// TODO 此处需要添加实际代码，用于ir生成icode
///
class icode *  func_IAN_FILE_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1-file->/*empty*/ 
	//parent:
    icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);

    ///空文件
    return a;
}
class icode *  func_IAN_FILE_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x2-file->translation_unit 
	//parent:
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_FILE_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3-file->BLOCKS translation_unit BLOCKE
    return pcompi->ast_to_icode(tdefs->m_tk_elems[1],need_result_icode, result_ic);

}
class icode *  func_IAN_TRANSLATION_UNIT_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x101-translation_unit->external_declaration 
	//parent:
	// file--> translation_unit
	// file--> BLOCKS translation_unit BLOCKE
	// translation_unit--> translation_unit external_declaration
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TRANSLATION_UNIT_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x102-translation_unit->translation_unit external_declaration 
	//parent:
	// file--> translation_unit
	// file--> BLOCKS translation_unit BLOCKE
	// translation_unit--> translation_unit external_declaration
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
    token_defs *translation_unit=tdefs->m_tk_elems[0];
    token_defs *external_declaration=tdefs->m_tk_elems[1];
    icode *translation_unit_ic=pcompi->ast_to_icode(translation_unit, need_result_icode);
    icode *external_declaration_ic=pcompi->ast_to_icode(external_declaration, need_result_icode);
    a->merge_icode(translation_unit_ic);
    a->merge_icode(external_declaration_ic);
	return a;
}
class icode *  func_IAN_EXTERNAL_DECLARATION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x201-external_declaration->block_item 
	//parent:
	// translation_unit--> external_declaration
	// translation_unit--> translation_unit external_declaration
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}



class icode *  func_IAN_EXTERNAL_DECLARATION_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x202-external_declaration->function_definition 
	//parent:
	// translation_unit--> external_declaration
	// translation_unit--> translation_unit external_declaration
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}

class icode *  func_function_definition_i(class comp_context* pcompi, class token_defs* FUNC_START,token_defs *VAR_NAME_IDENTIFIER,
                                          token_defs *func_attrib,token_defs *ret_type,token_defs *function_arg,token_defs *compound_statement,
                                          bool need_result_icode, class icode* result_ic)
{
    //0x304-function_definition->FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';'
    //parent:
    // external_declaration--> function_definition
    icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
    icode *VAR_NAME_IDENTIFIER_ic=pcompi->ast_to_icode(VAR_NAME_IDENTIFIER);


    ///此处生成1个函数
    icode *func_start_ic = pcompi->ast_to_icode(FUNC_START);
    func_start_ic->name = VAR_NAME_IDENTIFIER->val_str.substr(1);

    if(func_attrib!=NULL)
    {
        //icode *','_ic=pcompi->ast_to_icode(',');
        icode *func_attrib_ic=pcompi->ast_to_icode(func_attrib, 0, func_start_ic);
    }


    if(VAR_NAME_IDENTIFIER_ic!=NULL)
    {
        /// 函数已定义。
        /// 需要判断是否是extern。
        /// 如果之前的是extern，这个也是extern。则返回空block
        /// 如果之前的不是extern，现在的是extern，则返回空block
        /// 如果之前的不是extern，现在的也不是，则错误
        /// 如果之前的是extern，这个是非extern，则将此的函数体放入之前的，将之前的extern去掉，返回空block



        if(VAR_NAME_IDENTIFIER_ic->is_extern && func_start_ic->is_extern)
        {//如果之前的是extern，这个也是extern。则返回空block
            return a;
        }
        if((!VAR_NAME_IDENTIFIER_ic->is_extern) && func_start_ic->is_extern)
        {
            return a;
        }

        if((!VAR_NAME_IDENTIFIER_ic->is_extern) && (!func_start_ic->is_extern))
        {
            //变量已定义，无法重复定义的错误
            cerr<<"func_IAN_FUNCTION_DEFINITION_i: function name already beed defined"<< VAR_NAME_IDENTIFIER->val_str<<"\n";
            return a;
        }


        //if(VAR_NAME_IDENTIFIER_ic->is_extern && (!func_start_ic->is_extern))
        //之前的是extern，这个是非extern，则将此的函数体放入之前的，将之前的extern去掉，返回空block



        pcompi->level_enter();//函数体内部，level++
        for(int i=1;i<VAR_NAME_IDENTIFIER_ic->sub_icode.size();++i)
        {
            pcompi->add_symbol(VAR_NAME_IDENTIFIER_ic->sub_icode[i]->name, VAR_NAME_IDENTIFIER_ic->sub_icode[i]);
        }

        if(compound_statement!=NULL)
        {
            icode *compound_statement_ic=pcompi->ast_to_icode(compound_statement);
            VAR_NAME_IDENTIFIER_ic->merge_icode(compound_statement_ic);
        }
        VAR_NAME_IDENTIFIER_ic->is_extern = 0;

        pcompi->level_leave();//函数体解析结束
        return a;
    }




    pcompi->add_symbol(func_start_ic->name, func_start_ic);

    icode *ret_type_ic=pcompi->ast_to_icode(ret_type);

    func_start_ic->merge_icode(ret_type_ic);

    pcompi->level_enter();//函数体内部，level++

    if(function_arg!=NULL)
    {
        icode *function_arg_ic=pcompi->ast_to_icode(function_arg);
        func_start_ic->merge_icode(function_arg_ic);
    }
    if(compound_statement!=NULL)
    {
        icode *compound_statement_ic=pcompi->ast_to_icode(compound_statement);
        func_start_ic->merge_icode(compound_statement_ic);
    }

    pcompi->level_leave();//函数体解析结束

    a->merge_icode(func_start_ic);

    return a;
}

class icode *  func_IAN_FUNCTION_DEFINITION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
///函数的定义 返回block

    //0x301-function_definition->FUNC_START VAR_NAME_IDENTIFIER ';' ret_type compound_statement FUNC_END VAR_REF ';'
    //parent:
    // external_declaration--> function_definition
    icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
    token_defs *FUNC_START=tdefs->m_tk_elems[0];
    token_defs *VAR_NAME_IDENTIFIER=tdefs->m_tk_elems[1];
    //token_defs *';'=tdefs->m_tk_elems[2];
    token_defs *ret_type=tdefs->m_tk_elems[3];
    token_defs *compound_statement=tdefs->m_tk_elems[4];
    //token_defs *FUNC_END=tdefs->m_tk_elems[5];
    token_defs *VAR_REF=tdefs->m_tk_elems[6];
    //token_defs *';'=tdefs->m_tk_elems[7];


    return func_function_definition_i(pcompi, FUNC_START, VAR_NAME_IDENTIFIER,NULL, ret_type, NULL, compound_statement,need_result_icode,result_ic);


}

class icode *  func_IAN_FUNCTION_DEFINITION_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x302-function_definition->FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type compound_statement FUNC_END VAR_REF ';' 
	//parent:
	// external_declaration--> function_definition
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
    token_defs *FUNC_START=tdefs->m_tk_elems[0];
    token_defs *VAR_NAME_IDENTIFIER=tdefs->m_tk_elems[1];
	//token_defs *','=tdefs->m_tk_elems[2];
    token_defs *func_attrib=tdefs->m_tk_elems[3];
	//token_defs *';'=tdefs->m_tk_elems[4];
    token_defs *ret_type=tdefs->m_tk_elems[5];
    token_defs *compound_statement=tdefs->m_tk_elems[6];

    return func_function_definition_i(pcompi, FUNC_START, VAR_NAME_IDENTIFIER,func_attrib, ret_type, NULL, compound_statement,need_result_icode,result_ic);
}
class icode *  func_IAN_FUNCTION_DEFINITION_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x303-function_definition->FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';' 
	//parent:
	// external_declaration--> function_definition
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
    token_defs *FUNC_START=tdefs->m_tk_elems[0];
    token_defs *VAR_NAME_IDENTIFIER=tdefs->m_tk_elems[1];
    token_defs *ret_type=tdefs->m_tk_elems[3];
    token_defs *function_arg=tdefs->m_tk_elems[4];
    token_defs *compound_statement=tdefs->m_tk_elems[5];


    return func_function_definition_i(pcompi, FUNC_START, VAR_NAME_IDENTIFIER,NULL, ret_type, function_arg, compound_statement,need_result_icode,result_ic);


}

class icode *  func_IAN_FUNCTION_DEFINITION_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x304-function_definition->FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';' 
	//parent:
	// external_declaration--> function_definition
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
    token_defs *FUNC_START=tdefs->m_tk_elems[0];
    token_defs *VAR_NAME_IDENTIFIER=tdefs->m_tk_elems[1];
	//token_defs *','=tdefs->m_tk_elems[2];
    token_defs *func_attrib=tdefs->m_tk_elems[3];
	//token_defs *';'=tdefs->m_tk_elems[4];
    token_defs *ret_type=tdefs->m_tk_elems[5];
    token_defs *function_arg=tdefs->m_tk_elems[6];
    token_defs *compound_statement=tdefs->m_tk_elems[7];
	//token_defs *FUNC_END=tdefs->m_tk_elems[8];
	//token_defs *VAR_REF=tdefs->m_tk_elems[9];
	//token_defs *';'=tdefs->m_tk_elems[a];

    return func_function_definition_i(pcompi, FUNC_START, VAR_NAME_IDENTIFIER,func_attrib, ret_type, function_arg,
                                      compound_statement,need_result_icode,result_ic);

}
class icode *  func_IAN_FUNCTION_DEFINITION_5(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x305-function_definition->FUNC_START VAR_NAME_IDENTIFIER ';' ret_type FUNC_END VAR_REF ';' 
	//parent:
	// external_declaration--> function_definition
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
    token_defs *FUNC_START=tdefs->m_tk_elems[0];
    token_defs *VAR_NAME_IDENTIFIER=tdefs->m_tk_elems[1];
	//token_defs *';'=tdefs->m_tk_elems[2];
    token_defs *ret_type=tdefs->m_tk_elems[3];
	//token_defs *FUNC_END=tdefs->m_tk_elems[4];
	//token_defs *VAR_REF=tdefs->m_tk_elems[5];
	//token_defs *';'=tdefs->m_tk_elems[6];

    return func_function_definition_i(pcompi, FUNC_START, VAR_NAME_IDENTIFIER,NULL, ret_type, NULL, NULL, need_result_icode, result_ic);

}
class icode *  func_IAN_FUNCTION_DEFINITION_6(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x306-function_definition->FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type FUNC_END VAR_REF ';' 
	//parent:
	// external_declaration--> function_definition
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
    token_defs *FUNC_START=tdefs->m_tk_elems[0];
    token_defs *VAR_NAME_IDENTIFIER=tdefs->m_tk_elems[1];
	//token_defs *','=tdefs->m_tk_elems[2];
    token_defs *func_attrib=tdefs->m_tk_elems[3];
	//token_defs *';'=tdefs->m_tk_elems[4];
    token_defs *ret_type=tdefs->m_tk_elems[5];
	//token_defs *FUNC_END=tdefs->m_tk_elems[6];
	//token_defs *VAR_REF=tdefs->m_tk_elems[7];
    //token_defs *';'=tdefs->m_tk_elems[8];
    return func_function_definition_i(pcompi, FUNC_START, VAR_NAME_IDENTIFIER,func_attrib, ret_type, NULL, NULL,need_result_icode,result_ic);
}
class icode *  func_IAN_FUNCTION_DEFINITION_7(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x307-function_definition->FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg FUNC_END VAR_REF ';' 
	//parent:
	// external_declaration--> function_definition
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
    token_defs *FUNC_START=tdefs->m_tk_elems[0];
    token_defs *VAR_NAME_IDENTIFIER=tdefs->m_tk_elems[1];
	//token_defs *';'=tdefs->m_tk_elems[2];
    token_defs *ret_type=tdefs->m_tk_elems[3];
    token_defs *function_arg=tdefs->m_tk_elems[4];
	//token_defs *FUNC_END=tdefs->m_tk_elems[5];
	//token_defs *VAR_REF=tdefs->m_tk_elems[6];
	//token_defs *';'=tdefs->m_tk_elems[7];

    return func_function_definition_i(pcompi, FUNC_START, VAR_NAME_IDENTIFIER,NULL, ret_type, function_arg, NULL, need_result_icode,result_ic);

}
class icode *  func_IAN_FUNCTION_DEFINITION_8(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x308-function_definition->FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg FUNC_END VAR_REF ';' 
	//parent:
	// external_declaration--> function_definition
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
    token_defs *FUNC_START=tdefs->m_tk_elems[0];
    token_defs *VAR_NAME_IDENTIFIER=tdefs->m_tk_elems[1];
	//token_defs *','=tdefs->m_tk_elems[2];
    token_defs *func_attrib=tdefs->m_tk_elems[3];
	//token_defs *';'=tdefs->m_tk_elems[4];
    token_defs *ret_type=tdefs->m_tk_elems[5];
    token_defs *function_arg=tdefs->m_tk_elems[6];
	//token_defs *FUNC_END=tdefs->m_tk_elems[7];
	//token_defs *VAR_REF=tdefs->m_tk_elems[8];
	//token_defs *';'=tdefs->m_tk_elems[9];
    return func_function_definition_i(pcompi, FUNC_START, VAR_NAME_IDENTIFIER,func_attrib, ret_type, function_arg,
                                      NULL,need_result_icode,result_ic);
}

class icode *  func_IAN_FUNC_ATTRIB_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///函数属性值，没有返回值，只有result_ic为func_ic,将属性值直接填入result_ic中
	//0x401-func_attrib->func_attrib1 
	//parent:
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' function_arg compound_statement FUNC_END VAR_REF ';'
	// func_attrib--> func_attrib ',' func_attrib1
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_FUNC_ATTRIB_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///函数属性值，没有返回值，只有result_ic为func_ic,将属性值直接填入result_ic中
	//0x402-func_attrib->func_attrib ',' func_attrib1 
	//parent:
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' function_arg compound_statement FUNC_END VAR_REF ';'
	// func_attrib--> func_attrib ',' func_attrib1


    pcompi->ast_to_icode(tdefs->m_tk_elems[0],need_result_icode, result_ic);
    pcompi->ast_to_icode(tdefs->m_tk_elems[2],need_result_icode, result_ic);
    return NULL;

}
class icode *  func_IAN_FUNC_ATTRIB1_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///函数属性值，没有返回值，只有result_ic为func_ic,将属性值直接填入result_ic中
    ///
	//0x501-func_attrib1->IDENTIFIER '(' STRING_LITERAL ')' 
	//parent:
	// func_attrib--> func_attrib1
	// func_attrib--> func_attrib ',' func_attrib1


    token_defs *IDENTIFIER=tdefs->m_tk_elems[0];
	//token_defs *'('=tdefs->m_tk_elems[1];
    token_defs *STRING_LITERAL=tdefs->m_tk_elems[2];

    ///当前函数属性值，只支持regparams interrupt
    ///
    if(IDENTIFIER->val_str=="REGPARAMS")
    {
        result_ic->is_regparams = 1;
        icode* STRING_LITERAL_ic = pcompi->ast_to_icode(STRING_LITERAL);

        result_ic->m_reg_params_desc = STRING_LITERAL_ic->name;
    }
    else if(IDENTIFIER->val_str=="REGISTER")
    {

        result_ic->is_register = 1;
        icode* STRING_LITERAL_ic = pcompi->ast_to_icode(STRING_LITERAL);

        result_ic->m_register_desc = STRING_LITERAL_ic->name;
    }



	//token_defs *')'=tdefs->m_tk_elems[3];
	//icode *IDENTIFIER_ic=pcompi->ast_to_icode(IDENTIFIER);
	//icode *'('_ic=pcompi->ast_to_icode('(');
	//icode *STRING_LITERAL_ic=pcompi->ast_to_icode(STRING_LITERAL);
	//icode *')'_ic=pcompi->ast_to_icode(')');
	//a->merge_icode(IDENTIFIER_ic);
	//a->merge_icode('('_ic);
	//a->merge_icode(STRING_LITERAL_ic);
	//a->merge_icode(')'_ic);
    return NULL;
}
class icode *  func_IAN_FUNC_ATTRIB1_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///函数属性值，没有返回值，只有result_ic为func_ic,将属性值直接填入result_ic中
    ///
	//0x502-func_attrib1->IDENTIFIER '(' I_CONSTANT ')' 
	//parent:
	// func_attrib--> func_attrib1
	// func_attrib--> func_attrib ',' func_attrib1
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
    token_defs *IDENTIFIER=tdefs->m_tk_elems[0];
	//token_defs *'('=tdefs->m_tk_elems[1];
    token_defs *I_CONSTANT=tdefs->m_tk_elems[2];
    //token_defs *')'=tdefs->m_tk_elems[3];

    ///当前函数属性值，只支持 interrupt extern static
    ///
    //assert(IDENTIFIER->val_str=="INTERRUPT");

    if(IDENTIFIER->val_str=="INTERRUPT")
    {
        result_ic->is_interrupt = 1;

        icode *I_CONSTANT_ic=pcompi->ast_to_icode(I_CONSTANT);
        result_ic->m_interrupt_num = I_CONSTANT_ic->num;
    }
    else if(IDENTIFIER->val_str=="TYPEDEF")
    {
        result_ic->is_typedef = 1;
    }
    else if(IDENTIFIER->val_str=="EXTERN")
    {
        result_ic->is_extern = 1;
    }
    else if(IDENTIFIER->val_str=="STATIC")
    {
        result_ic->is_static = 1;
    }
    else if(IDENTIFIER->val_str=="SFR")
    {
        result_ic->is_sfr = 1;
    }
    else if(IDENTIFIER->val_str=="SFR16")
    {
        result_ic->is_sfr16 = 1;
    }
    else if(IDENTIFIER->val_str=="SFR32")
    {
        result_ic->is_sfr32 = 1;
    }
    else if(IDENTIFIER->val_str=="IDATA")
    {
        result_ic->is_idata = 1;
    }
    else if(IDENTIFIER->val_str=="XDATA")
    {
        result_ic->is_xdata = 1;
    }
    else if(IDENTIFIER->val_str=="NAKED")
    {
        result_ic->is_naked = 1;
    }
    else if(IDENTIFIER->val_str=="SBIT")
    {
        result_ic->is_sbit = 1;
    }
    else if(IDENTIFIER->val_str=="CODE")
    {
        result_ic->is_code = 1;
    }
    else if(IDENTIFIER->val_str=="CONST")
    {
        result_ic->is_const = 1;
    }
    else
    {
        assert(0);
    }


	//icode *IDENTIFIER_ic=pcompi->ast_to_icode(IDENTIFIER);
	//icode *'('_ic=pcompi->ast_to_icode('(');

	//icode *')'_ic=pcompi->ast_to_icode(')');
	//a->merge_icode(IDENTIFIER_ic);
	//a->merge_icode('('_ic);
	//a->merge_icode(I_CONSTANT_ic);
	//a->merge_icode(')'_ic);
    return NULL;
}


class icode *  func_IAN_DECLARATIONS_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 变量定义：返回为block
	//0x601-declarations->def_one_var 
	//parent:
	// declarations--> declarations def_one_var
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_DECLARATIONS_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 变量定义：返回为block
    ///
	//0x602-declarations->declarations def_one_var 
	//parent:
	// declarations--> declarations def_one_var
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
    token_defs *declarations=tdefs->m_tk_elems[0];
    token_defs *def_one_var=tdefs->m_tk_elems[1];
    icode *declarations_ic=pcompi->ast_to_icode(declarations);
    icode *def_one_var_ic=pcompi->ast_to_icode(def_one_var);
    a->merge_icode(declarations_ic);
    a->merge_icode(def_one_var_ic);
	return a;
}
class icode *  func_IAN_FUNCTION_ARG_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 函数返回值解析：返回为block
	//0x701-function_arg->def_arg 
	//parent:
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';'
	// function_arg--> function_arg def_arg
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);

}

class icode *  func_IAN_FUNCTION_ARG_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 函数返回值解析：返回为block

	//0x702-function_arg->function_arg def_arg 
	//parent:
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';'
	// function_arg--> function_arg def_arg

	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
    token_defs *function_arg=tdefs->m_tk_elems[0];
    token_defs *def_arg=tdefs->m_tk_elems[1];
    icode *function_arg_ic=pcompi->ast_to_icode(function_arg);
    icode *def_arg_ic=pcompi->ast_to_icode(def_arg);
    a->merge_icode(function_arg_ic);
    a->merge_icode(def_arg_ic);

	return a;
}

/**
 * @brief definition_one_var
 * 此函数用于定义一个变量
 * 返回变量的icode
 * 可用于 函数参数，返回值， 和普通变量定义
 *
 * @return
 */
icode* definition_one_var(comp_context* pcompi, token_defs* var_type, token_defs* VAR_NAME_IDENTIFIER,
                          token_defs * type_specifier, token_defs* attrib, bool need_result_icode, class icode* result_ic)
{


    icode *var_ret_ic=pcompi->ast_to_icode(var_type);
    icode *VAR_NAME_IDENTIFIER_ic=pcompi->ast_to_icode(VAR_NAME_IDENTIFIER);

    if(VAR_NAME_IDENTIFIER_ic!=NULL)
    {
        icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
        cerr<<"ret type name already used."<< VAR_NAME_IDENTIFIER->val_str<<"\n";
        return a;
    }
    var_ret_ic->name = VAR_NAME_IDENTIFIER->val_str.substr(1);

    icode *type_specifier_ic=pcompi->ast_to_icode(type_specifier, 0, var_ret_ic);
    if(attrib)
    {
        icode *var_attrib_ic=pcompi->ast_to_icode(attrib, 0, var_ret_ic);
    }

    pcompi->add_symbol(var_ret_ic->name, var_ret_ic);

    return var_ret_ic;
}


class icode *  func_IAN_RET_TYPE_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 函数返回值解析：返回为block

	//0x801-ret_type->RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ';' 
	//parent:
	// function_arg--> ret_type
	// function_arg--> function_arg ret_type
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);

    token_defs *RET_TYPE=tdefs->m_tk_elems[0];
    token_defs *VAR_NAME_IDENTIFIER=tdefs->m_tk_elems[1];
	//token_defs *','=tdefs->m_tk_elems[2];
    token_defs *type_specifier=tdefs->m_tk_elems[3];
	//token_defs *';'=tdefs->m_tk_elems[4];

    return definition_one_var(pcompi, RET_TYPE,VAR_NAME_IDENTIFIER, type_specifier,NULL,
                              need_result_icode, result_ic);


}

class icode *  func_IAN_RET_TYPE_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x802-ret_type->RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';' 
	//parent:
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' ret_type function_arg FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' ret_type function_arg FUNC_END VAR_REF ';'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
    token_defs *RET_TYPE=tdefs->m_tk_elems[0];
    token_defs *VAR_NAME_IDENTIFIER=tdefs->m_tk_elems[1];
	//token_defs *','=tdefs->m_tk_elems[2];
    token_defs *type_specifier=tdefs->m_tk_elems[3];
	//token_defs *','=tdefs->m_tk_elems[4];
    token_defs *func_attrib=tdefs->m_tk_elems[5];
	//token_defs *';'=tdefs->m_tk_elems[6];

    return definition_one_var(pcompi, RET_TYPE,VAR_NAME_IDENTIFIER, type_specifier,func_attrib,
                              need_result_icode, result_ic);
}

class icode *  func_IAN_DEF_ARG_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 函数参数解析：返回为block

	//0x901-def_arg->DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ';' 
	//parent:
	// function_arg--> def_arg
	// function_arg--> function_arg def_arg
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
    token_defs *DEF_ARG=tdefs->m_tk_elems[0];
    token_defs *VAR_NAME_IDENTIFIER=tdefs->m_tk_elems[1];
	//token_defs *','=tdefs->m_tk_elems[2];
    token_defs *type_specifier=tdefs->m_tk_elems[3];
	//token_defs *';'=tdefs->m_tk_elems[4];
    //icode *DEF_ARG_ic=pcompi->ast_to_icode(DEF_ARG);

    return definition_one_var(pcompi, DEF_ARG,VAR_NAME_IDENTIFIER, type_specifier,NULL,
                              need_result_icode, result_ic);

}

class icode *  func_IAN_DEF_ARG_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x902-def_arg->DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';' 
	//parent:
	// function_arg--> def_arg
	// function_arg--> function_arg def_arg
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
    token_defs *DEF_ARG=tdefs->m_tk_elems[0];
    token_defs *VAR_NAME_IDENTIFIER=tdefs->m_tk_elems[1];
	//token_defs *','=tdefs->m_tk_elems[2];
    token_defs *type_specifier=tdefs->m_tk_elems[3];
	//token_defs *','=tdefs->m_tk_elems[4];
    token_defs *func_attrib=tdefs->m_tk_elems[5];
	//token_defs *';'=tdefs->m_tk_elems[6];


    return definition_one_var(pcompi, DEF_ARG,VAR_NAME_IDENTIFIER, type_specifier,func_attrib,
                              need_result_icode, result_ic);

    //icode *DEF_ARG_ic=pcompi->ast_to_icode(DEF_ARG);
	//icode *VAR_NAME_IDENTIFIER_ic=pcompi->ast_to_icode(VAR_NAME_IDENTIFIER);
	//icode *','_ic=pcompi->ast_to_icode(',');
	//icode *type_specifier_ic=pcompi->ast_to_icode(type_specifier);
	//icode *','_ic=pcompi->ast_to_icode(',');
	//icode *func_attrib_ic=pcompi->ast_to_icode(func_attrib);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//a->merge_icode(DEF_ARG_ic);
	//a->merge_icode(VAR_NAME_IDENTIFIER_ic);
	//a->merge_icode(','_ic);
	//a->merge_icode(type_specifier_ic);
	//a->merge_icode(','_ic);
	//a->merge_icode(func_attrib_ic);
	//a->merge_icode(';'_ic);
	assert(0);
	return a;
}



class icode *  func_IAN_DEF_ONE_VAR_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 变量定义解析：返回为block

	//0xa01-def_one_var->def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ';' 
	//parent:
	// declarations--> def_one_var
	// declarations--> declarations def_one_var
	// block_item--> def_one_var
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
    token_defs *def_var_start=tdefs->m_tk_elems[0];
    token_defs *VAR_NAME_IDENTIFIER=tdefs->m_tk_elems[1];
	//token_defs *','=tdefs->m_tk_elems[2];
    token_defs *type_specifier=tdefs->m_tk_elems[3];
	//token_defs *';'=tdefs->m_tk_elems[4];


    return definition_one_var(pcompi, def_var_start,VAR_NAME_IDENTIFIER, type_specifier,NULL,
                              need_result_icode, result_ic);

}

class icode *  func_IAN_DEF_ONE_VAR_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xa02-def_one_var->def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';' 
	//parent:
	// declarations--> def_one_var
	// declarations--> declarations def_one_var
	// block_item--> def_one_var
    token_defs *def_var_start=tdefs->m_tk_elems[0];
    token_defs *VAR_NAME_IDENTIFIER=tdefs->m_tk_elems[1];
	//token_defs *','=tdefs->m_tk_elems[2];
    token_defs *type_specifier=tdefs->m_tk_elems[3];
	//token_defs *','=tdefs->m_tk_elems[4];
    token_defs *func_attrib=tdefs->m_tk_elems[5];
	//token_defs *';'=tdefs->m_tk_elems[6];


    return definition_one_var(pcompi, def_var_start,VAR_NAME_IDENTIFIER, type_specifier,func_attrib,
                              need_result_icode, result_ic);


}

class icode *  func_IAN_DEF_VAR_START_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 此处直接生成一个空变量并返回
	//0xb01-def_var_start->DEF_VAR 
	//parent:
	// def_one_var--> def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ';'
    return pcompi->new_icode(ICODE_TYPE_DEF_VAR);
}
class icode *  func_IAN_DEF_VAR_START_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 此处直接生成一个空变量并返回
	//0xb02-def_var_start->DEF_VAR_TMP 
	//parent:
	// def_one_var--> def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ';'
    return pcompi->new_icode(ICODE_TYPE_DEF_VAR_TMP);
}
class icode *  func_IAN_TYPE_SPECIFIER_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///变量/函数类型属性值，没有返回值，只有result_ic为func_ic,将属性值直接填入result_ic中

	//0xc01-type_specifier->type_specifier_basic 
	//parent:
	// ret_type--> RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_arg--> DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_one_var--> def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
	// type_specifier--> type_specifier '[' opr_elem ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///变量/函数类型属性值，没有返回值，只有result_ic为func_ic,将属性值直接填入result_ic中
    /// 小括号为struct类型，2个小括号为union类型
    ///
	//0xc02-type_specifier->type_specifier_basic '(' declarations ')' 
	//parent:
	// ret_type--> RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_arg--> DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_one_var--> def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
	// type_specifier--> type_specifier '[' opr_elem ']'

    token_defs *type_specifier_basic=tdefs->m_tk_elems[0];
	//token_defs *'('=tdefs->m_tk_elems[1];
    token_defs *declarations=tdefs->m_tk_elems[2];
	//token_defs *')'=tdefs->m_tk_elems[3];
    icode *type_specifier_basic_ic=pcompi->ast_to_icode(type_specifier_basic, need_result_icode, result_ic);

    result_ic->is_struct = 1;
    result_ic->is_signed = 0;

    pcompi->level_enter();//解析结构体内部变量，

	//icode *'('_ic=pcompi->ast_to_icode('(');
    icode *declarations_ic=pcompi->ast_to_icode(declarations);
	//icode *')'_ic=pcompi->ast_to_icode(')');

    pcompi->level_leave();

    for(int i=0;i<declarations_ic->sub_icode.size();++i)
    {
        result_ic->m_struct_type.push_back(declarations_ic->sub_icode[i]);
        /// TODO: 结构体内部变量名： a.b a.c 因为没有a变量名字，所以m_full_name此时无法填写，需要后面某处添加
    }

    //a->merge_icode(type_specifier_basic_ic);
	//a->merge_icode('('_ic);
	//a->merge_icode(declarations_ic);
	//a->merge_icode(')'_ic);
    return NULL;
}
class icode *  func_IAN_TYPE_SPECIFIER_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///变量/函数类型属性值，没有返回值，将属性值直接填入result_ic中

	//0xc03-type_specifier->type_specifier_basic '(' '(' declarations ')' ')' 
	//parent:
	// ret_type--> RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_arg--> DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_one_var--> def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
	// type_specifier--> type_specifier '[' opr_elem ']'
    token_defs *type_specifier_basic=tdefs->m_tk_elems[0];
	//token_defs *'('=tdefs->m_tk_elems[1];
	//token_defs *'('=tdefs->m_tk_elems[2];
    token_defs *declarations=tdefs->m_tk_elems[3];
	//token_defs *')'=tdefs->m_tk_elems[4];
	//token_defs *')'=tdefs->m_tk_elems[5];
    icode *type_specifier_basic_ic=pcompi->ast_to_icode(type_specifier_basic, need_result_icode, result_ic);

    result_ic->is_union = 1;
    result_ic->is_signed = 0;

    pcompi->level_enter();//解析结构体内部变量，

	//icode *'('_ic=pcompi->ast_to_icode('(');
	//icode *'('_ic=pcompi->ast_to_icode('(');
    icode *declarations_ic=pcompi->ast_to_icode(declarations);
	//icode *')'_ic=pcompi->ast_to_icode(')');
	//icode *')'_ic=pcompi->ast_to_icode(')');
	//a->merge_icode(type_specifier_basic_ic);
	//a->merge_icode('('_ic);
	//a->merge_icode('('_ic);
	//a->merge_icode(declarations_ic);
	//a->merge_icode(')'_ic);
	//a->merge_icode(')'_ic);

    pcompi->level_leave();

    for(int i=0;i<declarations_ic->sub_icode.size();++i)
    {
        result_ic->m_struct_type.push_back(declarations_ic->sub_icode[i]);
    }

    return NULL;
}
class icode *  func_IAN_TYPE_SPECIFIER_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///变量/函数类型属性值，没有返回值，将属性值直接填入result_ic中

	//0xc04-type_specifier->type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']' 
	//parent:
	// ret_type--> RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_arg--> DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_one_var--> def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
	// type_specifier--> type_specifier '[' opr_elem ']'
    token_defs *type_specifier_basic=tdefs->m_tk_elems[0];
	//token_defs *'*'=tdefs->m_tk_elems[1];
    token_defs *I_CONSTANT=tdefs->m_tk_elems[2];
	//token_defs *'*'=tdefs->m_tk_elems[3];
	//token_defs *'['=tdefs->m_tk_elems[4];
    token_defs *type_specifier=tdefs->m_tk_elems[5];
	//token_defs *']'=tdefs->m_tk_elems[6];


    icode *type_specifier_basic_ic=pcompi->ast_to_icode(type_specifier_basic, need_result_icode, result_ic);



	//icode *'*'_ic=pcompi->ast_to_icode('*');
    icode *I_CONSTANT_ic=pcompi->ast_to_icode(I_CONSTANT);

    result_ic->is_ptr= I_CONSTANT_ic->num;

    result_ic->m_in_ptr_type = pcompi->new_icode(ICODE_TYPE_DEF_VAR_TMP);
    //icode *'*'_ic=pcompi->ast_to_icode('*');
	//icode *'['_ic=pcompi->ast_to_icode('[');
    icode *type_specifier_ic=pcompi->ast_to_icode(type_specifier, 0, result_ic->m_in_ptr_type);

	//icode *']'_ic=pcompi->ast_to_icode(']');
	//a->merge_icode(type_specifier_basic_ic);
	//a->merge_icode('*'_ic);
	//a->merge_icode(I_CONSTANT_ic);
	//a->merge_icode('*'_ic);
	//a->merge_icode('['_ic);
	//a->merge_icode(type_specifier_ic);
	//a->merge_icode(']'_ic);
    return NULL;
}
class icode *  func_IAN_TYPE_SPECIFIER_5(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///变量/函数类型属性值，没有返回值，将属性值直接填入result_ic中

	//0xc05-type_specifier->type_specifier '[' type_specifier ']' 
	//parent:
	// ret_type--> RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// ret_type--> RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
	// def_arg--> DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_arg--> DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
	// def_one_var--> def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_one_var--> def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ',' func_attrib ';'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
	// type_specifier--> type_specifier '[' type_specifier ']'
	// type_specifier--> type_specifier '[' opr_elem ']'
    token_defs *type_specifier=tdefs->m_tk_elems[0];
	//token_defs *'['=tdefs->m_tk_elems[1];
    token_defs *type_specifier_in=tdefs->m_tk_elems[2];
	//token_defs *']'=tdefs->m_tk_elems[3];
    icode *type_specifier_ic=pcompi->ast_to_icode(type_specifier,need_result_icode, result_ic);
	//icode *'['_ic=pcompi->ast_to_icode('[');
    result_ic->m_in_ptr_type = pcompi->new_icode(ICODE_TYPE_DEF_VAR);
    icode *type_specifier_in_ic=pcompi->ast_to_icode(type_specifier_in, 0, result_ic->m_in_ptr_type);
	//icode *']'_ic=pcompi->ast_to_icode(']');
	//a->merge_icode(type_specifier_ic);
	//a->merge_icode('['_ic);
	//a->merge_icode(type_specifier_ic);
	//a->merge_icode(']'_ic);
    //assert(0);

    //此处是数组，但是数组层数此处清0，每调用一次func_IAN_TYPE_SPECIFIER_6 会加1
    result_ic->is_array=0;


    return NULL;
}

class icode *  func_IAN_TYPE_SPECIFIER_6(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///变量/函数类型属性值，没有返回值，将属性值直接填入result_ic中

	//0xc06-type_specifier->type_specifier '[' opr_elem ']' 
	//parent:
	// ret_type--> RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_arg--> DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_one_var--> def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
	// type_specifier--> type_specifier '[' opr_elem ']'

    token_defs *type_specifier=tdefs->m_tk_elems[0];
	//token_defs *'['=tdefs->m_tk_elems[1];
    token_defs *opr_elem=tdefs->m_tk_elems[2];
	//token_defs *']'=tdefs->m_tk_elems[3];
    icode *type_specifier_ic=pcompi->ast_to_icode(type_specifier, need_result_icode, result_ic);


    result_ic->is_array++;


	//icode *'['_ic=pcompi->ast_to_icode('[');
    icode *opr_elem_ic=pcompi->ast_to_icode(opr_elem);

    result_ic->array_cnt.push_back(opr_elem_ic);


	//icode *']'_ic=pcompi->ast_to_icode(']');
	//a->merge_icode(type_specifier_ic);
	//a->merge_icode('['_ic);
	//a->merge_icode(opr_elem_ic);
	//a->merge_icode(']'_ic);
    return NULL;
}
class icode *  func_IAN_TYPE_SPECIFIER_7(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	///变量/函数类型属性值，没有返回值，将属性值直接填入result_ic中
	//0xc07-type_specifier->type_specifier ',' func_attrib 
	//parent:
	// ret_type--> RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_arg--> DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_one_var--> def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
	// type_specifier--> type_specifier '[' type_specifier ']'
	// type_specifier--> type_specifier '[' opr_elem ']'
	// type_specifier--> type_specifier func_attrib

	token_defs *type_specifier=tdefs->m_tk_elems[0];
	//token_defs *','=tdefs->m_tk_elems[1];
	token_defs *func_attrib=tdefs->m_tk_elems[2];
	icode *type_specifier_ic=pcompi->ast_to_icode(type_specifier, need_result_icode, result_ic);
	//icode *','_ic=pcompi->ast_to_icode(',');
	icode *func_attrib_ic=pcompi->ast_to_icode(func_attrib, need_result_icode, result_ic);
	//a->merge_icode(type_specifier_ic);
	//a->merge_icode(','_ic);
	//a->merge_icode(func_attrib_ic);
    return NULL;
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///变量/函数类型属性值，没有返回值，将属性值直接填入result_ic中

	//0xd01-type_specifier_basic->VOID 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'



    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///变量/函数类型属性值，没有返回值，将属性值直接填入result_ic中

	//0xd02-type_specifier_basic->U1 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///变量/函数类型属性值，没有返回值，将属性值直接填入result_ic中

	//0xd03-type_specifier_basic->U8 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///变量/函数类型属性值，没有返回值，将属性值直接填入result_ic中

	//0xd04-type_specifier_basic->U16 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_5(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///变量/函数类型属性值，没有返回值，将属性值直接填入result_ic中

	//0xd05-type_specifier_basic->U24 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_6(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///变量/函数类型属性值，没有返回值，将属性值直接填入result_ic中

	//0xd06-type_specifier_basic->U32 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_7(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///变量/函数类型属性值，没有返回值，将属性值直接填入result_ic中

	//0xd07-type_specifier_basic->U64 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_8(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///变量/函数类型属性值，没有返回值，将属性值直接填入result_ic中

	//0xd08-type_specifier_basic->F16 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_9(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///变量/函数类型属性值，没有返回值，将属性值直接填入result_ic中

	//0xd09-type_specifier_basic->F32 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_10(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///变量/函数类型属性值，没有返回值，将属性值直接填入result_ic中

	//0xd0a-type_specifier_basic->F64 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_11(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///变量/函数类型属性值，没有返回值，将属性值直接填入result_ic中

	//0xd0b-type_specifier_basic->I1 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_12(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///变量/函数类型属性值，没有返回值，将属性值直接填入result_ic中

	//0xd0c-type_specifier_basic->I8 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_13(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///变量/函数类型属性值，没有返回值，将属性值直接填入result_ic中

	//0xd0d-type_specifier_basic->I16 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_14(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///变量/函数类型属性值，没有返回值，将属性值直接填入result_ic中

	//0xd0e-type_specifier_basic->I24 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_15(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///变量/函数类型属性值，没有返回值，将属性值直接填入result_ic中

	//0xd0f-type_specifier_basic->I32 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_16(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///变量/函数类型属性值，没有返回值，将属性值直接填入result_ic中

	//0xd10-type_specifier_basic->I64 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_TYPE_SPECIFIER_BASIC_17(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0xd11-type_specifier_basic->U_NUM 
	//parent:
	// type_specifier--> type_specifier_basic
	// type_specifier--> type_specifier_basic '(' declarations ')'
	// type_specifier--> type_specifier_basic '(' '(' declarations ')' ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_COMPOUND_STATEMENT_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///复合语句，返回block
	//0xe01-compound_statement->SCOPES SCOPEE 
	//parent:
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' function_arg compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' function_arg compound_statement FUNC_END VAR_REF ';'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *SCOPES=tdefs->m_tk_elems[0];
	//token_defs *SCOPEE=tdefs->m_tk_elems[1];
	//icode *SCOPES_ic=pcompi->ast_to_icode(SCOPES);
	//icode *SCOPEE_ic=pcompi->ast_to_icode(SCOPEE);
	//a->merge_icode(SCOPES_ic);
	//a->merge_icode(SCOPEE_ic);

    icode *ss = pcompi->new_icode(ICODE_TYPE_SCOPE);
    a->merge_icode(ss);

	return a;
}
class icode *  func_IAN_COMPOUND_STATEMENT_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///复合语句，返回block
	//0xe02-compound_statement->SCOPES block_item_list SCOPEE 
	//parent:
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' function_arg compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' function_arg compound_statement FUNC_END VAR_REF ';'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);

    icode *ss = pcompi->new_icode(ICODE_TYPE_SCOPE);

    pcompi->level_enter();//复合语句内，level++

    //token_defs *SCOPES=tdefs->m_tk_elems[0];
    token_defs *block_item_list=tdefs->m_tk_elems[1];
	//token_defs *SCOPEE=tdefs->m_tk_elems[2];
	//icode *SCOPES_ic=pcompi->ast_to_icode(SCOPES);
    icode *block_item_list_ic=pcompi->ast_to_icode(block_item_list);

    pcompi->level_leave();//复合语句结束

    ss->merge_icode(block_item_list_ic);


    a->merge_icode(ss);

	return a;
}
class icode *  func_IAN_BLOCK_ITEM_LIST_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///复合语句，返回block

	//0xf01-block_item_list->block_item 
	//parent:
	// compound_statement--> SCOPES block_item_list SCOPEE
	// block_item_list--> block_item_list block_item
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_BLOCK_ITEM_LIST_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///复合语句，返回block

	//0xf02-block_item_list->block_item_list block_item 
	//parent:
	// compound_statement--> SCOPES block_item_list SCOPEE
	// block_item_list--> block_item_list block_item
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
    token_defs *block_item_list=tdefs->m_tk_elems[0];
    token_defs *block_item=tdefs->m_tk_elems[1];
    icode *block_item_list_ic=pcompi->ast_to_icode(block_item_list);
    icode *block_item_ic=pcompi->ast_to_icode(block_item);
    a->merge_icode(block_item_list_ic);
    a->merge_icode(block_item_ic);
	return a;
}
class icode *  func_IAN_BLOCK_ITEM_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///复合语句，返回block

	//0x1001-block_item->def_one_var 
	//parent:
	// external_declaration--> block_item
	// block_item_list--> block_item
	// block_item_list--> block_item_list block_item
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_BLOCK_ITEM_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///复合语句，返回block

	//0x1002-block_item->statement 
	//parent:
	// external_declaration--> block_item
	// block_item_list--> block_item
	// block_item_list--> block_item_list block_item
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_STATEMENT_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///状态语句，返回block

	//0x1101-statement->opr_statement 
	//parent:
	// block_item--> statement
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_STATEMENT_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///状态语句，返回block

	//0x1102-statement->call_statement 
	//parent:
	// block_item--> statement
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_STATEMENT_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///状态语句，返回block

    //0x1103-statement->FUNC_RETURN
	//parent:
	// block_item--> statement
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_STATEMENT_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///状态语句，返回block

	//0x1104-statement->label_def 
	//parent:
	// block_item--> statement
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_STATEMENT_5(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1205-statement->inline_asm 
	//parent:
	// block_item--> statement
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_STATEMENT_6(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1106-statement->compound_statement 
	//parent:
	// block_item--> statement
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_OPR_STATEMENT_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///状态语句，返回block
    /// opr语句，绝大部分的逻辑语句都在此处实现

    //0x1201-opr_statement->OPR_START STRING_LITERAL ',' opr_elem ';' ',' opr_elem ';' ',' opr_elem ';'
	//parent:
	// statement--> opr_statement
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	//token_defs *OPR_START=tdefs->m_tk_elems[0];
    token_defs *STRING_LITERAL=tdefs->m_tk_elems[1];
	//token_defs *','=tdefs->m_tk_elems[2];
    token_defs *opr_elem1=tdefs->m_tk_elems[3];
	//token_defs *';'=tdefs->m_tk_elems[4];
	//token_defs *','=tdefs->m_tk_elems[5];
    token_defs *opr_elem2=tdefs->m_tk_elems[6];
	//token_defs *';'=tdefs->m_tk_elems[7];
	//token_defs *','=tdefs->m_tk_elems[8];
    token_defs *opr_elem3=tdefs->m_tk_elems[9];
	//token_defs *';'=tdefs->m_tk_elems[a];


    icode * opr_ic = pcompi->new_icode(ICODE_TYPE_EXP_OP);

    icode * STRING_LITERAL_ic = pcompi->ast_to_icode(STRING_LITERAL);
    opr_ic->name = STRING_LITERAL_ic->name;

    //icode *STRING_LITERAL_ic=pcompi->ast_to_icode(STRING_LITERAL);
	//icode *','_ic=pcompi->ast_to_icode(',');
    icode *opr_elem1_ic=pcompi->ast_to_icode(opr_elem1);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//icode *','_ic=pcompi->ast_to_icode(',');
    icode *opr_elem2_ic=pcompi->ast_to_icode(opr_elem2);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//icode *','_ic=pcompi->ast_to_icode(',');
    icode *opr_elem3_ic=pcompi->ast_to_icode(opr_elem3);

    opr_ic->left = opr_elem1_ic;
    opr_ic->right = opr_elem2_ic;
    opr_ic->result = opr_elem3_ic;

    a->merge_icode(opr_ic);


	return a;
}
class icode *  func_IAN_OPR_ELEM_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 直接返回元素对应的icode
    ///
	//0x1301-opr_elem->VAR_NULL 
	//parent:
	// type_specifier--> type_specifier '[' opr_elem ']'
	// opr_statement--> OPR_START STRING_LITERAL ',' opr_elem ';' ',' opr_elem ';' ',' opr_elem ';'
	// var_in_ref--> var_in_start VAR_REF '[' opr_elem ']'
	// opr_elem_seq--> opr_elem ';'
	// opr_elem_seq--> opr_elem_seq opr_elem ';'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_OPR_ELEM_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 直接返回元素对应的icode
    ///
	//0x1302-opr_elem->VAR_REF 
	//parent:
	// type_specifier--> type_specifier '[' opr_elem ']'
	// opr_statement--> OPR_START STRING_LITERAL ',' opr_elem ';' ',' opr_elem ';' ',' opr_elem ';'
	// var_in_ref--> var_in_start VAR_REF '[' opr_elem ']'
	// opr_elem_seq--> opr_elem ';'
	// opr_elem_seq--> opr_elem_seq opr_elem ';'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_OPR_ELEM_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 直接返回元素对应的icode
    ///
	//0x1303-opr_elem->constant 
	//parent:
	// type_specifier--> type_specifier '[' opr_elem ']'
	// opr_statement--> OPR_START STRING_LITERAL ',' opr_elem ';' ',' opr_elem ';' ',' opr_elem ';'
	// var_in_ref--> var_in_start VAR_REF '[' opr_elem ']'
	// opr_elem_seq--> opr_elem ';'
	// opr_elem_seq--> opr_elem_seq opr_elem ';'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_OPR_ELEM_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 直接返回元素对应的icode
    ///
	//0x1304-opr_elem->var_in_ref 
	//parent:
	// type_specifier--> type_specifier '[' opr_elem ']'
	// opr_statement--> OPR_START STRING_LITERAL ',' opr_elem ';' ',' opr_elem ';' ',' opr_elem ';'
	// var_in_ref--> var_in_start VAR_REF '[' opr_elem ']'
	// opr_elem_seq--> opr_elem ';'
	// opr_elem_seq--> opr_elem_seq opr_elem ';'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_OPR_ELEM_5(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 直接返回元素对应的icode
    ///
	//0x1305-opr_elem->label_ref 
	//parent:
	// type_specifier--> type_specifier '[' opr_elem ']'
	// opr_statement--> OPR_START STRING_LITERAL ',' opr_elem ';' ',' opr_elem ';' ',' opr_elem ';'
	// var_in_ref--> var_in_start VAR_REF '[' opr_elem ']'
	// opr_elem_seq--> opr_elem ';'
	// opr_elem_seq--> opr_elem_seq opr_elem ';'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_CONSTANT_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 直接返回元素对应的icode
    ///
	//0x1401-constant->i_const 
	//parent:
	// opr_elem--> constant
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_CONSTANT_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 直接返回元素对应的icode
    ///
	//0x1402-constant->f_const 
	//parent:
	// opr_elem--> constant
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_CONSTANT_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 直接返回元素对应的icode
    ///
	//0x1403-constant->string 
	//parent:
	// opr_elem--> constant
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_CONSTANT_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 直接返回元素对应的icode
    ///
	//0x1404-constant->const_list 
	//parent:
	// opr_elem--> constant
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_I_CONST_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 直接返回元素对应的icode
    ///
	//0x1501-i_const->I_CONST_ID I_CONSTANT 
	//parent:
	// constant--> i_const

	//token_defs *I_CONST_ID=tdefs->m_tk_elems[0];
    token_defs *I_CONSTANT=tdefs->m_tk_elems[1];

    icode *I_CONSTANT_ic=pcompi->ast_to_icode(I_CONSTANT);


	//icode *I_CONST_ID_ic=pcompi->ast_to_icode(I_CONST_ID);

	//a->merge_icode(I_CONST_ID_ic);
	//a->merge_icode(I_CONSTANT_ic);
    return I_CONSTANT_ic;
}
class icode *  func_IAN_F_CONST_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 直接返回元素对应的icode
    ///
    ///
	//0x1601-f_const->F_CONST_ID F_CONSTANT 
	//parent:
	// constant--> f_const
    token_defs *F_CONSTANT=tdefs->m_tk_elems[1];
    icode *F_CONSTANT_ic=pcompi->ast_to_icode(F_CONSTANT);
    F_CONSTANT_ic->const_refresh_width();

    return F_CONSTANT_ic;
}
class icode *  func_IAN_F_CONST_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1602-f_const->F_CONST_ID I_CONSTANT 
	//parent:
	// constant--> f_const
    token_defs *F_CONST_ID=tdefs->m_tk_elems[0];
    token_defs *I_CONSTANT=tdefs->m_tk_elems[1];
    icode *F_CONST_ID_ic=pcompi->ast_to_icode(F_CONST_ID);
    icode *I_CONSTANT_ic=pcompi->ast_to_icode(I_CONSTANT);

    F_CONST_ID_ic->fnum = I_CONSTANT_ic->num;
    F_CONST_ID_ic->const_refresh_width();

	//a->merge_icode(F_CONST_ID_ic);
	//a->merge_icode(I_CONSTANT_ic);
    return F_CONST_ID_ic;
}
class icode *  func_IAN_STRING_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 直接返回元素对应的icode
    ///
    ///
	//0x1701-string->STRING_ID STRING_LITERAL 
	//parent:
	// constant--> string
    token_defs *STRING_ID=tdefs->m_tk_elems[0];
    token_defs *STRING_LITERAL=tdefs->m_tk_elems[1];
    icode *STRING_ID_ic=pcompi->ast_to_icode(STRING_ID);
    icode *STRING_LITERAL_ic=pcompi->ast_to_icode(STRING_LITERAL);
	//a->merge_icode(STRING_ID_ic);
	//a->merge_icode(STRING_LITERAL_ic);

    STRING_ID_ic->name = STRING_LITERAL_ic->name;


    return STRING_ID_ic;
}


class icode *  func_IAN_VAR_IN_REF_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1801-var_in_ref->var_in_ref_ptr 
	//parent:
	// opr_elem--> var_in_ref
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_VAR_IN_REF_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1802-var_in_ref->var_in_ref_array 
	//parent:
	// opr_elem--> var_in_ref
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}

class icode *  func_IAN_VAR_IN_REF_PTR_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 直接返回元素对应的icode

	//0x1901-var_in_ref_ptr->var_in_start VAR_REF '*' I_CONSTANT 
	//parent:
	// var_in_ref--> var_in_ref_ptr

    token_defs *var_in_start=tdefs->m_tk_elems[0];
    token_defs *VAR_REF=tdefs->m_tk_elems[1];
    //token_defs *'*'=tdefs->m_tk_elems[2];
    token_defs *I_CONSTANT=tdefs->m_tk_elems[3];

    /// var_in类型icode
    icode *var_in_start_ic=pcompi->ast_to_icode(var_in_start);

    /// 查找对应的变量icode。如果找不到，返回NULL。如果找到，返回对应的icode
    icode *VAR_REF_ic=pcompi->ast_to_icode(VAR_REF);
    //icode *'*'_ic=pcompi->ast_to_icode('*');
    icode *I_CONSTANT_ic=pcompi->ast_to_icode(I_CONSTANT);

    var_in_start_ic->is_ptr = - I_CONSTANT_ic->num;
    if(VAR_REF_ic!=NULL)
    {
        // VAR_REF_ic返回的是一个引用。此处需要result=实际icode
        var_in_start_ic->result = pcompi->get_def_var(VAR_REF_ic);
    }
    else
    {
        var_in_start_ic->name = VAR_REF->val_str.substr(1);
        var_in_start_ic->result = NULL;
    }

    return var_in_start_ic;
}
class icode *  func_IAN_VAR_IN_REF_ARRAY_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 直接返回元素对应的icode

	//0x1a01-var_in_ref_array->var_in_start VAR_REF '[' opr_elem ']' 
	//parent:
	// var_in_ref--> var_in_ref_array
	// var_in_ref_array--> var_in_ref_array '[' opr_elem ']'

    token_defs *var_in_start=tdefs->m_tk_elems[0];
    token_defs *VAR_REF=tdefs->m_tk_elems[1];
    //token_defs *'['=tdefs->m_tk_elems[2];
    token_defs *opr_elem=tdefs->m_tk_elems[3];
    //token_defs *']'=tdefs->m_tk_elems[4];
    icode *var_in_start_ic=pcompi->ast_to_icode(var_in_start);
    icode *VAR_REF_ic=pcompi->ast_to_icode(VAR_REF);
    //icode *'['_ic=pcompi->ast_to_icode('[');
    icode *opr_elem_ic=pcompi->ast_to_icode(opr_elem);

    /// 引用的array都是--
    var_in_start_ic->is_array--;
    if(VAR_REF_ic!=NULL)
    {
        // VAR_REF_ic返回的是一个引用。此处需要result=实际icode
        var_in_start_ic->result = pcompi->get_def_var(VAR_REF_ic);
    }
    else
    {
        var_in_start_ic->name = VAR_REF->val_str.substr(1);
        var_in_start_ic->result = NULL;
    }
    var_in_start_ic->array_cnt.push_back(opr_elem_ic);

    return var_in_start_ic;

}
class icode *  func_IAN_VAR_IN_REF_ARRAY_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 直接返回元素对应的icode

	//0x1a02-var_in_ref_array->var_in_ref_array '[' opr_elem ']' 
	//parent:
	// var_in_ref--> var_in_ref_array
	// var_in_ref_array--> var_in_ref_array '[' opr_elem ']'
    token_defs *var_in_ref_array=tdefs->m_tk_elems[0];
	//token_defs *'['=tdefs->m_tk_elems[1];
    token_defs *opr_elem=tdefs->m_tk_elems[2];
	//token_defs *']'=tdefs->m_tk_elems[3];
    icode *var_in_ref_array_ic=pcompi->ast_to_icode(var_in_ref_array);
	//icode *'['_ic=pcompi->ast_to_icode('[');
    icode *opr_elem_ic=pcompi->ast_to_icode(opr_elem);

    var_in_ref_array_ic->is_array--;
    var_in_ref_array_ic->array_cnt.push_back(opr_elem_ic);

    return var_in_ref_array_ic;
}

class icode *  func_IAN_CONST_LIST_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 直接返回元素对应的icode
    /// TODO
    ///
	//0x1901-const_list->CONST_LIST_ID '[' opr_elem_seq ']' 
	//parent:
	// constant--> const_list

    token_defs *CONST_LIST_ID=tdefs->m_tk_elems[0];
	//token_defs *'['=tdefs->m_tk_elems[1];
    token_defs *opr_elem_seq=tdefs->m_tk_elems[2];
	//token_defs *']'=tdefs->m_tk_elems[3];
    icode *CONST_LIST_ID_ic=pcompi->ast_to_icode(CONST_LIST_ID);

    //icode *'['_ic=pcompi->ast_to_icode('[');
    /// opr_elem_seq 返回的ic是block
    icode *opr_elem_seq_ic=pcompi->ast_to_icode(opr_elem_seq);
    //icode *']'_ic=pcompi->ast_to_icode(']');

    CONST_LIST_ID_ic->merge_icode(opr_elem_seq_ic);


    //a->merge_icode(CONST_LIST_ID_ic);
	//a->merge_icode('['_ic);
	//a->merge_icode(opr_elem_seq_ic);
	//a->merge_icode(']'_ic);

    return CONST_LIST_ID_ic;
}
class icode *  func_IAN_VAR_IN_START_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 直接返回元素对应的icode
    /// new_icode(ICODE_TYPE_VAR_IN_VAR);


	//0x1a01-var_in_start->VAR_IN 
	//parent:
	// var_in_ref--> var_in_start VAR_REF '*' I_CONSTANT
	// var_in_ref--> var_in_start VAR_REF '[' opr_elem ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_VAR_IN_START_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1a02-var_in_start->VAR_IN_TMP 
	//parent:
	// var_in_ref--> var_in_start VAR_REF '*' I_CONSTANT
	// var_in_ref--> var_in_start VAR_REF '[' opr_elem ']'
return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_CALL_STATEMENT_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 返回block
	//0x1b01-call_statement->CALL_START VAR_REF ';' opr_elem_seq CALL_END VAR_REF ';' 
	//parent:
	// statement--> call_statement
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
    token_defs *CALL_START=tdefs->m_tk_elems[0];
    token_defs *VAR_REF=tdefs->m_tk_elems[1];
	//token_defs *';'=tdefs->m_tk_elems[2];
    token_defs *opr_elem_seq=tdefs->m_tk_elems[3];
	//token_defs *CALL_END=tdefs->m_tk_elems[4];
	//token_defs *VAR_REF=tdefs->m_tk_elems[5];
	//token_defs *';'=tdefs->m_tk_elems[6];
    icode *CALL_START_ic=pcompi->ast_to_icode(CALL_START);
    icode *VAR_REF_ic=pcompi->ast_to_icode(VAR_REF);
    CALL_START_ic->result = VAR_REF_ic;
	//icode *';'_ic=pcompi->ast_to_icode(';');
    icode *opr_elem_seq_ic=pcompi->ast_to_icode(opr_elem_seq);
	//icode *CALL_END_ic=pcompi->ast_to_icode(CALL_END);
	//icode *VAR_REF_ic=pcompi->ast_to_icode(VAR_REF);
	//icode *';'_ic=pcompi->ast_to_icode(';');
    CALL_START_ic->merge_icode(opr_elem_seq_ic);
    a->merge_icode(CALL_START_ic);
	//a->merge_icode(VAR_REF_ic);
	//a->merge_icode(';'_ic);
	//a->merge_icode(opr_elem_seq_ic);
	//a->merge_icode(CALL_END_ic);
	//a->merge_icode(VAR_REF_ic);
	//a->merge_icode(';'_ic);
	return a;
}
class icode *  func_IAN_CALL_STATEMENT_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x1b02-call_statement->CALL_START VAR_REF ';' CALL_END VAR_REF ';' 
	//parent:
	// statement--> call_statement
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
    token_defs *CALL_START=tdefs->m_tk_elems[0];
    token_defs *VAR_REF=tdefs->m_tk_elems[1];
	//token_defs *';'=tdefs->m_tk_elems[2];
	//token_defs *CALL_END=tdefs->m_tk_elems[3];
	//token_defs *VAR_REF=tdefs->m_tk_elems[4];
	//token_defs *';'=tdefs->m_tk_elems[5];
    icode *CALL_START_ic=pcompi->ast_to_icode(CALL_START);
    icode *VAR_REF_ic=pcompi->ast_to_icode(VAR_REF);

    CALL_START_ic->result = VAR_REF_ic;

	//icode *';'_ic=pcompi->ast_to_icode(';');
	//icode *CALL_END_ic=pcompi->ast_to_icode(CALL_END);
	//icode *VAR_REF_ic=pcompi->ast_to_icode(VAR_REF);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//a->merge_icode(CALL_START_ic);
	//a->merge_icode(VAR_REF_ic);
	//a->merge_icode(';'_ic);
	//a->merge_icode(CALL_END_ic);
	//a->merge_icode(VAR_REF_ic);
	//a->merge_icode(';'_ic);
    return CALL_START_ic;
}
class icode *  func_IAN_OPR_ELEM_SEQ_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 返回block
	//0x1c01-opr_elem_seq->opr_elem ';' 
	//parent:
	// const_list--> CONST_LIST_ID '[' opr_elem_seq ']'
	// call_statement--> CALL_START VAR_REF ';' opr_elem_seq CALL_END VAR_REF ';'
	// opr_elem_seq--> opr_elem_seq opr_elem ';'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
    token_defs *opr_elem=tdefs->m_tk_elems[0];
	//token_defs *';'=tdefs->m_tk_elems[1];
    icode *opr_elem_ic=pcompi->ast_to_icode(opr_elem);

	//icode *';'_ic=pcompi->ast_to_icode(';');
    a->merge_icode(opr_elem_ic);
	//a->merge_icode(';'_ic);
	return a;
}
class icode *  func_IAN_OPR_ELEM_SEQ_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 返回block

	//0x1c02-opr_elem_seq->opr_elem_seq opr_elem ';' 
	//parent:
	// const_list--> CONST_LIST_ID '[' opr_elem_seq ']'
	// call_statement--> CALL_START VAR_REF ';' opr_elem_seq CALL_END VAR_REF ';'
	// opr_elem_seq--> opr_elem_seq opr_elem ';'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
    token_defs *opr_elem_seq=tdefs->m_tk_elems[0];
    token_defs *opr_elem=tdefs->m_tk_elems[1];
	//token_defs *';'=tdefs->m_tk_elems[2];
    icode *opr_elem_seq_ic=pcompi->ast_to_icode(opr_elem_seq);
    icode *opr_elem_ic=pcompi->ast_to_icode(opr_elem);
	//icode *';'_ic=pcompi->ast_to_icode(';');
    a->merge_icode(opr_elem_seq_ic);
    a->merge_icode(opr_elem_ic);
	//a->merge_icode(';'_ic);
	return a;
}
class icode *  func_IAN_LABEL_DEF_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 返回语句icode

	//0x1d01-label_def->LABEL_START I_CONSTANT ';' 
	//parent:
	// statement--> label_def
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
    token_defs *LABEL_START=tdefs->m_tk_elems[0];
    token_defs *I_CONSTANT=tdefs->m_tk_elems[1];
	//token_defs *';'=tdefs->m_tk_elems[2];


    sym* s = pcompi->find_symbol("__LB"+I_CONSTANT->val_str);
    if(s!=NULL)
    {
        //已经有此定义直接返回
        return s->def_icode;
    }


    icode *LABEL_START_ic=pcompi->ast_to_icode(LABEL_START);

    LABEL_START_ic->name = I_CONSTANT->val_str;

    std::string sym_name = "__LB"+I_CONSTANT->val_str;
    pcompi->add_symbol(sym_name, LABEL_START_ic);

    return LABEL_START_ic;
}
class icode *  func_IAN_LABEL_REF_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 返回语句icode

	//0x1e01-label_ref->LABEL_REF I_CONSTANT 
	//parent:
	// opr_elem--> label_ref
    token_defs *LABEL_REF=tdefs->m_tk_elems[0];
    token_defs *I_CONSTANT=tdefs->m_tk_elems[1];
    icode *LABEL_REF_ic=pcompi->ast_to_icode(LABEL_REF);

    sym* s = pcompi->find_symbol("__LB"+I_CONSTANT->val_str);
    if(s==NULL)
    {
        //未定义
        icode *label_start_ic = pcompi->new_icode(ICODE_TYPE_LABELED_BLOCK);
        label_start_ic->name = I_CONSTANT->val_str;

        std::string sym_name = "__LB"+I_CONSTANT->val_str;
        pcompi->add_symbol(sym_name, label_start_ic);
        LABEL_REF_ic->result = label_start_ic;
    }
    else
    {
        LABEL_REF_ic->result = s->def_icode;
    }
    //icode *I_CONSTANT_ic=pcompi->ast_to_icode(I_CONSTANT);
	//a->merge_icode(LABEL_REF_ic);
	//a->merge_icode(I_CONSTANT_ic);
    return LABEL_REF_ic;
}

class icode *  func_IAN_INLINE_ASM_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//0x2001-inline_asm->INLINE_ASM STRING_LITERAL ';' 
	//parent:
	// statement--> inline_asm

    token_defs *INLINE_ASM=tdefs->m_tk_elems[0];
    token_defs *STRING_LITERAL=tdefs->m_tk_elems[1];
	//token_defs *';'=tdefs->m_tk_elems[2];
    icode *INLINE_ASM_ic=pcompi->ast_to_icode(INLINE_ASM);
    icode *STRING_LITERAL_ic=pcompi->ast_to_icode(STRING_LITERAL);
	//icode *';'_ic=pcompi->ast_to_icode(';');
	//a->merge_icode(INLINE_ASM_ic);
	//a->merge_icode(STRING_LITERAL_ic);
	//a->merge_icode(';'_ic);

    INLINE_ASM_ic->name = STRING_LITERAL_ic->name;
    return INLINE_ASM_ic;
}
 class icode *func_token_END(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
     /// 不可能用到此处
     assert(0);

	//END
	//parent:
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_EOL(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
     /// 不可能用到此处
     assert(0);

	//EOL
	//parent:
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_BLOCKS(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
     /// 不可能用到此处
     assert(0);

	//BLOCKS
	//parent:
	// file--> BLOCKS translation_unit BLOCKE
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_BLOCKE(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
     /// 不可能用到此处
     assert(0);

	//BLOCKE
	//parent:
	// file--> BLOCKS translation_unit BLOCKE
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_SCOPES(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
     /// 不可能用到此处
     assert(0);

	//SCOPES
	//parent:
	// compound_statement--> SCOPES SCOPEE
	// compound_statement--> SCOPES block_item_list SCOPEE
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_SCOPEE(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
     /// 不可能用到此处
     assert(0);
	//SCOPEE
	//parent:
	// compound_statement--> SCOPES SCOPEE
	// compound_statement--> SCOPES block_item_list SCOPEE
	assert(0);
}
 class icode *func_token_DEF_VAR(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
     /// 直接生成并返回对应类型的icode
	//DEF_VAR
	//parent:
	// def_var_start--> DEF_VAR
    icode *a = pcompi->new_icode(ICODE_TYPE_DEF_VAR);
	assert(0);
	return a;
}
 class icode *func_token_DEF_VAR_TMP(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
     /// 直接生成并返回对应类型的icode
	//DEF_VAR_TMP
	//parent:
	// def_var_start--> DEF_VAR_TMP
    icode *a = pcompi->new_icode(ICODE_TYPE_DEF_VAR_TMP);
	return a;
}
 class icode *func_token_VAR_IN(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
     /// 直接生成并返回对应类型的icode
	//VAR_IN
	//parent:
	// var_in_start--> VAR_IN
    icode *a = pcompi->new_icode(ICODE_TYPE_DEF_VAR_IN_VAR);
	return a;
}
 class icode *func_token_VAR_IN_TMP(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
     /// 直接生成并返回对应类型的icode
	//VAR_IN_TMP
	//parent:
	// var_in_start--> VAR_IN_TMP
    icode *a = pcompi->new_icode(ICODE_TYPE_DEF_VAR_IN_VAR_TMP);
	return a;
}
 class icode *func_token_DEF_ARG(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
     /// 直接生成并返回对应类型的icode
	//DEF_ARG
	//parent:
	// def_arg--> DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ';'
    icode *a = pcompi->new_icode(ICODE_TYPE_FUNC_DEF_ARG);
	return a;
}
 class icode *func_token_VOID(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
     /// 只处理result_ic中内容，不处理返回值
     ///


	//VOID
	//parent:
	// type_specifier_basic--> VOID
    result_ic->is_signed = 0;
    result_ic->m_bit_width = 0;
    return NULL;
}
 class icode *func_token_U1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//U1
	//parent:
	// type_specifier_basic--> U1
     result_ic->is_signed = 0;
     result_ic->m_bit_width = 1;
     return NULL;
}
 class icode *func_token_U8(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//U8
	//parent:
	// type_specifier_basic--> U8
     result_ic->is_signed = 0;
     result_ic->m_bit_width = 8;
     return NULL;
}
 class icode *func_token_U16(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//U16
	//parent:
	// type_specifier_basic--> U16
     result_ic->is_signed = 0;
     result_ic->m_bit_width = 16;
     return NULL;
}
 class icode *func_token_U24(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//U24
	//parent:
	// type_specifier_basic--> U24
     result_ic->is_signed = 0;
     result_ic->m_bit_width = 24;
     return NULL;
}
 class icode *func_token_U32(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//U32
	//parent:
	// type_specifier_basic--> U32
     result_ic->is_signed = 0;
     result_ic->m_bit_width = 32;
     return NULL;
}
 class icode *func_token_U64(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//U64
	//parent:
	// type_specifier_basic--> U64
     result_ic->is_signed = 0;
     result_ic->m_bit_width = 64;
     return NULL;
}
 class icode *func_token_F16(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//F16
	//parent:
	// type_specifier_basic--> F16
     result_ic->is_signed = 0;
     result_ic->is_float32 = 1;
     result_ic->m_bit_width = 16;
     return NULL;
}
 class icode *func_token_F32(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//F32
	//parent:
	// type_specifier_basic--> F32
     result_ic->is_signed = 0;
     result_ic->is_float32 = 1;
     result_ic->m_bit_width = 32;
     return NULL;
}
 class icode *func_token_F64(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//F64
	//parent:
	// type_specifier_basic--> F64
     result_ic->is_signed = 0;
     result_ic->is_float32 = 1;
     result_ic->m_bit_width = 64;
     return NULL;
}
 class icode *func_token_I1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//I1
	//parent:
	// type_specifier_basic--> I1
     result_ic->is_signed = 1;
     result_ic->is_float32 = 0;
     result_ic->m_bit_width = 1;
     return NULL;
}
 class icode *func_token_I8(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//I8
	//parent:
	// type_specifier_basic--> I8
     result_ic->is_signed = 1;
     result_ic->is_float32 = 0;
     result_ic->m_bit_width = 8;
     return NULL;
}
 class icode *func_token_I16(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//I16
	//parent:
	// type_specifier_basic--> I16
     result_ic->is_signed = 1;
     result_ic->is_float32 = 0;
     result_ic->m_bit_width = 16;
     return NULL;
}
 class icode *func_token_I24(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//I24
	//parent:
	// type_specifier_basic--> I24
     result_ic->is_signed = 1;
     result_ic->is_float32 = 0;
     result_ic->m_bit_width = 24;
     return NULL;
}
 class icode *func_token_I32(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//I32
	//parent:
	// type_specifier_basic--> I32
     result_ic->is_signed = 1;
     result_ic->is_float32 = 0;
     result_ic->m_bit_width = 32;
     return NULL;
}
 class icode *func_token_I64(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//I64
	//parent:
	// type_specifier_basic--> I64
     result_ic->is_signed = 1;
     result_ic->is_float32 = 0;
     result_ic->m_bit_width = 64;
     return NULL;
}
 class icode *func_token_U_NUM(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
     /// FIXME number错误，需要string2number转为数字、
	//U_NUM
	//parent:
	// type_specifier_basic--> U_NUM
     result_ic->is_signed = 0;
     result_ic->is_float32 = 0;
     result_ic->m_bit_width = StrToNumber(tdefs->val_str.substr(1));
     return NULL;
}

 class icode *func_token_LABEL_START(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//LABEL_START
	//parent:
	// label_def--> LABEL_START I_CONSTANT ';'
    icode *a = pcompi->new_icode(ICODE_TYPE_LABELED_BLOCK);
	return a;
}
 class icode *func_token_LABEL_REF(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//LABEL_REF
	//parent:
	// label_ref--> LABEL_REF I_CONSTANT
    icode *a = pcompi->new_icode(ICODE_TYPE_LABELED_BLOCK_START_REF);
	return a;
}
 class icode *func_token_VAR_REF(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
     //变量引用，如果定义，返回变量icode。否则返回空NULL
	//VAR_REF
	//parent:
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' function_arg compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' function_arg compound_statement FUNC_END VAR_REF ';'
	// opr_elem--> VAR_REF
	// var_in_ref--> var_in_start VAR_REF '*' I_CONSTANT
	// var_in_ref--> var_in_start VAR_REF '[' opr_elem ']'
	// call_statement--> CALL_START VAR_REF ';' opr_elem_seq CALL_END VAR_REF ';'


    sym* s = pcompi->find_symbol(tdefs->val_str.substr(1));
    if(s==NULL)
    {
        return NULL;
    }
    return pcompi->m_top_icodes->new_ref_icode(s->def_icode);

}

 class icode *func_token_VAR_NULL(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
     ///返回null的指针
     ///
	//VAR_NULL
	//parent:
	// opr_elem--> VAR_NULL
    return NULL;
}

 class icode *func_token_FUNC_START(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//FUNC_START
	//parent:
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' function_arg compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' function_arg compound_statement FUNC_END VAR_REF ';'
    icode *a = pcompi->new_icode(ICODE_TYPE_FUNC);
	return a;
}
 class icode *func_token_FUNC_END(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
     ///此函数不用
     assert(0);
	//FUNC_END
	//parent:
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' function_arg compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' function_arg compound_statement FUNC_END VAR_REF ';'

}
 class icode *func_token_FUNC_RETURN(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//FUNC_RETURN
	//parent:
	// statement--> FUNC_RETURN
    icode *a = pcompi->new_icode(ICODE_TYPE_FUNC_RETURN);
	return a;
}
 class icode *func_token_CALL_START(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//CALL_START
	//parent:
	// call_statement--> CALL_START VAR_REF ';' opr_elem_seq CALL_END VAR_REF ';'
    icode *a = pcompi->new_icode(ICODE_TYPE_CALL);
	return a;
}
 class icode *func_token_CALL_END(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
     /// 此处不需要
     ///

     assert(0);
     return NULL;
	//CALL_END
	//parent:
	// call_statement--> CALL_START VAR_REF ';' opr_elem_seq CALL_END VAR_REF ';'
	icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
	assert(0);
	return a;
}
 class icode *func_token_RET_TYPE(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//RET_TYPE
	//parent:
	// ret_type--> RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ';'
    icode *a = pcompi->new_icode(ICODE_TYPE_FUNC_RET_TYPE);
	return a;
}

 class icode *func_token_IDENTIFIER(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
     /// 此处不需要
     ///

     assert(0);
     return NULL;
     //IDENTIFIER
	//parent:
	// func_attrib1--> IDENTIFIER '(' STRING_LITERAL ')'
	// func_attrib1--> IDENTIFIER '(' I_CONSTANT ')'
    //icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);
    //assert(0);
    //return a;
}

 class icode *func_token_VAR_NAME_IDENTIFIER(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
     /// 此函数查询变量是否已经定义
     /// 如果未定义，返回NULL
     /// 如果已经定义，返回block result->已有变量的引用
     /// 2021.1.9 修改返回值，改为返回 已有变量icode
	//VAR_NAME_IDENTIFIER
	//parent:
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ';' function_arg compound_statement FUNC_END VAR_REF ';'
	// function_definition--> FUNC_START VAR_NAME_IDENTIFIER ',' func_attrib ';' function_arg compound_statement FUNC_END VAR_REF ';'
	// ret_type--> RET_TYPE VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_arg--> DEF_ARG VAR_NAME_IDENTIFIER ',' type_specifier ';'
	// def_one_var--> def_var_start VAR_NAME_IDENTIFIER ',' type_specifier ';'

     ///此处为变量定义。需要查找符号表
     /// 如果已经存在此符号，则是错误，不能再定义
     /// 如果不存在，则可以定义此符号

     assert(tdefs->val_str.size()>1);
     std::string var_name = tdefs->val_str.substr(1);

     sym* s = pcompi->find_symbol(var_name);

     if(s==NULL)
     {
         //之前无定义
         return NULL;
     }
     if(s->m_level!=pcompi->m_top_icodes->m_sym_manage.m_level)
     {
         //虽然定义过了，但是level不一致，可以重复定义
         /// TODO: 此处可添加覆盖定义的报警？
         return NULL;
     }

    return s->def_icode;
}
 class icode *func_token_I_CONST_ID(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//I_CONST_ID
	//parent:
	// i_const--> I_CONST_ID I_CONSTANT
    icode *a = pcompi->new_icode(ICODE_TYPE_I_CONST);
	return a;
}
 class icode *func_token_F_CONST_ID(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//F_CONST_ID
	//parent:
	// f_const--> F_CONST_ID F_CONSTANT
    icode *a = pcompi->new_icode(ICODE_TYPE_F_CONST);
	return a;
}
 class icode *func_token_STRING_ID(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//STRING_ID
	//parent:
	// string--> STRING_ID STRING_LITERAL
    icode *a = pcompi->new_icode(ICODE_TYPE_CONST_STRING);
	return a;
}
 class icode *func_token_CONST_LIST_ID(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//CONST_LIST_ID
	//parent:
	// const_list--> CONST_LIST_ID '[' opr_elem_seq ']'

     icode *a = pcompi->new_icode(ICODE_TYPE_CONST_LIST);
	return a;
}
 class icode *func_token_I_CONSTANT(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//I_CONSTANT
	//parent:
	// func_attrib1--> IDENTIFIER '(' I_CONSTANT ')'
	// type_specifier--> type_specifier_basic '*' I_CONSTANT '*' '[' type_specifier ']'
	// i_const--> I_CONST_ID I_CONSTANT
	// var_in_ref--> var_in_start VAR_REF '*' I_CONSTANT
	// label_def--> LABEL_START I_CONSTANT ';'
	// label_ref--> LABEL_REF I_CONSTANT
     icode *a = pcompi->new_icode(ICODE_TYPE_I_CONST);
     a->num = StrToNumber(tdefs->val_str);
     a->const_refresh_width();
     a->name = tdefs->val_str;
     return a;
}
 class icode *func_token_F_CONSTANT(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//F_CONSTANT
	//parent:
	// f_const--> F_CONST_ID F_CONSTANT
    icode *a = pcompi->new_icode(ICODE_TYPE_F_CONST);
    a->fnum = StrToFloat(tdefs->val_str);
    a->name = tdefs->val_str;
    a->const_refresh_width();
	return a;
}
 class icode *func_token_STRING_LITERAL(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//STRING_LITERAL
	//parent:
	// func_attrib1--> IDENTIFIER '(' STRING_LITERAL ')'
	// opr_statement--> OPR_START STRING_LITERAL ',' opr_elem ';' ',' opr_elem ';' ',' opr_elem ';'
	// string--> STRING_ID STRING_LITERAL
    icode *a = pcompi->new_icode(ICODE_TYPE_CONST_STRING);
    a->name = string_eval( tdefs->val_str);
	return a;
}
 class icode *func_token_OPR_START(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
     ///直接新生成对应的icode
	//OPR_START
	//parent:
	// opr_statement--> OPR_START STRING_LITERAL ',' opr_elem ';' ',' opr_elem ';' ',' opr_elem ';'
    icode *a = pcompi->new_icode(ICODE_TYPE_EXP_OP);
	return a;
}

 class icode *func_token_INLINE_ASM(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
	//INLINE_ASM
	//parent:
	// inline_asm--> INLINE_ASM STRING_LITERAL ';'
    icode *a = pcompi->new_icode(ICODE_TYPE_ASM);
	return a;
}

}//namespace NS_IR2ICODE
