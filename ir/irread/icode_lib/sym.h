#ifndef SYM_H
#define SYM_H

#include <string>
#include <vector>


///
/// \brief The sym_table class
/// 所有变量都是地址，长度4byte
/// type: U--undefined. D-defined. A--argement. L-local
class sym
{
public:
    sym();
    std::string name;
    char type;
    unsigned int addr;
    class icode *def_icode;
    int m_level;


    int is_typedef;//是否是类型名

};


#endif // SYM_H
