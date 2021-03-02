#ifndef STRING_EVAL_H
#define STRING_EVAL_H

#include <string>

///
/// \brief string_eval
/// \param str1
/// \return
/// c语言的字符串输入转为真是的字符串，主要是转义字符替换等
std::string string_eval(std::string str_raw);

/// 将真实的字符串，转为显示用的字符串。主要是回车符转为 \n
std::string string_pack(std::string stri);

#endif // STRING_EVAL_H
