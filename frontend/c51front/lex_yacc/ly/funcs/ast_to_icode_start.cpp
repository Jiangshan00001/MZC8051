/************************************************
 *
 *
 * 未实现：旧式函数的定义 //0x5201-function_definition->declaration_specifiers declarator declaration_list compound_statement
 *
 *
 * 输入：tdefs。 通过函数func_IAN_EXTERNAL_DECLARATION_1 func_IAN_EXTERNAL_DECLARATION_2 输入
 * 输出：将输出的icode放入m_top_icodes
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 *
 * ************************************************/



#include "ast_to_icode_start.h"
#include "parser.h"
#include "comp_context_gen_defs.h"
#include <assert.h>
#include "icode.h"
#include "comp_context.h"
#include "token_defs.h"
#include "mylog.h"
#include "str2number.h"
using mylog::cerr;
using mylog::cout;



namespace NS_C512IR{




class icode *  func_IAN_TRANSLATION_UNIT_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4f01-translation_unit->external_declaration
    //parent:
    // translation_unit--> translation_unit external_declaration
    // file--> translation_unit
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *external_declaration=tdefs->m_tk_elems[0];
    //icode *external_declaration_ic=pcompi->ast_to_icode(external_declaration);
    //a->merge_icode(external_declaration_ic);
    assert(0);
    return a;
}

class icode *  func_IAN_TRANSLATION_UNIT_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4f02-translation_unit->translation_unit external_declaration
    //parent:
    // translation_unit--> translation_unit external_declaration
    // file--> translation_unit
    //translation_unit->translation_unit external_declaration
    cerr<<"pcompi should never be executed!\n";
    cerr<<"translation_unit IAN_TRANSLATION_UNIT_2\n";
    cout<<"pcompi should never be executed!\n";
    cout<<"translation_unit IAN_TRANSLATION_UNIT_2\n";

    assert(0);/* not supported here*/
}

class icode *  func_IAN_FILE_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x5001-file->/*empty*/
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs */*empty*/=tdefs->m_tk_elems[0];
    //icode */*empty*/_ic=pcompi->ast_to_icode(/*empty*/);
    //a->merge_icode(/*empty*/_ic);

    cerr<<"empty source file\n";

    assert(0);
    return a;
}

class icode *  func_IAN_FILE_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x5002-file->translation_unit
    //parent:

    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *translation_unit=tdefs->m_tk_elems[0];
    //icode *translation_unit_ic=pcompi->ast_to_icode(translation_unit);
    //a->merge_icode(translation_unit_ic);
    assert(0);
    return a;
}



class icode *  func_IAN_EXTERNAL_DECLARATION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x5101-external_declaration->function_definition
    //parent:
    // translation_unit--> external_declaration
    // translation_unit--> translation_unit external_declaration
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}

class icode *  func_IAN_EXTERNAL_DECLARATION_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x5102-external_declaration->declaration
    //parent:
    // translation_unit--> external_declaration
    // translation_unit--> translation_unit external_declaration
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}

class icode *  func_IAN_FUNCTION_DEFINITION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x5201-function_definition->declaration_specifiers declarator declaration_list compound_statement
    //parent:
    // external_declaration--> function_definition
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *declaration_specifiers=tdefs->m_tk_elems[0];
    //token_defs *declarator=tdefs->m_tk_elems[1];
    //token_defs *declaration_list=tdefs->m_tk_elems[2];
    //token_defs *compound_statement=tdefs->m_tk_elems[3];
    //icode *declaration_specifiers_ic=pcompi->ast_to_icode(declaration_specifiers);
    //icode *declarator_ic=pcompi->ast_to_icode(declarator);
    //icode *declaration_list_ic=pcompi->ast_to_icode(declaration_list);
    //icode *compound_statement_ic=pcompi->ast_to_icode(compound_statement);
    //a->merge_icode(declaration_specifiers_ic);
    //a->merge_icode(declarator_ic);
    //a->merge_icode(declaration_list_ic);
    //a->merge_icode(compound_statement_ic);
    assert(0);
    return a;
}

class icode *  func_IAN_FUNCTION_DEFINITION_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x5202-function_definition->declaration_specifiers declarator compound_statement
    //parent:
    // external_declaration--> function_definition
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    return pcompi->ast_to_icode_func_definition(tdefs, need_result_icode, a);
}

}//namespace end

