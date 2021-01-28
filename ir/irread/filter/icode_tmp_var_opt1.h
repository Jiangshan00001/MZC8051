#ifndef ICODE_TMP_VAR_OPT1_H
#define ICODE_TMP_VAR_OPT1_H

#include "icode_visitor.h"




/****
 *
 *
 *
 *
 * sfr PSW = 0xD0 ;
sbit CY = PSW ^ 7 ;
---
def_var: $PSW,i8, SFR(1) ;
opr: "init", null;, iconst:0xd0;, %PSW;
def_var: $CY,i1, SBIT(1) ;
def_var_tmp: $TMP_528515384,i8;
opr: "^", %PSW;, iconst:0x7;, %TMP_528515384;
opr: "init", null;, %TMP_528515384;, %CY;
---
需要一个filter。将类型：
opr "opr", left, right, result_tmp;
opr: "init", NULL, result_tmp,result2
类型的result_tmp去掉.
或者：
opr "opr", left, right, result_tmp;
opr: "=", NULL, result_tmp,result2
类型的result_tmp去掉。
---


*/

///
/// \brief The icode_tmp_var_opt1 class
///
///
///
///
///
///
class icode_tmp_var_opt1 : public icode_visitor
{
public:
    icode_tmp_var_opt1();

    int process_one_icode(class icode *ic, std::vector<class icode *> &parent, int index, void *user_data, class icode *iparent);

    int process_find1( icode *ic, std::vector< icode *> &parent, int index, icode *iparent);
    int process_find2( icode *ic, std::vector< icode *> &parent, int index, icode *iparent);

    void execute(icodes *ics);


private:
    icode *m_replaced_to_var;
    icode *m_be_replaced_var;

};

#endif // ICODE_TMP_VAR_OPT1_H
