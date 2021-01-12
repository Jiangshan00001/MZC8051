#ifndef ASM_TOKEN_H
#define ASM_TOKEN_H

#include <vector>
#include <string>


enum ASM_TOKEN_TYPE
{
    TOKEN_CMD=1,
    TOKEN_AB=2,
    TOKEN_ACC=3,
    TOKEN_AT_A_PLUS_DPTR=4,
    TOKEN_AT_A_PLUS_PC=5,
    TOKEN_AT_DPTR=6,
    TOKEN_AT_RI=7,
    TOKEN_C=8,
    TOKEN_DIV_NUM=9,
    TOKEN_DPTR=10,
    TOKEN_KEYWORD=11,
    TOKEN_RN=12,
    TOKEN_J_DATA=13,
    TOKEN_NUM=14,
    TOKEN_LABEL = 15,
    TOKEN_MACRO = 16,
    TOKEN_DB = 17,


    TOKEN_OPR = 198,
    TOKEN_PARENT = 199,//此处说明是一个组合token，具体在m_childs 中

    TOKEN_UNKNOWN=200,
};

class asm_token
{
public:
    asm_token();
    int type;
    std::string val_str; //字符串
    int num;// 值， 地址值，或者数据值
    int rel;// 当num为地址时，此处保存相对地址
    std::string get_type_str();


    std::vector<std::string> val_str_sep;
    void sep_val_str();//切分字符串，放入val_str_sep
	
	int line_no;
	int column_no;
	
    ///此处只有在token为lex/yacc解析结果时有用
    std::vector<asm_token> m_childs;
    int child_type;///组合token时，使用此字段代表当前数组指令类型

    int m_resolved;

};









#endif // ASM_TOKEN_H
