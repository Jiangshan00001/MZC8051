#if defined(_WIN32) || defined(__CYGWIN__) || defined(__MINGW32__)
#include <direct.h>
#else
#include<unistd.h>
#include <sys/stat.h>

#endif


#include <time.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "lmake_api.h"
#include "replace.h"
#include "dir_file.h"
#include "trim.h"
#include "split.h"
#include "text_encode.h"
#include "mylog.h"
#include "myexecute.h"


using mylog::cout;
using mylog::cerr;

void make_new_project(char * directory_path, char *project_name)
{
    //创建新目录
    //创建Makefile
    //创建main.c

    if(access(directory_path,0)!=0)
    {
        cerr<<"directory not found:"<<directory_path<<std::endl;
        return;
    }

    std::string new_dir;
    new_dir=std::string(directory_path) +"/" + project_name+"/";

    if(0==access(new_dir.c_str(),0))
    {
        //project directory already exist
        cerr<<"directory already exist:"<<new_dir<<std::endl;
        return ;
    }
    if(0!=mkdir(new_dir.c_str()))
    {
        cerr<<"directory create error:"<<new_dir<<std::endl;
        return ;
    }

    std::ofstream fout;
    fout.open(new_dir+"Makefile");
    fout<<""
          "LMAKE_VERSION=0.01\n\n"
          "# 最前方为 \"#\" 的文字都是注释\n\n"
          "# 源文件列表，将自己需要编译下的c文件写在下面。已经添加了一个main.c。\n"
          "# 如果您的c文件实际名称不是main.c，则需要根据实际修改\n"
          "# 如果有多个c文件，则可以依次写在下面，多个文件之间以1个或多个空格分开\n"
          "# 如果一行写的太长，可以用 \"\\\" 字符换行\n"
          "SRC_C= main.c\n\n"

          "# 汇编文件原文件列表。 将需要编译的汇编文件下载下面=号右边。 多个文件以空格分隔\n"
          "SRC_A51= asm_file.a51\n\n"

          "#此处是生成的项目的hex文件名\n"
          "PROG=default_name\n";

    fout.close();


    fout.open(new_dir+"main.c");

    fout<<"//此处是示例代码\n\n void main()\n{\n}\n";
    fout.close();

    fout.open(new_dir+"asm_file.a51");

    fout<<";//此处是示例代码\n\n ";
    fout.close();


    cout<<"finish!\n";
}



std::vector<std::string> add_line_value(std::string v_str, std::ifstream &fin, int coding)
{
    std::vector<std::string> vv;
    if(v_str.empty())
    {
        return vv;
    }

    v_str = trim(v_str);
    vv = split(v_str, " ", 1);
    if(vv.empty())
    {
        return vv;
    }

    std::string &vv_last = vv[vv.size()-1];

    if(vv_last.empty())
    {
        return vv;
    }
    if(vv_last[vv_last.size()-1]=='\\')
    {
        //需要读取下一行，连接到vv中
        if(vv_last.size()>1)
        {
            //换行连接符和最后一个关键词连在一起，要去掉
            vv[vv.size()-1] =vv_last.substr(0, vv_last.size()-1);
        }
        else
        {
            vv.resize(vv.size()-1);
        }
        if(!fin.eof())
        {
            std::string mline;
            std::getline(fin, mline);
            std::vector<std::string> vv2 = add_line_value(mline, fin, coding);
            vv.insert(vv.end(), vv2.begin(), vv2.end());
        }
    }
    return vv;
}


bool get_line_coding_to_utf8(std::ifstream &fin, std::string &mline, int coding)
{
    std::wstring mline2;
    std::istream &ret= std::getline(fin, mline);
    //mline.assign(mline.begin(), mline.end());

    //cout<<"get line count:"<<mline.size()<<std::endl;
    //cout<<"mline0:"<<mline[0]<<std::endl;
    if(ret)
    {
        return true;
    }
    return false;
}

void read_makefile(char * directory_path, std::vector<std::string> &src_c, std::vector<std::string> &src_a51, std::string &proj_name, double &version)
{
    std::string make_file = path_add(std::string(directory_path), std::string("Makefile"));

    std::ifstream fin(make_file);

    std::string mline;
    int coding=0;//0--ansi. 1--utf-8 2--unicode(utf-16)

    //while(get_line_coding_to_utf8(fin, mline, coding))
    while(!fin.eof())
    {
        //cout<<"==============\n";
        //cout<<"before get line\n";
        std::getline(fin, mline);
        //if(fin.)
        if(mline.size()>0)
        {
            //cout<<"getline:mline:"<<mline[0]<<std::endl;
        }

        if(mline.size()==0)
        {
            //cout<<"skip empty line\n";
            continue;
        }
        if((mline=="#coding=utf-8")||(mline=="# coding=utf-8"))
        {
            coding=1;
        }


        if(mline[0]=='#')
        {
            //cout<<"skip comment line\n";
            continue;
        }
        else
        {
            //cout<<"mline[0]:"<<mline[0]<<std::endl;
        }

        //cout<<"mline2:"<<mline<<std::endl;

        mline = trim(mline);
        if(mline.empty())
        {
            cout<<"skip empty line\n";
            continue;
        }
        if(mline[0]=='#')
        {
            cout<<"skip comment line\n";
            continue;
        }


        //cout<<"mline_trimed:"<<mline<<std::endl;
        std::vector<std::string> vk = split(mline, "=");

        //cout<<"mline_splited:"<<vk.size()<<std::endl;

        if(vk.size()<2)
        {
            //没有等号，直接下一行
            continue;
        }

        vk[0] = trim(vk[0]);

        //cout<<"before add_line_value\n";
        std::vector<std::string> vv = add_line_value(vk[1], fin, coding);

        //cout<<"after add_line_value:"<<vv.size()<<"\n";
        if(vk[0]=="LMAKE_VERSION")
        {
            vk[1] = trim(vv[0]);
            std::stringstream mstrA;
            mstrA<<vk[1];
            mstrA>>version;
        }
        else if(vk[0]=="SRC_C")
        {
            src_c.insert(src_c.end(), vv.begin(), vv.end());
        }
        else if(vk[0]=="SRC_A51")
        {
            src_a51.insert(src_a51.end(), vv.begin(), vv.end());
        }
        else if(vk[0]=="PROG")
        {
            proj_name = vv[0];
        }
    }
}


extern std::string G_PROG_NAME;



std::string get_lmake_log_file(std::string directory_path)
{
    std::string file_name = directory_path+"lmake_make.tmp";
    std::ofstream fout(file_name);
    std::stringstream to_write;
    to_write<<"===================================\n";
    time_t aa = time(NULL);
    to_write<< "compile start:" <<asctime(localtime(&aa));
    std::string to_write_str = to_write.str();
    fout.write(to_write_str.c_str(), to_write_str.size() );
    fout.close();
    return file_name;
}

int make(char * directory_path)
{
    ///目录内执行make
    /// 读取c 和a51文件， 和程序名称。
    /// 进行编译，生成结果
    ///

    ///查找Makefile文件
    /// 读取内部变量：SRCS_C
    /// 读取内部变量：SRCS_A51

    std::vector<std::string> src_c;
    std::vector<std::string> src_a51;
    std::string proj_name;
    double version;

    ///切换路径到当前路径
    ///
    chdir(directory_path);
    directory_path="./";

    ///读取makefile内容
    read_makefile(directory_path, src_c, src_a51, proj_name, version);


    std::string log_file_name = get_lmake_log_file(directory_path);


    std::vector<std::string> src_mzo;

    int exit_err_code = 0;

    ///对每个c文件进行处理
    for(unsigned i=0;i<src_c.size();++i)
    {
#if 1
        std::string cmd_compi_one_c_file;
        std::string output_afile= src_c[i];
        output_afile = replace(replace(output_afile, ".c", ".mzo"), ".C", ".mzo");
        cmd_compi_one_c_file = "\"" + ( G_PROG_NAME) +"\""  +" -x c8051 " +"-c -d ";
        cmd_compi_one_c_file =cmd_compi_one_c_file + " -I "+ std::string(directory_path) ;
        cmd_compi_one_c_file =cmd_compi_one_c_file + " -I \""+ std::string(get_path(G_PROG_NAME)+"\\inc\\c8051") +"\" ";
        cmd_compi_one_c_file =cmd_compi_one_c_file + " -ISTDC8051";

        cmd_compi_one_c_file =cmd_compi_one_c_file + " -D mzc ";
        cmd_compi_one_c_file =cmd_compi_one_c_file + " -i " + path_add(directory_path, src_c[i].c_str());
        cmd_compi_one_c_file =cmd_compi_one_c_file + " -o " + path_add(directory_path, output_afile.c_str());
        cout<<cmd_compi_one_c_file<<"\n";
        //system(cmd_compi_one_c_file.c_str());
        exit_err_code += myexecute_ansi(cmd_compi_one_c_file, "", 1, log_file_name);
        src_mzo.push_back(output_afile);
#endif
    }

    if(exit_err_code<0)
    {
        //编译错误
        cerr<<"compile error when compile mzo. just exit\n";
        return exit_err_code;
    }



    {
        ///对.o文件，编译生成.a51
        ///
        std::string cmd_compi_one_c_file;

        std::string output_afile=  +"_mzo.a51";
        cmd_compi_one_c_file = "\"" + ( G_PROG_NAME) +"\""  +" -x c8051 " +" -d ";
        //cmd_compi_one_c_file = cmd_compi_one_c_file + " -I "+ std::string(directory_path) ;
        //cmd_compi_one_c_file = cmd_compi_one_c_file + " -I \""+ std::string(get_path(G_PROG_NAME)+"\\inc\\c8051") +"\" ";
        cmd_compi_one_c_file = cmd_compi_one_c_file + " -ISTDC8051";

        cmd_compi_one_c_file = cmd_compi_one_c_file + " -D mzc ";

        cmd_compi_one_c_file = cmd_compi_one_c_file + " -o " + path_add(directory_path, output_afile.c_str());

        for(unsigned i=0;i<src_mzo.size();++i)
        {
            cmd_compi_one_c_file =cmd_compi_one_c_file + " -i " + path_add(directory_path, src_mzo[i].c_str());
        }

        cout<<cmd_compi_one_c_file<<"\n";
        //system(cmd_compi_one_c_file.c_str());
        exit_err_code += myexecute_ansi(cmd_compi_one_c_file, "", 1, log_file_name);
        src_a51.push_back(output_afile);
    }


    if(exit_err_code<0)
    {
        //编译错误
        cerr<<"compile error when compile to a51. just exit\n";
        return exit_err_code;
    }



    {
        /// asm merge and to hex
        std::string cmd_compi_one_a;
        cmd_compi_one_a = "\"" +G_PROG_NAME +"\""  +" -x asm8051 " +" -d  -D mzc ";
        for(unsigned i=0;i<src_a51.size();++i)
        {
            cmd_compi_one_a = cmd_compi_one_a + " -i " + path_add(directory_path, src_a51[i].c_str())+" ";
        }
        cmd_compi_one_a = cmd_compi_one_a + " -o " + proj_name+".hex";
        cout<<cmd_compi_one_a<<"\n";
        //system(cmd_compi_one_a.c_str());
        myexecute_ansi(cmd_compi_one_a, "", 1, log_file_name);
    }


    if(exit_err_code<0)
    {
        //编译错误
        cerr<<"compile error when compile to hex. just exit\n";
        return exit_err_code;
    }


}


int make_clean(char * directory_path)
{

    std::vector<std::string> src_c;
    std::vector<std::string> src_a51;
    std::string proj_name;
    double version;

    chdir(directory_path);
    directory_path="./";
    read_makefile(directory_path, src_c, src_a51, proj_name, version);
    for(unsigned i=0;i<src_c.size();++i)
    {
        std::string output_afile;
        std::string src_c_org=src_c[i];
        output_afile = src_c[i];
        output_afile = replace(replace(output_afile, ".c", ".a51"), ".C", ".a51");
        if(output_afile==src_c_org)
        {
            cout<<"ignore:" << src_c[i]<<std::endl;
            //源文件不能删除
            continue;
        }
        output_afile = path_add(directory_path, output_afile);
        cout<<"rm -rf "<<output_afile<<"\n";
        remove(output_afile.c_str());

        std::vector<std::string> m_tmp_file_ext={".prc",".tmp", ".icode", ".func", ".tk", ".ic1", ".ic2", ".sym", ".dot1", ".dot2",".mzo"};
        for(unsigned j=0;j<m_tmp_file_ext.size();++j)
        {
            output_afile = file_without_extension( output_afile)+m_tmp_file_ext[j];
            cout<<"rm -rf "<<output_afile<<"\n";
            remove(output_afile.c_str());
        }

    }
    remove("_mzo.a51");
    cout.close_log_file();
    cerr.close_log_file();
    remove("lmake_err.tmp");
    remove("lmake_log.tmp");
    cout.set_log_file();
    cerr.set_log_file();

    std::string target_file=path_add( directory_path, proj_name+".hex");
    cout<<"rm -rf "<<target_file<<"\n";
    remove(target_file.c_str() );

    return 0;
}




