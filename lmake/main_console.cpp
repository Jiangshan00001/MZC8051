#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include "lmake_api.h"
#include "myexecute.h"

///https://my.oschina.net/SKII/blog/615073
/// 使用CommandLineToArgvW获得Unicode版本GUI程序的命令行参数
/// https://zhidao.baidu.com/question/1176134471712307339.html
/// 为什么 mingw 不支持 Unicode 的 main 函数
/// #ifdef UNICODE
/// int main(void)
/// {
/// int argc;
/// wchar_t **argv = CommandLineToArgvW(GetCommandLineW(), &argc);
/// #else
/// int main(int argc, char *argv[])
/// {
/// #endif




/// 此变量和main函数在一个文件中
std::string G_PROG_NAME;

/// 1 生成新的空项目
///
int main(int argc, char * argv[])
{
    std::vector<std::string> src_c;
    std::vector<std::string> src_a51;
    std::string proj_name;
    double version;

    std::cout<<"lmake test\n";

    G_PROG_NAME=argv[0];


    myexecute_ansi("ping.exe", "www.baidu.com", 1, "./test_ping.txt");


#if 0

    read_makefile("../../src/ide_one/test1", src_c, src_a51, proj_name, version);
#endif

	return 0;
}

