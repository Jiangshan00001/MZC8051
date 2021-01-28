/***************************
 *
 *
 *
 *
 *
 * 实现情况： 所有跳转函数均已实现
 *  ICODE_TYPE_FUNC_RETURN -需要根据是否是中断函数，进一步处理？
 *
 * 输入：tdefs
 * 输出：通过block a来返回代码
 * need_result result_ic 均未使用
 *
 *
 *
labeled_statement
        : identifier ':' statement
        | CASE constant_expression ':' statement
        | DEFAULT ':' statement
        ;

selection_statement
    : IF '(' expression ')' statement ELSE statement
    | IF '(' expression ')' statement
    | SWITCH '(' expression ')' statement
    ;

iteration_statement
    : WHILE '(' expression ')' statement
    | DO statement WHILE '(' expression ')' ';'
    | FOR '(' expression_statement expression_statement ')' statement
    | FOR '(' expression_statement expression_statement expression ')' statement
    | FOR '(' declaration expression_statement ')' statement
    | FOR '(' declaration expression_statement expression ')' statement
    ;


jump_statement
        : GOTO identifier ';'
        | CONTINUE ';'
        | BREAK ';'
        | RETURN ';'
        | RETURN expression ';'
        ;

***************************************************/

#include "ast_to_icode_jump.h"


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



namespace NS_C2IR{




class icode *  func_IAN_LABELED_STATEMENT_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4701-labeled_statement->identifier ':' statement
    //parent:
    // statement--> labeled_statement
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    std::string label_name = pcompi->get_label_name(tdefs->m_tk_elems[0]->name);
    sym *s = pcompi->find_symbol(label_name);
    if(s!=NULL)
    {


        //已经存在，则不能创建新的
        if(std::find(pcompi->m_goto_label_unset.begin(), pcompi->m_goto_label_unset.end(),label_name )!=pcompi->m_goto_label_unset.end())
        {
            a->merge_icode(s->def_icode);
            pcompi->m_goto_label_unset.erase(std::find(pcompi->m_goto_label_unset.begin(), pcompi->m_goto_label_unset.end(),label_name ));
        }
        else
        {
            //标签已经存在，并且已经使用，说明标签重复
            cerr<<"ERROR: label redefined!! label_name="<< label_name<<"\n";
            assert(0);
        }
    }
    else
    {
        //label不存在创建新的
        icode *n = pcompi->new_icode(ICODE_TYPE_LABELED_BLOCK);
        n->name = label_name;
        //pcompi->m_goto_label[label_name] = n;
        pcompi->add_symbol(label_name, n);
        a->merge_icode(n);
    }

    icode * n = pcompi->ast_to_icode( tdefs->m_tk_elems[2]);
    a->merge_icode(n);

    return a;
}
class icode *  func_IAN_LABELED_STATEMENT_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4702-labeled_statement->CASE constant_expression ':' statement
    //parent:
    // statement--> labeled_statement
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    token_defs *const_expr = tdefs->m_tk_elems[1];
    token_defs *statem = tdefs->m_tk_elems[3];

    icode * const_ic = pcompi->ast_to_icode(const_expr, 1);

    icode * lbc = pcompi->new_icode(ICODE_TYPE_LABELED_BLOCK);

    pcompi->m_case_label[const_ic->result->num] = lbc;
    pcompi->m_case_int_vec.push_back(const_ic->result->num);

    icode * statem_ic = pcompi->ast_to_icode(statem);

    a->merge_icode(const_ic);
    a->merge_icode(lbc);
    a->merge_icode(statem_ic);

    return a;
}
class icode *  func_IAN_LABELED_STATEMENT_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4703-labeled_statement->DEFAULT ':' statement
    //parent:
    // statement--> labeled_statement
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    pcompi->m_default_label = pcompi->new_icode(ICODE_TYPE_LABELED_BLOCK);
    token_defs *statem = tdefs->m_tk_elems[2];
    icode * statem_ic = pcompi->ast_to_icode(statem);

    a->merge_icode(pcompi->m_default_label);
    a->merge_icode(statem_ic);

    return a;
}

class icode *  func_IAN_SELECTION_STATEMENT_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4c01-selection_statement->IF '(' expression ')' statement ELSE statement
    //parent:
    // statement--> selection_statement
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    token_defs *expr = tdefs->m_tk_elems[2];
    token_defs *statem1 = tdefs->m_tk_elems[4];
    token_defs *statem2 = tdefs->m_tk_elems[6];

    icode * expr_ic = pcompi->ast_to_icode(expr, 1);

    icode *icb1=pcompi->new_icode(ICODE_TYPE_LABELED_BLOCK);

    icode *icb2 = pcompi->new_icode(ICODE_TYPE_LABELED_BLOCK);

    icode * jz_code = pcompi->new_icode();
    icode * jmp_code = pcompi->new_jmp_icode(icb2);

    jz_code->m_type = ICODE_TYPE_EXP_OP;
    jz_code->name = "JZ";//零跳转指令

    ///要判断的值
    jz_code->left = expr_ic->result;

    jz_code->result = pcompi->new_icode();
    jz_code->result->m_type = ICODE_TYPE_LABELED_BLOCK_START_REF;
    jz_code->result->result = icb1;



    icode * statem1_ic = pcompi->ast_to_icode(statem1);
    icode * statem2_ic = pcompi->ast_to_icode(statem2);

    /// expression
    ///
    /// jz block1-start
    ///
    /// statement1
    /// jmp block2-start
    ///
    /// block1-start
    ///
    /// statement2
    ///
    /// block2-start

    a->merge_icode(expr_ic);
    a->merge_icode(jz_code);
    a->merge_icode(statem1_ic);
    a->merge_icode(jmp_code);
    a->merge_icode(icb1);
    a->merge_icode(statem2_ic);
    a->merge_icode(icb2);

    return a;
}
class icode *  func_IAN_SELECTION_STATEMENT_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4c02-selection_statement->IF '(' expression ')' statement
    //parent:
    // statement--> selection_statement
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    token_defs *expr = tdefs->m_tk_elems[2];
    token_defs *statem1 = tdefs->m_tk_elems[4];

    icode * expr_ic = pcompi->ast_to_icode(expr, 1);

    icode *icb1=pcompi->new_icode(ICODE_TYPE_LABELED_BLOCK);

    icode * jz_code = pcompi->new_icode();

    jz_code->m_type = ICODE_TYPE_EXP_OP;
    jz_code->name = "JZ";//零跳转指令

    ///要判断的值
    jz_code->left = expr_ic->result;

    jz_code->result = pcompi->new_icode();
    jz_code->result->m_type = ICODE_TYPE_LABELED_BLOCK_START_REF;
    jz_code->result->result = icb1;



    icode * statem1_ic = pcompi->ast_to_icode(statem1);

    /// expression
    ///
    /// jz block1-start
    ///
    /// statement1
    ///
    /// block1-start

    a->merge_icode(expr_ic);
    a->merge_icode(jz_code);
    a->merge_icode(statem1_ic);
    a->merge_icode(icb1);

    return a;
}
class icode *  func_IAN_SELECTION_STATEMENT_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4c03-selection_statement->SWITCH '(' expression ')' statement
    //parent:
    // statement--> selection_statement
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    token_defs* expr = tdefs->m_tk_elems[2];
    token_defs* statement = tdefs->m_tk_elems[4];

    icode * expr_ic = pcompi->ast_to_icode(expr, 1);
    icode *icb1 = pcompi->new_icode(ICODE_TYPE_LABELED_BLOCK);
    icode *icb2 = pcompi->new_icode(ICODE_TYPE_LABELED_BLOCK);


    pcompi->m_break_label_dst = pcompi->new_jmp_icode(icb2);
    pcompi->m_case_label.clear();
    pcompi->m_case_int_vec.clear();

    pcompi->m_default_label = NULL;


    //此处设置case break
    icode * statement_ic = pcompi->ast_to_icode(statement);
    pcompi->m_break_label_dst = NULL;

    icode *jmp_code1 = pcompi->new_jmp_icode(icb1);
    icode *jmp_code2 = pcompi->new_jmp_icode(icb2);

    /// expr
    ///
    ///
    /// jmp block1-start
    ///
    /// statement
    ///
    /// jmp block2-start
    ///
    /// block1-start
    ///
    /// if(expr==case1) goto state_case1_label
    /// if((expr==case1) goto state_case1_label
    ///
    /// block2-start
    ///

    a->merge_icode(expr_ic);
    a->merge_icode(jmp_code1);
    a->merge_icode(statement_ic);
    a->merge_icode(jmp_code2);
    a->merge_icode(icb1);

#if 1
    icode *case_ret= pcompi->new_temp_var();
    a->merge_icode(case_ret);

    for(unsigned i=0;i<pcompi->m_case_int_vec.size();++i)
    {
        //-----------
        case_ret->m_bit_width = 8;
        icode *case_const = pcompi->new_icode(ICODE_TYPE_I_CONST);
        case_const->num = pcompi->m_case_int_vec[i];
        case_const->m_bit_width = 16;

        //-----------
        icode *opreq=pcompi->new_icode(ICODE_TYPE_EXP_OP);
        opreq->name="==";
        opreq->left = expr_ic->result;
        opreq->right =case_const;
        opreq->result = pcompi->new_ref_icode(case_ret);

        //-----------
        a->merge_icode(opreq);
        //-----------

        icode *jnz_code=pcompi->new_jnz_icode(pcompi->new_ref_icode(case_ret), pcompi->m_case_label[case_const->num],"JNZ");//
        //-----------
        a->merge_icode(jnz_code);
    }



    icode *jmp_code=NULL;
    if(pcompi->m_default_label)
    {
        jmp_code = pcompi->new_jmp_icode(pcompi->m_default_label);
    }
    else
    {
        jmp_code = pcompi->new_jmp_icode(icb2);
    }

    //-----------
    a->merge_icode(jmp_code);

    a->merge_icode(pcompi->release_tmp_if_need(case_ret));


#endif
    pcompi->m_default_label = NULL;
    pcompi->m_case_int_vec.clear();

    a->merge_icode(icb2);

    return a;
}
class icode *  func_IAN_ITERATION_STATEMENT_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4d01-iteration_statement->WHILE '(' expression ')' statement
    //parent:
    // statement--> iteration_statement
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    /// block1-start
    /// block1-end
    /// expression
    ///
    /// jz block2-end
    ///
    /// statement
    ///
    /// jmp block1-start
    ///
    /// block2-start
    /// block2-end

    token_defs *expr = tdefs->m_tk_elems[2];
    token_defs *statem = tdefs->m_tk_elems[4];

    icode * expr_ic = pcompi->ast_to_icode(expr, 1);

    icode *icb1=pcompi->new_icode(ICODE_TYPE_LABELED_BLOCK);

    icode *icb2 = pcompi->new_icode(ICODE_TYPE_LABELED_BLOCK);
    icode * jz_code = pcompi->new_icode();
    icode * jmp_code = pcompi->new_jmp_icode(icb1);

    jz_code->m_type = ICODE_TYPE_EXP_OP;
    jz_code->name = "JZ";//零跳转指令

    ///要判断的值
    jz_code->left = expr_ic->result;


    //零，跳转到icb2的起始位置
    jz_code->result = pcompi->new_icode();
    jz_code->result->m_type = ICODE_TYPE_LABELED_BLOCK_START_REF;
    jz_code->result->result = icb2;



    ///在解析statem之前，需要 设置这2个label dst
    pcompi->m_continue_label_dst = pcompi->new_jmp_icode(icb1);
    pcompi->m_break_label_dst = pcompi->new_jmp_icode(icb2);

    icode * statem_ic = pcompi->ast_to_icode(statem);
    pcompi->m_continue_label_dst = NULL;
    pcompi->m_break_label_dst = NULL;


    a->merge_icode(icb1);
    a->merge_icode(expr_ic);
    a->merge_icode(jz_code);
    a->merge_icode(statem_ic);
    a->merge_icode(jmp_code);
    a->merge_icode(icb2);

    return a;
}
class icode *  func_IAN_ITERATION_STATEMENT_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4d02-iteration_statement->DO statement WHILE '(' expression ')' ';'
    //parent:
    // statement--> iteration_statement
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    /// block1-start
    /// block1-end
    /// statement
    ///

    /// expression
    /// jnz block1-start
    /// block2-start
    /// block2-end


    token_defs *statement = tdefs->m_tk_elems[1];
    token_defs *expr = tdefs->m_tk_elems[4];


    icode * expr_ic = pcompi->ast_to_icode(expr, 1);

    icode *icb1=pcompi->new_icode(ICODE_TYPE_LABELED_BLOCK);

    icode *icb2=pcompi->new_icode(ICODE_TYPE_LABELED_BLOCK);

    icode * jmp_code = pcompi->new_jnz_icode(expr_ic->result, icb1,"JNZ", ICODE_TYPE_LABELED_BLOCK_START_REF); //pcompi->new_icode();


    ///在解析statem之前，需要 设置这2个label dst
    pcompi->m_continue_label_dst = pcompi->new_jmp_icode(icb1);
    pcompi->m_break_label_dst = pcompi->new_jmp_icode(icb2);

    icode * state_ic = pcompi->ast_to_icode(statement);
    pcompi->m_continue_label_dst = NULL;
    pcompi->m_break_label_dst = NULL;

    //----------------------
    a->merge_icode(icb1);
    a->merge_icode(state_ic);
    a->merge_icode(expr_ic);
    a->merge_icode(jmp_code);
    a->merge_icode(pcompi->release_tmp_if_need(expr_ic->result));
    a->merge_icode(icb2);
    //----------------------

    return a;
}
class icode *  func_IAN_ITERATION_STATEMENT_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4d03-iteration_statement->FOR '(' expression_statement expression_statement ')' statement
    //parent:
    // statement--> iteration_statement
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_SCOPE;

    token_defs *exp1=tdefs->m_tk_elems[2];
    token_defs *exp2=tdefs->m_tk_elems[3];
    token_defs *statem=tdefs->m_tk_elems[5];

    ///
    /// exp1
    ///
    ///
    ///
    /// block1-start
    /// block1-end
    /// exp2
    ///
    /// jz exp2->result block2-start
    ///
    /// statem
    /// jmp block1-start
    ///
    /// block2-start
    /// block2-end
    ///
    ///
    icode * exp1_ic = pcompi->ast_to_icode(exp1);
    icode * exp2_ic = pcompi->ast_to_icode(exp2, 1);

    icode *icb1=pcompi->new_icode(ICODE_TYPE_LABELED_BLOCK);

    icode *icb2 = pcompi->new_icode(ICODE_TYPE_LABELED_BLOCK);


    icode * jz_code = pcompi->new_icode();
    jz_code->m_type = ICODE_TYPE_EXP_OP;
    jz_code->name = "JZ";//零跳转指令
    ///要判断的值
    jz_code->left = exp2_ic->result;

    //零，跳转到icb2的起始位置
    jz_code->result = pcompi->new_icode(ICODE_TYPE_LABELED_BLOCK_START_REF);
    jz_code->result->result = icb2;


    ///在解析statem之前，需要 设置这2个label dst
    pcompi->m_continue_label_dst = pcompi->new_jmp_icode(icb1);
    pcompi->m_break_label_dst = pcompi->new_jmp_icode(icb2);

    icode * statem_ic = pcompi->ast_to_icode(statem);
    pcompi->m_continue_label_dst = NULL;
    pcompi->m_break_label_dst = NULL;


    icode *jmp_code = pcompi->new_jmp_icode(icb1);

    a->merge_icode(exp1_ic);
    a->merge_icode(icb1);
    a->merge_icode(exp2_ic);
    a->merge_icode(jz_code);
    a->merge_icode(statem_ic);
    a->merge_icode(jmp_code);
    a->merge_icode(icb2);
    return a;
}
class icode *  func_IAN_ITERATION_STATEMENT_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4d04-iteration_statement->FOR '(' expression_statement expression_statement expression ')' statement
    //parent:
    // statement--> iteration_statement
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_SCOPE;

    /// exp1
    ///
    /// block1-start
    /// block1-end
    /// exp2
    /// jz exp2->result block2-start
    /// statem
    /// exp3
    /// jmp block1-start
    ///
    /// block2-start
    /// block2-end
    ///
    ///


    token_defs *exp1=tdefs->m_tk_elems[2];
    token_defs *exp2=tdefs->m_tk_elems[3];
    token_defs *exp3=tdefs->m_tk_elems[4];
    token_defs *statem=tdefs->m_tk_elems[6];

    icode *exp1_ic = pcompi->ast_to_icode(exp1);
    icode *exp2_ic = pcompi->ast_to_icode(exp2, 1);
    icode *exp3_ic = pcompi->ast_to_icode(exp3);


    icode *icb1 = pcompi->new_icode(ICODE_TYPE_LABELED_BLOCK);
    icode *icb2 = pcompi->new_icode(ICODE_TYPE_LABELED_BLOCK);

    icode * jz_code = pcompi->new_icode();
    jz_code->m_type = ICODE_TYPE_EXP_OP;
    jz_code->name = "JZ";//零跳转指令


    ///要判断的值
    jz_code->left = exp2_ic->result;

    //零，跳转到icb2的起始位置
    jz_code->result = pcompi->new_icode();
    jz_code->result->m_type = ICODE_TYPE_LABELED_BLOCK_START_REF;
    jz_code->result->result = icb2;


    icode *jmp_code = pcompi->new_jmp_icode(icb1);


    ///在解析statem之前，需要 设置这2个label dst
    pcompi->m_continue_label_dst = pcompi->new_jmp_icode(icb1);
    pcompi->m_break_label_dst = pcompi->new_jmp_icode(icb2);
    icode *statem_ic = pcompi->ast_to_icode(statem);
    pcompi->m_continue_label_dst = NULL;
    pcompi->m_break_label_dst = NULL;


    a->merge_icode(exp1_ic);
    a->merge_icode(icb1);
    a->merge_icode(exp2_ic);
    a->merge_icode(jz_code);
    a->merge_icode(statem_ic);
    a->merge_icode(exp3_ic);
    a->merge_icode(jmp_code);
    a->merge_icode(icb2);
    return a;
}
class icode *  func_IAN_ITERATION_STATEMENT_5(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4d05-iteration_statement->FOR '(' declaration expression_statement ')' statement
    //parent:
    // statement--> iteration_statement
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_SCOPE;

    //pcompi->m_level++;
    //unsigned  sym_size = pcompi->get_symbol_list_size();
    pcompi->level_enter();


    token_defs *exp1=tdefs->m_tk_elems[2];
    token_defs *exp2=tdefs->m_tk_elems[3];
    token_defs *statem=tdefs->m_tk_elems[5];

    ///
    /// exp1
    ///
    ///
    ///
    /// block1-start
    /// block1-end
    /// exp2
    ///
    /// jz exp2->result block2-start
    ///
    /// statem
    /// jmp block1-start
    ///
    /// block2-start
    /// block2-end
    ///
    ///
    icode * exp1_ic = pcompi->ast_to_icode(exp1);
    icode * exp2_ic = pcompi->ast_to_icode(exp2, 1);

    icode *icb1=pcompi->new_icode(ICODE_TYPE_LABELED_BLOCK);

    icode *icb2 = pcompi->new_icode(ICODE_TYPE_LABELED_BLOCK);



    icode * jz_code = pcompi->new_icode();
    jz_code->m_type = ICODE_TYPE_EXP_OP;
    jz_code->name = "JZ";//零跳转指令
    ///要判断的值
    jz_code->left = exp2_ic->result;

    //零，跳转到icb2的起始位置
    jz_code->result = pcompi->new_icode();
    jz_code->result->m_type = ICODE_TYPE_LABELED_BLOCK_START_REF;
    jz_code->result->result = icb2;


    ///在解析statem之前，需要 设置这2个label dst
    pcompi->m_continue_label_dst = pcompi->new_jmp_icode(icb1);
    pcompi->m_break_label_dst = pcompi->new_jmp_icode(icb2);

    icode * statem_ic = pcompi->ast_to_icode(statem);
    pcompi->m_continue_label_dst = NULL;
    pcompi->m_break_label_dst = NULL;


    icode *jmp_code = pcompi->new_jmp_icode(icb1);

    a->merge_icode(exp1_ic);
    a->merge_icode(icb1);
    a->merge_icode(exp2_ic);
    a->merge_icode(jz_code);
    a->merge_icode(statem_ic);
    a->merge_icode(jmp_code);
    a->merge_icode(icb2);



    //pcompi->set_symbol_list_size(sym_size);
    //pcompi->m_level--;
    pcompi->level_leave();
    return a;
}
class icode *  func_IAN_ITERATION_STATEMENT_6(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4d06-iteration_statement->FOR '(' declaration expression_statement expression ')' statement
    //parent:
    // statement--> iteration_statement
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_SCOPE;

    //pcompi->m_level++;
    //unsigned  sym_size = pcompi->get_symbol_list_size();
    pcompi->level_enter();

    /// exp1
    ///
    /// block1-start
    /// block1-end
    /// exp2
    /// jz exp2->result block2-start
    /// statem
    /// exp3
    /// jmp block1-start
    ///
    /// block2-start
    /// block2-end
    ///
    ///


    token_defs *exp1=tdefs->m_tk_elems[2];
    token_defs *exp2=tdefs->m_tk_elems[3];
    token_defs *exp3=tdefs->m_tk_elems[4];
    token_defs *statem=tdefs->m_tk_elems[6];

    icode *exp1_ic = pcompi->ast_to_icode(exp1);
    icode *exp2_ic = pcompi->ast_to_icode(exp2, 1);
    icode *exp3_ic = pcompi->ast_to_icode(exp3);


    icode *icb1 = pcompi->new_icode(ICODE_TYPE_LABELED_BLOCK);
    icode *icb2 = pcompi->new_icode(ICODE_TYPE_LABELED_BLOCK);

    icode * jz_code = pcompi->new_icode();
    jz_code->m_type = ICODE_TYPE_EXP_OP;
    jz_code->name = "JZ";//零跳转指令


    ///要判断的值
    jz_code->left = exp2_ic->result;

    //零，跳转到icb2的起始位置
    jz_code->result = pcompi->new_icode();
    jz_code->result->m_type = ICODE_TYPE_LABELED_BLOCK_START_REF;
    jz_code->result->result = icb2;


    icode *jmp_code = pcompi->new_jmp_icode(icb1);


    ///在解析statem之前，需要 设置这2个label dst
    pcompi->m_continue_label_dst = pcompi->new_jmp_icode(icb1);
    pcompi->m_break_label_dst = pcompi->new_jmp_icode(icb2);
    icode *statem_ic = pcompi->ast_to_icode(statem);
    pcompi->m_continue_label_dst = NULL;
    pcompi->m_break_label_dst = NULL;


    a->merge_icode(exp1_ic);
    a->merge_icode(icb1);
    a->merge_icode(exp2_ic);
    a->merge_icode(jz_code);
    a->merge_icode(statem_ic);
    a->merge_icode(exp3_ic);
    a->merge_icode(jmp_code);
    a->merge_icode(icb2);


    //pcompi->set_symbol_list_size(sym_size);
    //pcompi->m_level--;
    pcompi->level_leave();
    return a;
}
class icode *  func_IAN_JUMP_STATEMENT_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4e01-jump_statement->GOTO identifier ';'
    //parent:
    // statement--> jump_statement
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    token_defs *tk = tdefs->m_tk_elems[1];

    std::string label_name = pcompi->get_label_name(tk->name);
    sym* s = pcompi->find_symbol(label_name);
    if(s==NULL)
    {
        pcompi->m_goto_label_unset.push_back(tk->name);
        icode *n = pcompi->new_icode(ICODE_TYPE_LABELED_BLOCK);
        n->name = label_name;
        pcompi->add_symbol(label_name, n);
    }
    s = pcompi->find_symbol(label_name);
    icode * n = pcompi->new_jmp_icode(s->def_icode);
    a->merge_icode(n);
    return a;
}

class icode *  func_IAN_JUMP_STATEMENT_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4e02-jump_statement->CONTINUE ';'
    //parent:
    // statement--> jump_statement
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    if(pcompi->m_continue_label_dst==NULL)
    {
        cerr<<"ERROR:continue used out side of loop\n";
        assert(0);
    }

    a->merge_icode(pcompi->m_continue_label_dst);
    return a;
}

class icode *  func_IAN_JUMP_STATEMENT_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4e03-jump_statement->BREAK ';'
    //parent:
    // statement--> jump_statement
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    if(pcompi->m_break_label_dst==NULL)
    {
        cerr<<"ERROR:break used out side of loop\n";
        assert(0);
    }

    a->merge_icode(pcompi->m_break_label_dst);

    return a;
}

class icode *  func_IAN_JUMP_STATEMENT_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4e04-jump_statement->RETURN ';'
    //parent:
    // statement--> jump_statement
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    a->m_type = ICODE_TYPE_FUNC_RETURN;

    return a;
}

class icode *  func_IAN_JUMP_STATEMENT_5(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x4e05-jump_statement->RETURN expression ';'
    //parent:
    // statement--> jump_statement
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    //GOTO identifier
    //RETURN expression
    assert(tdefs->m_tk_elems[0]->m_type==TOKEN_DEFS_TYPE_ELEM);
    //return expression;
    token_defs *ret1 = tdefs->m_tk_elems[0];
    token_defs *expr1 = tdefs->m_tk_elems[1];
    icode * expr1_ic = pcompi->ast_to_icode(expr1, 1);
    a->merge_icode(expr1_ic);


    sym* fun_ret_sym = pcompi->find_symbol(pcompi->get_func_ret_var_name(pcompi->m_curr_func->name));

    icode *mov = pcompi->new_copy_icode_gen(expr1_ic->result, fun_ret_sym->def_icode);
    a->merge_icode(mov);

    //释放右值结果，如果结果是临时变量
    //赋值语句，如果右值为临时变量，则赋值完成后，可以释放此变量
    icode * res_tt = pcompi->release_tmp_if_need(expr1_ic->result);
    a->merge_icode(res_tt);

    icode *ret_ic = pcompi->new_icode();
    ret_ic->m_type = ICODE_TYPE_FUNC_RETURN;
    a->merge_icode(ret_ic);

    return a;
}


}//namespace end
