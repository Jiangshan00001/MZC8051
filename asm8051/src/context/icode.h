#ifndef ICODE_H
#define ICODE_H
#include <vector>
#include <string>
namespace NS_AMS8051HEX{

typedef enum ICODE_TYPES
{
    ICODE_TYPE_BLOCK=512,
    ICODE_TYPE_ONE_CMD=513,
    ICODE_TYPE_ONE_OPERATION=514,// name--opr. sub_icode0--N param 见函数: calc_icode_val
    ICODE_TYPE_DEFINE_LABEL=515,
    ICODE_TYPE_ONE_MACRO=516,

    ICODE_TOKEN_OPR=600,
    ICODE_TOKEN_KEYWORD=601,
    ICODE_TOKEN_MACRO=602,
    ICODE_TOKEN_CMD=603,
    ICODE_TOKEN_ICONST=604,
    ICODE_TOKEN_FCONST=605,
    ICODE_TOKEN_STR=606,
}ICODE_TYPES;



class icode
{
public:	
    icode();
    icode(int itype);

    int merge_icode(icode *ic);

	int m_type;
    std::vector<icode*> sub_icode;
    std::string name;
    long num;
    double fnum;

    ///用于翻译后结果
    std::string m_bin;
    unsigned m_address;
};

}
#endif
