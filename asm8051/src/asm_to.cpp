#include <assert.h>
#include <sstream>
#include <iostream>
#include "asm_to.h"
#include "replace.h"
#include "comp_context.h"
#include "driver.h"
#include "string_eval.h"
#include "asm_funcs.h"
#include "hex_generator.h"
#include "mylog.h"
#include "parser.h"
#include "asmc51_predefined_symbol.h"
#include "bit_addr_parse.h"
#include "asm_extend_jmp.h"
using mylog::cdbg;
using mylog::cerr;
using mylog::cwarn;
namespace NS_AMS8051HEX{


asm_to::asm_to()
{
    m_is_debug = 0;
    m_inst = NULL;
    m_address = 0;
    cdbg.set_cout_output(0);

}

int asm_to::compile()
{
    return 0;
}

int asm_to::add_src(std::string code_src, std::string file_name)
{
    comp_context calc;
    Driver driver(calc);

    std::stringstream istr(code_src);

    //driver.trace_parsing = 1;
    //driver.trace_scanning = 1;
    bool result = driver.parse_stream(istr, file_name);

    m_top_icode = calc.m_top_icode;

    return 0;
}

std::string asm_to::generate_hex()
{
    m_address = 0;



    asmc51_predefined_symbol ms;


    m_other_symbol_val = ms.get_symbols();

    int ret = 0;
    do{
        m_is_second_pass = 0;
        ///第一次遍历，生成代码在m_hex_blocks中，
        /// 标签值在m_label_code_address中。
        visitor_ic(m_top_icode);

        //第二次遍历，所有label都必须有定义
        m_is_second_pass = 1;
        /// 第二次遍历，重新生成代码，使用上次的
        /// m_label_code_address中的值
        m_hex_blocks.clear();

        ret = visitor_ic(m_top_icode);
        if(ret)
        {
            cwarn<<"inst need ext. compile again\n";
        }
    }
    while(ret>0);



    return hex_data_to_hex_file(m_hex_blocks);
}

int asm_to::visitor_ic(icode *ic)
{
    int ret_val = 0;
    switch(ic->m_type)
    {
    case ICODE_TYPE_BLOCK:
        cdbg<<"ICODE_TYPE_BLOCK\n";
        for(int j=0;j<ic->sub_icode.size();++j)
        {
            ret_val+=visitor_ic(ic->sub_icode[j]);
        }
        break;
    case ICODE_TYPE_ONE_CMD:
        cdbg<<"ICODE_TYPE_ONE_CMD ";
    {
        if(ic->sub_icode.empty())break;

        std::string cmd_name = ic->sub_icode[0]->name;
        std::transform(cmd_name.begin(), cmd_name.end(), cmd_name.begin(), ::toupper);
        cdbg<<cmd_name<<". addr:"<<std::hex<<m_address <<"\n";

        int opr_cnt = ic->sub_icode.size()-1;
        int opr_type[3]={0};
        unsigned opr_val[3]={0};
        for(int i=1;i<ic->sub_icode.size();++i)
        {
            opr_type[i-1] =  calc_icode_type(ic->sub_icode[i]);
            opr_val[i-1] = calc_icode_val(ic->sub_icode[i]);
        }

        hex_block mhb;
        mhb.m_address = m_address;
        ///----------------------------------
        /// 此处进行命令的翻译
        ///
        int asm_to_status = get_asm_to_bin(cmd_name,opr_cnt, opr_type[0],opr_val[0],
        opr_type[1], opr_val[1],opr_type[2], opr_val[2], m_address, mhb.m_bin);

        ///----------------------------------
        ///
        if(asm_to_status<0)
        {
            cerr<<"convert error no match opr."<<cmd_name<<"\n";
            cerr<<"oprcnt="<< opr_cnt;
            cerr<<". opr type:"<<opr_type[0]<<". "<<opr_type[1]<<". "<<opr_type[2]<<"\n";
        }
        else if((asm_to_status==1)&&m_is_second_pass)
        {
            /// 如果是第二遍，则需要扩展跳转指令.第一遍时，可能是标签变量值未定义
            ///对于跳转指令跳转不到的问题，此处进行扩展。
            /// 扩展成功，返回0
            asm_extend_jmp m_ext;
            if(m_ext.extend_jmp_one_cmd(ic)==0)
            {
                //扩展成功。需要重新编译
                ret_val = 1;
            }
            else
            {
                cerr<<"jmp inst error.\n";
                cerr<<"oprcnt="<< opr_cnt;
                cerr<<"curr_addr:"<<m_address<<"\n";
                cerr<<". opr type:"<<opr_type[0]<<". "<<opr_type[1]<<". "<<opr_type[2]<<"\n";
                cerr<<". opr val:"<<opr_val[0]<<". "<<opr_val[1]<<". "<<opr_val[2]<<"\n";
            }

        }
        m_hex_blocks.push_back(mhb);
        m_address   += mhb.m_bin.size();
    }

        break;
    case ICODE_TYPE_ONE_OPERATION:
        cdbg<<"ICODE_TYPE_OPR\n";
        break;
    case ICODE_TYPE_DEFINE_LABEL:
        cdbg<<"ICODE_TYPE_DEFINE_LABEL\n";

        m_label_code_address[ic->sub_icode[0]->name] = m_address;
        break;
    case ICODE_TYPE_ONE_MACRO:
        cdbg<<"ICODE_TYPE_ONE_MACRO\n";
        process_macro(ic);
        break;
    default:
        cdbg<<"no type:"<<ic->m_type<<"\n";
        break;
    }
    return ret_val;
}

int asm_to::calc_icode_type(icode *ic)
{
    switch(ic->m_type)
    {
    case Parser::token_type::TK_AT_RI:
        return TOKENI_AT_RI;
    case Parser::token_type::TK_RN:
        return TOKENI_RN;
    case Parser::token_type::TK_ACC:
        return  TOKENI_ACC;
    case Parser::token_type::TK_C :
        return TOKENI_C;
    case Parser::token_type::TK_AB:
        return TOKENI_AB;
    case Parser::token_type::TK_AT_DPTR :
        return TOKENI_AT_DPTR;
    case Parser::token_type::TK_DPTR :
        return TOKENI_DPTR;
    case  Parser::token_type::TK_AT_A_PLUS_PC :
        return TOKENI_AT_A_PLUS_PC;
    case Parser::token_type::TK_AT_A_PLUS_DPTR :
        return TOKENI_AT_A_PLUS_DPTR;
    case ICODE_TOKEN_ICONST:
        return TOKENI_VAL;
        break;
    case ICODE_TOKEN_KEYWORD:
    case ICODE_TYPE_ONE_OPERATION:
    case ICODE_TYPE_ONE_MACRO:
    case Parser::token_type::TK_DOLLAR:
        return TOKENI_VAL;

    default:
        break;
    }

    if((ic->m_type==TOKENI_NBIT)||
            (ic->m_type==TOKENI_IMM)||
            (ic->m_type==TOKENI_DOTBIT)
            )
    {
        return ic->m_type;
    }


    cdbg<<"ic->m_type :"<< ic->m_type<<"."<< ic->name <<"\n";
    assert(0);
    return ic->m_type;
}

unsigned asm_to::calc_icode_val(icode *ic)
{
    cdbg<<"calc_icode_val:"<<std::dec<<ic->m_type<<"\n";

    if(ic->m_type==ICODE_TOKEN_KEYWORD)
    {
        if(m_label_code_address.find(ic->name)!=m_label_code_address.end())
        {
            cdbg<<"keyword find."<<ic->name<<". val:"<<m_label_code_address[ic->name]<<"\n";
            return m_label_code_address[ic->name];
        }
        if(m_other_symbol_val.find(ic->name)!=m_other_symbol_val.end())
        {
            return m_other_symbol_val[ic->name];
        }


        if(m_is_second_pass)
        {
            cerr<<"unresolved symbol:"<< ic->name<<"\n";
        }
        cdbg<<"no keyword find. value=0 for temp\n";
        cdbg<<ic->name<<"\n";
        // no match keyword
        return 0;
    }
    else if(ic->m_type==TOKENI_IMM)
    {
        return calc_icode_val(ic->sub_icode[0]);
    }
    else if(ic->m_type==TOKENI_NBIT)
    {
        return calc_icode_val(ic->sub_icode[0]);
    }
    else if(ic->m_type==TOKENI_DOTBIT)
    {
        //P1.7
        unsigned val1 = calc_icode_val(ic->sub_icode[0]);
        unsigned val2 = calc_icode_val(ic->sub_icode[1]);
        unsigned bit_address;
        bool is_ok = bit_addr_parse(val1, val2, bit_address);
        if(m_is_second_pass &&(!is_ok))
        {
            cerr<<"bit addr error: "<<ic->sub_icode[0]->name<<". "<< ic->sub_icode[1]->name<<"\n";
        }
        return bit_address;
    }
    else if(ic->m_type==Parser::token_type::TK_DOLLAR)
    {
        return m_address;
    }
    else if(ic->m_type==ICODE_TYPE_ONE_OPERATION)
    {
        //此处是算符的操作
        if(ic->name=="add")
        {
            assert(ic->sub_icode.size()==2);
            unsigned val1=calc_icode_val(ic->sub_icode[0]);
            unsigned val2=calc_icode_val(ic->sub_icode[1]);
            return val1+val2;
        }
        if(ic->name=="sub")
        {
            assert(ic->sub_icode.size()==2);
            unsigned val1=calc_icode_val(ic->sub_icode[0]);
            unsigned val2=calc_icode_val(ic->sub_icode[1]);
            return val1-val2;
        }
        if(ic->name=="multipy")
        {
            assert(ic->sub_icode.size()==2);
            unsigned val1=calc_icode_val(ic->sub_icode[0]);
            unsigned val2=calc_icode_val(ic->sub_icode[1]);
            return val1*val2;
        }
        if(ic->name=="div")
        {
            assert(ic->sub_icode.size()==2);
            unsigned val1=calc_icode_val(ic->sub_icode[0]);
            unsigned val2=calc_icode_val(ic->sub_icode[1]);
            return val1/val2;
        }
        if(ic->name=="MOD")
        {
            assert(ic->sub_icode.size()==2);
            unsigned val1=calc_icode_val(ic->sub_icode[0]);
            unsigned val2=calc_icode_val(ic->sub_icode[1]);
            return val1%val2;
        }
        if(ic->name=="&")
        {
            assert(ic->sub_icode.size()==2);
            unsigned val1=calc_icode_val(ic->sub_icode[0]);
            unsigned val2=calc_icode_val(ic->sub_icode[1]);
            return val1&val2;
        }
        if((ic->name=="SHL")||(ic->name=="<<"))
        {
            assert(ic->sub_icode.size()==2);
            unsigned val1=calc_icode_val(ic->sub_icode[0]);
            unsigned val2=calc_icode_val(ic->sub_icode[1]);
            return val1<<val2;
        }
        if((ic->name=="SHR")||(ic->name==">>"))
        {
            assert(ic->sub_icode.size()==2);
            unsigned val1=calc_icode_val(ic->sub_icode[0]);
            unsigned val2=calc_icode_val(ic->sub_icode[1]);
            return val1>>val2;
        }

        if(ic->name=="NOT")
        {
            assert(ic->sub_icode.size()==1);
            unsigned val1=calc_icode_val(ic->sub_icode[0]);
            return ~val1;
        }
        if(ic->name=="HIGH")
        {
            assert(ic->sub_icode.size()==1);
            unsigned val1=calc_icode_val(ic->sub_icode[0]);
            return 0xff&(val1>>8);
        }
        if(ic->name=="LOW")
        {
            assert(ic->sub_icode.size()==1);
            unsigned val1=calc_icode_val(ic->sub_icode[0]);
            return 0xff&(val1>>0);
        }


        cerr<<"ic->name"<< ic->name <<". "<<ic->sub_icode.size() <<"\n";
        assert(0);
    }

    return ic->num;
}

int asm_to::process_macro(icode *ic)
{
    if(ic->sub_icode.empty())return 0;

    std::string mac_name = ic->sub_icode[0]->name;

    if((mac_name=="org")||(mac_name=="ORG"))
    {
        unsigned addr = ic->sub_icode[1]->num;
        m_address = addr;
        cdbg<<"org addr="<<m_address<<"\n";
    }
    else if((mac_name=="equ")||(mac_name=="EQU")
            || (mac_name=="sfr")
            || (mac_name=="sbit")
            || (mac_name=="bit")
            || (mac_name=="BIT")
            || (mac_name=="DATA")
            || (mac_name=="data")
            || (mac_name=="XDATA")
            || (mac_name=="xdata")
            )
    {
        assert(ic->sub_icode.size()==3);
        std::string key = ic->sub_icode[1]->name;
        unsigned val = calc_icode_val(ic->sub_icode[2]);
        m_other_symbol_val[key] = val;
        cdbg<<"equ:"<<key<<"="<<val<<"\n";
    }
    else if((mac_name=="$NOMOD51")&&(!m_is_second_pass))
    {
        m_other_symbol_val.clear();
    }
    else if((mac_name=="db") || (mac_name=="DB"))
    {
        hex_block mhb;
        mhb.m_address = m_address;
        int db_size = ic->sub_icode.size()-1;
        mhb.m_bin.resize(db_size);
        for(int i=1;i<ic->sub_icode.size();++i)
        {
            mhb.m_bin[i-1] = (unsigned char)(unsigned)calc_icode_val(ic->sub_icode[i]);
        }
        m_hex_blocks.push_back(mhb);
        m_address   += mhb.m_bin.size();
    }
    else if((mac_name=="END")||
            (mac_name=="end"))
    {
        return 0;
    }
    else if((mac_name=="USING")||
            (mac_name=="using"))
    {
        //fixme 此处未实现
        cerr<<"USING macro not implement\n";
        return 0;
    }
    else
    {
        cerr<<"unknown macro:"<< mac_name<<"\n";
    }
    return 0;
}

}
