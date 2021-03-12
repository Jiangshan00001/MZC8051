#ifndef ASM_EXTEND_JMP_H
#define ASM_EXTEND_JMP_H

#include <string>

namespace NS_AMS8051HEX{

class icode;
class asm_extend_jmp
{
public:
    asm_extend_jmp();
    int extend_jmp_one_cmd(icode *ic);
    static int m_ext_index;
    std::string get_tmp_label(std::string prefix);
};

}
#endif // ASM_EXTEND_JMP_H
