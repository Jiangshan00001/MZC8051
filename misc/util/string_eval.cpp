#include <map>
#include "replace.h"
#include "str2number.h"
#include "string_eval.h"


std::string string_eval(std::string str_raw)
{
    ///https://baike.baidu.com/item/%E8%BD%AC%E4%B9%89%E5%AD%97%E7%AC%A6/86397?fr=aladdin
    //字符串，前后双引号要去掉，转义字符进行转义

    //前后空格去掉
    int trim_one_space=0;
    while(str_raw.size()>1)
    {
        trim_one_space=0;

        if(str_raw[0]==' ')
        {
            str_raw= str_raw.substr(1);
            trim_one_space++;
        }
        if(str_raw[str_raw.size()-1]==' ')
        {
            str_raw= str_raw.substr(0, str_raw.size()-1);
            trim_one_space++;
        }
        if(trim_one_space==0)break;
    }


    //转义字符翻译
    if(str_raw.size()>1)
    {

        for(unsigned i=0;i<str_raw.size();++i)
        {
            if(str_raw[i]=='\\')
            {
                //此处是转义字符
                if(i==str_raw.size()-1)break;

                switch(str_raw[i+1])
                {
                    case 'x':
                    {
                        // \x000ff
                        unsigned j=i+2;
                        for(j=i+2;j<str_raw.size();++j)
                        {
                            if(((str_raw[j]>='0')&&(str_raw[j]<='9'))||
                                    ((str_raw[j]>='a')&&(str_raw[j]<='f'))||
                                    ((str_raw[j]>='A')&&(str_raw[j]<='F'))
                                    )
                            {
                                continue;
                            }
                            break;
                        }
                        std::string numstr = str_raw.substr(i+2, j-i-2);
                        // \x00ff 擦除 x00ff 保留 \ 用于存储ff数值
                        str_raw.erase(str_raw.begin()+i+1,str_raw.begin()+j);
                        str_raw[i] =StrToNumber("0x"+numstr);
                    }
                    break;



                    case '\\':
                    case '\"':
                    case '\'':
                    case '\?':
                    {
                        // \\ 转义
                        str_raw.erase(str_raw.begin()+i,str_raw.begin()+i+1 );
                    }
                    break;
                    case 'a':
                    {
                        str_raw.erase(str_raw.begin()+i,str_raw.begin()+i+1 );
                        str_raw[i] = '\a';
                    }
                    break;
                    case 'b':
                    {
                        str_raw.erase(str_raw.begin()+i,str_raw.begin()+i+1 );
                        str_raw[i] = '\b';
                    }
                    break;
                    case 'f':
                    {
                        str_raw.erase(str_raw.begin()+i,str_raw.begin()+i+1 );
                        str_raw[i] = '\f';
                    }
                    break;
                    case 'n':
                    {
                        str_raw.erase(str_raw.begin()+i,str_raw.begin()+i+1 );
                        str_raw[i] = '\n';
                    }
                    break;
                    case 'r':
                    {
                        str_raw.erase(str_raw.begin()+i,str_raw.begin()+i+1 );
                        str_raw[i] = '\r';
                    }
                    break;
                    case 't':
                    {
                        str_raw.erase(str_raw.begin()+i,str_raw.begin()+i+1 );
                        str_raw[i] = '\t';
                    }
                    break;
                    case 'v':
                    {
                        str_raw.erase(str_raw.begin()+i,str_raw.begin()+i+1 );
                        str_raw[i] = '\v';
                    }
                    break;
                    case '0':
                    {
                        str_raw.erase(str_raw.begin()+i,str_raw.begin()+i+1 );
                        str_raw[i] = 0;
                    }
                    break;

                    default:
                    {
                        // \\ 转义
                        str_raw.erase(str_raw.begin()+i,str_raw.begin()+i+1 );
                    }
                    break;
                }
            }
        }


    }


    //多个字符串连接 "111"  "222" "333"
    std::string str_cont;
    int in_str=0;
    for(unsigned i=0;i<str_raw.size();++i)
    {
        if(str_raw[i]=='\\')
        {
            continue;
        }
        if(str_raw[i]=='\"')
        {
            if(in_str==0)
            {
                in_str=1;
            }
            else
            {
                in_str=0;
            }
            continue;
        }
        if(in_str)
        {
            str_cont.push_back(str_raw[i]);
        }
    }
    str_raw = str_cont;

    return str_raw;
}


std::string string_pack(std::string strA)
{

    std::string retA=strA;
    replace(retA, "\n", "\\n");
    replace(retA, "\r", "\\r");
    replace(retA, "\t", "\\t");
    replace(retA, "\v", "\\v");
    replace(retA, "\f", "\\f");
    replace(retA, "\"", "\\\"");

    return retA;
#if 0
    std::map<std::string, std::string> m_rep_list;

    m_rep_list["\v"]="\\v";
    m_rep_list["\a"]="\\a";
    m_rep_list["\b"]="\\b";
    m_rep_list["\f"]="\\f";
    m_rep_list["\n"]="\\n";
    m_rep_list["\r"]="\\r";
    m_rep_list["\t"]="\\t";
    m_rep_list["\v"]="\\v";
    m_rep_list["\0"]="\\0";
    //m_rep_list["\\"]="\\\\";

    for(auto i=m_rep_list.begin();i!=m_rep_list.end();++i)
    {
        stri = replace(stri, i->first, i->second);
    }

    return stri;
#endif
}
