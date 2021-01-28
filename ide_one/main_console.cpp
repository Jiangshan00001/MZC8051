#include <stdio.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <string>

#if defined(_WIN32) || defined(__CYGWIN__) || defined(__MINGW32__)
#include <direct.h>
#include <windows.h>
#else
#include <sys/stat.h>
#include <unistd.h>
#endif


#include "argv.h"
#include "asm8051_api.h"
#include "c8051_api.h"
#include "lmake_api.h"
#include "sim8051_api.h"
#include "dir_file.h"
#include "main_var.h"
#include "mylog.h"
#include "cpp_api.h"
#include "icodes.h"
#include "ir_api.h"
#include "ir2asm8051_api.h"


using mylog::cout;
using mylog::cerr;
using mylog::cdbg;
using mylog::csummary;

///
/// \brief usage_exit
/// 命令行，帮助内容
void usage_exit()
{
    cout<<"usage: prog  -x cmd_str(c8051/asm8051/lmake/c2)  -d (for debug) -i input_file -o output_file -D define_sym -I includ_path  -n include_file  -s parse_str\n";
    cout<<"cmd_str could be: c8051/asm8051/lmake\n";
    cout<<"options for lmake: -m  create/make/clean   -i directory_here -o project_name \n";
    cout<<"prog -x lmake -m make -i directory_containing_makefile\n";
    cout<<"prog -x c8051 -i input_c_file  -c(just output .o) -o output_asm_file  -D define_sym -I includ_path  -n include_file  \n";
    cout<<"prog -x asm8051 -i input_asm_file -o output_hex_file \n";
    cout<<"prog -x sim8051 -i input_hex_file\n";
    cout<<"prog -x dis8051 -i input_hex_file -o output_asm_file\n";
    cout<<"prog -x c2 -i input_c_file -o output_file_name -t output_type(c/)  -O number\n";
    cout<<"prog -x cpp -i input_c_file -o output_file_name  -D define_sym -I includ_path  -n include_file\n";
    cout<<"prog -x c2ir -i input_c_file -o output_file_name\n";
    cout<<"prog -x ir2ir -i input_ir_file [-i input_ir_file2 ] -o output_file_name\n";
    cout<<"prog -x ir2asm8051  -i input_ir_file  [-i input_ir_file2 ] -o output_file_name\n";

    exit(0);
}

///
/// \brief set_log_path
/// \param file_path
/// \param cmd_str
/// 记录路径和文件设置
void set_log_path(std::string file_path, std::string cmd_str)
{
    std::string path1 = get_path(file_path);

    if(cmd_str=="lmake")
    {
        path1=file_path;
    }
    else
    {
        path1 = get_path(file_path);
    }

    std::cout<<"log path1:"<<path1<<"\n";

    std::cout<<"log_file:"<<path_add( path1, cmd_str+ "_log"+ ".tmp")<<std::endl;

    cout.set_log_file(path_add( path1, cmd_str+ "_log"+ ".tmp"));
    cerr.set_log_file(path_add( path1,  cmd_str + "_err"+ ".tmp"));

    cout<<"======================\n";
    time_t now_time;
    char tmp[64];
    now_time = time(NULL);
    strftime( tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&now_time) );
    cout<<tmp<<"\n";

    cdbg.set_cout_output(0);
}

///
/// \brief argv_print 调试函数，
/// \param argc
/// \param argv
///
void argv_print(int argc, char *argv[])
{
    for(int i=0;i<argc;++i)
    {
        cout<<"arg:"<<i<<argv[i]<<"\n";
    }
    cout<<"\n";
    return;
}

#ifdef QT_WIDGETS_LIB
int main_test(int argc, char * argv[])
#else
int main(int argc, char * argv[])
#endif
{

    // assume the command is : Demo -A -b somevalue -c othervalue
    ArgsParser arg(argc, argv);



    G_PROG_NAME=argv[0];



    char *pwd_abs = getcwd(NULL, 0);


    bool is_debug_flag = arg.HaveOption('d');

    int is_just_c = arg.HaveOption('c');


    std::string cmd_str = arg.GetOption('x');

    std::vector<std::string> input_file = arg.GetOptionVec('i');

    if(input_file.size()>0)
    {
        set_log_path(input_file[0], cmd_str);

        //记录当前命令行
        for(unsigned i=0;i<argc;++i)
        {
            cout<<argv[i]<<" ";
        }
        cout<<"\n";
    }





    std::string output_file = arg.GetOption('o');

    std::string parse_str = arg.GetOption('s');
    std::string make_cmd = arg.GetOption('m');


    int opt_flag = arg.GetOptionInt('O', 0);



    std::vector<std::string> include_file = arg.GetOptionVec('n');
    std::vector<std::string> defined_sym = arg.GetOptionVec('D');
    std::vector<std::string> include_path = arg.GetOptionVec('I');





    cout<<"================\n";
    cout<<"cmd_str:"<<cmd_str<<std::endl;
#if 0
    cout<<"is_just_c:"<<is_just_c<<std::endl;
    cout<<"is_debug_flag:"<<is_debug_flag<<std::endl;
    cout<<"input_file:"<<input_file.size()<<std::endl;
    for(unsigned i=0;i<input_file.size();++i)
    {
        cout<<i<<":"<<input_file[i]<<std::endl;
    }
    cout<<"output_file:"<<output_file<<std::endl;
    cout<<"parse_str:"<<parse_str<<std::endl;
    cout<<"make_cmd:"<<make_cmd<<std::endl;
    cout<<"include_file:"<<include_file.size()<<std::endl;
    for(unsigned i=0;i<include_file.size();++i)
    {
        cout<<i<<":"<<include_file[i]<<std::endl;
    }
    cout<<"defined_sym:"<<defined_sym.size()<<std::endl;
    for(unsigned i=0;i<defined_sym.size();++i)
    {
        cout<<i<<":"<<defined_sym[i]<<std::endl;
    }
    cout<<"include_path:"<<include_path.size()<<std::endl;
    for(unsigned i=0;i<include_path.size();++i)
    {
        cout<<i<<":"<<include_path[i]<<std::endl;
    }
    cout<<"opt_flag:"<<opt_flag<<std::endl;
#endif
    cout<<"================\n";



    if(cmd_str.size()==0)
    {
        cerr<<"-x MUST have one cmd!\n";
        usage_exit();
    }
    if((input_file.size()==0)&& (parse_str.size()==0))
    {
        cerr<<"-i -s at least have one!\n";
        usage_exit();
    }


    if(cmd_str=="cpp")
    {
        cpp_api m_cpp;
        m_cpp.c_do_cpp(input_file[0], output_file,include_file, defined_sym, include_path, is_debug_flag);
    }
    else if(cmd_str=="c2ir")
    {
        c8051_api m_api;
        icodes* ics = m_api.c_to_icode(input_file[0],is_debug_flag);
        std::ofstream fout(output_file);
        fout<<ics->m_top_icodes->to_str();
        fout.close();
        delete ics;
    }
    else if(cmd_str=="ir2ir")
    {
        if(input_file.size()>1)
        {

            ir_api m_ir;
            icodes *ics = m_ir.ir_to_icode(input_file, is_debug_flag);
            std::ofstream fout(output_file);
            fout<<ics->m_top_icodes->to_str();
            fout.close();
            delete ics;
        }
        else
        {
            ir_api m_ir;
            icodes *ics = m_ir.ir_to_icode(input_file[0], is_debug_flag);
            std::ofstream fout(output_file);
            fout<<ics->m_top_icodes->to_str();
            fout.close();
            delete ics;
        }
    }
    else if(cmd_str=="ir2asm8051")
    {
        ///fixme: 此处寻找3个文件：
        /// _sys_func_def.ir
        /// _simtrap.ir
        /// intrins.ir
        /// 认为在第一个include目录中


        input_file.push_back(path_add(include_path[0] , "_sys_func_def.ir"));
        input_file.push_back(path_add(include_path[0] , "_simtrap.ir"));
        input_file.push_back(path_add(include_path[0] , "intrins.ir"));


        ir_api m_ir;
        icodes *ics = m_ir.ir_to_icode(input_file, is_debug_flag);

        if(is_debug_flag)
        {
            std::ofstream fout1(output_file+".tmp");
            fout1<<ics->m_top_icodes->to_str();
            fout1.close();
        }

        ir2asm8051_api m_asm;
        std::string out_str = m_asm.icode_to_asm8051(ics);
        std::ofstream fout(output_file);
        fout<<out_str;
        fout.close();
        delete ics;
        return -cerr.m_line_count;
    }
    else if(cmd_str=="c8051")
    {
        cpp_api m_cpp;
        std::string out_cpp = m_cpp.c_do_cpp(input_file[0], include_file, defined_sym, include_path, is_debug_flag);
        c8051_api m_api;
        icodes* ics = m_api.c_to_icode(out_cpp,input_file[0],is_debug_flag);

        if(is_just_c)
        {
            std::ofstream fout(output_file);
            fout<<ics->m_top_icodes->to_str();
            fout.close();
            delete ics;
            return -cerr.m_line_count;
        }


        ir2asm8051_api m_asm;
        std::string out_str = m_asm.icode_to_asm8051(ics);
        std::ofstream fout(output_file);
        fout<<out_str;
        fout.close();
        delete ics;

        return -cerr.m_line_count;
        //translate_c_to_asm(input_file, parse_str, output_file, include_file, defined_sym, include_path, is_just_c, is_debug_flag);
    }
    else if(cmd_str=="asm8051")
    {
        translate_asm_to_hex(input_file, parse_str, output_file, is_debug_flag);
    }
    else if(cmd_str=="lmake")
    {
        if(make_cmd.size()==0)
        {
            usage_exit();
        }
        if(make_cmd=="create")
        {
            make_new_project((char*)input_file[0].c_str(), (char*)output_file.c_str());
        }
        else if(make_cmd=="make")
        {
            make((char*)input_file[0].c_str());

        }
        else if(make_cmd=="clean")
        {
            make_clean((char*)input_file[0].c_str());
        }
        else
        {
            usage_exit();
        }
    }
    else if(cmd_str=="sim8051")
    {
        // sim8051
        sim8051_run(input_file[0]);
    }
    else if(cmd_str=="dis8051")
    {//int dis_compile_file(std::string in_file, std::string out_file, int is_debug);
        dis_compile_file(input_file[0], output_file, 1);
    }
    else if(cmd_str=="c2")
    {//prog -x c2 -i input_c_file -o ouput_file_name -t output_type(c/)

        std::string otype = arg.GetOption('t');
        //translate_c_to(input_file[0],otype, output_file,include_file,defined_sym,include_path, opt_flag);
        cerr<<"unsupported now\n";

    }
    else
    {
        cerr<<"unknown cmd:"<<cmd_str<<"\n" ;
        usage_exit();
    }


    if(cerr.m_line_count>0)
    {
        csummary<<"ERRCNT:"<<cerr.m_line_count<<"\n";
        return -cerr.m_line_count;
    }
    else
    {
        return 0;
    }

    return 0;
}

