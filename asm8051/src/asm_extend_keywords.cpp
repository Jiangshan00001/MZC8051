#include <assert.h>
#include "asm_extend_keywords.h"
#include "asm_context.h"


int T_ASM_CONTEXT::extend_inst(int index)
{
    //无任何操作返回0. 扩展指令返回1

    //目标block
    T_HEX_TEXT_BLOCK & curr_block = this->m_text_block[index];


    //目标block当前内容
    this->m_current_block;

    if(this->m_current_block.m_tokens.size()==0)
    {
        //没法处理
        return 0;
    }

    if(this->m_current_block.m_tokens[0].val_str=="SJMP")
    {
        //SJMP	rel	Short Jump (relative addr)	2
        //AJMP	addr11	Absolute Jump	2
        //LJMP	addr16	Long Jump	3
        //JMP	rel	Short Jump (relative addr)	2


        //跳转
        assert(this->m_current_block.m_tokens.size()==2);

        //
        if(this->m_current_block.m_tokens[1].num &0xf800)
        {
            //地址超过11bit了，只能用ljmp
            this->m_current_block.m_tokens[0].val_str="LJMP";
        }
        else
        {
            this->m_current_block.m_tokens[0].val_str="AJMP";
        }
        this->m_current_block.m_tokens[1].m_resolved=0;
        this->m_text_block[index] = this->m_current_block;
        return 1;
    }
    else if((this->m_current_block.m_tokens[0].val_str=="JZ")||
            (this->m_current_block.m_tokens[0].val_str=="JNZ")||
            (this->m_current_block.m_tokens[0].val_str=="JC")||
            (this->m_current_block.m_tokens[0].val_str=="JNC")
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


        //std::string cmd = this->m_current_block.m_tokens[0].val_str;

        std::string tmplab1=get_tmp_label("jz");
        std::string tmplab2=get_tmp_label("jz");

        assert(this->m_current_block.m_tokens.size()==2);

        std::string labaaa = this->m_current_block.m_tokens[1].val_str;
        this->m_current_block.m_tokens[1].val_str=tmplab1;
        this->m_current_block.m_tokens[1].m_resolved=0;
        this->m_current_block.m_tokens[1].num=0;
        this->m_current_block.m_tokens[1].rel=0;


        this->m_text_block[index] = this->m_current_block;


        std::vector<T_HEX_TEXT_BLOCK> insert_list;

        T_HEX_TEXT_BLOCK sjmp;
        sjmp.m_tokens.resize(2);
        sjmp.m_tokens[0].type=TOKEN_CMD;
        sjmp.m_tokens[0].val_str="SJMP";
        sjmp.m_tokens[0].m_resolved = 1;

        sjmp.m_tokens[1].type=TOKEN_KEYWORD;
        sjmp.m_tokens[1].val_str=tmplab2;
        sjmp.m_tokens[1].m_resolved = 0;
        sjmp.m_address = this->m_current_address+2;
        insert_list.push_back(sjmp);

        T_HEX_TEXT_BLOCK lab1;
        lab1.m_tokens.resize(1);
        lab1.m_tokens[0].type=TOKEN_LABEL;
        lab1.m_tokens[0].val_str = tmplab1;
        lab1.m_tokens[0].m_resolved = 1;
        lab1.m_address = this->m_current_address+4;
        insert_list.push_back(lab1);

        T_HEX_TEXT_BLOCK ljmp;
        ljmp.m_tokens.resize(2);
        ljmp.m_tokens[0].type=TOKEN_CMD;
        ljmp.m_tokens[0].val_str="LJMP";
        ljmp.m_tokens[0].m_resolved = 1;

        ljmp.m_tokens[1].type=TOKEN_KEYWORD;
        ljmp.m_tokens[1].val_str=labaaa;
        ljmp.m_tokens[1].m_resolved = 0;
        ljmp.m_address = this->m_current_address+4;
        insert_list.push_back(ljmp);

        T_HEX_TEXT_BLOCK lab2;
        lab2.m_tokens.resize(1);
        lab2.m_tokens[0].type=TOKEN_LABEL;
        lab2.m_tokens[0].val_str = tmplab2;
        lab2.m_tokens[0].m_resolved = 1;
        lab2.m_address = this->m_current_address+7;

        insert_list.push_back(lab2);


        this->m_text_block.insert(this->m_text_block.begin()+index+1, insert_list.begin(), insert_list.end());

        return 5;
    }
    else if((this->m_current_block.m_tokens[0].val_str=="JB")||
            (this->m_current_block.m_tokens[0].val_str=="JNB")||
            (this->m_current_block.m_tokens[0].val_str=="JBC")
            )
    {
        ///TODO: JB 指令扩展
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



        //std::string cmd = this->m_current_block.m_tokens[0].val_str;

        std::string tmplab1=get_tmp_label("jb");
        std::string tmplab2=get_tmp_label("jb");

        assert(this->m_current_block.m_tokens.size()==3);

        std::string labaaa = this->m_current_block.m_tokens[2].val_str;
        this->m_current_block.m_tokens[2].val_str=tmplab1;
        this->m_current_block.m_tokens[2].m_resolved=0;
        this->m_current_block.m_tokens[2].num=0;
        this->m_current_block.m_tokens[2].rel=0;


        this->m_text_block[index] = this->m_current_block;


        std::vector<T_HEX_TEXT_BLOCK> insert_list;

        T_HEX_TEXT_BLOCK sjmp;
        sjmp.m_tokens.resize(2);
        sjmp.m_tokens[0].type=TOKEN_CMD;
        sjmp.m_tokens[0].val_str="SJMP";
        sjmp.m_tokens[0].m_resolved = 1;

        sjmp.m_tokens[1].type=TOKEN_KEYWORD;
        sjmp.m_tokens[1].val_str=tmplab2;
        sjmp.m_tokens[1].m_resolved = 0;
        sjmp.m_address = this->m_current_address+2+1;
        insert_list.push_back(sjmp);

        T_HEX_TEXT_BLOCK lab1;
        lab1.m_tokens.resize(1);
        lab1.m_tokens[0].type=TOKEN_LABEL;
        lab1.m_tokens[0].val_str = tmplab1;
        lab1.m_tokens[0].m_resolved = 1;
        lab1.m_address = this->m_current_address+4+1;
        insert_list.push_back(lab1);

        T_HEX_TEXT_BLOCK ljmp;
        ljmp.m_tokens.resize(2);
        ljmp.m_tokens[0].type=TOKEN_CMD;
        ljmp.m_tokens[0].val_str="LJMP";
        ljmp.m_tokens[0].m_resolved = 1;

        ljmp.m_tokens[1].type=TOKEN_KEYWORD;
        ljmp.m_tokens[1].val_str=labaaa;
        ljmp.m_tokens[1].m_resolved = 0;
        ljmp.m_address = this->m_current_address+4+1;
        insert_list.push_back(ljmp);

        T_HEX_TEXT_BLOCK lab2;
        lab2.m_tokens.resize(1);
        lab2.m_tokens[0].type=TOKEN_LABEL;
        lab2.m_tokens[0].val_str = tmplab2;
        lab2.m_tokens[0].m_resolved = 1;
        lab2.m_address = this->m_current_address+7+1;

        insert_list.push_back(lab2);


        this->m_text_block.insert(this->m_text_block.begin()+index+1, insert_list.begin(), insert_list.end());

        return 5;
    }



    curr_block.m_source;

    return 0;

}

