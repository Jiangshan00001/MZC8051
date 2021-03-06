#include <assert.h>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stack>
#include <algorithm>
#include <fstream>
#include <time.h>

#include <sstream>
#include "icode_to_c51.h"
//#include "token_defs.h"
#include "icode.h"
#include "c51_addr.h"
#include "c51_var_manage.h"
#include "mylog.h"
#include "get_j_data_byte.h"

using mylog::cerr;
using mylog::cout;

bool icode_to_c51::is_byte_shift_over_flow(c51_addr * from, int addr_shift, std::string &byte_str, std::string &byte_prepare_str)
{
    if((addr_shift==0) || (addr_shift*8 < from->m_bit_width))
    {
        return false;
    }
    if(from->m_bit_width==0)
    {
        assert(0);
    }

    if((!from->is_signed )|| (from->m_bit_width==1))
    {
        std::stringstream asm_str;

        //无符号，或者最高位不是1
        byte_str = "#0x0";
        return true;
    }

    ///有符号数
    if(from->m_type==DATA_TYPE_J_DATA)
    {
        std::stringstream asm_str;
        asm_str<<"#0x"<<std::hex<< (0xff &get_j_data_byte(from, addr_shift));
        byte_str = asm_str.str();
        return true;
    }

    std::stringstream asm_str;

    ///有符号数读取。如果读取超过长度，则根据符号位和最高位返回0 或者ff
    ///
    ///
    int last_byte = from->m_bit_width/8 -1;
    asm_str<<mov_byte_to_a(from, last_byte);
    asm_str<<"RLC A;\n";//最高位移动到C

    /// (A) ← (A) - (C) - (direct)
    /// A-A 如果C为0， 则结果为0， 如果C为1，则为FF
    asm_str<<"SUBB A, 0x"<<std::hex<<REG_ADDR_ACC<<";\n";

    byte_prepare_str = asm_str.str();
    std::stringstream strB;
    strB<<"0x"<< std::hex<<REG_ADDR_ACC;
    byte_str = strB.str();

    return true;
}


std::string icode_to_c51::mov_byte_to_a(c51_addr *from, int addr_shift, int dptr_just_inc)
{
    /// MOV	A,Rn
    /// MOV	A,direct
    /// MOV	A,@Ri
    /// MOV	A,#data
    /// MOVC	A,@A+DPTR
    /// MOVC	A,@A+PC
    /// MOVX	A,@Ri
    /// MOVX	A,@DPTR

    std::stringstream asm_str;

    std::string byte_str, byte_parapare_str;
    if(is_byte_shift_over_flow(from, addr_shift, byte_str, byte_parapare_str))
    {
        asm_str<<byte_parapare_str;
        asm_str<<"MOV A, "<<byte_str<<";over flow\n";
        return asm_str.str();
    }


    if(from->m_type==DATA_TYPE_BIT)
    {
        //bit->c
        // rlc
        //MOV	C,bit	Move direct bit to Carry
        //MOV	bit,C	Move Carry to direct bit
        //RLC	A	Rotate Accumulator Left through the Carry

        asm_str<<"CLR A;\n";
        asm_str<<"MOV C, 0x"<<std::hex<<from->m_addr<<ASM_END_STR;
        asm_str<<"RLC A;\n";
    }
    else if(from->m_type==DATA_TYPE_J_DATA)
    {
        //立即数
        asm_str<< "MOV A, #0x"<<std::hex<< ( ((0xff<<(addr_shift*8))& from->m_addr) >>(addr_shift*8)  )<<";\n";
    }
    else if(from->m_type==DATA_TYPE_J_DATA_F)
    {
        //立即数float
        unsigned byte1 = ((unsigned char*)&from->fnum)[addr_shift];

        //asm_str<< "MOV A, #0x"<<std::hex<< ( ((0xff<<(addr_shift*8))& ( *(unsigned int*)(&from->fnum))  ) >>(addr_shift*8)  )<<";\n";
        asm_str<<"MOV A, #0x"<<std::hex<<byte1<<ASM_END_STR;
    }
    else if(from->m_type==DATA_TYPE_DIRECT)
    {
        if(from->m_addr==REG_ADDR_ACC)
        {
            asm_str<<";A<-A\n";
        }
        else
        {
            asm_str<< "MOV A, 0x"<<std::hex<< from->m_addr + addr_shift<<";\n";
        }
    }
    else if((from->m_type==DATA_TYPE_RI)||(from->m_type==DATA_TYPE_RN))
    {
        asm_str<<"MOV A, R"<<from->m_addr + addr_shift<<";\n";
    }
    else if(from->m_type==DATA_TYPE_IDATA)
    {
        int mR = m_Rn.get_reg(0,1);
        asm_str<<"MOV R"<<mR <<",  0x"<<std::hex<<from->m_addr+addr_shift<<";\n";
        asm_str<<"MOV A, @R"<<mR <<";\n";
        m_Rn.free_reg(mR);
    }
    else if(from->m_type==DATA_TYPE_PDATA)
    {
        int mR = m_Rn.get_reg(0,1);
        asm_str<<"MOV R"<<mR <<", #0x"<<std::hex<< from->m_addr + addr_shift<<";\n";
        asm_str<< "MOVX A, @R"<< mR << ";\n";
        m_Rn.free_reg(mR);
    }
    else if(from->m_type==DATA_TYPE_XDATA)
    {

        if(dptr_just_inc)
        {
            asm_str<<"INC DPTR;\n";
        }
        else
        {
            asm_str<<"MOV DPTR, #0x"<<std::hex<< from->m_addr + addr_shift<<";\n";
        }

        asm_str<< "MOVX A, @DPTR;\n";
    }
    else if(from->m_type==DATA_TYPE_IDIRECT_RI)
    {
        //FIXME: 此处需要使用add函数，不能在此处手工生成add代码

        ///数据实际在direct类型存储器中，待使用时临时申请R并放入

        int mR = m_Rn.get_reg(0,1);
        asm_str<<"MOV R"<<mR<<", 0x"<<std::hex<<from->m_addr<<ASM_END_STR;

        if(addr_shift)
        {

            asm_str<<"MOV A, R"<<mR<<";\n";
            asm_str<<"ADD A"<<", #0x"<<std::hex<<addr_shift<<";\n";
            asm_str<<"MOV R"<<mR<<", A;\n";
        }

        asm_str<<"MOV A, @R"<<mR<<";\n";
        m_Rn.free_reg(mR);
    }
    else if(from->m_type==DATA_TYPE_PDATA_RI)
    {
        ///数据实际在direct类型存储器中，待使用时临时申请R并放入

        int mR = m_Rn.get_reg(0,1);
        asm_str<<"MOV R"<<mR<<", 0x"<<std::hex<<from->m_addr<<ASM_END_STR;

        if(addr_shift)
        {
            asm_str<<"MOV A, R"<<mR<<ASM_END_STR;
            asm_str<<"ADD A"<<", #0x"<<std::hex<<addr_shift<<ASM_END_STR;
            asm_str<<"MOV R"<<mR<<", A"<<ASM_END_STR;
        }

        asm_str<<"MOVX A, @R"<<mR<<ASM_END_STR;
        m_Rn.free_reg(mR);
    }
    else if(from->m_type==DATA_TYPE_CODE_AT_DPTR)
    {
        /// MOVC	A,@A+DPTR
        ///
        ///
        //FIXME: 此处需要使用add函数，不能在此处手工生成add代码
        ///数据实际在direct类型存储器中，待使用时临时放入
        asm_str<<"MOV 0x"<<std::hex<<REG_ADDR_DPL<<", 0x"<<std::hex<< from->m_addr<<ASM_END_STR;
        asm_str<<"MOV 0x"<<std::hex<<REG_ADDR_DPH<<", 0x"<<std::hex<< from->m_addr+1<<ASM_END_STR;


        if(addr_shift)
        {
            asm_str<<"MOV A, #0x"<<std::hex<<addr_shift<<ASM_END_STR;
            asm_str<<"ADD A, 0x"<<std::hex<<REG_ADDR_DPL<<ASM_END_STR;
            asm_str<<"MOV 0x"<<std::hex<<REG_ADDR_DPL<<", A"<<ASM_END_STR;
            asm_str<<"MOV A, #0x"<<std::hex<<(0xff& ((0xff00&addr_shift)>>8))<<ASM_END_STR;
            asm_str<<"ADDC A, 0x"<<std::hex<<REG_ADDR_DPH<<ASM_END_STR;
            asm_str<<"MOV 0x"<<std::hex<<REG_ADDR_DPH<<", A"<<ASM_END_STR;
        }

        asm_str<<"CLR A;\n";
        asm_str<<"MOVC A, @A+DPTR"<<";\n";
    }
    else if(from->m_type==DATA_TYPE_XDATA_AT_DPTR)
    {
        ///数据实际在direct类型存储器中，待使用时临时放入
        asm_str<<"MOV 0x"<<std::hex<<REG_ADDR_DPL<<", 0x"<<std::hex<< from->m_addr<<ASM_END_STR;
        asm_str<<"MOV 0x"<<std::hex<<REG_ADDR_DPH<<", 0x"<<std::hex<< from->m_addr+1<<ASM_END_STR;

        if(addr_shift)
        {
            asm_str<<"MOV A, #0x"<<std::hex<<addr_shift<<ASM_END_STR;
            asm_str<<"ADD A, 0x"<<std::hex<<REG_ADDR_DPL<<ASM_END_STR;
            asm_str<<"MOV 0x"<<std::hex<<REG_ADDR_DPL<<", A"<<ASM_END_STR;
            asm_str<<"MOV A, #0x"<<std::hex<<(0xff& ((0xff00&addr_shift)>>8))<<ASM_END_STR;
            asm_str<<"ADDC A, 0x"<<std::hex<<REG_ADDR_DPH<<ASM_END_STR;
            asm_str<<"MOV 0x"<<std::hex<<REG_ADDR_DPH<<", A"<<ASM_END_STR;
        }

        asm_str<<"MOVX A, @DPTR"<<";\n";
    }
    else if(from->m_type==DATA_TYPE_J_DATA_LABEL)
    {
        if(addr_shift==2)
        {
            asm_str<<"MOV A, #5;\n";
        }
        else if(addr_shift==0)
        {
            asm_str<<"MOV A, #("<<from->labelA <<" &0xff);\n";
        }
        else if(addr_shift==1)
        {
            asm_str<<"MOV A, #(0xff&(( 0xff00&"<<from->labelA <<") >>8));\n";
        }
        else
        {
            assert(0);
        }
    }
    else if(from->m_type==DATA_TYPE_CODE)
    {
        asm_str<<"MOV DPTR, #("<<from->labelA <<std::hex <<"+0x" <<addr_shift<<");\n";
        asm_str<<"CLR A;\n";
        asm_str<<"MOVC A, @A+DPTR;\n";
    }
    else if(from->m_type==DATA_TYPE_IN_GENRIC_PTR)
    {
        /// 此处应该调用函数，用于将A中数据，放入指针所指向的位置

        asm_str<<this->mov_byte_to_r1(from->ptr_target,0);

        if(addr_shift)
        {
            asm_str<<"MOV A, R1;\n";
            asm_str<<"ADD A, #0x"<<std::hex<<addr_shift<<ASM_END_STR;
            asm_str<<"MOV R1, A;\n";
        }
        asm_str<<this->mov_byte_to_r2(from->ptr_target,1);

        if(addr_shift)
        {
            asm_str<<"MOV A, R2;\n";
            asm_str<<"ADDC A, #0x"<<std::hex<<(0x00ff&(addr_shift>>8))<<ASM_END_STR;
            asm_str<<"MOV R2, A;\n";
        }

        asm_str<<this->mov_byte_to_r3(from->ptr_target,2);
        asm_str<<this->lcall("__sys_func_ptr_byte_to_a")   ;
    }
    else if(from->m_type==DATA_TYPE_RN)
    {
        asm_str<<"MOV A, R"<< from->m_addr + addr_shift<<";\n";
    }
    else
    {
        cerr<<"unsupported mov_byte_to_a: "<<from->m_type<<"\n";
        assert(0);
    }

    return asm_str.str();
}

std::string icode_to_c51::mov_byte_to_r0(c51_addr *from, int addr_shift, int dptr_just_inc)
{
    return mov_byte_to_ri(from, addr_shift,dptr_just_inc, 0);
}

std::string icode_to_c51::mov_byte_to_r1(c51_addr *from, int addr_shift, int dptr_just_inc)
{
    return mov_byte_to_ri(from, addr_shift,dptr_just_inc,1);
}

std::string icode_to_c51::mov_byte_to_r2(c51_addr *from, int addr_shift, int dptr_just_inc)
{
    return mov_byte_to_ri(from, addr_shift,dptr_just_inc,2);

}

std::string icode_to_c51::mov_byte_to_r3(c51_addr *from, int addr_shift, int dptr_just_inc)
{
    return mov_byte_to_ri(from, addr_shift,dptr_just_inc,3);

}

std::string icode_to_c51::mov_byte_to_r4(c51_addr *from, int addr_shift, int dptr_just_inc)
{
    return mov_byte_to_ri(from, addr_shift,dptr_just_inc,4);

}

std::string icode_to_c51::mov_byte_to_r5(c51_addr *from, int addr_shift, int dptr_just_inc)
{
    return mov_byte_to_ri(from, addr_shift,dptr_just_inc,5);
}

std::string icode_to_c51::mov_byte_to_r6(c51_addr *from, int addr_shift, int dptr_just_inc)
{
    return mov_byte_to_ri(from, addr_shift,dptr_just_inc,6);

}

std::string icode_to_c51::mov_byte_to_r7(c51_addr *from, int addr_shift, int dptr_just_inc)
{
    return mov_byte_to_ri(from, addr_shift,dptr_just_inc,7);
}

std::string icode_to_c51::mov_byte_ri_to(c51_addr *to, int addr_shift, int dptr_just_inc, int R)
{
    std::stringstream asm_str;


    if(to->m_type==DATA_TYPE_DIRECT)
    {
        asm_str<<"MOV 0x"<<std::hex<<to->m_addr+addr_shift<< ", R"<<R<<   ";\n";
        return asm_str.str();
    }


    asm_str<<"MOV A, R"<<R<< ";\n";
    asm_str<<this->mov_byte_a_to(to, addr_shift, dptr_just_inc);
    return asm_str.str();
}

std::string icode_to_c51::mov_byte_to_ri(c51_addr *from, int addr_shift,int dptr_just_inc, int R)
{
    std::stringstream asm_str;

    std::string byte_str, byte_parapare_str;
    if(is_byte_shift_over_flow(from, addr_shift, byte_str, byte_parapare_str))
    {
        asm_str<<byte_parapare_str;
        asm_str<<"MOV R"<<R<<", "<<byte_str<<";over flow\n";
        return asm_str.str();
    }

    if(from->m_type==DATA_TYPE_J_DATA)
    {
        asm_str<<"MOV R"<<R<< ", #0x"<<std::hex << ((0xff)& ( ((0x000000fful<<(addr_shift*8))& from->m_addr) >> (addr_shift*8) )) << ";\n";
    }
    else if(from->m_type==DATA_TYPE_DIRECT)
    {
        asm_str<<"MOV R"<<R<< ",0x"<<std::hex<<from->m_addr+addr_shift<< ";\n";
    }
    else
    {
        asm_str<<this->mov_byte_to_a(from, addr_shift, dptr_just_inc);
        asm_str<<"MOV R"<<R<< ", A;\n";
    }
    return asm_str.str();
}

std::string icode_to_c51::mov_byte_to_b(c51_addr *from, int addr_shift)
{
    std::stringstream asm_str;

    if(from->m_bit_width/8<=addr_shift)
    {
        asm_str<<"MOV 0x"<<std::hex<<REG_ADDR_B<<", #0;\n";
    }
    else if(from->m_type==DATA_TYPE_DIRECT)
    {
        asm_str<<"MOV 0x"<<std::hex<<REG_ADDR_B<<", 0x"<<std::hex<<from->m_addr+addr_shift<<";\n";

    }
    else
    {
        asm_str<<this->mov_byte_to_a(from, addr_shift);
        asm_str<<"MOV 0x"<<std::hex<<REG_ADDR_B<<", A;\n";
    }

    return asm_str.str();
}


c51_addr *icode_to_c51::new_c51_addr_jdata(int num)
{
    c51_addr * a51 = new c51_addr();
    a51->m_type=DATA_TYPE_J_DATA;
    a51->m_addr = num;
    a51->refresh_width_from_addr();
    return a51;
}

int icode_to_c51::del_c51_addr(c51_addr *a51)
{
    delete a51;

}

std::string icode_to_c51::mov_byte_a_to(c51_addr *to, int addr_shift, int dptr_just_inc)
{

    /// MOV	Rn,A
    /// MOV	direct,A
    /// MOV	@Ri,A
    /// MOVX	@Ri,A
    /// MOVX	@DPTR,A
    /// MOV	C,bit
    /// MOV	bit,C


    std::stringstream asm_str;

    std::string byte_str, byte_parapare_str;
    if(is_byte_shift_over_flow(to, addr_shift, byte_str, byte_parapare_str))
    {
        asm_str<<byte_parapare_str;
        asm_str<<"MOV "<<byte_str<<", A;over flow\n";
        return asm_str.str();
    }

    if((to->m_type==DATA_TYPE_RN)||(to->m_type==DATA_TYPE_RI))
    {
        asm_str<<"MOV R"<<to->m_addr+addr_shift<<", A;\n";
    }
    else if(to->m_type==DATA_TYPE_DIRECT)
    {
        if(to->m_addr+addr_shift!=REG_ADDR_ACC)
        {
        asm_str<<"MOV 0x"<<std::hex<<to->m_addr+addr_shift<<", A;\n";
        }
        else
        {
            asm_str<<";mov a<-a. just comment\n";
        }
    }
    else if(to->m_type==DATA_TYPE_IDATA)
    {
        c51_addr *raddr = new_c51_addr_jdata(to->m_addr);
        int mR = m_Rn.get_reg(0,1);
        asm_str<<this->mov_byte_to_ri(raddr,0,0,mR);
        asm_str<<"MOV @R"<<mR<<", A;\n";
        m_Rn.free_reg(mR);
        del_c51_addr(raddr);
    }
    else if(to->m_type==DATA_TYPE_PDATA)
    {
        c51_addr *raddr = new_c51_addr_jdata(to->m_addr);
        int mR = m_Rn.get_reg(0,1);
        asm_str<<this->mov_byte_to_ri(raddr,0,0,mR);
        asm_str<<"MOVX @R"<<mR<<", A;\n";
        m_Rn.free_reg(mR);
        del_c51_addr(raddr);
    }
    else if(to->m_type==DATA_TYPE_XDATA)
    {
        if(dptr_just_inc)
        {
            asm_str<<"INC DPTR;\n";
        }
        else
        {
            asm_str<<"MOV DPTR, #0x"<<std::hex<< to->m_addr + addr_shift<<";\n";
        }
        asm_str<<"MOVX @DPTR, A;\n";
    }
    else if(to->m_type==DATA_TYPE_BIT)
    {
        asm_str<<"RRC A;\n";
        asm_str<<"MOV 0" <<std::hex<< to->m_addr +addr_shift<<"H, C;\n";
    }
    else if(to->m_type==DATA_TYPE_IDIRECT_RI)
    {
        //FIXME: 此处需要使用add函数，不能在此处手工生成add代码

        int mR2 = m_Rn.get_reg(0,1);
        asm_str<<"MOV R"<<mR2<<", 0x"<<std::hex<<to->m_addr<<ASM_END_STR;
        if(addr_shift)
        {
            //申请一个临时变量，用于存放A
            int mR = m_Rn.get_reg();
            asm_str<<"MOV R"<<mR<<", A;\n";

            //地址+addr_shift
            asm_str<<"MOV A, R"<<mR2<<";\n";
            asm_str<<"ADD A"<<", #0x"<<std::hex<<addr_shift<<";\n";
            asm_str<<"MOV R"<<mR2<<", A;\n";

            asm_str<<"MOV A, R"<<mR<<ASM_END_STR;
            m_Rn.free_reg(mR);

        }
        asm_str<<"MOV @R"<<mR2<<", A;\n";
        m_Rn.free_reg(mR2);

    }
    else if(to->m_type==DATA_TYPE_PDATA_RI)
    {
        int mR2 = m_Rn.get_reg(0,1);
        asm_str<<"MOV R"<<mR2<<", 0x"<<std::hex<<to->m_addr<<ASM_END_STR;
        if(addr_shift)
        {
            int mR = m_Rn.get_reg();
            asm_str<<"MOV R"<<mR<<", A;\n";

            asm_str<<"MOV A, R"<<mR2<<ASM_END_STR;
            asm_str<<"ADD A"<<", #0x"<<std::hex<<addr_shift<<ASM_END_STR;
            asm_str<<"MOV R"<<mR2<<", A"<<ASM_END_STR;

            asm_str<<"MOV A, R"<<mR<<ASM_END_STR;
            m_Rn.free_reg(mR);
        }

        asm_str<<"MOVX @R"<<mR2<<", A"<<ASM_END_STR;
        m_Rn.free_reg(mR2);
    }
    else if(to->m_type==DATA_TYPE_XDATA_AT_DPTR)
    {
        ///数据实际在direct类型存储器中，待使用时临时放入
        asm_str<<"MOV 0x"<<std::hex<<REG_ADDR_DPL<<", 0x"<<std::hex<< to->m_addr<<ASM_END_STR;
        asm_str<<"MOV 0x"<<std::hex<<REG_ADDR_DPH<<", 0x"<<std::hex<< to->m_addr+1<<ASM_END_STR;

        if(addr_shift)
        {
            int mR = m_Rn.get_reg();
            asm_str<<"MOV R"<<mR<<", A;\n";
            asm_str<<"MOV A, #0x"<<std::hex<<addr_shift<<ASM_END_STR;
            asm_str<<"ADD A, 0x"<<std::hex<<REG_ADDR_DPL<<ASM_END_STR;
            asm_str<<"MOV 0x"<<std::hex<<REG_ADDR_DPL<<", A"<<ASM_END_STR;
            asm_str<<"MOV A, #0x"<<std::hex<<(0xff& ((0xff00&addr_shift)>>8))<<ASM_END_STR;
            asm_str<<"ADDC A, 0x"<<std::hex<<REG_ADDR_DPH<<ASM_END_STR;
            asm_str<<"MOV 0x"<<std::hex<<REG_ADDR_DPH<<", A"<<ASM_END_STR;
            asm_str<<"MOV A, R"<<mR<<ASM_END_STR;
            m_Rn.free_reg(mR);
        }
        asm_str<<"MOVX @DPTR, A"<<";\n";
    }
    else if(to->m_type==DATA_TYPE_IN_GENRIC_PTR)
    {
        /// 此处应该调用函数，用于将A中数据，放入指针所指向的位置

        asm_str<<"MOV R4, A;\n";

        asm_str<<this->mov_byte_to_r1(to->ptr_target,0);

        if(addr_shift)
        {
            asm_str<<"MOV A, R1;\n";
            asm_str<<"ADD A, #0x"<<std::hex<<addr_shift<<ASM_END_STR;
            asm_str<<"MOV R1, A;\n";
        }

        asm_str<<this->mov_byte_to_r2(to->ptr_target,1);

        if(addr_shift)
        {
            asm_str<<"MOV A, R2;\n";
            asm_str<<"ADDC A, #0x"<<std::hex<<((addr_shift>>8)&0x00ff)<<ASM_END_STR;
            asm_str<<"MOV R2, A;\n";
        }

        asm_str<<this->mov_byte_to_r3(to->ptr_target,2);
        asm_str<<this->lcall("__sys_func_byte_to_ptr")   ;
        //asm_str<<"MOV A, #0;\n";
    }
    else
    {
        cerr<<"ERROR: unsupported mov_byte_a_to:"<<to->m_type<<"\n";
        //assert(0);
    }

    return asm_str.str();
}

std::string icode_to_c51::mov_byte_b_to(c51_addr * to, int addr_shift)
{
    std::stringstream asm_str;

    if((to->m_type==DATA_TYPE_RN)||(to->m_type==DATA_TYPE_RI))
    {
        asm_str<<"MOV R"<<to->m_addr+addr_shift<<", 0x"<<std::hex<<REG_ADDR_B<<  ";\n";
    }
    else if(to->m_type==DATA_TYPE_DIRECT)
    {
        asm_str<<"MOV 0x"<<std::hex<<to->m_addr+addr_shift<<", 0x"<<std::hex<<REG_ADDR_B<<  ";\n";
    }
    else
    {
        asm_str<<"MOV A, 0x"<<std::hex<<REG_ADDR_B<< ";\n";
        asm_str<<this->mov_byte_a_to(to, addr_shift);
    }


    return asm_str.str();
}



std::string icode_to_c51::mov_byte_r0_to(c51_addr *to, int addr_shift, int dptr_just_inc)
{
    return mov_byte_ri_to(to, addr_shift, dptr_just_inc, 0);
}

std::string icode_to_c51::mov_byte_r1_to(c51_addr *to, int addr_shift, int dptr_just_inc)
{
    return mov_byte_ri_to(to, addr_shift, dptr_just_inc, 1);
}

std::string icode_to_c51::mov_byte_r2_to(c51_addr *to, int addr_shift, int dptr_just_inc)
{
    return mov_byte_ri_to(to, addr_shift, dptr_just_inc, 2);
}

std::string icode_to_c51::mov_byte_r3_to(c51_addr *to, int addr_shift, int dptr_just_inc)
{
    return mov_byte_ri_to(to, addr_shift, dptr_just_inc, 3);
}

std::string icode_to_c51::mov_byte_r4_to(c51_addr *to, int addr_shift, int dptr_just_inc)
{
    return mov_byte_ri_to(to, addr_shift, dptr_just_inc, 4);
}

std::string icode_to_c51::mov_byte_r5_to(c51_addr *to, int addr_shift, int dptr_just_inc)
{
    return mov_byte_ri_to(to, addr_shift, dptr_just_inc, 5);
}

std::string icode_to_c51::mov_byte_r6_to(c51_addr *to, int addr_shift, int dptr_just_inc)
{
    return mov_byte_ri_to(to, addr_shift, dptr_just_inc, 6);
}

std::string icode_to_c51::mov_byte_r7_to(c51_addr *to, int addr_shift, int dptr_just_inc)
{
    return mov_byte_ri_to(to, addr_shift, dptr_just_inc, 7);
}

std::string icode_to_c51::mov_byte_to_at_ri(c51_addr *from, int addr_shift, int dptr_just_inc, int R)
{
    std::stringstream asm_str;
    asm_str<<this->mov_byte_to_a(from, addr_shift);
    asm_str<< "MOV @R"<<R<<", A;\n";

    return asm_str.str();
}

std::string icode_to_c51::mov_byte_to_at_r0(c51_addr *from, int addr_shift, int dptr_just_inc)
{
    return mov_byte_to_at_ri(from, addr_shift, dptr_just_inc, 0);

}
std::string icode_to_c51::mov_byte_to_at_dptr(c51_addr *from, int addr_shift, int dptr_just_inc)
{
    std::stringstream asm_str;
    asm_str<<this->mov_byte_to_a(from, addr_shift);
    asm_str<< "MOV @DPTR"<<", A;\n";

    return asm_str.str();
}

std::string icode_to_c51::mov_byte_at_ri_to(c51_addr *to, int addr_shift, int dptr_just_inc, int R)
{
    std::stringstream asm_str;

    if(to->m_bit_width/8<=addr_shift)
    {
        asm_str<<";to_addr="<<to->m_addr<<". shift="<<addr_shift<<". just ignore\n";
    }

    else if(to->m_type==DATA_TYPE_DIRECT)
    {
        asm_str<< "MOV  0x"<<std::hex<< to->m_addr + addr_shift<<",@R"<<R<<";\n";
    }
    else
    {
        asm_str<<"MOV A, @R"<<R<<";\n";
        asm_str<<this->mov_byte_a_to(to, addr_shift, dptr_just_inc);
    }

    return asm_str.str();
}

std::string icode_to_c51::movc_byte_at_dptr_to(c51_addr *to, int addr_shift, int dptr_just_inc)
{
    ///MOV	DPTR,#data16
    /// MOVC	A,@A+DPTR
    /// MOVC	A,@A+PC
    /// MOVX	A,@Ri
    /// MOVX	A,@DPTR
    /// MOVX	@Ri,A
    /// MOVX	@DPTR,A

}

std::string icode_to_c51::movx_byte_at_dptr_to(c51_addr *to, int addr_shift, int dptr_just_inc)
{
    ///MOV	DPTR,#data16
    /// MOVC	A,@A+DPTR
    /// MOVC	A,@A+PC
    /// MOVX	A,@Ri
    /// MOVX	A,@DPTR
    /// MOVX	@Ri,A
    /// MOVX	@DPTR,A
    ///

    return "";

}

std::string icode_to_c51::mov_byte_to_at_r1(c51_addr *from, int addr_shift, int dptr_just_inc)
{
    return mov_byte_to_at_ri(from, addr_shift, dptr_just_inc, 1);
}

std::string icode_to_c51::mov_0_to(c51_addr *to)
{
    std::stringstream asm_str;

    int byte_cnt=0;
    byte_cnt=to->m_bit_width/8;
    if(byte_cnt*8<to->m_bit_width)
    {
        byte_cnt++;
    }

    for(int i=0;i<byte_cnt;++i)
    {
        asm_str<<"MOV A, #0;\n";
        asm_str<<this->mov_byte_a_to(to, i);
    }

    return asm_str.str();
}

std::string icode_to_c51::mov_1_to(c51_addr *to)
{
    std::stringstream asm_str;

    int byte_cnt=0;
    byte_cnt=to->m_bit_width/8;
    if(byte_cnt*8<to->m_bit_width)
    {
        byte_cnt++;
    }
    asm_str<<"MOV A, #1;\n";
    asm_str<<this->mov_byte_a_to(to);

    for(int i=1;i<byte_cnt;++i)
    {
        asm_str<<"MOV A, #0;\n";
        asm_str<<this->mov_byte_a_to(to, i);
    }

    return asm_str.str();
}

std::string icode_to_c51::mov_byte_0_to(c51_addr *to, int addr_shift)
{

    if(to->m_bit_width/8<=addr_shift)
    {
        //could not mov
        //just return
        return std::string(";mov overflow. just return\n");
    }


    c51_addr zero;
    zero.m_addr=0;
    zero.m_type=DATA_TYPE_J_DATA;
    zero.m_bit_width = 8;
    c51_addr to2=*to;
    to2.m_addr = to->m_addr+addr_shift;
    return this->mov(&zero, &to2);
}

std::string icode_to_c51::mov_byte_to_direct(c51_addr *from, int addr_shift, int direct)
{
    std::stringstream asm_str;

    if(from->m_type==DATA_TYPE_DIRECT)
    {
        if((from->m_bit_width/8)<=addr_shift)
        {
            asm_str<<"MOV 0x"<<std::hex<<direct <<", #0; mov shift over. just fill zero\n";
        }
        else
        {
            asm_str<< "MOV 0x"<<std::hex<<direct <<", 0x"<<std::hex<<from->m_addr+addr_shift <<";\n";
        }
    }
    else if(from->m_type==DATA_TYPE_J_DATA)
    {
        asm_str<< "MOV 0x"<<std::hex<<direct <<", #0x"<<std::hex<< (((0xff <<(addr_shift*8))& from->m_addr) >>(addr_shift*8)) <<";\n";
    }
    else if(from->m_type==DATA_TYPE_IDATA)
    {
        int mIndex = m_Rn.get_reg(0,1);
        c51_addr imm;
        imm.m_type = DATA_TYPE_J_DATA;
        imm.m_addr = from->m_addr;
        //imm.m_bit_width = 8;
        imm.refresh_width_from_addr();
        asm_str<< this->mov_byte_to_ri(&imm, 0, 0, mIndex);


        c51_addr dirA;
        dirA.m_type = DATA_TYPE_DIRECT;
        dirA.m_addr = direct;
        dirA.m_bit_width = 8;

        asm_str<< this->mov_byte_at_ri_to(&dirA, 0,0, mIndex);
        m_Rn.free_reg(mIndex);
    }
    else if(from->m_type==DATA_TYPE_J_DATA_LABEL)
    {
        if(addr_shift==2)
        {
            asm_str<<"MOV 0x"<<std::hex<<direct<<", #5;\n";
        }
        else if(addr_shift==0)
        {
            asm_str<<"MOV 0x"<<std::hex<<direct<<", #("<<from->labelA <<" &0xff);\n";
        }
        else if(addr_shift==1)
        {
            asm_str<<"MOV 0x"<<std::hex<<direct<<", #(0xff&(( 0xff00&"<<from->labelA <<") >>8));\n";
        }
        else
        {
            assert(0);
        }
    }
    else
    {
        assert(0);
    }
    return asm_str.str();
}


