#ifndef COMP_CONTEXT_YY_DEBUG_H
#define COMP_CONTEXT_YY_DEBUG_H

#include <vector>
#include <string>

typedef struct TAG_T_DEBUG_LIST
{
  int m_type;
    std::string m_name;
}T_DEBUG_LIST;

extern std::vector<T_DEBUG_LIST>g_ast_debug_str;
extern std::vector<T_DEBUG_LIST>g_elem_debug_str;
#endif // COMP_CONTEXT_YY_DEBUG_H
