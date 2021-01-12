#ifndef C51_ADDR_H
#define C51_ADDR_H

#include <string>


#define ASM_END_STR ";\n"

//因为sfr特殊功能寄存器是通过赋值语句设置地址，所以定义时添加此地址，带后期补充上。
#define UNKNOWN_ADDR 0x1ffff

typedef enum E_DATA_TYPE_8051_TAG
{
    /*未知数据类型，只有代码出错未赋值时才会出现*/
    DATA_TYPE_UNKNOWN=0,

    DATA_TYPE_DIRECT=1,/*可直接读写的寄存器数据存储，0-127的ram，0x80-0xff的sfr*/
    DATA_TYPE_IDATA=2,/*不可以直接读写的内部数据存储 0x80-0xff的idata*/
    DATA_TYPE_PDATA=3, /*可以通过movx @Ri读写的数据存储,地址空间0-0xff*/
    DATA_TYPE_XDATA=4,/*可以通过movx @dptr读写的数据存储，地址空间0-0xffff */
    DATA_TYPE_CODE=5, /*通过movc读写的数据，在code区*/



    DATA_TYPE_BIT=6,      /*bit 属性，8051特定的某些寄存器可以读写bit，只能特定的指令读写， mov c, bit*/
    DATA_TYPE_J_DATA=7, /*立即数，不需要保存。如果编写到指令中，存储位置在code区。如果有jdata之间的计算，则可以直接在编译时计算并获取结果*/
    DATA_TYPE_RN=8,     /*寄存器 r0-r7*/
    DATA_TYPE_RI=9,     /*寄存器r0-r1*/
    DATA_TYPE_J_DATA_LABEL=10,/*立即数，但是是代码地址标签，只有汇编编译后，才会生成真正的数值， 此处使用labelA代替数值生成汇编代码*/
    DATA_TYPE_J_DATA_F, /*float 立即数*/

    DATA_TYPE_IDIRECT_RI,/*变量地址的变量（变量指针）：     通过Ri读写的direct idata. 实际为direct变量，在读写时，临时申请ri读写完成后释放*/
    DATA_TYPE_PDATA_RI, /*变量地址的变量（变量指针）：      通过Ri读写的PDATA 实际为direct变量，在读写时，临时申请ri读写完成后释放*/
    DATA_TYPE_CODE_AT_DPTR, /*变量地址的变量（变量指针）：  通过dptr读的代码段 实际为direct变量，在读写时，临时申请dptr读写完成后释放*/
    DATA_TYPE_XDATA_AT_DPTR, /*变量地址的变量（变量指针）： 通过dptr读写的xdata实际为direct变量，在读写时，临时申请dptr读写完成后释放*/

    /// 通用指针
    /// 此类型并不是说是指针，而是说数据的读写，都是通过指针进行的
    /// ptr_target指向的是指针
    DATA_TYPE_IN_GENRIC_PTR,

#if 0
    DATA_TYPE_CODE_CONST_PTR,
    DATA_TYPE_DIRECT_CONST_PTR,
    DATA_TYPE_IDATA_CONST_PTR,
    DATA_TYPE_XDATA_CONST_PTR,
    DATA_TYPE_PDATA_CONST_PTR,
    //DATA_TYPE_PTR,
#endif
}E_DATA_TYPE_8051;


class c51_addr
{
public:
    c51_addr();

    E_DATA_TYPE_8051 m_type;
    unsigned long long m_addr;
    unsigned m_bit_width;
    std::string labelA;

    /// JDATA JDATA_F时使用
    float fnum;
    unsigned long long num;

    ///说明数据是否有符号
    int is_signed:1;
    /// 说明是否是float类型
    int is_float32:1;

    int refresh_width_from_addr();


    unsigned m_bit_width_array_comp;//数组时，此处保存数组元素的位宽

    int is_array;/// 0--数组指针。 -1--指针指向的地址
    int is_ptr;

    /// 如果是数组，则此处放置指针指向的实际数据定义
    /// eg: int a[5];
    /// 实际对a的访问： int *p = a;
    /// 是访问的指针。只有
    /// int p=a[0]; 才是访问的a的内部数据
    /// 所以，变量a实际默认c51_addr是指针常数(3byte)，内部数据通过ptr_target定义
    c51_addr * ptr_target;


    bool is_equal(c51_addr *another);

};

#endif // C51_ADDR_H
