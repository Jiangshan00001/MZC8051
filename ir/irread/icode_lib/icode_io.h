#ifndef ICODE_IO_H
#define ICODE_IO_H

#include <string>
#include <vector>

///将icode保存到文件
/// 将文件中的icode内容读出，生成icode
class icode_io
{
public:
    icode_io();

    std::string icode_to_str(class icode *ic);
    class icode* str_to_icode(std::string icode_str);



    int save_icode(class icode *ic, std::string file_name);
    class icode* read_icode(std::string file_name);

    int save_icode_vec(std::vector<class icode *>ic, std::string file_name);
    std::vector<class icode*> read_icode_vec(std::string file_name);


};

#endif // ICODE_IO_H
