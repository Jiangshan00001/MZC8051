#include <string>
#include <sstream>
#include "icode_to_c51.h"



void icode_to_c51::load_sys_func_def()
{

    std::stringstream asm_str;

    ///带符号的8bit除法
    /// A/B
    /// 结果在A，余数在B
    std::string func_div_signed_char=   "JNB      0xF0.7, __SIGNED_CHAR_DIV_JMP1;\n"
            "CPL      0xD0.5;\n"
            "XRL      0xF0, #0xFF;\n"
            "INC      0xF0;\n"
            "__SIGNED_CHAR_DIV_JMP1:\n"
            "JNB      0xE0.7,__SIGNED_CHAR_DIV_JMP2;\n"
            "CPL      0xD0.5;\n"
            "CPL      A;\n"
            "INC      A;\n"
            "__SIGNED_CHAR_DIV_JMP3:\n"
            "DIV      AB;\n"
            "XRL      0xF0,#0xFF;\n"
            "INC      0xF0;\n"
            "SJMP     __SIGNED_CHAR_DIV_JMP5;\n"
            "__SIGNED_CHAR_DIV_JMP2:\n"
            "DIV      AB;\n"
            "__SIGNED_CHAR_DIV_JMP5：\n"
            "JNB      0xD0.5, __SIGNED_CHAR_DIV_JMP4;\n"
            "CPL      A;\n"
            "INC      A;\n"
            "__SIGNED_CHAR_DIV_JMP4:\n"
            "RET ;\n";

    m_inline_sys_func["_sys_func_div_byte1_signed"] =func_div_signed_char;




    ///R1 R2 R3 ---指针。 R4 数值
#if 0
    DATA_TYPE_DIRECT=1,/*可直接读写的寄存器数据存储，0-127的ram，0x80-0xff的sfr*/
    DATA_TYPE_IDATA=2,/*不可以直接读写的内部数据存储 0x80-0xff的idata*/
    DATA_TYPE_PDATA=3, /*可以通过movx @Ri读写的数据存储,地址空间0-0xff*/
    DATA_TYPE_XDATA=4,/*可以通过movx @dptr读写的数据存储，地址空间0-0xffff */
    DATA_TYPE_CODE=5, /*通过movc读写的数据，在code区*/
#endif

    std::string func_byte_to_ptr =  "CJNE R3, #4, _SYS_FUNC_BYTE_TO_PTR_3;\n"
                                    "MOV 0x82, R1;\n"
                                    "MOV 0x83, R2;\n"
                                    "MOV A, R4;\n"
                                    "MOVX @DPTR, A;\n"
                                    "RET;\n"
                                    "_SYS_FUNC_BYTE_TO_PTR_3:\n"
                                    "CJNE R3, #3, _SYS_FUNC_BYTE_TO_PTR_2;\n"
                                    "MOV A, R4;\n"
                                    "MOVX @R1, A;\n"
                                    "RET;\n"
                                    "_SYS_FUNC_BYTE_TO_PTR_2:\n"
                                    "CJNE R3, #2, _SYS_FUNC_BYTE_TO_PTR_1;\n"
                                    "MOV A, R4;\n"
                                    "MOV @R1, A;\n"
                                    "RET;\n"
                                    "_SYS_FUNC_BYTE_TO_PTR_1:\n"
                                    "CJNE R3, #1, _SYS_FUNC_BYTE_TO_PTR_5;\n"
                                    "MOV A, R4;\n"
                                    "MOV @R1, A;\n"
                                    "_SYS_FUNC_BYTE_TO_PTR_5:\n"
                                    "RET;\n";


    /// ptr byte to a
    /// ptr input: r1 r2 r3
    std::string func_ptr_byte_to_a =  "CJNE R3, #4, _SYS_FUNC_PTR_BYTE_TO_A_3;\n"
                                    "MOV 0x82, R1;\n"
                                    "MOV 0x83, R2;\n"
                                    "MOVX A, @DPTR;\n"
                                    "RET;\n"
                                    "_SYS_FUNC_PTR_BYTE_TO_A_3:\n"
                                    "CJNE R3, #3, _SYS_FUNC_PTR_BYTE_TO_A_2;\n"
                                    "MOVX A, @R1;\n"
                                    "RET;\n"
                                    "_SYS_FUNC_PTR_BYTE_TO_A_2:\n"
                                    "CJNE R3, #2, _SYS_FUNC_PTR_BYTE_TO_A_1;\n"
                                    "MOV A, @R1;\n"
                                    "RET;\n"
                                    "_SYS_FUNC_PTR_BYTE_TO_A_1:\n"
                                    "CJNE R3, #1, _SYS_FUNC_PTR_BYTE_TO_A_5;\n"
                                    "MOV  A, @R1;\n"
                                    "RET;\n"
                                    "_SYS_FUNC_PTR_BYTE_TO_A_5:\n"
                                      "MOV 0x82, R1;\n"
                                      "MOV 0x83, R2;\n"
                                      "MOV A, #0;\n"
                                      "MOVC A, @A+DPTR;\n"
                                    "RET;\n";
    m_inline_sys_func["__sys_func_byte_to_ptr"] =func_byte_to_ptr;
    m_inline_sys_func["__sys_func_ptr_byte_to_a"] =func_ptr_byte_to_a;




    ///R4 R5 R6 R7 float32--->R4-R7 uint32
    ///
    /// r0-r3-float32-a r4-r7-float32-b
    ///
    std::string func_float32_sub="_FPSUB:\n"
            "MOV A, R0;\n"
            "XRL A, #0x80;\n"
            "MOV R0, A;\n"
            "_FPADD:\n"
            "MOV A, R1\n"


            ;


    m_inline_sys_func["__sys_func_float32_add"] =func_float32_sub;
    m_inline_sys_func["__sys_func_float32_minus"] =func_float32_sub;

    m_inline_sys_func["_sys_func_float32_mul"] =func_float32_sub;
    m_inline_sys_func["_sys_func_float32_div"] =func_float32_sub;




    /// 不带符号的byte2的除法
    ///  R4 R5
    /// R6 R7
    /// 结果在: R6 R7
    ///
}



