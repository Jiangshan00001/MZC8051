#include "asm_to.h"
#include "asm_funcs.h"
#include "assert.h"
#include "mylog.h"
using mylog::cerr;
namespace NS_AMS8051HEX{

//this enum may conflit with dis_funcs.h
// so please do not include dis_funcs.h
typedef enum E_TYPE_ASM_TOKEN_OPR{
TOKEN_AB,
TOKEN_ACC,
TOKEN_ADDR11,
TOKEN_ADDR16,
TOKEN_AT_A_PLUS_DPTR,
TOKEN_AT_A_PLUS_PC,
TOKEN_AT_DPTR,
TOKEN_AT_RI,
TOKEN_BIT,
TOKEN_C,
TOKEN_DIRECT,
TOKEN_DPTR,
TOKEN_IMM16,
TOKEN_IMM8,
TOKEN_NBIT,
TOKEN_REL,
TOKEN_RN,
} E_TYPE_ASM_TOKEN_OPR;

            /// 8bit signed data. -128 -> +127
            ///curr_addr=curr_addr+this_inst_len.
            /// curr_addr is the end of the inst addr
            int abs_to_rel(unsigned curr_addr, unsigned &abs_addr)
    {
        unsigned rel1 = 0;
        int is_jmp_err = 0;
        if(abs_addr>curr_addr)
        {
            rel1 = abs_addr - curr_addr;

            if(rel1>127)
            {
                is_jmp_err = 1;
                /**
                cerr<<"relative address jmp not reach error.\n";
                cerr<<"curr_addr+inst="<<std::hex<<curr_addr<<"H\n";
                cerr<<"abs_addr="<<std::hex<<abs_addr<<"H\n";
                cerr<<"jmp length="<<rel1<<"H\n";
                **/
            }
            abs_addr = rel1;
        }
        else if(abs_addr==curr_addr)
        {
            abs_addr = 0;
        }
        else
        {
            ///此处是<0的负数
            int kk = curr_addr-abs_addr;

            if(kk>128)
            {
                is_jmp_err = 1;
                /**
                cerr<<"relative address jmp not reach error.\n";
                cerr<<"curr_addr+inst="<<std::hex<<curr_addr<<"H\n";
                cerr<<"abs_addr="<<std::hex<<abs_addr<<"H\n";
                cerr<<"jmp length="<<kk<<"H\n";**/
            }

            abs_addr = (unsigned)((-kk)&0xff);

        }
        return is_jmp_err;
    }


            int ACALL_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//ACALL addr11 Absolute Subroutine Call 2 24 PROGRAM BRANCHING (($1&0x700)>>3)+0x11 ($1&0xff)  
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_VAL))
)
{
int is_jmp_err = 0;
if(((curr_addr+2)&0x0000f800)!=(opr_val1 &0x0000f800))
{is_jmp_err = 1;}
opr_val1 &=0x7ff;
ibin.resize(2);
ibin[0] = ((opr_val1&0x700)>>3)+0x11;
ibin[1] = (opr_val1&0xff);
return is_jmp_err;
}
return -1;

}
int ADD_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//ADD "A,Rn" Add register to Accumulator 1 12 ARITHMETIC OPERATIONS 0x28+$2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_RN))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(1);
ibin[0] = 0x28+opr_val2;
return is_jmp_err;
}
//ADD "A,direct" Add direct byte to Accumulator 2 12 ARITHMETIC OPERATIONS 0x25 $2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(2);
ibin[0] = 0x25;
ibin[1] = opr_val2 ;
return is_jmp_err;
}
//ADD "A,@Ri" Add indirect RAM to Accumulator 1 12 ARITHMETIC OPERATIONS 0x26+$2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_AT_RI))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(1);
ibin[0] = 0x26+opr_val2;
return is_jmp_err;
}
//ADD "A,#data" Add immediate data to Accumulator 2 12 ARITHMETIC OPERATIONS 0x24 $2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_IMM))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(2);
ibin[0] = 0x24;
ibin[1] = opr_val2 ;
return is_jmp_err;
}
return -1;

}
int ADDC_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//ADDC "A,Rn" Add register to Accumulator with Carry 1 12 ARITHMETIC OPERATIONS 0x38+$2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_RN))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(1);
ibin[0] = 0x38+opr_val2;
return is_jmp_err;
}
//ADDC "A,direct" Add direct byte to Accumulator with Carry 2 12 ARITHMETIC OPERATIONS 0x35 $2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(2);
ibin[0] = 0x35;
ibin[1] = opr_val2 ;
return is_jmp_err;
}
//ADDC "A,@Ri" Add indirect RAM to Accumulator with Carry 1 12 ARITHMETIC OPERATIONS 0x36+$2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_AT_RI))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(1);
ibin[0] = 0x36+opr_val2;
return is_jmp_err;
}
//ADDC "A,#data" Add immediate data to Acc with Carry 2 12 ARITHMETIC OPERATIONS 0x34 $2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_IMM))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(2);
ibin[0] = 0x34;
ibin[1] = opr_val2 ;
return is_jmp_err;
}
return -1;

}
int AJMP_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//AJMP addr11 Absolute Jump 2 24 PROGRAM BRANCHING (($1&0x700)>>3)+1 $1&0xff  
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_VAL))
)
{
int is_jmp_err = 0;
if(((curr_addr+2)&0x0000f800)!=(opr_val1 &0x0000f800))
{is_jmp_err = 1;}
opr_val1 &=0x7ff;
ibin.resize(2);
ibin[0] = ((opr_val1&0x700)>>3)+1;
ibin[1] = opr_val1&0xff;
return is_jmp_err;
}
return -1;

}
int ANL_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//ANL "C,bit" AND direct bit to CARRY 2 24 BOOLEAN VARIABLE MANIPULATION 0x82 $2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_C))
&&((opr_type2==TOKENI_DOTBIT)||(opr_type2==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(2);
ibin[0] = 0x82;
ibin[1] = opr_val2 ;
return is_jmp_err;
}
//ANL "C,/bit" AND complement of direct bit to Carry 2 24 BOOLEAN VARIABLE MANIPULATION 0xB0 $2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_C))
&&((opr_type2==TOKENI_NBIT))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(2);
ibin[0] = 0xB0;
ibin[1] = opr_val2 ;
return is_jmp_err;
}
//ANL "A,Rn" AND Register to Accumulator 1 12 LOGICAL OPERATIONS 0x58+$2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_RN))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(1);
ibin[0] = 0x58+opr_val2;
return is_jmp_err;
}
//ANL "A,direct" AND direct byte to Accumulator 2 12 LOGICAL OPERATIONS 0x55 $2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(2);
ibin[0] = 0x55;
ibin[1] = opr_val2 ;
return is_jmp_err;
}
//ANL "A,@Ri" AND indirect RAM to Accumulator 1 12 LOGICAL OPERATIONS 0x56+$2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_AT_RI))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(1);
ibin[0] = 0x56+opr_val2;
return is_jmp_err;
}
//ANL "A,#data" AND immediate data to Accumulator 2 12 LOGICAL OPERATIONS 0x54 $2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_IMM))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(2);
ibin[0] = 0x54;
ibin[1] = opr_val2 ;
return is_jmp_err;
}
//ANL "direct,A" AND Accumulator to direct byte 2 12 LOGICAL OPERATIONS 0x52 $1   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_VAL))
&&((opr_type2==TOKENI_ACC))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
opr_val2 &=0x00;
ibin.resize(2);
ibin[0] = 0x52;
ibin[1] = opr_val1 ;
return is_jmp_err;
}
//ANL "direct,#data" AND immediate data to direct byte 3 24 LOGICAL OPERATIONS 0x53 $1  $2 
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_VAL))
&&((opr_type2==TOKENI_IMM))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
opr_val2 &=0xff;
ibin.resize(3);
ibin[0] = 0x53;
ibin[1] = opr_val1 ;
ibin[2] = opr_val2;
return is_jmp_err;
}
return -1;

}
int CALL_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//CALL addr11 Absolute Subroutine Call 2 24 PROGRAM BRANCHING (($1&0x700)>>3)+0x11 ($1&0xff)  
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_VAL))
)
{
int is_jmp_err = 0;
if(((curr_addr+2)&0x0000f800)!=(opr_val1 &0x0000f800))
{is_jmp_err = 1;}
opr_val1 &=0x7ff;
ibin.resize(2);
ibin[0] = ((opr_val1&0x700)>>3)+0x11;
ibin[1] = (opr_val1&0xff);
return is_jmp_err;
}
return -1;

}
int CJNE_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//CJNE "A,direct,rel" Compare direct byte to Acc and Jump if Not Equal 3 24 PROGRAM BRANCHING 0xB5 $2  $3 
if(
(opr_cnt==0x3)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_VAL))
&&((opr_type3==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
is_jmp_err |= abs_to_rel(curr_addr+3,opr_val3);
opr_val3 &=0xff;
ibin.resize(3);
ibin[0] = 0xB5;
ibin[1] = opr_val2 ;
ibin[2] = opr_val3;
return is_jmp_err;
}
//CJNE "A,#data,rel" Compare immediate to Acc and Jump if Not Equal 3 24 PROGRAM BRANCHING 0xB4 $2  $3 
if(
(opr_cnt==0x3)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_IMM))
&&((opr_type3==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
is_jmp_err |= abs_to_rel(curr_addr+3,opr_val3);
opr_val3 &=0xff;
ibin.resize(3);
ibin[0] = 0xB4;
ibin[1] = opr_val2 ;
ibin[2] = opr_val3;
return is_jmp_err;
}
//CJNE "Rn,#data,rel" Compare immediate to register and Jump if Not Equal 3 24 PROGRAM BRANCHING 0xB8+$1 $2  $3 
if(
(opr_cnt==0x3)
&&((opr_type1==TOKENI_RN))
&&((opr_type2==TOKENI_IMM))
&&((opr_type3==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
opr_val2 &=0xff;
is_jmp_err |= abs_to_rel(curr_addr+3,opr_val3);
opr_val3 &=0xff;
ibin.resize(3);
ibin[0] = 0xB8+opr_val1;
ibin[1] = opr_val2 ;
ibin[2] = opr_val3;
return is_jmp_err;
}
//CJNE "@Ri,#data,rel" Compare immediate to indirect and Jump if Not Equal 3 24 PROGRAM BRANCHING 0xB6+$1 $2  $3 
if(
(opr_cnt==0x3)
&&((opr_type1==TOKENI_AT_RI))
&&((opr_type2==TOKENI_IMM))
&&((opr_type3==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
opr_val2 &=0xff;
is_jmp_err |= abs_to_rel(curr_addr+3,opr_val3);
opr_val3 &=0xff;
ibin.resize(3);
ibin[0] = 0xB6+opr_val1;
ibin[1] = opr_val2 ;
ibin[2] = opr_val3;
return is_jmp_err;
}
return -1;

}
int CLR_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//CLR C Clear Carry 1 12 BOOLEAN VARIABLE MANIPULATION 0xC3   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_C))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
ibin.resize(1);
ibin[0] = 0xC3;
return is_jmp_err;
}
//CLR bit Clear direct bit 2 12 BOOLEAN VARIABLE MANIPULATION 0xC2 $1   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_DOTBIT)||(opr_type1==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
ibin.resize(2);
ibin[0] = 0xC2;
ibin[1] = opr_val1 ;
return is_jmp_err;
}
//CLR A Clear Accumulator 1 12 LOGICAL OPERATIONS 0xE4   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_ACC))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
ibin.resize(1);
ibin[0] = 0xE4;
return is_jmp_err;
}
return -1;

}
int CPL_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//CPL C Complement Carry 1 12 BOOLEAN VARIABLE MANIPULATION 0xB3   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_C))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
ibin.resize(1);
ibin[0] = 0xB3;
return is_jmp_err;
}
//CPL bit Complement direct bit 2 12 BOOLEAN VARIABLE MANIPULATION 0xB2 $1   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_DOTBIT)||(opr_type1==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
ibin.resize(2);
ibin[0] = 0xB2;
ibin[1] = opr_val1 ;
return is_jmp_err;
}
//CPL A Complement Accumulator 1 12 LOGICAL OPERATIONS 0xF4   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_ACC))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
ibin.resize(1);
ibin[0] = 0xF4;
return is_jmp_err;
}
return -1;

}
int DA_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//DA A Decimal Adjust Accumulator 1 12 ARITHMETIC OPERATIONS 0xD4   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_ACC))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
ibin.resize(1);
ibin[0] = 0xD4;
return is_jmp_err;
}
return -1;

}
int DEC_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//DEC A Decrement Accumulator 1 12 ARITHMETIC OPERATIONS 0x14   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_ACC))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
ibin.resize(1);
ibin[0] = 0x14;
return is_jmp_err;
}
//DEC Rn Decrement Register 1 12 ARITHMETIC OPERATIONS 0x18+$1   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_RN))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
ibin.resize(1);
ibin[0] = 0x18+opr_val1;
return is_jmp_err;
}
//DEC direct Decrement direct byte 2 12 ARITHMETIC OPERATIONS 0x15 $1   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
ibin.resize(2);
ibin[0] = 0x15;
ibin[1] = opr_val1 ;
return is_jmp_err;
}
//DEC @Ri Decrement indirect RAM 1 12 ARITHMETIC OPERATIONS 0x16+$1   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_AT_RI))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
ibin.resize(1);
ibin[0] = 0x16+opr_val1;
return is_jmp_err;
}
return -1;

}
int DIV_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//DIV AB Divide A by B 1 48 ARITHMETIC OPERATIONS 0x84   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_AB))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
ibin.resize(1);
ibin[0] = 0x84;
return is_jmp_err;
}
return -1;

}
int DJNZ_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//DJNZ "Rn,rel" Decrement register and Jump if Not Zero 2 24 PROGRAM BRANCHING 0xD8+$1 $2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_RN))
&&((opr_type2==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
is_jmp_err |= abs_to_rel(curr_addr+2,opr_val2);
opr_val2 &=0xff;
ibin.resize(2);
ibin[0] = 0xD8+opr_val1;
ibin[1] = opr_val2 ;
return is_jmp_err;
}
//DJNZ "direct,rel" Decrement direct byte and Jump if Not Zero 3 24 PROGRAM BRANCHING 0xD5 $1  $2 
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_VAL))
&&((opr_type2==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
is_jmp_err |= abs_to_rel(curr_addr+3,opr_val2);
opr_val2 &=0xff;
ibin.resize(3);
ibin[0] = 0xD5;
ibin[1] = opr_val1 ;
ibin[2] = opr_val2;
return is_jmp_err;
}
return -1;

}
int INC_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//INC A Increment Accumulator 1 12 ARITHMETIC OPERATIONS 0x04   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_ACC))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
ibin.resize(1);
ibin[0] = 0x04;
return is_jmp_err;
}
//INC Rn Increment register 1 12 ARITHMETIC OPERATIONS 0x08+$1   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_RN))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
ibin.resize(1);
ibin[0] = 0x08+opr_val1;
return is_jmp_err;
}
//INC direct Increment direct byte 2 12 ARITHMETIC OPERATIONS 0x05 $1   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
ibin.resize(2);
ibin[0] = 0x05;
ibin[1] = opr_val1 ;
return is_jmp_err;
}
//INC @Ri Increment direct RAM 1 12 ARITHMETIC OPERATIONS 0x06+$1   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_AT_RI))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
ibin.resize(1);
ibin[0] = 0x06+opr_val1;
return is_jmp_err;
}
//INC DPTR Increment Data Pointer 1 24 ARITHMETIC OPERATIONS 0xA3   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_DPTR))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
ibin.resize(1);
ibin[0] = 0xA3;
return is_jmp_err;
}
return -1;

}
int JB_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//JB "bit,rel" Jump if direct Bit is set 3 24 BOOLEAN VARIABLE MANIPULATION 0x20 $1  $2 
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_DOTBIT)||(opr_type1==TOKENI_VAL))
&&((opr_type2==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
is_jmp_err |= abs_to_rel(curr_addr+3,opr_val2);
opr_val2 &=0xff;
ibin.resize(3);
ibin[0] = 0x20;
ibin[1] = opr_val1 ;
ibin[2] = opr_val2;
return is_jmp_err;
}
return -1;

}
int JBC_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//JBC "bit,rel" Jump if direct Bit is set & clear bit 3 24 BOOLEAN VARIABLE MANIPULATION 0x10 $1  $2 
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_DOTBIT)||(opr_type1==TOKENI_VAL))
&&((opr_type2==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
is_jmp_err |= abs_to_rel(curr_addr+3,opr_val2);
opr_val2 &=0xff;
ibin.resize(3);
ibin[0] = 0x10;
ibin[1] = opr_val1 ;
ibin[2] = opr_val2;
return is_jmp_err;
}
return -1;

}
int JC_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//JC rel Jump if Carry is set 2 24 BOOLEAN VARIABLE MANIPULATION 0x40 $1   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_VAL))
)
{
int is_jmp_err = 0;
is_jmp_err |= abs_to_rel(curr_addr+2,opr_val1);
opr_val1 &=0xff;
ibin.resize(2);
ibin[0] = 0x40;
ibin[1] = opr_val1 ;
return is_jmp_err;
}
return -1;

}
int JMP_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//JMP @A+DPTR Jump indirect relative to the DPTR 1 24 PROGRAM BRANCHING 0x73   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_AT_A_PLUS_DPTR))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
ibin.resize(1);
ibin[0] = 0x73;
return is_jmp_err;
}
//JMP rel Short Jump (relative addr) 2 24 PROGRAM BRANCHING 0x80 $1   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_VAL))
)
{
int is_jmp_err = 0;
is_jmp_err |= abs_to_rel(curr_addr+2,opr_val1);
opr_val1 &=0xff;
ibin.resize(2);
ibin[0] = 0x80;
ibin[1] = opr_val1 ;
return is_jmp_err;
}
return -1;

}
int JNB_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//JNB "bit,rel" Jump if direct Bit is Not set 3 24 BOOLEAN VARIABLE MANIPULATION 0x30 $1  $2 
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_DOTBIT)||(opr_type1==TOKENI_VAL))
&&((opr_type2==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
is_jmp_err |= abs_to_rel(curr_addr+3,opr_val2);
opr_val2 &=0xff;
ibin.resize(3);
ibin[0] = 0x30;
ibin[1] = opr_val1 ;
ibin[2] = opr_val2;
return is_jmp_err;
}
return -1;

}
int JNC_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//JNC rel Jump if Carry not set 2 24 BOOLEAN VARIABLE MANIPULATION 0x50 $1   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_VAL))
)
{
int is_jmp_err = 0;
is_jmp_err |= abs_to_rel(curr_addr+2,opr_val1);
opr_val1 &=0xff;
ibin.resize(2);
ibin[0] = 0x50;
ibin[1] = opr_val1 ;
return is_jmp_err;
}
return -1;

}
int JNZ_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//JNZ rel Jump if Accumulator is Not Zero 2 24 PROGRAM BRANCHING 0x70 $1   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_VAL))
)
{
int is_jmp_err = 0;
is_jmp_err |= abs_to_rel(curr_addr+2,opr_val1);
opr_val1 &=0xff;
ibin.resize(2);
ibin[0] = 0x70;
ibin[1] = opr_val1 ;
return is_jmp_err;
}
return -1;

}
int JZ_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//JZ rel Jump if Accumulator is Zero 2 24 PROGRAM BRANCHING 0x60 $1   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_VAL))
)
{
int is_jmp_err = 0;
is_jmp_err |= abs_to_rel(curr_addr+2,opr_val1);
opr_val1 &=0xff;
ibin.resize(2);
ibin[0] = 0x60;
ibin[1] = opr_val1 ;
return is_jmp_err;
}
return -1;

}
int LCALL_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//LCALL addr16 Long Subroutine Call 3 24 PROGRAM BRANCHING 0x12 ($1 &0xff00)>>8 ($1 &0xff) 
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0xffff;
ibin.resize(3);
ibin[0] = 0x12;
ibin[1] = (opr_val1 &0xff00)>>8;
ibin[2] = (opr_val1 &0xff);
return is_jmp_err;
}
return -1;

}
int LJMP_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//LJMP addr16 Long Jump 3 24 PROGRAM BRANCHING 0x02 ($1 &0xff00)>>8 ($1 &0xff) 
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0xffff;
ibin.resize(3);
ibin[0] = 0x02;
ibin[1] = (opr_val1 &0xff00)>>8;
ibin[2] = (opr_val1 &0xff);
return is_jmp_err;
}
return -1;

}
int MOV_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//MOV "C,bit" Move direct bit to Carry 2 12 BOOLEAN VARIABLE MANIPULATION 0xA2 $2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_C))
&&((opr_type2==TOKENI_DOTBIT)||(opr_type2==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(2);
ibin[0] = 0xA2;
ibin[1] = opr_val2 ;
return is_jmp_err;
}
//MOV "bit,C" Move Carry to direct bit 2 24 BOOLEAN VARIABLE MANIPULATION 0x92 $1   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_DOTBIT)||(opr_type1==TOKENI_VAL))
&&((opr_type2==TOKENI_C))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
opr_val2 &=0x00;
ibin.resize(2);
ibin[0] = 0x92;
ibin[1] = opr_val1 ;
return is_jmp_err;
}
//MOV "A,Rn" Move register to Accumulator 1 12 DATA TRANSFER 0xe8+$2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_RN))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(1);
ibin[0] = 0xe8+opr_val2;
return is_jmp_err;
}
//MOV "A,direct" Move direct byte to Accumulator 2 12 DATA TRANSFER 0xe5 $2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(2);
ibin[0] = 0xe5;
ibin[1] = opr_val2 ;
return is_jmp_err;
}
//MOV "A,@Ri" Move indirect RAM to Accumulator 1 12 DATA TRANSFER 0xe6+$2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_AT_RI))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(1);
ibin[0] = 0xe6+opr_val2;
return is_jmp_err;
}
//MOV "A,#data" Move immediate data to Accumulator 2 12 DATA TRANSFER 0x74 $2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_IMM))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(2);
ibin[0] = 0x74;
ibin[1] = opr_val2 ;
return is_jmp_err;
}
//MOV "Rn,A" Move Accumulator to register 1 12 DATA TRANSFER 0xF8+$1   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_RN))
&&((opr_type2==TOKENI_ACC))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
opr_val2 &=0x00;
ibin.resize(1);
ibin[0] = 0xF8+opr_val1;
return is_jmp_err;
}
//MOV "Rn,direct" Move direct byte to register 2 24 DATA TRANSFER 0xA8+$1 $2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_RN))
&&((opr_type2==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
opr_val2 &=0xff;
ibin.resize(2);
ibin[0] = 0xA8+opr_val1;
ibin[1] = opr_val2 ;
return is_jmp_err;
}
//MOV "Rn,#data" Move immediate data to register 2 12 DATA TRANSFER 0x78+$1 $2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_RN))
&&((opr_type2==TOKENI_IMM))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
opr_val2 &=0xff;
ibin.resize(2);
ibin[0] = 0x78+opr_val1;
ibin[1] = opr_val2 ;
return is_jmp_err;
}
//MOV "direct,A" Move Accumulator to direct byte 2 12 DATA TRANSFER 0xF5 $1   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_VAL))
&&((opr_type2==TOKENI_ACC))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
opr_val2 &=0x00;
ibin.resize(2);
ibin[0] = 0xF5;
ibin[1] = opr_val1 ;
return is_jmp_err;
}
//MOV "direct,Rn" Move register to direct byte 2 24 DATA TRANSFER 0x88+$2 $1   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_VAL))
&&((opr_type2==TOKENI_RN))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
opr_val2 &=0xff;
ibin.resize(2);
ibin[0] = 0x88+opr_val2;
ibin[1] = opr_val1 ;
return is_jmp_err;
}
//MOV "direct,direct" Move direct byte to direct 3 24 DATA TRANSFER 0x85 $2  $1 
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_VAL))
&&((opr_type2==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
opr_val2 &=0xff;
ibin.resize(3);
ibin[0] = 0x85;
ibin[1] = opr_val2 ;
ibin[2] = opr_val1;
return is_jmp_err;
}
//MOV "direct,@Ri" Move indirect RAM to direct byte 2 24 DATA TRANSFER 0x86+$2 $1   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_VAL))
&&((opr_type2==TOKENI_AT_RI))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
opr_val2 &=0xff;
ibin.resize(2);
ibin[0] = 0x86+opr_val2;
ibin[1] = opr_val1 ;
return is_jmp_err;
}
//MOV "direct,#data" Move immediate data to direct byte 3 24 DATA TRANSFER 0x75 $1  $2 
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_VAL))
&&((opr_type2==TOKENI_IMM))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
opr_val2 &=0xff;
ibin.resize(3);
ibin[0] = 0x75;
ibin[1] = opr_val1 ;
ibin[2] = opr_val2;
return is_jmp_err;
}
//MOV "@Ri,A" Move Accumulator to indirect RAM 1 12 DATA TRANSFER 0xF6+$1   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_AT_RI))
&&((opr_type2==TOKENI_ACC))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
opr_val2 &=0x00;
ibin.resize(1);
ibin[0] = 0xF6+opr_val1;
return is_jmp_err;
}
//MOV "@Ri,direct" Move direct byte to indirect RAM 2 24 DATA TRANSFER 0xA6+$1 $2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_AT_RI))
&&((opr_type2==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
opr_val2 &=0xff;
ibin.resize(2);
ibin[0] = 0xA6+opr_val1;
ibin[1] = opr_val2 ;
return is_jmp_err;
}
//MOV "@Ri,#data" Move immediate data to indirect RAM 2 12 DATA TRANSFER 0x76+$1 $2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_AT_RI))
&&((opr_type2==TOKENI_IMM))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
opr_val2 &=0xff;
ibin.resize(2);
ibin[0] = 0x76+opr_val1;
ibin[1] = opr_val2 ;
return is_jmp_err;
}
//MOV "DPTR,#data16" Load Data Pointer with a 16-bit constant 3 24 DATA TRANSFER 0x90 ($2 &0xff00)>>8 ($2 &0xff) 
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_DPTR))
&&((opr_type2==TOKENI_IMM))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xffff;
ibin.resize(3);
ibin[0] = 0x90;
ibin[1] = (opr_val2 &0xff00)>>8;
ibin[2] = (opr_val2 &0xff);
return is_jmp_err;
}
return -1;

}
int MOVC_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//MOVC "A,@A+DPTR" Move Code byte relative to DPTR to Acc 1 24 DATA TRANSFER 0x93   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_AT_A_PLUS_DPTR))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0x00;
ibin.resize(1);
ibin[0] = 0x93;
return is_jmp_err;
}
//MOVC "A,@A+PC" Move Code byte relative to PC to Acc 1 24 DATA TRANSFER 0x83   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_AT_A_PLUS_PC))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0x00;
ibin.resize(1);
ibin[0] = 0x83;
return is_jmp_err;
}
return -1;

}
int MOVX_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//MOVX "A,@Ri" Move External RAM (8- bit addr) to Acc 1 24 DATA TRANSFER 0xe2+$2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_AT_RI))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(1);
ibin[0] = 0xe2+opr_val2;
return is_jmp_err;
}
//MOVX "A,@DPTR" Move Exernal RAM (16- bit addr) to Acc 1 24 DATA TRANSFER 0xe0   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_AT_DPTR))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0x00;
ibin.resize(1);
ibin[0] = 0xe0;
return is_jmp_err;
}
//MOVX "@Ri,A" Move Acc to External RAM (8-bit addr) 1 24 DATA TRANSFER 0xf2+$1   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_AT_RI))
&&((opr_type2==TOKENI_ACC))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
opr_val2 &=0x00;
ibin.resize(1);
ibin[0] = 0xf2+opr_val1;
return is_jmp_err;
}
//MOVX "@DPTR,A" Move Acc to External RAM (16-bit addr) 1 24 DATA TRANSFER 0xf0   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_AT_DPTR))
&&((opr_type2==TOKENI_ACC))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0x00;
ibin.resize(1);
ibin[0] = 0xf0;
return is_jmp_err;
}
return -1;

}
int MUL_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//MUL AB Multiply A & B 1 48 ARITHMETIC OPERATIONS 0xA4   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_AB))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
ibin.resize(1);
ibin[0] = 0xA4;
return is_jmp_err;
}
return -1;

}
int NOP_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//NOP  No Operation 1 12 PROGRAM BRANCHING 0x00   
if(
(opr_cnt==0x0)
)
{
int is_jmp_err = 0;
ibin.resize(1);
ibin[0] = 0x00;
return is_jmp_err;
}
return -1;

}
int ORL_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//ORL "C,bit" OR direct bit to Carry 2 24 BOOLEAN VARIABLE MANIPULATION 0x72 $2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_C))
&&((opr_type2==TOKENI_DOTBIT)||(opr_type2==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(2);
ibin[0] = 0x72;
ibin[1] = opr_val2 ;
return is_jmp_err;
}
//ORL "C,/bit" OR complement of direct bit to Carry 2 24 BOOLEAN VARIABLE MANIPULATION 0xA0 $2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_C))
&&((opr_type2==TOKENI_NBIT))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(2);
ibin[0] = 0xA0;
ibin[1] = opr_val2 ;
return is_jmp_err;
}
//ORL "A,Rn" OR register to Accumulator 1 12 LOGICAL OPERATIONS 0x48+$2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_RN))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(1);
ibin[0] = 0x48+opr_val2;
return is_jmp_err;
}
//ORL "A,direct" OR direct byte to Accumulator 2 12 LOGICAL OPERATIONS 0x45 $2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(2);
ibin[0] = 0x45;
ibin[1] = opr_val2 ;
return is_jmp_err;
}
//ORL "A,@Ri" OR indirect RAM to Accumulator 1 12 LOGICAL OPERATIONS 0x46+$2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_AT_RI))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(1);
ibin[0] = 0x46+opr_val2;
return is_jmp_err;
}
//ORL "A,#data" OR immediate data to Accumulator 2 12 LOGICAL OPERATIONS 0x44 $2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_IMM))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(2);
ibin[0] = 0x44;
ibin[1] = opr_val2 ;
return is_jmp_err;
}
//ORL "direct,A" OR Accumulator to direct byte 2 12 LOGICAL OPERATIONS 0x42 $1   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_VAL))
&&((opr_type2==TOKENI_ACC))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
opr_val2 &=0x00;
ibin.resize(2);
ibin[0] = 0x42;
ibin[1] = opr_val1 ;
return is_jmp_err;
}
//ORL "direct,#data" OR immediate data to direct byte 3 24 LOGICAL OPERATIONS 0x43 $1  $2 
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_VAL))
&&((opr_type2==TOKENI_IMM))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
opr_val2 &=0xff;
ibin.resize(3);
ibin[0] = 0x43;
ibin[1] = opr_val1 ;
ibin[2] = opr_val2;
return is_jmp_err;
}
return -1;

}
int POP_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//POP direct Pop direct byte from stack 2 24 DATA TRANSFER 0xD0 $1   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
ibin.resize(2);
ibin[0] = 0xD0;
ibin[1] = opr_val1 ;
return is_jmp_err;
}
return -1;

}
int PUSH_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//PUSH direct Push direct byte onto stack 2 24 DATA TRANSFER 0xC0 $1   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
ibin.resize(2);
ibin[0] = 0xC0;
ibin[1] = opr_val1 ;
return is_jmp_err;
}
return -1;

}
int RET_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//RET  Return from Subroutine 1 24 PROGRAM BRANCHING 0x22   
if(
(opr_cnt==0x0)
)
{
int is_jmp_err = 0;
ibin.resize(1);
ibin[0] = 0x22;
return is_jmp_err;
}
return -1;

}
int RETI_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//RETI  Return from interrupt 1 24 PROGRAM BRANCHING 0x32   
if(
(opr_cnt==0x0)
)
{
int is_jmp_err = 0;
ibin.resize(1);
ibin[0] = 0x32;
return is_jmp_err;
}
return -1;

}
int RL_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//RL A Rotate Accumulator Left 1 12 LOGICAL OPERATIONS 0x23   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_ACC))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
ibin.resize(1);
ibin[0] = 0x23;
return is_jmp_err;
}
return -1;

}
int RLC_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//RLC A Rotate Accumulator Left through the Carry 1 12 LOGICAL OPERATIONS 0x33   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_ACC))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
ibin.resize(1);
ibin[0] = 0x33;
return is_jmp_err;
}
return -1;

}
int RR_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//RR A Rotate Accumulator Right 1 12 LOGICAL OPERATIONS 0x03   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_ACC))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
ibin.resize(1);
ibin[0] = 0x03;
return is_jmp_err;
}
return -1;

}
int RRC_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//RRC A Rotate Accumulator Right through the Carry 1 12 LOGICAL OPERATIONS 0x13   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_ACC))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
ibin.resize(1);
ibin[0] = 0x13;
return is_jmp_err;
}
return -1;

}
int SETB_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//SETB C Set Carry 1 12 BOOLEAN VARIABLE MANIPULATION 0xD3   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_C))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
ibin.resize(1);
ibin[0] = 0xD3;
return is_jmp_err;
}
//SETB bit Set direct bit 2 12 BOOLEAN VARIABLE MANIPULATION 0xD2 $1   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_DOTBIT)||(opr_type1==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
ibin.resize(2);
ibin[0] = 0xD2;
ibin[1] = opr_val1 ;
return is_jmp_err;
}
return -1;

}
int SIMTRAP_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//SIMTRAP "direct,direct" A5 test A if not zero 3 12 TEST 0xA5 $1  $2 
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_VAL))
&&((opr_type2==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
opr_val2 &=0xff;
ibin.resize(3);
ibin[0] = 0xA5;
ibin[1] = opr_val1 ;
ibin[2] = opr_val2;
return is_jmp_err;
}
return -1;

}
int SJMP_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//SJMP rel Short Jump (relative addr) 2 24 PROGRAM BRANCHING 0x80 $1   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_VAL))
)
{
int is_jmp_err = 0;
is_jmp_err |= abs_to_rel(curr_addr+2,opr_val1);
opr_val1 &=0xff;
ibin.resize(2);
ibin[0] = 0x80;
ibin[1] = opr_val1 ;
return is_jmp_err;
}
return -1;

}
int SUBB_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//SUBB "A,Rn" Subtract Register from Acc with borrow 1 12 ARITHMETIC OPERATIONS 0x98+$2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_RN))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(1);
ibin[0] = 0x98+opr_val2;
return is_jmp_err;
}
//SUBB "A,direct" Subtract direct byte from Acc with borrow 2 12 ARITHMETIC OPERATIONS 0x95 $2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(2);
ibin[0] = 0x95;
ibin[1] = opr_val2 ;
return is_jmp_err;
}
//SUBB "A,@Ri" Subtract indirect RAM from ACC with borrow 1 12 ARITHMETIC OPERATIONS 0x96+$2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_AT_RI))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(1);
ibin[0] = 0x96+opr_val2;
return is_jmp_err;
}
//SUBB "A,#data" Subtract immediate data from Acc with borrow 2 12 ARITHMETIC OPERATIONS 0x94 $2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_IMM))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(2);
ibin[0] = 0x94;
ibin[1] = opr_val2 ;
return is_jmp_err;
}
return -1;

}
int SWAP_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//SWAP A Swap nibbles within the Accumulator 1 12 LOGICAL OPERATIONS 0xC4   
if(
(opr_cnt==0x1)
&&((opr_type1==TOKENI_ACC))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
ibin.resize(1);
ibin[0] = 0xC4;
return is_jmp_err;
}
return -1;

}
int XCH_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//XCH "A,Rn" Exchange register with Accumulator 1 12 DATA TRANSFER 0xC8+$2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_RN))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(1);
ibin[0] = 0xC8+opr_val2;
return is_jmp_err;
}
//XCH "A,direct" Exchange direct byte with Accumulator 2 12 DATA TRANSFER 0xC5 $2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(2);
ibin[0] = 0xC5;
ibin[1] = opr_val2 ;
return is_jmp_err;
}
//XCH "A,@Ri" Exchange indirect RAM with Accumulator 1 12 DATA TRANSFER 0xC6+$2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_AT_RI))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(1);
ibin[0] = 0xC6+opr_val2;
return is_jmp_err;
}
return -1;

}
int XCHD_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//XCHD "A,@Ri" Exchange low-order Digit indirect RAM with Acc 1 12 DATA TRANSFER 0xD6+$2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_AT_RI))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(1);
ibin[0] = 0xD6+opr_val2;
return is_jmp_err;
}
return -1;

}
int XRL_CodeGen(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin)

{
//XRL "A,Rn" Exclusive-OR register to Accumulator 1 12 LOGICAL OPERATIONS 0x68+$2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_RN))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(1);
ibin[0] = 0x68+opr_val2;
return is_jmp_err;
}
//XRL "A,direct" Exclusive-OR direct byte to Accumulator 2 12 LOGICAL OPERATIONS 0x65 $2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_VAL))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(2);
ibin[0] = 0x65;
ibin[1] = opr_val2 ;
return is_jmp_err;
}
//XRL "A,@Ri" Exclusive-OR indirect RAM to Accumulator 1 12 LOGICAL OPERATIONS 0x66+$2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_AT_RI))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(1);
ibin[0] = 0x66+opr_val2;
return is_jmp_err;
}
//XRL "A,#data" Exclusive-OR immediate data to Accumulator 2 12 LOGICAL OPERATIONS 0x64 $2   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_ACC))
&&((opr_type2==TOKENI_IMM))
)
{
int is_jmp_err = 0;
opr_val1 &=0x00;
opr_val2 &=0xff;
ibin.resize(2);
ibin[0] = 0x64;
ibin[1] = opr_val2 ;
return is_jmp_err;
}
//XRL "direct,A" Exclusive-OR Accumulator to direct byte 2 12 LOGICAL OPERATIONS 0x62 $1   
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_VAL))
&&((opr_type2==TOKENI_ACC))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
opr_val2 &=0x00;
ibin.resize(2);
ibin[0] = 0x62;
ibin[1] = opr_val1 ;
return is_jmp_err;
}
//XRL "direct,#data" Exclusive-OR immediate data to direct byte 3 24 LOGICAL OPERATIONS 0x63 $1  $2 
if(
(opr_cnt==0x2)
&&((opr_type1==TOKENI_VAL))
&&((opr_type2==TOKENI_IMM))
)
{
int is_jmp_err = 0;
opr_val1 &=0xff;
opr_val2 &=0xff;
ibin.resize(3);
ibin[0] = 0x63;
ibin[1] = opr_val1 ;
ibin[2] = opr_val2;
return is_jmp_err;
}
return -1;

}
typedef int (*ASM_FUNC_PTR)(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr, std::string &ibin);
static std::map<std::string, ASM_FUNC_PTR> g_func_map {
{"ACALL",ACALL_CodeGen},
{"ADD",ADD_CodeGen},
{"ADDC",ADDC_CodeGen},
{"AJMP",AJMP_CodeGen},
{"ANL",ANL_CodeGen},
{"CALL",CALL_CodeGen},
{"CJNE",CJNE_CodeGen},
{"CLR",CLR_CodeGen},
{"CPL",CPL_CodeGen},
{"DA",DA_CodeGen},
{"DEC",DEC_CodeGen},
{"DIV",DIV_CodeGen},
{"DJNZ",DJNZ_CodeGen},
{"INC",INC_CodeGen},
{"JB",JB_CodeGen},
{"JBC",JBC_CodeGen},
{"JC",JC_CodeGen},
{"JMP",JMP_CodeGen},
{"JNB",JNB_CodeGen},
{"JNC",JNC_CodeGen},
{"JNZ",JNZ_CodeGen},
{"JZ",JZ_CodeGen},
{"LCALL",LCALL_CodeGen},
{"LJMP",LJMP_CodeGen},
{"MOV",MOV_CodeGen},
{"MOVC",MOVC_CodeGen},
{"MOVX",MOVX_CodeGen},
{"MUL",MUL_CodeGen},
{"NOP",NOP_CodeGen},
{"ORL",ORL_CodeGen},
{"POP",POP_CodeGen},
{"PUSH",PUSH_CodeGen},
{"RET",RET_CodeGen},
{"RETI",RETI_CodeGen},
{"RL",RL_CodeGen},
{"RLC",RLC_CodeGen},
{"RR",RR_CodeGen},
{"RRC",RRC_CodeGen},
{"SETB",SETB_CodeGen},
{"SIMTRAP",SIMTRAP_CodeGen},
{"SJMP",SJMP_CodeGen},
{"SUBB",SUBB_CodeGen},
{"SWAP",SWAP_CodeGen},
{"XCH",XCH_CodeGen},
{"XCHD",XCHD_CodeGen},
{"XRL",XRL_CodeGen},
};
int get_asm_to_bin(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr,  std::string &ibin)
{
ASM_FUNC_PTR ptr = g_func_map[cmd];
assert(ptr!=NULL);
return ptr(cmd,opr_cnt,opr_type1, opr_val1, opr_type2, opr_val2, opr_type3, opr_val3,curr_addr, ibin);

}//asm_to_bin_func end

}//namespace end
