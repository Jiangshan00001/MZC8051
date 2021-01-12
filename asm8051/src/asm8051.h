#ifndef ASM8051_H
#define ASM8051_H

#include <string>

#include "lex_yacc/driver.h"

///限制：
/// 转移地址必须使用标签，不能直接使用常数(可通过预处理实现)
/// asm8051 m_8051;
/// m_8051.add_src(ui->plainTextEditASM->toPlainText().toStdString());
/// m_8051.compile();
/// std::string mout = m_8051.generate_hex();
/// ui->plainTextEditHEX->setPlainText(QString::fromStdString(mout));
///
///
///
///
class asm8051
{
public:
    asm8051();

    ~asm8051();
    int add_src(std::string code_src, std::string file_name="");
    int compile();
    std::string generate_hex();
    std::string generate_sym();

public:
    int clear();
    int add_line(std::string one_line_text, int line_no=-1 );

    ///读入的中间代码
    int debug_out1(std::ostream &fout);
    /// 编译流程：
    ///
    /// 1 add_line:加入行代码，生成每行一个T_HEX_TEXT_BLOCK。总结果在m_text_block中
    /// 2 compile_first 编译生成： 每行的地址码，标签地址码。每行字节数
    /// 3 查找包含token.resolved=0 的指令，生成 m_text_block_need_refresh_index
    /// 3 生成参数，检查每个参数是否超出范围。如果超出范围，则报警。如果有扩展选项，则生成扩展指令
    /// 4 检查是否有扩展指令，如果有扩展，则goto 2
    /// 5 解析参数并编译生成hex
    ///
    /// 关键点：
    /// 1 token求值后，保留原始求值等式，后期可以求值
    /// 2 token求值后，记录是后期求值的token，待后期如果有扩展，则可以重新求值
    /// 方式：每个token.m_resolved 直接可用的=1. 后期求值可用的=2 不可用需求值的=0； token的child不删除
    ///

    int compile_1();

    int m_is_debug;

private:
    ///将部分功能放入context，保持接口的简单和依赖小
    void *mp_context;

    /// 0--ok
    /// -1--不可恢复的错误
    /// 3--inst extended. need reprocess
    int compile_start();
    int compile_first();
    int compile_update_label();
    int compile_second();
    int compile_check();

    /// 0--ok
    /// -1--error
    /// 2--current line param truncated warning
    /// 3--current is extended. reprocess needed
    int process_one_line(void *mCtx, int index, int first_time);

    int token_to_block(asm_token& tk, std::vector<class T_HEX_TEXT_BLOCK> &blk, int line_no,
                       std::string &dir_source, int &dir_line_no, std::string line_str="");

public:
    std::string m_stream_name;

    asm_lex_stuff::driver *m_lexyacc;

    std::string current_block_info();


};

#endif // ASM8051_H
