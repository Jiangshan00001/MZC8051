#ifndef NS_AMS8051HEX_ASM_FUNCS_H
#define NS_AMS8051HEX_ASM_FUNCS_H
#include <map>
namespace NS_AMS8051HEX{

class asm_to;
typedef enum E_TYPE_IC_TOKEN_OPR{
TOKENI_AB,
TOKENI_ACC,
TOKENI_AT_A_PLUS_DPTR,
TOKENI_AT_A_PLUS_PC,
TOKENI_AT_DPTR,
TOKENI_AT_RI,
TOKENI_C,
TOKENI_DOTBIT,
TOKENI_DPTR,
TOKENI_IMM,
TOKENI_NBIT,
TOKENI_RN,
TOKENI_VAL,
} E_TYPE_IC_TOKEN_OPR;
int get_asm_to_bin(const std::string cmd, int opr_cnt, int opr_type1, unsigned opr_val1, int opr_type2, unsigned opr_val2,int opr_type3, unsigned opr_val3, unsigned curr_addr,  std::string &ibin);
}//namespace end
#endif
