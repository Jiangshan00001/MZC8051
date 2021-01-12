#ifndef CODE_GEN_PARAM_PARSE_H
#define CODE_GEN_PARAM_PARSE_H

#include <vector>
#include <string>

std::vector<std::string> template_param_parse_str(std::string str1);
std::vector<std::string> template_param_parse_str_var(std::string str1);
std::vector<std::string> template_param_parse_str_var_range(std::string str1);
std::vector<int> template_param_parse_str_var_range_8bit_sign(std::string str1);
#endif // CODE_GEN_PARAM_PARSE_H
