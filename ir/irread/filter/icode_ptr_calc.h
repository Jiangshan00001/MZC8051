#ifndef ICODE_PTR_CALC_H
#define ICODE_PTR_CALC_H

#include <vector>
#include <string>

#include <icode_visitor.h>


///
/// \brief The icode_ptr_calc class
/// 此类引入指针的计算
/// 将原来的数组访问icode，拆解为指针计算和指针访问：
/// int a[5];
///  a[4]=4;--->
/// 将a[4]=4的icode，拆解为：
/// var1=a;
/// var2=4*2;
/// var1=var1+var2;
/// *var1=4;
///
/// 理论上此filter可的多次运行对icode无影响
///
/// 2020.9.8 重写此类，改为集成icode_visitor
///
///
/// \todo 此处需要处理数组中是指针的问题：int * a[2][4]; a[1][2][3]的访问？？？
///
class icode_ptr_calc:public icode_visitor
{
public:
    icode_ptr_calc();
    ///查找所有指针，将指针替换为实际的计算
    /// OPR: =, SYM_REF(name:bb, ptr:-1, ptr_s:ICONST(0x3,8,3d), num:9);, null;, SYM_REF(name:b, num:52)
    ///
    /// tmp_var2= ICONST(0x3,8,3d) * 2
    /// tmp_var1= SYM_REF(name:bb, ptr:0, ptr_s:null, num:9) + tmp_var2
    /// OPR: =, SYM_REF(name:tmp_var1, ptr:-1, ptr_s:null, num:9);, null;, SYM_REF(name:b, num:52)
    /// res(tmp_var1)
    /// res(tmp_var2)
    ///
    ///
    ///
    ///

    //bool process_one_icode(class icode *ic, std::vector<class icode *> &parent, int index, void *user_data, class icode *iparent);

    int process_one_icode(class icode * ic, std::vector<class icode *> &parent, int index, void *user_data, class icode *iparent);


    //此处是生成的icodes
    std::vector<class icode*> m_icodes;
    //此处是需要代替原来的ref的结果
    class icode * m_icode_result;

    ///通过数组的方式来访问数组
    ///
    ///
    ///
    int process_array_result(icode *ic, std::vector<icode *> &parent, int index, void *user_data, icode *iparent);

    ///
    /// \brief process_ptr_result 通过数组的方式来访问指针
    /// \param ic
    /// \param parent
    /// \param index
    /// \param user_data
    /// \param iparent
    /// \return
    ///
    /// int *a;
    /// a[2]=3;
    /// 此时需要生成的icode代码：
    /// int *temp2;
    /// temp2=a;
    /// temp2 += 2*2;
    /// *temp2 = 3;
    ///
    /// int **a;
    /// a[1][2]=3;
    /// 生成的代码：
    /// int *temp2;
    ///
    ///
    int process_ptr_result(icode *ic, std::vector<icode *> &parent, int index, void *user_data, icode *iparent);

};

#endif // ICODE_PTR_CALC_H
