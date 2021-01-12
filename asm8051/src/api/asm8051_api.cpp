#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "asm8051_api.h"
#include "asm8051.h"
#include "dis8051.h"
#include "replace.h"
std::string asm_compile(const std::string& in, std::string in_file_name, int is_debug)
{
    asm8051 m_8051;
    m_8051.m_is_debug = is_debug;
    m_8051.add_src(in, in_file_name);
    m_8051.compile();

    std::string mout = m_8051.generate_hex();
    return mout;
}


std::string dis_compile(const std::string& in, int is_debug)
{
    dis8051 m_dis8051;
    //m_dis8051.clear();
    std::string ret = m_dis8051.add_hex_str(in);
    return ret;
}

int dis_compile_file(std::string in_file, std::string out_file, int is_debug)
{
    std::ifstream fin;
    fin.open(in_file);

    std::stringstream a;
    a<< fin.rdbuf();

    std::string mout = dis_compile(a.str(), is_debug);
    std::ofstream fout;
    fout.open(out_file);

    fout<<mout;
    fout.close();
    fin.close();
    return 0;
}

int asm_compile_file(std::string asm_file, std::string hex_file, int is_debug)
{
    std::ifstream fin;
    fin.open(asm_file);

    std::stringstream a;
    a<< fin.rdbuf();

    std::string mout = asm_compile(a.str(),asm_file, is_debug);
    std::ofstream fout;
    fout.open(hex_file);

    fout<<mout;
    fout.close();
    fin.close();
    return 0;
}

std::string asm_compile_str(std::string asm_str,int is_out_to_cout, int is_debug)
{
    replace(asm_str, "\\n", "\n");

    std::string mout = asm_compile(asm_str, "str", is_debug);

    if(is_out_to_cout)
    {
        std::cout<<mout;
    }


    return mout;
}

std::string dis_compile_str(std::string hex_str,int is_out_to_cout, int is_debug)
{
    replace(hex_str, "\\n", "\n");

    std::string mout = dis_compile(hex_str, is_debug);

    if(is_out_to_cout)
    {
        std::cout<<mout;
    }
    return mout;
}

void translate_asm_to_hex(std::vector<std::string> &input_file, std::string parse_str, std::string output_file, bool is_debug)
{
    asm8051 m_8051;

    m_8051.m_is_debug = is_debug;

    //此处没有预处理，只是把所有文件读出顺序合并，然后输出

    if(input_file.size()>0)
    {
        for(unsigned i=0;i<input_file.size();++i)
        {
            std::string in_file_name = input_file[i];
            std::ifstream ifile(in_file_name);

            std::stringstream ibstream;
            ibstream<< ifile.rdbuf();
            std::string in_buf = ibstream.str();

            m_8051.add_src(in_buf, in_file_name);
        }
    }
    else
    {
        m_8051.add_src(parse_str, "str");
    }

    m_8051.compile();
    std::string mout = m_8051.generate_hex();
    std::ofstream ofile(output_file);
    ofile<<mout;
    ofile.close();
    return;
}



