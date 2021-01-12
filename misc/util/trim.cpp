#include "trim.h"

std::string& trim1(std::string &s, char tr_char)
{
    if (s.empty())
    {
        return s;
    }

    s.erase(0,s.find_first_not_of(tr_char));
    s.erase(s.find_last_not_of(tr_char) + 1);
    return s;
}


std::string& trim(std::string &s)
{
    if (s.empty())
    {
        return s;
    }

    s.erase(0,s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);

    s.erase(0,s.find_first_not_of("\t"));
    s.erase(s.find_last_not_of("\t") + 1);

    s.erase(0,s.find_first_not_of("\r"));
    s.erase(s.find_last_not_of("\r") + 1);

    s.erase(0,s.find_first_not_of("\n"));
    s.erase(s.find_last_not_of("\n") + 1);
    return s;
}
