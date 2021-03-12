#ifndef TOKEN_DEFS_H
#define TOKEN_DEFS_H


#include <vector>
#include <string>

namespace NS_AMS8051HEX{

typedef enum{
    TOKEN_DEFS_UNKNOWN=0x0000,
    TOKEN_DEFS_TYPE_ELEM=1,  /// lex生成的类型，m_token_type是lex种的type，主要用于临时生成，或者固定关键字
    TOKEN_DEFS_TYPE_AST, /*ast--yacc type*/

} TOKEN_DEFS_TYPE;

    class token_defs
    {
    public:
        token_defs();
    public:
        std::vector<int> m_tk_type_int_list;
        int m_tk_type_int;
        TOKEN_DEFS_TYPE m_type;
        std::vector<token_defs*> m_tk_elems;
        //type from yacc token id
        int m_token_type;

        std::string m_file_name;
        int column_no;
        int line_no;
        int num;
        int m_resolved;
        std::string val_str;


    public:
        std::string name;


        void print();
        void print_self();
    };



    token_defs &gempty_token();
    token_defs *parser_ntoken(token_defs& tk);


    /// 此宏定义在ll文件中使用
    /// tp: token_type_int_val
    /// resolved: [0/1]
    /// vnum 数值
#define TKEY_DEF(tp, resolved, vnum )  \
        { \
       yylval->val_str = yytext; \
       yylval->m_tk_type_int_list.clear(); \
       yylval->num = vnum; \
       yylval->m_resolved = resolved;\
       yylval->line_no=yylloc->begin.line; \
       yylval->column_no=yylloc->begin.column; \
       if(yylloc->begin.filename!=NULL)yylval->m_file_name = *(yylloc->begin.filename);\
       yylval->m_token_type=tp; \
       yylval->m_type=TOKEN_DEFS_TYPE_ELEM; \
       return tp; \
       }

}


#endif // TOKEN_DEFS_H
