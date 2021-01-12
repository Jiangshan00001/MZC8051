#ifndef ICODE_CONST_FOLDER_H
#define ICODE_CONST_FOLDER_H

#include <vector>
#include "icode_visitor.h"

/// 常量折叠 和一次使用变量传播同时进行
/// 例如：
/// tmp1=1+2;
/// tmp2=tmp1+3;
/// int a = tmp2;
/// 此时，tmp1只赋值1次，使用一次，且赋值为常量，则可替换为：
/// tmp2=3+3;
/// int a = tmp2;
/// 此时，tmp2只赋值1次，使用一次，且赋值为常量，则可替换为：
/// int a = 6;
///
/// 需要循环遍历多次，直到无法折叠为止
/// 然后常量，需要重新计算长度 refresh_const_width???
/// 需要查找记录每个变量的被读写次数？？？
class icode_const_folder : public icode_visitor
{
public:
    icode_const_folder();
    virtual ~icode_const_folder();



    void execute(icodes* ics);

    virtual int process_one_icode(class icode *ic, std::vector<class icode *> &parent, int index, void *user_data, class icode *iparent);

    std::vector<class icode*> m_icodes;

    //常量折叠后，需要清理之前申请的，现在已经不用的临时变量
    int second_cleanup_tmp_var();
    int first_folder(icode *ic, std::vector<icode *> &parent, int index);


public:

    class icode * const_folder_opr(class icode *ic, bool &can_folder);
    bool is_const_ref(icode *ic);
    long long iconst_opr(icode *ic, bool &can_folder);
    double fconst_opr(icode *ic, bool &can_folder);
};


#endif // ICODE_CONST_FOLDER_H
