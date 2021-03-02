/*********************************************
 *
 * 输入： tdefs result_ic
 * 输出： 结果放入result_ic. 返回值为NULL
 *
 *struct_or_union_specifier
        : struct_or_union '{' struct_declaration_list '}'
        | struct_or_union identifier '{' struct_declaration_list '}'
        | struct_or_union identifier
        ;

struct_or_union
    : STRUCT
    | UNION
    ;
struct_declaration_list
    : struct_declaration
    | struct_declaration_list struct_declaration
    ;

struct_declaration
    : specifier_qualifier_list ';'
    | specifier_qualifier_list struct_declarator_list ';'
    | static_assert_declaration
    ;


struct_declarator_list
    : struct_declarator
    | struct_declarator_list ',' struct_declarator
    ;

struct_declarator
    : ':' constant_expression
    | declarator ':' constant_expression
    | declarator
    ;


specifier_qualifier_list
    : type_specifier specifier_qualifier_list
    | type_specifier
    | type_qualifier specifier_qualifier_list
    | type_qualifier
    ;
 *
 *
 *
 *
 *使用的pcompi中的变量：
 *
 * std::map<std::string, std::map<std::string, class icode*> > m_struct_union_type;
    std::map<std::string, int> m_struct_or_union;///0--union. 1--struct
    std::string m_curr_struct_union_name;
 *
 *
 *
 *
 * *********************************************/

#include "ast_to_icode_struct_or_union_specifier.h"

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



int struct_get_define(comp_context* pcompi, std::string enum_name, class icode *result_ic)
{
    result_ic->is_signed = 0;
    result_ic->m_bit_width = pcompi->m_struct_union_bitwidth[enum_name];
    result_ic->is_struct = 1;
    result_ic->m_type_str = result_ic->m_type_str+" struct "+ enum_name;


    result_ic->m_struct_name = pcompi->m_struct_union_name[enum_name];
    result_ic->m_struct_type = pcompi->m_struct_union_type[enum_name];


    return 0;
}

int union_get_define(comp_context* pcompi, std::string enum_name, class icode *result_ic)
{
    result_ic->is_signed = 0;
    result_ic->m_bit_width = pcompi->m_struct_union_bitwidth[enum_name];
    result_ic->is_union = 1;
    result_ic->m_type_str = result_ic->m_type_str+" union "+ enum_name;

    result_ic->m_struct_name = pcompi->m_struct_union_name[enum_name];
    result_ic->m_struct_type = pcompi->m_struct_union_type[enum_name];

    return 0;
}


icode *  struct_define(class comp_context* pcompi, token_defs* enumerator_list,std::string enum_name, bool need_result_icode, class icode* result_ic)
{
    pcompi->m_curr_struct_union_name = enum_name;
    pcompi->m_struct_or_union[enum_name] = 1;

    //unsigned sym_size = pcompi->get_symbol_list_size();
    //pcompi->m_level++;
    pcompi->level_enter();



    pcompi->ast_to_icode(enumerator_list);
    //pcompi->m_struct_union;


    //pcompi->set_symbol_list_size(sym_size);
    //pcompi->m_level--;
    pcompi->level_leave();


    //enum定义完成后。将名称清空
    pcompi->m_curr_struct_union_name="";



    //计算总体的bitwidth
    std::vector<icode*> &tps = pcompi->m_struct_union_type[enum_name];
    pcompi->m_struct_union_bitwidth[enum_name] = 0;
    int &bitwidth_cnt = pcompi->m_struct_union_bitwidth[enum_name];
    for(unsigned i=0;i<tps.size();++i)
    {
        bitwidth_cnt += tps[i]->m_bit_width;
    }


    //类型定义完成后，修改result_ic为指定的类型
    struct_get_define(pcompi, enum_name, result_ic);

    return NULL;
}


icode *  union_define(class comp_context* pcompi, token_defs* enumerator_list,std::string enum_name, bool need_result_icode, class icode* result_ic)
{
    pcompi->m_curr_struct_union_name = enum_name;
    pcompi->m_struct_or_union[enum_name] = 0;//union

    //unsigned sym_size = pcompi->get_symbol_list_size();
    //pcompi->m_level++;
    pcompi->level_enter();



    pcompi->ast_to_icode(enumerator_list);
    //pcompi->m_struct_union;


    //pcompi->set_symbol_list_size(sym_size);
    //pcompi->m_level--;
    pcompi->level_leave();


    //enum定义完成后。将名称清空
    pcompi->m_curr_struct_union_name="";

    //计算总体的bitwidth
    std::vector<icode*> &tps = pcompi->m_struct_union_type[enum_name];
    pcompi->m_struct_union_bitwidth[enum_name] = 0;
    int &bitwidth_cnt = pcompi->m_struct_union_bitwidth[enum_name];
    for(unsigned i=0;i<tps.size();++i)
    {
        if(bitwidth_cnt < tps[i]->m_bit_width)
        {
            bitwidth_cnt = tps[i]->m_bit_width;
        }
    }


    //类型定义完成后，修改result_ic为指定的类型
    union_get_define(pcompi, enum_name, result_ic);

    return NULL;
}

class icode *  func_IAN_STRUCT_OR_UNION_SPECIFIER_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2201-struct_or_union_specifier->struct_or_union '{' struct_declaration_list '}'
    //parent:
    // type_specifier--> struct_or_union_specifier

    std::string key_su = tdefs->m_tk_elems[0]->val_str;

    //新生成一个enum。返回enum的名称icode
    token_defs * enumerator_list = tdefs->m_tk_elems[2];
    std::string enum_name = pcompi->get_temp_name("unname_"+key_su);

    if(key_su=="struct")
    {
        return struct_define(pcompi, enumerator_list, enum_name, need_result_icode, result_ic );
    }

    return union_define(pcompi, enumerator_list, enum_name, need_result_icode, result_ic );
}

class icode *  func_IAN_STRUCT_OR_UNION_SPECIFIER_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2202-struct_or_union_specifier->struct_or_union identifier '{' struct_declaration_list '}'
    //parent:
    // type_specifier--> struct_or_union_specifier

    std::string key_su = tdefs->m_tk_elems[0]->val_str;

    //新生成一个enum。返回enum的名称icode
    token_defs * enumerator_list = tdefs->m_tk_elems[3];
    std::string enum_name = tdefs->m_tk_elems[1]->val_str;

    if(key_su=="struct")
    {
        return struct_define(pcompi, enumerator_list, enum_name, need_result_icode, result_ic );
    }

    return union_define(pcompi, enumerator_list, enum_name, need_result_icode, result_ic );

}

class icode *  func_IAN_STRUCT_OR_UNION_SPECIFIER_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2203-struct_or_union_specifier->struct_or_union identifier
    //parent:
    // type_specifier--> struct_or_union_specifier

    std::string key_su = tdefs->m_tk_elems[0]->val_str;
    std::string enum_name = tdefs->m_tk_elems[1]->val_str;

    if(key_su=="struct")
    {
        struct_get_define(pcompi, enum_name, result_ic);
    }
    else
    {
        union_get_define(pcompi, enum_name, result_ic);
    }

    return NULL;

}




class icode *  func_IAN_STRUCT_OR_UNION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2301-struct_or_union->STRUCT
    //parent:
    // struct_or_union_specifier--> struct_or_union '{' struct_declaration_list '}'
    // struct_or_union_specifier--> struct_or_union identifier '{' struct_declaration_list '}'
    // struct_or_union_specifier--> struct_or_union identifier
    cerr<<"this should never be got\n";
    assert(0);
}

class icode *  func_IAN_STRUCT_OR_UNION_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2302-struct_or_union->UNION
    //parent:
    // struct_or_union_specifier--> struct_or_union '{' struct_declaration_list '}'
    // struct_or_union_specifier--> struct_or_union identifier '{' struct_declaration_list '}'
    // struct_or_union_specifier--> struct_or_union identifier
    cerr<<"this should never be got\n";
    assert(0);
}


class icode *func_token_STRUCT(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //STRUCT
    //parent:
    // struct_or_union--> STRUCT
    cerr<<"this should never be got\n";

    assert(0);
    return NULL;
}
class icode *func_token_UNION(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //UNION
    //parent:
    // struct_or_union--> UNION
    cerr<<"this should never be got\n";

    assert(0);
    return NULL;
}



class icode *  func_IAN_STRUCT_DECLARATION_LIST_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2401-struct_declaration_list->struct_declaration
    //parent:
    // struct_or_union_specifier--> struct_or_union '{' struct_declaration_list '}'
    // struct_or_union_specifier--> struct_or_union identifier '{' struct_declaration_list '}'
    // struct_declaration_list--> struct_declaration_list struct_declaration
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}

class icode *  func_IAN_STRUCT_DECLARATION_LIST_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2402-struct_declaration_list->struct_declaration_list struct_declaration
    //parent:
    // struct_or_union_specifier--> struct_or_union '{' struct_declaration_list '}'
    // struct_or_union_specifier--> struct_or_union identifier '{' struct_declaration_list '}'
    // struct_declaration_list--> struct_declaration_list struct_declaration

    pcompi->ast_to_icode(tdefs->m_tk_elems[0]);
    pcompi->ast_to_icode(tdefs->m_tk_elems[1]);

    return NULL;
}

class icode *  func_IAN_STRUCT_DECLARATION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2501-struct_declaration->specifier_qualifier_list ';'
    //parent:
    // struct_declaration_list--> struct_declaration
    // struct_declaration_list--> struct_declaration_list struct_declaration

    //此处定义个变量

    icode *type_ic = pcompi->new_icode();
    type_ic->m_type = ICODE_TYPE_DEF_VAR;

    pcompi->ast_to_icode(tdefs->m_tk_elems[0], 0, type_ic);

    std::string name = pcompi->get_temp_name("_unname_var");

    assert(pcompi->m_curr_struct_union_name.size()>0);



    type_ic->name = name;
    pcompi->m_struct_union_name[pcompi->m_curr_struct_union_name].push_back(name);
    pcompi->m_struct_union_type[pcompi->m_curr_struct_union_name].push_back(type_ic);

    return NULL;
}

class icode *  func_IAN_STRUCT_DECLARATION_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2502-struct_declaration->specifier_qualifier_list struct_declarator_list ';'
    //parent:
    // struct_declaration_list--> struct_declaration
    // struct_declaration_list--> struct_declaration_list struct_declaration

    assert(pcompi->m_curr_struct_union_name.size()>0);

    icode *type_ic = pcompi->new_icode();
    type_ic->m_type = ICODE_TYPE_DEF_VAR;

    pcompi->ast_to_icode(tdefs->m_tk_elems[0], 0, type_ic);

    ///有名字的变量，声明放入struct_declarator_list 中
    /// type_ic通过result_ic传递

    pcompi->ast_to_icode(tdefs->m_tk_elems[1],0, type_ic);

    return NULL;

}

class icode *  func_IAN_STRUCT_DECLARATION_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2503-struct_declaration->static_assert_declaration
    //parent:
    // struct_declaration_list--> struct_declaration
    // struct_declaration_list--> struct_declaration_list struct_declaration
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}



class icode *  func_IAN_STRUCT_DECLARATOR_LIST_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2701-struct_declarator_list->struct_declarator
    //parent:
    // struct_declaration--> specifier_qualifier_list struct_declarator_list ';'
    // struct_declarator_list--> struct_declarator_list ',' struct_declarator
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_STRUCT_DECLARATOR_LIST_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2702-struct_declarator_list->struct_declarator_list ',' struct_declarator
    //parent:
    // struct_declaration--> specifier_qualifier_list struct_declarator_list ';'
    // struct_declarator_list--> struct_declarator_list ',' struct_declarator

    pcompi->ast_to_icode(tdefs->m_tk_elems[0], 0, result_ic);
    pcompi->ast_to_icode(tdefs->m_tk_elems[2], 0, result_ic);

}
class icode *  func_IAN_STRUCT_DECLARATOR_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2801-struct_declarator->':' constant_expression
    //parent:
    // struct_declarator_list--> struct_declarator
    // struct_declarator_list--> struct_declarator_list ',' struct_declarator


    //此处不知道代码示例??
    assert(0);

}
class icode *  func_IAN_STRUCT_DECLARATOR_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2802-struct_declarator->declarator ':' constant_expression
    //parent:
    // struct_declarator_list--> struct_declarator
    // struct_declarator_list--> struct_declarator_list ',' struct_declarator

    token_defs* declarator = tdefs->m_tk_elems[0];
    token_defs* constant_expression = tdefs->m_tk_elems[2];


    /// TODO: 结构体的bit filed.  此处忽略了const_expression的值
    /// struct A
    /// {
    /// int a:1;
    /// int b:7;
    ///
    /// };
    //根据declarator的代码，将结果存入m_struct_union_name  m_struct_union_type
    icode *decl = pcompi->ast_to_icode(tdefs->m_tk_elems[0],1);
    icode *constant_expression_ic = pcompi->ast_to_icode(constant_expression, 1);
    assert(decl->result->m_type==ICODE_TYPE_SYMBOL_REF);

    std::string name = decl->result->name;
    if(decl->result->result!=NULL)
    {
        //检查是否重复定义
        if(decl->result->result->m_level==pcompi->get_level())
        {
            cerr<<"ERROR: symbol redefined!. "<< decl->result->name<<"\n";
            return NULL;
        }
    }

    icode * type_ic = pcompi->new_icode( *result_ic);
    type_ic->name = name;
    type_ic->is_signed = 0;//此处因为是bit field。所以把符号去掉
    type_ic->m_bit_width = constant_expression_ic->result->num;
    pcompi->m_struct_union_name[pcompi->m_curr_struct_union_name].push_back(name);
    pcompi->m_struct_union_type[pcompi->m_curr_struct_union_name].push_back(type_ic);

    pcompi->add_symbol(name, type_ic);

    return NULL;
}
class icode *  func_IAN_STRUCT_DECLARATOR_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2803-struct_declarator->declarator
    //parent:
    // struct_declarator_list--> struct_declarator
    // struct_declarator_list--> struct_declarator_list ',' struct_declarator



    //根据declarator的代码，将结果存入m_struct_union_name  m_struct_union_type
    icode *decl = pcompi->ast_to_icode(tdefs,1);

    assert(decl->result->m_type==ICODE_TYPE_SYMBOL_REF);

    std::string name = decl->result->name;
    if(decl->result->result!=NULL)
    {
        //检查是否重复定义
        if(decl->result->result->m_level==pcompi->get_level())
        {
            cerr<<"ERROR: symbol redefined!. "<< decl->result->name<<"\n";
            return NULL;
        }
    }

    icode * type_ic = pcompi->new_icode( *result_ic);
    type_ic->name = name;
    pcompi->m_struct_union_name[pcompi->m_curr_struct_union_name].push_back(name);
    pcompi->m_struct_union_type[pcompi->m_curr_struct_union_name].push_back(type_ic);

    pcompi->add_symbol(name, type_ic);

    return NULL;
}


class icode *  func_IAN_SPECIFIER_QUALIFIER_LIST_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2601-specifier_qualifier_list->type_specifier specifier_qualifier_list
    //parent:
    // struct_declaration--> specifier_qualifier_list ';'
    // struct_declaration--> specifier_qualifier_list struct_declarator_list ';'
    // specifier_qualifier_list--> type_specifier specifier_qualifier_list
    // specifier_qualifier_list--> type_qualifier specifier_qualifier_list
    // type_name--> specifier_qualifier_list abstract_declarator
    // type_name--> specifier_qualifier_list

    pcompi->ast_to_icode(tdefs->m_tk_elems[0],0, result_ic);
    pcompi->ast_to_icode(tdefs->m_tk_elems[1],0, result_ic);



    return NULL;
}

class icode *  func_IAN_SPECIFIER_QUALIFIER_LIST_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2602-specifier_qualifier_list->type_specifier
    //parent:
    // struct_declaration--> specifier_qualifier_list ';'
    // struct_declaration--> specifier_qualifier_list struct_declarator_list ';'
    // specifier_qualifier_list--> type_specifier specifier_qualifier_list
    // specifier_qualifier_list--> type_qualifier specifier_qualifier_list
    // type_name--> specifier_qualifier_list abstract_declarator
    // type_name--> specifier_qualifier_list
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_SPECIFIER_QUALIFIER_LIST_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2603-specifier_qualifier_list->type_qualifier specifier_qualifier_list
    //parent:
    // struct_declaration--> specifier_qualifier_list ';'
    // struct_declaration--> specifier_qualifier_list struct_declarator_list ';'
    // specifier_qualifier_list--> type_specifier specifier_qualifier_list
    // specifier_qualifier_list--> type_qualifier specifier_qualifier_list
    // type_name--> specifier_qualifier_list abstract_declarator
    // type_name--> specifier_qualifier_list
    pcompi->ast_to_icode(tdefs->m_tk_elems[0],0, result_ic);
    pcompi->ast_to_icode(tdefs->m_tk_elems[1],0, result_ic);

    return NULL;
}

class icode *  func_IAN_SPECIFIER_QUALIFIER_LIST_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2604-specifier_qualifier_list->type_qualifier
    //parent:
    // struct_declaration--> specifier_qualifier_list ';'
    // struct_declaration--> specifier_qualifier_list struct_declarator_list ';'
    // specifier_qualifier_list--> type_specifier specifier_qualifier_list
    // specifier_qualifier_list--> type_qualifier specifier_qualifier_list
    // type_name--> specifier_qualifier_list abstract_declarator
    // type_name--> specifier_qualifier_list
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}






}//namespace end




