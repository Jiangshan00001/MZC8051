#include <assert.h>
#include <string>
#include <sstream>
#include <vector>
#include "str2number.h"
#include "trim.h"
#include "split.h"
#include "mylog.h"

using mylog::cdbg;

float StrToFloat(std::string  mHexStr)
{
    std::stringstream ss;
    ss<<mHexStr;
    float ret;
    ss>>ret;
    return ret;
}

unsigned long long StrToNumber(std::string  mHexStr)
{
    mHexStr = trim(mHexStr);
    if(mHexStr.size()==0)
    {
        return 0;
    }

    std::stringstream ss;
    unsigned long long x=0;


    if(mHexStr.size()>3)
    {
        ///字符串是： NOT 20H
        if(mHexStr.find("NOT ")==0)
        {
            std::string tmp11= mHexStr.substr(4);
            tmp11=trim(tmp11);
            unsigned long a = StrToNumber(tmp11);
            return ~a;
        }
    }
    if(mHexStr.size()>3)
    {
        if(mHexStr.find("LOW")==0)
        {
            std::string tmp11= mHexStr.substr(3);
            tmp11=trim(tmp11);
            unsigned long a = StrToNumber(tmp11);
            return (0xff&a);
        }
    }
    if(mHexStr.size()>4)
    {
        if(mHexStr.find("HIGH")==0)
        {
            std::string tmp11= mHexStr.substr(4);
            tmp11=trim(tmp11);
            unsigned long a = StrToNumber(tmp11);
            return ((a>>8)&0xff);
        }
    }


    if(mHexStr[0]=='(')
    {
        //右括号，需要去除括号
        size_t lindex = mHexStr.find(')');
        std::string sub_str = mHexStr.substr(1, lindex-1);
        unsigned long a = StrToNumber(sub_str);
        ///FIXME 此处没有考虑运算符
        return a;
    }

    size_t lindex2 = mHexStr.find('/');
    if(lindex2 != std::string::npos)
    {
        std::vector<std::string> wds = split(mHexStr, "/");
        unsigned long a = StrToNumber( wds[0]);
        unsigned long b = StrToNumber( wds[1]);
        return a/b;
    }








    if((mHexStr[mHexStr.size()-1]=='H')||(mHexStr[mHexStr.size()-1]=='h'))
    {
        ss << std::hex << mHexStr;
        ss >> x;
        return x;
    }

    if(mHexStr.size()>2)
    {
        if((mHexStr[0]=='0')&&((mHexStr[1]=='X')||(mHexStr[1]=='x')))
        {
            ss << std::hex << mHexStr.substr(2);
            ss >> x;
            return x;
        }
    }

    if((mHexStr[mHexStr.size()-1]=='B')||(mHexStr[mHexStr.size()-1]=='b'))
    {
        x=0;
        for(unsigned i=0;i<mHexStr.size();++i)
        {
            if((mHexStr[i]!='1')&&(mHexStr[i]!='0'))
            {
                break;
            }

            x<<=1;
            if(mHexStr[i]=='1')
            {
                x+=1;
            }

        }
        return x;
    }

    //正常字符串，去掉后面有空格的地方
    //eg: 6 file_name 则只保留6
    if(mHexStr.find(' ')!=std::string::npos)
    {
        mHexStr.substr(0, mHexStr.find(' '));
    }

    if((mHexStr.size()>2)&&(mHexStr[0]=='\''))
    {
        ///ascii 转数字
        /// '12'---> (chr(1)<<8)+ chr(2)
        assert(mHexStr.size()==3);
        x = (unsigned int)(unsigned char)mHexStr[1];



        return x;

    }


    //正常数字字符串，直接转换
    ss << mHexStr;
    ss >> x;
    return x;
}
