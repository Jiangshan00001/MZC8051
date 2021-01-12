#ifndef ASM_TABLE_H
#define ASM_TABLE_H
#include<string>
#include <vector>

typedef struct hex_code_asm_table
{
    unsigned m_hex_code;
    unsigned m_byte_num;
    std::string cmd;
    std::string params;
    int param_cnt;
    std::string m_param0;// #$0
    std::string m_param1; // R$1
    std::string m_param2;
}hex_code_asm_table;



typedef struct asm_to_hex_table
{
    std::string cmd;
    std::string params;
    std::string description;
    unsigned m_byte_num;
    unsigned m_oscillator_period;
    std::string m_class;
    std::string m_byte0;
    std::string m_byte1;
    std::string m_byte2;

    std::string m_token0;
    std::string m_token1;
    std::string m_token2;
    std::string m_token3;
} asm_to_hex_table;


extern hex_code_asm_table g_hex_table[];
extern asm_to_hex_table g_asm_table[];
extern int g_hex_table_size;
extern int g_asm_table_size;
#endif // ASM_TABLE_H
