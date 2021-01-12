#include <set>
#include<string>
#include <sstream>
#include <map>
#include <vector>
#include <iostream>
#include "asm_test_code_gen.h"
#include "asm_table.h"

typedef struct token_accd_vals
{
    std::string m_token;
    int m_num;
    std::string v1[5];

}token_accd_vals;


token_accd_vals g_token_accd_vals_table[]={
    {"TOKEN_AB", 1, {"AB" , "", "", "", "",} },
    {"TOKEN_ACC", 1, {"A" , "", "", "", "",} },
    {"TOKEN_AT_A_PLUS_DPTR", 1, {"@A+DPTR" , "", "", "", "",} },
    {"TOKEN_AT_A_PLUS_PC", 1,{ "@A+PC" , "", "", "", "",} },
    {"TOKEN_AT_DPTR", 1,{ "@DPTR" , "", "", "", "",} },
    {"TOKEN_AT_RI", 2,{ "@R0" , "@R1", "", "", "",}},
    {"TOKEN_C", 1,{ "C" , "", "", "", "",} },
    {"TOKEN_DIV_NUM", 1,{ "/23H" , "/64H", "", "", "",} },
    {"TOKEN_DPTR", 1, {"DPTR" , "", "", "", "",} },
    {"TOKEN_J_DATA", 3,{ "#1234H" , "#12H", "#78H", "", "",} },
    {"TOKEN_KEYWORD", 1,{ "ADDR_TEST1" , "", "", "", "",} },
    {"TOKEN_NUM", 3,{ "63H" , "54H", "23H", "", "",} },
    {"TOKEN_RN", 3, {"R0" , "R7", "R3", "", "",} },
};




asm_test_code_gen::asm_test_code_gen()
{


}

std::string asm_test_code_gen::test_code_gen1()
{
    //生成测试用的asm代码
    std::stringstream ret_out;
    ret_out<<"ORG 2000H\r\n";
    ret_out<<"ADDR_TEST1:\r\n";
    std::map<std::string, token_accd_vals > param_enum_list;

    for(int i=0;i<sizeof(g_token_accd_vals_table)/sizeof(g_token_accd_vals_table[0]);++i)
    {
        param_enum_list[g_token_accd_vals_table[i].m_token] = g_token_accd_vals_table[i];
    }


    for(int i=0;i<g_asm_table_size;++i)
    {
        std::string cmd = g_asm_table[i].cmd;

        std::cout<<g_asm_table[i].cmd<<std::endl;

        //std::string params = g_asm_table[i].params;
        int token_num = 4;
        if(g_asm_table[i].m_token3.size()==0)
        {
            token_num--;
        }
        if(g_asm_table[i].m_token2.size()==0)
        {
            token_num--;
        }
        if(g_asm_table[i].m_token1.size()==0)
        {
            token_num--;
        }
        if(g_asm_table[i].m_token0.size()==0)
        {
            token_num--;
        }

        if(token_num==0)
        {
            ret_out<<cmd<<";";
        }
        else if(token_num==1)
        {
            for(int j1=0;j1<param_enum_list[g_asm_table[i].m_token0].m_num;++j1)
            {
                ret_out<<cmd<<" "<<param_enum_list[g_asm_table[i].m_token0].v1[j1]<<";\r\n";
            }
        }
        else if(token_num==2)
        {
            for(int j1=0;j1<param_enum_list[g_asm_table[i].m_token0].m_num;++j1)
            {
                for(int j2=0;j2<param_enum_list[g_asm_table[i].m_token1].m_num;++j2)
                {
                    ret_out<<cmd<<" "<<param_enum_list[g_asm_table[i].m_token0].v1[j1]<<","<<param_enum_list[g_asm_table[i].m_token1].v1[j2]<<   ";\r\n";
                }
            }
        }
        else if(token_num==3)
        {
            for(int j1=0;j1<param_enum_list[g_asm_table[i].m_token0].m_num;++j1)
            {
                for(int j2=0;j2<param_enum_list[g_asm_table[i].m_token1].m_num;++j2)
                {
                    for(int j3=0;j3<param_enum_list[g_asm_table[i].m_token2].m_num;++j3)
                    {
                        ret_out<<cmd<<" "<<param_enum_list[g_asm_table[i].m_token0].v1[j1]<<","<<param_enum_list[g_asm_table[i].m_token1].v1[j2]<<", "<<param_enum_list[g_asm_table[i].m_token2].v1[j3]<<   ";\r\n";
                    }
                }
            }
        }

    }

    //std::cout<<ret_out.str()<<std::endl;
    return ret_out.str();
}

