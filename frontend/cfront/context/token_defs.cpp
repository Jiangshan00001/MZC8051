#include "token_defs.h"


namespace NS_C2IR{

token_defs::token_defs()
{
}

void token_defs::print()
{
    print_self();
    for(int i=0;i<m_tk_elems.size();++i)
    {
        m_tk_elems[i]->print();
    }


}

void token_defs::print_self()
{

}


token_defs g_tk;
token_defs &gempty_token()
{
    g_tk.m_type = TOKEN_DEFS_TYPE_ELEM;

return g_tk;
}

token_defs *parser_ntoken(token_defs& tk)
{
    token_defs * tk_tmp = new token_defs();
    *tk_tmp = tk;
    return tk_tmp;
}



}
