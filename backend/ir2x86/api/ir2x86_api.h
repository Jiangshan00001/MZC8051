#ifndef IR2X86_API_H
#define IR2X86_API_H
#include <string>

class icodes;

class ir2x86_api
{
public:
    ir2x86_api();

public:

    std::string icode_to_asm(icodes* ics);
};

#endif // IR2X86_API_H
