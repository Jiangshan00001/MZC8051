#include <map>
#include "asm_token.h"


static std::map<int, std::string> s_token_type_str;

void init_asm_token_type_to_str()
{
    s_token_type_str[TOKEN_CMD]="TOKEN_CMD";
    s_token_type_str[TOKEN_AB]="TOKEN_AB";
    s_token_type_str[TOKEN_ACC]="TOKEN_ACC";
    s_token_type_str[TOKEN_AT_A_PLUS_DPTR]="TOKEN_AT_A_PLUS_DPTR";
    s_token_type_str[TOKEN_AT_A_PLUS_PC]="TOKEN_AT_A_PLUS_PC";
    s_token_type_str[TOKEN_AT_DPTR]="TOKEN_AT_DPTR";
    s_token_type_str[TOKEN_AT_RI]="TOKEN_AT_RI";
    s_token_type_str[TOKEN_C]="TOKEN_C";
    s_token_type_str[TOKEN_DIV_NUM]="TOKEN_DIV_NUM";
    s_token_type_str[TOKEN_DPTR]="TOKEN_DPTR";

    s_token_type_str[TOKEN_KEYWORD]="TOKEN_KEYWORD";
    s_token_type_str[TOKEN_RN]="TOKEN_RN";
    s_token_type_str[TOKEN_J_DATA]="TOKEN_J_DATA";
    s_token_type_str[TOKEN_NUM]="TOKEN_NUM";
    s_token_type_str[TOKEN_LABEL]="TOKEN_LABEL";
    s_token_type_str[TOKEN_MACRO]="TOKEN_MACRO";
    s_token_type_str[TOKEN_OPR]="TOKEN_OPR";
    s_token_type_str[TOKEN_PARENT]="TOKEN_PARENT";
    s_token_type_str[TOKEN_DB]="TOKEN_DB";


    s_token_type_str[TOKEN_UNKNOWN]="TOKEN_UNKNOWN";

}

asm_token::asm_token()
{
    num = 0;
    rel = 0;

    m_resolved = 0;
    line_no = 0;
    column_no = 0;

}


std::string asm_token::get_type_str()
{
    auto it = s_token_type_str.find(this->type);
    if(it==s_token_type_str.end())
    {
        init_asm_token_type_to_str();
        it = s_token_type_str.find(this->type);
    }
    return it->second;
}

void asm_token::sep_val_str()
{

    for(unsigned i=0;i<this->val_str.size();++i)
    {

    }
}




