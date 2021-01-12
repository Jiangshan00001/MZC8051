#include "dis_keywords.h"
#include <string>
#include <sstream>
#include "dis8051.h"
std::string AA_0H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//0|	1|	NOP|	|	-1|	|	|	|	
std::stringstream mout;
mout<<"NOP"<<" ";
mout<<""<<";";
return mout.str();
}
std::string AA_1H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//1|	2|	AJMP|	abs code addr|	1|	(((($0>>5)<<8)+($1&0xff))&0x7ff)|	|	|	
std::stringstream mout;
mout<<"AJMP"<<" ";
unsigned val0=((((mbin[0]>>5)<<8)+(mbin[1]&0xff))&0x7ff);
mout<<dis->ABS_CODE_ADDR_DIS(val0, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_2H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//2|	3|	LJMP|	abs code addr|	1|	((($1<<8) + ($2&0xff))&0xffff)|	|	|	
std::stringstream mout;
mout<<"LJMP"<<" ";
unsigned val0=(((mbin[1]<<8) + (mbin[2]&0xff))&0xffff);
mout<<dis->ABS_CODE_ADDR_DIS(val0, curr_addr, 3);
mout<<";"; 
return mout.str();
}
std::string AA_3H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//3|	1|	RR|	A|	-1|	|	|	|	
std::stringstream mout;
mout<<"RR"<<" ";
mout<<"A"<<";";
return mout.str();
}
std::string AA_4H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//4|	1|	INC|	A|	-1|	|	|	|	
std::stringstream mout;
mout<<"INC"<<" ";
mout<<"A"<<";";
return mout.str();
}
std::string AA_5H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//5|	2|	INC|	data addr|	1|	(($1)&0xff)|	|	|	
std::stringstream mout;
mout<<"INC"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val0, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_6H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//6|	1|	INC|	@R0|	-1|	|	|	|	
std::stringstream mout;
mout<<"INC"<<" ";
mout<<"@R0"<<";";
return mout.str();
}
std::string AA_7H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//7|	1|	INC|	@R1|	-1|	|	|	|	
std::stringstream mout;
mout<<"INC"<<" ";
mout<<"@R1"<<";";
return mout.str();
}
std::string AA_8H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//8|	1|	INC|	R0|	-1|	|	|	|	
std::stringstream mout;
mout<<"INC"<<" ";
mout<<"R0"<<";";
return mout.str();
}
std::string AA_9H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//9|	1|	INC|	R1|	-1|	|	|	|	
std::stringstream mout;
mout<<"INC"<<" ";
mout<<"R1"<<";";
return mout.str();
}
std::string AA_0AH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//0A|	1|	INC|	R2|	-1|	|	|	|	
std::stringstream mout;
mout<<"INC"<<" ";
mout<<"R2"<<";";
return mout.str();
}
std::string AA_0BH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//0B|	1|	INC|	R3|	-1|	|	|	|	
std::stringstream mout;
mout<<"INC"<<" ";
mout<<"R3"<<";";
return mout.str();
}
std::string AA_0CH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//0C|	1|	INC|	R4|	-1|	|	|	|	
std::stringstream mout;
mout<<"INC"<<" ";
mout<<"R4"<<";";
return mout.str();
}
std::string AA_0DH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//0D|	1|	INC|	R5|	-1|	|	|	|	
std::stringstream mout;
mout<<"INC"<<" ";
mout<<"R5"<<";";
return mout.str();
}
std::string AA_0EH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//0E|	1|	INC|	R6|	-1|	|	|	|	
std::stringstream mout;
mout<<"INC"<<" ";
mout<<"R6"<<";";
return mout.str();
}
std::string AA_0FH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//0F|	1|	INC|	R7|	-1|	|	|	|	
std::stringstream mout;
mout<<"INC"<<" ";
mout<<"R7"<<";";
return mout.str();
}
std::string AA_10H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//10|	3|	JBC|	"bit addr,rel code addr"|	2|	(($1)&0xff)|	(($2)&0xff)|	|	
std::stringstream mout;
mout<<"JBC"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->BIT_ADDR_DIS(val0, curr_addr, 3);
mout<<", "; 
unsigned val1=((mbin[2])&0xff);
mout<<dis->REL_CODE_ADDR_DIS(val1, curr_addr, 3);
mout<<";"; 
return mout.str();
}
std::string AA_11H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//11|	2|	ACALL|	abs code addr|	1|	((($1&0xff) + (($0&0xe0)<<3))&0x7ff)|	|	|	
std::stringstream mout;
mout<<"ACALL"<<" ";
unsigned val0=(((mbin[1]&0xff) + ((mbin[0]&0xe0)<<3))&0x7ff);
mout<<dis->ABS_CODE_ADDR_DIS(val0, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_12H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//12|	3|	LCALL|	abs code addr|	1|	((($1<<8) + ($2&0xff))&0xffff)|	|	|	
std::stringstream mout;
mout<<"LCALL"<<" ";
unsigned val0=(((mbin[1]<<8) + (mbin[2]&0xff))&0xffff);
mout<<dis->ABS_CODE_ADDR_DIS(val0, curr_addr, 3);
mout<<";"; 
return mout.str();
}
std::string AA_13H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//13|	1|	RRC|	A|	-1|	|	|	|	
std::stringstream mout;
mout<<"RRC"<<" ";
mout<<"A"<<";";
return mout.str();
}
std::string AA_14H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//14|	1|	DEC|	A|	-1|	|	|	|	
std::stringstream mout;
mout<<"DEC"<<" ";
mout<<"A"<<";";
return mout.str();
}
std::string AA_15H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//15|	2|	DEC|	data addr|	1|	(($1)&0xff)|	|	|	
std::stringstream mout;
mout<<"DEC"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val0, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_16H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//16|	1|	DEC|	@R0|	-1|	|	|	|	
std::stringstream mout;
mout<<"DEC"<<" ";
mout<<"@R0"<<";";
return mout.str();
}
std::string AA_17H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//17|	1|	DEC|	@R1|	-1|	|	|	|	
std::stringstream mout;
mout<<"DEC"<<" ";
mout<<"@R1"<<";";
return mout.str();
}
std::string AA_18H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//18|	1|	DEC|	R0|	-1|	|	|	|	
std::stringstream mout;
mout<<"DEC"<<" ";
mout<<"R0"<<";";
return mout.str();
}
std::string AA_19H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//19|	1|	DEC|	R1|	-1|	|	|	|	
std::stringstream mout;
mout<<"DEC"<<" ";
mout<<"R1"<<";";
return mout.str();
}
std::string AA_1AH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//1A|	1|	DEC|	R2|	-1|	|	|	|	
std::stringstream mout;
mout<<"DEC"<<" ";
mout<<"R2"<<";";
return mout.str();
}
std::string AA_1BH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//1B|	1|	DEC|	R3|	-1|	|	|	|	
std::stringstream mout;
mout<<"DEC"<<" ";
mout<<"R3"<<";";
return mout.str();
}
std::string AA_1CH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//1C|	1|	DEC|	R4|	-1|	|	|	|	
std::stringstream mout;
mout<<"DEC"<<" ";
mout<<"R4"<<";";
return mout.str();
}
std::string AA_1DH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//1D|	1|	DEC|	R5|	-1|	|	|	|	
std::stringstream mout;
mout<<"DEC"<<" ";
mout<<"R5"<<";";
return mout.str();
}
std::string AA_1EH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//1E|	1|	DEC|	R6|	-1|	|	|	|	
std::stringstream mout;
mout<<"DEC"<<" ";
mout<<"R6"<<";";
return mout.str();
}
std::string AA_1FH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//1F|	1|	DEC|	R7|	-1|	|	|	|	
std::stringstream mout;
mout<<"DEC"<<" ";
mout<<"R7"<<";";
return mout.str();
}
std::string AA_20H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//20|	3|	JB|	"bit addr,rel code addr"|	2|	(($1+0)&0xff)|	(($2)&0xff)|	|	
std::stringstream mout;
mout<<"JB"<<" ";
unsigned val0=((mbin[1]+0)&0xff);
mout<<dis->BIT_ADDR_DIS(val0, curr_addr, 3);
mout<<", "; 
unsigned val1=((mbin[2])&0xff);
mout<<dis->REL_CODE_ADDR_DIS(val1, curr_addr, 3);
mout<<";"; 
return mout.str();
}
std::string AA_21H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//21|	2|	AJMP|	abs code addr|	1|	(((($0>>5)<<8)+($1&0xff))&0x7ff)|	|	|	
std::stringstream mout;
mout<<"AJMP"<<" ";
unsigned val0=((((mbin[0]>>5)<<8)+(mbin[1]&0xff))&0x7ff);
mout<<dis->ABS_CODE_ADDR_DIS(val0, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_22H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//22|	1|	RET|	|	-1|	|	|	|	
std::stringstream mout;
mout<<"RET"<<" ";
mout<<""<<";";
return mout.str();
}
std::string AA_23H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//23|	1|	RL|	A|	-1|	|	|	|	
std::stringstream mout;
mout<<"RL"<<" ";
mout<<"A"<<";";
return mout.str();
}
std::string AA_24H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//24|	2|	ADD|	"A,#data"|	2|	|	(($1+0)&0xff)|	|	
std::stringstream mout;
mout<<"ADD"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[1]+0)&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_25H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//25|	2|	ADD|	"A,data addr"|	2|	|	(($1+0)&0xff)|	|	
std::stringstream mout;
mout<<"ADD"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[1]+0)&0xff);
mout<<dis->DATA_ADDR_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_26H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//26|	1|	ADD|	"A,@R0"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ADD"<<" ";
mout<<"A,@R0"<<";";
return mout.str();
}
std::string AA_27H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//27|	1|	ADD|	"A,@R1"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ADD"<<" ";
mout<<"A,@R1"<<";";
return mout.str();
}
std::string AA_28H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//28|	1|	ADD|	"A,R0"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ADD"<<" ";
mout<<"A,R0"<<";";
return mout.str();
}
std::string AA_29H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//29|	1|	ADD|	"A,R1"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ADD"<<" ";
mout<<"A,R1"<<";";
return mout.str();
}
std::string AA_2AH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//2A|	1|	ADD|	"A,R2"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ADD"<<" ";
mout<<"A,R2"<<";";
return mout.str();
}
std::string AA_2BH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//2B|	1|	ADD|	"A,R3"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ADD"<<" ";
mout<<"A,R3"<<";";
return mout.str();
}
std::string AA_2CH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//2C|	1|	ADD|	"A,R4"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ADD"<<" ";
mout<<"A,R4"<<";";
return mout.str();
}
std::string AA_2DH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//2D|	1|	ADD|	"A,R5"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ADD"<<" ";
mout<<"A,R5"<<";";
return mout.str();
}
std::string AA_2EH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//2E|	1|	ADD|	"A,R6"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ADD"<<" ";
mout<<"A,R6"<<";";
return mout.str();
}
std::string AA_2FH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//2F|	1|	ADD|	"A,R7"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ADD"<<" ";
mout<<"A,R7"<<";";
return mout.str();
}
std::string AA_30H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//30|	3|	JNB|	"bit addr,rel code addr"|	2|	(($1)&0xff)|	(($2)&0xff)|	|	
std::stringstream mout;
mout<<"JNB"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->BIT_ADDR_DIS(val0, curr_addr, 3);
mout<<", "; 
unsigned val1=((mbin[2])&0xff);
mout<<dis->REL_CODE_ADDR_DIS(val1, curr_addr, 3);
mout<<";"; 
return mout.str();
}
std::string AA_31H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//31|	2|	ACALL|	abs code addr|	1|	((($1&0xff) + (($0&0xe0)<<3))&0x7ff)|	|	|	
std::stringstream mout;
mout<<"ACALL"<<" ";
unsigned val0=(((mbin[1]&0xff) + ((mbin[0]&0xe0)<<3))&0x7ff);
mout<<dis->ABS_CODE_ADDR_DIS(val0, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_32H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//32|	1|	RETI|	|	-1|	|	|	|	
std::stringstream mout;
mout<<"RETI"<<" ";
mout<<""<<";";
return mout.str();
}
std::string AA_33H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//33|	1|	RLC|	A|	-1|	|	|	|	
std::stringstream mout;
mout<<"RLC"<<" ";
mout<<"A"<<";";
return mout.str();
}
std::string AA_34H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//34|	2|	ADDC|	"A,#data"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"ADDC"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_35H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//35|	2|	ADDC|	"A,data addr"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"ADDC"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_36H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//36|	1|	ADDC|	"A,@R0"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ADDC"<<" ";
mout<<"A,@R0"<<";";
return mout.str();
}
std::string AA_37H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//37|	1|	ADDC|	"A,@R1"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ADDC"<<" ";
mout<<"A,@R1"<<";";
return mout.str();
}
std::string AA_38H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//38|	1|	ADDC|	"A,R0"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ADDC"<<" ";
mout<<"A,R0"<<";";
return mout.str();
}
std::string AA_39H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//39|	1|	ADDC|	"A,R1"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ADDC"<<" ";
mout<<"A,R1"<<";";
return mout.str();
}
std::string AA_3AH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//3A|	1|	ADDC|	"A,R2"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ADDC"<<" ";
mout<<"A,R2"<<";";
return mout.str();
}
std::string AA_3BH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//3B|	1|	ADDC|	"A,R3"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ADDC"<<" ";
mout<<"A,R3"<<";";
return mout.str();
}
std::string AA_3CH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//3C|	1|	ADDC|	"A,R4"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ADDC"<<" ";
mout<<"A,R4"<<";";
return mout.str();
}
std::string AA_3DH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//3D|	1|	ADDC|	"A,R5"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ADDC"<<" ";
mout<<"A,R5"<<";";
return mout.str();
}
std::string AA_3EH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//3E|	1|	ADDC|	"A,R6"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ADDC"<<" ";
mout<<"A,R6"<<";";
return mout.str();
}
std::string AA_3FH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//3F|	1|	ADDC|	"A,R7"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ADDC"<<" ";
mout<<"A,R7"<<";";
return mout.str();
}
std::string AA_40H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//40|	2|	JC|	rel code addr|	1|	(($1)&0xff)|	|	|	
std::stringstream mout;
mout<<"JC"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->REL_CODE_ADDR_DIS(val0, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_41H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//41|	2|	AJMP|	abs code addr|	1|	(((($0>>5)<<8)+($1&0xff))&0x7ff)|	|	|	
std::stringstream mout;
mout<<"AJMP"<<" ";
unsigned val0=((((mbin[0]>>5)<<8)+(mbin[1]&0xff))&0x7ff);
mout<<dis->ABS_CODE_ADDR_DIS(val0, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_42H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//42|	2|	ORL|	"data addr,A"|	2|	(($1)&0xff)|	|	|	
std::stringstream mout;
mout<<"ORL"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val0, curr_addr, 2);
mout<<", "; 
mout<<"A";
mout<<";"; 
return mout.str();
}
std::string AA_43H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//43|	3|	ORL|	"data addr,#data"|	2|	(($1)&0xff)|	(($2)&0xff)|	|	
std::stringstream mout;
mout<<"ORL"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val0, curr_addr, 3);
mout<<", "; 
unsigned val1=((mbin[2])&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 3);
mout<<";"; 
return mout.str();
}
std::string AA_44H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//44|	2|	ORL|	"A,#data"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"ORL"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_45H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//45|	2|	ORL|	"A,data addr"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"ORL"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_46H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//46|	1|	ORL|	"A,@R0"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ORL"<<" ";
mout<<"A,@R0"<<";";
return mout.str();
}
std::string AA_47H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//47|	1|	ORL|	"A,@R1"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ORL"<<" ";
mout<<"A,@R1"<<";";
return mout.str();
}
std::string AA_48H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//48|	1|	ORL|	"A,R0"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ORL"<<" ";
mout<<"A,R0"<<";";
return mout.str();
}
std::string AA_49H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//49|	1|	ORL|	"A,R1"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ORL"<<" ";
mout<<"A,R1"<<";";
return mout.str();
}
std::string AA_4AH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//4A|	1|	ORL|	"A,R2"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ORL"<<" ";
mout<<"A,R2"<<";";
return mout.str();
}
std::string AA_4BH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//4B|	1|	ORL|	"A,R3"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ORL"<<" ";
mout<<"A,R3"<<";";
return mout.str();
}
std::string AA_4CH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//4C|	1|	ORL|	"A,R4"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ORL"<<" ";
mout<<"A,R4"<<";";
return mout.str();
}
std::string AA_4DH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//4D|	1|	ORL|	"A,R5"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ORL"<<" ";
mout<<"A,R5"<<";";
return mout.str();
}
std::string AA_4EH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//4E|	1|	ORL|	"A,R6"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ORL"<<" ";
mout<<"A,R6"<<";";
return mout.str();
}
std::string AA_4FH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//4F|	1|	ORL|	"A,R7"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ORL"<<" ";
mout<<"A,R7"<<";";
return mout.str();
}
std::string AA_50H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//50|	2|	JNC|	rel code addr|	1|	(($1)&0xff)|	|	|	
std::stringstream mout;
mout<<"JNC"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->REL_CODE_ADDR_DIS(val0, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_51H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//51|	2|	ACALL|	abs code addr|	1|	((($1&0xff) + (($0&0xe0)<<3))&0x7ff)|	|	|	
std::stringstream mout;
mout<<"ACALL"<<" ";
unsigned val0=(((mbin[1]&0xff) + ((mbin[0]&0xe0)<<3))&0x7ff);
mout<<dis->ABS_CODE_ADDR_DIS(val0, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_52H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//52|	2|	ANL|	"data addr,A"|	2|	(($1)&0xff)|	|	|	
std::stringstream mout;
mout<<"ANL"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val0, curr_addr, 2);
mout<<", "; 
mout<<"A";
mout<<";"; 
return mout.str();
}
std::string AA_53H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//53|	3|	ANL|	"data addr,#data"|	2|	(($1)&0xff)|	(($2)&0xff)|	|	
std::stringstream mout;
mout<<"ANL"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val0, curr_addr, 3);
mout<<", "; 
unsigned val1=((mbin[2])&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 3);
mout<<";"; 
return mout.str();
}
std::string AA_54H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//54|	2|	ANL|	"A,#data"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"ANL"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_55H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//55|	2|	ANL|	"A,data addr"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"ANL"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_56H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//56|	1|	ANL|	"A,@R0"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ANL"<<" ";
mout<<"A,@R0"<<";";
return mout.str();
}
std::string AA_57H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//57|	1|	ANL|	"A,@R1"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ANL"<<" ";
mout<<"A,@R1"<<";";
return mout.str();
}
std::string AA_58H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//58|	1|	ANL|	"A,R0"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ANL"<<" ";
mout<<"A,R0"<<";";
return mout.str();
}
std::string AA_59H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//59|	1|	ANL|	"A,R1"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ANL"<<" ";
mout<<"A,R1"<<";";
return mout.str();
}
std::string AA_5AH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//5A|	1|	ANL|	"A,R2"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ANL"<<" ";
mout<<"A,R2"<<";";
return mout.str();
}
std::string AA_5BH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//5B|	1|	ANL|	"A,R3"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ANL"<<" ";
mout<<"A,R3"<<";";
return mout.str();
}
std::string AA_5CH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//5C|	1|	ANL|	"A,R4"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ANL"<<" ";
mout<<"A,R4"<<";";
return mout.str();
}
std::string AA_5DH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//5D|	1|	ANL|	"A,R5"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ANL"<<" ";
mout<<"A,R5"<<";";
return mout.str();
}
std::string AA_5EH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//5E|	1|	ANL|	"A,R6"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ANL"<<" ";
mout<<"A,R6"<<";";
return mout.str();
}
std::string AA_5FH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//5F|	1|	ANL|	"A,R7"|	-1|	|	|	|	
std::stringstream mout;
mout<<"ANL"<<" ";
mout<<"A,R7"<<";";
return mout.str();
}
std::string AA_60H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//60|	2|	JZ|	rel code addr|	1|	(($1)&0xff)|	|	|	
std::stringstream mout;
mout<<"JZ"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->REL_CODE_ADDR_DIS(val0, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_61H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//61|	2|	AJMP|	abs code addr|	1|	(((($0>>5)<<8)+($1&0xff))&0x7ff)|	|	|	
std::stringstream mout;
mout<<"AJMP"<<" ";
unsigned val0=((((mbin[0]>>5)<<8)+(mbin[1]&0xff))&0x7ff);
mout<<dis->ABS_CODE_ADDR_DIS(val0, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_62H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//62|	2|	XRL|	"data addr,A"|	2|	(($1)&0xff)|	|	|	
std::stringstream mout;
mout<<"XRL"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val0, curr_addr, 2);
mout<<", "; 
mout<<"A";
mout<<";"; 
return mout.str();
}
std::string AA_63H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//63|	3|	XRL|	"data addr,#data"|	2|	(($1)&0xff)|	(($2)&0xff)|	|	
std::stringstream mout;
mout<<"XRL"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val0, curr_addr, 3);
mout<<", "; 
unsigned val1=((mbin[2])&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 3);
mout<<";"; 
return mout.str();
}
std::string AA_64H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//64|	2|	XRL|	"A,#data"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"XRL"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_65H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//65|	2|	XRL|	"A,data addr"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"XRL"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_66H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//66|	1|	XRL|	"A,@R0"|	-1|	|	|	|	
std::stringstream mout;
mout<<"XRL"<<" ";
mout<<"A,@R0"<<";";
return mout.str();
}
std::string AA_67H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//67|	1|	XRL|	"A,@R1"|	-1|	|	|	|	
std::stringstream mout;
mout<<"XRL"<<" ";
mout<<"A,@R1"<<";";
return mout.str();
}
std::string AA_68H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//68|	1|	XRL|	"A,R0"|	-1|	|	|	|	
std::stringstream mout;
mout<<"XRL"<<" ";
mout<<"A,R0"<<";";
return mout.str();
}
std::string AA_69H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//69|	1|	XRL|	"A,R1"|	-1|	|	|	|	
std::stringstream mout;
mout<<"XRL"<<" ";
mout<<"A,R1"<<";";
return mout.str();
}
std::string AA_6AH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//6A|	1|	XRL|	"A,R2"|	-1|	|	|	|	
std::stringstream mout;
mout<<"XRL"<<" ";
mout<<"A,R2"<<";";
return mout.str();
}
std::string AA_6BH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//6B|	1|	XRL|	"A,R3"|	-1|	|	|	|	
std::stringstream mout;
mout<<"XRL"<<" ";
mout<<"A,R3"<<";";
return mout.str();
}
std::string AA_6CH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//6C|	1|	XRL|	"A,R4"|	-1|	|	|	|	
std::stringstream mout;
mout<<"XRL"<<" ";
mout<<"A,R4"<<";";
return mout.str();
}
std::string AA_6DH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//6D|	1|	XRL|	"A,R5"|	-1|	|	|	|	
std::stringstream mout;
mout<<"XRL"<<" ";
mout<<"A,R5"<<";";
return mout.str();
}
std::string AA_6EH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//6E|	1|	XRL|	"A,R6"|	-1|	|	|	|	
std::stringstream mout;
mout<<"XRL"<<" ";
mout<<"A,R6"<<";";
return mout.str();
}
std::string AA_6FH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//6F|	1|	XRL|	"A,R7"|	-1|	|	|	|	
std::stringstream mout;
mout<<"XRL"<<" ";
mout<<"A,R7"<<";";
return mout.str();
}
std::string AA_70H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//70|	2|	JNZ|	rel code addr|	1|	(($1)&0xff)|	|	|	
std::stringstream mout;
mout<<"JNZ"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->REL_CODE_ADDR_DIS(val0, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_71H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//71|	2|	ACALL|	abs code addr|	1|	((($1&0xff) + (($0&0xe0)<<3))&0x7ff)|	|	|	
std::stringstream mout;
mout<<"ACALL"<<" ";
unsigned val0=(((mbin[1]&0xff) + ((mbin[0]&0xe0)<<3))&0x7ff);
mout<<dis->ABS_CODE_ADDR_DIS(val0, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_72H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//72|	2|	ORL|	"C,bit addr"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"ORL"<<" ";
mout<<"C";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->BIT_ADDR_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_73H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//73|	1|	JMP|	@A+DPTR|	-1|	|	|	|	
std::stringstream mout;
mout<<"JMP"<<" ";
mout<<"@A+DPTR"<<";";
return mout.str();
}
std::string AA_74H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//74|	2|	MOV|	"A,#data"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_75H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//75|	3|	MOV|	"data addr,#data"|	2|	(($1)&0xff)|	(($2)&0xff)|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val0, curr_addr, 3);
mout<<", "; 
unsigned val1=((mbin[2])&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 3);
mout<<";"; 
return mout.str();
}
std::string AA_76H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//76|	2|	MOV|	"@R0,#data"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"@R0";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_77H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//77|	2|	MOV|	"@R1,#data"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"@R1";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_78H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//78|	2|	MOV|	"R0,#data"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"R0";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_79H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//79|	2|	MOV|	"R1,#data"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"R1";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_7AH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//7A|	2|	MOV|	"R2,#data"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"R2";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_7BH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//7B|	2|	MOV|	"R3,#data"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"R3";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_7CH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//7C|	2|	MOV|	"R4,#data"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"R4";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_7DH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//7D|	2|	MOV|	"R5,#data"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"R5";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_7EH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//7E|	2|	MOV|	"R6,#data"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"R6";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_7FH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//7F|	2|	MOV|	"R7,#data"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"R7";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_80H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//80|	2|	SJMP|	rel code addr|	1|	(($1)&0xff)|	|	|	
std::stringstream mout;
mout<<"SJMP"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->REL_CODE_ADDR_DIS(val0, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_81H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//81|	2|	AJMP|	abs code addr|	1|	(((($0>>5)<<8)+($1&0xff))&0x7ff)|	|	|	
std::stringstream mout;
mout<<"AJMP"<<" ";
unsigned val0=((((mbin[0]>>5)<<8)+(mbin[1]&0xff))&0x7ff);
mout<<dis->ABS_CODE_ADDR_DIS(val0, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_82H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//82|	2|	ANL|	"C,bit addr"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"ANL"<<" ";
mout<<"C";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->BIT_ADDR_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_83H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//83|	1|	MOVC|	"A,@A+PC"|	-1|	|	|	|	
std::stringstream mout;
mout<<"MOVC"<<" ";
mout<<"A,@A+PC"<<";";
return mout.str();
}
std::string AA_84H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//84|	1|	DIV|	AB|	-1|	|	|	|	
std::stringstream mout;
mout<<"DIV"<<" ";
mout<<"AB"<<";";
return mout.str();
}
std::string AA_85H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//85|	3|	MOV|	"data addr,data addr"|	2|	(($2)&0xff)|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
unsigned val0=((mbin[2])&0xff);
mout<<dis->DATA_ADDR_DIS(val0, curr_addr, 3);
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val1, curr_addr, 3);
mout<<";"; 
return mout.str();
}
std::string AA_86H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//86|	2|	MOV|	"data addr,@R0"|	2|	(($1)&0xff)|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val0, curr_addr, 2);
mout<<", "; 
mout<<"@R0";
mout<<";"; 
return mout.str();
}
std::string AA_87H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//87|	2|	MOV|	"data addr,@R1"|	2|	(($1)&0xff)|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val0, curr_addr, 2);
mout<<", "; 
mout<<"@R1";
mout<<";"; 
return mout.str();
}
std::string AA_88H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//88|	2|	MOV|	"data addr,R0"|	2|	(($1)&0xff)|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val0, curr_addr, 2);
mout<<", "; 
mout<<"R0";
mout<<";"; 
return mout.str();
}
std::string AA_89H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//89|	2|	MOV|	"data addr,R1"|	2|	(($1)&0xff)|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val0, curr_addr, 2);
mout<<", "; 
mout<<"R1";
mout<<";"; 
return mout.str();
}
std::string AA_8AH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//8A|	2|	MOV|	"data addr,R2"|	2|	(($1)&0xff)|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val0, curr_addr, 2);
mout<<", "; 
mout<<"R2";
mout<<";"; 
return mout.str();
}
std::string AA_8BH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//8B|	2|	MOV|	"data addr,R3"|	2|	(($1)&0xff)|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val0, curr_addr, 2);
mout<<", "; 
mout<<"R3";
mout<<";"; 
return mout.str();
}
std::string AA_8CH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//8C|	2|	MOV|	"data addr,R4"|	2|	(($1)&0xff)|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val0, curr_addr, 2);
mout<<", "; 
mout<<"R4";
mout<<";"; 
return mout.str();
}
std::string AA_8DH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//8D|	2|	MOV|	"data addr,R5"|	2|	(($1)&0xff)|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val0, curr_addr, 2);
mout<<", "; 
mout<<"R5";
mout<<";"; 
return mout.str();
}
std::string AA_8EH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//8E|	2|	MOV|	"data addr,R6"|	2|	(($1)&0xff)|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val0, curr_addr, 2);
mout<<", "; 
mout<<"R6";
mout<<";"; 
return mout.str();
}
std::string AA_8FH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//8F|	2|	MOV|	"data addr,R7"|	2|	(($1)&0xff)|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val0, curr_addr, 2);
mout<<", "; 
mout<<"R7";
mout<<";"; 
return mout.str();
}
std::string AA_90H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//90|	3|	MOV|	"DPTR,#data"|	2|	|	((($1<<8)+($2&0xff))&0xffff)|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"DPTR";
mout<<", "; 
unsigned val1=(((mbin[1]<<8)+(mbin[2]&0xff))&0xffff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 3);
mout<<";"; 
return mout.str();
}
std::string AA_91H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//91|	2|	ACALL|	abs code addr|	1|	((($1&0xff) + (($0&0xe0)<<3))&0x7ff)|	|	|	
std::stringstream mout;
mout<<"ACALL"<<" ";
unsigned val0=(((mbin[1]&0xff) + ((mbin[0]&0xe0)<<3))&0x7ff);
mout<<dis->ABS_CODE_ADDR_DIS(val0, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_92H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//92|	2|	MOV|	"bit addr,C"|	2|	(($1)&0xff)|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->BIT_ADDR_DIS(val0, curr_addr, 2);
mout<<", "; 
mout<<"C";
mout<<";"; 
return mout.str();
}
std::string AA_93H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//93|	1|	MOVC|	"A,@A+DPTR"|	-1|	|	|	|	
std::stringstream mout;
mout<<"MOVC"<<" ";
mout<<"A,@A+DPTR"<<";";
return mout.str();
}
std::string AA_94H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//94|	2|	SUBB|	"A,#data"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"SUBB"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_95H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//95|	2|	SUBB|	"A,data addr"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"SUBB"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_96H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//96|	1|	SUBB|	"A,@R0"|	-1|	|	|	|	
std::stringstream mout;
mout<<"SUBB"<<" ";
mout<<"A,@R0"<<";";
return mout.str();
}
std::string AA_97H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//97|	1|	SUBB|	"A,@R1"|	-1|	|	|	|	
std::stringstream mout;
mout<<"SUBB"<<" ";
mout<<"A,@R1"<<";";
return mout.str();
}
std::string AA_98H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//98|	1|	SUBB|	"A,R0"|	-1|	|	|	|	
std::stringstream mout;
mout<<"SUBB"<<" ";
mout<<"A,R0"<<";";
return mout.str();
}
std::string AA_99H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//99|	1|	SUBB|	"A,R1"|	-1|	|	|	|	
std::stringstream mout;
mout<<"SUBB"<<" ";
mout<<"A,R1"<<";";
return mout.str();
}
std::string AA_9AH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//9A|	1|	SUBB|	"A,R2"|	-1|	|	|	|	
std::stringstream mout;
mout<<"SUBB"<<" ";
mout<<"A,R2"<<";";
return mout.str();
}
std::string AA_9BH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//9B|	1|	SUBB|	"A,R3"|	-1|	|	|	|	
std::stringstream mout;
mout<<"SUBB"<<" ";
mout<<"A,R3"<<";";
return mout.str();
}
std::string AA_9CH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//9C|	1|	SUBB|	"A,R4"|	-1|	|	|	|	
std::stringstream mout;
mout<<"SUBB"<<" ";
mout<<"A,R4"<<";";
return mout.str();
}
std::string AA_9DH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//9D|	1|	SUBB|	"A,R5"|	-1|	|	|	|	
std::stringstream mout;
mout<<"SUBB"<<" ";
mout<<"A,R5"<<";";
return mout.str();
}
std::string AA_9EH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//9E|	1|	SUBB|	"A,R6"|	-1|	|	|	|	
std::stringstream mout;
mout<<"SUBB"<<" ";
mout<<"A,R6"<<";";
return mout.str();
}
std::string AA_9FH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//9F|	1|	SUBB|	"A,R7"|	-1|	|	|	|	
std::stringstream mout;
mout<<"SUBB"<<" ";
mout<<"A,R7"<<";";
return mout.str();
}
std::string AA_A0H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//A0|	2|	ORL|	"C,/bit addr"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"ORL"<<" ";
mout<<"C";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->MBIT_ADDR_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_A1H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//A1|	2|	AJMP|	abs code addr|	1|	(((($0>>5)<<8)+($1&0xff))&0x7ff)|	|	|	
std::stringstream mout;
mout<<"AJMP"<<" ";
unsigned val0=((((mbin[0]>>5)<<8)+(mbin[1]&0xff))&0x7ff);
mout<<dis->ABS_CODE_ADDR_DIS(val0, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_A2H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//A2|	2|	MOV|	"C,bit addr"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"C";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->BIT_ADDR_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_A3H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//A3|	1|	INC|	DPTR|	-1|	|	|	|	
std::stringstream mout;
mout<<"INC"<<" ";
mout<<"DPTR"<<";";
return mout.str();
}
std::string AA_A4H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//A4|	1|	MUL|	AB|	-1|	|	|	|	
std::stringstream mout;
mout<<"MUL"<<" ";
mout<<"AB"<<";";
return mout.str();
}
std::string AA_A5H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//A5|	3|	SIMTRAP|	"data addr,data addr"|	2|	(($1)&0xff)|	(($2)&0xff)|	|	
std::stringstream mout;
mout<<"SIMTRAP"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val0, curr_addr, 3);
mout<<", "; 
unsigned val1=((mbin[2])&0xff);
mout<<dis->DATA_ADDR_DIS(val1, curr_addr, 3);
mout<<";"; 
return mout.str();
}
std::string AA_A6H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//A6|	2|	MOV|	"@R0,data addr"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"@R0";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_A7H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//A7|	2|	MOV|	"@R1,data addr"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"@R1";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_A8H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//A8|	2|	MOV|	"R0,data addr"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"R0";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_A9H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//A9|	2|	MOV|	"R1,data addr"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"R1";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_AAH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//AA|	2|	MOV|	"R2,data addr"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"R2";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_ABH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//AB|	2|	MOV|	"R3,data addr"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"R3";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_ACH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//AC|	2|	MOV|	"R4,data addr"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"R4";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_ADH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//AD|	2|	MOV|	"R5,data addr"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"R5";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_AEH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//AE|	2|	MOV|	"R6,data addr"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"R6";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_AFH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//AF|	2|	MOV|	"R7,data addr"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"R7";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_B0H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//B0|	2|	ANL|	"C,/bit addr"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"ANL"<<" ";
mout<<"C";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->MBIT_ADDR_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_B1H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//B1|	2|	ACALL|	abs code addr|	1|	((($1&0xff) + (($0&0xe0)<<3))&0x7ff)|	|	|	
std::stringstream mout;
mout<<"ACALL"<<" ";
unsigned val0=(((mbin[1]&0xff) + ((mbin[0]&0xe0)<<3))&0x7ff);
mout<<dis->ABS_CODE_ADDR_DIS(val0, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_B2H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//B2|	2|	CPL|	bit addr|	1|	(($1)&0xff)|	|	|	
std::stringstream mout;
mout<<"CPL"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->BIT_ADDR_DIS(val0, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_B3H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//B3|	1|	CPL|	C|	-1|	|	|	|	
std::stringstream mout;
mout<<"CPL"<<" ";
mout<<"C"<<";";
return mout.str();
}
std::string AA_B4H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//B4|	3|	CJNE|	"A,#data,rel code addr"|	3|	|	(($1)&0xff)|	(($2)&0xff)|	
std::stringstream mout;
mout<<"CJNE"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 3);
mout<<", "; 
unsigned val2=((mbin[2])&0xff);
mout<<dis->REL_CODE_ADDR_DIS(val2, curr_addr, 3);
mout<<";"; 
return mout.str();
}
std::string AA_B5H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//B5|	3|	CJNE|	"A,data addr,rel code addr"|	3|	|	(($1)&0xff)|	(($2)&0xff)|	
std::stringstream mout;
mout<<"CJNE"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val1, curr_addr, 3);
mout<<", "; 
unsigned val2=((mbin[2])&0xff);
mout<<dis->REL_CODE_ADDR_DIS(val2, curr_addr, 3);
mout<<";"; 
return mout.str();
}
std::string AA_B6H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//B6|	3|	CJNE|	"@R0,#data,rel code addr"|	3|	|	(($1)&0xff)|	(($2)&0xff)|	
std::stringstream mout;
mout<<"CJNE"<<" ";
mout<<"@R0";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 3);
mout<<", "; 
unsigned val2=((mbin[2])&0xff);
mout<<dis->REL_CODE_ADDR_DIS(val2, curr_addr, 3);
mout<<";"; 
return mout.str();
}
std::string AA_B7H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//B7|	3|	CJNE|	"@R1,#data,rel code addr"|	3|	|	(($1)&0xff)|	(($2)&0xff)|	
std::stringstream mout;
mout<<"CJNE"<<" ";
mout<<"@R1";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 3);
mout<<", "; 
unsigned val2=((mbin[2])&0xff);
mout<<dis->REL_CODE_ADDR_DIS(val2, curr_addr, 3);
mout<<";"; 
return mout.str();
}
std::string AA_B8H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//B8|	3|	CJNE|	"R0,#data,rel code addr"|	3|	|	(($1)&0xff)|	(($2)&0xff)|	
std::stringstream mout;
mout<<"CJNE"<<" ";
mout<<"R0";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 3);
mout<<", "; 
unsigned val2=((mbin[2])&0xff);
mout<<dis->REL_CODE_ADDR_DIS(val2, curr_addr, 3);
mout<<";"; 
return mout.str();
}
std::string AA_B9H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//B9|	3|	CJNE|	"R1,#data,rel code addr"|	3|	|	(($1)&0xff)|	(($2)&0xff)|	
std::stringstream mout;
mout<<"CJNE"<<" ";
mout<<"R1";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 3);
mout<<", "; 
unsigned val2=((mbin[2])&0xff);
mout<<dis->REL_CODE_ADDR_DIS(val2, curr_addr, 3);
mout<<";"; 
return mout.str();
}
std::string AA_BAH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//BA|	3|	CJNE|	"R2,#data,rel code addr"|	3|	|	(($1)&0xff)|	(($2)&0xff)|	
std::stringstream mout;
mout<<"CJNE"<<" ";
mout<<"R2";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 3);
mout<<", "; 
unsigned val2=((mbin[2])&0xff);
mout<<dis->REL_CODE_ADDR_DIS(val2, curr_addr, 3);
mout<<";"; 
return mout.str();
}
std::string AA_BBH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//BB|	3|	CJNE|	"R3,#data,rel code addr"|	3|	|	(($1)&0xff)|	(($2)&0xff)|	
std::stringstream mout;
mout<<"CJNE"<<" ";
mout<<"R3";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 3);
mout<<", "; 
unsigned val2=((mbin[2])&0xff);
mout<<dis->REL_CODE_ADDR_DIS(val2, curr_addr, 3);
mout<<";"; 
return mout.str();
}
std::string AA_BCH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//BC|	3|	CJNE|	"R4,#data,rel code addr"|	3|	|	(($1)&0xff)|	(($2)&0xff)|	
std::stringstream mout;
mout<<"CJNE"<<" ";
mout<<"R4";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 3);
mout<<", "; 
unsigned val2=((mbin[2])&0xff);
mout<<dis->REL_CODE_ADDR_DIS(val2, curr_addr, 3);
mout<<";"; 
return mout.str();
}
std::string AA_BDH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//BD|	3|	CJNE|	"R5,#data,rel code addr"|	3|	|	(($1)&0xff)|	(($2)&0xff)|	
std::stringstream mout;
mout<<"CJNE"<<" ";
mout<<"R5";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 3);
mout<<", "; 
unsigned val2=((mbin[2])&0xff);
mout<<dis->REL_CODE_ADDR_DIS(val2, curr_addr, 3);
mout<<";"; 
return mout.str();
}
std::string AA_BEH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//BE|	3|	CJNE|	"R6,#data,rel code addr"|	3|	|	(($1)&0xff)|	(($2)&0xff)|	
std::stringstream mout;
mout<<"CJNE"<<" ";
mout<<"R6";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 3);
mout<<", "; 
unsigned val2=((mbin[2])&0xff);
mout<<dis->REL_CODE_ADDR_DIS(val2, curr_addr, 3);
mout<<";"; 
return mout.str();
}
std::string AA_BFH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//BF|	3|	CJNE|	"R7,#data,rel code addr"|	3|	|	(($1)&0xff)|	(($2)&0xff)|	
std::stringstream mout;
mout<<"CJNE"<<" ";
mout<<"R7";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_VALUE_DIS(val1, curr_addr, 3);
mout<<", "; 
unsigned val2=((mbin[2])&0xff);
mout<<dis->REL_CODE_ADDR_DIS(val2, curr_addr, 3);
mout<<";"; 
return mout.str();
}
std::string AA_C0H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//C0|	2|	PUSH|	data addr|	1|	(($1)&0xff)|	|	|	
std::stringstream mout;
mout<<"PUSH"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val0, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_C1H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//C1|	2|	AJMP|	abs code addr|	1|	(((($0>>5)<<8)+($1&0xff))&0x7ff)|	|	|	
std::stringstream mout;
mout<<"AJMP"<<" ";
unsigned val0=((((mbin[0]>>5)<<8)+(mbin[1]&0xff))&0x7ff);
mout<<dis->ABS_CODE_ADDR_DIS(val0, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_C2H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//C2|	2|	CLR|	bit addr|	1|	(($1)&0xff)|	|	|	
std::stringstream mout;
mout<<"CLR"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->BIT_ADDR_DIS(val0, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_C3H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//C3|	1|	CLR|	C|	-1|	|	|	|	
std::stringstream mout;
mout<<"CLR"<<" ";
mout<<"C"<<";";
return mout.str();
}
std::string AA_C4H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//C4|	1|	SWAP|	A|	-1|	|	|	|	
std::stringstream mout;
mout<<"SWAP"<<" ";
mout<<"A"<<";";
return mout.str();
}
std::string AA_C5H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//C5|	2|	XCH|	"A,data addr"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"XCH"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_C6H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//C6|	1|	XCH|	"A,@R0"|	-1|	|	|	|	
std::stringstream mout;
mout<<"XCH"<<" ";
mout<<"A,@R0"<<";";
return mout.str();
}
std::string AA_C7H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//C7|	1|	XCH|	"A,@R1"|	-1|	|	|	|	
std::stringstream mout;
mout<<"XCH"<<" ";
mout<<"A,@R1"<<";";
return mout.str();
}
std::string AA_C8H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//C8|	1|	XCH|	"A,R0"|	-1|	|	|	|	
std::stringstream mout;
mout<<"XCH"<<" ";
mout<<"A,R0"<<";";
return mout.str();
}
std::string AA_C9H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//C9|	1|	XCH|	"A,R1"|	-1|	|	|	|	
std::stringstream mout;
mout<<"XCH"<<" ";
mout<<"A,R1"<<";";
return mout.str();
}
std::string AA_CAH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//CA|	1|	XCH|	"A,R2"|	-1|	|	|	|	
std::stringstream mout;
mout<<"XCH"<<" ";
mout<<"A,R2"<<";";
return mout.str();
}
std::string AA_CBH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//CB|	1|	XCH|	"A,R3"|	-1|	|	|	|	
std::stringstream mout;
mout<<"XCH"<<" ";
mout<<"A,R3"<<";";
return mout.str();
}
std::string AA_CCH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//CC|	1|	XCH|	"A,R4"|	-1|	|	|	|	
std::stringstream mout;
mout<<"XCH"<<" ";
mout<<"A,R4"<<";";
return mout.str();
}
std::string AA_CDH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//CD|	1|	XCH|	"A,R5"|	-1|	|	|	|	
std::stringstream mout;
mout<<"XCH"<<" ";
mout<<"A,R5"<<";";
return mout.str();
}
std::string AA_CEH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//CE|	1|	XCH|	"A,R6"|	-1|	|	|	|	
std::stringstream mout;
mout<<"XCH"<<" ";
mout<<"A,R6"<<";";
return mout.str();
}
std::string AA_CFH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//CF|	1|	XCH|	"A,R7"|	-1|	|	|	|	
std::stringstream mout;
mout<<"XCH"<<" ";
mout<<"A,R7"<<";";
return mout.str();
}
std::string AA_D0H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//D0|	2|	POP|	data addr|	1|	(($1)&0xff)|	|	|	
std::stringstream mout;
mout<<"POP"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val0, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_D1H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//D1|	2|	ACALL|	abs code addr|	1|	((($1&0xff) + (($0&0xe0)<<3))&0x7ff)|	|	|	
std::stringstream mout;
mout<<"ACALL"<<" ";
unsigned val0=(((mbin[1]&0xff) + ((mbin[0]&0xe0)<<3))&0x7ff);
mout<<dis->ABS_CODE_ADDR_DIS(val0, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_D2H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//D2|	2|	SETB|	bit addr|	1|	(($1)&0xff)|	|	|	
std::stringstream mout;
mout<<"SETB"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->BIT_ADDR_DIS(val0, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_D3H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//D3|	1|	SETB|	C|	-1|	|	|	|	
std::stringstream mout;
mout<<"SETB"<<" ";
mout<<"C"<<";";
return mout.str();
}
std::string AA_D4H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//D4|	1|	DA|	A|	-1|	|	|	|	
std::stringstream mout;
mout<<"DA"<<" ";
mout<<"A"<<";";
return mout.str();
}
std::string AA_D5H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//D5|	3|	DJNZ|	"data addr,rel code addr"|	2|	(($1)&0xff)|	(($2)&0xff)|	|	
std::stringstream mout;
mout<<"DJNZ"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val0, curr_addr, 3);
mout<<", "; 
unsigned val1=((mbin[2])&0xff);
mout<<dis->REL_CODE_ADDR_DIS(val1, curr_addr, 3);
mout<<";"; 
return mout.str();
}
std::string AA_D6H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//D6|	1|	XCHD|	"A,@R0"|	-1|	|	|	|	
std::stringstream mout;
mout<<"XCHD"<<" ";
mout<<"A,@R0"<<";";
return mout.str();
}
std::string AA_D7H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//D7|	1|	XCHD|	"A,@R1"|	-1|	|	|	|	
std::stringstream mout;
mout<<"XCHD"<<" ";
mout<<"A,@R1"<<";";
return mout.str();
}
std::string AA_D8H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//D8|	2|	DJNZ|	"R0,rel code addr"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"DJNZ"<<" ";
mout<<"R0";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->REL_CODE_ADDR_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_D9H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//D9|	2|	DJNZ|	"R1,rel code addr"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"DJNZ"<<" ";
mout<<"R1";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->REL_CODE_ADDR_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_DAH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//DA|	2|	DJNZ|	"R2,rel code addr"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"DJNZ"<<" ";
mout<<"R2";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->REL_CODE_ADDR_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_DBH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//DB|	2|	DJNZ|	"R3,rel code addr"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"DJNZ"<<" ";
mout<<"R3";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->REL_CODE_ADDR_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_DCH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//DC|	2|	DJNZ|	"R4,rel code addr"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"DJNZ"<<" ";
mout<<"R4";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->REL_CODE_ADDR_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_DDH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//DD|	2|	DJNZ|	"R5,rel code addr"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"DJNZ"<<" ";
mout<<"R5";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->REL_CODE_ADDR_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_DEH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//DE|	2|	DJNZ|	"R6,rel code addr"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"DJNZ"<<" ";
mout<<"R6";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->REL_CODE_ADDR_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_DFH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//DF|	2|	DJNZ|	"R7,rel code addr"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"DJNZ"<<" ";
mout<<"R7";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->REL_CODE_ADDR_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_E0H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//E0|	1|	MOVX|	"A,@DPTR"|	-1|	|	|	|	
std::stringstream mout;
mout<<"MOVX"<<" ";
mout<<"A,@DPTR"<<";";
return mout.str();
}
std::string AA_E1H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//E1|	2|	AJMP|	abs code addr|	1|	(((($0>>5)<<8)+($1&0xff))&0x7ff)|	|	|	
std::stringstream mout;
mout<<"AJMP"<<" ";
unsigned val0=((((mbin[0]>>5)<<8)+(mbin[1]&0xff))&0x7ff);
mout<<dis->ABS_CODE_ADDR_DIS(val0, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_E2H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//E2|	1|	MOVX|	"A,@R0"|	-1|	|	|	|	
std::stringstream mout;
mout<<"MOVX"<<" ";
mout<<"A,@R0"<<";";
return mout.str();
}
std::string AA_E3H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//E3|	1|	MOVX|	"A,@R1"|	-1|	|	|	|	
std::stringstream mout;
mout<<"MOVX"<<" ";
mout<<"A,@R1"<<";";
return mout.str();
}
std::string AA_E4H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//E4|	1|	CLR|	A|	-1|	|	|	|	
std::stringstream mout;
mout<<"CLR"<<" ";
mout<<"A"<<";";
return mout.str();
}
std::string AA_E5H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//E5|	2|	MOV|	"A,data addr"|	2|	|	(($1)&0xff)|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"A";
mout<<", "; 
unsigned val1=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val1, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_E6H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//E6|	1|	MOV|	"A,@R0"|	-1|	|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"A,@R0"<<";";
return mout.str();
}
std::string AA_E7H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//E7|	1|	MOV|	"A,@R1"|	-1|	|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"A,@R1"<<";";
return mout.str();
}
std::string AA_E8H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//E8|	1|	MOV|	"A,R0"|	-1|	|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"A,R0"<<";";
return mout.str();
}
std::string AA_E9H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//E9|	1|	MOV|	"A,R1"|	-1|	|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"A,R1"<<";";
return mout.str();
}
std::string AA_EAH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//EA|	1|	MOV|	"A,R2"|	-1|	|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"A,R2"<<";";
return mout.str();
}
std::string AA_EBH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//EB|	1|	MOV|	"A,R3"|	-1|	|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"A,R3"<<";";
return mout.str();
}
std::string AA_ECH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//EC|	1|	MOV|	"A,R4"|	-1|	|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"A,R4"<<";";
return mout.str();
}
std::string AA_EDH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//ED|	1|	MOV|	"A,R5"|	-1|	|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"A,R5"<<";";
return mout.str();
}
std::string AA_EEH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//EE|	1|	MOV|	"A,R6"|	-1|	|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"A,R6"<<";";
return mout.str();
}
std::string AA_EFH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//EF|	1|	MOV|	"A,R7"|	-1|	|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"A,R7"<<";";
return mout.str();
}
std::string AA_F0H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//F0|	1|	MOVX|	"@DPTR,A"|	-1|	|	|	|	
std::stringstream mout;
mout<<"MOVX"<<" ";
mout<<"@DPTR,A"<<";";
return mout.str();
}
std::string AA_F1H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//F1|	2|	ACALL|	abs code addr|	1|	((($1&0xff) + (($0&0xe0)<<3))&0x7ff)|	|	|	
std::stringstream mout;
mout<<"ACALL"<<" ";
unsigned val0=(((mbin[1]&0xff) + ((mbin[0]&0xe0)<<3))&0x7ff);
mout<<dis->ABS_CODE_ADDR_DIS(val0, curr_addr, 2);
mout<<";"; 
return mout.str();
}
std::string AA_F2H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//F2|	1|	MOVX|	"@R0,A"|	-1|	|	|	|	
std::stringstream mout;
mout<<"MOVX"<<" ";
mout<<"@R0,A"<<";";
return mout.str();
}
std::string AA_F3H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//F3|	1|	MOVX|	"@R1,A"|	-1|	|	|	|	
std::stringstream mout;
mout<<"MOVX"<<" ";
mout<<"@R1,A"<<";";
return mout.str();
}
std::string AA_F4H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//F4|	1|	CPL|	A|	-1|	|	|	|	
std::stringstream mout;
mout<<"CPL"<<" ";
mout<<"A"<<";";
return mout.str();
}
std::string AA_F5H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//F5|	2|	MOV|	"data addr,A"|	2|	(($1)&0xff)|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
unsigned val0=((mbin[1])&0xff);
mout<<dis->DATA_ADDR_DIS(val0, curr_addr, 2);
mout<<", "; 
mout<<"A";
mout<<";"; 
return mout.str();
}
std::string AA_F6H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//F6|	1|	MOV|	"@R0,A"|	-1|	|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"@R0,A"<<";";
return mout.str();
}
std::string AA_F7H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//F7|	1|	MOV|	"@R1,A"|	-1|	|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"@R1,A"<<";";
return mout.str();
}
std::string AA_F8H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//F8|	1|	MOV|	"R0,A"|	-1|	|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"R0,A"<<";";
return mout.str();
}
std::string AA_F9H(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//F9|	1|	MOV|	"R1,A"|	-1|	|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"R1,A"<<";";
return mout.str();
}
std::string AA_FAH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//FA|	1|	MOV|	"R2,A"|	-1|	|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"R2,A"<<";";
return mout.str();
}
std::string AA_FBH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//FB|	1|	MOV|	"R3,A"|	-1|	|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"R3,A"<<";";
return mout.str();
}
std::string AA_FCH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//FC|	1|	MOV|	"R4,A"|	-1|	|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"R4,A"<<";";
return mout.str();
}
std::string AA_FDH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//FD|	1|	MOV|	"R5,A"|	-1|	|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"R5,A"<<";";
return mout.str();
}
std::string AA_FEH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//FE|	1|	MOV|	"R6,A"|	-1|	|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"R6,A"<<";";
return mout.str();
}
std::string AA_FFH(dis8051* dis, std::string mbin, unsigned curr_addr)
{
//FF|	1|	MOV|	"R7,A"|	-1|	|	|	|	
std::stringstream mout;
mout<<"MOV"<<" ";
mout<<"R7,A"<<";";
return mout.str();
}
int load_dis_keywords(std::map<unsigned, DIS_FUNC_PTR> &keys)
{
keys[0x0]=&AA_0H;
keys[0x1]=&AA_1H;
keys[0x2]=&AA_2H;
keys[0x3]=&AA_3H;
keys[0x4]=&AA_4H;
keys[0x5]=&AA_5H;
keys[0x6]=&AA_6H;
keys[0x7]=&AA_7H;
keys[0x8]=&AA_8H;
keys[0x9]=&AA_9H;
keys[0x0A]=&AA_0AH;
keys[0x0B]=&AA_0BH;
keys[0x0C]=&AA_0CH;
keys[0x0D]=&AA_0DH;
keys[0x0E]=&AA_0EH;
keys[0x0F]=&AA_0FH;
keys[0x10]=&AA_10H;
keys[0x11]=&AA_11H;
keys[0x12]=&AA_12H;
keys[0x13]=&AA_13H;
keys[0x14]=&AA_14H;
keys[0x15]=&AA_15H;
keys[0x16]=&AA_16H;
keys[0x17]=&AA_17H;
keys[0x18]=&AA_18H;
keys[0x19]=&AA_19H;
keys[0x1A]=&AA_1AH;
keys[0x1B]=&AA_1BH;
keys[0x1C]=&AA_1CH;
keys[0x1D]=&AA_1DH;
keys[0x1E]=&AA_1EH;
keys[0x1F]=&AA_1FH;
keys[0x20]=&AA_20H;
keys[0x21]=&AA_21H;
keys[0x22]=&AA_22H;
keys[0x23]=&AA_23H;
keys[0x24]=&AA_24H;
keys[0x25]=&AA_25H;
keys[0x26]=&AA_26H;
keys[0x27]=&AA_27H;
keys[0x28]=&AA_28H;
keys[0x29]=&AA_29H;
keys[0x2A]=&AA_2AH;
keys[0x2B]=&AA_2BH;
keys[0x2C]=&AA_2CH;
keys[0x2D]=&AA_2DH;
keys[0x2E]=&AA_2EH;
keys[0x2F]=&AA_2FH;
keys[0x30]=&AA_30H;
keys[0x31]=&AA_31H;
keys[0x32]=&AA_32H;
keys[0x33]=&AA_33H;
keys[0x34]=&AA_34H;
keys[0x35]=&AA_35H;
keys[0x36]=&AA_36H;
keys[0x37]=&AA_37H;
keys[0x38]=&AA_38H;
keys[0x39]=&AA_39H;
keys[0x3A]=&AA_3AH;
keys[0x3B]=&AA_3BH;
keys[0x3C]=&AA_3CH;
keys[0x3D]=&AA_3DH;
keys[0x3E]=&AA_3EH;
keys[0x3F]=&AA_3FH;
keys[0x40]=&AA_40H;
keys[0x41]=&AA_41H;
keys[0x42]=&AA_42H;
keys[0x43]=&AA_43H;
keys[0x44]=&AA_44H;
keys[0x45]=&AA_45H;
keys[0x46]=&AA_46H;
keys[0x47]=&AA_47H;
keys[0x48]=&AA_48H;
keys[0x49]=&AA_49H;
keys[0x4A]=&AA_4AH;
keys[0x4B]=&AA_4BH;
keys[0x4C]=&AA_4CH;
keys[0x4D]=&AA_4DH;
keys[0x4E]=&AA_4EH;
keys[0x4F]=&AA_4FH;
keys[0x50]=&AA_50H;
keys[0x51]=&AA_51H;
keys[0x52]=&AA_52H;
keys[0x53]=&AA_53H;
keys[0x54]=&AA_54H;
keys[0x55]=&AA_55H;
keys[0x56]=&AA_56H;
keys[0x57]=&AA_57H;
keys[0x58]=&AA_58H;
keys[0x59]=&AA_59H;
keys[0x5A]=&AA_5AH;
keys[0x5B]=&AA_5BH;
keys[0x5C]=&AA_5CH;
keys[0x5D]=&AA_5DH;
keys[0x5E]=&AA_5EH;
keys[0x5F]=&AA_5FH;
keys[0x60]=&AA_60H;
keys[0x61]=&AA_61H;
keys[0x62]=&AA_62H;
keys[0x63]=&AA_63H;
keys[0x64]=&AA_64H;
keys[0x65]=&AA_65H;
keys[0x66]=&AA_66H;
keys[0x67]=&AA_67H;
keys[0x68]=&AA_68H;
keys[0x69]=&AA_69H;
keys[0x6A]=&AA_6AH;
keys[0x6B]=&AA_6BH;
keys[0x6C]=&AA_6CH;
keys[0x6D]=&AA_6DH;
keys[0x6E]=&AA_6EH;
keys[0x6F]=&AA_6FH;
keys[0x70]=&AA_70H;
keys[0x71]=&AA_71H;
keys[0x72]=&AA_72H;
keys[0x73]=&AA_73H;
keys[0x74]=&AA_74H;
keys[0x75]=&AA_75H;
keys[0x76]=&AA_76H;
keys[0x77]=&AA_77H;
keys[0x78]=&AA_78H;
keys[0x79]=&AA_79H;
keys[0x7A]=&AA_7AH;
keys[0x7B]=&AA_7BH;
keys[0x7C]=&AA_7CH;
keys[0x7D]=&AA_7DH;
keys[0x7E]=&AA_7EH;
keys[0x7F]=&AA_7FH;
keys[0x80]=&AA_80H;
keys[0x81]=&AA_81H;
keys[0x82]=&AA_82H;
keys[0x83]=&AA_83H;
keys[0x84]=&AA_84H;
keys[0x85]=&AA_85H;
keys[0x86]=&AA_86H;
keys[0x87]=&AA_87H;
keys[0x88]=&AA_88H;
keys[0x89]=&AA_89H;
keys[0x8A]=&AA_8AH;
keys[0x8B]=&AA_8BH;
keys[0x8C]=&AA_8CH;
keys[0x8D]=&AA_8DH;
keys[0x8E]=&AA_8EH;
keys[0x8F]=&AA_8FH;
keys[0x90]=&AA_90H;
keys[0x91]=&AA_91H;
keys[0x92]=&AA_92H;
keys[0x93]=&AA_93H;
keys[0x94]=&AA_94H;
keys[0x95]=&AA_95H;
keys[0x96]=&AA_96H;
keys[0x97]=&AA_97H;
keys[0x98]=&AA_98H;
keys[0x99]=&AA_99H;
keys[0x9A]=&AA_9AH;
keys[0x9B]=&AA_9BH;
keys[0x9C]=&AA_9CH;
keys[0x9D]=&AA_9DH;
keys[0x9E]=&AA_9EH;
keys[0x9F]=&AA_9FH;
keys[0xA0]=&AA_A0H;
keys[0xA1]=&AA_A1H;
keys[0xA2]=&AA_A2H;
keys[0xA3]=&AA_A3H;
keys[0xA4]=&AA_A4H;
keys[0xA5]=&AA_A5H;
keys[0xA6]=&AA_A6H;
keys[0xA7]=&AA_A7H;
keys[0xA8]=&AA_A8H;
keys[0xA9]=&AA_A9H;
keys[0xAA]=&AA_AAH;
keys[0xAB]=&AA_ABH;
keys[0xAC]=&AA_ACH;
keys[0xAD]=&AA_ADH;
keys[0xAE]=&AA_AEH;
keys[0xAF]=&AA_AFH;
keys[0xB0]=&AA_B0H;
keys[0xB1]=&AA_B1H;
keys[0xB2]=&AA_B2H;
keys[0xB3]=&AA_B3H;
keys[0xB4]=&AA_B4H;
keys[0xB5]=&AA_B5H;
keys[0xB6]=&AA_B6H;
keys[0xB7]=&AA_B7H;
keys[0xB8]=&AA_B8H;
keys[0xB9]=&AA_B9H;
keys[0xBA]=&AA_BAH;
keys[0xBB]=&AA_BBH;
keys[0xBC]=&AA_BCH;
keys[0xBD]=&AA_BDH;
keys[0xBE]=&AA_BEH;
keys[0xBF]=&AA_BFH;
keys[0xC0]=&AA_C0H;
keys[0xC1]=&AA_C1H;
keys[0xC2]=&AA_C2H;
keys[0xC3]=&AA_C3H;
keys[0xC4]=&AA_C4H;
keys[0xC5]=&AA_C5H;
keys[0xC6]=&AA_C6H;
keys[0xC7]=&AA_C7H;
keys[0xC8]=&AA_C8H;
keys[0xC9]=&AA_C9H;
keys[0xCA]=&AA_CAH;
keys[0xCB]=&AA_CBH;
keys[0xCC]=&AA_CCH;
keys[0xCD]=&AA_CDH;
keys[0xCE]=&AA_CEH;
keys[0xCF]=&AA_CFH;
keys[0xD0]=&AA_D0H;
keys[0xD1]=&AA_D1H;
keys[0xD2]=&AA_D2H;
keys[0xD3]=&AA_D3H;
keys[0xD4]=&AA_D4H;
keys[0xD5]=&AA_D5H;
keys[0xD6]=&AA_D6H;
keys[0xD7]=&AA_D7H;
keys[0xD8]=&AA_D8H;
keys[0xD9]=&AA_D9H;
keys[0xDA]=&AA_DAH;
keys[0xDB]=&AA_DBH;
keys[0xDC]=&AA_DCH;
keys[0xDD]=&AA_DDH;
keys[0xDE]=&AA_DEH;
keys[0xDF]=&AA_DFH;
keys[0xE0]=&AA_E0H;
keys[0xE1]=&AA_E1H;
keys[0xE2]=&AA_E2H;
keys[0xE3]=&AA_E3H;
keys[0xE4]=&AA_E4H;
keys[0xE5]=&AA_E5H;
keys[0xE6]=&AA_E6H;
keys[0xE7]=&AA_E7H;
keys[0xE8]=&AA_E8H;
keys[0xE9]=&AA_E9H;
keys[0xEA]=&AA_EAH;
keys[0xEB]=&AA_EBH;
keys[0xEC]=&AA_ECH;
keys[0xED]=&AA_EDH;
keys[0xEE]=&AA_EEH;
keys[0xEF]=&AA_EFH;
keys[0xF0]=&AA_F0H;
keys[0xF1]=&AA_F1H;
keys[0xF2]=&AA_F2H;
keys[0xF3]=&AA_F3H;
keys[0xF4]=&AA_F4H;
keys[0xF5]=&AA_F5H;
keys[0xF6]=&AA_F6H;
keys[0xF7]=&AA_F7H;
keys[0xF8]=&AA_F8H;
keys[0xF9]=&AA_F9H;
keys[0xFA]=&AA_FAH;
keys[0xFB]=&AA_FBH;
keys[0xFC]=&AA_FCH;
keys[0xFD]=&AA_FDH;
keys[0xFE]=&AA_FEH;
keys[0xFF]=&AA_FFH;
return 0;
}
