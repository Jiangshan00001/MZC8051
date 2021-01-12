#ifndef DIR_FILE_H
#define DIR_FILE_H

#include <string>

std::string file_without_extension(const std::string &file_name);
std::string path_add(const std::string &directory_path, const std::string &filen);
std::string get_path(const std::string full_path_name);
std::string get_file_name(const std::string full_path_name);

std::string add_slash_before_space(std::string strA, char sp=' ');

#endif // DIR_FILE_H
