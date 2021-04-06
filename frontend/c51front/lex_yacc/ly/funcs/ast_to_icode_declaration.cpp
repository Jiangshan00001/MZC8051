/**************************************************
 *
 *
 *
 *
 * 未完成：无
 * 声明变量或函数
 *
 * 输入：
 * 输出： 1 如果是struct enum等 没有具体变量的结构，则返回空block。
 *       2 如果是具体变量或函数定义，则返回带变量定义的block。
 *       3即使是只声明未定义的变量或函数，此处返回的指针后期也会被填充为
 *      定义所在位置。
 *
 *
 *
 *
 *
 * declaration
    : declaration_specifiers ';'
    | declaration_specifiers init_declarator_list ';'
    | static_assert_declaration
    ;
declaration_specifiers
    : declaration_specifiers_
                        ;


declaration_specifiers_
        : storage_class_specifier declaration_specifiers_
        | storage_class_specifier
        | type_specifier declaration_specifiers_
        | type_specifier
        | type_qualifier declaration_specifiers_
        | type_qualifier
        | function_specifier declaration_specifiers_
        | function_specifier
        | alignment_specifier declaration_specifiers_
        | alignment_specifier
        ;





init_declarator_list
    : init_declarator
    | init_declarator_list ',' init_declarator
    ;

init_declarator
    : declarator '=' initializer
    | declarator
    ;

 *
 * *************************************************/


#include "driver.h"
#include "ast_to_icode_declaration.h"

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



class icode *  func_IAN_DECLARATION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1b01-declaration->declaration_specifiers ';'
    //parent:
    // block_item--> declaration
    // iteration_statement--> FOR '(' declaration expression_statement ')' statement
    // iteration_statement--> FOR '(' declaration expression_statement expression ')' statement
    // external_declaration--> declaration
    // declaration_list--> declaration
    // declaration_list--> declaration_list declaration


    /// struct A{ int a};
    /// enum B{B1, B2,};


    icode *type_ic = pcompi->new_icode();
    type_ic->m_type= ICODE_TYPE_DEF_VAR;

    pcompi->ast_to_icode(tdefs->m_tk_elems[0], 0, type_ic);

    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;




    return a;
}

class icode *  func_IAN_DECLARATION_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1b02-declaration->declaration_specifiers init_declarator_list ';'
    //parent:
    // block_item--> declaration
    // iteration_statement--> FOR '(' declaration expression_statement ')' statement
    // iteration_statement--> FOR '(' declaration expression_statement expression ')' statement
    // external_declaration--> declaration
    // declaration_list--> declaration
    // declaration_list--> declaration_list declaration
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;


    /// declaration_specifiers(int) init_declarator_list(a);
    /// declaration_specifiers(int) init_declarator_list(a=1);
    /// declaration_specifiers(typedef unsigned char) init_declarator_list(u8);
    /// declaration_specifiers(u8) init_declarator_list(a=1);
    /// declaration_specifiers(void) init_declarator_list(a()) ;
    /// declaration_specifiers(int) init_declarator(*a=0);
    /// declaration_specifiers(int) init_declarator(a[4][5]);

    icode *b = NULL;
    //b->m_type = ICODE_TYPE_DEF_VAR;
    token_defs *declaration_specifiers = tdefs->m_tk_elems[0];
    token_defs* init_declarator_list = tdefs->m_tk_elems[1];


    icode *type_ic = pcompi->new_icode();
    type_ic->m_type= ICODE_TYPE_DEF_VAR;

    pcompi->ast_to_icode(declaration_specifiers, 0, type_ic);
    type_ic->m_level = pcompi->m_top_icodes->m_sym_manage.m_level;


    ///--------------------------
    /// 2020.9.14 添加调试位置信息
    type_ic->m_dir_line_no = declaration_specifiers->line_no;
    type_ic->m_dir_source = declaration_specifiers->m_file_name;
    type_ic->m_source = pcompi->mp_driver->streamname;
    type_ic->m_line_no = type_ic->m_dir_line_no;

#if 0
    ///2021.3.30 此处去掉对于函数的单独处理，在ast_to_icode中处理
    ///--------------------------

    if((init_declarator_list->m_tk_type_int==IAN_DIRECT_DECLARATOR_FUNCTION1_2)||
            (init_declarator_list->m_tk_type_int==IAN_DIRECT_DECLARATOR_FUNCTION1_3)||
            (init_declarator_list->m_tk_type_int==IAN_DIRECT_DECLARATOR_FUNCTION1_4)||
            (init_declarator_list->m_tk_type_int==IAN_DIRECT_DECLARATOR_FUNCTION2_2))
    {
        //函数声明。 函数名字在icode的name中
        std::string func_name;
        pcompi->ast_to_icode_func_decl(declaration_specifiers, init_declarator_list, a, func_name);
        return a;
    }
#endif


    pcompi->m_curr_var_type  = type_ic;
    ///如果是typedef，此处已经声明变量，后面不再重复声明
    icode *c = pcompi->ast_to_icode(init_declarator_list, 1);
    pcompi->m_curr_var_type  = NULL;

    a->merge_icode(c);
    return a;
}

class icode *  func_IAN_DECLARATION_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1b03-declaration->static_assert_declaration
    //parent:
    // block_item--> declaration
    // iteration_statement--> FOR '(' declaration expression_statement ')' statement
    // iteration_statement--> FOR '(' declaration expression_statement expression ')' statement
    // external_declaration--> declaration
    // declaration_list--> declaration
    // declaration_list--> declaration_list declaration
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}


class icode *  func_IAN_DECLARATION_SPECIFIERS_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1c01-declaration_specifiers->declaration_specifiers_
    //parent:
    // declaration--> declaration_specifiers ';'
    // declaration--> declaration_specifiers init_declarator_list ';'
    // parameter_declaration--> declaration_specifiers declarator
    // parameter_declaration--> declaration_specifiers abstract_declarator
    // parameter_declaration--> declaration_specifiers
    // function_definition--> declaration_specifiers declarator declaration_list compound_statement
    // function_definition--> declaration_specifiers declarator compound_statement
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_DECLARATION_SPECIFIERS__1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1d01-declaration_specifiers_->storage_class_specifier declaration_specifiers_
    //parent:
    // declaration_specifiers--> declaration_specifiers_
    // declaration_specifiers_--> storage_class_specifier declaration_specifiers_
    // declaration_specifiers_--> type_specifier declaration_specifiers_
    // declaration_specifiers_--> type_qualifier declaration_specifiers_
    // declaration_specifiers_--> function_specifier declaration_specifiers_

    //storage_class_specifier(typedef)  declaration_specifiers_(unsigned char)
    //storage_class_specifier(extern)  declaration_specifiers_(unsigned char)
    token_defs *storage_class_specifier = tdefs->m_tk_elems[0];
    token_defs *declaration_specifiers_ = tdefs->m_tk_elems[1];


    icode* b = NULL;
    if(result_ic)
    {
        b=result_ic;
    }
    else
    {
        b=pcompi->new_icode();
        b->m_type=ICODE_TYPE_DEF_VAR;
    }

    //此处改为先解析左边的，再解析右边的，如果长度不一致，则右边会覆盖左边的。
    // unsigned short;--->unsigned-->bw=4. short-->bw=2
    // signed char
    // long long
    //
    pcompi->ast_to_icode(storage_class_specifier,0, b);
    pcompi->ast_to_icode(declaration_specifiers_, 0, b);

    return NULL;
}
class icode *  func_IAN_DECLARATION_SPECIFIERS__2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1d02-declaration_specifiers_->storage_class_specifier
    //parent:
    // declaration_specifiers--> declaration_specifiers_
    // declaration_specifiers_--> storage_class_specifier declaration_specifiers_
    // declaration_specifiers_--> type_specifier declaration_specifiers_
    // declaration_specifiers_--> type_qualifier declaration_specifiers_
    // declaration_specifiers_--> function_specifier declaration_specifiers_
    // declaration_specifiers_--> alignment_specifier declaration_specifiers_
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_DECLARATION_SPECIFIERS__3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1d03-declaration_specifiers_->type_specifier declaration_specifiers_
    //parent:
    // declaration_specifiers--> declaration_specifiers_
    // declaration_specifiers_--> storage_class_specifier declaration_specifiers_
    // declaration_specifiers_--> type_specifier declaration_specifiers_
    // declaration_specifiers_--> type_qualifier declaration_specifiers_
    // declaration_specifiers_--> function_specifier declaration_specifiers_
    // declaration_specifiers_--> alignment_specifier declaration_specifiers_

    /// 3 和1 虽然内容不一样，但形式完全一样，所以直接调用
    return func_IAN_DECLARATION_SPECIFIERS__1(pcompi, tdefs, need_result_icode, result_ic);
}
class icode *  func_IAN_DECLARATION_SPECIFIERS__4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1d04-declaration_specifiers_->type_specifier
    //parent:
    // declaration_specifiers--> declaration_specifiers_
    // declaration_specifiers_--> storage_class_specifier declaration_specifiers_
    // declaration_specifiers_--> type_specifier declaration_specifiers_
    // declaration_specifiers_--> type_qualifier declaration_specifiers_
    // declaration_specifiers_--> function_specifier declaration_specifiers_
    // declaration_specifiers_--> alignment_specifier declaration_specifiers_
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_DECLARATION_SPECIFIERS__5(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1d05-declaration_specifiers_->type_qualifier declaration_specifiers_
    //parent:
    // declaration_specifiers--> declaration_specifiers_
    // declaration_specifiers_--> storage_class_specifier declaration_specifiers_
    // declaration_specifiers_--> type_specifier declaration_specifiers_
    // declaration_specifiers_--> type_qualifier declaration_specifiers_
    // declaration_specifiers_--> function_specifier declaration_specifiers_
    // declaration_specifiers_--> alignment_specifier declaration_specifiers_

    /// 5 和1 虽然内容不一样，但形式完全一样，所以直接调用
    return func_IAN_DECLARATION_SPECIFIERS__1(pcompi, tdefs, need_result_icode, result_ic);
}
class icode *  func_IAN_DECLARATION_SPECIFIERS__6(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1d06-declaration_specifiers_->type_qualifier
    //parent:
    // declaration_specifiers--> declaration_specifiers_
    // declaration_specifiers_--> storage_class_specifier declaration_specifiers_
    // declaration_specifiers_--> type_specifier declaration_specifiers_
    // declaration_specifiers_--> type_qualifier declaration_specifiers_
    // declaration_specifiers_--> function_specifier declaration_specifiers_
    // declaration_specifiers_--> alignment_specifier declaration_specifiers_
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_DECLARATION_SPECIFIERS__7(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1d07-declaration_specifiers_->function_specifier declaration_specifiers_
    //parent:
    // declaration_specifiers--> declaration_specifiers_
    // declaration_specifiers_--> storage_class_specifier declaration_specifiers_
    // declaration_specifiers_--> type_specifier declaration_specifiers_
    // declaration_specifiers_--> type_qualifier declaration_specifiers_
    // declaration_specifiers_--> function_specifier declaration_specifiers_
    // declaration_specifiers_--> alignment_specifier declaration_specifiers_

    /// 7 和1 虽然内容不一样，但形式完全一样，所以直接调用
    return func_IAN_DECLARATION_SPECIFIERS__1(pcompi, tdefs, need_result_icode, result_ic);

}
class icode *  func_IAN_DECLARATION_SPECIFIERS__8(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1d08-declaration_specifiers_->function_specifier
    //parent:
    // declaration_specifiers--> declaration_specifiers_
    // declaration_specifiers_--> storage_class_specifier declaration_specifiers_
    // declaration_specifiers_--> type_specifier declaration_specifiers_
    // declaration_specifiers_--> type_qualifier declaration_specifiers_
    // declaration_specifiers_--> function_specifier declaration_specifiers_
    // declaration_specifiers_--> alignment_specifier declaration_specifiers_
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_DECLARATION_SPECIFIERS__9(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1d09-declaration_specifiers_->alignment_specifier declaration_specifiers_
    //parent:
    // declaration_specifiers--> declaration_specifiers_
    // declaration_specifiers_--> storage_class_specifier declaration_specifiers_
    // declaration_specifiers_--> type_specifier declaration_specifiers_
    // declaration_specifiers_--> type_qualifier declaration_specifiers_
    // declaration_specifiers_--> function_specifier declaration_specifiers_
    // declaration_specifiers_--> alignment_specifier declaration_specifiers_

    /// 9 和1 虽然内容不一样，但形式完全一样，所以直接调用
    return func_IAN_DECLARATION_SPECIFIERS__1(pcompi, tdefs, need_result_icode, result_ic);

}
class icode *  func_IAN_DECLARATION_SPECIFIERS__10(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1d0a-declaration_specifiers_->alignment_specifier
    //parent:
    // declaration_specifiers--> declaration_specifiers_
    // declaration_specifiers_--> storage_class_specifier declaration_specifiers_
    // declaration_specifiers_--> type_specifier declaration_specifiers_
    // declaration_specifiers_--> type_qualifier declaration_specifiers_
    // declaration_specifiers_--> function_specifier declaration_specifiers_
    // declaration_specifiers_--> alignment_specifier declaration_specifiers_
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}

class icode *  func_IAN_INIT_DECLARATOR_LIST_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{   //例子： char *b; -->init_declarator(*b)
    //0x1e01-init_declarator_list->init_declarator
    //parent:
    // declaration--> declaration_specifiers init_declarator_list ';'
    // init_declarator_list--> init_declarator_list ',' init_declarator
    icode *ret = pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);


    return ret;
}
class icode *  func_IAN_INIT_DECLARATOR_LIST_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1e02-init_declarator_list->init_declarator_list ',' init_declarator
    //parent:
    // declaration--> declaration_specifiers init_declarator_list ';'
    // init_declarator_list--> init_declarator_list ',' init_declarator
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    token_defs * init_declarator_list= tdefs->m_tk_elems[0];
    token_defs * init_declarator= tdefs->m_tk_elems[2];

    icode * a2= pcompi->ast_to_icode(init_declarator_list, 1);
    icode * a3= pcompi->ast_to_icode(init_declarator, 1);

    a->merge_icode(a2);
    a->merge_icode(a3);

    return a;
}

class icode *  func_IAN_INIT_DECLARATOR_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1f01-init_declarator->declarator '=' initializer
    //parent:
    // init_declarator_list--> init_declarator
    // init_declarator_list--> init_declarator_list ',' init_declarator
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;


    /// 2021.1.25 添加opr init。用于初始化变量值

    /// int a =1;
    /// 1b02-declaration(int a=1;)-3
    /// -- type_specifier(int)
    /// -- 1f01-init_declarator(a=1)
    /// ---- declarator(a)
    /// ---- =
    /// ---- initializer(1);
    /// --;
    ///
    ///
    /// int a[5] = {5,2,6};
    /// 1b02-declaration(int a[5] = {5,2,6};)-3
    /// -- type_specifier(int)
    /// -- 1f01-init_declarator(a[5] = {5,2,6})-3
    /// ---- 320a-direct_declarator_array(a[5])-4
    /// -------- a
    /// -------- [
    /// -------- 5
    /// -------- ]
    /// ---- =
    /// ---- 4001-initializer-3
    /// -------- {
    /// -------- 4104-initializer_list-3
    /// -----------initializer_list, num_elem
    ///
    ///
    ///int *a=0;
    /// 1f01--> 3001(declarator)  identifier = const(1);
    ///
    ///
    /// -- ;
    token_defs * declarator = tdefs->m_tk_elems[0];
    token_defs * initializer = tdefs->m_tk_elems[2];

    icode *b = pcompi->ast_to_icode(declarator, 1);
    a->merge_icode(b);


    // 添加对数组的支持
    //添加新变量。名称b->result
    int is_already_exist=0;
    icode * asym = pcompi->new_var(b->result, pcompi->m_curr_var_type, is_already_exist);//

    if(!is_already_exist)
    {
        ///添加变量定义
        a->merge_icode(asym);
    }

    icode* b_ref = pcompi->new_ref_icode(asym);


    ///-------------------------------------------------
    ///变量的初始值
    /// 如果是数组，初始值是向数组内部填内容
#if 0
    if(asym->is_array)
    {
        b_ref->m_type = ICODE_TYPE_DEF_VAR_IN_VAR;
        b_ref->is_ptr = - asym->is_array;
        b_ref->m_bit_width = asym->get_array_bit_width();
    }
#endif
    ///-------------------------------------------------
    ///


    /// , b_ref--2021.1.25不再放在result参数中
    ///
    //后面的语句。如果语句结果已经在b_ref中，则不再赋值
    icode * ret_ic = pcompi->ast_to_icode(initializer, 1);
    a->merge_icode(ret_ic);

    ///===========
    /// 此处函数功能是，根据declarator的类型，对initializer的位宽做修正。
    /// eg: char a = 2567; const的位宽只能是8
    /// eg: int a[4]={1,2,3,4} const的位宽只能是sizeof(int)
    ///===========
    ///
    pcompi->correct_initializer_width_from_declarator(asym, ret_ic->result);


    ///2021.1.25 添加init算符
    #if 0
    ///-----------------------------------------------------
    /// char a[]="pcompi is a string";
    /// 这种情况下，是复制数据。
    /// 其他默认情况，都是复制指针，例如：
    /// char *a = "pcompi is a string";
    if(asym->is_array && ret_ic->result->m_type==ICODE_TYPE_SYMBOL_REF)
    {
        if(ret_ic->result->result->m_type==ICODE_TYPE_CONST_STRING)
        {
            ret_ic->result->is_ptr = -1;
        }
    }
    ///-----------------------------------------------------
    #endif

    //if((ret_ic->result->m_type!=ICODE_TYPE_SYMBOL_REF)||(ret_ic->result->result!=b_ref->result))
    {

        ///添加变量初始化
        /// 2020.8.10 =赋值运算符，改为 right result

        //icode *c = pcompi->new_copy_icode_gen(ret_ic->result, b_ref);
        icode *c = pcompi->new_opr_icode("init",NULL, ret_ic->result, b_ref  );

        a->merge_icode(c);
    }
    return a;
}

class icode *  func_IAN_INIT_DECLARATOR_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1f02-init_declarator->declarator
    //parent:
    // init_declarator_list--> init_declarator
    // init_declarator_list--> init_declarator_list ',' init_declarator

    icode *b = pcompi->ast_to_icode(tdefs, 1);
#if 0
    if(b->result->m_type==ICODE_TYPE_FUNC)
    {
        /// 函数不在此处处理
        {
            return b;
        }
    }
#endif
    //此处进行变量声明

    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    a->merge_icode(b);


    // typedef unsigned int u16;也会在此处声明 u16
    // 添加对数组的支持
    //添加新变量。名称b->result
    int is_already_exist=0;
    icode * asym = pcompi->new_var(b->result, pcompi->m_curr_var_type, is_already_exist);//

    if(!is_already_exist)
    {
        ///添加变量定义
        a->merge_icode(asym);
    }

    icode* b_ref = pcompi->new_ref_icode(asym);


    ///-------------------------------------------------
    ///变量的初始值
    /// 如果是数组，初始值是向数组内部填内容
    /// 此处没有初始值内容，所以不需要处理is_array

    //if(asym->is_array)
    //{
    //    b_ref->is_ptr = - asym->is_array;
    //    b_ref->m_bit_width = asym->get_array_bit_width();
    //}
    ///-------------------------------------------------

    return a;
}


}//namespace end
