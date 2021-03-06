#ifndef SIM8051_API_H
#define SIM8051_API_H

#include <string>

int sim8051_run(std::string hex_file, bool is_debug);
int sim8051_run_str(std::string hex_str);

class sim8051{
public:
    sim8051();
    ~sim8051();

    void reset_all();

    void load_str(std::string hex_str);
    void load_file(std::string file_name);
    void step(int cnt);
    bool read_port_bit(int port_index, int bit_index);
    unsigned char read_byte(int address);


    void *m_handle;


};

#endif // SIM8051_API_H
