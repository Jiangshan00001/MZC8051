#include "bit_addr_parse.h"

namespace NS_AMS8051HEX
{

bool bit_addr_parse(unsigned a, unsigned b, unsigned &bit_addr)
{
    if((a>=0x20)&&(a<=0x2f))
    {
        bit_addr = (a-0x20)*8 +b;
    }
    else if((a>=0x80)&&(a<=0xff))
    {
        bit_addr = a + b;
    }
    else
    {
        bit_addr = 0;
        return false;
    }
    return true;
}


}
