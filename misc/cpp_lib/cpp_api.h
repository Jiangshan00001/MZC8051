#ifndef CPP_API_H
#define CPP_API_H

#include <string>
#include <vector>
#include <fstream>


class cpp_api
{
public:
    cpp_api();

public:
    std::string  c_do_cpp(std::istream& input_file, std::string input_file_name,
                  std::vector<std::string> &include_file, std::vector<std::string> &defined_sym, \
             std::vector<std::string> &include_path, int is_debug);

public:
    void c_do_cpp(std::string input_file, std::string out_file,
                  std::vector<std::string> &include_file,std::vector<std::string> &defined_sym, \
             std::vector<std::string> &include_path, int is_debug);
    void c_do_cpp(std::istream& input_file, std::string input_file_name, std::ostream& out_file,
                  std::vector<std::string> &include_file,std::vector<std::string> &defined_sym, \
             std::vector<std::string> &include_path, int is_debug);
    std::string c_do_cpp(std::string input_file,
                         std::vector<std::string> &include_file,std::vector<std::string> &defined_sym, \
                    std::vector<std::string> &include_path, int is_debug);
};

#endif // CPP_API_H
