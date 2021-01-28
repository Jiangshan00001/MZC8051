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

    params.clear();
    params.push_back("0");
    params.push_back( NumberToStr(shell.cpu.alu.flash.get_written_max_addr()) );
    shell.RunCommand("disassemble", params);

    params.clear();
    shell.RunCommand("run", params);

    return 0;
}

class SCC
{
public:
    Shell shell;
    Command *command;
public:
    SCC()
    {
        command = new Command(shell);
    }
    ~SCC()
    {
        delete command;
    }


};


sim8051::sim8051()
{
    m_handle = NULL;
    m_handle = (void*)new SCC();

}

sim8051::~sim8051()
{
    delete ((SCC*)(m_handle));
}

void sim8051::reset_all()
{
    if(m_handle)
    {
        delete ((SCC*)(m_handle));
    }
    m_handle = (void*)new SCC();



}

void sim8051::load_str(std::string hex_str)
{
    SCC * scc = (SCC* )m_handle;
    std::vector<std::string> params;

    scc->shell.cpu.Reset();

    params.push_back(hex_str);
    scc->shell.RunCommand("loadstr", params);

}

void sim8051::load_file(std::string file_name)
{
    SCC * scc = (SCC *  )(m_handle);
    std::vector<std::string> params;

    scc->shell.cpu.Reset();

    params.push_back(file_name);
    scc->shell.RunCommand("load", params);

}

void sim8051::step(int cnt)
{
    SCC * scc = (SCC*  )(m_handle);
    std::vector<std::string> params;

    std::stringstream ss;
    ss<<cnt;
    params.push_back(ss.str());
    scc->shell.RunCommand("step instructions", params);
}

bool sim8051::read_port_bit(int port_index, int bit_index)
{
    SCC * scc = (SCC*  )(m_handle);
    if(port_index==0)
    {
    //return scc->shell.cpu.port0.p0.ReadBit(bit_index);
    }
    return true;
}

unsigned char sim8051::read_byte(int address)
{
    SCC * scc = (SCC*  )(m_handle);
    return scc->shell.cpu.alu.Read(address);

}
