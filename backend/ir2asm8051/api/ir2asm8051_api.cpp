#include "ir2asm8051_api.h"

#include <iostream>
#include <fstream>

#include "replace.h"

#include "main_var.h"

#include "dir_file.h"
#include "mylog.h"
#include "icodes.h"
#include "icode_to_c51.h"
#include "c51_filter_manage.h"
#include "c51_asm_opt.h"

using mylog::cout;
using mylog::cerr;





std::string ir2asm8051_api::icode_to_asm8051(icodes *ics)
{
    c51_filter_manage m_filter;
    icode_to_c51 m_c51(ics);

    m_filter.do_filter(ics);
    std::string asm_str= m_c51.to_asm(ics);
    c51_asm_opt m_opt2;
    asm_str = m_opt2.pin_hole(asm_str);

    return asm_str;

}
