#include "dir_file.h"

std::string file_without_extension(const std::string &file_name)
{

    std::string file_name_without_ext = file_name;
    unsigned pos = file_name_without_ext.rfind('.');
    if (pos != std::string::npos)
    {
        file_name_without_ext=file_name_without_ext.substr(0, pos);
    }
    return file_name_without_ext;
}


std::string path_add(const std::string &directory_path, const std::string &filen)
{
    std::string new_p = directory_path;

    if(new_p.size()==0)
    {
        return std::string("./")+ filen;
    }

    if((new_p[new_p.size()-1]=='\\')||(new_p[new_p.size()-1]=='/'))
    {
        return std::string(directory_path)+filen;
    }
    return std::string(directory_path)+"/"+filen;
}

std::string get_path(const std::string full_path_name)
{
	std::string file_name_without_ext = full_path_name;
    unsigned pos = file_name_without_ext.rfind('\\');
    if (pos != std::string::npos)
    {
        file_name_without_ext=file_name_without_ext.substr(0, pos);
    }
    else
    {
        pos = file_name_without_ext.rfind('/');
        if (pos != std::string::npos)
        {
            file_name_without_ext=file_name_without_ext.substr(0, pos);
        }
        else
        {
            return "./";
        }
    }
    return file_name_without_ext;
}
std::string get_file_name(const std::string full_path_name)
{
	std::string file_name_without_ext = full_path_name;
    unsigned pos = file_name_without_ext.rfind('\\');
    if (pos != std::string::npos)
    {
        file_name_without_ext=file_name_without_ext.substr(pos+1);
    }
    return file_name_without_ext;	
}


std::string add_slash_before_space(std::string strA, char sp)
{
    for(unsigned i=0;i<strA.size();++i)
    {
        if(strA[i]==sp)
        {
            //
            if(i==0)
            {
                strA.insert(strA.begin(), '\\');
            }
            else
            {
                strA.insert(strA.begin()+i, '\\');
            }
            i++;
        }
    }

    return strA;
}














