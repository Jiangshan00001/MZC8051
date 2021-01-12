#include <assert.h>
#include "reg_alloc.h"
#include "mylog.h"


using mylog::cerr;
using mylog::cout;

reg_alloc::reg_alloc()
{
}



int reg_alloc::init_reg(std::vector<int> reg_num)
{
    this->m_reg_list = reg_num;
    this->m_reg_used_list.resize(this->m_reg_list.size());
    return 0;
}

int reg_alloc::get_reg(int start, int end)
{
   unsigned cnt=0;
   for(cnt=0;cnt<this->m_reg_used_list.size();cnt++)
   {
       if(start>=0){
        if(this->m_reg_list[cnt]<start)continue;
       }
       if(end>=0){
        if(this->m_reg_list[cnt]>end)continue;
       }


       if(!this->m_reg_used_list[cnt])
       {
           this->m_reg_used_list[cnt]=1;
           return this->m_reg_list[cnt];
       }
   }

   cerr<<"ERROR: reg alloc error; start="<<start<<". end="<<end<<"\n";
   assert(0);
   return -1;
}

int reg_alloc::free_reg(int reg_num)
{
    for(unsigned i=0;i<this->m_reg_list.size();++i)
    {
        if(this->m_reg_list[i]==reg_num)
        {
            if(this->m_reg_used_list[i] ==0)
            {
                cerr<<"ERROR: free unused reg;\n";
                assert(0);
            }
            this->m_reg_used_list[i] =0;
            break;
        }
    }
    return 0;
}
