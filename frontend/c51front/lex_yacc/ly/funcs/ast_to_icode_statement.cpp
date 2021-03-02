/***************
 *

statement
        : labeled_statement
        | compound_statement
        | expression_statement
        | selection_statement
        | iteration_statement
        | jump_statement
        ;


compound_statement
    : '{' '}'
    | '{'  block_item_list '}'
    ;

block_item_list
    : block_item
    | block_item_list block_item
    ;

block_item
    : declaration
    | statement
    ;

expression_statement
    : ';'
    | expression ';'
    ;
 * ***/

#include "ast_to_icode_statement.h"


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




class icode *  func_IAN_STATEMENT_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4601-statement->labeled_statement
    //parent:
    // labeled_statement--> identifier ':' statement
    // labeled_statement--> CASE constant_expression ':' statement
    // labeled_statement--> DEFAULT ':' statement
    // block_item--> statement
    // selection_statement--> IF '(' expression ')' statement ELSE statement
    // selection_statement--> IF '(' expression ')' statement ELSE statement
    // selection_statement--> IF '(' expression ')' statement
    // selection_statement--> SWITCH '(' expression ')' statement
    // iteration_statement--> WHILE '(' expression ')' statement
    // iteration_statement--> DO statement WHILE '(' expression ')' ';'
    // iteration_statement--> FOR '(' expression_statement expression_statement ')' statement
    // iteration_statement--> FOR '(' expression_statement expression_statement expression ')' statement
    // iteration_statement--> FOR '(' declaration expression_statement ')' statement
    // iteration_statement--> FOR '(' declaration expression_statement expression ')' statement
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}

class icode *  func_IAN_STATEMENT_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4602-statement->compound_statement
    //parent:
    // labeled_statement--> identifier ':' statement
    // labeled_statement--> CASE constant_expression ':' statement
    // labeled_statement--> DEFAULT ':' statement
    // block_item--> statement
    // selection_statement--> IF '(' expression ')' statement ELSE statement
    // selection_statement--> IF '(' expression ')' statement ELSE statement
    // selection_statement--> IF '(' expression ')' statement
    // selection_statement--> SWITCH '(' expression ')' statement
    // iteration_statement--> WHILE '(' expression ')' statement
    // iteration_statement--> DO statement WHILE '(' expression ')' ';'
    // iteration_statement--> FOR '(' expression_statement expression_statement ')' statement
    // iteration_statement--> FOR '(' expression_statement expression_statement expression ')' statement
    // iteration_statement--> FOR '(' declaration expression_statement ')' statement
    // iteration_statement--> FOR '(' declaration expression_statement expression ')' statement
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}

class icode *  func_IAN_STATEMENT_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4603-statement->expression_statement
    //parent:
    // labeled_statement--> identifier ':' statement
    // labeled_statement--> CASE constant_expression ':' statement
    // labeled_statement--> DEFAULT ':' statement
    // block_item--> statement
    // selection_statement--> IF '(' expression ')' statement ELSE statement
    // selection_statement--> IF '(' expression ')' statement ELSE statement
    // selection_statement--> IF '(' expression ')' statement
    // selection_statement--> SWITCH '(' expression ')' statement
    // iteration_statement--> WHILE '(' expression ')' statement
    // iteration_statement--> DO statement WHILE '(' expression ')' ';'
    // iteration_statement--> FOR '(' expression_statement expression_statement ')' statement
    // iteration_statement--> FOR '(' expression_statement expression_statement expression ')' statement
    // iteration_statement--> FOR '(' declaration expression_statement ')' statement
    // iteration_statement--> FOR '(' declaration expression_statement expression ')' statement
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}

class icode *  func_IAN_STATEMENT_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4604-statement->selection_statement
    //parent:
    // labeled_statement--> identifier ':' statement
    // labeled_statement--> CASE constant_expression ':' statement
    // labeled_statement--> DEFAULT ':' statement
    // block_item--> statement
    // selection_statement--> IF '(' expression ')' statement ELSE statement
    // selection_statement--> IF '(' expression ')' statement ELSE statement
    // selection_statement--> IF '(' expression ')' statement
    // selection_statement--> SWITCH '(' expression ')' statement
    // iteration_statement--> WHILE '(' expression ')' statement
    // iteration_statement--> DO statement WHILE '(' expression ')' ';'
    // iteration_statement--> FOR '(' expression_statement expression_statement ')' statement
    // iteration_statement--> FOR '(' expression_statement expression_statement expression ')' statement
    // iteration_statement--> FOR '(' declaration expression_statement ')' statement
    // iteration_statement--> FOR '(' declaration expression_statement expression ')' statement
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}

class icode *  func_IAN_STATEMENT_5(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4605-statement->iteration_statement
    //parent:
    // labeled_statement--> identifier ':' statement
    // labeled_statement--> CASE constant_expression ':' statement
    // labeled_statement--> DEFAULT ':' statement
    // block_item--> statement
    // selection_statement--> IF '(' expression ')' statement ELSE statement
    // selection_statement--> IF '(' expression ')' statement ELSE statement
    // selection_statement--> IF '(' expression ')' statement
    // selection_statement--> SWITCH '(' expression ')' statement
    // iteration_statement--> WHILE '(' expression ')' statement
    // iteration_statement--> DO statement WHILE '(' expression ')' ';'
    // iteration_statement--> FOR '(' expression_statement expression_statement ')' statement
    // iteration_statement--> FOR '(' expression_statement expression_statement expression ')' statement
    // iteration_statement--> FOR '(' declaration expression_statement ')' statement
    // iteration_statement--> FOR '(' declaration expression_statement expression ')' statement
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}

class icode *  func_IAN_STATEMENT_6(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4606-statement->jump_statement
    //parent:
    // labeled_statement--> identifier ':' statement
    // labeled_statement--> CASE constant_expression ':' statement
    // labeled_statement--> DEFAULT ':' statement
    // block_item--> statement
    // selection_statement--> IF '(' expression ')' statement ELSE statement
    // selection_statement--> IF '(' expression ')' statement ELSE statement
    // selection_statement--> IF '(' expression ')' statement
    // selection_statement--> SWITCH '(' expression ')' statement
    // iteration_statement--> WHILE '(' expression ')' statement
    // iteration_statement--> DO statement WHILE '(' expression ')' ';'
    // iteration_statement--> FOR '(' expression_statement expression_statement ')' statement
    // iteration_statement--> FOR '(' expression_statement expression_statement expression ')' statement
    // iteration_statement--> FOR '(' declaration expression_statement ')' statement
    // iteration_statement--> FOR '(' declaration expression_statement expression ')' statement
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}


class icode *  func_IAN_COMPOUND_STATEMENT_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4801-compound_statement->'{' '}'
    //parent:
    // statement--> compound_statement
    // function_definition--> declaration_specifiers declarator declaration_list compound_statement
    // function_definition--> declaration_specifiers declarator compound_statement
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_SCOPE;

    //no nothing. just return a(empty block);

    return a;
}

class icode *  func_IAN_COMPOUND_STATEMENT_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4802-compound_statement->'{' block_item_list '}'
    //parent:
    // statement--> compound_statement
    // function_definition--> declaration_specifiers declarator declaration_list compound_statement
    // function_definition--> declaration_specifiers declarator compound_statement
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_SCOPE;

    //pcompi->m_level++;
    //unsigned  sym_size = pcompi->get_symbol_list_size();
    pcompi->level_enter();

    a->merge_icode(pcompi->ast_to_icode(tdefs->m_tk_elems[1]));

    //pcompi->set_symbol_list_size(sym_size);
    //pcompi->m_level--;
    pcompi->level_leave();
    return a;
}

class icode *  func_IAN_BLOCK_ITEM_LIST_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4901-block_item_list->block_item
    //parent:
    // compound_statement--> '{' block_item_list '}'
    // block_item_list--> block_item_list block_item
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}

class icode *  func_IAN_BLOCK_ITEM_LIST_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4902-block_item_list->block_item_list block_item
    //parent:
    // compound_statement--> '{' block_item_list '}'
    // block_item_list--> block_item_list block_item

    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    icode *b = pcompi->ast_to_icode(tdefs->m_tk_elems[0]);
    a->merge_icode_raw(b);
    b = pcompi->ast_to_icode(tdefs->m_tk_elems[1]);
    a->merge_icode_raw(b);

    return a;
}

class icode *  func_IAN_BLOCK_ITEM_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4a01-block_item->declaration
    //parent:
    // block_item_list--> block_item
    // block_item_list--> block_item_list block_item
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}

class icode *  func_IAN_BLOCK_ITEM_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4a02-block_item->statement
    //parent:
    // block_item_list--> block_item
    // block_item_list--> block_item_list block_item
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}

class icode *  func_IAN_EXPRESSION_STATEMENT_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4b01-expression_statement->';'
    //parent:
    // statement--> expression_statement
    // iteration_statement--> FOR '(' expression_statement expression_statement ')' statement
    // iteration_statement--> FOR '(' expression_statement expression_statement ')' statement
    // iteration_statement--> FOR '(' expression_statement expression_statement expression ')' statement
    // iteration_statement--> FOR '(' expression_statement expression_statement expression ')' statement
    // iteration_statement--> FOR '(' declaration expression_statement ')' statement
    // iteration_statement--> FOR '(' declaration expression_statement expression ')' statement
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    return a;
}

class icode *  func_IAN_EXPRESSION_STATEMENT_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4b02-expression_statement->expression ';'
    //parent:
    // statement--> expression_statement
    // iteration_statement--> FOR '(' expression_statement expression_statement ')' statement
    // iteration_statement--> FOR '(' expression_statement expression_statement ')' statement
    // iteration_statement--> FOR '(' expression_statement expression_statement expression ')' statement
    // iteration_statement--> FOR '(' expression_statement expression_statement expression ')' statement
    // iteration_statement--> FOR '(' declaration expression_statement ')' statement
    // iteration_statement--> FOR '(' declaration expression_statement expression ')' statement


    return pcompi->ast_to_icode(tdefs->m_tk_elems[0], need_result_icode, result_ic);
}

}//namespace end


