#ifndef MEM_ALLOC_H
#define MEM_ALLOC_H

#include <vector>
#include <string>
#include <map>

/// 用于8051的data, idata, xdata 的申请和释放
///
///
///
///
class mem_alloc
{
public:
    mem_alloc();

    void init_mem(long start, long end, bool from_start);



    void use_reg(long addr);
    long free_reg(long addr);

    long get_reg(int start=-1, int end=-1);
    long get_mem(int len, int start=-1, int end=-1);

    bool try_get_reg(long &addr, int start=-1, int end=-1);
    bool try_get_mem(long &addr, int len, int start=-1, int end=-1);
    void free_mem(long addr, int len);

    ///这两个函数，是在堆栈式内存分配中使用。
    /// 如果顺序调用此2个函数，则两个函数之间申请的内存会全部释放
    void stack_enter(int st_num);
    void stack_leave(int st_num);
    void set_stack_num(int st_num);
    long address_to_index(long addr);
    long index_to_address(long index);

    std::string usage();



    std::vector<long > m_reg_list;
    std::vector<bool > m_reg_used_list;
    long m_start;
    long m_end;
    bool m_alloc_from_start;

    std::map<long, std::vector<long > > m_stack_reg;

    int m_max_used;
    int m_curr_used;

    int m_stack_num;



};

#endif // MEM_ALLOC_H

