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
namespace NS_IR2ICODE{


    class token_defs;
    class Driver;

    class comp_context:public icode_manage
	{
    public:
        comp_context(int target_typ);
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
    ///当前函数，在函数名称获取时需要用到
    icode *m_curr_func;



public:
    Driver *mp_driver;



    public://function from yy

        ///
        /// 用户定义函数，用于在start标记符时，处理所有的token_defs
        void add_translation_unit(token_defs & start_tk);

    };

}

#endif // EXPRESSION_H
