#include "replace.h"



std::string& replace(std::string& str, const std::string& to_replaced, const std::string& newchars)
{
    for(std::string::size_type pos(0); pos != std::string::npos; pos += newchars.length())
    {
        pos = str.find(to_replaced,pos);
        if(pos!=std::string::npos)
           str.replace(pos,to_replaced.length(),newchars);
        else
            break;
     }
     return   str;
}

