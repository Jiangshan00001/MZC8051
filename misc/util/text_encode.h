#ifndef TEXT_ENCODE_H
#define TEXT_ENCODE_H

#include <string>

std::wstring AsciiToUnicode(const std::string& str);
std::string UnicodeToAscii(const std::wstring& wstr) ;
std::wstring Utf8ToUnicode(const std::string& str);
std::string UnicodeToUtf8(const std::wstring& wstr);
std::string AsciiToUtf8(const std::string& str);
std::string Utf8ToAscii(const std::string& str);
#endif // TEXT_ENCODE_H
