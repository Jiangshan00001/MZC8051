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
#include "asm_funcs.h"

namespace NS_AMS8051HEX{

	class icode;
    class token_defs;
    class Driver;

    class comp_context
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



	icode* new_icode();
		icode* new_icode(int itype);

public:
    Driver *mp_driver;


        ///如果此变量被设置，则只生成语法树
        int m_just_ret_tree;
        std::string m_yy_tree;

        std::string token_to_tree(token_defs *tdefs);

        icode * m_top_icode;
    };

}

#endif // EXPRESSION_H
