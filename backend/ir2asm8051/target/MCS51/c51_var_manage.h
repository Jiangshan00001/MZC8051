#ifndef C51_VAR_MANAGE_H
#define C51_VAR_MANAGE_H
#include <vector>
#include <string>
#include <map>
#include "c51_addr.h"
#include "mem_alloc.h"
/// stc8 内部扩展ram：
/// pdata 0-0xff 读写： movx A, @Ri  movx @Ri, A.
/// xdata 0-0xffff 读写： movx A, @DPTR; movx @DPTR, A
/// pdata xdata都是扩展的ram，区别是pdata是低256字节，可以用Ri保存地址，xdata包括pdata
/// data :0x00->0x7f.  stc8 的128byte ram地址 data: 可直接访问也可以间接访问： .  其中00-20h为寄存器组Ri 30h-7fh为用户区
/// idata :0x80-0xff.  stc8 的128-256的ram地址 idata:  只能间接访问：. 因为直接访问为sfr。
///  idata访问： mov a, @Ri; mov @Ri, A;
///  sfr访问： 只能直接访问，因为和idata地址重合，只能通过寻址方式区分 mov A, direct;  mov direct, A;
/// stc8 的sfr 地址0x80->0xff 只能直接寻址方式访问
/// stc8 的bit寻址：ram的20h->2fh  16个寄存器可位寻址，对应位地址：00-7fh
/// stc8 的bit寻址：ram中sfr，地址能被8整除的16个寄存器可位寻址，对应位地址:0x80-0xff
/// ===================
/// sfr中，ACC->e0h B->f0h sp->81h dpl->82h dph->83h
///


///
/// \brief The c51_var_manage class
///
///
///
/// \todo 变量范围：如果变量int a; &a;被取地址，则范围扩展到函数级别，因为无法确定地址哪里被使用
///
///
class c51_var_manage
{
public:
    c51_var_manage(class icodes *mcontext);
    int process(std::vector<class icode *>& ic);
private:
    ///2020.8.10 添加is_register参数的部分支持：只有 m_register_desc有内容时，才会改为使用寄存器
    int process_one(class icode *ic);

    int m_data_alloc_start;
    int m_data_alloc_curr;
    int m_data_alloc_END;

    int m_idata_alloc_start;
    int m_idata_alloc_curr;
    int m_idata_alloc_END;

    int m_xdata_alloc_start;
    int m_xdata_alloc_curr;
    int m_xdata_alloc_END;

    class c51_addr *alloc_variable(icode *ic);

    //对于非指针和数组的正常变量空间申请
    class c51_addr *alloc_variable_not_ptr(icode *ic);
    class c51_addr *alloc_variable_array(icode *ic);
    class c51_addr *alloc_variable_ptr(icode *ic);
    class c51_addr *alloc_variable_str(icode *ic);


    int alloc_memory(c51_addr * ad, class icode *ic);
    void alloc_xdata(c51_addr *ad, icode *ic);
    bool alloc_low_data(c51_addr *ad, icode *ic);


    int print_usage();

private:
    //字符串和数组等初始值。 需要放入代码

    std::string new_const_label();

    int m_const_label_cnt;


    int parse_ptr(class icode *ic);

public:
    class icodes * m_context;

    class c51_addr * new_c51_addr();
    class c51_addr * new_c51_addr(class icode* ic);


public:
    ///符号表，用于调试
    std::map<std::string, c51_addr> m_sym;


    mem_alloc m_low_data;//0-128
    mem_alloc m_idata;//128-256
    mem_alloc m_xdata;//0-0x10000


};

#endif // C51_VAR_MANAGE_H

