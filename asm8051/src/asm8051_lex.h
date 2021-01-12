#ifndef ASM8051_LEX_H
#define ASM8051_LEX_H

#include <vector>
#include <string>


std::vector<std::string> template_param_parse_str(std::string str1);
std::vector<std::string> template_param_parse_str_var(std::string str1);
//unsigned long StrToNumber(std::string mHexStr);
//std::string NumberToStr(long num);
#include "str2number.h"
#include "number2str.h"


#endif // ASM8051_LEX_H
