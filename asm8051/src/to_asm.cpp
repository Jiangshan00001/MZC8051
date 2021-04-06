#include <sstream>
#include "to_asm.h"

#include "dis_funcs.h"
#include "hex_generator.h"
#include "mylog.h"
using mylog::cdbg;


namespace NS_AMS8051HEX{

to_asm::to_asm()
{
    //cdbg.set_cout_output(1);
    load_dis_funcs(this->m_dis_funcs);
}

int to_asm::hex_to_code1(std::string &hex_format_str)
{
    std::vector<hex_block> ihex_block =
    hex_file_to_hex_data(hex_format_str);


    cdbg<<ihex_block.size()<<"\n";

    for(unsigned i=0;i<ihex_block.size();++i)
    {
        std::vector<T_HEX_TEXT_BLOCK> mm;
        m_blocks.push_back(mm);

        hex_block &curr_block = ihex_block[i];
        std::vector<T_HEX_TEXT_BLOCK> &text_block = m_blocks[i];

        cdbg<<"block["<<i<<"].size="<< curr_block.m_bin.size()<<"\n";

        unsigned curr_address = curr_block.m_address;

        unsigned curr_pos = 0;
        while(curr_pos<curr_block.m_bin.size())
        {
            T_HEX_TEXT_BLOCK mtb;
            std::stringstream iret;
            DIS_FUNC_PTR ptr_func = m_dis_funcs[0xff&curr_block.m_bin[curr_pos]];
            ptr_func(this, curr_block.m_bin, curr_pos,curr_address, iret );


            unsigned pos_offset = get_inst_byte_len(0xff&curr_block.m_bin[curr_pos]);

            mtb.m_address = curr_address;
            mtb.m_source = iret.str();
            mtb.m_hex_text = curr_block.m_bin.substr(curr_pos, pos_offset);
            text_block.push_back(mtb);

            curr_pos+= pos_offset;
            curr_address += pos_offset;

            cdbg<<"curr_pos:"<<curr_pos<<". next_inst:" <<std::hex<<(unsigned)(0xff&curr_block.m_bin[curr_pos])<< "\n";
        }
    }
    return 0;

}

std::string to_asm::hex_to_code2()
{
    std::stringstream istr;
    for(unsigned i=0;i<m_blocks.size();++i)
    {
        if(m_blocks[i].empty())continue;

        istr<<"ORG "<<std::hex<<"0"<< m_blocks[i][0].m_address<<"H;\n";
        for(unsigned j=0;j<m_blocks[i].size();++j)
        {
            ///汇编代码
            if(m_label_code_address.find(m_blocks[i][j].m_address)!=m_label_code_address.end())
            {
                istr<<m_label_code_address[m_blocks[i][j].m_address]<<":\n";
            }
            istr<<m_blocks[i][j].m_source<<"\t\t";
            /// hex数据
            istr<<std::hex<<m_blocks[i][j].m_address<<"H\t";
            for(unsigned k=0;k<m_blocks[i][j].m_hex_text.size();++k)
            {
                istr<<ByteToStr(m_blocks[i][j].m_hex_text[k])<<" ";
            }
            istr<<"\n";
        }
        unsigned block_end_addr = m_blocks[i][m_blocks[i].size()-1].m_address + m_blocks[i][m_blocks[i].size()-1].m_hex_text.size();
        if(m_label_code_address.find(block_end_addr)!=m_label_code_address.end())
        {
            istr<<m_label_code_address[block_end_addr]<<":\n";
        }

    }

    return istr.str();
}

std::string to_asm::add_hex_str(std::string hex_format_str)
{

    hex_to_code1(hex_format_str);
    return hex_to_code2();

}


std::string to_asm::type_to_str_TOKEN_BIT(unsigned value, unsigned curr_addr, int inst_byte_cnt)
{
    std::stringstream istr;
    istr<<"0"<<std::hex<<(0xff&value)<<"H";
    return istr.str();
}

std::string to_asm::type_to_str_TOKEN_REL(unsigned addr, unsigned curr_addr, int inst_byte_cnt)
{

    std::stringstream mout;

    if(addr&0x80)
    {//负数偏移
        addr = ~addr;
        addr++;
        addr&=0xff;
        addr = curr_addr - addr + inst_byte_cnt;
    }
    else
    {
        //正数
        addr = curr_addr + addr + inst_byte_cnt;
    }


    mout<<"C_"<<std::hex<<addr<<"H";

    std::string a;
    a=mout.str();
    m_label_code_address[addr] = a;
    return a;

}

std::string to_asm::type_to_str_TOKEN_ADDR11(unsigned value, unsigned curr_addr, int inst_byte_cnt)
{
    std::stringstream istr;
    unsigned addr = (value&0x7ff);


    istr<<"C_"<<std::hex<<addr<<"H";

    std::string a;
    a=istr.str();
    m_label_code_address[addr] = a;
    return a;

}

std::string to_asm::type_to_str_TOKEN_ADDR16(unsigned value, unsigned curr_addr, int inst_byte_cnt)
{
    std::stringstream istr;
    unsigned addr = (value&0xffff);


    istr<<"C_"<<std::hex<<addr<<"H";

    std::string a;
    a=istr.str();
    m_label_code_address[addr] = a;
    return a;
}

std::string to_asm::type_to_str_TOKEN_AB(unsigned value, unsigned curr_addr, int inst_byte_cnt)
{
    return "AB";
}

std::string to_asm::type_to_str_TOKEN_ACC(unsigned value, unsigned curr_addr, int inst_byte_cnt)
{
    return "A";
}


std::string to_asm::type_to_str_TOKEN_AT_A_PLUS_DPTR(unsigned value, unsigned curr_addr, int inst_byte_cnt)
{
    return "@A+DPTR";
}

std::string to_asm::type_to_str_TOKEN_AT_A_PLUS_PC(unsigned value, unsigned curr_addr, int inst_byte_cnt)
{
    return "@A+PC";
}

std::string to_asm::type_to_str_TOKEN_AT_DPTR(unsigned value, unsigned curr_addr, int inst_byte_cnt)
{
    return "@DPTR";
}

std::string to_asm::type_to_str_TOKEN_AT_RI(unsigned value, unsigned curr_addr, int inst_byte_cnt)
{
    std::stringstream istr;
    istr<<"R"<<value;
    return istr.str();
}

std::string to_asm::type_to_str_TOKEN_C(unsigned value, unsigned curr_addr, int inst_byte_cnt)
{
    return "C";
}


std::string to_asm::type_to_str_TOKEN_DIRECT(unsigned value, unsigned curr_addr, int inst_byte_cnt)
{
    std::stringstream istr;
    istr<<"0"<<std::hex<<value<<"H";
    return istr.str();
}

std::string to_asm::type_to_str_TOKEN_DPTR(unsigned value, unsigned curr_addr, int inst_byte_cnt)
{
    return "DPTR";
}



std::string to_asm::type_to_str_TOKEN_RN(unsigned value, unsigned curr_addr, int inst_byte_cnt)
{
    std::stringstream istr;
    istr<<"R"<<value;
    return istr.str();
}

std::string to_asm::type_to_str_TOKEN_IMM16(unsigned value, unsigned curr_addr, int inst_byte_cnt)
{
    std::stringstream istr;
    istr<<std::hex<<"#0"<<(value&0xffff)<<"H";
    return istr.str();
}

std::string to_asm::type_to_str_TOKEN_IMM8(unsigned value, unsigned curr_addr, int inst_byte_cnt)
{
    std::stringstream istr;
    istr<<std::hex<<"#0"<<(value&0xff)<<"H";
    return istr.str();
}

std::string to_asm::type_to_str_TOKEN_NBIT(unsigned value, unsigned curr_addr, int inst_byte_cnt)
{
    std::stringstream istr;
    istr<<"/"<<std::hex<<"0"<<value<<"H";
    return istr.str();
}

}//namespace
