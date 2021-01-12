#ifndef REG_ALLOC_H
#define REG_ALLOC_H

#include <vector>
#include <string>


class reg_alloc{
public:
    reg_alloc();
    std::vector<int > m_reg_list;
    std::vector<int > m_reg_used_list;
    int init_reg(std::vector<int> reg_num);
    int get_reg(int start=-1, int end=-1);
    int free_reg(int reg_num);
};

#endif // REG_ALLOC_H
