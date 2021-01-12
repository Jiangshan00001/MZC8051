#include "c8051_api.h"

#include <iostream>
#include <fstream>


#include "../lex_yacc_adapt/driver.h"
#include "../context/comp_context.h"
#include "replace.h"

#include "main_var.h"

#include "simplecpp.h"
#include "dir_file.h"
#include "mylog.h"
#include "icodes.h"


using mylog::cout;
using mylog::cerr;



icodes* c8051_api::c_to_icode(std::istream & istr, std::string file_name, int is_debug)
{
    NS_C2IR::comp_context calc;
    NS_C2IR::Driver driver(calc);


    driver.trace_parsing = is_debug;
    driver.trace_scanning = is_debug;
    bool result = driver.parse_stream(istr, file_name);

    return calc.m_top_icodes;
}

icodes* c8051_api::c_to_icode(std::string file_name, int is_debug)
{
    std::ifstream fin(file_name);
    return c_to_icode(fin, file_name, is_debug);
}

icodes* c8051_api::c_to_icode(std::string file_str, std::string file_name, int is_debug)
{
    std::stringstream ss(file_str);
    return c_to_icode(ss, file_name, is_debug);
}

std::string c8051_api::c_to_yy(std::istream &istr, std::string file_name, int is_debug)
{
    NS_C2IR::comp_context calc;
    NS_C2IR::Driver driver(calc);


    calc.m_just_ret_tree=1;
    driver.trace_parsing = is_debug;
    driver.trace_scanning = is_debug;
    bool result = driver.parse_stream(istr, file_name);

    return calc.m_yy_tree;
}

std::string c8051_api::c_to_yy(std::string file_name, int is_debug)
{
    std::ifstream fin(file_name);
    return c_to_yy(fin, file_name, is_debug);
}

std::string c8051_api::c_to_yy(std::string file_str, std::string file_name, int is_debug)
{
    std::stringstream ss(file_str);
    return c_to_yy(ss, file_name, is_debug);
}

#if 0
std::string c2a_compile(const std::string& in, std::string &file_name, int is_debug, int is_just_c)
{
    comp_context calc;
    example::Driver driver(&calc);
    if(is_debug)
    {
        calc.m_is_debug=1;
        driver.trace_parsing = true;
    }
    else
    {
        calc.m_is_debug=0;
    }
    driver.trace_parsing = false;

    //driver.trace_scanning = true;

    cout<<"parse start\n";
    driver.parse_string(in, file_name);

    cout<<"parse finish\n";
    std::string mout;
    mout= driver.pcompi->generate_hex(is_just_c);

    cout<<"generate asm finish\n";
    return mout;
}


int c2a_compile_str(std::string c_str,int is_out_to_cout, int is_debug, std::string in_file_name, std::string out_file, int is_just_c)
{
    std::string mout = c2a_compile(c_str,in_file_name, is_debug, is_just_c);

    if(is_out_to_cout)
    {
        cout<<mout;
    }
    if(out_file.size()>0)
    {
        cout<<"writing to outfile:"<<out_file<<"\n";
        std::ofstream fout;
        fout.open(out_file);
        fout<<mout;
        fout.close();
        cout<<"writing to outfile finish"<<"\n";

    }
    return 0;
}

int mzo2a(std::vector<std::string> &input_file, std::string output_file, std::vector<std::string> &include_file,std::vector<std::string> &include_path, bool is_debug)
{
    comp_context calc;
    example::Driver driver(&calc);
    if(is_debug)
    {
        calc.m_is_debug=1;
        driver.trace_parsing = true;
    }
    else
    {
        calc.m_is_debug=0;
    }
    driver.trace_parsing = false;

    std::string mout;

    driver.streamname = "_mzo";
    for(int i=0;i<input_file.size();++i)
    {
        std::ifstream fin;
        fin.open(input_file[i]);
        std::stringstream ss1;
        ss1<<fin.rdbuf();
        driver.pcompi->merge_mzo(ss1.str());
    }


    mout = driver.pcompi->generate_hex(0);
    std::ofstream fout;
    fout.open(output_file);
    fout<<mout;
    fout.close();
    return 0;
}

void translate_c_to_asm(std::vector<std::string> &input_file, std::string parse_str, std::string output_file, std::vector<std::string> &include_file,
                        std::vector<std::string> &defined_sym, std::vector<std::string> &include_path, int is_just_c, bool is_debug)
{
    ///此函数进行分类处理：
    /// 输入： 单个.c文件
    ///       多个.c文件
    ///       单个.mzo文件
    ///       多个.mzo文件
    /// 选项：-c
    ///
    /// 历史功能：is_just_c=0, 输入单个.c文件。生成.a51文件
    /// 新功能： is_just_c=1，输入单个.c文件，生成.mzo文件
    /// 新功能： is_just_c=0 输入多个.mzo文件，生成a51文件
    /// 历史遗留功能：str字符串编译为a51
    ///

    bool is_mzo = 0;
    if(input_file.size()>0)
    {
        if(input_file[0].size()>3)
        {
            int sz = input_file[0].size();
            if(((input_file[0][sz-1]=='o')||(input_file[0][sz-1]=='O'))&&
                    ((input_file[0][sz-2]=='z')||(input_file[0][sz-2]=='Z'))&&
                    ((input_file[0][sz-3]=='m')||(input_file[0][sz-3]=='M')))
            {
                is_mzo = 1;
            }
        }
    }

    if(is_mzo)
    {
        mzo2a(input_file, output_file, include_file, include_path, is_debug);
        return;
    }



    for(unsigned i=0;i<input_file.size();++i)
    {
        std::string ifile = input_file[i];

        if(!is_just_c)
        {
            //-c选项，是从.c 转为.o
            ///2020.8.12 添加_sys_func_def.h的默认包含，因为 int float的部分算符是通过函数实现的
            int need_add_sys=1;
            for(unsigned i=0;i<include_file.size();++i)
            {
                if(include_file[i]=="_sys_func_def.h")
                {
                    need_add_sys = 0;
                }
            }
            if(need_add_sys)
            {
                include_file.push_back("_sys_func_def.h");
            }
            ///----------------------------

        }
        {
            parse_str = do_cpp(ifile, include_file, defined_sym,include_path,is_debug);


            if(is_debug)
            {
                std::string proc_dbg_file = file_without_extension( ifile)+".prc";
                std::ofstream fout(proc_dbg_file);
                fout<<parse_str;
                fout.close();
            }

            if(is_debug)
            {
                std::string proc_dbg_file = file_without_extension( ifile)+".tk";
                std::ofstream fout(proc_dbg_file);
                fout<<"//file token parse file\n";
                fout.close();
            }
            c2a_compile_str(parse_str, 0, is_debug, ifile, output_file, is_just_c);
        }
    }


    if(input_file.size()==0)
    {
        ///如果是字符串，则只做一个预处理
        replace(parse_str, "\\n", "\n");
        c2a_compile_str(parse_str, 0, is_debug, "str", output_file);
    }

}

#endif
