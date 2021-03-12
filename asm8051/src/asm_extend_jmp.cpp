#include <time.h>
#include <sstream>
#include <algorithm>
#include "asm_extend_jmp.h"
#include "mylog.h"
#include "icode.h"
using mylog::cdbg;
using mylog::cerr;
using mylog::cwarn;


namespace NS_AMS8051HEX{

int asm_extend_jmp::m_ext_index=1;

asm_extend_jmp::asm_extend_jmp()
{
}


int asm_extend_jmp::extend_jmp_one_cmd(icode *ic)
{
    std::string cmd_name = ic->sub_icode[0]->name;
    std::transform(cmd_name.begin(), cmd_name.end(), cmd_name.begin(), ::toupper);
    ///此处是跳转指令跳转不到的问题

        if(cmd_name=="SJMP")
        {
            cwarn<<"sjmp not reach the length. ext to ajmp\n";
            ic->sub_icode[0]->name="AJMP";
            return 0;
        }
        else if(cmd_name=="AJMP")
        {
            cwarn<<"ajmp not reach the length. ext to ljmp\n";
            ic->sub_icode[0]->name="LJMP";
            return 0;
        }
        else if((cmd_name=="JZ")
                ||(cmd_name=="JNZ")
                ||(cmd_name=="JC")
                ||(cmd_name=="JNC")
                )
        {
            //JZ	rel	Jump if Accumulator is Zero	2
            //JNZ	rel	Jump if Accumulator is Not Zero	2

            /// JZ/JNZ LABAAA
            /// --->
            /// JZ/JNZ TMPLAB1
            /// SJMP TMPLAB2
            /// TMPLAB1:
            /// LJMP LABAAA
            /// TMPLAB2:
            ///
            ///


            cwarn<<cmd_name<< " not reach the length. ext to ljmp insts\n";


            icode * cmd_ic = ic->sub_icode[0];//当前指令ic
            icode * dst_label = ic->sub_icode[1];//最终目的地


            ic->m_type= ICODE_TYPE_BLOCK;
            ic->sub_icode.clear();

            std::string tmplab1=get_tmp_label("jz");
            std::string tmplab2=get_tmp_label("jz");


            icode *lab1_ref=new icode((int)ICODE_TOKEN_KEYWORD);
            lab1_ref->name = tmplab1;
            icode *lab2_ref =new icode((int)ICODE_TOKEN_KEYWORD);
            lab2_ref->name = tmplab2;

            //JZ/JNZ TMPLAB1
            ic->sub_icode.push_back(new icode((int)ICODE_TYPE_ONE_CMD));
            ic->sub_icode[0]->sub_icode.push_back(cmd_ic);
            ic->sub_icode[0]->sub_icode.push_back(lab1_ref);
            //SJMP TMPLAB2
            ic->sub_icode.push_back(new icode((int)ICODE_TYPE_ONE_CMD));
            ic->sub_icode[1]->sub_icode.push_back(new icode((int)ICODE_TOKEN_CMD));
            ic->sub_icode[1]->sub_icode[0]->name = "SJMP";
            ic->sub_icode[1]->sub_icode.push_back(lab2_ref);

            //TMPLAB1:
            ic->sub_icode.push_back(new icode((int)ICODE_TYPE_DEFINE_LABEL));
            ic->sub_icode[2]->sub_icode.push_back(new icode((int)ICODE_TOKEN_KEYWORD));
            ic->sub_icode[2]->sub_icode[0]->name = tmplab1;

            //LJMP LABAAA
            ic->sub_icode.push_back(new icode((int)ICODE_TYPE_ONE_CMD));
            ic->sub_icode[3]->sub_icode.push_back(new icode((int)ICODE_TOKEN_CMD));
            ic->sub_icode[3]->sub_icode[0]->name = "LJMP";
            ic->sub_icode[3]->sub_icode.push_back(dst_label);

            //TMPLAB2:
            ic->sub_icode.push_back(new icode((int)ICODE_TYPE_DEFINE_LABEL));
            ic->sub_icode[4]->sub_icode.push_back(new icode((int)ICODE_TOKEN_KEYWORD));
            ic->sub_icode[4]->sub_icode[0]->name = tmplab2;

            return 0;
        }
        else if((cmd_name=="JB")
                ||(cmd_name=="JNB")
                ||(cmd_name=="JBC")
                )
        {
            cwarn<<cmd_name<< " not reach the length. ext to ljmp insts\n";

            ///
            ///
            /// JB/JNB BIT REL_LAB
            /// --->
            /// JB/JNB BIT TMPLAB1
            /// SJMP TMPLAB2
            /// TMPLAB1:
            /// LJMP REL_LAB
            /// TMPLAB2:
            ///
            ///
            icode *cmd_ic= ic->sub_icode[0];
            icode *bit_ic= ic->sub_icode[1];
            icode *dst_ic= ic->sub_icode[2];

            ic->sub_icode.clear();
            ic->m_type= ICODE_TYPE_BLOCK;

            std::string tmplab1=get_tmp_label("JB");
            std::string tmplab2=get_tmp_label("JB");

            icode *lab1_ref=new icode(ICODE_TOKEN_KEYWORD);
            lab1_ref->name = tmplab1;
            icode *lab2_ref =new icode(ICODE_TOKEN_KEYWORD);
            lab2_ref->name = tmplab2;

            //JB/JNB BIT TMPLAB1
            ic->sub_icode.push_back(new icode(ICODE_TYPE_ONE_CMD));
            ic->sub_icode[0]->sub_icode.push_back(cmd_ic);
            ic->sub_icode[0]->sub_icode.push_back(bit_ic);
            ic->sub_icode[0]->sub_icode.push_back(lab1_ref);
            //SJMP TMPLAB2
            ic->sub_icode.push_back(new icode(ICODE_TYPE_ONE_CMD));
            ic->sub_icode[1]->sub_icode.push_back(new icode(ICODE_TOKEN_CMD));
            ic->sub_icode[1]->sub_icode[0]->name = "SJMP";
            ic->sub_icode[1]->sub_icode.push_back(lab2_ref);

            //TMPLAB1:
            ic->sub_icode.push_back(new icode(ICODE_TYPE_DEFINE_LABEL));
            ic->sub_icode[2]->sub_icode.push_back(new icode(ICODE_TOKEN_KEYWORD));
            ic->sub_icode[2]->sub_icode[0]->name = tmplab1;

            //LJMP LABAAA
            ic->sub_icode.push_back(new icode(ICODE_TYPE_ONE_CMD));
            ic->sub_icode[3]->sub_icode.push_back(new icode(ICODE_TOKEN_CMD));
            ic->sub_icode[3]->sub_icode[0]->name = "LJMP";
            ic->sub_icode[3]->sub_icode.push_back(dst_ic);

            //TMPLAB2:
            ic->sub_icode.push_back(new icode(ICODE_TYPE_DEFINE_LABEL));
            ic->sub_icode[4]->sub_icode.push_back(new icode(ICODE_TOKEN_KEYWORD));
            ic->sub_icode[4]->sub_icode[0]->name = tmplab2;

            return 0;
        }



        return -1;

}

std::string asm_extend_jmp::get_tmp_label(std::string prefix)
{
    std::stringstream asm_str;
    asm_str<<"__asm_context_"<< prefix<<"_"<< time(NULL)<<"_"<<  m_ext_index;

    m_ext_index++;
    return asm_str.str();
}


}
