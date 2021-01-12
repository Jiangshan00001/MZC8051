#include <assert.h>
#include <sstream>
#include "mylog.h"
#include "mem_alloc.h"


using mylog::cerr;
using mylog::cout;

mem_alloc::mem_alloc()
{
    m_max_used = 0;
    m_curr_used = 0;
    m_start = 0;
    m_end = 0;
    m_alloc_from_start = 0;
}

void mem_alloc::init_mem(long start, long end, bool from_start)
{

    m_max_used = 0;
    m_curr_used = 0;

    m_alloc_from_start = from_start;

    m_start = start;
    m_end = end;
    for(long i=m_start;i<m_end;++i)
    {
        m_reg_list.push_back(i);
    }

    m_reg_used_list.resize(end-start+1);
}


void mem_alloc::use_reg(long addr)
{
    if(addr<0)
    {
        cerr<<"ERROR: free -1 reg;\n";
        assert(0);
    }
    long index = address_to_index(addr);
    if(this->m_reg_used_list[index] !=0)
    {
        cerr<<"ERROR: use unfreed reg;\n";
        assert(0);
    }
    this->m_reg_used_list[index] =1;


    std::vector<long > &mn = m_stack_reg[m_stack_num];
    mn.push_back(addr);

    ++m_curr_used;
    if(m_max_used<m_curr_used)
    {
        m_max_used = m_curr_used;
    }

    return ;
}

long mem_alloc::free_reg(long addr)
{
    if(addr<0)
    {
        cerr<<"ERROR: free -1 reg;\n";
        assert(0);
    }
    long index = address_to_index(addr);
    if(this->m_reg_used_list[index] ==0)
    {
        cerr<<"ERROR: free unused reg;\n";
        assert(0);
    }
    this->m_reg_used_list[index] =0;

    --m_curr_used;

    return 0;
}


bool mem_alloc::try_get_reg(long &addr, int start, int end)
{
    long cnt=0;
    for(cnt=0;cnt<this->m_reg_used_list.size();cnt++)
    {
        long index = cnt;
        if(!m_alloc_from_start)
        {
            index = this->m_reg_used_list.size()-1-cnt;
        }

        if(start>=0){
         if(this->index_to_address(index)<start)continue;
        }
        if(end>=0){
         if(this->index_to_address(index)>=end)continue;
        }

        if(!this->m_reg_used_list[index])
        {
            use_reg(index_to_address(index));
            addr = this->index_to_address(index);
            return true;
        }
    }
    return false;
}

bool mem_alloc::try_get_mem(long &addr, int len, int start, int end)
{
    long cnt=0;
    int len_cnt=0;
    for(cnt=0;cnt<this->m_reg_used_list.size();cnt++)
    {
        long index = cnt;
        if(!m_alloc_from_start)
        {
            index = this->m_reg_used_list.size()-1-cnt;
        }

        if(start>=0){
         if(this->index_to_address(index)<start)continue;
        }
        if(end>=0){
         if(this->index_to_address(index)>=end)continue;
        }

        if(!this->m_reg_used_list[index])
        {
            len_cnt++;

            if(len_cnt==len)
            {
                long index_start = index ;
                if(m_alloc_from_start)
                {
                    index_start -= len_cnt-1;
                    for(long i=index_start;i<=index;++i)
                    {
                        use_reg(index_to_address(i));
                    }
                    addr = index_to_address(index_start);
                    return true;
                }
                else
                {
                    index_start += len_cnt-1;
                    for(long i=index_start;i>=index;--i)
                    {
                        use_reg(index_to_address(i));
                    }
                    addr= index_to_address(index);
                    return true;
                }
            }
        }
        else
        {
            len_cnt=0;
        }
    }

    return false;
}

long mem_alloc::get_reg(int start, int end)
{
    long addr=-1;
    try_get_reg(addr, start, end);
    return addr;
}

long mem_alloc::get_mem(int len, int start, int end)
{
    long addr=-1;
    try_get_mem(addr, len, start, end);
    return addr;
}




void mem_alloc::free_mem(long addr, int len)
{
    for(long i=addr;i<addr+len;++i)
    {
        free_reg(i);
    }
    return;
}

void mem_alloc::stack_enter(int st_num)
{
    std::vector<long > mn;
    m_stack_reg[st_num] = mn;
    m_stack_num = st_num;
    return ;
}

void mem_alloc::stack_leave(int st_num)
{
    std::vector<long > &mn = m_stack_reg[st_num];
    for(long i=0;i<mn.size();++i)
    {
        free_reg(mn[i]);
    }
    m_stack_reg.erase(m_stack_reg.find(st_num));

    return ;
}

void mem_alloc::set_stack_num(int st_num)
{
    m_stack_num = st_num;
}

long mem_alloc::address_to_index(long addr)
{
    return addr - m_start;
}

long mem_alloc::index_to_address(long index)
{
    return index + m_start;

}

std::string mem_alloc::usage()
{
    std::stringstream asm_str;
    asm_str<<"used:"<<m_max_used;
    return asm_str.str();
}
