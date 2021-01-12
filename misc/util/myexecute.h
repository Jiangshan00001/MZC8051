#ifndef MYEXECUTE_H
#define MYEXECUTE_H
#include <string>
int myexecute(std::string cmd_utf8, std::string param_utf8, int wait_for_finish=1);
int myexecute_ansi_old(std::string cmd_ansi, std::string param_ansi, int wait_for_finish=1);
int myexecute_ansi(std::string cmd_ansi, std::string param_ansi, int wait_for_finish, std::string output_file_name);

#endif // MYEXECUTE_H
