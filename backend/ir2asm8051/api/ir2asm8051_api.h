#ifndef IR2ASM8051_API_H
#define IR2ASM8051_API_H

#include <vector>
#include <string>


/**
*
* @mainpage c8051
* @ref compile_intro
*
*
* **/

class icodes;

class ir2asm8051_api
{
public:

    std::string icode_to_asm8051(icodes* ics);
};


#endif // IR2ASM8051_API_H
