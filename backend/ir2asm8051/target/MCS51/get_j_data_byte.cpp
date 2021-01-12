#include "get_j_data_byte.h"
#include "c51_addr.h"



unsigned get_j_data_byte(c51_addr *jdata, int byte_shift)
{
    //立即数。如果是

    return ( ((0xff<<(byte_shift*8))& jdata->m_addr) >>(byte_shift*8)  );
}
