#include "split.h"

std::vector<std::string>  split(std::string str, std::string token, bool remove_empty)
{
    std::vector<std::string>result;
       while(str.size())
       {


           unsigned index = str.find(token);

           if(index!=std::string::npos)
           {

               result.push_back(str.substr(0,index));
               str = str.substr(index+token.size());
               if(str.size()==0)result.push_back(str);
           }
           else
           {
               result.push_back(str);
               str = "";
           }
       }




       if(remove_empty)
       {
           ///去除空word
           auto it=result.begin();
           while(it!=result.end())
           {
               if(it->size()==0)
               {
                   if(it==result.begin())
                   {
                       result.erase(result.begin());
                       it=result.begin();
                   }
                   else
                   {
                       auto old_it=it;
                       it--;
                       result.erase(old_it);
                   }
               }
               else
               {
                   ++it;
               }
           }
       }

       return result;
}
