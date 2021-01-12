#include "dis8051.h"
#include<set>
#include <iostream>

#include "hex_generator.h"
#include "asm_table.h"
#include "split.h"
#include "trim.h"

dis8051::dis8051()
{
    load_inst();
    load_dis_keywords(m_inst_dis_func);
}


dis8051::~dis8051()
{

}

std::string dis8051::dis_one_inst(std::string mbin, hex_code_asm_table &inst_info, unsigned curr_addr)
{
//    if( (inst_info.param_cnt==-1)||(inst_info.param_cnt>0 && inst_info.m_param0.size()==0))
//    {
//        ///不需要特别解码，或者未添加解码参数
//        return dis_one_inst_default(mbin, inst_info);
//    }

    unsigned key = ((unsigned int)((unsigned char)mbin[0])&0xff);
    return (*m_inst_dis_func[key])(this, mbin, curr_addr);
}

std::string dis8051::generate_str()
{

    std::stringstream ret_out;

    for(unsigned i=0;i<m_text_block.size();++i)
    {
        T_HEX_TEXT_BLOCK &blk = m_text_block[i];

        if((blk.m_hex_text.size()>0)&&( m_label_code_address.find(blk.m_address)!=m_label_code_address.end()  ))
        {
            ret_out<< m_label_code_address[blk.m_address]<<": "<<std::endl;
        }

        ret_out<<"\t"<<m_text_block[i].m_source<<"\t";

        if(blk.m_hex_text.size()>0)
        {
            ret_out<<std::hex<<blk.m_address <<"H:";
            for(unsigned k=0;k<blk.m_hex_text.size();++k)
            {
                ret_out<<" "<<ByteToStr(blk.m_hex_text[k]);
            }
        }
        ret_out<<"\n";
    }

    return ret_out.str();
}


std::string dis8051::add_hex_str(std::string hex_format_str)
{
    std::vector<hex_block> hex_blocks = hex_file_to_hex_data(hex_format_str);
    for(unsigned i=0;i<hex_blocks.size();++i)
    {
        unsigned curr_addr = hex_blocks[i].m_address;
        T_HEX_TEXT_BLOCK blk1;

        std::stringstream str1;
        str1<<"ORG " <<std::hex<<hex_blocks[i].m_address<<"H;"<<"size="<<std::hex<<hex_blocks[i].m_bin.size()<<"H";
        blk1.m_source=str1.str();
        blk1.m_address = curr_addr;
        blk1.m_hex_text="";
        this->m_text_block.push_back(blk1);


        //hex_blocks[i].m_address;
        for(unsigned j=0;j<hex_blocks[i].m_bin.size();)
        {   //每个byte

            unsigned char cbyte = hex_blocks[i].m_bin[j];
            hex_code_asm_table &inst_info =m_inst_dis[cbyte];
            unsigned int inst_byte_num = inst_info.m_byte_num;

            std::string mbin = hex_blocks[i].m_bin.substr(j, inst_byte_num);

            T_HEX_TEXT_BLOCK blk2;
            blk2.m_hex_text = mbin;
            blk2.m_address = curr_addr;
            blk2.m_source = dis_one_inst(mbin, inst_info, curr_addr);
            this->m_text_block.push_back(blk2);

            curr_addr += inst_byte_num;
            j+=inst_byte_num;
        }
    }




    return generate_str();

}

int dis8051::clear()
{
    m_text_block.clear();
    m_label_code_address.clear();
    return 0;
}

int dis8051::load_inst()
{
    for(int i=0;i<g_hex_table_size;++i)
    {
        m_inst_dis[g_hex_table[i].m_hex_code] = g_hex_table[i];
    }
    return 0;
}

std::string dis8051::CODE_ADDR_DIS(unsigned addr, unsigned curr_addr, unsigned inst_byte_cnt)
{
    std::stringstream mout;
    std::string a;
    mout<<"CODE_"<<std::hex<<addr<<"H";
    a=mout.str();

    m_label_code_address[addr] = a;
    return a;
}

std::string dis8051::ABS_CODE_ADDR_DIS(unsigned addr, unsigned curr_addr, unsigned inst_byte_cnt)
{
    std::stringstream mout;
    std::string a;

    mout<<"CODE_"<<std::hex<<addr<<"H";

    a=mout.str();
    m_label_code_address[addr] = a;
    return a;

}

std::string dis8051::REL_CODE_ADDR_DIS(unsigned addr, unsigned curr_addr, unsigned inst_byte_cnt)
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


    mout<<"CODE_"<<std::hex<<addr<<"H";

    std::string a;
    a=mout.str();
    m_label_code_address[addr] = a;
    return a;
}

std::string dis8051::DATA_ADDR_DIS(unsigned addr, unsigned curr_addr, unsigned inst_byte_cnt)
{
    std::stringstream mout;
    mout<<""<<std::hex<<"0"<<addr<<"H";
    return mout.str();
}

std::string dis8051::BIT_ADDR_DIS(unsigned addr, unsigned curr_addr, unsigned inst_byte_cnt)
{
    std::stringstream mout;
    mout<<""<<std::hex<<"0"<<addr<<"H";
    return mout.str();
}

std::string dis8051::DATA_VALUE_DIS(unsigned addr, unsigned curr_addr, unsigned inst_byte_cnt)
{
    std::stringstream mout;
    mout<<"#"<<std::hex<<"0"<<addr<<"H";
    return mout.str();
}

std::string dis8051::MBIT_ADDR_DIS(unsigned addr, unsigned curr_addr, unsigned inst_byte_cnt)
{
    std::stringstream mout;
    mout<<"/"<<std::hex<<"0"<<addr<<"H";
    return mout.str();
}


















