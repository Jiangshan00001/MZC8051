#include "to_asm.h"
#include "dis_funcs.h"
namespace NS_AMS8051HEX{
int AA_0H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//0|	1|	NOP|	|	-1|	|	|	|	
mout<<"NOP"<<" ";
mout<<""<<";";
return 0;
}

int AA_1H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//1|	2|	AJMP|	addr11|	1|	(((($0>>5)<<8)+($1&0xff))&0x7ff)|	|	|	
mout<<"AJMP"<<" ";
unsigned val0=((((mbin[i_byte_offset]>>5)<<8)+(mbin[i_byte_offset+1]&0xff))&0x7ff);
mout<<dis->type_to_str_TOKEN_ADDR11(val0, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_2H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//2|	3|	LJMP|	addr16|	1|	((($1<<8) + ($2&0xff))&0xffff)|	|	|	
mout<<"LJMP"<<" ";
unsigned val0=(((mbin[i_byte_offset+1]<<8) + (mbin[i_byte_offset+2]&0xff))&0xffff);
mout<<dis->type_to_str_TOKEN_ADDR16(val0, curr_addr, 3);
mout<<";"; 
return 0;
}

int AA_3H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//3|	1|	RR|	A|	-1|	|	|	|	
mout<<"RR"<<" ";
mout<<"A"<<";";
return 0;
}

int AA_4H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//4|	1|	INC|	A|	-1|	|	|	|	
mout<<"INC"<<" ";
mout<<"A"<<";";
return 0;
}

int AA_5H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//5|	2|	INC|	data addr|	1|	(($1)&0xff)|	|	|	
mout<<"INC"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val0, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_6H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//6|	1|	INC|	@R0|	-1|	|	|	|	
mout<<"INC"<<" ";
mout<<"@R0"<<";";
return 0;
}

int AA_7H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//7|	1|	INC|	@R1|	-1|	|	|	|	
mout<<"INC"<<" ";
mout<<"@R1"<<";";
return 0;
}

int AA_8H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//8|	1|	INC|	R0|	-1|	|	|	|	
mout<<"INC"<<" ";
mout<<"R0"<<";";
return 0;
}

int AA_9H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//9|	1|	INC|	R1|	-1|	|	|	|	
mout<<"INC"<<" ";
mout<<"R1"<<";";
return 0;
}

int AA_0AH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//0A|	1|	INC|	R2|	-1|	|	|	|	
mout<<"INC"<<" ";
mout<<"R2"<<";";
return 0;
}

int AA_0BH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//0B|	1|	INC|	R3|	-1|	|	|	|	
mout<<"INC"<<" ";
mout<<"R3"<<";";
return 0;
}

int AA_0CH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//0C|	1|	INC|	R4|	-1|	|	|	|	
mout<<"INC"<<" ";
mout<<"R4"<<";";
return 0;
}

int AA_0DH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//0D|	1|	INC|	R5|	-1|	|	|	|	
mout<<"INC"<<" ";
mout<<"R5"<<";";
return 0;
}

int AA_0EH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//0E|	1|	INC|	R6|	-1|	|	|	|	
mout<<"INC"<<" ";
mout<<"R6"<<";";
return 0;
}

int AA_0FH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//0F|	1|	INC|	R7|	-1|	|	|	|	
mout<<"INC"<<" ";
mout<<"R7"<<";";
return 0;
}

int AA_10H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//10|	3|	JBC|	"bit addr,rel code addr"|	2|	(($1)&0xff)|	(($2)&0xff)|	|	
mout<<"JBC"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_BIT(val0, curr_addr, 3);
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+2])&0xff);
mout<<dis->type_to_str_TOKEN_REL(val1, curr_addr, 3);
mout<<";"; 
return 0;
}

int AA_11H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//11|	2|	ACALL|	addr11|	1|	((($1&0xff) + (($0&0xe0)<<3))&0x7ff)|	|	|	
mout<<"ACALL"<<" ";
unsigned val0=(((mbin[i_byte_offset+1]&0xff) + ((mbin[i_byte_offset]&0xe0)<<3))&0x7ff);
mout<<dis->type_to_str_TOKEN_ADDR11(val0, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_12H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//12|	3|	LCALL|	addr16|	1|	((($1<<8) + ($2&0xff))&0xffff)|	|	|	
mout<<"LCALL"<<" ";
unsigned val0=(((mbin[i_byte_offset+1]<<8) + (mbin[i_byte_offset+2]&0xff))&0xffff);
mout<<dis->type_to_str_TOKEN_ADDR16(val0, curr_addr, 3);
mout<<";"; 
return 0;
}

int AA_13H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//13|	1|	RRC|	A|	-1|	|	|	|	
mout<<"RRC"<<" ";
mout<<"A"<<";";
return 0;
}

int AA_14H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//14|	1|	DEC|	A|	-1|	|	|	|	
mout<<"DEC"<<" ";
mout<<"A"<<";";
return 0;
}

int AA_15H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//15|	2|	DEC|	data addr|	1|	(($1)&0xff)|	|	|	
mout<<"DEC"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val0, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_16H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//16|	1|	DEC|	@R0|	-1|	|	|	|	
mout<<"DEC"<<" ";
mout<<"@R0"<<";";
return 0;
}

int AA_17H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//17|	1|	DEC|	@R1|	-1|	|	|	|	
mout<<"DEC"<<" ";
mout<<"@R1"<<";";
return 0;
}

int AA_18H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//18|	1|	DEC|	R0|	-1|	|	|	|	
mout<<"DEC"<<" ";
mout<<"R0"<<";";
return 0;
}

int AA_19H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//19|	1|	DEC|	R1|	-1|	|	|	|	
mout<<"DEC"<<" ";
mout<<"R1"<<";";
return 0;
}

int AA_1AH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//1A|	1|	DEC|	R2|	-1|	|	|	|	
mout<<"DEC"<<" ";
mout<<"R2"<<";";
return 0;
}

int AA_1BH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//1B|	1|	DEC|	R3|	-1|	|	|	|	
mout<<"DEC"<<" ";
mout<<"R3"<<";";
return 0;
}

int AA_1CH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//1C|	1|	DEC|	R4|	-1|	|	|	|	
mout<<"DEC"<<" ";
mout<<"R4"<<";";
return 0;
}

int AA_1DH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//1D|	1|	DEC|	R5|	-1|	|	|	|	
mout<<"DEC"<<" ";
mout<<"R5"<<";";
return 0;
}

int AA_1EH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//1E|	1|	DEC|	R6|	-1|	|	|	|	
mout<<"DEC"<<" ";
mout<<"R6"<<";";
return 0;
}

int AA_1FH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//1F|	1|	DEC|	R7|	-1|	|	|	|	
mout<<"DEC"<<" ";
mout<<"R7"<<";";
return 0;
}

int AA_20H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//20|	3|	JB|	"bit addr,rel code addr"|	2|	(($1+0)&0xff)|	(($2)&0xff)|	|	
mout<<"JB"<<" ";
unsigned val0=((mbin[i_byte_offset+1]+0)&0xff);
mout<<dis->type_to_str_TOKEN_BIT(val0, curr_addr, 3);
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+2])&0xff);
mout<<dis->type_to_str_TOKEN_REL(val1, curr_addr, 3);
mout<<";"; 
return 0;
}

int AA_21H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//21|	2|	AJMP|	addr11|	1|	(((($0>>5)<<8)+($1&0xff))&0x7ff)|	|	|	
mout<<"AJMP"<<" ";
unsigned val0=((((mbin[i_byte_offset]>>5)<<8)+(mbin[i_byte_offset+1]&0xff))&0x7ff);
mout<<dis->type_to_str_TOKEN_ADDR11(val0, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_22H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//22|	1|	RET|	|	-1|	|	|	|	
mout<<"RET"<<" ";
mout<<""<<";";
return 0;
}

int AA_23H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//23|	1|	RL|	A|	-1|	|	|	|	
mout<<"RL"<<" ";
mout<<"A"<<";";
return 0;
}

int AA_24H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//24|	2|	ADD|	"A,#data"|	2|	|	(($1+0)&0xff)|	|	
mout<<"ADD"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1]+0)&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_25H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//25|	2|	ADD|	"A,data addr"|	2|	|	(($1+0)&0xff)|	|	
mout<<"ADD"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1]+0)&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_26H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//26|	1|	ADD|	"A,@R0"|	-1|	|	|	|	
mout<<"ADD"<<" ";
mout<<"A,@R0"<<";";
return 0;
}

int AA_27H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//27|	1|	ADD|	"A,@R1"|	-1|	|	|	|	
mout<<"ADD"<<" ";
mout<<"A,@R1"<<";";
return 0;
}

int AA_28H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//28|	1|	ADD|	"A,R0"|	-1|	|	|	|	
mout<<"ADD"<<" ";
mout<<"A,R0"<<";";
return 0;
}

int AA_29H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//29|	1|	ADD|	"A,R1"|	-1|	|	|	|	
mout<<"ADD"<<" ";
mout<<"A,R1"<<";";
return 0;
}

int AA_2AH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//2A|	1|	ADD|	"A,R2"|	-1|	|	|	|	
mout<<"ADD"<<" ";
mout<<"A,R2"<<";";
return 0;
}

int AA_2BH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//2B|	1|	ADD|	"A,R3"|	-1|	|	|	|	
mout<<"ADD"<<" ";
mout<<"A,R3"<<";";
return 0;
}

int AA_2CH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//2C|	1|	ADD|	"A,R4"|	-1|	|	|	|	
mout<<"ADD"<<" ";
mout<<"A,R4"<<";";
return 0;
}

int AA_2DH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//2D|	1|	ADD|	"A,R5"|	-1|	|	|	|	
mout<<"ADD"<<" ";
mout<<"A,R5"<<";";
return 0;
}

int AA_2EH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//2E|	1|	ADD|	"A,R6"|	-1|	|	|	|	
mout<<"ADD"<<" ";
mout<<"A,R6"<<";";
return 0;
}

int AA_2FH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//2F|	1|	ADD|	"A,R7"|	-1|	|	|	|	
mout<<"ADD"<<" ";
mout<<"A,R7"<<";";
return 0;
}

int AA_30H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//30|	3|	JNB|	"bit addr,rel code addr"|	2|	(($1)&0xff)|	(($2)&0xff)|	|	
mout<<"JNB"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_BIT(val0, curr_addr, 3);
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+2])&0xff);
mout<<dis->type_to_str_TOKEN_REL(val1, curr_addr, 3);
mout<<";"; 
return 0;
}

int AA_31H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//31|	2|	ACALL|	addr11|	1|	((($1&0xff) + (($0&0xe0)<<3))&0x7ff)|	|	|	
mout<<"ACALL"<<" ";
unsigned val0=(((mbin[i_byte_offset+1]&0xff) + ((mbin[i_byte_offset]&0xe0)<<3))&0x7ff);
mout<<dis->type_to_str_TOKEN_ADDR11(val0, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_32H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//32|	1|	RETI|	|	-1|	|	|	|	
mout<<"RETI"<<" ";
mout<<""<<";";
return 0;
}

int AA_33H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//33|	1|	RLC|	A|	-1|	|	|	|	
mout<<"RLC"<<" ";
mout<<"A"<<";";
return 0;
}

int AA_34H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//34|	2|	ADDC|	"A,#data"|	2|	|	(($1)&0xff)|	|	
mout<<"ADDC"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_35H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//35|	2|	ADDC|	"A,data addr"|	2|	|	(($1)&0xff)|	|	
mout<<"ADDC"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_36H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//36|	1|	ADDC|	"A,@R0"|	-1|	|	|	|	
mout<<"ADDC"<<" ";
mout<<"A,@R0"<<";";
return 0;
}

int AA_37H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//37|	1|	ADDC|	"A,@R1"|	-1|	|	|	|	
mout<<"ADDC"<<" ";
mout<<"A,@R1"<<";";
return 0;
}

int AA_38H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//38|	1|	ADDC|	"A,R0"|	-1|	|	|	|	
mout<<"ADDC"<<" ";
mout<<"A,R0"<<";";
return 0;
}

int AA_39H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//39|	1|	ADDC|	"A,R1"|	-1|	|	|	|	
mout<<"ADDC"<<" ";
mout<<"A,R1"<<";";
return 0;
}

int AA_3AH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//3A|	1|	ADDC|	"A,R2"|	-1|	|	|	|	
mout<<"ADDC"<<" ";
mout<<"A,R2"<<";";
return 0;
}

int AA_3BH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//3B|	1|	ADDC|	"A,R3"|	-1|	|	|	|	
mout<<"ADDC"<<" ";
mout<<"A,R3"<<";";
return 0;
}

int AA_3CH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//3C|	1|	ADDC|	"A,R4"|	-1|	|	|	|	
mout<<"ADDC"<<" ";
mout<<"A,R4"<<";";
return 0;
}

int AA_3DH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//3D|	1|	ADDC|	"A,R5"|	-1|	|	|	|	
mout<<"ADDC"<<" ";
mout<<"A,R5"<<";";
return 0;
}

int AA_3EH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//3E|	1|	ADDC|	"A,R6"|	-1|	|	|	|	
mout<<"ADDC"<<" ";
mout<<"A,R6"<<";";
return 0;
}

int AA_3FH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//3F|	1|	ADDC|	"A,R7"|	-1|	|	|	|	
mout<<"ADDC"<<" ";
mout<<"A,R7"<<";";
return 0;
}

int AA_40H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//40|	2|	JC|	rel code addr|	1|	(($1)&0xff)|	|	|	
mout<<"JC"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_REL(val0, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_41H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//41|	2|	AJMP|	abs code addr|	1|	(((($0>>5)<<8)+($1&0xff))&0x7ff)|	|	|	
mout<<"AJMP"<<" ";
unsigned val0=((((mbin[i_byte_offset]>>5)<<8)+(mbin[i_byte_offset+1]&0xff))&0x7ff);
mout<<dis->type_to_str_TOKEN_ADDR11(val0, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_42H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//42|	2|	ORL|	"data addr,A"|	2|	(($1)&0xff)|	|	|	
mout<<"ORL"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val0, curr_addr, 2);
mout<<", "; 
mout<<"A";
mout<<";"; 
return 0;
}

int AA_43H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//43|	3|	ORL|	"data addr,#data"|	2|	(($1)&0xff)|	(($2)&0xff)|	|	
mout<<"ORL"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val0, curr_addr, 3);
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+2])&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 3);
mout<<";"; 
return 0;
}

int AA_44H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//44|	2|	ORL|	"A,#data"|	2|	|	(($1)&0xff)|	|	
mout<<"ORL"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_45H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//45|	2|	ORL|	"A,data addr"|	2|	|	(($1)&0xff)|	|	
mout<<"ORL"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_46H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//46|	1|	ORL|	"A,@R0"|	-1|	|	|	|	
mout<<"ORL"<<" ";
mout<<"A,@R0"<<";";
return 0;
}

int AA_47H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//47|	1|	ORL|	"A,@R1"|	-1|	|	|	|	
mout<<"ORL"<<" ";
mout<<"A,@R1"<<";";
return 0;
}

int AA_48H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//48|	1|	ORL|	"A,R0"|	-1|	|	|	|	
mout<<"ORL"<<" ";
mout<<"A,R0"<<";";
return 0;
}

int AA_49H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//49|	1|	ORL|	"A,R1"|	-1|	|	|	|	
mout<<"ORL"<<" ";
mout<<"A,R1"<<";";
return 0;
}

int AA_4AH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//4A|	1|	ORL|	"A,R2"|	-1|	|	|	|	
mout<<"ORL"<<" ";
mout<<"A,R2"<<";";
return 0;
}

int AA_4BH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//4B|	1|	ORL|	"A,R3"|	-1|	|	|	|	
mout<<"ORL"<<" ";
mout<<"A,R3"<<";";
return 0;
}

int AA_4CH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//4C|	1|	ORL|	"A,R4"|	-1|	|	|	|	
mout<<"ORL"<<" ";
mout<<"A,R4"<<";";
return 0;
}

int AA_4DH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//4D|	1|	ORL|	"A,R5"|	-1|	|	|	|	
mout<<"ORL"<<" ";
mout<<"A,R5"<<";";
return 0;
}

int AA_4EH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//4E|	1|	ORL|	"A,R6"|	-1|	|	|	|	
mout<<"ORL"<<" ";
mout<<"A,R6"<<";";
return 0;
}

int AA_4FH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//4F|	1|	ORL|	"A,R7"|	-1|	|	|	|	
mout<<"ORL"<<" ";
mout<<"A,R7"<<";";
return 0;
}

int AA_50H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//50|	2|	JNC|	rel code addr|	1|	(($1)&0xff)|	|	|	
mout<<"JNC"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_REL(val0, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_51H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//51|	2|	ACALL|	abs code addr|	1|	((($1&0xff) + (($0&0xe0)<<3))&0x7ff)|	|	|	
mout<<"ACALL"<<" ";
unsigned val0=(((mbin[i_byte_offset+1]&0xff) + ((mbin[i_byte_offset]&0xe0)<<3))&0x7ff);
mout<<dis->type_to_str_TOKEN_ADDR11(val0, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_52H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//52|	2|	ANL|	"data addr,A"|	2|	(($1)&0xff)|	|	|	
mout<<"ANL"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val0, curr_addr, 2);
mout<<", "; 
mout<<"A";
mout<<";"; 
return 0;
}

int AA_53H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//53|	3|	ANL|	"data addr,#data"|	2|	(($1)&0xff)|	(($2)&0xff)|	|	
mout<<"ANL"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val0, curr_addr, 3);
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+2])&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 3);
mout<<";"; 
return 0;
}

int AA_54H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//54|	2|	ANL|	"A,#data"|	2|	|	(($1)&0xff)|	|	
mout<<"ANL"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_55H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//55|	2|	ANL|	"A,data addr"|	2|	|	(($1)&0xff)|	|	
mout<<"ANL"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_56H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//56|	1|	ANL|	"A,@R0"|	-1|	|	|	|	
mout<<"ANL"<<" ";
mout<<"A,@R0"<<";";
return 0;
}

int AA_57H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//57|	1|	ANL|	"A,@R1"|	-1|	|	|	|	
mout<<"ANL"<<" ";
mout<<"A,@R1"<<";";
return 0;
}

int AA_58H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//58|	1|	ANL|	"A,R0"|	-1|	|	|	|	
mout<<"ANL"<<" ";
mout<<"A,R0"<<";";
return 0;
}

int AA_59H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//59|	1|	ANL|	"A,R1"|	-1|	|	|	|	
mout<<"ANL"<<" ";
mout<<"A,R1"<<";";
return 0;
}

int AA_5AH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//5A|	1|	ANL|	"A,R2"|	-1|	|	|	|	
mout<<"ANL"<<" ";
mout<<"A,R2"<<";";
return 0;
}

int AA_5BH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//5B|	1|	ANL|	"A,R3"|	-1|	|	|	|	
mout<<"ANL"<<" ";
mout<<"A,R3"<<";";
return 0;
}

int AA_5CH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//5C|	1|	ANL|	"A,R4"|	-1|	|	|	|	
mout<<"ANL"<<" ";
mout<<"A,R4"<<";";
return 0;
}

int AA_5DH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//5D|	1|	ANL|	"A,R5"|	-1|	|	|	|	
mout<<"ANL"<<" ";
mout<<"A,R5"<<";";
return 0;
}

int AA_5EH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//5E|	1|	ANL|	"A,R6"|	-1|	|	|	|	
mout<<"ANL"<<" ";
mout<<"A,R6"<<";";
return 0;
}

int AA_5FH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//5F|	1|	ANL|	"A,R7"|	-1|	|	|	|	
mout<<"ANL"<<" ";
mout<<"A,R7"<<";";
return 0;
}

int AA_60H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//60|	2|	JZ|	rel code addr|	1|	(($1)&0xff)|	|	|	
mout<<"JZ"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_REL(val0, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_61H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//61|	2|	AJMP|	abs code addr|	1|	(((($0>>5)<<8)+($1&0xff))&0x7ff)|	|	|	
mout<<"AJMP"<<" ";
unsigned val0=((((mbin[i_byte_offset]>>5)<<8)+(mbin[i_byte_offset+1]&0xff))&0x7ff);
mout<<dis->type_to_str_TOKEN_ADDR11(val0, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_62H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//62|	2|	XRL|	"data addr,A"|	2|	(($1)&0xff)|	|	|	
mout<<"XRL"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val0, curr_addr, 2);
mout<<", "; 
mout<<"A";
mout<<";"; 
return 0;
}

int AA_63H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//63|	3|	XRL|	"data addr,#data"|	2|	(($1)&0xff)|	(($2)&0xff)|	|	
mout<<"XRL"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val0, curr_addr, 3);
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+2])&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 3);
mout<<";"; 
return 0;
}

int AA_64H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//64|	2|	XRL|	"A,#data"|	2|	|	(($1)&0xff)|	|	
mout<<"XRL"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_65H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//65|	2|	XRL|	"A,data addr"|	2|	|	(($1)&0xff)|	|	
mout<<"XRL"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_66H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//66|	1|	XRL|	"A,@R0"|	-1|	|	|	|	
mout<<"XRL"<<" ";
mout<<"A,@R0"<<";";
return 0;
}

int AA_67H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//67|	1|	XRL|	"A,@R1"|	-1|	|	|	|	
mout<<"XRL"<<" ";
mout<<"A,@R1"<<";";
return 0;
}

int AA_68H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//68|	1|	XRL|	"A,R0"|	-1|	|	|	|	
mout<<"XRL"<<" ";
mout<<"A,R0"<<";";
return 0;
}

int AA_69H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//69|	1|	XRL|	"A,R1"|	-1|	|	|	|	
mout<<"XRL"<<" ";
mout<<"A,R1"<<";";
return 0;
}

int AA_6AH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//6A|	1|	XRL|	"A,R2"|	-1|	|	|	|	
mout<<"XRL"<<" ";
mout<<"A,R2"<<";";
return 0;
}

int AA_6BH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//6B|	1|	XRL|	"A,R3"|	-1|	|	|	|	
mout<<"XRL"<<" ";
mout<<"A,R3"<<";";
return 0;
}

int AA_6CH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//6C|	1|	XRL|	"A,R4"|	-1|	|	|	|	
mout<<"XRL"<<" ";
mout<<"A,R4"<<";";
return 0;
}

int AA_6DH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//6D|	1|	XRL|	"A,R5"|	-1|	|	|	|	
mout<<"XRL"<<" ";
mout<<"A,R5"<<";";
return 0;
}

int AA_6EH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//6E|	1|	XRL|	"A,R6"|	-1|	|	|	|	
mout<<"XRL"<<" ";
mout<<"A,R6"<<";";
return 0;
}

int AA_6FH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//6F|	1|	XRL|	"A,R7"|	-1|	|	|	|	
mout<<"XRL"<<" ";
mout<<"A,R7"<<";";
return 0;
}

int AA_70H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//70|	2|	JNZ|	rel code addr|	1|	(($1)&0xff)|	|	|	
mout<<"JNZ"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_REL(val0, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_71H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//71|	2|	ACALL|	abs code addr|	1|	((($1&0xff) + (($0&0xe0)<<3))&0x7ff)|	|	|	
mout<<"ACALL"<<" ";
unsigned val0=(((mbin[i_byte_offset+1]&0xff) + ((mbin[i_byte_offset]&0xe0)<<3))&0x7ff);
mout<<dis->type_to_str_TOKEN_ADDR11(val0, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_72H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//72|	2|	ORL|	"C,bit addr"|	2|	|	(($1)&0xff)|	|	
mout<<"ORL"<<" ";
mout<<"C";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_BIT(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_73H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//73|	1|	JMP|	@A+DPTR|	-1|	|	|	|	
mout<<"JMP"<<" ";
mout<<"@A+DPTR"<<";";
return 0;
}

int AA_74H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//74|	2|	MOV|	"A,#data"|	2|	|	(($1)&0xff)|	|	
mout<<"MOV"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_75H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//75|	3|	MOV|	"data addr,#data"|	2|	(($1)&0xff)|	(($2)&0xff)|	|	
mout<<"MOV"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val0, curr_addr, 3);
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+2])&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 3);
mout<<";"; 
return 0;
}

int AA_76H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//76|	2|	MOV|	"@R0,#data"|	2|	|	(($1)&0xff)|	|	
mout<<"MOV"<<" ";
mout<<"@R0";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_77H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//77|	2|	MOV|	"@R1,#data"|	2|	|	(($1)&0xff)|	|	
mout<<"MOV"<<" ";
mout<<"@R1";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_78H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//78|	2|	MOV|	"R0,#data"|	2|	|	(($1)&0xff)|	|	
mout<<"MOV"<<" ";
mout<<"R0";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_79H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//79|	2|	MOV|	"R1,#data"|	2|	|	(($1)&0xff)|	|	
mout<<"MOV"<<" ";
mout<<"R1";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_7AH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//7A|	2|	MOV|	"R2,#data"|	2|	|	(($1)&0xff)|	|	
mout<<"MOV"<<" ";
mout<<"R2";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_7BH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//7B|	2|	MOV|	"R3,#data"|	2|	|	(($1)&0xff)|	|	
mout<<"MOV"<<" ";
mout<<"R3";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_7CH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//7C|	2|	MOV|	"R4,#data"|	2|	|	(($1)&0xff)|	|	
mout<<"MOV"<<" ";
mout<<"R4";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_7DH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//7D|	2|	MOV|	"R5,#data"|	2|	|	(($1)&0xff)|	|	
mout<<"MOV"<<" ";
mout<<"R5";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_7EH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//7E|	2|	MOV|	"R6,#data"|	2|	|	(($1)&0xff)|	|	
mout<<"MOV"<<" ";
mout<<"R6";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_7FH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//7F|	2|	MOV|	"R7,#data"|	2|	|	(($1)&0xff)|	|	
mout<<"MOV"<<" ";
mout<<"R7";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_80H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//80|	2|	SJMP|	rel code addr|	1|	(($1)&0xff)|	|	|	
mout<<"SJMP"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_REL(val0, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_81H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//81|	2|	AJMP|	abs code addr|	1|	(((($0>>5)<<8)+($1&0xff))&0x7ff)|	|	|	
mout<<"AJMP"<<" ";
unsigned val0=((((mbin[i_byte_offset]>>5)<<8)+(mbin[i_byte_offset+1]&0xff))&0x7ff);
mout<<dis->type_to_str_TOKEN_ADDR11(val0, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_82H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//82|	2|	ANL|	"C,bit addr"|	2|	|	(($1)&0xff)|	|	
mout<<"ANL"<<" ";
mout<<"C";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_BIT(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_83H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//83|	1|	MOVC|	"A,@A+PC"|	-1|	|	|	|	
mout<<"MOVC"<<" ";
mout<<"A,@A+PC"<<";";
return 0;
}

int AA_84H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//84|	1|	DIV|	AB|	-1|	|	|	|	
mout<<"DIV"<<" ";
mout<<"AB"<<";";
return 0;
}

int AA_85H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//85|	3|	MOV|	"data addr,data addr"|	2|	(($2)&0xff)|	(($1)&0xff)|	|	
mout<<"MOV"<<" ";
unsigned val0=((mbin[i_byte_offset+2])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val0, curr_addr, 3);
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val1, curr_addr, 3);
mout<<";"; 
return 0;
}

int AA_86H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//86|	2|	MOV|	"data addr,@R0"|	2|	(($1)&0xff)|	|	|	
mout<<"MOV"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val0, curr_addr, 2);
mout<<", "; 
mout<<"@R0";
mout<<";"; 
return 0;
}

int AA_87H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//87|	2|	MOV|	"data addr,@R1"|	2|	(($1)&0xff)|	|	|	
mout<<"MOV"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val0, curr_addr, 2);
mout<<", "; 
mout<<"@R1";
mout<<";"; 
return 0;
}

int AA_88H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//88|	2|	MOV|	"data addr,R0"|	2|	(($1)&0xff)|	|	|	
mout<<"MOV"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val0, curr_addr, 2);
mout<<", "; 
mout<<"R0";
mout<<";"; 
return 0;
}

int AA_89H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//89|	2|	MOV|	"data addr,R1"|	2|	(($1)&0xff)|	|	|	
mout<<"MOV"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val0, curr_addr, 2);
mout<<", "; 
mout<<"R1";
mout<<";"; 
return 0;
}

int AA_8AH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//8A|	2|	MOV|	"data addr,R2"|	2|	(($1)&0xff)|	|	|	
mout<<"MOV"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val0, curr_addr, 2);
mout<<", "; 
mout<<"R2";
mout<<";"; 
return 0;
}

int AA_8BH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//8B|	2|	MOV|	"data addr,R3"|	2|	(($1)&0xff)|	|	|	
mout<<"MOV"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val0, curr_addr, 2);
mout<<", "; 
mout<<"R3";
mout<<";"; 
return 0;
}

int AA_8CH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//8C|	2|	MOV|	"data addr,R4"|	2|	(($1)&0xff)|	|	|	
mout<<"MOV"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val0, curr_addr, 2);
mout<<", "; 
mout<<"R4";
mout<<";"; 
return 0;
}

int AA_8DH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//8D|	2|	MOV|	"data addr,R5"|	2|	(($1)&0xff)|	|	|	
mout<<"MOV"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val0, curr_addr, 2);
mout<<", "; 
mout<<"R5";
mout<<";"; 
return 0;
}

int AA_8EH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//8E|	2|	MOV|	"data addr,R6"|	2|	(($1)&0xff)|	|	|	
mout<<"MOV"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val0, curr_addr, 2);
mout<<", "; 
mout<<"R6";
mout<<";"; 
return 0;
}

int AA_8FH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//8F|	2|	MOV|	"data addr,R7"|	2|	(($1)&0xff)|	|	|	
mout<<"MOV"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val0, curr_addr, 2);
mout<<", "; 
mout<<"R7";
mout<<";"; 
return 0;
}

int AA_90H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//90|	3|	MOV|	"DPTR,#data"|	2|	|	((($1<<8)+($2&0xff))&0xffff)|	|	
mout<<"MOV"<<" ";
mout<<"DPTR";
mout<<", "; 
unsigned val1=(((mbin[i_byte_offset+1]<<8)+(mbin[i_byte_offset+2]&0xff))&0xffff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 3);
mout<<";"; 
return 0;
}

int AA_91H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//91|	2|	ACALL|	abs code addr|	1|	((($1&0xff) + (($0&0xe0)<<3))&0x7ff)|	|	|	
mout<<"ACALL"<<" ";
unsigned val0=(((mbin[i_byte_offset+1]&0xff) + ((mbin[i_byte_offset]&0xe0)<<3))&0x7ff);
mout<<dis->type_to_str_TOKEN_ADDR11(val0, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_92H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//92|	2|	MOV|	"bit addr,C"|	2|	(($1)&0xff)|	|	|	
mout<<"MOV"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_BIT(val0, curr_addr, 2);
mout<<", "; 
mout<<"C";
mout<<";"; 
return 0;
}

int AA_93H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//93|	1|	MOVC|	"A,@A+DPTR"|	-1|	|	|	|	
mout<<"MOVC"<<" ";
mout<<"A,@A+DPTR"<<";";
return 0;
}

int AA_94H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//94|	2|	SUBB|	"A,#data"|	2|	|	(($1)&0xff)|	|	
mout<<"SUBB"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_95H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//95|	2|	SUBB|	"A,data addr"|	2|	|	(($1)&0xff)|	|	
mout<<"SUBB"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_96H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//96|	1|	SUBB|	"A,@R0"|	-1|	|	|	|	
mout<<"SUBB"<<" ";
mout<<"A,@R0"<<";";
return 0;
}

int AA_97H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//97|	1|	SUBB|	"A,@R1"|	-1|	|	|	|	
mout<<"SUBB"<<" ";
mout<<"A,@R1"<<";";
return 0;
}

int AA_98H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//98|	1|	SUBB|	"A,R0"|	-1|	|	|	|	
mout<<"SUBB"<<" ";
mout<<"A,R0"<<";";
return 0;
}

int AA_99H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//99|	1|	SUBB|	"A,R1"|	-1|	|	|	|	
mout<<"SUBB"<<" ";
mout<<"A,R1"<<";";
return 0;
}

int AA_9AH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//9A|	1|	SUBB|	"A,R2"|	-1|	|	|	|	
mout<<"SUBB"<<" ";
mout<<"A,R2"<<";";
return 0;
}

int AA_9BH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//9B|	1|	SUBB|	"A,R3"|	-1|	|	|	|	
mout<<"SUBB"<<" ";
mout<<"A,R3"<<";";
return 0;
}

int AA_9CH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//9C|	1|	SUBB|	"A,R4"|	-1|	|	|	|	
mout<<"SUBB"<<" ";
mout<<"A,R4"<<";";
return 0;
}

int AA_9DH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//9D|	1|	SUBB|	"A,R5"|	-1|	|	|	|	
mout<<"SUBB"<<" ";
mout<<"A,R5"<<";";
return 0;
}

int AA_9EH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//9E|	1|	SUBB|	"A,R6"|	-1|	|	|	|	
mout<<"SUBB"<<" ";
mout<<"A,R6"<<";";
return 0;
}

int AA_9FH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//9F|	1|	SUBB|	"A,R7"|	-1|	|	|	|	
mout<<"SUBB"<<" ";
mout<<"A,R7"<<";";
return 0;
}

int AA_A0H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//A0|	2|	ORL|	"C,/bit addr"|	2|	|	(($1)&0xff)|	|	
mout<<"ORL"<<" ";
mout<<"C";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_NBIT(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_A1H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//A1|	2|	AJMP|	abs code addr|	1|	(((($0>>5)<<8)+($1&0xff))&0x7ff)|	|	|	
mout<<"AJMP"<<" ";
unsigned val0=((((mbin[i_byte_offset]>>5)<<8)+(mbin[i_byte_offset+1]&0xff))&0x7ff);
mout<<dis->type_to_str_TOKEN_ADDR11(val0, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_A2H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//A2|	2|	MOV|	"C,bit addr"|	2|	|	(($1)&0xff)|	|	
mout<<"MOV"<<" ";
mout<<"C";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_BIT(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_A3H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//A3|	1|	INC|	DPTR|	-1|	|	|	|	
mout<<"INC"<<" ";
mout<<"DPTR"<<";";
return 0;
}

int AA_A4H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//A4|	1|	MUL|	AB|	-1|	|	|	|	
mout<<"MUL"<<" ";
mout<<"AB"<<";";
return 0;
}

int AA_A5H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//A5|	3|	SIMTRAP|	"data addr,data addr"|	2|	(($1)&0xff)|	(($2)&0xff)|	|	
mout<<"SIMTRAP"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val0, curr_addr, 3);
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+2])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val1, curr_addr, 3);
mout<<";"; 
return 0;
}

int AA_A6H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//A6|	2|	MOV|	"@R0,data addr"|	2|	|	(($1)&0xff)|	|	
mout<<"MOV"<<" ";
mout<<"@R0";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_A7H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//A7|	2|	MOV|	"@R1,data addr"|	2|	|	(($1)&0xff)|	|	
mout<<"MOV"<<" ";
mout<<"@R1";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_A8H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//A8|	2|	MOV|	"R0,data addr"|	2|	|	(($1)&0xff)|	|	
mout<<"MOV"<<" ";
mout<<"R0";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_A9H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//A9|	2|	MOV|	"R1,data addr"|	2|	|	(($1)&0xff)|	|	
mout<<"MOV"<<" ";
mout<<"R1";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_AAH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//AA|	2|	MOV|	"R2,data addr"|	2|	|	(($1)&0xff)|	|	
mout<<"MOV"<<" ";
mout<<"R2";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_ABH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//AB|	2|	MOV|	"R3,data addr"|	2|	|	(($1)&0xff)|	|	
mout<<"MOV"<<" ";
mout<<"R3";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_ACH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//AC|	2|	MOV|	"R4,data addr"|	2|	|	(($1)&0xff)|	|	
mout<<"MOV"<<" ";
mout<<"R4";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_ADH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//AD|	2|	MOV|	"R5,data addr"|	2|	|	(($1)&0xff)|	|	
mout<<"MOV"<<" ";
mout<<"R5";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_AEH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//AE|	2|	MOV|	"R6,data addr"|	2|	|	(($1)&0xff)|	|	
mout<<"MOV"<<" ";
mout<<"R6";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_AFH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//AF|	2|	MOV|	"R7,data addr"|	2|	|	(($1)&0xff)|	|	
mout<<"MOV"<<" ";
mout<<"R7";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_B0H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//B0|	2|	ANL|	"C,/bit addr"|	2|	|	(($1)&0xff)|	|	
mout<<"ANL"<<" ";
mout<<"C";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_NBIT(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_B1H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//B1|	2|	ACALL|	abs code addr|	1|	((($1&0xff) + (($0&0xe0)<<3))&0x7ff)|	|	|	
mout<<"ACALL"<<" ";
unsigned val0=(((mbin[i_byte_offset+1]&0xff) + ((mbin[i_byte_offset]&0xe0)<<3))&0x7ff);
mout<<dis->type_to_str_TOKEN_ADDR11(val0, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_B2H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//B2|	2|	CPL|	bit addr|	1|	(($1)&0xff)|	|	|	
mout<<"CPL"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_BIT(val0, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_B3H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//B3|	1|	CPL|	C|	-1|	|	|	|	
mout<<"CPL"<<" ";
mout<<"C"<<";";
return 0;
}

int AA_B4H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//B4|	3|	CJNE|	"A,#data,rel code addr"|	3|	|	(($1)&0xff)|	(($2)&0xff)|	
mout<<"CJNE"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 3);
mout<<", "; 
unsigned val2=((mbin[i_byte_offset+2])&0xff);
mout<<dis->type_to_str_TOKEN_REL(val2, curr_addr, 3);
mout<<";"; 
return 0;
}

int AA_B5H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//B5|	3|	CJNE|	"A,data addr,rel code addr"|	3|	|	(($1)&0xff)|	(($2)&0xff)|	
mout<<"CJNE"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val1, curr_addr, 3);
mout<<", "; 
unsigned val2=((mbin[i_byte_offset+2])&0xff);
mout<<dis->type_to_str_TOKEN_REL(val2, curr_addr, 3);
mout<<";"; 
return 0;
}

int AA_B6H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//B6|	3|	CJNE|	"@R0,#data,rel code addr"|	3|	|	(($1)&0xff)|	(($2)&0xff)|	
mout<<"CJNE"<<" ";
mout<<"@R0";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 3);
mout<<", "; 
unsigned val2=((mbin[i_byte_offset+2])&0xff);
mout<<dis->type_to_str_TOKEN_REL(val2, curr_addr, 3);
mout<<";"; 
return 0;
}

int AA_B7H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//B7|	3|	CJNE|	"@R1,#data,rel code addr"|	3|	|	(($1)&0xff)|	(($2)&0xff)|	
mout<<"CJNE"<<" ";
mout<<"@R1";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 3);
mout<<", "; 
unsigned val2=((mbin[i_byte_offset+2])&0xff);
mout<<dis->type_to_str_TOKEN_REL(val2, curr_addr, 3);
mout<<";"; 
return 0;
}

int AA_B8H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//B8|	3|	CJNE|	"R0,#data,rel code addr"|	3|	|	(($1)&0xff)|	(($2)&0xff)|	
mout<<"CJNE"<<" ";
mout<<"R0";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 3);
mout<<", "; 
unsigned val2=((mbin[i_byte_offset+2])&0xff);
mout<<dis->type_to_str_TOKEN_REL(val2, curr_addr, 3);
mout<<";"; 
return 0;
}

int AA_B9H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//B9|	3|	CJNE|	"R1,#data,rel code addr"|	3|	|	(($1)&0xff)|	(($2)&0xff)|	
mout<<"CJNE"<<" ";
mout<<"R1";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 3);
mout<<", "; 
unsigned val2=((mbin[i_byte_offset+2])&0xff);
mout<<dis->type_to_str_TOKEN_REL(val2, curr_addr, 3);
mout<<";"; 
return 0;
}

int AA_BAH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//BA|	3|	CJNE|	"R2,#data,rel code addr"|	3|	|	(($1)&0xff)|	(($2)&0xff)|	
mout<<"CJNE"<<" ";
mout<<"R2";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 3);
mout<<", "; 
unsigned val2=((mbin[i_byte_offset+2])&0xff);
mout<<dis->type_to_str_TOKEN_REL(val2, curr_addr, 3);
mout<<";"; 
return 0;
}

int AA_BBH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//BB|	3|	CJNE|	"R3,#data,rel code addr"|	3|	|	(($1)&0xff)|	(($2)&0xff)|	
mout<<"CJNE"<<" ";
mout<<"R3";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 3);
mout<<", "; 
unsigned val2=((mbin[i_byte_offset+2])&0xff);
mout<<dis->type_to_str_TOKEN_REL(val2, curr_addr, 3);
mout<<";"; 
return 0;
}

int AA_BCH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//BC|	3|	CJNE|	"R4,#data,rel code addr"|	3|	|	(($1)&0xff)|	(($2)&0xff)|	
mout<<"CJNE"<<" ";
mout<<"R4";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 3);
mout<<", "; 
unsigned val2=((mbin[i_byte_offset+2])&0xff);
mout<<dis->type_to_str_TOKEN_REL(val2, curr_addr, 3);
mout<<";"; 
return 0;
}

int AA_BDH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//BD|	3|	CJNE|	"R5,#data,rel code addr"|	3|	|	(($1)&0xff)|	(($2)&0xff)|	
mout<<"CJNE"<<" ";
mout<<"R5";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 3);
mout<<", "; 
unsigned val2=((mbin[i_byte_offset+2])&0xff);
mout<<dis->type_to_str_TOKEN_REL(val2, curr_addr, 3);
mout<<";"; 
return 0;
}

int AA_BEH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//BE|	3|	CJNE|	"R6,#data,rel code addr"|	3|	|	(($1)&0xff)|	(($2)&0xff)|	
mout<<"CJNE"<<" ";
mout<<"R6";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 3);
mout<<", "; 
unsigned val2=((mbin[i_byte_offset+2])&0xff);
mout<<dis->type_to_str_TOKEN_REL(val2, curr_addr, 3);
mout<<";"; 
return 0;
}

int AA_BFH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//BF|	3|	CJNE|	"R7,#data,rel code addr"|	3|	|	(($1)&0xff)|	(($2)&0xff)|	
mout<<"CJNE"<<" ";
mout<<"R7";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_IMM8(val1, curr_addr, 3);
mout<<", "; 
unsigned val2=((mbin[i_byte_offset+2])&0xff);
mout<<dis->type_to_str_TOKEN_REL(val2, curr_addr, 3);
mout<<";"; 
return 0;
}

int AA_C0H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//C0|	2|	PUSH|	data addr|	1|	(($1)&0xff)|	|	|	
mout<<"PUSH"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val0, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_C1H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//C1|	2|	AJMP|	abs code addr|	1|	(((($0>>5)<<8)+($1&0xff))&0x7ff)|	|	|	
mout<<"AJMP"<<" ";
unsigned val0=((((mbin[i_byte_offset]>>5)<<8)+(mbin[i_byte_offset+1]&0xff))&0x7ff);
mout<<dis->type_to_str_TOKEN_ADDR11(val0, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_C2H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//C2|	2|	CLR|	bit addr|	1|	(($1)&0xff)|	|	|	
mout<<"CLR"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_BIT(val0, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_C3H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//C3|	1|	CLR|	C|	-1|	|	|	|	
mout<<"CLR"<<" ";
mout<<"C"<<";";
return 0;
}

int AA_C4H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//C4|	1|	SWAP|	A|	-1|	|	|	|	
mout<<"SWAP"<<" ";
mout<<"A"<<";";
return 0;
}

int AA_C5H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//C5|	2|	XCH|	"A,data addr"|	2|	|	(($1)&0xff)|	|	
mout<<"XCH"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_C6H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//C6|	1|	XCH|	"A,@R0"|	-1|	|	|	|	
mout<<"XCH"<<" ";
mout<<"A,@R0"<<";";
return 0;
}

int AA_C7H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//C7|	1|	XCH|	"A,@R1"|	-1|	|	|	|	
mout<<"XCH"<<" ";
mout<<"A,@R1"<<";";
return 0;
}

int AA_C8H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//C8|	1|	XCH|	"A,R0"|	-1|	|	|	|	
mout<<"XCH"<<" ";
mout<<"A,R0"<<";";
return 0;
}

int AA_C9H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//C9|	1|	XCH|	"A,R1"|	-1|	|	|	|	
mout<<"XCH"<<" ";
mout<<"A,R1"<<";";
return 0;
}

int AA_CAH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//CA|	1|	XCH|	"A,R2"|	-1|	|	|	|	
mout<<"XCH"<<" ";
mout<<"A,R2"<<";";
return 0;
}

int AA_CBH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//CB|	1|	XCH|	"A,R3"|	-1|	|	|	|	
mout<<"XCH"<<" ";
mout<<"A,R3"<<";";
return 0;
}

int AA_CCH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//CC|	1|	XCH|	"A,R4"|	-1|	|	|	|	
mout<<"XCH"<<" ";
mout<<"A,R4"<<";";
return 0;
}

int AA_CDH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//CD|	1|	XCH|	"A,R5"|	-1|	|	|	|	
mout<<"XCH"<<" ";
mout<<"A,R5"<<";";
return 0;
}

int AA_CEH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//CE|	1|	XCH|	"A,R6"|	-1|	|	|	|	
mout<<"XCH"<<" ";
mout<<"A,R6"<<";";
return 0;
}

int AA_CFH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//CF|	1|	XCH|	"A,R7"|	-1|	|	|	|	
mout<<"XCH"<<" ";
mout<<"A,R7"<<";";
return 0;
}

int AA_D0H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//D0|	2|	POP|	data addr|	1|	(($1)&0xff)|	|	|	
mout<<"POP"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val0, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_D1H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//D1|	2|	ACALL|	abs code addr|	1|	((($1&0xff) + (($0&0xe0)<<3))&0x7ff)|	|	|	
mout<<"ACALL"<<" ";
unsigned val0=(((mbin[i_byte_offset+1]&0xff) + ((mbin[i_byte_offset]&0xe0)<<3))&0x7ff);
mout<<dis->type_to_str_TOKEN_ADDR11(val0, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_D2H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//D2|	2|	SETB|	bit addr|	1|	(($1)&0xff)|	|	|	
mout<<"SETB"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_BIT(val0, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_D3H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//D3|	1|	SETB|	C|	-1|	|	|	|	
mout<<"SETB"<<" ";
mout<<"C"<<";";
return 0;
}

int AA_D4H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//D4|	1|	DA|	A|	-1|	|	|	|	
mout<<"DA"<<" ";
mout<<"A"<<";";
return 0;
}

int AA_D5H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//D5|	3|	DJNZ|	"data addr,rel code addr"|	2|	(($1)&0xff)|	(($2)&0xff)|	|	
mout<<"DJNZ"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val0, curr_addr, 3);
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+2])&0xff);
mout<<dis->type_to_str_TOKEN_REL(val1, curr_addr, 3);
mout<<";"; 
return 0;
}

int AA_D6H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//D6|	1|	XCHD|	"A,@R0"|	-1|	|	|	|	
mout<<"XCHD"<<" ";
mout<<"A,@R0"<<";";
return 0;
}

int AA_D7H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//D7|	1|	XCHD|	"A,@R1"|	-1|	|	|	|	
mout<<"XCHD"<<" ";
mout<<"A,@R1"<<";";
return 0;
}

int AA_D8H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//D8|	2|	DJNZ|	"R0,rel code addr"|	2|	|	(($1)&0xff)|	|	
mout<<"DJNZ"<<" ";
mout<<"R0";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_REL(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_D9H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//D9|	2|	DJNZ|	"R1,rel code addr"|	2|	|	(($1)&0xff)|	|	
mout<<"DJNZ"<<" ";
mout<<"R1";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_REL(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_DAH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//DA|	2|	DJNZ|	"R2,rel code addr"|	2|	|	(($1)&0xff)|	|	
mout<<"DJNZ"<<" ";
mout<<"R2";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_REL(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_DBH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//DB|	2|	DJNZ|	"R3,rel code addr"|	2|	|	(($1)&0xff)|	|	
mout<<"DJNZ"<<" ";
mout<<"R3";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_REL(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_DCH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//DC|	2|	DJNZ|	"R4,rel code addr"|	2|	|	(($1)&0xff)|	|	
mout<<"DJNZ"<<" ";
mout<<"R4";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_REL(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_DDH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//DD|	2|	DJNZ|	"R5,rel code addr"|	2|	|	(($1)&0xff)|	|	
mout<<"DJNZ"<<" ";
mout<<"R5";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_REL(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_DEH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//DE|	2|	DJNZ|	"R6,rel code addr"|	2|	|	(($1)&0xff)|	|	
mout<<"DJNZ"<<" ";
mout<<"R6";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_REL(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_DFH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//DF|	2|	DJNZ|	"R7,rel code addr"|	2|	|	(($1)&0xff)|	|	
mout<<"DJNZ"<<" ";
mout<<"R7";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_REL(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_E0H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//E0|	1|	MOVX|	"A,@DPTR"|	-1|	|	|	|	
mout<<"MOVX"<<" ";
mout<<"A,@DPTR"<<";";
return 0;
}

int AA_E1H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//E1|	2|	AJMP|	abs code addr|	1|	(((($0>>5)<<8)+($1&0xff))&0x7ff)|	|	|	
mout<<"AJMP"<<" ";
unsigned val0=((((mbin[i_byte_offset]>>5)<<8)+(mbin[i_byte_offset+1]&0xff))&0x7ff);
mout<<dis->type_to_str_TOKEN_ADDR11(val0, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_E2H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//E2|	1|	MOVX|	"A,@R0"|	-1|	|	|	|	
mout<<"MOVX"<<" ";
mout<<"A,@R0"<<";";
return 0;
}

int AA_E3H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//E3|	1|	MOVX|	"A,@R1"|	-1|	|	|	|	
mout<<"MOVX"<<" ";
mout<<"A,@R1"<<";";
return 0;
}

int AA_E4H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//E4|	1|	CLR|	A|	-1|	|	|	|	
mout<<"CLR"<<" ";
mout<<"A"<<";";
return 0;
}

int AA_E5H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//E5|	2|	MOV|	"A,data addr"|	2|	|	(($1)&0xff)|	|	
mout<<"MOV"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val1, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_E6H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//E6|	1|	MOV|	"A,@R0"|	-1|	|	|	|	
mout<<"MOV"<<" ";
mout<<"A,@R0"<<";";
return 0;
}

int AA_E7H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//E7|	1|	MOV|	"A,@R1"|	-1|	|	|	|	
mout<<"MOV"<<" ";
mout<<"A,@R1"<<";";
return 0;
}

int AA_E8H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//E8|	1|	MOV|	"A,R0"|	-1|	|	|	|	
mout<<"MOV"<<" ";
mout<<"A,R0"<<";";
return 0;
}

int AA_E9H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//E9|	1|	MOV|	"A,R1"|	-1|	|	|	|	
mout<<"MOV"<<" ";
mout<<"A,R1"<<";";
return 0;
}

int AA_EAH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//EA|	1|	MOV|	"A,R2"|	-1|	|	|	|	
mout<<"MOV"<<" ";
mout<<"A,R2"<<";";
return 0;
}

int AA_EBH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//EB|	1|	MOV|	"A,R3"|	-1|	|	|	|	
mout<<"MOV"<<" ";
mout<<"A,R3"<<";";
return 0;
}

int AA_ECH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//EC|	1|	MOV|	"A,R4"|	-1|	|	|	|	
mout<<"MOV"<<" ";
mout<<"A,R4"<<";";
return 0;
}

int AA_EDH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//ED|	1|	MOV|	"A,R5"|	-1|	|	|	|	
mout<<"MOV"<<" ";
mout<<"A,R5"<<";";
return 0;
}

int AA_EEH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//EE|	1|	MOV|	"A,R6"|	-1|	|	|	|	
mout<<"MOV"<<" ";
mout<<"A,R6"<<";";
return 0;
}

int AA_EFH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//EF|	1|	MOV|	"A,R7"|	-1|	|	|	|	
mout<<"MOV"<<" ";
mout<<"A,R7"<<";";
return 0;
}

int AA_F0H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//F0|	1|	MOVX|	"@DPTR,A"|	-1|	|	|	|	
mout<<"MOVX"<<" ";
mout<<"@DPTR,A"<<";";
return 0;
}

int AA_F1H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//F1|	2|	ACALL|	abs code addr|	1|	((($1&0xff) + (($0&0xe0)<<3))&0x7ff)|	|	|	
mout<<"ACALL"<<" ";
unsigned val0=(((mbin[i_byte_offset+1]&0xff) + ((mbin[i_byte_offset]&0xe0)<<3))&0x7ff);
mout<<dis->type_to_str_TOKEN_ADDR11(val0, curr_addr, 2);
mout<<";"; 
return 0;
}

int AA_F2H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//F2|	1|	MOVX|	"@R0,A"|	-1|	|	|	|	
mout<<"MOVX"<<" ";
mout<<"@R0,A"<<";";
return 0;
}

int AA_F3H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//F3|	1|	MOVX|	"@R1,A"|	-1|	|	|	|	
mout<<"MOVX"<<" ";
mout<<"@R1,A"<<";";
return 0;
}

int AA_F4H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//F4|	1|	CPL|	A|	-1|	|	|	|	
mout<<"CPL"<<" ";
mout<<"A"<<";";
return 0;
}

int AA_F5H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//F5|	2|	MOV|	"data addr,A"|	2|	(($1)&0xff)|	|	|	
mout<<"MOV"<<" ";
unsigned val0=((mbin[i_byte_offset+1])&0xff);
mout<<dis->type_to_str_TOKEN_DIRECT(val0, curr_addr, 2);
mout<<", "; 
mout<<"A";
mout<<";"; 
return 0;
}

int AA_F6H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//F6|	1|	MOV|	"@R0,A"|	-1|	|	|	|	
mout<<"MOV"<<" ";
mout<<"@R0,A"<<";";
return 0;
}

int AA_F7H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//F7|	1|	MOV|	"@R1,A"|	-1|	|	|	|	
mout<<"MOV"<<" ";
mout<<"@R1,A"<<";";
return 0;
}

int AA_F8H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//F8|	1|	MOV|	"R0,A"|	-1|	|	|	|	
mout<<"MOV"<<" ";
mout<<"R0,A"<<";";
return 0;
}

int AA_F9H(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//F9|	1|	MOV|	"R1,A"|	-1|	|	|	|	
mout<<"MOV"<<" ";
mout<<"R1,A"<<";";
return 0;
}

int AA_FAH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//FA|	1|	MOV|	"R2,A"|	-1|	|	|	|	
mout<<"MOV"<<" ";
mout<<"R2,A"<<";";
return 0;
}

int AA_FBH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//FB|	1|	MOV|	"R3,A"|	-1|	|	|	|	
mout<<"MOV"<<" ";
mout<<"R3,A"<<";";
return 0;
}

int AA_FCH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//FC|	1|	MOV|	"R4,A"|	-1|	|	|	|	
mout<<"MOV"<<" ";
mout<<"R4,A"<<";";
return 0;
}

int AA_FDH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//FD|	1|	MOV|	"R5,A"|	-1|	|	|	|	
mout<<"MOV"<<" ";
mout<<"R5,A"<<";";
return 0;
}

int AA_FEH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//FE|	1|	MOV|	"R6,A"|	-1|	|	|	|	
mout<<"MOV"<<" ";
mout<<"R6,A"<<";";
return 0;
}

int AA_FFH(to_asm* dis, const std::string &mbin, int i_byte_offset, unsigned curr_addr, std::ostream &mout)
{
//FF|	1|	MOV|	"R7,A"|	-1|	|	|	|	
mout<<"MOV"<<" ";
mout<<"R7,A"<<";";
return 0;
}

int load_dis_funcs(std::map<unsigned, DIS_FUNC_PTR> &keys)
{
keys[0x0]=AA_0H;
keys[0x1]=AA_1H;
keys[0x2]=AA_2H;
keys[0x3]=AA_3H;
keys[0x4]=AA_4H;
keys[0x5]=AA_5H;
keys[0x6]=AA_6H;
keys[0x7]=AA_7H;
keys[0x8]=AA_8H;
keys[0x9]=AA_9H;
keys[0x0A]=AA_0AH;
keys[0x0B]=AA_0BH;
keys[0x0C]=AA_0CH;
keys[0x0D]=AA_0DH;
keys[0x0E]=AA_0EH;
keys[0x0F]=AA_0FH;
keys[0x10]=AA_10H;
keys[0x11]=AA_11H;
keys[0x12]=AA_12H;
keys[0x13]=AA_13H;
keys[0x14]=AA_14H;
keys[0x15]=AA_15H;
keys[0x16]=AA_16H;
keys[0x17]=AA_17H;
keys[0x18]=AA_18H;
keys[0x19]=AA_19H;
keys[0x1A]=AA_1AH;
keys[0x1B]=AA_1BH;
keys[0x1C]=AA_1CH;
keys[0x1D]=AA_1DH;
keys[0x1E]=AA_1EH;
keys[0x1F]=AA_1FH;
keys[0x20]=AA_20H;
keys[0x21]=AA_21H;
keys[0x22]=AA_22H;
keys[0x23]=AA_23H;
keys[0x24]=AA_24H;
keys[0x25]=AA_25H;
keys[0x26]=AA_26H;
keys[0x27]=AA_27H;
keys[0x28]=AA_28H;
keys[0x29]=AA_29H;
keys[0x2A]=AA_2AH;
keys[0x2B]=AA_2BH;
keys[0x2C]=AA_2CH;
keys[0x2D]=AA_2DH;
keys[0x2E]=AA_2EH;
keys[0x2F]=AA_2FH;
keys[0x30]=AA_30H;
keys[0x31]=AA_31H;
keys[0x32]=AA_32H;
keys[0x33]=AA_33H;
keys[0x34]=AA_34H;
keys[0x35]=AA_35H;
keys[0x36]=AA_36H;
keys[0x37]=AA_37H;
keys[0x38]=AA_38H;
keys[0x39]=AA_39H;
keys[0x3A]=AA_3AH;
keys[0x3B]=AA_3BH;
keys[0x3C]=AA_3CH;
keys[0x3D]=AA_3DH;
keys[0x3E]=AA_3EH;
keys[0x3F]=AA_3FH;
keys[0x40]=AA_40H;
keys[0x41]=AA_41H;
keys[0x42]=AA_42H;
keys[0x43]=AA_43H;
keys[0x44]=AA_44H;
keys[0x45]=AA_45H;
keys[0x46]=AA_46H;
keys[0x47]=AA_47H;
keys[0x48]=AA_48H;
keys[0x49]=AA_49H;
keys[0x4A]=AA_4AH;
keys[0x4B]=AA_4BH;
keys[0x4C]=AA_4CH;
keys[0x4D]=AA_4DH;
keys[0x4E]=AA_4EH;
keys[0x4F]=AA_4FH;
keys[0x50]=AA_50H;
keys[0x51]=AA_51H;
keys[0x52]=AA_52H;
keys[0x53]=AA_53H;
keys[0x54]=AA_54H;
keys[0x55]=AA_55H;
keys[0x56]=AA_56H;
keys[0x57]=AA_57H;
keys[0x58]=AA_58H;
keys[0x59]=AA_59H;
keys[0x5A]=AA_5AH;
keys[0x5B]=AA_5BH;
keys[0x5C]=AA_5CH;
keys[0x5D]=AA_5DH;
keys[0x5E]=AA_5EH;
keys[0x5F]=AA_5FH;
keys[0x60]=AA_60H;
keys[0x61]=AA_61H;
keys[0x62]=AA_62H;
keys[0x63]=AA_63H;
keys[0x64]=AA_64H;
keys[0x65]=AA_65H;
keys[0x66]=AA_66H;
keys[0x67]=AA_67H;
keys[0x68]=AA_68H;
keys[0x69]=AA_69H;
keys[0x6A]=AA_6AH;
keys[0x6B]=AA_6BH;
keys[0x6C]=AA_6CH;
keys[0x6D]=AA_6DH;
keys[0x6E]=AA_6EH;
keys[0x6F]=AA_6FH;
keys[0x70]=AA_70H;
keys[0x71]=AA_71H;
keys[0x72]=AA_72H;
keys[0x73]=AA_73H;
keys[0x74]=AA_74H;
keys[0x75]=AA_75H;
keys[0x76]=AA_76H;
keys[0x77]=AA_77H;
keys[0x78]=AA_78H;
keys[0x79]=AA_79H;
keys[0x7A]=AA_7AH;
keys[0x7B]=AA_7BH;
keys[0x7C]=AA_7CH;
keys[0x7D]=AA_7DH;
keys[0x7E]=AA_7EH;
keys[0x7F]=AA_7FH;
keys[0x80]=AA_80H;
keys[0x81]=AA_81H;
keys[0x82]=AA_82H;
keys[0x83]=AA_83H;
keys[0x84]=AA_84H;
keys[0x85]=AA_85H;
keys[0x86]=AA_86H;
keys[0x87]=AA_87H;
keys[0x88]=AA_88H;
keys[0x89]=AA_89H;
keys[0x8A]=AA_8AH;
keys[0x8B]=AA_8BH;
keys[0x8C]=AA_8CH;
keys[0x8D]=AA_8DH;
keys[0x8E]=AA_8EH;
keys[0x8F]=AA_8FH;
keys[0x90]=AA_90H;
keys[0x91]=AA_91H;
keys[0x92]=AA_92H;
keys[0x93]=AA_93H;
keys[0x94]=AA_94H;
keys[0x95]=AA_95H;
keys[0x96]=AA_96H;
keys[0x97]=AA_97H;
keys[0x98]=AA_98H;
keys[0x99]=AA_99H;
keys[0x9A]=AA_9AH;
keys[0x9B]=AA_9BH;
keys[0x9C]=AA_9CH;
keys[0x9D]=AA_9DH;
keys[0x9E]=AA_9EH;
keys[0x9F]=AA_9FH;
keys[0xA0]=AA_A0H;
keys[0xA1]=AA_A1H;
keys[0xA2]=AA_A2H;
keys[0xA3]=AA_A3H;
keys[0xA4]=AA_A4H;
keys[0xA5]=AA_A5H;
keys[0xA6]=AA_A6H;
keys[0xA7]=AA_A7H;
keys[0xA8]=AA_A8H;
keys[0xA9]=AA_A9H;
keys[0xAA]=AA_AAH;
keys[0xAB]=AA_ABH;
keys[0xAC]=AA_ACH;
keys[0xAD]=AA_ADH;
keys[0xAE]=AA_AEH;
keys[0xAF]=AA_AFH;
keys[0xB0]=AA_B0H;
keys[0xB1]=AA_B1H;
keys[0xB2]=AA_B2H;
keys[0xB3]=AA_B3H;
keys[0xB4]=AA_B4H;
keys[0xB5]=AA_B5H;
keys[0xB6]=AA_B6H;
keys[0xB7]=AA_B7H;
keys[0xB8]=AA_B8H;
keys[0xB9]=AA_B9H;
keys[0xBA]=AA_BAH;
keys[0xBB]=AA_BBH;
keys[0xBC]=AA_BCH;
keys[0xBD]=AA_BDH;
keys[0xBE]=AA_BEH;
keys[0xBF]=AA_BFH;
keys[0xC0]=AA_C0H;
keys[0xC1]=AA_C1H;
keys[0xC2]=AA_C2H;
keys[0xC3]=AA_C3H;
keys[0xC4]=AA_C4H;
keys[0xC5]=AA_C5H;
keys[0xC6]=AA_C6H;
keys[0xC7]=AA_C7H;
keys[0xC8]=AA_C8H;
keys[0xC9]=AA_C9H;
keys[0xCA]=AA_CAH;
keys[0xCB]=AA_CBH;
keys[0xCC]=AA_CCH;
keys[0xCD]=AA_CDH;
keys[0xCE]=AA_CEH;
keys[0xCF]=AA_CFH;
keys[0xD0]=AA_D0H;
keys[0xD1]=AA_D1H;
keys[0xD2]=AA_D2H;
keys[0xD3]=AA_D3H;
keys[0xD4]=AA_D4H;
keys[0xD5]=AA_D5H;
keys[0xD6]=AA_D6H;
keys[0xD7]=AA_D7H;
keys[0xD8]=AA_D8H;
keys[0xD9]=AA_D9H;
keys[0xDA]=AA_DAH;
keys[0xDB]=AA_DBH;
keys[0xDC]=AA_DCH;
keys[0xDD]=AA_DDH;
keys[0xDE]=AA_DEH;
keys[0xDF]=AA_DFH;
keys[0xE0]=AA_E0H;
keys[0xE1]=AA_E1H;
keys[0xE2]=AA_E2H;
keys[0xE3]=AA_E3H;
keys[0xE4]=AA_E4H;
keys[0xE5]=AA_E5H;
keys[0xE6]=AA_E6H;
keys[0xE7]=AA_E7H;
keys[0xE8]=AA_E8H;
keys[0xE9]=AA_E9H;
keys[0xEA]=AA_EAH;
keys[0xEB]=AA_EBH;
keys[0xEC]=AA_ECH;
keys[0xED]=AA_EDH;
keys[0xEE]=AA_EEH;
keys[0xEF]=AA_EFH;
keys[0xF0]=AA_F0H;
keys[0xF1]=AA_F1H;
keys[0xF2]=AA_F2H;
keys[0xF3]=AA_F3H;
keys[0xF4]=AA_F4H;
keys[0xF5]=AA_F5H;
keys[0xF6]=AA_F6H;
keys[0xF7]=AA_F7H;
keys[0xF8]=AA_F8H;
keys[0xF9]=AA_F9H;
keys[0xFA]=AA_FAH;
keys[0xFB]=AA_FBH;
keys[0xFC]=AA_FCH;
keys[0xFD]=AA_FDH;
keys[0xFE]=AA_FEH;
keys[0xFF]=AA_FFH;
return 0;
}
int get_inst_byte_len(unsigned first_byte)
{
switch(first_byte)
{
case 0x0:return 1;
case 0x1:return 2;
case 0x2:return 3;
case 0x3:return 1;
case 0x4:return 1;
case 0x5:return 2;
case 0x6:return 1;
case 0x7:return 1;
case 0x8:return 1;
case 0x9:return 1;
case 0x0A:return 1;
case 0x0B:return 1;
case 0x0C:return 1;
case 0x0D:return 1;
case 0x0E:return 1;
case 0x0F:return 1;
case 0x10:return 3;
case 0x11:return 2;
case 0x12:return 3;
case 0x13:return 1;
case 0x14:return 1;
case 0x15:return 2;
case 0x16:return 1;
case 0x17:return 1;
case 0x18:return 1;
case 0x19:return 1;
case 0x1A:return 1;
case 0x1B:return 1;
case 0x1C:return 1;
case 0x1D:return 1;
case 0x1E:return 1;
case 0x1F:return 1;
case 0x20:return 3;
case 0x21:return 2;
case 0x22:return 1;
case 0x23:return 1;
case 0x24:return 2;
case 0x25:return 2;
case 0x26:return 1;
case 0x27:return 1;
case 0x28:return 1;
case 0x29:return 1;
case 0x2A:return 1;
case 0x2B:return 1;
case 0x2C:return 1;
case 0x2D:return 1;
case 0x2E:return 1;
case 0x2F:return 1;
case 0x30:return 3;
case 0x31:return 2;
case 0x32:return 1;
case 0x33:return 1;
case 0x34:return 2;
case 0x35:return 2;
case 0x36:return 1;
case 0x37:return 1;
case 0x38:return 1;
case 0x39:return 1;
case 0x3A:return 1;
case 0x3B:return 1;
case 0x3C:return 1;
case 0x3D:return 1;
case 0x3E:return 1;
case 0x3F:return 1;
case 0x40:return 2;
case 0x41:return 2;
case 0x42:return 2;
case 0x43:return 3;
case 0x44:return 2;
case 0x45:return 2;
case 0x46:return 1;
case 0x47:return 1;
case 0x48:return 1;
case 0x49:return 1;
case 0x4A:return 1;
case 0x4B:return 1;
case 0x4C:return 1;
case 0x4D:return 1;
case 0x4E:return 1;
case 0x4F:return 1;
case 0x50:return 2;
case 0x51:return 2;
case 0x52:return 2;
case 0x53:return 3;
case 0x54:return 2;
case 0x55:return 2;
case 0x56:return 1;
case 0x57:return 1;
case 0x58:return 1;
case 0x59:return 1;
case 0x5A:return 1;
case 0x5B:return 1;
case 0x5C:return 1;
case 0x5D:return 1;
case 0x5E:return 1;
case 0x5F:return 1;
case 0x60:return 2;
case 0x61:return 2;
case 0x62:return 2;
case 0x63:return 3;
case 0x64:return 2;
case 0x65:return 2;
case 0x66:return 1;
case 0x67:return 1;
case 0x68:return 1;
case 0x69:return 1;
case 0x6A:return 1;
case 0x6B:return 1;
case 0x6C:return 1;
case 0x6D:return 1;
case 0x6E:return 1;
case 0x6F:return 1;
case 0x70:return 2;
case 0x71:return 2;
case 0x72:return 2;
case 0x73:return 1;
case 0x74:return 2;
case 0x75:return 3;
case 0x76:return 2;
case 0x77:return 2;
case 0x78:return 2;
case 0x79:return 2;
case 0x7A:return 2;
case 0x7B:return 2;
case 0x7C:return 2;
case 0x7D:return 2;
case 0x7E:return 2;
case 0x7F:return 2;
case 0x80:return 2;
case 0x81:return 2;
case 0x82:return 2;
case 0x83:return 1;
case 0x84:return 1;
case 0x85:return 3;
case 0x86:return 2;
case 0x87:return 2;
case 0x88:return 2;
case 0x89:return 2;
case 0x8A:return 2;
case 0x8B:return 2;
case 0x8C:return 2;
case 0x8D:return 2;
case 0x8E:return 2;
case 0x8F:return 2;
case 0x90:return 3;
case 0x91:return 2;
case 0x92:return 2;
case 0x93:return 1;
case 0x94:return 2;
case 0x95:return 2;
case 0x96:return 1;
case 0x97:return 1;
case 0x98:return 1;
case 0x99:return 1;
case 0x9A:return 1;
case 0x9B:return 1;
case 0x9C:return 1;
case 0x9D:return 1;
case 0x9E:return 1;
case 0x9F:return 1;
case 0xA0:return 2;
case 0xA1:return 2;
case 0xA2:return 2;
case 0xA3:return 1;
case 0xA4:return 1;
case 0xA5:return 3;
case 0xA6:return 2;
case 0xA7:return 2;
case 0xA8:return 2;
case 0xA9:return 2;
case 0xAA:return 2;
case 0xAB:return 2;
case 0xAC:return 2;
case 0xAD:return 2;
case 0xAE:return 2;
case 0xAF:return 2;
case 0xB0:return 2;
case 0xB1:return 2;
case 0xB2:return 2;
case 0xB3:return 1;
case 0xB4:return 3;
case 0xB5:return 3;
case 0xB6:return 3;
case 0xB7:return 3;
case 0xB8:return 3;
case 0xB9:return 3;
case 0xBA:return 3;
case 0xBB:return 3;
case 0xBC:return 3;
case 0xBD:return 3;
case 0xBE:return 3;
case 0xBF:return 3;
case 0xC0:return 2;
case 0xC1:return 2;
case 0xC2:return 2;
case 0xC3:return 1;
case 0xC4:return 1;
case 0xC5:return 2;
case 0xC6:return 1;
case 0xC7:return 1;
case 0xC8:return 1;
case 0xC9:return 1;
case 0xCA:return 1;
case 0xCB:return 1;
case 0xCC:return 1;
case 0xCD:return 1;
case 0xCE:return 1;
case 0xCF:return 1;
case 0xD0:return 2;
case 0xD1:return 2;
case 0xD2:return 2;
case 0xD3:return 1;
case 0xD4:return 1;
case 0xD5:return 3;
case 0xD6:return 1;
case 0xD7:return 1;
case 0xD8:return 2;
case 0xD9:return 2;
case 0xDA:return 2;
case 0xDB:return 2;
case 0xDC:return 2;
case 0xDD:return 2;
case 0xDE:return 2;
case 0xDF:return 2;
case 0xE0:return 1;
case 0xE1:return 2;
case 0xE2:return 1;
case 0xE3:return 1;
case 0xE4:return 1;
case 0xE5:return 2;
case 0xE6:return 1;
case 0xE7:return 1;
case 0xE8:return 1;
case 0xE9:return 1;
case 0xEA:return 1;
case 0xEB:return 1;
case 0xEC:return 1;
case 0xED:return 1;
case 0xEE:return 1;
case 0xEF:return 1;
case 0xF0:return 1;
case 0xF1:return 2;
case 0xF2:return 1;
case 0xF3:return 1;
case 0xF4:return 1;
case 0xF5:return 2;
case 0xF6:return 1;
case 0xF7:return 1;
case 0xF8:return 1;
case 0xF9:return 1;
case 0xFA:return 1;
case 0xFB:return 1;
case 0xFC:return 1;
case 0xFD:return 1;
case 0xFE:return 1;
case 0xFF:return 1;
}
return 0;
}
}//namespace end
