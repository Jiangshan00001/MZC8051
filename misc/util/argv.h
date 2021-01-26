/* 
 * File:   ArgsParser.h
 * Author: liangxh
 *
 * Created on 2015年6月26日, 上午9:16
 */

#ifndef ARGSPARSER_H
#define	ARGSPARSER_H

//2020.12.4 添加函数 GetOptionInt 用于获取数值选项
//2020.6.28 添加对引号的处理
//2020.6.23 add iostream songjiangshan

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
class ArgsParser
{
public:
    int is_debug;
    ArgsParser(){}
    ArgsParser(int argc, char** argv)
    {
        is_debug=0;
        Parse(argc, argv);
    }
    void Parse(int argc, char** argv)
    {
        m_mapArgs.clear();
        char cOption = 0;
        char cOptionNext = 0;
        for(int i=1; i<argc; ++i)
        {
            switch(CheckItemType(argv[i], cOption))
            {
            case ItemType_Option:
            {
                if(i+1<argc && (ItemType_Value == CheckItemType(argv[i+1], cOptionNext)))
                {
                    if(is_debug)
                    {
                        std::cout<<"opt_val:"<<cOption<<":"<< argv[i+1]<<"\n";
                    }
                    //m_mapArgs[cOption] = argv[i+1];

                    std::string val = argv[i+1];
                    if((val.size()>1)&&(val[0]=='\"'))
                    {
                        //字符第一个是引号，需要去掉
                        val = val.substr(1, val.size()-2);
                    }


                    m_mapArgs.insert(std::pair<char, std::string>(cOption, val));
                    ++i;
                }
                else
                {
                    m_mapArgs.insert(std::pair<char, std::string>(cOption, ""));
                    if(is_debug)
                    {
                        std::cout<<"opt_empty:"<<cOption<<":"<<""<<"\n";
                    }
                }
            }
                break;
            case ItemType_OP_VA:
            {

                m_mapArgs.insert(std::pair<char, std::string>(cOption, argv[i]+2));
                if(is_debug)
                {
                    std::cout<<"opt_thight:"<<cOption<<":"<< argv[i]+2<<"\n";
                }
            }
                break;
            default:
                std::cout<<"unknown arg:"<<i<<", "<<argv[i];
                continue;

            }
        }        
        return;
    }
    
    std::string GetOption(char cOption)
    {
        auto it = m_mapArgs.find(cOption);
        if(it == m_mapArgs.end())
        {
            return "";
        }
        return it->second;
    }
    int GetOptionInt(char cOption, int default_val)
    {
        auto it = m_mapArgs.find(cOption);
        if(it == m_mapArgs.end())
        {
            return default_val;
        }
        std::stringstream stri;
        stri<<it->second;
        int ret;
        stri>>ret;
        return ret;
    }


    std::vector<std::string> GetOptionVec(char cOption)
    {
        if(is_debug)
        {
            std::cout<<"GetOptionVec:"<<cOption<<std::endl;
        }
        std::vector<std::string> ret;

        int cnt = m_mapArgs.count(cOption);
        auto iter = m_mapArgs.find(cOption);

        for(unsigned i=0;i<cnt;++i)
        {
            ret.push_back(iter->second);
            ++iter;
        }
        if(is_debug)
        {
            std::cout<<"size:"<<ret.size()<<std::endl;
        }
        return ret;
    }


    bool HaveOption(char cOption)
    {
        auto it = m_mapArgs.find(cOption);
        return (it != m_mapArgs.end());
    }
    
private:
    enum ItemType
    {
        ItemType_Option, // eg: -a  -b ... -z  -A -B ... -Z
        ItemType_Value,  // eg: somestring 123456 ...
        ItemType_Invalid, // eg: -1 -? -ab -asomestring ...
        ItemType_OP_VA,  //eg: -athis_is_arg -bthis_is_another_arg
    };    
    ItemType CheckItemType(const char* pRawString , char &cOption)
    {
        cOption = 0;
        if(pRawString[0] == '-')
        {         
            if(pRawString[2]=='\0')
            {
                if((pRawString[1] >= 'a' && pRawString[1] <= 'z') || (pRawString[1] >= 'A' && pRawString[1] <= 'Z'))
                {
                    cOption = pRawString[1];
                    return ItemType_Option;
                }
            }
            else
            {
                if((pRawString[1] >= 'a' && pRawString[1] <= 'z') || (pRawString[1] >= 'A' && pRawString[1] <= 'Z'))
                {
                    cOption = pRawString[1];
                    return ItemType_OP_VA;
                }
            }
            return ItemType_Invalid;                
        }
        return ItemType_Value;
    }
private:
    std::multimap<char,std::string> m_mapArgs;
};

#endif	/* ARGSPARSER_H */
