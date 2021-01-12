// $Id$
/** \file expression.h Implements an example calculator class group. */

#ifndef COMP_CONTEXT_H
#define COMP_CONTEXT_H

#include <map>
#include <vector>
#include <ostream>
#include <stdexcept>
#include <cmath>
#include <vector>
#include "icode_manage.h"


class icode;
namespace NS_C2IR{


    class token_defs;
    class Driver;

    class comp_context:public icode_manage
	{
    public:
        comp_context();
        virtual ~comp_context();
    public:

        ///
        /// \brief ast_to_icode 自动生成函数，用于解码token_defs转为icode
        /// \param tdefs
        /// \param need_result_icode
        /// \param result_ic
        /// \return
        ///
        icode * ast_to_icode(token_defs* tdefs, bool need_result_icode=true, icode *result_ic=NULL);

        ///
        /// \brief ast_to_icode_elem
        /// \param tdefs
        /// \param need_result_icode
        /// \param result_ic
        /// \return
        ///
        icode * ast_to_icode_elem(token_defs* tdefs, bool need_result_icode, icode *result_ic);
        icode * ast_to_icode_ast(token_defs* tdefs, bool need_result_icode, icode *result_ic);


    public:
        ///
        /// 用户定义函数，用于在start标记符时，处理所有的token_defs
        void parse_start_token(token_defs & start_tk);

        void clearExpressions();


		
public:
    //for lex
    int check_type(std::string text1);



public:
    ///当前函数，在函数名称获取时需要用到
    icode *m_curr_func;


    public:
    icode *new_ref_icode(icode *to_ref);

public:
    Driver *mp_driver;

    int ast_to_icode_func_decl(token_defs *declaration_specifiers, token_defs *declarator, icode *ret, std::string &func_name);


    int correct_initializer_width_from_declarator(icode *var, icode *initializer);
    icode *new_copy_icode_gen(icode *from, icode *to);
    icode *release_tmp_if_need(icode *c);
    std::string get_func_ret_var_name(std::string func_name);
    icode *new_temp_ptr_var(icode *in_ptr_type);
    icode *mov_icode(icode *left, icode *result);
    icode *new_var_in_var_icode(icode *to_ref);
    icode *ast_to_icode_a_op_b(token_defs *tdefs, bool need_result_icode, icode *ret, icode *result_ic);
    icode *new_jnz_icode(icode *result, icode *labeled_block, std::string jz_str, ICODE_TYPE label_start_end_ref=ICODE_TYPE_LABELED_BLOCK_START_REF);
    icode *new_jmp_icode(icode *labeled_block, ICODE_TYPE label_start_end_ref=ICODE_TYPE_LABELED_BLOCK_START_REF);
    icode *ast_to_icode_func_definition(token_defs *tdefs, bool need_result_icode, icode *ret);

    public://function from yy
        int add_function(token_defs *func);
        int add_declaration(token_defs *declaration);


        ///如果此变量被设置，则只生成语法树
        int m_just_ret_tree;
        std::string m_yy_tree;

        std::string token_to_tree(token_defs *tdefs);


    };

}

#endif // EXPRESSION_H
