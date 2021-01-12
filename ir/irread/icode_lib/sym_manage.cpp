#include "sym_manage.h"

sym_manage::sym_manage()
{
    m_level = 0;
}

void sym_manage::add_symbol(std::string &name, icode *pdef, int level)
{
    sym a;
    a.name = name;
    a.def_icode = pdef;
    if(level==-1)
    {
        a.m_level = this->m_level;
    }
    m_symbols.push_back(a);
}

sym *sym_manage::find_symbol(const std::string &name)
{
#if 1
  ///此处为查找符号表
  for(unsigned i=0;i<m_symbols.size();++i)
  {
      unsigned t_index = m_symbols.size()-1-i;
      if(m_symbols[t_index].name == name)
      {
          //cout<<"sym_lookup:"<<name<<". type:"<<m_symbols[t_index].type<<". addr:"<<m_symbols[t_index].addr<<std::endl;
          return &m_symbols[t_index];
      }
  }
#endif
  return NULL;
}

unsigned sym_manage::get_symbol_list_size()
{
    return m_symbols.size();
}

int sym_manage::set_symbol_list_size(unsigned nsize)
{
    m_symbols.resize(nsize);
    return 0;
}

int sym_manage::level_enter()
{
    m_level++;
    int tmp = get_symbol_list_size();
    m_last_sym_size.push_back(tmp);
    return 0;
}

int sym_manage::level_leave()
{
    m_level--;
    int tmp = m_last_sym_size[m_last_sym_size.size()-1];
    set_symbol_list_size(tmp);
    m_last_sym_size.pop_back();
    return 0;
}
