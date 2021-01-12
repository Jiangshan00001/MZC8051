#ifndef ASM8051_API_H
#define ASM8051_API_H

#include <string>

void translate_asm_to_hex(std::vector<std::string> &input_file, std::string parse_str, std::string output_file, bool is_debug);


int asm_compile_file(std::string asm_file, std::string hex_file, int is_debug);
int dis_compile_file(std::string in_file, std::string out_file, int is_debug);
std::string asm_compile_str(std::string asm_str,int is_out_to_cout, int is_debug);
std::string dis_compile_str(std::string hex_str,int is_out_to_cout, int is_debug);


#endif // ASM8051_API_H
