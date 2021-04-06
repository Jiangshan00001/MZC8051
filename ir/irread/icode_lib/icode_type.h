#ifndef ICODE_TYPE_H
#define ICODE_TYPE_H




typedef enum ICODE_TYPE_TAG
{
    ICODE_TYPE_UNKNOWN=0,



    ICODE_TYPE_I_CONST=1,
    ICODE_TYPE_F_CONST=2,
    ICODE_TYPE_CONST_STRING=3,



    ICODE_TYPE_DEF_VAR=4,/*变量定义*/

    ///var in var.定义一个变量，
    /// 此变量是通过另一个在result中的变量确定地址位置的
    /// @code
    /// char b;
    ///  char *a=&b;
    /// *a就是这种变量，其地址位置在变量a中
    /// a[10] 也是这种变量，地址位置在临时变量 a+10*sizeof(a[0])中
    /// a->b
    /// @endcode
    ICODE_TYPE_DEF_VAR_IN_VAR=5,
    ICODE_TYPE_DEF_VAR_IN_VAR_TMP=6,


    ICODE_TYPE_DEF_VAR_TMP=11,/*中间临时变量*/

    ICODE_TYPE_SYMBOL_REF=12, ///只是符号引用

    ICODE_TYPE_FUNC=13, //函数开始
    ICODE_TYPE_FUNC_RET_TYPE=14, //函数返回值
    ICODE_TYPE_FUNC_DEF_ARG=15,   //函数参数
    ICODE_TYPE_EXP_OP=16,        //算符
    ICODE_TYPE_FUNC_RETURN=17,

    ICODE_TYPE_BLOCK=18,//只是将多个icode顺序组合在一起
    ICODE_TYPE_LABELED_BLOCK=19,// 此处是一个特殊的block，前后可以有2个标签，用于跳转语句
    ICODE_TYPE_LABELED_BLOCK_START_REF=20,//代表result中的icode的起始位置
    ICODE_TYPE_LABELED_BLOCK_END_REF=21,  // 此处后期要废弃，只需要start就足够了


    ICODE_TYPE_CALL=22,

    ICODE_TYPE_ASM=23, /* 添加asm嵌入汇编 _inline_asm_  */


    ICODE_TYPE_CONST_LIST=24,//常数列表 {0x12,0x34,0x3,5,6,7,}

    ICODE_TYPE_SCOPE=25,//作用域，现在为c语言中的大括号: {}

    ICODE_TYPE_RELEASE=26,//变量释放位置
    ICODE_TYPE_ELLIPSIS,/// ellipsis func params

}ICODE_TYPE;


#endif // ICODE_TYPE_H
