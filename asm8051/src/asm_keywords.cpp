#include "asm_keywords.h"
#include "asm_context.h"

int ACALL_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //ACALL|	addr11|	Absolute Subroutine Call|	2|	24|	PROGRAM BRANCHING|	(($1&0x700)>>3)+0x11|	($1&0xff)|	|	TOKEN_KEYWORD|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_KEYWORD) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=((m_tokens[1].num&0x700)>>3)+0x11;
    m_hex_text[1]=(m_tokens[1].num&0xff);
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0x7ff& m_tokens[1].num;
    unsigned int cmp01=0x7ff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0x7ff^(0x7ff>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    return 0;
    }
    }
    

//unknown code
return -1;
}
int ADD_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //ADD|	"A,Rn"|	Add register to Accumulator|	1|	12|	ARITHMETIC OPERATIONS|	0x28+$2|	|	|	TOKEN_ACC|	TOKEN_RN|	
    //ADD|	"A,direct"|	Add direct byte to Accumulator|	2|	12|	ARITHMETIC OPERATIONS|	0x25|	$2 |	|	TOKEN_ACC|	TOKEN_NUM|	
    //ADD|	"A,@Ri"|	Add indirect RAM to Accumulator|	1|	12|	ARITHMETIC OPERATIONS|	0x26+$2|	|	|	TOKEN_ACC|	TOKEN_AT_RI|	
    //ADD|	"A,#data"|	Add immediate data to Accumulator|	2|	12|	ARITHMETIC OPERATIONS|	0x24|	$2 |	|	TOKEN_ACC|	TOKEN_J_DATA|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_RN) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x28+m_tokens[2].num;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0x07& m_tokens[2].num;
    unsigned int cmp11=0x07;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0x07^(0x07>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_NUM) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x25;
    m_hex_text[1]=m_tokens[2].num ;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_AT_RI) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x26+m_tokens[2].num;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0x01& m_tokens[2].num;
    unsigned int cmp11=0x01;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0x01^(0x01>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_J_DATA) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x24;
    m_hex_text[1]=m_tokens[2].num ;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    

//unknown code
return -1;
}
int ADDC_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //ADDC|	"A,Rn"|	Add register to Accumulator with Carry|	1|	12|	ARITHMETIC OPERATIONS|	0x38+$2|	|	|	TOKEN_ACC|	TOKEN_RN|	
    //ADDC|	"A,direct"|	Add direct byte to Accumulator with Carry|	2|	12|	ARITHMETIC OPERATIONS|	0x35|	$2 |	|	TOKEN_ACC|	TOKEN_NUM|	
    //ADDC|	"A,@Ri"|	Add indirect RAM to Accumulator with Carry|	1|	12|	ARITHMETIC OPERATIONS|	0x36+$2|	|	|	TOKEN_ACC|	TOKEN_AT_RI|	
    //ADDC|	"A,#data"|	Add immediate data to Acc with Carry|	2|	12|	ARITHMETIC OPERATIONS|	0x34|	$2 |	|	TOKEN_ACC|	TOKEN_J_DATA|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_RN) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x38+m_tokens[2].num;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0x07& m_tokens[2].num;
    unsigned int cmp11=0x07;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0x07^(0x07>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_NUM) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x35;
    m_hex_text[1]=m_tokens[2].num ;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_AT_RI) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x36+m_tokens[2].num;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0x01& m_tokens[2].num;
    unsigned int cmp11=0x01;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0x01^(0x01>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_J_DATA) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x34;
    m_hex_text[1]=m_tokens[2].num ;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    

//unknown code
return -1;
}
int AJMP_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //AJMP|	addr11|	Absolute Jump|	2|	24|	PROGRAM BRANCHING|	(($1&0x700)>>3)+1|	$1&0xff|	|	TOKEN_KEYWORD|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_KEYWORD) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=((m_tokens[1].num&0x700)>>3)+1;
    m_hex_text[1]=m_tokens[1].num&0xff;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0x7ff& m_tokens[1].num;
    unsigned int cmp01=0x7ff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0x7ff^(0x7ff>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    return 0;
    }
    }
    

//unknown code
return -1;
}
int ANL_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //ANL|	"C,bit"|	AND direct bit to CARRY|	2|	24|	BOOLEAN VARIABLE MANIPULATION|	0x82|	$2 |	|	TOKEN_C|	TOKEN_NUM|	
    //ANL|	"C,/bit"|	AND complement of direct bit to Carry|	2|	24|	BOOLEAN VARIABLE MANIPULATION|	0xB0|	$2 |	|	TOKEN_C|	TOKEN_DIV_NUM|	
    //ANL|	"A,Rn"|	AND Register to Accumulator|	1|	12|	LOGICAL OPERATIONS|	0x58+$2|	|	|	TOKEN_ACC|	TOKEN_RN|	
    //ANL|	"A,direct"|	AND direct byte to Accumulator|	2|	12|	LOGICAL OPERATIONS|	0x55|	$2 |	|	TOKEN_ACC|	TOKEN_NUM|	
    //ANL|	"A,@Ri"|	AND indirect RAM to Accumulator|	1|	12|	LOGICAL OPERATIONS|	0x56+$2|	|	|	TOKEN_ACC|	TOKEN_AT_RI|	
    //ANL|	"A,#data"|	AND immediate data to Accumulator|	2|	12|	LOGICAL OPERATIONS|	0x54|	$2 |	|	TOKEN_ACC|	TOKEN_J_DATA|	
    //ANL|	"direct,A"|	AND Accumulator to direct byte|	2|	12|	LOGICAL OPERATIONS|	0x52|	$1 |	|	TOKEN_NUM|	TOKEN_ACC|	
    //ANL|	"direct,#data"|	AND immediate data to direct byte|	3|	24|	LOGICAL OPERATIONS|	0x53|	$1 |	$2|	TOKEN_NUM|	TOKEN_J_DATA|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_C)&&
    (m_tokens[2].type==TOKEN_NUM) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x82;
    m_hex_text[1]=m_tokens[2].num ;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_C)&&
    (m_tokens[2].type==TOKEN_DIV_NUM) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xB0;
    m_hex_text[1]=m_tokens[2].num ;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_RN) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x58+m_tokens[2].num;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0x07& m_tokens[2].num;
    unsigned int cmp11=0x07;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0x07^(0x07>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_NUM) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x55;
    m_hex_text[1]=m_tokens[2].num ;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_AT_RI) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x56+m_tokens[2].num;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0x01& m_tokens[2].num;
    unsigned int cmp11=0x01;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0x01^(0x01>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_J_DATA) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x54;
    m_hex_text[1]=m_tokens[2].num ;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_NUM)&&
    (m_tokens[2].type==TOKEN_ACC) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x52;
    m_hex_text[1]=m_tokens[1].num ;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0xff& m_tokens[1].num;
    unsigned int cmp01=0xff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xff^(0xff>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    //1--check ignore
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_NUM)&&
    (m_tokens[2].type==TOKEN_J_DATA) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(3);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x53;
    m_hex_text[1]=m_tokens[1].num ;
    m_hex_text[2]=m_tokens[2].num;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0xff& m_tokens[1].num;
    unsigned int cmp01=0xff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xff^(0xff>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    

//unknown code
return -1;
}
int CALL_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //CALL|	addr11|	Absolute Subroutine Call|	2|	24|	PROGRAM BRANCHING|	(($1&0x700)>>3)+0x11|	($1&0xff)|	|	TOKEN_KEYWORD|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_KEYWORD) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=((m_tokens[1].num&0x700)>>3)+0x11;
    m_hex_text[1]=(m_tokens[1].num&0xff);
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0x7ff& m_tokens[1].num;
    unsigned int cmp01=0x7ff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0x7ff^(0x7ff>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    return 0;
    }
    }
    

//unknown code
return -1;
}
int CJNE_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //CJNE|	"A,direct,rel"|	Compare direct byte to Acc and Jump if Not Equal|	3|	24|	PROGRAM BRANCHING|	0xB5|	$2 |	$3|	TOKEN_ACC|	TOKEN_NUM|	TOKEN_KEYWORD|	
    //CJNE|	"A,#data,rel"|	Compare immediate to Acc and Jump if Not Equal|	3|	24|	PROGRAM BRANCHING|	0xB4|	$2 |	$3|	TOKEN_ACC|	TOKEN_J_DATA|	TOKEN_KEYWORD|	
    //CJNE|	"Rn,#data,rel"|	Compare immediate to register and Jump if Not Equal|	3|	24|	PROGRAM BRANCHING|	0xB8+$1|	$2 |	$3|	TOKEN_RN|	TOKEN_J_DATA|	TOKEN_KEYWORD|	
    //CJNE|	"@Ri,#data,rel"|	Compare immediate to indirect and Jump if Not Equal|	3|	24|	PROGRAM BRANCHING|	0xB6+$1|	$2 |	$3|	TOKEN_AT_RI|	TOKEN_J_DATA|	TOKEN_KEYWORD|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==4)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_NUM)&&
    (m_tokens[3].type==TOKEN_KEYWORD) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(3);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xB5;
    m_hex_text[1]=m_tokens[2].num ;
    m_hex_text[2]=m_tokens[3].rel;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    //2--check
    unsigned int tcmp2= m_tokens[3].rel;
    unsigned int cmp20=0xff& m_tokens[3].rel;
    unsigned int cmp21=0xff;
    cmp21=~cmp21;
    cmp21=cmp21|cmp20;
    unsigned int cmp22=(0xff^(0xff>>1)) & cmp20  ;
    // 8bit sign check
     if ( ( m_tokens[3].rel>0)&&(cmp22)){return 2;}
    if(  (tcmp2!=cmp20)&&(!(cmp22&&(tcmp2==cmp21)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==4)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_J_DATA)&&
    (m_tokens[3].type==TOKEN_KEYWORD) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(3);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xB4;
    m_hex_text[1]=m_tokens[2].num ;
    m_hex_text[2]=m_tokens[3].rel;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    //2--check
    unsigned int tcmp2= m_tokens[3].rel;
    unsigned int cmp20=0xff& m_tokens[3].rel;
    unsigned int cmp21=0xff;
    cmp21=~cmp21;
    cmp21=cmp21|cmp20;
    unsigned int cmp22=(0xff^(0xff>>1)) & cmp20  ;
    // 8bit sign check
     if ( ( m_tokens[3].rel>0)&&(cmp22)){return 2;}
    if(  (tcmp2!=cmp20)&&(!(cmp22&&(tcmp2==cmp21)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==4)
    {
    if(     (m_tokens[1].type==TOKEN_RN)&&
    (m_tokens[2].type==TOKEN_J_DATA)&&
    (m_tokens[3].type==TOKEN_KEYWORD) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(3);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xB8+m_tokens[1].num;
    m_hex_text[1]=m_tokens[2].num ;
    m_hex_text[2]=m_tokens[3].rel;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0x07& m_tokens[1].num;
    unsigned int cmp01=0x07;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0x07^(0x07>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    //2--check
    unsigned int tcmp2= m_tokens[3].rel;
    unsigned int cmp20=0xff& m_tokens[3].rel;
    unsigned int cmp21=0xff;
    cmp21=~cmp21;
    cmp21=cmp21|cmp20;
    unsigned int cmp22=(0xff^(0xff>>1)) & cmp20  ;
    // 8bit sign check
     if ( ( m_tokens[3].rel>0)&&(cmp22)){return 2;}
    if(  (tcmp2!=cmp20)&&(!(cmp22&&(tcmp2==cmp21)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==4)
    {
    if(     (m_tokens[1].type==TOKEN_AT_RI)&&
    (m_tokens[2].type==TOKEN_J_DATA)&&
    (m_tokens[3].type==TOKEN_KEYWORD) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(3);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xB6+m_tokens[1].num;
    m_hex_text[1]=m_tokens[2].num ;
    m_hex_text[2]=m_tokens[3].rel;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0x01& m_tokens[1].num;
    unsigned int cmp01=0x01;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0x01^(0x01>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    //2--check
    unsigned int tcmp2= m_tokens[3].rel;
    unsigned int cmp20=0xff& m_tokens[3].rel;
    unsigned int cmp21=0xff;
    cmp21=~cmp21;
    cmp21=cmp21|cmp20;
    unsigned int cmp22=(0xff^(0xff>>1)) & cmp20  ;
    // 8bit sign check
     if ( ( m_tokens[3].rel>0)&&(cmp22)){return 2;}
    if(  (tcmp2!=cmp20)&&(!(cmp22&&(tcmp2==cmp21)))){ return 2; }
    return 0;
    }
    }
    

//unknown code
return -1;
}
int CLR_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //CLR|	C|	Clear Carry|	1|	12|	BOOLEAN VARIABLE MANIPULATION|	0xC3|	|	|	TOKEN_C|	
    //CLR|	bit|	Clear direct bit|	2|	12|	BOOLEAN VARIABLE MANIPULATION|	0xC2|	$1 |	|	TOKEN_NUM|	
    //CLR|	A|	Clear Accumulator|	1|	12|	LOGICAL OPERATIONS|	0xE4|	|	|	TOKEN_ACC|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_C) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xC3;
    //oprand range check
    //0--check ignore
    return 0;
    }
    }
    
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_NUM) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xC2;
    m_hex_text[1]=m_tokens[1].num ;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0xff& m_tokens[1].num;
    unsigned int cmp01=0xff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xff^(0xff>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_ACC) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xE4;
    //oprand range check
    //0--check ignore
    return 0;
    }
    }
    

//unknown code
return -1;
}
int CPL_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //CPL|	C|	Complement Carry|	1|	12|	BOOLEAN VARIABLE MANIPULATION|	0xB3|	|	|	TOKEN_C|	
    //CPL|	bit|	Complement direct bit|	2|	12|	BOOLEAN VARIABLE MANIPULATION|	0xB2|	$1 |	|	TOKEN_NUM|	
    //CPL|	A|	Complement Accumulator|	1|	12|	LOGICAL OPERATIONS|	0xF4|	|	|	TOKEN_ACC|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_C) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xB3;
    //oprand range check
    //0--check ignore
    return 0;
    }
    }
    
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_NUM) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xB2;
    m_hex_text[1]=m_tokens[1].num ;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0xff& m_tokens[1].num;
    unsigned int cmp01=0xff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xff^(0xff>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_ACC) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xF4;
    //oprand range check
    //0--check ignore
    return 0;
    }
    }
    

//unknown code
return -1;
}
int DA_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //DA|	A|	Decimal Adjust Accumulator|	1|	12|	ARITHMETIC OPERATIONS|	0xD4|	|	|	TOKEN_ACC|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_ACC) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xD4;
    //oprand range check
    //0--check ignore
    return 0;
    }
    }
    

//unknown code
return -1;
}
int DEC_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //DEC|	A|	Decrement Accumulator|	1|	12|	ARITHMETIC OPERATIONS|	0x14|	|	|	TOKEN_ACC|	
    //DEC|	Rn|	Decrement Register|	1|	12|	ARITHMETIC OPERATIONS|	0x18+$1|	|	|	TOKEN_RN|	
    //DEC|	direct|	Decrement direct byte|	2|	12|	ARITHMETIC OPERATIONS|	0x15|	$1 |	|	TOKEN_NUM|	
    //DEC|	@Ri|	Decrement indirect RAM|	1|	12|	ARITHMETIC OPERATIONS|	0x16+$1|	|	|	TOKEN_AT_RI|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_ACC) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x14;
    //oprand range check
    //0--check ignore
    return 0;
    }
    }
    
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_RN) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x18+m_tokens[1].num;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0x07& m_tokens[1].num;
    unsigned int cmp01=0x07;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0x07^(0x07>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_NUM) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x15;
    m_hex_text[1]=m_tokens[1].num ;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0xff& m_tokens[1].num;
    unsigned int cmp01=0xff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xff^(0xff>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_AT_RI) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x16+m_tokens[1].num;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0x01& m_tokens[1].num;
    unsigned int cmp01=0x01;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0x01^(0x01>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    return 0;
    }
    }
    

//unknown code
return -1;
}
int DIV_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //DIV|	AB|	Divide A by B|	1|	48|	ARITHMETIC OPERATIONS|	0x84|	|	|	TOKEN_AB|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_AB) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=48;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x84;
    //oprand range check
    //0--check ignore
    return 0;
    }
    }
    

//unknown code
return -1;
}
int DJNZ_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //DJNZ|	"Rn,rel"|	Decrement register and Jump if Not Zero|	2|	24|	PROGRAM BRANCHING|	0xD8+$1|	$2 |	|	TOKEN_RN|	TOKEN_KEYWORD|	
    //DJNZ|	"direct,rel"|	Decrement direct byte and Jump if Not Zero|	3|	24|	PROGRAM BRANCHING|	0xD5|	$1 |	$2|	TOKEN_NUM|	TOKEN_KEYWORD|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_RN)&&
    (m_tokens[2].type==TOKEN_KEYWORD) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xD8+m_tokens[1].num;
    m_hex_text[1]=m_tokens[2].rel ;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0x07& m_tokens[1].num;
    unsigned int cmp01=0x07;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0x07^(0x07>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    //1--check
    unsigned int tcmp1= m_tokens[2].rel;
    unsigned int cmp10=0xff& m_tokens[2].rel;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    // 8bit sign check
     if ( ( m_tokens[2].rel>0)&&(cmp12)){return 2;}
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_NUM)&&
    (m_tokens[2].type==TOKEN_KEYWORD) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(3);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xD5;
    m_hex_text[1]=m_tokens[1].num ;
    m_hex_text[2]=m_tokens[2].rel;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0xff& m_tokens[1].num;
    unsigned int cmp01=0xff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xff^(0xff>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    //1--check
    unsigned int tcmp1= m_tokens[2].rel;
    unsigned int cmp10=0xff& m_tokens[2].rel;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    // 8bit sign check
     if ( ( m_tokens[2].rel>0)&&(cmp12)){return 2;}
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    

//unknown code
return -1;
}
int INC_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //INC|	A|	Increment Accumulator|	1|	12|	ARITHMETIC OPERATIONS|	0x04|	|	|	TOKEN_ACC|	
    //INC|	Rn|	Increment register|	1|	12|	ARITHMETIC OPERATIONS|	0x08+$1|	|	|	TOKEN_RN|	
    //INC|	direct|	Increment direct byte|	2|	12|	ARITHMETIC OPERATIONS|	0x05|	$1 |	|	TOKEN_NUM|	
    //INC|	@Ri|	Increment direct RAM|	1|	12|	ARITHMETIC OPERATIONS|	0x06+$1|	|	|	TOKEN_AT_RI|	
    //INC|	DPTR|	Increment Data Pointer|	1|	24|	ARITHMETIC OPERATIONS|	0xA3|	|	|	TOKEN_DPTR|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_ACC) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x04;
    //oprand range check
    //0--check ignore
    return 0;
    }
    }
    
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_RN) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x08+m_tokens[1].num;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0x07& m_tokens[1].num;
    unsigned int cmp01=0x07;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0x07^(0x07>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_NUM) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x05;
    m_hex_text[1]=m_tokens[1].num ;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0xff& m_tokens[1].num;
    unsigned int cmp01=0xff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xff^(0xff>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_AT_RI) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x06+m_tokens[1].num;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0x01& m_tokens[1].num;
    unsigned int cmp01=0x01;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0x01^(0x01>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_DPTR) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xA3;
    //oprand range check
    //0--check ignore
    return 0;
    }
    }
    

//unknown code
return -1;
}
int JB_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //JB|	"bit,rel"|	Jump if direct Bit is set|	3|	24|	BOOLEAN VARIABLE MANIPULATION|	0x20|	$1 |	$2|	TOKEN_NUM|	TOKEN_KEYWORD|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_NUM)&&
    (m_tokens[2].type==TOKEN_KEYWORD) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(3);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x20;
    m_hex_text[1]=m_tokens[1].num ;
    m_hex_text[2]=m_tokens[2].rel;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0xff& m_tokens[1].num;
    unsigned int cmp01=0xff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xff^(0xff>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    //1--check
    unsigned int tcmp1= m_tokens[2].rel;
    unsigned int cmp10=0xff& m_tokens[2].rel;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    // 8bit sign check
     if ( ( m_tokens[2].rel>0)&&(cmp12)){return 2;}
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    

//unknown code
return -1;
}
int JBC_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //JBC|	"bit,rel"|	Jump if direct Bit is set & clear bit|	3|	24|	BOOLEAN VARIABLE MANIPULATION|	0x10|	$1 |	$2|	TOKEN_NUM|	TOKEN_KEYWORD|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_NUM)&&
    (m_tokens[2].type==TOKEN_KEYWORD) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(3);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x10;
    m_hex_text[1]=m_tokens[1].num ;
    m_hex_text[2]=m_tokens[2].rel;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0xff& m_tokens[1].num;
    unsigned int cmp01=0xff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xff^(0xff>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    //1--check
    unsigned int tcmp1= m_tokens[2].rel;
    unsigned int cmp10=0xff& m_tokens[2].rel;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    // 8bit sign check
     if ( ( m_tokens[2].rel>0)&&(cmp12)){return 2;}
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    

//unknown code
return -1;
}
int JC_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //JC|	rel|	Jump if Carry is set|	2|	24|	BOOLEAN VARIABLE MANIPULATION|	0x40|	$1 |	|	TOKEN_KEYWORD|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_KEYWORD) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x40;
    m_hex_text[1]=m_tokens[1].rel ;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].rel;
    unsigned int cmp00=0xff& m_tokens[1].rel;
    unsigned int cmp01=0xff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xff^(0xff>>1)) & cmp00  ;
    // 8bit sign check
     if ( ( m_tokens[1].rel>0)&&(cmp02)){return 2;}
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    return 0;
    }
    }
    

//unknown code
return -1;
}
int JMP_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //JMP|	@A+DPTR|	Jump indirect relative to the DPTR|	1|	24|	PROGRAM BRANCHING|	0x73|	|	|	TOKEN_AT_A_PLUS_DPTR|	
    //JMP|	rel|	Short Jump (relative addr)|	2|	24|	PROGRAM BRANCHING|	0x80|	$1 |	|	TOKEN_KEYWORD|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_AT_A_PLUS_DPTR) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x73;
    //oprand range check
    //0--check ignore
    return 0;
    }
    }
    
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_KEYWORD) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x80;
    m_hex_text[1]=m_tokens[1].rel ;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].rel;
    unsigned int cmp00=0xff& m_tokens[1].rel;
    unsigned int cmp01=0xff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xff^(0xff>>1)) & cmp00  ;
    // 8bit sign check
     if ( ( m_tokens[1].rel>0)&&(cmp02)){return 2;}
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    return 0;
    }
    }
    

//unknown code
return -1;
}
int JNB_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //JNB|	"bit,rel"|	Jump if direct Bit is Not set|	3|	24|	BOOLEAN VARIABLE MANIPULATION|	0x30|	$1 |	$2|	TOKEN_NUM|	TOKEN_KEYWORD|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_NUM)&&
    (m_tokens[2].type==TOKEN_KEYWORD) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(3);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x30;
    m_hex_text[1]=m_tokens[1].num ;
    m_hex_text[2]=m_tokens[2].rel;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0xff& m_tokens[1].num;
    unsigned int cmp01=0xff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xff^(0xff>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    //1--check
    unsigned int tcmp1= m_tokens[2].rel;
    unsigned int cmp10=0xff& m_tokens[2].rel;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    // 8bit sign check
     if ( ( m_tokens[2].rel>0)&&(cmp12)){return 2;}
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    

//unknown code
return -1;
}
int JNC_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //JNC|	rel|	Jump if Carry not set|	2|	24|	BOOLEAN VARIABLE MANIPULATION|	0x50|	$1 |	|	TOKEN_KEYWORD|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_KEYWORD) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x50;
    m_hex_text[1]=m_tokens[1].rel ;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].rel;
    unsigned int cmp00=0xff& m_tokens[1].rel;
    unsigned int cmp01=0xff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xff^(0xff>>1)) & cmp00  ;
    // 8bit sign check
     if ( ( m_tokens[1].rel>0)&&(cmp02)){return 2;}
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    return 0;
    }
    }
    

//unknown code
return -1;
}
int JNZ_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //JNZ|	rel|	Jump if Accumulator is Not Zero|	2|	24|	PROGRAM BRANCHING|	0x70|	$1 |	|	TOKEN_KEYWORD|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_KEYWORD) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x70;
    m_hex_text[1]=m_tokens[1].rel ;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].rel;
    unsigned int cmp00=0xff& m_tokens[1].rel;
    unsigned int cmp01=0xff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xff^(0xff>>1)) & cmp00  ;
    // 8bit sign check
     if ( ( m_tokens[1].rel>0)&&(cmp02)){return 2;}
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    return 0;
    }
    }
    

//unknown code
return -1;
}
int JZ_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //JZ|	rel|	Jump if Accumulator is Zero|	2|	24|	PROGRAM BRANCHING|	0x60|	$1 |	|	TOKEN_KEYWORD|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_KEYWORD) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x60;
    m_hex_text[1]=m_tokens[1].rel ;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].rel;
    unsigned int cmp00=0xff& m_tokens[1].rel;
    unsigned int cmp01=0xff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xff^(0xff>>1)) & cmp00  ;
    // 8bit sign check
     if ( ( m_tokens[1].rel>0)&&(cmp02)){return 2;}
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    return 0;
    }
    }
    

//unknown code
return -1;
}
int LCALL_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //LCALL|	addr16|	Long Subroutine Call|	3|	24|	PROGRAM BRANCHING|	0x12|	($1 &0xff00)>>8|	($1 &0xff)|	TOKEN_KEYWORD|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_KEYWORD) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(3);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x12;
    m_hex_text[1]=(m_tokens[1].num &0xff00)>>8;
    m_hex_text[2]=(m_tokens[1].num &0xff);
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0xffff& m_tokens[1].num;
    unsigned int cmp01=0xffff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xffff^(0xffff>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    return 0;
    }
    }
    

//unknown code
return -1;
}
int LJMP_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //LJMP|	addr16|	Long Jump|	3|	24|	PROGRAM BRANCHING|	0x02|	($1 &0xff00)>>8|	($1 &0xff)|	TOKEN_KEYWORD|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_KEYWORD) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(3);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x02;
    m_hex_text[1]=(m_tokens[1].num &0xff00)>>8;
    m_hex_text[2]=(m_tokens[1].num &0xff);
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0xffff& m_tokens[1].num;
    unsigned int cmp01=0xffff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xffff^(0xffff>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    return 0;
    }
    }
    

//unknown code
return -1;
}
int MOV_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //MOV|	"C,bit"|	Move direct bit to Carry|	2|	12|	BOOLEAN VARIABLE MANIPULATION|	0xA2|	$2 |	|	TOKEN_C|	TOKEN_NUM|	
    //MOV|	"bit,C"|	Move Carry to direct bit|	2|	24|	BOOLEAN VARIABLE MANIPULATION|	0x92|	$1 |	|	TOKEN_NUM|	TOKEN_C|	
    //MOV|	"A,Rn"|	Move register to Accumulator|	1|	12|	DATA TRANSFER|	0xe8+$2|	|	|	TOKEN_ACC|	TOKEN_RN|	
    //MOV|	"A,direct"|	Move direct byte to Accumulator|	2|	12|	DATA TRANSFER|	0xe5|	$2 |	|	TOKEN_ACC|	TOKEN_NUM|	
    //MOV|	"A,@Ri"|	Move indirect RAM to Accumulator|	1|	12|	DATA TRANSFER|	0xe6+$2|	|	|	TOKEN_ACC|	TOKEN_AT_RI|	
    //MOV|	"A,#data"|	Move immediate data to Accumulator|	2|	12|	DATA TRANSFER|	0x74|	$2 |	|	TOKEN_ACC|	TOKEN_J_DATA|	
    //MOV|	"Rn,A"|	Move Accumulator to register|	1|	12|	DATA TRANSFER|	0xF8+$1|	|	|	TOKEN_RN|	TOKEN_ACC|	
    //MOV|	"Rn,direct"|	Move direct byte to register|	2|	24|	DATA TRANSFER|	0xA8+$1|	$2 |	|	TOKEN_RN|	TOKEN_NUM|	
    //MOV|	"Rn,#data"|	Move immediate data to register|	2|	12|	DATA TRANSFER|	0x78+$1|	$2 |	|	TOKEN_RN|	TOKEN_J_DATA|	
    //MOV|	"direct,A"|	Move Accumulator to direct byte|	2|	12|	DATA TRANSFER|	0xF5|	$1 |	|	TOKEN_NUM|	TOKEN_ACC|	
    //MOV|	"direct,Rn"|	Move register to direct byte|	2|	24|	DATA TRANSFER|	0x88+$2|	$1 |	|	TOKEN_NUM|	TOKEN_RN|	
    //MOV|	"direct,direct"|	Move direct byte to direct|	3|	24|	DATA TRANSFER|	0x85|	$2 |	$1|	TOKEN_NUM|	TOKEN_NUM|	
    //MOV|	"direct,@Ri"|	Move indirect RAM to direct byte|	2|	24|	DATA TRANSFER|	0x86+$2|	$1 |	|	TOKEN_NUM|	TOKEN_AT_RI|	
    //MOV|	"direct,#data"|	Move immediate data to direct byte|	3|	24|	DATA TRANSFER|	0x75|	$1 |	$2|	TOKEN_NUM|	TOKEN_J_DATA|	
    //MOV|	"@Ri,A"|	Move Accumulator to indirect RAM|	1|	12|	DATA TRANSFER|	0xF6+$1|	|	|	TOKEN_AT_RI|	TOKEN_ACC|	
    //MOV|	"@Ri,direct"|	Move direct byte to indirect RAM|	2|	24|	DATA TRANSFER|	0xA6+$1|	$2 |	|	TOKEN_AT_RI|	TOKEN_NUM|	
    //MOV|	"@Ri,#data"|	Move immediate data to indirect RAM|	2|	12|	DATA TRANSFER|	0x76+$1|	$2 |	|	TOKEN_AT_RI|	TOKEN_J_DATA|	
    //MOV|	"DPTR,#data16"|	Load Data Pointer with a 16-bit constant|	3|	24|	DATA TRANSFER|	0x90|	($2 &0xff00)>>8|	($2 &0xff)|	TOKEN_DPTR|	TOKEN_J_DATA|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_C)&&
    (m_tokens[2].type==TOKEN_NUM) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xA2;
    m_hex_text[1]=m_tokens[2].num ;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_NUM)&&
    (m_tokens[2].type==TOKEN_C) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x92;
    m_hex_text[1]=m_tokens[1].num ;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0xff& m_tokens[1].num;
    unsigned int cmp01=0xff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xff^(0xff>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    //1--check ignore
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_RN) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xe8+m_tokens[2].num;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0x07& m_tokens[2].num;
    unsigned int cmp11=0x07;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0x07^(0x07>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_NUM) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xe5;
    m_hex_text[1]=m_tokens[2].num ;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_AT_RI) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xe6+m_tokens[2].num;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0x01& m_tokens[2].num;
    unsigned int cmp11=0x01;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0x01^(0x01>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_J_DATA) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x74;
    m_hex_text[1]=m_tokens[2].num ;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_RN)&&
    (m_tokens[2].type==TOKEN_ACC) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xF8+m_tokens[1].num;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0x07& m_tokens[1].num;
    unsigned int cmp01=0x07;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0x07^(0x07>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    //1--check ignore
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_RN)&&
    (m_tokens[2].type==TOKEN_NUM) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xA8+m_tokens[1].num;
    m_hex_text[1]=m_tokens[2].num ;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0x07& m_tokens[1].num;
    unsigned int cmp01=0x07;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0x07^(0x07>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_RN)&&
    (m_tokens[2].type==TOKEN_J_DATA) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x78+m_tokens[1].num;
    m_hex_text[1]=m_tokens[2].num ;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0x07& m_tokens[1].num;
    unsigned int cmp01=0x07;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0x07^(0x07>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_NUM)&&
    (m_tokens[2].type==TOKEN_ACC) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xF5;
    m_hex_text[1]=m_tokens[1].num ;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0xff& m_tokens[1].num;
    unsigned int cmp01=0xff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xff^(0xff>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    //1--check ignore
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_NUM)&&
    (m_tokens[2].type==TOKEN_RN) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x88+m_tokens[2].num;
    m_hex_text[1]=m_tokens[1].num ;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0xff& m_tokens[1].num;
    unsigned int cmp01=0xff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xff^(0xff>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0x07& m_tokens[2].num;
    unsigned int cmp11=0x07;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0x07^(0x07>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_NUM)&&
    (m_tokens[2].type==TOKEN_NUM) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(3);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x85;
    m_hex_text[1]=m_tokens[2].num ;
    m_hex_text[2]=m_tokens[1].num;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0xff& m_tokens[1].num;
    unsigned int cmp01=0xff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xff^(0xff>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_NUM)&&
    (m_tokens[2].type==TOKEN_AT_RI) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x86+m_tokens[2].num;
    m_hex_text[1]=m_tokens[1].num ;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0xff& m_tokens[1].num;
    unsigned int cmp01=0xff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xff^(0xff>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0x01& m_tokens[2].num;
    unsigned int cmp11=0x01;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0x01^(0x01>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_NUM)&&
    (m_tokens[2].type==TOKEN_J_DATA) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(3);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x75;
    m_hex_text[1]=m_tokens[1].num ;
    m_hex_text[2]=m_tokens[2].num;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0xff& m_tokens[1].num;
    unsigned int cmp01=0xff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xff^(0xff>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_AT_RI)&&
    (m_tokens[2].type==TOKEN_ACC) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xF6+m_tokens[1].num;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0x01& m_tokens[1].num;
    unsigned int cmp01=0x01;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0x01^(0x01>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    //1--check ignore
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_AT_RI)&&
    (m_tokens[2].type==TOKEN_NUM) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xA6+m_tokens[1].num;
    m_hex_text[1]=m_tokens[2].num ;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0x01& m_tokens[1].num;
    unsigned int cmp01=0x01;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0x01^(0x01>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_AT_RI)&&
    (m_tokens[2].type==TOKEN_J_DATA) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x76+m_tokens[1].num;
    m_hex_text[1]=m_tokens[2].num ;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0x01& m_tokens[1].num;
    unsigned int cmp01=0x01;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0x01^(0x01>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_DPTR)&&
    (m_tokens[2].type==TOKEN_J_DATA) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(3);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x90;
    m_hex_text[1]=(m_tokens[2].num &0xff00)>>8;
    m_hex_text[2]=(m_tokens[2].num &0xff);
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xffff& m_tokens[2].num;
    unsigned int cmp11=0xffff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xffff^(0xffff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    

//unknown code
return -1;
}
int MOVC_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //MOVC|	"A,@A+DPTR"|	Move Code byte relative to DPTR to Acc|	1|	24|	DATA TRANSFER|	0x93|	|	|	TOKEN_ACC|	TOKEN_AT_A_PLUS_DPTR|	
    //MOVC|	"A,@A+PC"|	Move Code byte relative to PC to Acc|	1|	24|	DATA TRANSFER|	0x83|	|	|	TOKEN_ACC|	TOKEN_AT_A_PLUS_PC|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_AT_A_PLUS_DPTR) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x93;
    //oprand range check
    //0--check ignore
    //1--check ignore
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_AT_A_PLUS_PC) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x83;
    //oprand range check
    //0--check ignore
    //1--check ignore
    return 0;
    }
    }
    

//unknown code
return -1;
}
int MOVX_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //MOVX|	"A,@Ri"|	Move External RAM (8- bit addr) to Acc|	1|	24|	DATA TRANSFER|	0xe2+$2|	|	|	TOKEN_ACC|	TOKEN_AT_RI|	
    //MOVX|	"A,@DPTR"|	Move Exernal RAM (16- bit addr) to Acc|	1|	24|	DATA TRANSFER|	0xe0|	|	|	TOKEN_ACC|	TOKEN_AT_DPTR|	
    //MOVX|	"@Ri,A"|	Move Acc to External RAM (8-bit addr)|	1|	24|	DATA TRANSFER|	0xf2+$1|	|	|	TOKEN_AT_RI|	TOKEN_ACC|	
    //MOVX|	"@DPTR,A"|	Move Acc to External RAM (16-bit addr)|	1|	24|	DATA TRANSFER|	0xf0|	|	|	TOKEN_AT_DPTR|	TOKEN_ACC|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_AT_RI) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xe2+m_tokens[2].num;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0x01& m_tokens[2].num;
    unsigned int cmp11=0x01;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0x01^(0x01>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_AT_DPTR) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xe0;
    //oprand range check
    //0--check ignore
    //1--check ignore
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_AT_RI)&&
    (m_tokens[2].type==TOKEN_ACC) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xf2+m_tokens[1].num;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0x01& m_tokens[1].num;
    unsigned int cmp01=0x01;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0x01^(0x01>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    //1--check ignore
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_AT_DPTR)&&
    (m_tokens[2].type==TOKEN_ACC) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xf0;
    //oprand range check
    //0--check ignore
    //1--check ignore
    return 0;
    }
    }
    

//unknown code
return -1;
}
int MUL_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //MUL|	AB|	Multiply A & B|	1|	48|	ARITHMETIC OPERATIONS|	0xA4|	|	|	TOKEN_AB|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_AB) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=48;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xA4;
    //oprand range check
    //0--check ignore
    return 0;
    }
    }
    

//unknown code
return -1;
}
int NOP_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //NOP|	|	No Operation|	1|	12|	PROGRAM BRANCHING|	0x00|	|	|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==1)
    {
    if( 1 )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x00;
    //oprand range check
    return 0;
    }
    }
    

//unknown code
return -1;
}
int ORL_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //ORL|	"C,bit"|	OR direct bit to Carry|	2|	24|	BOOLEAN VARIABLE MANIPULATION|	0x72|	$2 |	|	TOKEN_C|	TOKEN_NUM|	
    //ORL|	"C,/bit"|	OR complement of direct bit to Carry|	2|	24|	BOOLEAN VARIABLE MANIPULATION|	0xA0|	$2 |	|	TOKEN_C|	TOKEN_DIV_NUM|	
    //ORL|	"A,Rn"|	OR register to Accumulator|	1|	12|	LOGICAL OPERATIONS|	0x48+$2|	|	|	TOKEN_ACC|	TOKEN_RN|	
    //ORL|	"A,direct"|	OR direct byte to Accumulator|	2|	12|	LOGICAL OPERATIONS|	0x45|	$2 |	|	TOKEN_ACC|	TOKEN_NUM|	
    //ORL|	"A,@Ri"|	OR indirect RAM to Accumulator|	1|	12|	LOGICAL OPERATIONS|	0x46+$2|	|	|	TOKEN_ACC|	TOKEN_AT_RI|	
    //ORL|	"A,#data"|	OR immediate data to Accumulator|	2|	12|	LOGICAL OPERATIONS|	0x44|	$2 |	|	TOKEN_ACC|	TOKEN_J_DATA|	
    //ORL|	"direct,A"|	OR Accumulator to direct byte|	2|	12|	LOGICAL OPERATIONS|	0x42|	$1 |	|	TOKEN_NUM|	TOKEN_ACC|	
    //ORL|	"direct,#data"|	OR immediate data to direct byte|	3|	24|	LOGICAL OPERATIONS|	0x43|	$1 |	$2|	TOKEN_NUM|	TOKEN_J_DATA|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_C)&&
    (m_tokens[2].type==TOKEN_NUM) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x72;
    m_hex_text[1]=m_tokens[2].num ;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_C)&&
    (m_tokens[2].type==TOKEN_DIV_NUM) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xA0;
    m_hex_text[1]=m_tokens[2].num ;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_RN) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x48+m_tokens[2].num;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0x07& m_tokens[2].num;
    unsigned int cmp11=0x07;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0x07^(0x07>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_NUM) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x45;
    m_hex_text[1]=m_tokens[2].num ;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_AT_RI) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x46+m_tokens[2].num;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0x01& m_tokens[2].num;
    unsigned int cmp11=0x01;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0x01^(0x01>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_J_DATA) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x44;
    m_hex_text[1]=m_tokens[2].num ;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_NUM)&&
    (m_tokens[2].type==TOKEN_ACC) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x42;
    m_hex_text[1]=m_tokens[1].num ;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0xff& m_tokens[1].num;
    unsigned int cmp01=0xff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xff^(0xff>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    //1--check ignore
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_NUM)&&
    (m_tokens[2].type==TOKEN_J_DATA) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(3);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x43;
    m_hex_text[1]=m_tokens[1].num ;
    m_hex_text[2]=m_tokens[2].num;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0xff& m_tokens[1].num;
    unsigned int cmp01=0xff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xff^(0xff>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    

//unknown code
return -1;
}
int POP_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //POP|	direct|	Pop direct byte from stack|	2|	24|	DATA TRANSFER|	0xD0|	$1 |	|	TOKEN_NUM|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_NUM) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xD0;
    m_hex_text[1]=m_tokens[1].num ;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0xff& m_tokens[1].num;
    unsigned int cmp01=0xff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xff^(0xff>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    return 0;
    }
    }
    

//unknown code
return -1;
}
int PUSH_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //PUSH|	direct|	Push direct byte onto stack|	2|	24|	DATA TRANSFER|	0xC0|	$1 |	|	TOKEN_NUM|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_NUM) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xC0;
    m_hex_text[1]=m_tokens[1].num ;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0xff& m_tokens[1].num;
    unsigned int cmp01=0xff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xff^(0xff>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    return 0;
    }
    }
    

//unknown code
return -1;
}
int RET_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //RET|	|	Return from Subroutine|	1|	24|	PROGRAM BRANCHING|	0x22|	|	|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==1)
    {
    if( 1 )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x22;
    //oprand range check
    return 0;
    }
    }
    

//unknown code
return -1;
}
int RETI_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //RETI|	|	Return from interrupt|	1|	24|	PROGRAM BRANCHING|	0x32|	|	|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==1)
    {
    if( 1 )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x32;
    //oprand range check
    return 0;
    }
    }
    

//unknown code
return -1;
}
int RL_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //RL|	A|	Rotate Accumulator Left|	1|	12|	LOGICAL OPERATIONS|	0x23|	|	|	TOKEN_ACC|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_ACC) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x23;
    //oprand range check
    //0--check ignore
    return 0;
    }
    }
    

//unknown code
return -1;
}
int RLC_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //RLC|	A|	Rotate Accumulator Left through the Carry|	1|	12|	LOGICAL OPERATIONS|	0x33|	|	|	TOKEN_ACC|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_ACC) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x33;
    //oprand range check
    //0--check ignore
    return 0;
    }
    }
    

//unknown code
return -1;
}
int RR_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //RR|	A|	Rotate Accumulator Right|	1|	12|	LOGICAL OPERATIONS|	0x03|	|	|	TOKEN_ACC|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_ACC) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x03;
    //oprand range check
    //0--check ignore
    return 0;
    }
    }
    

//unknown code
return -1;
}
int RRC_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //RRC|	A|	Rotate Accumulator Right through the Carry|	1|	12|	LOGICAL OPERATIONS|	0x13|	|	|	TOKEN_ACC|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_ACC) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x13;
    //oprand range check
    //0--check ignore
    return 0;
    }
    }
    

//unknown code
return -1;
}
int SETB_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //SETB|	C|	Set Carry|	1|	12|	BOOLEAN VARIABLE MANIPULATION|	0xD3|	|	|	TOKEN_C|	
    //SETB|	bit|	Set direct bit|	2|	12|	BOOLEAN VARIABLE MANIPULATION|	0xD2|	$1 |	|	TOKEN_NUM|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_C) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xD3;
    //oprand range check
    //0--check ignore
    return 0;
    }
    }
    
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_NUM) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xD2;
    m_hex_text[1]=m_tokens[1].num ;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0xff& m_tokens[1].num;
    unsigned int cmp01=0xff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xff^(0xff>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    return 0;
    }
    }
    

//unknown code
return -1;
}
int SIMTRAP_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //SIMTRAP|	"direct,direct"|	A5 test A if not zero|	3|	12|	TEST|	0xA5|	$1 |	$2|	TOKEN_NUM|	TOKEN_NUM|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_NUM)&&
    (m_tokens[2].type==TOKEN_NUM) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(3);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xA5;
    m_hex_text[1]=m_tokens[1].num ;
    m_hex_text[2]=m_tokens[2].num;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0xff& m_tokens[1].num;
    unsigned int cmp01=0xff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xff^(0xff>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    

//unknown code
return -1;
}
int SJMP_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //SJMP|	rel|	Short Jump (relative addr)|	2|	24|	PROGRAM BRANCHING|	0x80|	$1 |	|	TOKEN_KEYWORD|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_KEYWORD) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x80;
    m_hex_text[1]=m_tokens[1].rel ;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].rel;
    unsigned int cmp00=0xff& m_tokens[1].rel;
    unsigned int cmp01=0xff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xff^(0xff>>1)) & cmp00  ;
    // 8bit sign check
     if ( ( m_tokens[1].rel>0)&&(cmp02)){return 2;}
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    return 0;
    }
    }
    

//unknown code
return -1;
}
int SUBB_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //SUBB|	"A,Rn"|	Subtract Register from Acc with borrow|	1|	12|	ARITHMETIC OPERATIONS|	0x98+$2|	|	|	TOKEN_ACC|	TOKEN_RN|	
    //SUBB|	"A,direct"|	Subtract direct byte from Acc with borrow|	2|	12|	ARITHMETIC OPERATIONS|	0x95|	$2 |	|	TOKEN_ACC|	TOKEN_NUM|	
    //SUBB|	"A,@Ri"|	Subtract indirect RAM from ACC with borrow|	1|	12|	ARITHMETIC OPERATIONS|	0x96+$2|	|	|	TOKEN_ACC|	TOKEN_AT_RI|	
    //SUBB|	"A,#data"|	Subtract immediate data from Acc with borrow|	2|	12|	ARITHMETIC OPERATIONS|	0x94|	$2 |	|	TOKEN_ACC|	TOKEN_J_DATA|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_RN) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x98+m_tokens[2].num;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0x07& m_tokens[2].num;
    unsigned int cmp11=0x07;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0x07^(0x07>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_NUM) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x95;
    m_hex_text[1]=m_tokens[2].num ;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_AT_RI) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x96+m_tokens[2].num;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0x01& m_tokens[2].num;
    unsigned int cmp11=0x01;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0x01^(0x01>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_J_DATA) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x94;
    m_hex_text[1]=m_tokens[2].num ;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    

//unknown code
return -1;
}
int SWAP_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //SWAP|	A|	Swap nibbles within the Accumulator|	1|	12|	LOGICAL OPERATIONS|	0xC4|	|	|	TOKEN_ACC|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==2)
    {
    if(     (m_tokens[1].type==TOKEN_ACC) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xC4;
    //oprand range check
    //0--check ignore
    return 0;
    }
    }
    

//unknown code
return -1;
}
int XCH_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //XCH|	"A,Rn"|	Exchange register with Accumulator|	1|	12|	DATA TRANSFER|	0xC8+$2|	|	|	TOKEN_ACC|	TOKEN_RN|	
    //XCH|	"A,direct"|	Exchange direct byte with Accumulator|	2|	12|	DATA TRANSFER|	0xC5|	$2 |	|	TOKEN_ACC|	TOKEN_NUM|	
    //XCH|	"A,@Ri"|	Exchange indirect RAM with Accumulator|	1|	12|	DATA TRANSFER|	0xC6+$2|	|	|	TOKEN_ACC|	TOKEN_AT_RI|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_RN) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xC8+m_tokens[2].num;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0x07& m_tokens[2].num;
    unsigned int cmp11=0x07;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0x07^(0x07>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_NUM) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xC5;
    m_hex_text[1]=m_tokens[2].num ;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_AT_RI) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xC6+m_tokens[2].num;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0x01& m_tokens[2].num;
    unsigned int cmp11=0x01;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0x01^(0x01>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    

//unknown code
return -1;
}
int XCHD_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //XCHD|	"A,@Ri"|	Exchange low-order Digit indirect RAM with Acc|	1|	12|	DATA TRANSFER|	0xD6+$2|	|	|	TOKEN_ACC|	TOKEN_AT_RI|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_AT_RI) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0xD6+m_tokens[2].num;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0x01& m_tokens[2].num;
    unsigned int cmp11=0x01;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0x01^(0x01>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    

//unknown code
return -1;
}
int XRL_CodeGen(T_ASM_CONTEXT *mCtx)
{
    //Mnemonic|	Operands|	Description|	Byte|	Oscillator Period|	Class|	BYTE0|	BYTE1|	BYTE2|	PARAM_TOKEN0|	PARAM_TOKEN1|	PARAM_TOKEN2|	PARAM_TOKEN3|	    
    //XRL|	"A,Rn"|	Exclusive-OR register to Accumulator|	1|	12|	LOGICAL OPERATIONS|	0x68+$2|	|	|	TOKEN_ACC|	TOKEN_RN|	
    //XRL|	"A,direct"|	Exclusive-OR direct byte to Accumulator|	2|	12|	LOGICAL OPERATIONS|	0x65|	$2 |	|	TOKEN_ACC|	TOKEN_NUM|	
    //XRL|	"A,@Ri"|	Exclusive-OR indirect RAM to Accumulator|	1|	12|	LOGICAL OPERATIONS|	0x66+$2|	|	|	TOKEN_ACC|	TOKEN_AT_RI|	
    //XRL|	"A,#data"|	Exclusive-OR immediate data to Accumulator|	2|	12|	LOGICAL OPERATIONS|	0x64|	$2 |	|	TOKEN_ACC|	TOKEN_J_DATA|	
    //XRL|	"direct,A"|	Exclusive-OR Accumulator to direct byte|	2|	12|	LOGICAL OPERATIONS|	0x62|	$1 |	|	TOKEN_NUM|	TOKEN_ACC|	
    //XRL|	"direct,#data"|	Exclusive-OR immediate data to direct byte|	3|	24|	LOGICAL OPERATIONS|	0x63|	$1 |	$2|	TOKEN_NUM|	TOKEN_J_DATA|	
    std::vector<asm_token> &m_tokens = mCtx->m_current_block.m_tokens;
    std::string &m_hex_text = mCtx->m_current_block.m_hex_text;
    int &m_current_line_oscillator_period = mCtx->m_current_block.m_current_line_oscillator_period;
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_RN) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x68+m_tokens[2].num;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0x07& m_tokens[2].num;
    unsigned int cmp11=0x07;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0x07^(0x07>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_NUM) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x65;
    m_hex_text[1]=m_tokens[2].num ;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_AT_RI) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(1);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x66+m_tokens[2].num;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0x01& m_tokens[2].num;
    unsigned int cmp11=0x01;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0x01^(0x01>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_ACC)&&
    (m_tokens[2].type==TOKEN_J_DATA) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x64;
    m_hex_text[1]=m_tokens[2].num ;
    //oprand range check
    //0--check ignore
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_NUM)&&
    (m_tokens[2].type==TOKEN_ACC) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(2);
    m_current_line_oscillator_period=12;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x62;
    m_hex_text[1]=m_tokens[1].num ;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0xff& m_tokens[1].num;
    unsigned int cmp01=0xff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xff^(0xff>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    //1--check ignore
    return 0;
    }
    }
    
    if(m_tokens.size()==3)
    {
    if(     (m_tokens[1].type==TOKEN_NUM)&&
    (m_tokens[2].type==TOKEN_J_DATA) )
    {
    //set hex size & inst-circle
    m_hex_text.resize(3);
    m_current_line_oscillator_period=24;
    //OUTPUT:m_hex_text
    //INPUT:m_tokens
    m_hex_text[0]=0x63;
    m_hex_text[1]=m_tokens[1].num ;
    m_hex_text[2]=m_tokens[2].num;
    //oprand range check
    //0--check
    unsigned int tcmp0= m_tokens[1].num;
    unsigned int cmp00=0xff& m_tokens[1].num;
    unsigned int cmp01=0xff;
    cmp01=~cmp01;
    cmp01=cmp01|cmp00;
    unsigned int cmp02=(0xff^(0xff>>1)) & cmp00  ;
    if(  (tcmp0!=cmp00)&&(!(cmp02&&(tcmp0==cmp01)))){ return 2; }
    //1--check
    unsigned int tcmp1= m_tokens[2].num;
    unsigned int cmp10=0xff& m_tokens[2].num;
    unsigned int cmp11=0xff;
    cmp11=~cmp11;
    cmp11=cmp11|cmp10;
    unsigned int cmp12=(0xff^(0xff>>1)) & cmp10  ;
    if(  (tcmp1!=cmp10)&&(!(cmp12&&(tcmp1==cmp11)))){ return 2; }
    return 0;
    }
    }
    

//unknown code
return -1;
}
int asm8051_context_init(void *mCtx)
{
// inst codegen func count:46
T_ASM_CONTEXT* mp_ctx = (T_ASM_CONTEXT*)mCtx;

    mp_ctx->m_line_key_word_ptr["ACALL"] = &ACALL_CodeGen;
    mp_ctx->m_line_key_word_ptr["ADD"] = &ADD_CodeGen;
    mp_ctx->m_line_key_word_ptr["ADDC"] = &ADDC_CodeGen;
    mp_ctx->m_line_key_word_ptr["AJMP"] = &AJMP_CodeGen;
    mp_ctx->m_line_key_word_ptr["ANL"] = &ANL_CodeGen;
    mp_ctx->m_line_key_word_ptr["CALL"] = &CALL_CodeGen;
    mp_ctx->m_line_key_word_ptr["CJNE"] = &CJNE_CodeGen;
    mp_ctx->m_line_key_word_ptr["CLR"] = &CLR_CodeGen;
    mp_ctx->m_line_key_word_ptr["CPL"] = &CPL_CodeGen;
    mp_ctx->m_line_key_word_ptr["DA"] = &DA_CodeGen;
    mp_ctx->m_line_key_word_ptr["DEC"] = &DEC_CodeGen;
    mp_ctx->m_line_key_word_ptr["DIV"] = &DIV_CodeGen;
    mp_ctx->m_line_key_word_ptr["DJNZ"] = &DJNZ_CodeGen;
    mp_ctx->m_line_key_word_ptr["INC"] = &INC_CodeGen;
    mp_ctx->m_line_key_word_ptr["JB"] = &JB_CodeGen;
    mp_ctx->m_line_key_word_ptr["JBC"] = &JBC_CodeGen;
    mp_ctx->m_line_key_word_ptr["JC"] = &JC_CodeGen;
    mp_ctx->m_line_key_word_ptr["JMP"] = &JMP_CodeGen;
    mp_ctx->m_line_key_word_ptr["JNB"] = &JNB_CodeGen;
    mp_ctx->m_line_key_word_ptr["JNC"] = &JNC_CodeGen;
    mp_ctx->m_line_key_word_ptr["JNZ"] = &JNZ_CodeGen;
    mp_ctx->m_line_key_word_ptr["JZ"] = &JZ_CodeGen;
    mp_ctx->m_line_key_word_ptr["LCALL"] = &LCALL_CodeGen;
    mp_ctx->m_line_key_word_ptr["LJMP"] = &LJMP_CodeGen;
    mp_ctx->m_line_key_word_ptr["MOV"] = &MOV_CodeGen;
    mp_ctx->m_line_key_word_ptr["MOVC"] = &MOVC_CodeGen;
    mp_ctx->m_line_key_word_ptr["MOVX"] = &MOVX_CodeGen;
    mp_ctx->m_line_key_word_ptr["MUL"] = &MUL_CodeGen;
    mp_ctx->m_line_key_word_ptr["NOP"] = &NOP_CodeGen;
    mp_ctx->m_line_key_word_ptr["ORL"] = &ORL_CodeGen;
    mp_ctx->m_line_key_word_ptr["POP"] = &POP_CodeGen;
    mp_ctx->m_line_key_word_ptr["PUSH"] = &PUSH_CodeGen;
    mp_ctx->m_line_key_word_ptr["RET"] = &RET_CodeGen;
    mp_ctx->m_line_key_word_ptr["RETI"] = &RETI_CodeGen;
    mp_ctx->m_line_key_word_ptr["RL"] = &RL_CodeGen;
    mp_ctx->m_line_key_word_ptr["RLC"] = &RLC_CodeGen;
    mp_ctx->m_line_key_word_ptr["RR"] = &RR_CodeGen;
    mp_ctx->m_line_key_word_ptr["RRC"] = &RRC_CodeGen;
    mp_ctx->m_line_key_word_ptr["SETB"] = &SETB_CodeGen;
    mp_ctx->m_line_key_word_ptr["SIMTRAP"] = &SIMTRAP_CodeGen;
    mp_ctx->m_line_key_word_ptr["SJMP"] = &SJMP_CodeGen;
    mp_ctx->m_line_key_word_ptr["SUBB"] = &SUBB_CodeGen;
    mp_ctx->m_line_key_word_ptr["SWAP"] = &SWAP_CodeGen;
    mp_ctx->m_line_key_word_ptr["XCH"] = &XCH_CodeGen;
    mp_ctx->m_line_key_word_ptr["XCHD"] = &XCHD_CodeGen;
    mp_ctx->m_line_key_word_ptr["XRL"] = &XRL_CodeGen;

return 0;
}

