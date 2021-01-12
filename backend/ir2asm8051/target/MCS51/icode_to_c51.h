#ifndef ICODE_TO_C51_H
#define ICODE_TO_C51_H

#include <map>
#include <string>
#include <vector>
#include <set>
#include "icode.h"
#include "reg_alloc.h"

#include "target_base.h"
#include "icode_manage.h"
///从中间代码生成8051的汇编语言代码
///


/**
为了保持与 gcc 和 vc 编译器的二进制兼容性，ucc 遵从这些编译器的调用规范。
(1) 函数调用时，实参从右往左进栈。调用者负责实参出栈。
(2) 保值寄存器：EBX, ESI 和 EDI。这些寄存器由被调用者保存。
易失寄存器：EAX, ECX 和 EDX。这些寄存器由调用者保存。
(3) 函数返回值的处理：
若返回值为整型，返回值位于 EAX 寄存器。
 若返回值为浮点型，返回值位于 ST(0)寄存器。
若返回值为大小为 1，2 或 4 的 struct/union 类型，返回值位于 EAX 寄存器。
若返回值为大小为 8 的 struct/union 类型，返回值位于 EAX,EDX 寄存器。
若返回值为其它大小的 struct/union 类型，函数的第一个参数是隐式参数，该参数
为函数返回值接收变量的地址，函数的返回类型成为 void。
***/




/// stc8 内部扩展ram：
/// pdata 0-0xff 读写： movx A, @Ri  movx @Ri, A.
/// xdata 0-0xffff 读写： movx A, @DPTR; movx @DPTR, A
/// pdata xdata都是扩展的ram，区别是pdata是低256字节，可以用Ri保存地址，xdata包括pdata
/// data :0x00->0x7f.  stc8 的128byte ram地址 data: 可直接访问： .  其中00-20h为寄存器组Ri 30h-7fh为用户区
/// idata :0x80-0xff.  stc8 的128-256的ram地址 idata:  只能间接访问：. 因为直接访问为sfr。
///  idata访问： mov a, @Ri; mov @Ri, A;
///  sfr访问： mov A, direct;  mov direct, A;
/// stc8 的sfr 地址0x7f->0xff 只能直接寻址方式访问
/// stc8 的bit寻址：ram的20h->2fh  16个寄存器可位寻址，对应位地址：00-7fh
/// stc8 的bit寻址：ram种sfr，地址能被8整除的16个寄存器可位寻址，对应位地址:0x80-0xff
/// ===================
/// sfr中，ACC->e0h B->f0h sp->81h dpl->82h dph->83h
///
/// 存储空间管理
/// 0-0x7f 128个byte data区，直接 寄存器。其中寄存器组0的R0-R3被编译器占用，用于临时变量。4byte？？
///                               其他寄存器组，如果程序中有试用using 0-3, 则会占用相应的8个字节空间。
/// -寄存器组：00-0x1fh 32个byte
///
/// -20h->2fh 可位寻址寄存器。 16byte. 16x8bit
/// -30h->7fh 用户自定义区域。 ---80byte.
/// -80h->ffh 128byte. 只能间接寻址。idata
/// -80h->ffh 128byte. 只能直接寻址sfr
/// 00h-ffffh 64kbyte. 内部扩展ram(pdata, xdata)。 movx
/// 00-ffffh 64kbyte. 代码区。 movc
///

/// 空间分配流程：
/// 1 确定工作寄存器组使用个数。0--4byte。其他：每个组8个byte
/// 2 确定 bit位 使用个数. ---
/// 3 确定栈sp使用个数 根据调用关系--reentrant 模拟栈？？咱不实现模拟栈，使用常规栈
/// 4 对于不可重入函数，确定每个函数变量的地址
/// 5


#define REG_ADDR_PSW  0xD0
#define REG_ADDR_ACC 0xE0
#define REG_ADDR_B 0xF0
#define REG_ADDR_DPTR 0x82
#define REG_ADDR_DPL 0x82
#define REG_ADDR_DPH 0x83

#define CODE_PTR_BIT_WIDTH (2*8)
#define VAR_PTR_BIT_WIDTH (3*8)


///此处是本机的float使用。因为立即数时，使用本机的float存储方式？？？？？
//#define FLOAT32 float

/// enum定义转移到 icode.h中
//typedef enum E_DATA_TYPE_8051_TAG
//{
//    DATA_TYPE_UNKNOWN=0,
//    DATA_TYPE_DIRECT=1,/*可直接读写的寄存器数据存储，0-127的ram，0x80-0xff的sfr*/
//    DATA_TYPE_IDATA=2,/*不可以直接读写的内部数据存储 0x80-0xff的idata*/
//    DATA_TYPE_PDATA=3, /*可以通过movx @Ri读写的数据存储,地址空间0-0xff*/
//    DATA_TYPE_XDATA=4,/*可以通过movx @dptr读写的数据存储，地址空间0-0xffff */
//    DATA_TYPE_CODE=5, /*通过movc读写的数据，在code区*/

//    DATA_TYPE_BIT=6,      /*bit 属性，8051特定的某些寄存器可以读写bit，只能特定的指令读写， mov c, bit*/
//    DATA_TYPE_J_DATA=7, /*立即数，存储位置在code区，但是代码指令执行时自动读出*/
//    DATA_TYPE_RN=8,     /**/
//    DATA_TYPE_RI=9,     /**/

//}E_DATA_TYPE_8051;




///
/// \brief The icode_to_c51 class
/// 第一步：
/// 变量申请：全局变量使用全局空间。 函数返回值和函数参数和局部变量 使用栈空间
///

class icodes;

class icode_to_c51: public target_base
{
public:
    icode_to_c51(icodes * mpcompi);
    virtual ~icode_to_c51();
    std::string to_asm(std::vector<class icode *> &ic, std::vector<icode *> &str_ic);
    std::string to_asm(class icodes *ics);



    ///每种数据类型，占用的byte数。其中bit是特殊的，只占用1bit，其他都是字节
    /// bit时，返回
    int get_basic_type_bit_width(const std::string &type_str);


    std::map<std::string, int> m_type_bit_list;




    std::string icode_to_asm(class icode* ic);


    std::string icode_to_asm_op(class icode *ic);
    std::string generate_interrupt_ljmp(std::vector<class icode *> &ic);


    std::set<std::string> m_inline_sys_func_needed;
    std::map<std::string, std::string> m_inline_sys_func;


    void load_sys_func_def();

public:

    ///
    /// \brief interrupts
    ///中断向量保存表。其中0---main函数，复位中断
    ///                 1---0x0003 int0中断，对应标识 interrupt 0
    ///                 2---0x000B timer0中断，对应标识 interrupt 1
    ///                 3---0x0013 int1中断，对应标识 interrupt 2
    ///                 4---0x001B timer1中断，对应标识 interrupt 3
    /// 。。。后面以此类推
    std::map<int, std::string> interrupts;

    //for 8051
    std::map<int, int> interrupt_addr;


    icodes * pcompi;

private:
    ///=====================================
    /// mov函数
    std::string mov_byte_to_direct(c51_addr * from, int addr_shift=0, int direct=0);
    std::string mov_byte_to_a(c51_addr * from, int addr_shift=0, int dptr_just_inc=0);
    std::string mov_byte_to_r0(c51_addr * from, int addr_shift=0, int dptr_just_inc=0);
    std::string mov_byte_to_r1(c51_addr * from, int addr_shift=0, int dptr_just_inc=0);
    std::string mov_byte_to_r2(c51_addr * from, int addr_shift=0, int dptr_just_inc=0);
    std::string mov_byte_to_r3(c51_addr * from, int addr_shift=0, int dptr_just_inc=0);
    std::string mov_byte_to_r4(c51_addr * from, int addr_shift=0, int dptr_just_inc=0);
    std::string mov_byte_to_r5(c51_addr * from, int addr_shift=0, int dptr_just_inc=0);
    std::string mov_byte_to_r6(c51_addr * from, int addr_shift=0, int dptr_just_inc=0);
    std::string mov_byte_to_r7(c51_addr * from, int addr_shift=0, int dptr_just_inc=0);
    std::string mov_byte_to_ri(c51_addr * from, int addr_shift=0, int dptr_just_inc=0, int R=0);
    std::string mov_byte_to_b(c51_addr * from, int addr_shift=0);
    //std::string mov_byte_to_R(c51_addr * from, int addr_shift=0, int Raddr=0);

    std::string mov_byte_a_to(c51_addr * to, int addr_shift=0, int dptr_just_inc=0);
    std::string mov_byte_b_to(c51_addr * to, int addr_shift=0);
    std::string mov_byte_ri_to(c51_addr * to, int addr_shift=0, int dptr_just_inc=0, int R=0);
    std::string mov_byte_r0_to(c51_addr * to, int addr_shift=0, int dptr_just_inc=0);
    std::string mov_byte_r1_to(c51_addr * to, int addr_shift=0, int dptr_just_inc=0);
    std::string mov_byte_r2_to(c51_addr * to, int addr_shift=0, int dptr_just_inc=0);
    std::string mov_byte_r3_to(c51_addr * to, int addr_shift=0, int dptr_just_inc=0);
    std::string mov_byte_r4_to(c51_addr * to, int addr_shift=0, int dptr_just_inc=0);
    std::string mov_byte_r5_to(c51_addr * to, int addr_shift=0, int dptr_just_inc=0);
    std::string mov_byte_r6_to(c51_addr * to, int addr_shift=0, int dptr_just_inc=0);
    std::string mov_byte_r7_to(c51_addr * to, int addr_shift=0, int dptr_just_inc=0);


    std::string mov_byte_to_at_ri(c51_addr * from, int addr_shift=0, int dptr_just_inc=0, int R=0);
    std::string mov_byte_to_at_r0(c51_addr * from, int addr_shift=0, int dptr_just_inc=0);
    std::string mov_byte_to_at_r1(c51_addr * from, int addr_shift=0, int dptr_just_inc=0);
    std::string mov_byte_to_at_dptr(c51_addr *from, int addr_shift, int dptr_just_inc=0);


    std::string mov_byte_at_ri_to(c51_addr * to, int addr_shift=0, int dptr_just_inc=0, int R=0);
    std::string movc_byte_at_dptr_to(c51_addr *to, int addr_shift=0, int dptr_just_inc=0);
    std::string movx_byte_at_dptr_to(c51_addr *to, int addr_shift=0, int dptr_just_inc=0);



    std::string mov_0_to(c51_addr*to);
    std::string mov_1_to(c51_addr*to);
    std::string mov_byte_0_to(c51_addr*to, int addr_shift=0);

    std::string mov(c51_addr * from, c51_addr*to);

    ///===========================================================================================



    ///===========================================================================================
    /// opr
    /// 转移、算术运算
    std::string to_asm_opr_mov(class icode* ic);
    std::string to_asm_opr_plus(icode *ic);
    std::string to_asm_opr_sub(icode *ic);
    std::string to_asm_opr_mul(icode *ic);
    std::string to_asm_opr_div(icode *ic);
    std::string to_asm_opr_mod(icode *ic);
    std::string to_asm_opr_bit_and(icode *ic);
    std::string to_asm_opr_bit_or(icode *ic);
    std::string to_asm_opr_bit_not(icode *ic);
    std::string to_asm_opr_shiftr(icode *ic);
    std::string to_asm_opr_shiftl(icode *ic);
    std::string to_asm_opr_rotate_shiftr(icode *ic);
    std::string to_asm_opr_rotate_shiftl(icode *ic);



    std::string to_asm_opr_plus_eq(icode *ic);
    std::string to_asm_opr_sub_eq(icode *ic);
    std::string to_asm_opr_mul_eq(icode *ic);
    std::string to_asm_opr_div_eq(icode *ic);
    std::string to_asm_opr_shiftr_eq(icode *ic);
    std::string to_asm_opr_shiftl_eq(icode *ic);


    std::string to_asm_opr_mm(icode *ic);
    std::string to_asm_opr_pp(icode *ic);


    /// 逻辑运算  < > <= != == ~ &&
    std::string to_asm_opr_less(icode *ic);
    std::string to_asm_opr_greater(icode *ic);
    std::string to_asm_opr_less_eq(icode *ic);
    std::string to_asm_opr_greater_eq(icode *ic);
    std::string to_asm_opr_is_not_equal(class icode* ic);
    std::string to_asm_opr_is_equal(class icode* ic);
    std::string to_asm_opr_logic_not(class icode* ic);
    std::string to_asm_opr_logic_and(class icode* ic);
    std::string to_asm_opr_logic_or(class icode* ic);

    /// 跳转指令
    std::string to_asm_opr_jmp(icode *ic);
    std::string to_asm_opr_jz(icode *ic);
    std::string to_asm_opr_xor(icode *ic);
    std::string to_asm_opr_jnz(icode *ic);



    std::string to_asm_opr_address_of(icode * ic);
    std::string to_asm_opr_negative(icode *ic);

    /// 具体实现函数
    std::string add(c51_addr *a1, c51_addr *a2, c51_addr *result);
    std::string sub(c51_addr *a1, c51_addr *a2, c51_addr *result, int is_set_c=0);
    std::string mulA(c51_addr *a1, c51_addr *a2, c51_addr *result);
    /// \todo 除法还没有完全完成。
    std::string divA(c51_addr *a1, c51_addr *a2, c51_addr *result);    
    std::string modA(c51_addr *a1, c51_addr *a2, c51_addr *result);
    std::string shiftR(c51_addr *a1, c51_addr *a2, c51_addr *result);
    std::string shiftL(c51_addr *a1, c51_addr *a2, c51_addr *result);
    std::string rotate_shiftR(c51_addr *a1, c51_addr *a2, c51_addr *result);
    std::string rotate_shiftL(c51_addr *a1, c51_addr *a2, c51_addr *result);


    std::string decA(c51_addr * varA);
    std::string incA(c51_addr * varA);
    std::string bit_not(c51_addr *a1, c51_addr *result);
    std::string bit_and(c51_addr *a1, c51_addr *a2, c51_addr *result);
    std::string bit_or(c51_addr *a1, c51_addr *a2, c51_addr *result);


    std::string lessA(c51_addr *a1, c51_addr *a2, c51_addr *result, bool include_eq=0);
    std::string greaterA(c51_addr *a1, c51_addr *a2, c51_addr *result, bool include_eq=0);


    std::string xorA(c51_addr *a1, c51_addr *a2, c51_addr *result);
    std::string jzA(c51_addr * expr, c51_addr* labA, bool is_jnz=0);
    std::string is_equal(c51_addr *a1, c51_addr *a2, c51_addr *result);
    std::string is_not_equal(c51_addr *a1, c51_addr *a2, c51_addr *result);
    std::string logic_not(c51_addr *a1, c51_addr *result);
    std::string logic_and(c51_addr *a1, c51_addr *a2, c51_addr *result);
    std::string logic_or(c51_addr *a1, c51_addr *a2, c51_addr *result);

    //求bit或
    std::string orl_byte_with_a(c51_addr* a1, int addr_shift);
    //求bit 异或：相同为0，不同为1
    std::string xrl_byte_with_a(c51_addr* a1, int addr_shift);


    ///===========================================================================================
    /// misc

    c51_addr * get_target(class icode * ic);
    class icode * get_def_var(class icode * ic);
    std::string get_tmp_label(std::string comment);
    std::string get_tmp_label_nake(std::string comment);

    std::string lcall(std::string func_full_name, icode *func=NULL);

    ///添加数组，代表当前嵌入的标记
    std::vector<std::string> m_inline_vec;
    ///标签前缀，用于不同的函数作用域
    std::string m_inline_func_label_prefix;
    int refresh_label_prefix();


private:
    void shiftOneR(int byte_cnt, std::stringstream &asm_str);
    void shiftOneL(int byte_cnt, std::stringstream &asm_str);

    void rotateShiftOneR(int byte_cnt, std::stringstream &asm_str);
    void rotateShiftOneL(int byte_cnt, std::stringstream &asm_str);

    //将常量数组或字符串，转为db代码数据的asm
    std::string const_to_db(std::vector<icode *> &ic);

    reg_alloc m_Rn;

    /// 当前函数的icode.用于return语句。
    class icode * m_curr_func;


private:
    c51_addr * new_c51_addr_jdata(int num);
    int del_c51_addr(c51_addr* a51);

private:
    void to_asm_call(icode *ic, std::stringstream &asm_str);

    //std::string parse_ptr(c51_addr *from, int addr_shift, c51_addr &dst);

public:
    std::map<std::string, c51_addr> m_sym;

    bool is_byte_shift_over_flow(c51_addr *from, int addr_shift, std::string &byte_str, std::string &byte_prepare_str);



};

#endif // ICODE_TO_C51_H
