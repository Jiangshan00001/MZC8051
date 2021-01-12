#include "comp_context.h"
#include "icode.h"
#include "token_defs.h"
#include "parser.h"
#include "driver.h"
#include "target_base.h"
#include "comp_context_gen_defs.h"
#include "mylog.h"

//#include "target_base.h"


using mylog::cerr;
using mylog::cout;

namespace NS_IR2ICODE{

comp_context::comp_context()
{
    //m_target = new icode_to_c51(this);
}


void comp_context::add_translation_unit(token_defs &start_tk)
{

    icode* ic = this->ast_to_icode(&start_tk, 1, 0);
    this->m_top_icodes->m_top_icodes->merge_icode(ic);
}







}


