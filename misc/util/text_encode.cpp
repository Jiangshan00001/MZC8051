#include <windows.h>
#include <string>

#include "text_encode.h"

using namespace std;

wstring AsciiToUnicode(const string& str)
{
    // 预算-缓冲区中宽字节的长度
    int unicodeLen = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
    // 给指向缓冲区的指针变量分配内存
    wchar_t *pUnicode = (wchar_t*)malloc(sizeof(wchar_t)*unicodeLen);
    // 开始向缓冲区转换字节
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, pUnicode, unicodeLen);
    wstring ret_str = pUnicode;
    free(pUnicode);
    return ret_str;
}

string UnicodeToAscii(const wstring& wstr)
{
    // 预算-缓冲区中多字节的长度
    int ansiiLen = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    // 给指向缓冲区的指针变量分配内存
    char *pAssii = (char*)malloc(sizeof(char)*ansiiLen);
    // 开始向缓冲区转换字节
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, pAssii, ansiiLen, nullptr, nullptr);
    string ret_str = pAssii;
    free(pAssii);
    return ret_str;
}

wstring Utf8ToUnicode(const string& str)
{
    // 预算-缓冲区中宽字节的长度
    int unicodeLen = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
    // 给指向缓冲区的指针变量分配内存
    wchar_t *pUnicode = (wchar_t*)malloc(sizeof(wchar_t)*unicodeLen);
    // 开始向缓冲区转换字节
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, pUnicode, unicodeLen);
    wstring ret_str = pUnicode;
    free(pUnicode);
    return ret_str;
}

string UnicodeToUtf8(const wstring& wstr)
{
    // 预算-缓冲区中多字节的长度
    int ansiiLen = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    // 给指向缓冲区的指针变量分配内存
    char *pAssii = (char*)malloc(sizeof(char)*ansiiLen);
    // 开始向缓冲区转换字节
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, pAssii, ansiiLen, nullptr, nullptr);
    string ret_str = pAssii;
    free(pAssii);
    return ret_str;
}

string AsciiToUtf8(const string& str)
{
    return UnicodeToUtf8(AsciiToUnicode(str));
}

string Utf8ToAscii(const string& str)
{
    return UnicodeToAscii(Utf8ToUnicode(str));
}

//————————————————
//版权声明：本文为CSDN博主「江左周郎」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
//原文链接：https://blog.csdn.net/Best_ZYJ/article/details/79011502


