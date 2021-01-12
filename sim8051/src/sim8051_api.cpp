#include "sim8051_api.h"

#include "command.hpp"
#include "shell.hpp"
#include "argv.h"
#include "number2str.h"

int sim8051_run(std::string hex_file)
{
    Shell shell;
    Command command(shell);

    shell.cpu.Reset();

    std::string load_file_name = hex_file;


    std::vector<std::string> params;
    params.push_back(load_file_name);
    shell.RunCommand("load", params);
    params.clear();


    //params.push_back("0");
    //params.push_back( NumberToStr(shell.cpu.alu.flash.get_written_max_addr()) );
    //shell.RunCommand("disassemble", params);

    params.clear();
    shell.RunCommand("run", params);

    return 0;
}


int sim8051_run_str(std::string hex_str)
{
    Shell shell;
    Command command(shell);
    std::vector<std::string> params;

    shell.cpu.Reset();

    params.push_back(hex_str);
    shell.RunCommand("loadstr", params);

    params.push_back("0");
    params.push_back( NumberToStr(shell.cpu.alu.flash.get_written_max_addr()) );
    shell.RunCommand("disassemble", params);

    params.clear();
    shell.RunCommand("run", params);

    return 0;
}
