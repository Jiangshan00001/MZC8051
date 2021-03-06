#ifndef C51_ASM_OPT_H
#define C51_ASM_OPT_H
#include <string>

class c51_asm_opt
{
public:
    c51_asm_opt();
    std::string pin_hole(std::string &in_asm);

};

#endif // C51_ASM_OPT_H
