#ifndef REPLACE_H
#define REPLACE_H

#include <string>

//在原字符串上替换，不会复制
std::string& replace(std::string& str, const std::string& to_replaced, const std::string& newchars);

#endif // REPLACE_H
