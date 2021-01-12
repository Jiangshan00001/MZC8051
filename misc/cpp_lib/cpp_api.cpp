#include "cpp_api.h"
#include "simplecpp.h"
#include "mylog.h"
#include "main_var.h"
#include "dir_file.h"


using mylog::cout;
using mylog::cerr;

cpp_api::cpp_api()
{
}


std::string cpp_api::c_do_cpp(std::istream &input_file, std::string input_file_name,
                              std::vector<std::string> &include_file,
                              std::vector<std::string> &defined_sym, std::vector<std::string> &include_path, int is_debug)
{
    std::string cpp_output;

    // Settings..
    simplecpp::DUI dui;

    ///==============================================
    /// init environment
    ///==============================================
    // defined sym
    for(unsigned i=0;i<defined_sym.size();++i)
    {
        if(is_debug)
        {
            cout<<"def_sym:"<<defined_sym[i]<<"\n";
        }
        dui.defines.push_back(defined_sym[i]);
    }

    //include path
    for(unsigned i=0;i<include_path.size();++i)
    {
        if(is_debug)
        {
            cout<<"inc_path:"<<include_path[i]<<"\n";
        }
        if (include_path[i]=="STDC8051")
        {
            std::string pathA = get_path(G_PROG_NAME);
            pathA= pathA + "\\inc\\c8051\\";
            dui.includePaths.push_back(pathA);
        }
        else
        {
            dui.includePaths.push_back(include_path[i]);
        }
    }
    for(unsigned i=0;i<include_file.size();++i)
    {
        if(is_debug)
        {
            cout<<"inc_file:"<<include_file[i]<<"\n";
        }
        dui.includes.push_back(include_file[i]);
    }
    ///==============================================


    std::string filename = input_file_name;

    // Perform preprocessing
    simplecpp::OutputList outputList;
    std::vector<std::string> files;
    std::istream &f = input_file;
    simplecpp::TokenList rawtokens(f,files,filename,&outputList);
    rawtokens.removeComments();
    std::map<std::string, simplecpp::TokenList*> included = simplecpp::load(rawtokens, files, dui, &outputList);
    for (std::pair<std::string, simplecpp::TokenList *> i : included)
    {
        i.second->removeComments();
    }
    simplecpp::TokenList outputTokens(files);
    simplecpp::preprocess(outputTokens, rawtokens, files, included, dui, &outputList);

    ///2020.8.3 添加constfold
    ///outputTokens.constFold();
    /// 此处常量折叠有问题： delay(1==3); 折叠后，变为 delay 0;

    // Output
    cpp_output = outputTokens.stringify();

    for (const simplecpp::Output &output : outputList) {
        cerr << output.location.file() << ':' << output.location.line << ": ";
        switch (output.type) {
        case simplecpp::Output::ERROR:
            cerr << "#error: ";
            break;
        case simplecpp::Output::WARNING:
            cerr << "#warning: ";
            break;
        case simplecpp::Output::MISSING_HEADER:
            cerr << "missing header: ";
            break;
        case simplecpp::Output::INCLUDE_NESTED_TOO_DEEPLY:
            cerr << "include nested too deeply: ";
            break;
        case simplecpp::Output::SYNTAX_ERROR:
            cerr << "syntax error: ";
            break;
        case simplecpp::Output::PORTABILITY_BACKSLASH:
            cerr << "portability: ";
            break;
        case simplecpp::Output::UNHANDLED_CHAR_ERROR:
            cerr << "unhandled char error: ";
            break;
        case simplecpp::Output::EXPLICIT_INCLUDE_NOT_FOUND:
            cerr << "explicit include not found: ";
            break;
        }
        cerr << output.msg << std::endl;
    }

    // cleanup included tokenlists
    simplecpp::cleanup(included);

    cout<<"cpp finish!\n";

    return cpp_output;
}

void cpp_api::c_do_cpp(std::string input_file, std::string out_file, std::vector<std::string> &include_file,
                       std::vector<std::string> &defined_sym, std::vector<std::string> &include_path, int is_debug)
{
    std::ifstream fin(input_file);
    std::string cpp_output = c_do_cpp(fin,input_file, include_file,  defined_sym, include_path, is_debug);

    std::ofstream fout(out_file);
    fout<<cpp_output;
    fout.close();
}

void cpp_api::c_do_cpp(std::istream &input_file,std::string input_file_name,  std::ostream &out_file, std::vector<std::string> &include_file,
                       std::vector<std::string> &defined_sym, std::vector<std::string> &include_path, int is_debug)
{
    std::string cpp_output = c_do_cpp(input_file,input_file_name,include_file,  defined_sym, include_path, is_debug);

    out_file<<cpp_output;
}


std::string cpp_api::c_do_cpp(std::string input_file, std::vector<std::string> &include_file, std::vector<std::string> &defined_sym, std::vector<std::string> &include_path, int is_debug)
{
    std::ifstream fin(input_file);
    std::string cpp_output = c_do_cpp(fin,input_file,include_file,  defined_sym, include_path, is_debug);

    return cpp_output;
}
