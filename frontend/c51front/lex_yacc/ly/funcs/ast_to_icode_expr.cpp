/***********
 *
 * 输入：tdefs result_ic
 * 输出：a->result. 如果有result_ic，则a->result==result_ic
 *
 *
primary_expression
        : identifier
        | constant
        | string
        | '(' expression ')'
        | generic_selection
        ;
postfix_expression
        : primary_expression
        | postfix_expression '[' expression ']'
        | postfix_expression '(' ')'
        | postfix_expression '(' argument_expression_list ')'
        | postfix_expression '.'   identifier
        | postfix_expression PTR_OP  identifier
        | postfix_expression INC_OP

        | postfix_expression DEC_OP
        | '(' type_name ')' '{' initializer_list '}'
        | '(' type_name ')' '{' initializer_list ',' '}'
        ;


argument_expression_list
        : assignment_expression
        | argument_expression_list ',' assignment_expression
        ;


unary_expression
        : postfix_expression
        | INC_OP unary_expression
        | DEC_OP unary_expression
        | unary_operator cast_expression
        | SIZEOF unary_expression
        | SIZEOF '(' type_name ')'
        | ALIGNOF '(' type_name ')'





        ;

unary_operator
        : '&'
        | '*'
        | '+'
        | '-'
        | '~'
        | '!'
        ;


cast_expression
    : unary_expression
    | '(' type_name ')' cast_expression
    ;

multiplicative_expression
    : cast_expression
    | multiplicative_expression '*' cast_expression
    | multiplicative_expression '/' cast_expression
    | multiplicative_expression '%' cast_expression
    ;

additive_expression
    : multiplicative_expression
    | additive_expression '+' multiplicative_expression
    | additive_expression '-' multiplicative_expression
    ;

shift_expression
    : additive_expression
    | shift_expression LEFT_OP additive_expression
    | shift_expression RIGHT_OP additive_expression
    | shift_expression ROTATE_LEFT_OP additive_expression
    | shift_expression ROTATE_RIGHT_OP additive_expression
    ;

relational_expression
    : shift_expression
    | relational_expression '<' shift_expression
    | relational_expression '>' shift_expression
    | relational_expression LE_OP shift_expression
    | relational_expression GE_OP shift_expression
    ;

equality_expression
    : relational_expression
    | equality_expression EQ_OP relational_expression
    | equality_expression NE_OP relational_expression
    ;

and_expression
    : equality_expression
    | and_expression '&' equality_expression
    ;

exclusive_or_expression
    : and_expression
    | exclusive_or_expression '^' and_expression
    ;

inclusive_or_expression
    : exclusive_or_expression
    | inclusive_or_expression '|' exclusive_or_expression
    ;

logical_and_expression
    : inclusive_or_expression
    | logical_and_expression AND_OP inclusive_or_expression
    ;

logical_or_expression
    : logical_and_expression
    | logical_or_expression OR_OP logical_and_expression
    ;

conditional_expression
    : logical_or_expression
    | logical_or_expression '?' expression ':' conditional_expression
    ;

assignment_expression
    : conditional_expression
    | unary_expression assignment_operator assignment_expression
    ;

assignment_operator
    : '='
    | MUL_ASSIGN
    | DIV_ASSIGN
    | MOD_ASSIGN
    | ADD_ASSIGN
    | SUB_ASSIGN
    | LEFT_ASSIGN
    | RIGHT_ASSIGN
    | AND_ASSIGN
    | XOR_ASSIGN
    | OR_ASSIGN
    ;

expression
    : assignment_expression
    | expression ',' assignment_expression
    ;

constant_expression
    : conditional_expression
    ;
 * **/

#include "ast_to_icode_expr.h"
#include "target_base.h"

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





class icode *  func_IAN_PRIMARY_EXPRESSION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1-primary_expression->identifier
    //parent:
    // postfix_expression--> primary_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_PRIMARY_EXPRESSION_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x2-primary_expression->constant
    //parent:
    // postfix_expression--> primary_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_PRIMARY_EXPRESSION_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x3-primary_expression->string
    //parent:
    // postfix_expression--> primary_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_PRIMARY_EXPRESSION_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{

    //0x4-primary_expression->'(' expression ')'
    //parent:
    // postfix_expression--> primary_expression
    icode *b = pcompi->ast_to_icode(tdefs->m_tk_elems[1], need_result_icode, result_ic);

    return b;
}
class icode *  func_IAN_PRIMARY_EXPRESSION_5(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x5-primary_expression->generic_selection
    //parent:
    // postfix_expression--> primary_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}


class icode *  func_IAN_POSTFIX_EXPRESSION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x701-postfix_expression->primary_expression
    //parent:
    // postfix_expression--> postfix_expression '[' expression ']'
    // postfix_expression--> postfix_expression '(' ')'
    // postfix_expression--> postfix_expression '(' argument_expression_list ')'
    // postfix_expression--> postfix_expression '.' identifier
    // postfix_expression--> postfix_expression PTR_OP identifier
    // postfix_expression--> postfix_expression INC_OP
    // postfix_expression--> postfix_expression DEC_OP
    // unary_expression--> postfix_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}

class icode *  func_IAN_POSTFIX_EXPRESSION_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    ///数组方式读取的访问
    ///2021.1.20L
    ///
    ///
    /// int a[4];
    /// a[2]=5;
    /// -------------
    /// def_var: $a,u64[i16][iconst:0x4];
    /// opr: "=", null;, iconst:0x5;, var_in:%a[iconst:0x2];
    /// -------------
    ///
    /// int a[4][7];
    /// a[2][6]=3;
    ///
    /// def_var: $a,u448[i16][iconst:0x4][iconst:0x7];
    /// opr: "=", null;, iconst:0x3;, var_in:%a[iconst:0x2][iconst:0x6];
    ///
    /// --------------------
    /// int **a;
    /// a[3][4]=5;
    ///
    /// def_var: $a,u24*2*[i16];
    /// opr: "=", null;, iconst:0x5;, var_in:%a[iconst:0x3][iconst:0x4];
    /// --------------------
    ///
    ///
    ///
    ///
    ///
    ///

    //0x702-postfix_expression->postfix_expression '[' expression ']'
    //parent:
    // postfix_expression--> postfix_expression '[' expression ']'
    // postfix_expression--> postfix_expression '(' ')'
    // postfix_expression--> postfix_expression '(' argument_expression_list ')'
    // postfix_expression--> postfix_expression '.' identifier
    // postfix_expression--> postfix_expression PTR_OP identifier
    // postfix_expression--> postfix_expression INC_OP
    // postfix_expression--> postfix_expression DEC_OP
    // unary_expression--> postfix_expression
#if 1


    token_defs *postfix_expression = tdefs->m_tk_elems[0];
    token_defs *expression = tdefs->m_tk_elems[2];

    icode *post_ic = pcompi->ast_to_icode(postfix_expression, 1);
    icode *expr_ic = pcompi->ast_to_icode(expression, 1);
    icode *post_def_var = pcompi->get_def_var(post_ic->result);


    if((post_def_var->m_type==ICODE_TYPE_DEF_VAR_IN_VAR)||
            (post_def_var->m_type==ICODE_TYPE_DEF_VAR_IN_VAR_TMP))
    {
        ///此处只能是数组生成的
        /// 内部是指针，指向一个数组
        ///
        ///
        ///
        /// int a[5][6];
        /// a[3][4]=7;
        /// def_var: $a,u480[i16][iconst:0x5][iconst:0x6];
        ///
        /// def_var_tmp: $tmp1, u24*1*u88[i16][iconst:0x6]; <--多维数组，数据类型是少了一层的数组的指针
        /// opr:"address_of";,null;,%a;,%tmp1;
        /// def_var_tmp:$tmp2;,u24;
        /// opr:"*";,const:11;, const:3;, %tmp2;
        /// opr:"+";,%tmp1;,%tmp2;, %tmp1;
        /// var_in_tmp:%tmp1*1; <<--多维数组，返回一个数组的指针
        ///
        ///
        ///
        ///
        ///
        ///
        assert(post_def_var->result->is_ptr==1);

        icode *a = pcompi->new_icode();
        a->m_type = ICODE_TYPE_BLOCK;

        icode *tmp1=NULL;
        if(post_def_var->result->m_in_ptr_type->is_array==1)
        {
            //是数组，并且就是1维数组
            tmp1 = pcompi->new_temp_ptr_var(post_def_var->result->m_in_ptr_type->m_in_ptr_type);
        }
        else
        {
            tmp1 = pcompi->new_temp_ptr_var(post_def_var->result->m_in_ptr_type);
            tmp1->m_in_ptr_type->array_cnt.erase(tmp1->m_in_ptr_type->array_cnt.begin());
            tmp1->m_in_ptr_type->refresh_array_total_bit_width();
        }

        //opr:"=";,null;,%a;,%tmp1;
        icode *movB = pcompi->new_opr_icode("=", NULL, post_def_var->result, tmp1);

        //def_var_tmp:$tmp2;,u24;
        icode *tmp2 = pcompi->new_temp_var();
        tmp2->m_bit_width = pcompi->m_top_icodes->m_target->get_basic_type_bit_width("GENERIC_PTR");
        tmp2->is_signed = 0;

        //opr:"*";,const:11;, const:3;, %tmp2;
        icode *movA = pcompi->new_opr_icode("*", expr_ic->result, pcompi->new_iconst_icode((tmp1->m_in_ptr_type->m_bit_width+7)/8), tmp2 );


        //opr:"+";,%tmp1;,%tmp2;, %tmp1;
        icode *addA = pcompi->new_opr_icode("+", tmp1, tmp2, tmp1);


        //是数组，并且就是1维数组
        icode *var_in1 = pcompi->m_top_icodes->new_var_in_var_tmp_icode(tmp1);
        post_ic->result = var_in1;


        a->merge_icode(post_ic);
        a->merge_icode(expr_ic);

        a->merge_icode(tmp1);
        a->merge_icode(movB);
        a->merge_icode(tmp2);
        a->merge_icode(movA);
        a->merge_icode(addA);

        a->result = post_ic->result;
        return a;

    }
    else if(post_def_var->is_ptr)
    {
        int is_ptr_level = pcompi->get_def_var(post_ic->result)->is_ptr;
        ///
        /// int *a;
        /// a[3]=6;
        ///
        /// def_var:$a, u24*1*[u16];
        /// def_var_tmp: $tmp1, u24*1*[u16];
        /// opr:"=";,null;,%a;,%tmp1;
        /// def_var_tmp:$tmp2;,u24;
        /// opr:"*";,const:2;, const:3;, %tmp2;
        /// opr:"+";,%tmp1;,%tmp2;, %tmp1;
        /// var_in_tmp:tmp1*1;
        ///
        ///
        /// int **a;
        /// a[3][4]=6;
        ///
        /// def_var:$a, u24*2*[u16];
        /// def_var_tmp: $tmp0, u24*1*[u16];
        /// def_var_tmp: $tmp1, u24*2*[u16];
        /// opr:"=";,null;,%a;,%tmp1;
        /// def_var_tmp:$tmp2;,u24;
        /// opr:"*";,const:2;, const:3;, %tmp2;
        /// opr:"+";,%tmp1;,%tmp2;, %tmp1;
        /// opr:"=";,null;,var_in_tmp:tmp1*1;,%tmp0;
        /// tmp0???
        ///
        ///
        /// (int *) p[5]; <--数组，里面存的是指针
        /// int (* p)[5]; <--指针，指向的是数组
        ///
        ///
        ///如果是指针
        /// 通过数组的方式读写，则只需要将原来指针复制到新临时变量，+偏移。 返回新的指针,var_in 类型
        ///创建1个临时变量



        icode *a = pcompi->new_icode(ICODE_TYPE_BLOCK);

        a->merge_icode(post_ic);
        a->merge_icode(expr_ic);

        icode * tmp0 = NULL;
        icode * tmp_var_curr=NULL;
        if(is_ptr_level!=1)
        {
            tmp0 = pcompi->m_top_icodes->new_temp_var(pcompi->get_def_var(post_ic->result));
            tmp0->is_ptr--;
            a->merge_icode(tmp0);
        }

        {
            //如果是-1，则返回的是var_in.
            icode * tmp_1 = pcompi->m_top_icodes->new_temp_var(pcompi->get_def_var(post_ic->result));
            tmp_var_curr = tmp_1;

            icode *movB = pcompi->new_opr_icode("=", NULL, post_ic->result, tmp_1);

            icode *tmp2 = pcompi->new_temp_var();
            tmp2->m_bit_width = pcompi->m_top_icodes->m_target->get_basic_type_bit_width("GENERIC_PTR");
            tmp2->is_signed = 0;

            icode *movA = pcompi->new_opr_icode("*",NULL, expr_ic->result,  tmp2);
            if(is_ptr_level==1)
            {
                movA->left = pcompi->new_iconst_icode((pcompi->get_def_var(post_ic->result)->m_in_ptr_type->m_bit_width+7)/8);
            }
            else
            {
                //不是最后一层，每一层都是指针的长度
                movA->left = pcompi->new_iconst_icode((pcompi->m_top_icodes->m_target->get_basic_type_bit_width("GENERIC_PTR")+7)/8);
            }

            icode *addA = pcompi->new_opr_icode("+",tmp2, tmp_1, tmp_1 );

            a->merge_icode(tmp_1);
            a->merge_icode(movB);
            a->merge_icode(tmp2);
            a->merge_icode(movA);
            a->merge_icode(addA);
        }
        if(is_ptr_level==1)
        {
            ///最后一层。返回的是var_in
            icode *var_in1 = pcompi->m_top_icodes->new_var_in_var_tmp_icode(tmp_var_curr);
            post_ic->result = var_in1;
            a->result = post_ic->result;
            return a;
        }
        else
        {
            ///非最后一层，返回的是tmp0
            ///
            icode *var_in1 = pcompi->m_top_icodes->new_var_in_var_tmp_icode(tmp_var_curr);
            icode *ass2A = pcompi->new_opr_icode("=", NULL, var_in1, tmp0);

            post_ic->result = pcompi->new_ref_icode(tmp0);
            a->result = post_ic->result;
            a->merge_icode(ass2A);

            return a;


        }

    }
    else
    {
        //如果是数组
        /// int a[5];
        /// a[3]=4;
        ///
        /// def_var: $a,u80[i16][iconst:0x5];
        /// def_var_tmp: $tmp1, u24*1*u16; <---一维数组，此tmp1就是内部是数据类型的指针
        /// opr:"address_of";,null;,%a;,%tmp1;
        /// def_var_tmp:$tmp2;,u24;
        /// opr:"*";,const:2;, const:3;, %tmp2;
        /// opr:"+";,%tmp1;,%tmp2;, %tmp1;
        /// var_in_tmp:tmp1*1; <<--一维数组，返回var_in
        ///
        ///
        /// int a[5][6];
        /// a[3][4]=7;
        /// def_var: $a,u480[i16][iconst:0x5][iconst:0x6];
        ///
        /// def_var_tmp: $tmp1, u24*1*u88[i16][iconst:0x6]; <--多维数组，数据类型是少了一层的数组的指针
        /// opr:"address_of";,null;,%a;,%tmp1;
        /// def_var_tmp:$tmp2;,u24;
        /// opr:"*";,const:11;, const:3;, %tmp2;
        /// opr:"+";,%tmp1;,%tmp2;, %tmp1;
        /// tmp1; <<--多维数组，返回一个数组的指针
        ///
        ///
        ///
        icode *a = pcompi->new_icode();
        a->m_type = ICODE_TYPE_BLOCK;

        icode *tmp1=NULL;
        if(post_def_var->is_array==1)
        {
            //是数组，并且就是1维数组
            tmp1 = pcompi->new_temp_ptr_var(post_def_var->m_in_ptr_type);
        }
        else
        {
            tmp1 = pcompi->new_temp_ptr_var(post_def_var);
            tmp1->m_in_ptr_type->array_cnt.erase(tmp1->m_in_ptr_type->array_cnt.begin());
            tmp1->m_in_ptr_type->is_array = tmp1->m_in_ptr_type->array_cnt.size();
            tmp1->m_in_ptr_type->refresh_array_total_bit_width();

        }

        //opr:"address_of";,null;,%a;,%tmp1;
        icode *movB = pcompi->new_opr_icode("address_of", NULL, post_ic->result, tmp1);

        //def_var_tmp:$tmp2;,u24;
        icode *tmp2 = pcompi->new_temp_var();
        tmp2->m_bit_width = pcompi->m_top_icodes->m_target->get_basic_type_bit_width("GENERIC_PTR");
        tmp2->is_signed = 0;

        //opr:"*";,const:11;, const:3;, %tmp2;
        icode *movA = pcompi->new_opr_icode("*", expr_ic->result, pcompi->new_iconst_icode((tmp1->m_in_ptr_type->m_bit_width+7)/8), tmp2 );

        //opr:"+";,%tmp1;,%tmp2;, %tmp1;
        icode *addA = pcompi->new_opr_icode("+", tmp1, tmp2, tmp1);


        //是数组，并且就是1维数组
        icode *var_in1 = pcompi->m_top_icodes->new_var_in_var_tmp_icode(tmp1);
        post_ic->result = var_in1;


        a->merge_icode(post_ic);
        a->merge_icode(expr_ic);

        a->merge_icode(tmp1);
        a->merge_icode(movB);
        a->merge_icode(tmp2);
        a->merge_icode(movA);
        a->merge_icode(addA);

        a->result = post_ic->result;
        return a;
    }

#endif
}

class icode *  func_IAN_POSTFIX_EXPRESSION_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 无参数的函数调用
    ///
    ///
    //0x703-postfix_expression->postfix_expression '(' ')'
    //parent:
    // postfix_expression--> postfix_expression '[' expression ']'
    // postfix_expression--> postfix_expression '(' ')'
    // postfix_expression--> postfix_expression '(' argument_expression_list ')'
    // postfix_expression--> postfix_expression '.' identifier
    // postfix_expression--> postfix_expression PTR_OP identifier
    // postfix_expression--> postfix_expression INC_OP
    // postfix_expression--> postfix_expression DEC_OP
    // unary_expression--> postfix_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    token_defs *postfix_expression = tdefs->m_tk_elems[0];
    assert((postfix_expression->m_type==TOKEN_DEFS_TYPE_ELEM)&&
           (postfix_expression->m_token_type==Parser::token::IDENTIFIER));

    icode * post_ic = pcompi->ast_to_icode(postfix_expression);

    //post_ic应该是一个函数。函数调用

    icode *curr = pcompi->new_icode();
    curr->m_type = ICODE_TYPE_CALL;
    curr->result=post_ic->result;

    a->merge_icode(post_ic);
    a->merge_icode(curr);

    if(need_result_icode)
    {
        //函数调用。需要返回值???
        a->result=(pcompi->new_ref_icode(post_ic->result->result->sub_icode[0])) ;
        //a->result = pcompi->new_icode();
        //a->result->m_type = ICODE_TYPE_SYMBOL_REF;
        //a->result->result = post_ic->result->result;
    }
    return a;
}

class icode *  func_IAN_POSTFIX_EXPRESSION_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{

    ///有参数的函数调用

    /// 此处是函数调用 _inline_asm_("MOV A, 0x30;\n"); 的前半部分，没有";"

    //0x704-postfix_expression->postfix_expression '(' argument_expression_list ')'
    //parent:
    // postfix_expression--> postfix_expression '[' expression ']'
    // postfix_expression--> postfix_expression '(' ')'
    // postfix_expression--> postfix_expression '(' argument_expression_list ')'
    // postfix_expression--> postfix_expression '.' identifier
    // postfix_expression--> postfix_expression PTR_OP identifier
    // postfix_expression--> postfix_expression INC_OP
    // postfix_expression--> postfix_expression DEC_OP
    // unary_expression--> postfix_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    ///带参数的函数调用
    ///
    token_defs * postfix_expression = tdefs->m_tk_elems[0];
    token_defs * argument_expression_list = tdefs->m_tk_elems[2];

    if(postfix_expression->val_str=="_inline_asm_")
    {
        ///此处是内嵌的asm，直接转换为
        ///ICODE_TYPE_ASM

        a->m_type=ICODE_TYPE_ASM;
        icode *argu = pcompi->ast_to_icode(argument_expression_list, 1);
        a->name = argu->result->name;
        return a;
    }



    icode * post_ic = pcompi->ast_to_icode(postfix_expression, 1);

    icode *argu = pcompi->ast_to_icode(argument_expression_list, 1);
    icode *curr = pcompi->new_icode();
    curr->m_type = ICODE_TYPE_CALL;
    curr->result = post_ic->result;// 函数调用，此处不能添加引用
    curr->merge_icode(argu->result);

    a->merge_icode(post_ic);
    a->merge_icode(argu);
    a->merge_icode(curr);

    if(need_result_icode)
    {
        //函数调用。需要返回值???
        a->result = pcompi->new_ref_icode(pcompi->get_def_var(post_ic->result)->sub_icode[0]);
    }

    return a;
}

class icode *  func_IAN_POSTFIX_EXPRESSION_5(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{

    /// 结构体的内部成员变量读取

    //0x705-postfix_expression->postfix_expression '.' identifier
    //parent:
    // postfix_expression--> postfix_expression '[' expression ']'
    // postfix_expression--> postfix_expression '(' ')'
    // postfix_expression--> postfix_expression '(' argument_expression_list ')'
    // postfix_expression--> postfix_expression '.' identifier
    // postfix_expression--> postfix_expression PTR_OP identifier
    // postfix_expression--> postfix_expression INC_OP
    // postfix_expression--> postfix_expression DEC_OP
    // unary_expression--> postfix_expression
#if 0
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    token_defs *postfix_expression=tdefs->m_tk_elems[0];
    //token_defs *'.'=tdefs->m_tk_elems[1];
    token_defs *identifier=tdefs->m_tk_elems[2];
    icode *postfix_expression_ic=pcompi->ast_to_icode(postfix_expression, 1);
    //icode *'.'_ic=pcompi->ast_to_icode('.');

    assert((postfix_expression_ic->result->m_type==ICODE_TYPE_SYMBOL_REF)||
           (postfix_expression_ic->result->m_type==ICODE_TYPE_DEF_VAR_IN_VAR)||
           (postfix_expression_ic->result->m_type==ICODE_TYPE_DEF_VAR_IN_VAR_TMP)
           );

    /// result是一个ref，因为之前ref和ptr是用同一个类型，所以做此判断
    /// 现在ptr使用VAR_IN_VAR来实现,所以不再用此断言
    //assert(postfix_expression_ic->result->is_ptr==0);


    icode *dst = pcompi->get_def_var( postfix_expression_ic->result);

    if(dst==NULL)
    {
        cerr<<"ERROR: unresolved symbol:"<< postfix_expression_ic->result->name<<"\n";
        return a;
    }

    icode * ret = dst->get_member_icode(identifier->val_str);
    if(ret==NULL)
    {
        cerr<<"var:" << dst->name <<" has no member:"<< identifier->val_str<<"\n";
        assert(0);
    }
    assert(ret!=NULL);

    a->result = (pcompi->new_ref_icode(ret));
    return a;
#else
    icode *a = pcompi->new_icode();
       a->m_type=ICODE_TYPE_BLOCK;
       token_defs *postfix_expression=tdefs->m_tk_elems[0];
       //token_defs *'.'=tdefs->m_tk_elems[1];
       token_defs *identifier=tdefs->m_tk_elems[2];
       icode *postfix_expression_ic=pcompi->ast_to_icode(postfix_expression, 1);
       //icode *'.'_ic=pcompi->ast_to_icode('.');

       assert((postfix_expression_ic->result->m_type==ICODE_TYPE_SYMBOL_REF)||
              (postfix_expression_ic->result->m_type==ICODE_TYPE_DEF_VAR_IN_VAR)||
              (postfix_expression_ic->result->m_type==ICODE_TYPE_DEF_VAR_IN_VAR_TMP)
              );

       /// result是一个ref，因为之前ref和ptr是用同一个类型，所以做此判断
       /// 现在ptr使用VAR_IN_VAR来实现,所以不再用此断言
       //assert(postfix_expression_ic->result->is_ptr==0);


       icode *dst = pcompi->get_def_var( postfix_expression_ic->result);

       if(dst==NULL)
       {
           cerr<<"ERROR: unresolved symbol:"<< postfix_expression_ic->result->name<<"\n";
           return a;
       }

       icode * var_attr = NULL;
       int bit_width_offset = NULL;


       var_attr = dst->get_member_icode(identifier->val_str);
       bit_width_offset = dst->get_member_offset_bit_width(identifier->val_str);


       icode *ptr_new = pcompi->new_temp_ptr_var(var_attr);


       icode * mova = pcompi->new_opr_icode("address_of", NULL, dst, ptr_new);

       icode *adda = pcompi->new_opr_icode("+",
                                           pcompi->new_iconst_icode((bit_width_offset+7)/8),
                                           ptr_new, ptr_new);

       a->merge_icode(postfix_expression_ic);
       a->merge_icode(ptr_new);
       a->merge_icode(mova);
       a->merge_icode(adda);

       a->result = pcompi->new_var_in_var_icode(ptr_new);

       return a;
#endif
}




///
/// \brief func_IAN_POSTFIX_EXPRESSION_6 p->a类型代码翻译
/// \param pcompi
/// \param tdefs
/// \param need_result_icode
/// \param result_ic
/// \return
/// 此处是结构图指针的读写
/// struct A{
/// int a;
/// float b;
/// };
/// struct A *p, d;
/// p = &d;
/// p->a=12;               <------
/// 此处生成一个临时的DEF_VAR 指针变量 is_ptr=1，变量的值:基础值+偏移。 类型为成员的类型
/// 生成一个VAR_IN_VAR,类型为
///
class icode *  func_IAN_POSTFIX_EXPRESSION_6(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    /// 内部成员访问：指针内部 a->b
    ///
    ///
    //0x706-postfix_expression->postfix_expression PTR_OP identifier
    //parent:
    // postfix_expression--> postfix_expression '[' expression ']'
    // postfix_expression--> postfix_expression '(' ')'
    // postfix_expression--> postfix_expression '(' argument_expression_list ')'
    // postfix_expression--> postfix_expression '.' identifier
    // postfix_expression--> postfix_expression PTR_OP identifier
    // postfix_expression--> postfix_expression INC_OP
    // postfix_expression--> postfix_expression DEC_OP
    // unary_expression--> postfix_expression





    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    token_defs *postfix_expression=tdefs->m_tk_elems[0];
    token_defs *PTR_OP = tdefs->m_tk_elems[1];
    token_defs *identifier = tdefs->m_tk_elems[2];

    icode * expr_ic = pcompi->ast_to_icode(postfix_expression, 1);

    ///expr_ic->result可能是两种值：
    /// struct A *a;
    /// a->a=1;//->此处expr_ic=a 为符号引用
    /// struct A **a;
    /// (*a)->a=1; //->此处expr_ic=*a 为var_in_var


    assert((expr_ic->result->m_type==ICODE_TYPE_SYMBOL_REF)||
           (expr_ic->result->m_type==ICODE_TYPE_DEF_VAR_IN_VAR)||
           (expr_ic->result->m_type==ICODE_TYPE_DEF_VAR_IN_VAR_TMP)
           );
    assert(expr_ic->result->result!=NULL);
    icode *ptr_ic_ref = expr_ic->result;
    icode *ptr_ic = pcompi->get_def_var(expr_ic->result);
    //assert(ptr_ic->is_union || ptr_ic->is_struct);
    //assert(ptr_ic->is_array||ptr_ic->is_ptr);

    icode * var_attr = NULL;
    int bit_width_offset = NULL;


    var_attr = ptr_ic->get_member_icode(identifier->val_str);
    bit_width_offset = ptr_ic->get_member_offset_bit_width(identifier->val_str);



    icode *ptr_new = pcompi->new_temp_ptr_var(var_attr);

    icode *mova = pcompi->mov_icode(ptr_ic, ptr_new);


    icode *adda = pcompi->new_icode(ICODE_TYPE_EXP_OP);
    adda->name = "+";
    adda->right=pcompi->new_ref_icode(ptr_new);
    adda->left=pcompi->new_iconst_icode(bit_width_offset/8);
    adda->result = pcompi->new_ref_icode(ptr_new);

    a->merge_icode(expr_ic);
    a->merge_icode(ptr_new);
    a->merge_icode(mova);
    a->merge_icode(adda);

    a->result = pcompi->new_var_in_var_icode(ptr_new);

    if(need_result_icode&&result_ic)
    {
        icode *bb = pcompi->new_copy_icode_gen(a->result, result_ic);
        a->result = result_ic;
        a->merge_icode(bb);
    }


    return a;
}

class icode *  func_IAN_POSTFIX_EXPRESSION_7(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x707-postfix_expression->postfix_expression INC_OP
    //parent:
    // postfix_expression--> postfix_expression '[' expression ']'
    // postfix_expression--> postfix_expression '(' ')'
    // postfix_expression--> postfix_expression '(' argument_expression_list ')'
    // postfix_expression--> postfix_expression '.' identifier
    // postfix_expression--> postfix_expression PTR_OP identifier
    // postfix_expression--> postfix_expression INC_OP
    // postfix_expression--> postfix_expression DEC_OP
    // unary_expression--> postfix_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    token_defs* postfix_expression = tdefs->m_tk_elems[0];

    icode *b = pcompi->new_icode();
    b->m_type = ICODE_TYPE_EXP_OP;

    //左值减1 +1
    b->name = tdefs->m_tk_elems[1]->val_str;

    icode *c = pcompi->ast_to_icode(postfix_expression, 1);
    b->result = c->result;

    a->merge_icode(c);
    if(need_result_icode)
    {
        //此处生成一个临时变量，用于传递结果？？？
        //前置表达式，不需要临时变量，--i; 直接使用i
        //后置表达式需要临时变量，i--,先临时变量保存i，再操作i，返回临时变量
        icode *tmp = pcompi->new_temp_var();
        icode *tmp_ref = pcompi->new_ref_icode(tmp);
        a->merge_icode(tmp);
        //此处生成赋值语句代码

        tmp->set_width_from(c->result);
        icode *cp_tmp = pcompi->new_copy_icode_gen(c->result, tmp);
        a->merge_icode(cp_tmp);

        a->result =tmp_ref;
    }
    a->merge_icode(b);

    return a;
}

class icode *  func_IAN_POSTFIX_EXPRESSION_8(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x708-postfix_expression->postfix_expression DEC_OP
    //parent:
    // postfix_expression--> postfix_expression '[' expression ']'
    // postfix_expression--> postfix_expression '(' ')'
    // postfix_expression--> postfix_expression '(' argument_expression_list ')'
    // postfix_expression--> postfix_expression '.' identifier
    // postfix_expression--> postfix_expression PTR_OP identifier
    // postfix_expression--> postfix_expression INC_OP
    // postfix_expression--> postfix_expression DEC_OP
    // unary_expression--> postfix_expression

    return func_IAN_POSTFIX_EXPRESSION_7(pcompi, tdefs, need_result_icode, result_ic);
}

class icode *  func_IAN_POSTFIX_EXPRESSION_9(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x709-postfix_expression->'(' type_name ')' '{' initializer_list '}'
    //parent:
    // postfix_expression--> postfix_expression '[' expression ']'
    // postfix_expression--> postfix_expression '(' ')'
    // postfix_expression--> postfix_expression '(' argument_expression_list ')'
    // postfix_expression--> postfix_expression '.' identifier
    // postfix_expression--> postfix_expression PTR_OP identifier
    // postfix_expression--> postfix_expression INC_OP
    // postfix_expression--> postfix_expression DEC_OP
    // unary_expression--> postfix_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *'('=tdefs->m_tk_elems[0];
    token_defs *type_name=tdefs->m_tk_elems[1];
    //token_defs *')'=tdefs->m_tk_elems[2];
    //token_defs *'{'=tdefs->m_tk_elems[3];
    token_defs *initializer_list=tdefs->m_tk_elems[4];
    //token_defs *'}'=tdefs->m_tk_elems[5];
    //icode *'('_ic=pcompi->ast_to_icode('(');
    icode *type_name_ic=pcompi->ast_to_icode(type_name);
    //icode *')'_ic=pcompi->ast_to_icode(')');
    //icode *'{'_ic=pcompi->ast_to_icode('{');
    icode *initializer_list_ic=pcompi->ast_to_icode(initializer_list);
    //icode *'}'_ic=pcompi->ast_to_icode('}');
    //a->merge_icode('('_ic);
    //a->merge_icode(type_name_ic);
    //a->merge_icode(')'_ic);
    //a->merge_icode('{'_ic);
    //a->merge_icode(initializer_list_ic);
    //a->merge_icode('}'_ic);
    assert(0);
    return a;
}

class icode *  func_IAN_POSTFIX_EXPRESSION_10(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x70a-postfix_expression->'(' type_name ')' '{' initializer_list ',' '}'
    //parent:
    // postfix_expression--> postfix_expression '[' expression ']'
    // postfix_expression--> postfix_expression '(' ')'
    // postfix_expression--> postfix_expression '(' argument_expression_list ')'
    // postfix_expression--> postfix_expression '.' identifier
    // postfix_expression--> postfix_expression PTR_OP identifier
    // postfix_expression--> postfix_expression INC_OP
    // postfix_expression--> postfix_expression DEC_OP
    // unary_expression--> postfix_expression

    return func_IAN_POSTFIX_EXPRESSION_9(pcompi, tdefs, need_result_icode, result_ic);
}



class icode *  func_IAN_ARGUMENT_EXPRESSION_LIST_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x801-argument_expression_list->assignment_expression
    //parent:
    // postfix_expression--> postfix_expression '(' argument_expression_list ')'
    // argument_expression_list--> argument_expression_list ',' assignment_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_ARGUMENT_EXPRESSION_LIST_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x802-argument_expression_list->argument_expression_list ',' assignment_expression
    //parent:
    // postfix_expression--> postfix_expression '(' argument_expression_list ')'
    // argument_expression_list--> argument_expression_list ',' assignment_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    token_defs *  argument_expression_list = tdefs->m_tk_elems[0];
    token_defs *  assignment_expression = tdefs->m_tk_elems[2];
    icode *arg_ic = pcompi->ast_to_icode(argument_expression_list, 1);
    icode *ass_ic = pcompi->ast_to_icode(assignment_expression, 1);

    a->merge_icode(arg_ic);
    a->merge_icode(ass_ic);
    if(need_result_icode)
    {

        a->result = pcompi->new_icode();
        a->result->m_type = ICODE_TYPE_BLOCK;
        ///2020.7.19 函数参数有多个时，result中返回
        a->result->merge_icode(arg_ic->result);
        a->result->merge_icode(ass_ic->result);
    }

    return a;
}
class icode *  func_IAN_UNARY_EXPRESSION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x901-unary_expression->postfix_expression
    //parent:
    // unary_expression--> INC_OP unary_expression
    // unary_expression--> DEC_OP unary_expression
    // unary_expression--> SIZEOF unary_expression
    // cast_expression--> unary_expression
    // assignment_expression--> unary_expression assignment_operator assignment_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}

class icode *  func_IAN_UNARY_EXPRESSION_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x902-unary_expression->INC_OP unary_expression
    //parent:
    // unary_expression--> INC_OP unary_expression
    // unary_expression--> DEC_OP unary_expression
    // unary_expression--> SIZEOF unary_expression
    // cast_expression--> unary_expression
    // assignment_expression--> unary_expression assignment_operator assignment_expression

    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;


    //INC_OP unary_expression
    //DEC_OP unary_expression
    token_defs* unary_expr = tdefs->m_tk_elems[1];

    icode *b = pcompi->new_icode();
    b->m_type = ICODE_TYPE_EXP_OP;
    b->name = tdefs->m_tk_elems[0]->val_str;

    icode *c = pcompi->ast_to_icode(unary_expr, 1);

    ///----------------

    b->result = c->result;
    ///----------------
    ///


    a->merge_icode(c);

    a->merge_icode(b);

    if(need_result_icode)
    {
        if((result_ic==NULL)||(b->result->is_ref_equal(result_ic)))
        {
            a->result = b->result;
        }
        else
        {
            //b!=result_ic
            //需要将结果放入result_ic
            icode *another_mov = pcompi->new_copy_icode_gen(b->result, result_ic);
#if 0
            icode *another_mov = pcompi->new_icode();
            another_mov->m_type = ICODE_TYPE_EXP_OP;
            another_mov->name = "=";
            ///2020.8.10 修改赋值语句的left right定义
            ///
            another_mov->right = b->result;
            another_mov->left = result_ic;
            another_mov->result = result_ic;
#endif
            a->merge_icode(another_mov);
            a->result = result_ic;
        }
    }

    return a;
}
class icode *  func_IAN_UNARY_EXPRESSION_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x903-unary_expression->DEC_OP unary_expression
    //parent:
    // unary_expression--> INC_OP unary_expression
    // unary_expression--> DEC_OP unary_expression
    // unary_expression--> SIZEOF unary_expression
    // cast_expression--> unary_expression
    // assignment_expression--> unary_expression assignment_operator assignment_expression

    return func_IAN_UNARY_EXPRESSION_2(pcompi, tdefs, need_result_icode, result_ic);
}



icode * in_ptr_expr(comp_context* pcompi, token_defs* tdefs, bool need_result_icode, icode* result_ic)
{
    /// int *a;
    /// *a=3;
    ///
    /// def_var: $a,u24*1*[i16];
    /// opr: "=", null;, iconst:0x3;, var_in:%a*1;

    /// int **a;
    /// **a=3;
    ///
    /// def_var: $a,u24*2*[i16];
    /// def_var_tmp: $tmp1, u24*1*[i16];
    /// opr: "=", null;, var_in:%a*1;, %tmp1;
    /// opr: "=", null;, iconst:0x3;, var_in:%tmp1*1;
    ///
    ///
    ///
    /// *b;
    token_defs * unary_operator = tdefs->m_tk_elems[0];
    token_defs* unary_expr = tdefs->m_tk_elems[1];


    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;


    icode *c = pcompi->ast_to_icode(unary_expr, 1);
    a->merge_icode(c);

    if((c->result->m_type!=ICODE_TYPE_DEF_VAR_IN_VAR)&&
            (c->result->m_type!=ICODE_TYPE_DEF_VAR_IN_VAR_TMP))
    {
        //不是指针的多次迭代
        a->result = pcompi->new_var_in_var_icode(c->result);

        if(need_result_icode&&result_ic)
        {
            {
                icode *b = pcompi->new_copy_icode_gen(a->result, result_ic);
                a->result = result_ic;
                a->merge_icode(b);
            }
        }

        return a;
    }
    else
    {
        /// 此处是指针的多次迭代，
        /// int **a;
        /// **a=3;
        ///
        /// 如果按照上面同样的代码，会生成中间代码：
        /// def_var: $a,u24*2*[i16];
        /// opr: "=", null;, iconst:0x3;, var_in:%a*2;
        /// 此处直接将 var_in:%a*2 翻译为只有var_in:%x*1的1维指针模式。
        ///
        /// def_var: $a,u24*2*[i16];
        /// def_var_tmp: $tmp1, u24*1*[i16];  <<<----------生成新的临时变量
        /// opr: "=", null;, var_in:%a*1;, %tmp1;
        /// opr: "=", null;, iconst:0x3;, var_in:%tmp1*1;
        ///

        /// c->result是var_in_var类型
        /// c->result->result是引用的类型，应该是指针或者数组变量
        ///

        icode * tmp1 = pcompi->m_top_icodes->new_temp_var( c->result->result);
        if(tmp1->is_ptr>1)
        {
            tmp1->is_ptr--;
        }
        else
        {
            assert(0);
        }
        a->merge_icode(tmp1);
        icode *opr_mov = pcompi->new_opr_icode("=", NULL, c->result, tmp1);
        a->merge_icode(opr_mov);
        a->result = pcompi->m_top_icodes->new_var_in_var_tmp_icode(tmp1);
        return a;
    }




}

class icode *  func_IAN_UNARY_EXPRESSION_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x904-unary_expression->unary_operator cast_expression
    //parent:
    // unary_expression--> INC_OP unary_expression
    // unary_expression--> DEC_OP unary_expression
    // unary_expression--> SIZEOF unary_expression
    // cast_expression--> unary_expression
    // assignment_expression--> unary_expression assignment_operator assignment_expression


    ///opr: & 求地址
    ///  * 指针求值
    ///
    ///  + 正号
    ///  - 负号
    ///  ~ 按位求反
    ///  ! 逻辑求反


    token_defs * unary_operator = tdefs->m_tk_elems[0];
    token_defs* unary_expr = tdefs->m_tk_elems[1];


    if(unary_operator->val_str=="*")
    {
        //指针求值，因为需要返回左值，其他都是右值。所以单独处理
        return in_ptr_expr(pcompi, tdefs, need_result_icode, result_ic);
    }





    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //return pcompi->ast_to_icode_op_b(tdefs, need_result_icode, a, result_ic, 0);


    std::string opr_name="";
    if(tdefs->m_tk_elems[0]->val_str=="&")
    {
        //此处是求地址 &c; 只有右操作符，没有左操作符
        //修改名字，方便后期使用
        opr_name = "address_of";
    }
    else if(tdefs->m_tk_elems[0]->val_str=="-")
    {
        ///因为- 负号 减号 是一样的，所以负号 改为negative，方便后期区分
        opr_name = "negative";
    }
    else if(tdefs->m_tk_elems[0]->val_str=="+")
    {
        ///因为+ 正号 加号 是一样的，所以正号 改为positive，方便后期区分
        opr_name = "positive";
    }
    else
    {
        opr_name = tdefs->m_tk_elems[0]->val_str;
    }



    icode *c = pcompi->ast_to_icode(unary_expr, 1);

    icode *b = pcompi->new_opr_icode(opr_name, NULL, c->result, NULL);


    a->merge_icode(c);
    if(need_result_icode)
    {
        if(result_ic)
        {
            b->result = result_ic;
            a->result = result_ic;
        }
        else
        {
            //此处还是需要临时变量，如果right是常量值
            //此处生成一个临时变量，用于传递结果？？？
            {
                icode * tmp = pcompi->new_temp_var();
                a->merge_icode(tmp);
                b->result = pcompi->new_ref_icode( tmp);
                tmp->set_width_from(c->result);
            }
        }

        a->result = b->result;
    }

    a->merge_icode(b);

    return a;
}



icode *func_opr_sizeof(comp_context* pcompi, token_defs *unary_expression, bool need_result_icode, icode *result_ic)
{
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;


    icode *b = pcompi->new_icode();
    b->m_type = ICODE_TYPE_EXP_OP;
    b->name = "sizeof";

    icode *c = pcompi->ast_to_icode(unary_expression, 1);

    ///----------------

    b->right = c->result;
    ///----------------


    a->merge_icode(c);
    if(need_result_icode)
    {
        if(result_ic)
        {
            b->result = result_ic;
        }
        else
        {
            //此处还是需要临时变量，如果right是常量值
            //此处生成一个临时变量，用于传递结果？？？
            {
                icode * tmp = pcompi->new_temp_var();
                a->merge_icode(tmp);
                b->result = pcompi->new_ref_icode( tmp);
                tmp->set_width_from(c->result);
            }
        }

        a->result = b->result;
    }

    a->merge_icode(b);

    return a;
}


class icode *  func_IAN_UNARY_EXPRESSION_5(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x905-unary_expression->SIZEOF unary_expression
    //parent:
    // unary_expression--> INC_OP unary_expression
    // unary_expression--> DEC_OP unary_expression
    // unary_expression--> SIZEOF unary_expression
    // cast_expression--> unary_expression
    // assignment_expression--> unary_expression assignment_operator assignment_expression


    return func_opr_sizeof(pcompi, tdefs->m_tk_elems[1], need_result_icode, result_ic);
}

class icode *  func_IAN_UNARY_EXPRESSION_6(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x906-unary_expression->SIZEOF '(' type_name ')'
    //parent:
    // unary_expression--> INC_OP unary_expression
    // unary_expression--> DEC_OP unary_expression
    // unary_expression--> SIZEOF unary_expression
    // cast_expression--> unary_expression
    // assignment_expression--> unary_expression assignment_operator assignment_expression

    return func_opr_sizeof(pcompi, tdefs->m_tk_elems[2], need_result_icode, result_ic);
}


class icode *  func_IAN_UNARY_EXPRESSION_7(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x907-unary_expression->ALIGNOF '(' type_name ')'
    //parent:
    // unary_expression--> INC_OP unary_expression
    // unary_expression--> DEC_OP unary_expression
    // unary_expression--> SIZEOF unary_expression
    // cast_expression--> unary_expression
    // assignment_expression--> unary_expression assignment_operator assignment_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *ALIGNOF=tdefs->m_tk_elems[0];
    //token_defs *'('=tdefs->m_tk_elems[1];
    //token_defs *type_name=tdefs->m_tk_elems[2];
    //token_defs *')'=tdefs->m_tk_elems[3];
    //icode *ALIGNOF_ic=pcompi->ast_to_icode(ALIGNOF);
    //icode *'('_ic=pcompi->ast_to_icode('(');
    //icode *type_name_ic=pcompi->ast_to_icode(type_name);
    //icode *')'_ic=pcompi->ast_to_icode(')');
    //a->merge_icode(ALIGNOF_ic);
    //a->merge_icode('('_ic);
    //a->merge_icode(type_name_ic);
    //a->merge_icode(')'_ic);
    assert(0);
    return a;
}


class icode *  func_IAN_UNARY_OPERATOR_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0xa01-unary_operator->'&'
    //parent:
    // unary_expression--> unary_operator cast_expression

    //this should never be called\n
    assert(0);
}
class icode *  func_IAN_UNARY_OPERATOR_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0xa02-unary_operator->'*'
    //parent:
    // unary_expression--> unary_operator cast_expression
    //this should never be called\n
    assert(0);
}
class icode *  func_IAN_UNARY_OPERATOR_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0xa03-unary_operator->'+'
    //parent:
    // unary_expression--> unary_operator cast_expression
    //this should never be called\n
    assert(0);
}
class icode *  func_IAN_UNARY_OPERATOR_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0xa04-unary_operator->'-'
    //parent:
    // unary_expression--> unary_operator cast_expression
    //this should never be called\n
    assert(0);

}
class icode *  func_IAN_UNARY_OPERATOR_5(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0xa05-unary_operator->'~'
    //parent:
    // unary_expression--> unary_operator cast_expression
    //this should never be called\n
    assert(0);

}
class icode *  func_IAN_UNARY_OPERATOR_6(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0xa06-unary_operator->'!'
    //parent:
    // unary_expression--> unary_operator cast_expression
    //this should never be called\n
    assert(0);

}
class icode *  func_IAN_CAST_EXPRESSION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0xb01-cast_expression->unary_expression
    //parent:
    // unary_expression--> unary_operator cast_expression
    // cast_expression--> '(' type_name ')' cast_expression
    // multiplicative_expression--> cast_expression
    // multiplicative_expression--> multiplicative_expression '*' cast_expression
    // multiplicative_expression--> multiplicative_expression '/' cast_expression
    // multiplicative_expression--> multiplicative_expression '%' cast_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}

class icode *  func_IAN_CAST_EXPRESSION_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0xb02-cast_expression->'(' type_name ')' cast_expression
    //parent:
    // unary_expression--> unary_operator cast_expression
    // cast_expression--> '(' type_name ')' cast_expression
    // multiplicative_expression--> cast_expression
    // multiplicative_expression--> multiplicative_expression '*' cast_expression
    // multiplicative_expression--> multiplicative_expression '/' cast_expression
    // multiplicative_expression--> multiplicative_expression '%' cast_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    if(!need_result_icode)
    {
        //如果不需要结果，则代码无作用
        return a;
    }

#if 0
    if(result_ic==NULL)
    {
        //此处需要生成临时变量
        icode *type_n = pcompi->new_var();
        type_n->m_type=ICODE_TYPE_DEF_VAR;
        pcompi->ast_to_icode(tdefs->m_tk_elems[1], 0, type_n);

        int is_exist = 0;
        icode *result_ic_n = pcompi->new_var(pcompi->get_temp_name(), type_n, is_exist );
        result_ic = pcompi->new_ref_icode(result_ic_n);
    }

    icode *cast_expr = pcompi->ast_to_icode(tdefs->m_tk_elems[3], 1, result_ic);
    a->merge_icode(cast_expr);

    if(!cast_expr->result->is_ref_equal(result_ic))
    {
        //返回值需要进一步添加
        icode * movi = pcompi->mov_icode(cast_expr->result, result_ic->result);
        a->merge_icode(movi);
    }
#else
    //此处需要生成临时变量
    // 1-新变量类型生成声明
    icode *type_n = pcompi->new_icode();
    type_n->m_type=ICODE_TYPE_DEF_VAR;
    pcompi->ast_to_icode(tdefs->m_tk_elems[1], 0, type_n);

    int is_exist = 0;
    icode *result_ic_n = pcompi->new_var(pcompi->get_temp_name(), type_n, is_exist );

    result_ic = pcompi->new_ref_icode(result_ic_n);

    icode *cast_expr = pcompi->ast_to_icode(tdefs->m_tk_elems[3], 1);
    a->merge_icode(cast_expr);


    a->merge_icode(result_ic_n);

    //返回值需要进一步添加
    icode * movi = pcompi->mov_icode(cast_expr->result, result_ic->result);
    a->merge_icode(movi);

#endif


    a->result = result_ic;

    return a;
}

class icode *  func_IAN_MULTIPLICATIVE_EXPRESSION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0xc01-multiplicative_expression->cast_expression
    //parent:
    // multiplicative_expression--> multiplicative_expression '*' cast_expression
    // multiplicative_expression--> multiplicative_expression '/' cast_expression
    // multiplicative_expression--> multiplicative_expression '%' cast_expression
    // additive_expression--> multiplicative_expression
    // additive_expression--> additive_expression '+' multiplicative_expression
    // additive_expression--> additive_expression '-' multiplicative_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}

class icode *  func_IAN_MULTIPLICATIVE_EXPRESSION_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0xc02-multiplicative_expression->multiplicative_expression '*' cast_expression
    //parent:
    // multiplicative_expression--> multiplicative_expression '*' cast_expression
    // multiplicative_expression--> multiplicative_expression '/' cast_expression
    // multiplicative_expression--> multiplicative_expression '%' cast_expression
    // additive_expression--> multiplicative_expression
    // additive_expression--> additive_expression '+' multiplicative_expression
    // additive_expression--> additive_expression '-' multiplicative_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    pcompi->ast_to_icode_a_op_b(tdefs, need_result_icode, a, result_ic);

    return a;
}

class icode *  func_IAN_MULTIPLICATIVE_EXPRESSION_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0xc03-multiplicative_expression->multiplicative_expression '/' cast_expression
    //parent:
    // multiplicative_expression--> multiplicative_expression '*' cast_expression
    // multiplicative_expression--> multiplicative_expression '/' cast_expression
    // multiplicative_expression--> multiplicative_expression '%' cast_expression
    // additive_expression--> multiplicative_expression
    // additive_expression--> additive_expression '+' multiplicative_expression
    // additive_expression--> additive_expression '-' multiplicative_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    pcompi->ast_to_icode_a_op_b(tdefs, need_result_icode, a, result_ic);

    return a;
}

class icode *  func_IAN_MULTIPLICATIVE_EXPRESSION_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0xc04-multiplicative_expression->multiplicative_expression '%' cast_expression
    //parent:
    // multiplicative_expression--> multiplicative_expression '*' cast_expression
    // multiplicative_expression--> multiplicative_expression '/' cast_expression
    // multiplicative_expression--> multiplicative_expression '%' cast_expression
    // additive_expression--> multiplicative_expression
    // additive_expression--> additive_expression '+' multiplicative_expression
    // additive_expression--> additive_expression '-' multiplicative_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    pcompi->ast_to_icode_a_op_b(tdefs, need_result_icode, a, result_ic);

    return a;
}
class icode *  func_IAN_ADDITIVE_EXPRESSION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0xd01-additive_expression->multiplicative_expression
    //parent:
    // additive_expression--> additive_expression '+' multiplicative_expression
    // additive_expression--> additive_expression '-' multiplicative_expression
    // shift_expression--> additive_expression
    // shift_expression--> shift_expression LEFT_OP additive_expression
    // shift_expression--> shift_expression RIGHT_OP additive_expression
    // shift_expression--> shift_expression ROTATE_LEFT_OP additive_expression
    // shift_expression--> shift_expression ROTATE_RIGHT_OP additive_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_ADDITIVE_EXPRESSION_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0xd02-additive_expression->additive_expression '+' multiplicative_expression
    //parent:
    // additive_expression--> additive_expression '+' multiplicative_expression
    // additive_expression--> additive_expression '-' multiplicative_expression
    // shift_expression--> additive_expression
    // shift_expression--> shift_expression LEFT_OP additive_expression
    // shift_expression--> shift_expression RIGHT_OP additive_expression
    // shift_expression--> shift_expression ROTATE_LEFT_OP additive_expression
    // shift_expression--> shift_expression ROTATE_RIGHT_OP additive_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    pcompi->ast_to_icode_a_op_b(tdefs, need_result_icode, a, result_ic);

    return a;
}
class icode *  func_IAN_ADDITIVE_EXPRESSION_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0xd03-additive_expression->additive_expression '-' multiplicative_expression
    //parent:
    // additive_expression--> additive_expression '+' multiplicative_expression
    // additive_expression--> additive_expression '-' multiplicative_expression
    // shift_expression--> additive_expression
    // shift_expression--> shift_expression LEFT_OP additive_expression
    // shift_expression--> shift_expression RIGHT_OP additive_expression
    // shift_expression--> shift_expression ROTATE_LEFT_OP additive_expression
    // shift_expression--> shift_expression ROTATE_RIGHT_OP additive_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    pcompi->ast_to_icode_a_op_b(tdefs, need_result_icode, a, result_ic);

    return a;
}
class icode *  func_IAN_SHIFT_EXPRESSION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0xe01-shift_expression->additive_expression
    //parent:
    // shift_expression--> shift_expression LEFT_OP additive_expression
    // shift_expression--> shift_expression RIGHT_OP additive_expression
    // shift_expression--> shift_expression ROTATE_LEFT_OP additive_expression
    // shift_expression--> shift_expression ROTATE_RIGHT_OP additive_expression
    // relational_expression--> shift_expression
    // relational_expression--> relational_expression '<' shift_expression
    // relational_expression--> relational_expression '>' shift_expression
    // relational_expression--> relational_expression LE_OP shift_expression
    // relational_expression--> relational_expression GE_OP shift_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_SHIFT_EXPRESSION_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0xe02-shift_expression->shift_expression LEFT_OP additive_expression
    //parent:
    // shift_expression--> shift_expression LEFT_OP additive_expression
    // shift_expression--> shift_expression RIGHT_OP additive_expression
    // shift_expression--> shift_expression ROTATE_LEFT_OP additive_expression
    // shift_expression--> shift_expression ROTATE_RIGHT_OP additive_expression
    // relational_expression--> shift_expression
    // relational_expression--> relational_expression '<' shift_expression
    // relational_expression--> relational_expression '>' shift_expression
    // relational_expression--> relational_expression LE_OP shift_expression
    // relational_expression--> relational_expression GE_OP shift_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    pcompi->ast_to_icode_a_op_b(tdefs, need_result_icode, a, result_ic);

    return a;
}
class icode *  func_IAN_SHIFT_EXPRESSION_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0xe03-shift_expression->shift_expression RIGHT_OP additive_expression
    //parent:
    // shift_expression--> shift_expression LEFT_OP additive_expression
    // shift_expression--> shift_expression RIGHT_OP additive_expression
    // shift_expression--> shift_expression ROTATE_LEFT_OP additive_expression
    // shift_expression--> shift_expression ROTATE_RIGHT_OP additive_expression
    // relational_expression--> shift_expression
    // relational_expression--> relational_expression '<' shift_expression
    // relational_expression--> relational_expression '>' shift_expression
    // relational_expression--> relational_expression LE_OP shift_expression
    // relational_expression--> relational_expression GE_OP shift_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    pcompi->ast_to_icode_a_op_b(tdefs, need_result_icode, a, result_ic);

    return a;
}
class icode *  func_IAN_SHIFT_EXPRESSION_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0xe04-shift_expression->shift_expression ROTATE_LEFT_OP additive_expression
    //parent:
    // shift_expression--> shift_expression LEFT_OP additive_expression
    // shift_expression--> shift_expression RIGHT_OP additive_expression
    // shift_expression--> shift_expression ROTATE_LEFT_OP additive_expression
    // shift_expression--> shift_expression ROTATE_RIGHT_OP additive_expression
    // relational_expression--> shift_expression
    // relational_expression--> relational_expression '<' shift_expression
    // relational_expression--> relational_expression '>' shift_expression
    // relational_expression--> relational_expression LE_OP shift_expression
    // relational_expression--> relational_expression GE_OP shift_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    pcompi->ast_to_icode_a_op_b(tdefs, need_result_icode, a, result_ic);

    return a;
}
class icode *  func_IAN_SHIFT_EXPRESSION_5(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0xe05-shift_expression->shift_expression ROTATE_RIGHT_OP additive_expression
    //parent:
    // shift_expression--> shift_expression LEFT_OP additive_expression
    // shift_expression--> shift_expression RIGHT_OP additive_expression
    // shift_expression--> shift_expression ROTATE_LEFT_OP additive_expression
    // shift_expression--> shift_expression ROTATE_RIGHT_OP additive_expression
    // relational_expression--> shift_expression
    // relational_expression--> relational_expression '<' shift_expression
    // relational_expression--> relational_expression '>' shift_expression
    // relational_expression--> relational_expression LE_OP shift_expression
    // relational_expression--> relational_expression GE_OP shift_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    pcompi->ast_to_icode_a_op_b(tdefs, need_result_icode, a, result_ic);

    return a;
}
class icode *  func_IAN_RELATIONAL_EXPRESSION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0xf01-relational_expression->shift_expression
    //parent:
    // relational_expression--> relational_expression '<' shift_expression
    // relational_expression--> relational_expression '>' shift_expression
    // relational_expression--> relational_expression LE_OP shift_expression
    // relational_expression--> relational_expression GE_OP shift_expression
    // equality_expression--> relational_expression
    // equality_expression--> equality_expression EQ_OP relational_expression
    // equality_expression--> equality_expression NE_OP relational_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_RELATIONAL_EXPRESSION_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0xf02-relational_expression->relational_expression '<' shift_expression
    //parent:
    // relational_expression--> relational_expression '<' shift_expression
    // relational_expression--> relational_expression '>' shift_expression
    // relational_expression--> relational_expression LE_OP shift_expression
    // relational_expression--> relational_expression GE_OP shift_expression
    // equality_expression--> relational_expression
    // equality_expression--> equality_expression EQ_OP relational_expression
    // equality_expression--> equality_expression NE_OP relational_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    pcompi->ast_to_icode_a_op_b(tdefs, need_result_icode, a, result_ic);

    return a;
}
class icode *  func_IAN_RELATIONAL_EXPRESSION_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0xf03-relational_expression->relational_expression '>' shift_expression
    //parent:
    // relational_expression--> relational_expression '<' shift_expression
    // relational_expression--> relational_expression '>' shift_expression
    // relational_expression--> relational_expression LE_OP shift_expression
    // relational_expression--> relational_expression GE_OP shift_expression
    // equality_expression--> relational_expression
    // equality_expression--> equality_expression EQ_OP relational_expression
    // equality_expression--> equality_expression NE_OP relational_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    pcompi->ast_to_icode_a_op_b(tdefs, need_result_icode, a, result_ic);

    return a;
}
class icode *  func_IAN_RELATIONAL_EXPRESSION_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0xf04-relational_expression->relational_expression LE_OP shift_expression
    //parent:
    // relational_expression--> relational_expression '<' shift_expression
    // relational_expression--> relational_expression '>' shift_expression
    // relational_expression--> relational_expression LE_OP shift_expression
    // relational_expression--> relational_expression GE_OP shift_expression
    // equality_expression--> relational_expression
    // equality_expression--> equality_expression EQ_OP relational_expression
    // equality_expression--> equality_expression NE_OP relational_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    pcompi->ast_to_icode_a_op_b(tdefs, need_result_icode, a, result_ic);

    return a;
}
class icode *  func_IAN_RELATIONAL_EXPRESSION_5(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0xf05-relational_expression->relational_expression GE_OP shift_expression
    //parent:
    // relational_expression--> relational_expression '<' shift_expression
    // relational_expression--> relational_expression '>' shift_expression
    // relational_expression--> relational_expression LE_OP shift_expression
    // relational_expression--> relational_expression GE_OP shift_expression
    // equality_expression--> relational_expression
    // equality_expression--> equality_expression EQ_OP relational_expression
    // equality_expression--> equality_expression NE_OP relational_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    pcompi->ast_to_icode_a_op_b(tdefs, need_result_icode, a, result_ic);

    return a;
}
class icode *  func_IAN_EQUALITY_EXPRESSION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1001-equality_expression->relational_expression
    //parent:
    // equality_expression--> equality_expression EQ_OP relational_expression
    // equality_expression--> equality_expression NE_OP relational_expression
    // and_expression--> equality_expression
    // and_expression--> and_expression '&' equality_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_EQUALITY_EXPRESSION_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1002-equality_expression->equality_expression EQ_OP relational_expression
    //parent:
    // equality_expression--> equality_expression EQ_OP relational_expression
    // equality_expression--> equality_expression NE_OP relational_expression
    // and_expression--> equality_expression
    // and_expression--> and_expression '&' equality_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    pcompi->ast_to_icode_a_op_b(tdefs, need_result_icode, a, result_ic);

    return a;
}
class icode *  func_IAN_EQUALITY_EXPRESSION_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1003-equality_expression->equality_expression NE_OP relational_expression
    //parent:
    // equality_expression--> equality_expression EQ_OP relational_expression
    // equality_expression--> equality_expression NE_OP relational_expression
    // and_expression--> equality_expression
    // and_expression--> and_expression '&' equality_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    pcompi->ast_to_icode_a_op_b(tdefs, need_result_icode, a, result_ic);

    return a;
}
class icode *  func_IAN_AND_EXPRESSION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1101-and_expression->equality_expression
    //parent:
    // and_expression--> and_expression '&' equality_expression
    // exclusive_or_expression--> and_expression
    // exclusive_or_expression--> exclusive_or_expression '^' and_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_AND_EXPRESSION_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1102-and_expression->and_expression '&' equality_expression
    //parent:
    // and_expression--> and_expression '&' equality_expression
    // exclusive_or_expression--> and_expression
    // exclusive_or_expression--> exclusive_or_expression '^' and_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    pcompi->ast_to_icode_a_op_b(tdefs, need_result_icode, a, result_ic);

    return a;
}
class icode *  func_IAN_EXCLUSIVE_OR_EXPRESSION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1201-exclusive_or_expression->and_expression
    //parent:
    // exclusive_or_expression--> exclusive_or_expression '^' and_expression
    // inclusive_or_expression--> exclusive_or_expression
    // inclusive_or_expression--> inclusive_or_expression '|' exclusive_or_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_EXCLUSIVE_OR_EXPRESSION_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1202-exclusive_or_expression->exclusive_or_expression '^' and_expression
    //parent:
    // exclusive_or_expression--> exclusive_or_expression '^' and_expression
    // inclusive_or_expression--> exclusive_or_expression
    // inclusive_or_expression--> inclusive_or_expression '|' exclusive_or_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    pcompi->ast_to_icode_a_op_b(tdefs, need_result_icode, a, result_ic);

    return a;
}
class icode *  func_IAN_INCLUSIVE_OR_EXPRESSION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1301-inclusive_or_expression->exclusive_or_expression
    //parent:
    // inclusive_or_expression--> inclusive_or_expression '|' exclusive_or_expression
    // logical_and_expression--> inclusive_or_expression
    // logical_and_expression--> logical_and_expression AND_OP inclusive_or_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_INCLUSIVE_OR_EXPRESSION_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1302-inclusive_or_expression->inclusive_or_expression '|' exclusive_or_expression
    //parent:
    // inclusive_or_expression--> inclusive_or_expression '|' exclusive_or_expression
    // logical_and_expression--> inclusive_or_expression
    // logical_and_expression--> logical_and_expression AND_OP inclusive_or_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    pcompi->ast_to_icode_a_op_b(tdefs, need_result_icode, a, result_ic);

    return a;
}
class icode *  func_IAN_LOGICAL_AND_EXPRESSION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1401-logical_and_expression->inclusive_or_expression
    //parent:
    // logical_and_expression--> logical_and_expression AND_OP inclusive_or_expression
    // logical_or_expression--> logical_and_expression
    // logical_or_expression--> logical_or_expression OR_OP logical_and_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_LOGICAL_AND_EXPRESSION_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1402-logical_and_expression->logical_and_expression AND_OP inclusive_or_expression
    //parent:
    // logical_and_expression--> logical_and_expression AND_OP inclusive_or_expression
    // logical_or_expression--> logical_and_expression
    // logical_or_expression--> logical_or_expression OR_OP logical_and_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    pcompi->ast_to_icode_a_op_b(tdefs, need_result_icode, a, result_ic);

    return a;
}
class icode *  func_IAN_LOGICAL_OR_EXPRESSION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1501-logical_or_expression->logical_and_expression
    //parent:
    // logical_or_expression--> logical_or_expression OR_OP logical_and_expression
    // conditional_expression--> logical_or_expression
    // conditional_expression--> logical_or_expression '?' expression ':' conditional_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_LOGICAL_OR_EXPRESSION_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1502-logical_or_expression->logical_or_expression OR_OP logical_and_expression
    //parent:
    // logical_or_expression--> logical_or_expression OR_OP logical_and_expression
    // conditional_expression--> logical_or_expression
    // conditional_expression--> logical_or_expression '?' expression ':' conditional_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    pcompi->ast_to_icode_a_op_b(tdefs, need_result_icode, a, result_ic);

    return a;
}
class icode *  func_IAN_CONDITIONAL_EXPRESSION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1601-conditional_expression->logical_or_expression
    //parent:
    // conditional_expression--> logical_or_expression '?' expression ':' conditional_expression
    // assignment_expression--> conditional_expression
    // constant_expression--> conditional_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_CONDITIONAL_EXPRESSION_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1602-conditional_expression->logical_or_expression '?' expression ':' conditional_expression
    //parent:
    // conditional_expression--> logical_or_expression '?' expression ':' conditional_expression
    // assignment_expression--> conditional_expression
    // constant_expression--> conditional_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *logical_or_expression=tdefs->m_tk_elems[0];
    //token_defs *'?'=tdefs->m_tk_elems[1];
    //token_defs *expression=tdefs->m_tk_elems[2];
    //token_defs *':'=tdefs->m_tk_elems[3];
    //token_defs *conditional_expression=tdefs->m_tk_elems[4];
    //icode *logical_or_expression_ic=pcompi->ast_to_icode(logical_or_expression);
    //icode *'?'_ic=pcompi->ast_to_icode('?');
    //icode *expression_ic=pcompi->ast_to_icode(expression);
    //icode *':'_ic=pcompi->ast_to_icode(':');
    //icode *conditional_expression_ic=pcompi->ast_to_icode(conditional_expression);
    //a->merge_icode(logical_or_expression_ic);
    //a->merge_icode('?'_ic);
    //a->merge_icode(expression_ic);
    //a->merge_icode(':'_ic);
    //a->merge_icode(conditional_expression_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_ASSIGNMENT_EXPRESSION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1701-assignment_expression->conditional_expression
    //parent:
    // generic_selection--> GENERIC '(' assignment_expression ',' generic_assoc_list ')'
    // generic_association--> type_name ':' assignment_expression
    // generic_association--> DEFAULT ':' assignment_expression
    // argument_expression_list--> assignment_expression
    // argument_expression_list--> argument_expression_list ',' assignment_expression
    // assignment_expression--> unary_expression assignment_operator assignment_expression
    // expression--> assignment_expression
    // expression--> expression ',' assignment_expression
    // direct_declarator_array--> direct_declarator_array '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' STATIC assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' assignment_expression ']'
    // direct_abstract_declarator--> '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> '[' STATIC assignment_expression ']'
    // direct_abstract_declarator--> '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_abstract_declarator--> '[' type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> '[' assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' assignment_expression ']'
    // initializer--> assignment_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_ASSIGNMENT_EXPRESSION_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1702-assignment_expression->unary_expression assignment_operator assignment_expression
    //parent:
    // generic_selection--> GENERIC '(' assignment_expression ',' generic_assoc_list ')'
    // generic_association--> type_name ':' assignment_expression
    // generic_association--> DEFAULT ':' assignment_expression
    // argument_expression_list--> assignment_expression
    // argument_expression_list--> argument_expression_list ',' assignment_expression
    // assignment_expression--> unary_expression assignment_operator assignment_expression
    // expression--> assignment_expression
    // expression--> expression ',' assignment_expression
    // direct_declarator_array--> direct_declarator_array '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' STATIC assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' type_qualifier_list assignment_expression ']'
    // direct_declarator_array--> direct_declarator_array '[' assignment_expression ']'
    // direct_abstract_declarator--> '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> '[' STATIC assignment_expression ']'
    // direct_abstract_declarator--> '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_abstract_declarator--> '[' type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> '[' assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' type_qualifier_list STATIC assignment_expression ']'
    // direct_abstract_declarator--> direct_abstract_declarator '[' assignment_expression ']'
    // initializer--> assignment_expression
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;

    assert(tdefs->m_tk_elems.size()==3);
    token_defs* unary_expression = tdefs->m_tk_elems[0];
    token_defs* assignment_operator = tdefs->m_tk_elems[1];
    token_defs* assignment_expression = tdefs->m_tk_elems[2];


    //等号左边值
    icode *unary_ic = pcompi->ast_to_icode(unary_expression, 1);
    a->merge_icode(unary_ic);


    //等号右边值

    icode *ret_ic = NULL;
    if(assignment_operator->val_str=="=")
    {
        ret_ic = pcompi->ast_to_icode(assignment_expression, 1, unary_ic->result);
    }
    else
    {
        //算符不一定是等号，可能是 += /=
        ret_ic = pcompi->ast_to_icode(assignment_expression, 1);
    }

    a->merge_icode(ret_ic);


    if(!ret_ic->result->is_ref_equal(unary_ic->result))
    {
        icode *b = pcompi->new_icode();
        b->m_type = ICODE_TYPE_EXP_OP;
        b->name = assignment_operator->val_str;

        /// 2020.8.9  = += *=  /=等算符，原来是 left, result。
        /// 改为 right, left, result
        ///
        /// 2020.8.19 赋值语句，改为left=NULL.
        /// 因为，如果语句： a[3]=5; left=a[3],result=a[3], right=4;
        /// 则会对a[3]求值2次，导致计算复杂。
        ///
        ///
        //b->left = ret_ic->result;
        b->right = ret_ic->result;
        //b->left = unary_ic->result;
        b->left = NULL;
        b->result = unary_ic->result;
        a->merge_icode(b);
        if(need_result_icode)
        {
            a->result = b->result;
        }

        //赋值语句，如果右值为临时变量，则赋值完成后，可以释放此变量
        icode * res_tt = pcompi->release_tmp_if_need(ret_ic->result);
        a->merge_icode(res_tt);
    }
    else
    {
        if(need_result_icode)
        {
            a->result = unary_ic->result;
        }
    }

    return a;
}


class icode *  func_IAN_ASSIGNMENT_OPERATOR_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1801-assignment_operator->'='
    //parent:
    // assignment_expression--> unary_expression assignment_operator assignment_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_ASSIGNMENT_OPERATOR_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1802-assignment_operator->MUL_ASSIGN
    //parent:
    // assignment_expression--> unary_expression assignment_operator assignment_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_ASSIGNMENT_OPERATOR_3(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1803-assignment_operator->DIV_ASSIGN
    //parent:
    // assignment_expression--> unary_expression assignment_operator assignment_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_ASSIGNMENT_OPERATOR_4(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1804-assignment_operator->MOD_ASSIGN
    //parent:
    // assignment_expression--> unary_expression assignment_operator assignment_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_ASSIGNMENT_OPERATOR_5(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1805-assignment_operator->ADD_ASSIGN
    //parent:
    // assignment_expression--> unary_expression assignment_operator assignment_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_ASSIGNMENT_OPERATOR_6(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1806-assignment_operator->SUB_ASSIGN
    //parent:
    // assignment_expression--> unary_expression assignment_operator assignment_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_ASSIGNMENT_OPERATOR_7(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1807-assignment_operator->LEFT_ASSIGN
    //parent:
    // assignment_expression--> unary_expression assignment_operator assignment_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_ASSIGNMENT_OPERATOR_8(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1808-assignment_operator->RIGHT_ASSIGN
    //parent:
    // assignment_expression--> unary_expression assignment_operator assignment_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_ASSIGNMENT_OPERATOR_9(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1809-assignment_operator->AND_ASSIGN
    //parent:
    // assignment_expression--> unary_expression assignment_operator assignment_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_ASSIGNMENT_OPERATOR_10(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x180a-assignment_operator->XOR_ASSIGN
    //parent:
    // assignment_expression--> unary_expression assignment_operator assignment_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_ASSIGNMENT_OPERATOR_11(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x180b-assignment_operator->OR_ASSIGN
    //parent:
    // assignment_expression--> unary_expression assignment_operator assignment_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_EXPRESSION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1901-expression->assignment_expression
    //parent:
    // primary_expression--> '(' expression ')'
    // postfix_expression--> postfix_expression '[' expression ']'
    // conditional_expression--> logical_or_expression '?' expression ':' conditional_expression
    // expression--> expression ',' assignment_expression
    // expression_statement--> expression ';'
    // selection_statement--> IF '(' expression ')' statement ELSE statement
    // selection_statement--> IF '(' expression ')' statement
    // selection_statement--> SWITCH '(' expression ')' statement
    // iteration_statement--> WHILE '(' expression ')' statement
    // iteration_statement--> DO statement WHILE '(' expression ')' ';'
    // iteration_statement--> FOR '(' expression_statement expression_statement expression ')' statement
    // iteration_statement--> FOR '(' declaration expression_statement expression ')' statement
    // jump_statement--> RETURN expression ';'
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}
class icode *  func_IAN_EXPRESSION_2(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1902-expression->expression ',' assignment_expression
    //parent:
    // primary_expression--> '(' expression ')'
    // postfix_expression--> postfix_expression '[' expression ']'
    // conditional_expression--> logical_or_expression '?' expression ':' conditional_expression
    // expression--> expression ',' assignment_expression
    // expression_statement--> expression ';'
    // selection_statement--> IF '(' expression ')' statement ELSE statement
    // selection_statement--> IF '(' expression ')' statement
    // selection_statement--> SWITCH '(' expression ')' statement
    // iteration_statement--> WHILE '(' expression ')' statement
    // iteration_statement--> DO statement WHILE '(' expression ')' ';'
    // iteration_statement--> FOR '(' expression_statement expression_statement expression ')' statement
    // iteration_statement--> FOR '(' declaration expression_statement expression ')' statement
    // jump_statement--> RETURN expression ';'
    icode *a = pcompi->new_icode();
    a->m_type=ICODE_TYPE_BLOCK;
    //token_defs *expression=tdefs->m_tk_elems[0];
    //token_defs *','=tdefs->m_tk_elems[1];
    //token_defs *assignment_expression=tdefs->m_tk_elems[2];
    //icode *expression_ic=pcompi->ast_to_icode(expression);
    //icode *','_ic=pcompi->ast_to_icode(',');
    //icode *assignment_expression_ic=pcompi->ast_to_icode(assignment_expression);
    //a->merge_icode(expression_ic);
    //a->merge_icode(','_ic);
    //a->merge_icode(assignment_expression_ic);
    assert(0);
    return a;
}
class icode *  func_IAN_CONSTANT_EXPRESSION_1(class comp_context* pcompi, class token_defs* tdefs, bool need_result_icode, class icode* result_ic)
{
    //0x1a01-constant_expression->conditional_expression
    //parent:
    // struct_declarator--> ':' constant_expression
    // struct_declarator--> declarator ':' constant_expression
    // enumerator--> enumeration_constant '=' constant_expression
    // alignment_specifier--> ALIGNAS '(' constant_expression ')'
    // designator--> '[' constant_expression ']'
    // static_assert_declaration--> STATIC_ASSERT '(' constant_expression ',' STRING_LITERAL ')' ';'
    // labeled_statement--> CASE constant_expression ':' statement
    // function_attribute1--> USING constant_expression
    // function_attribute1--> INTERRUPT constant_expression
    return pcompi->ast_to_icode(tdefs,need_result_icode, result_ic);
}

}//namespace end
