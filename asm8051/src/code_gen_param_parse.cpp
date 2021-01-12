#include <map>
#include <iostream>
#include "code_gen_param_parse.h"
#include "trim.h"
#include "split.h"
#include "replace.h"




std::vector<std::string> template_param_parse_str(std::string str1)
{
    //"A,direct"
    //"A,Rn"
    std::vector<std::string> ret;

    str1 = trim1(str1,'\"');
    std::vector<std::string> params = split(str1, ",");


    std::map<std::string, std::string> m_token_dict;
    m_token_dict["A"]="TOKEN_ACC";
    m_token_dict["Rn"]="TOKEN_RN";
    m_token_dict["direct"]="TOKEN_NUM";
    m_token_dict["#data"]="TOKEN_J_DATA";
    m_token_dict["#data16"]="TOKEN_J_DATA";
    m_token_dict["@Ri"]="TOKEN_AT_RI";

    m_token_dict["rel code addr"]="TOKEN_KEYWORD";
    m_token_dict["rel"]="TOKEN_KEYWORD";
    m_token_dict["addr11"]="TOKEN_KEYWORD";
    m_token_dict["addr16"]="TOKEN_KEYWORD";
    m_token_dict["data16"]="TOKEN_KEYWORD";
    m_token_dict["bit"]="TOKEN_NUM";
    m_token_dict["/bit"]="TOKEN_DIV_NUM";
    m_token_dict["@A+DPTR"]="TOKEN_AT_A_PLUS_DPTR";
    m_token_dict["@A+PC"]="TOKEN_AT_A_PLUS_PC";

    m_token_dict["DPTR"]="TOKEN_DPTR";
    m_token_dict["@DPTR"]="TOKEN_AT_DPTR";
    m_token_dict["AB"]="TOKEN_AB";
    m_token_dict["C"]="TOKEN_C";

    m_token_dict["code addr"]="TOKEN_KEYWORD";
    m_token_dict["data addr"]="TOKEN_KEYWORD";
    m_token_dict["bit addr"]="TOKEN_KEYWORD";

    for(unsigned i=0;i<params.size();++i)
    {
        std::string token1;
        std::string param1=params[i];

        token1 = "";
        if(m_token_dict.find(param1)==m_token_dict.end())
        {
            token1="TOKEN_UNKNOWN";
            std::cout<<"template_param_parse---unkown type:"<<param1<<std::endl;
        }
        else
        {
            token1 = m_token_dict[param1];
        }
        ret.push_back(token1);
    }
    return ret;
}




std::vector<std::string> template_param_parse_str_var(std::string str1)
{

    std::vector<std::string> ret;

    str1 = trim1(str1,'\"');
    std::vector<std::string> params = split(str1, ",");

    std::map<std::string, std::string> m_token_dict;
    m_token_dict["A"]="num";
    m_token_dict["Rn"]="num";
    m_token_dict["direct"]="num";
    m_token_dict["#data"]="num";
    m_token_dict["#data16"]="num";
    m_token_dict["@Ri"]="num";

    m_token_dict["rel code addr"]="rel";
    m_token_dict["rel"]="rel";
    m_token_dict["addr11"]="num";
    m_token_dict["addr16"]="num";
    m_token_dict["data16"]="num";
    m_token_dict["bit"]="num";
    m_token_dict["/bit"]="num";
    m_token_dict["@A+DPTR"]="num";
    m_token_dict["@A+PC"]="num";

    m_token_dict["DPTR"]="num";
    m_token_dict["@DPTR"]="num";
    m_token_dict["AB"]="num";
    m_token_dict["C"]="num";

    m_token_dict["code addr"]="num";
    m_token_dict["data addr"]="num";
    m_token_dict["bit addr"]="num";

    for(unsigned i=0;i<params.size();++i)
    {
        std::string token1;
        std::string param1=params[i];

        token1 = "";
        if(m_token_dict.find(param1)==m_token_dict.end())
        {
            token1="TOKEN_UNKNOWN";
            std::cout<<"template_param_parse---unkown type:"<<param1<<std::endl;
        }
        else
        {
            token1 = m_token_dict[param1];
        }
        ret.push_back(token1);
    }
    return ret;

}


std::vector<int> template_param_parse_str_var_range_8bit_sign(std::string str1)
{
    std::vector<int> ret;

    str1 = trim1(str1,'\"');
    std::vector<std::string> params = split(str1, ",");

    std::map<std::string, std::string> m_token_dict;
    m_token_dict["rel code addr"]="0xff";
    m_token_dict["rel"]="0xff";

    for(unsigned i=0;i<params.size();++i)
    {
        int token1;
        std::string param1=params[i];

        if(m_token_dict.find(param1)==m_token_dict.end())
        {
            token1=0;
        }
        else
        {
            token1 = 1;
        }
        ret.push_back(token1);
    }
    return ret;
}

std::vector<std::string> template_param_parse_str_var_range(std::string str1)
{
    std::vector<std::string> ret;

    str1 = trim1(str1,'\"');
    std::vector<std::string> params = split(str1, ",");

    std::map<std::string, std::string> m_token_dict;
    m_token_dict["A"]="";
    m_token_dict["Rn"]="0x07";
    m_token_dict["direct"]="0xff";
    m_token_dict["#data"]="0xff";
    m_token_dict["#data16"]="0xffff";
    m_token_dict["@Ri"]="0x01";

    m_token_dict["rel code addr"]="0xff";
    m_token_dict["rel"]="0xff";
    m_token_dict["addr11"]="0x7ff";
    m_token_dict["addr16"]="0xffff";
    m_token_dict["data16"]="0xffff";
    m_token_dict["bit"]="0xff";
    m_token_dict["/bit"]="0xff";
    m_token_dict["@A+DPTR"]="";
    m_token_dict["@A+PC"]="";

    m_token_dict["DPTR"]="";
    m_token_dict["@DPTR"]="";
    m_token_dict["AB"]="";
    m_token_dict["C"]="";

    m_token_dict["code addr"]="";
    m_token_dict["data addr"]="";
    m_token_dict["bit addr"]="";

    for(unsigned i=0;i<params.size();++i)
    {
        std::string token1;
        std::string param1=params[i];

        token1 = "";
        if(m_token_dict.find(param1)==m_token_dict.end())
        {
            token1="TOKEN_UNKNOWN";
            std::cout<<"template_param_parse---unkown type:"<<param1<<std::endl;
        }
        else
        {
            token1 = m_token_dict[param1];
        }
        ret.push_back(token1);
    }
    return ret;
}
