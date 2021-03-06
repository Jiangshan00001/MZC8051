#ifndef REG_ALLOC2_H
#define REG_ALLOC2_H

#include <vector>
#include <string>
#include "mylog.h"



using mylog::cerr;
using mylog::cout;


template<class reg_type>
class reg_alloc2{
public:
    reg_alloc2()
    {
    }
    ///默认的reg_type=int
    std::vector<reg_type > m_reg_list;
    std::vector<int > m_reg_used_list;
    int add_reg(reg_type reg1)
    {
        this->m_reg_list.push_back(reg1);
        this->m_reg_used_list.resize(this->m_reg_list.size());
        return 0;
    }

    int init_reg(std::vector<reg_type> reg_num)
    {
        this->m_reg_list = reg_num;
        this->m_reg_used_list.resize(this->m_reg_list.size());
        return 0;
    }
    reg_type get_reg()
    {
        unsigned cnt=0;
        for(cnt=0;cnt<this->m_reg_used_list.size();cnt++)
        {
            if(!this->m_reg_used_list[cnt])
            {
                this->m_reg_used_list[cnt]=1;
                return this->m_reg_list[cnt];
            }
        }
        return reg_type();
    }

    reg_type get_reg(reg_type start, reg_type end)
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
        return reg_type();
    }
    int free_reg(reg_type reg_num)
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
};

#endif // REG_ALLOC_H
