#include <fstream>
#include <iostream>
#include <sstream>
//#include "asm8051.h"
#include <string.h>
#include "replace.h"
//#include "dis8051.h"
#include "asm8051_api.h"
#include "mylog.h"

using mylog::cdbg;


using namespace NS_AMS8051HEX;

#ifndef USING_QT_WID
int main( int argc, char** argv)
#else
int main_qt(int argc, char **argv)
#endif
{
    int is_debug = 0;

    cdbg.set_cout_output(0);

    if(argc<3)
    {
        std::cout<<"usage: prog -asm   	-d/-nd input_asm_file_name output_hex_file_name\n";
        std::cout<<"usage: prog -asmstr -d/-nd input_asm_str\n";
        std::cout<<"usage: prog -dis 	-d/-nd input_hex_file_name output_asm_file_name\n";
        std::cout<<"usage: prog -disstr -d/-nd input_hex_str\n";
        std::cout<<"usage: prog -yy   	-d/-nd input_asm_file_name output_hex_file_name\n";
		std::cout<<"usage: prog -yystr -d/-nd input_asm_str\n";
		std::cout<<"eg: prog -asmstr 	-d \"ORG 000H;\\nMOV 23H, 34H;\\n\"  \n";
		
        return 0;
    }

    if( strcmp(argv[2], "-nd")==0)
    {
        is_debug=0;
    }
    else
    {
        is_debug=1;
    }

    if(strcmp(argv[1], "-asm")==0)
    {
        asm_compile_file(argv[3], argv[4], is_debug);
        return 0;
    }
    else if(strcmp(argv[1], "-asmstr")==0)
    {
        asm_compile_str(argv[3], 1, is_debug);
        return 0;
    }
    else if(strcmp(argv[1], "-dis")==0)
    {
        dis_compile_file(argv[3], argv[4], is_debug);
        return 0;
    }
    else if(strcmp(argv[1], "-disstr")==0)
    {
        dis_compile_str(argv[3], 1, is_debug);
        return 0;
    }
	else if(strcmp(argv[1], "-yy")==0)
	{
        asm_compile_file_to_yy(argv[3], argv[4], is_debug);
	}
	else if(strcmp(argv[1], "-yystr")==0)
	{
        asm_compile_str_to_yy(argv[3], 1, is_debug);
	}

    return 0;
}











