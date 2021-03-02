#include <sstream>
#include "ir2x86_api.h"

//#include "icode_collect_global_var.h"
#include "code_gen_x86.h"

ir2x86_api::ir2x86_api()
{
}

std::string ir2x86_api::icode_to_asm(icodes *ics)
{
    /// ir转为asm的流程：
    /// 1 全局变量内存空间分配
    /// 2 局部变量的内存空间分配
    /// 3 代码生成
    std::stringstream istr;

    ///----------------------------------------------
    code_gen_x86 m_code_gen;

    m_code_gen.execute(ics, istr);

    return istr.str();
}
