#ifndef ASMC51_PREDEFINED_SYMBOL_H
#define ASMC51_PREDEFINED_SYMBOL_H
#include <map>
#include <string>
class asmc51_predefined_symbol
{
public:
    asmc51_predefined_symbol();
    std::map<std::string, unsigned> get_symbols();
    std::map<std::string, unsigned> m_symbols;
};

#endif // ASMC51_PREDEFINED_SYMBOL_H
