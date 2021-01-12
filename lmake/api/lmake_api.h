#ifndef LMAKE_API_H
#define LMAKE_API_H
#include <vector>
#include <string>

void make_new_project(char * directory_path, char *project_name);

///传入参数为makefile所在路径
int make(char * directory_path);
///传入参数为makefile所在路径
int make_clean(char * directory_path);

void read_makefile(char * directory_path, std::vector<std::string> &src_c, std::vector<std::string> &src_a51, std::string &proj_name, double &version);
#endif // LMAKE_API_H
