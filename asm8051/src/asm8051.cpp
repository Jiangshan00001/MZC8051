#include <sstream>
#include <assert.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "asm8051.h"
#include "asm_context.h"
#include "hex_generator.h"
#include "asm8051_lex.h"
#include "text_block.h"
#include "asm_keywords.h"
#include "trim.h"
#include "split.h"
#include "replace.h"
#include "asm_token.h"
#include "mylog.h"


using mylog::cerr;
using mylog::cout;
using mylog::cdbg;

using mylog::csummary;

//using namespace std;

asm8051::asm8051()
{
    m_lexyacc = NULL;
    mp_context = NULL;
    m_is_debug = 0;



    clear();
}

asm8051::~asm8051()
{
    if(mp_context!=NULL)
    {
        delete (T_ASM_CONTEXT*)mp_context;
    }
    if(m_lexyacc!=NULL)
    {
        delete m_lexyacc;
    }
}

int asm8051::clear()
{

    if(mp_context!=NULL)
    {
        delete (T_ASM_CONTEXT*)mp_context;
    }
    mp_context = new T_ASM_CONTEXT();

    if(m_lexyacc!=NULL)
    {
        delete m_lexyacc;
    }
    m_lexyacc = new asm_lex_stuff::driver();

    T_ASM_CONTEXT &m_context = * (T_ASM_CONTEXT*)mp_context;
    m_context.m_current_line_no = 0;
    m_context.m_text_block.clear();
    m_context.m_label_address.clear();
    m_context.m_preprocess_var.clear();
    m_context.m_current_address = 0;


    std::ifstream fin;
    std::stringstream str1;
    fin.open("reg51_asm.h");
    str1<<fin.rdbuf();

    add_src(str1.str(), "reg51_asm.h");
    return 0;
}


int asm8051::add_src(std::string code_src, std::string file_name)
{
#if 1
    T_ASM_CONTEXT &m_context = * (T_ASM_CONTEXT*)mp_context;

    this->m_stream_name = file_name;
    m_context.m_current_line_no = 0;

    std::stringstream m_file_in(code_src);

    ///读出一行
    std::string mOneLine;

    if(m_is_debug)
    {
        cdbg<<"============"<<std::endl;
        cdbg<<"add src:"<<file_name<<"\n";
    }
    int cnt=0;



    while(getline(m_file_in, mOneLine))
    {
        add_line(mOneLine);
        cnt++;
    }

    if(m_is_debug)
    {
        cdbg<<"add src finish\n";
        cdbg<<"line count:"<<cnt<<"\n";
        cdbg<<"============"<<std::endl;
    }
#endif

    return 0;
}


int asm8051::compile()
{
    int recomp_index = 0;

    cdbg<<"recomp_index:"<<recomp_index<<"\n";
    int ret = compile_1();
    recomp_index++;

    while(ret>0)
    {
        cout<<"extend inst:"<<ret<<"\n";
        cout<<"compile_1 again\n";
        //需要重新编译
        cdbg<<"recomp_index:"<<recomp_index<<"\n";
        ret = compile_1();
        recomp_index++;
    }


    int unresolved = compile_check();
    if(ret<0)
    {
        cerr<<"ERROR: compile error\n";
    }

    if(unresolved<0)
    {
        cerr<<"ERROR: unresolved error\n";
    }

    return ret;
}

std::string asm8051::generate_hex()
{
    int code_size = 0;
    for(unsigned i=0;i< ((T_ASM_CONTEXT*)mp_context)->m_text_block.size();++i)
    {
        code_size += ((T_ASM_CONTEXT*)mp_context)->m_text_block[i].m_hex_text.size();
    }

    csummary << "code_size: "    <<code_size<<"\n";

    std::string m_out = hex_generator_str((T_ASM_CONTEXT*)mp_context);

    return m_out;
}

std::string asm8051::generate_sym()
{
    std::stringstream mout;
    T_ASM_CONTEXT &m_context = * (T_ASM_CONTEXT*)mp_context;

    mout<<"{version:.01,\ndirective_list:[\n";
    ///打印调试信息到.asym
    int dir_size = 0;
    for(unsigned i=0;i< m_context.m_text_block.size();++i)
    {
        T_HEX_TEXT_BLOCK &blk = m_context.m_text_block[i];
        if(blk.m_dir_source.empty())
        {
            continue;
        }
        if(dir_size>0)
        {
            mout<<",\n";
        }
        mout<<"{"<<"line:"<<blk.m_dir_line_no<<", source:"<< blk.m_dir_source<<", addr:"<< blk.m_address<<"}";
        dir_size++;
    }
    mout<<"\n]\n}";

    return mout.str();
}


int asm8051::add_line(std::string one_line_text, int line_no)
{
    ///TODO: 行的随机插入不支持，只支持顺序插入
    assert(line_no==-1);
    T_ASM_CONTEXT &m_context = * (T_ASM_CONTEXT*)mp_context;

    m_context.m_current_line_no++;

    ///预处理
    one_line_text = m_context.asm_line_preprocess(one_line_text);

    if(one_line_text.size()==0)
    {
        return 0;
    }

    line_no = m_context.m_current_line_no;
    //cout<<"============================\nline-"<<line_no<<":"<<one_line_text<<std::endl;

    std::istringstream iss1(one_line_text+"\n");
    if(m_lexyacc!=NULL)
    {
        delete m_lexyacc;
    }
    m_lexyacc = new asm_lex_stuff::driver();

    m_lexyacc->parse_stream(iss1, this->m_stream_name);
    //m_lexyacc->m_token_result;

    if(!m_lexyacc->m_parse_success)
    {
        cout<<"ERROR:line:"<<line_no<<". "<<one_line_text <<"--asm8051::add_line\n";
        cerr<<"ERROR:line:"<<line_no<<". "<<one_line_text <<"--asm8051::add_line\n";
        return -1;
    }


    token_to_block(m_lexyacc->m_token_result, m_context.m_text_block, line_no,
                   m_context.m_dir_source, m_context.m_dir_line_no, one_line_text);

    return 0;
}


///        mBlk.set_src_text(label_str, line_no);
/// mBlk.m_tokens = m_context.asm_line_parse(mBlk.m_source);
/// m_context.m_text_block.push_back(mBlk);
int asm8051::token_to_block(asm_token& tk, std::vector<T_HEX_TEXT_BLOCK> &blk, int line_no,
                            std::string &dir_source, int &dir_line_no, std::string line_str)
{
    ///token转为block
    ///
    unsigned i=0;
    T_HEX_TEXT_BLOCK mBlk;

    mBlk.m_dir_source = dir_source;
    mBlk.m_dir_line_no = dir_line_no;

    dir_source ="";
    dir_line_no=0;

    if(tk.type==TOKEN_PARENT)
    {

        ///包含字token的
        ///
        switch(tk.child_type)
        {
        case TOKEN_CMD:
        case TOKEN_MACRO:
        case TOKEN_LABEL:
        case TOKEN_DB:
            if(line_str.size()>0)
            {
                mBlk.set_src_text(line_str, line_no);
            }
            else
            {
                mBlk.set_src_text(tk.val_str, line_no);
            }

            mBlk.m_tokens = tk.m_childs;
            blk.push_back(mBlk);
            break;
        case TOKEN_PARENT:
            for(i=0;i<tk.m_childs.size();++i)
            {
                token_to_block(tk.m_childs[i], blk, line_no, dir_source, dir_line_no);
            }
            break;
        default:
            cout<<"token_to_block not processed token:"<<tk.child_type<<std::endl;
            cerr<<"token_to_block not processed token:"<<tk.child_type<<std::endl;
            break;
        }
    }
    else
    {
        mBlk.set_src_text(tk.val_str, line_no);
        mBlk.m_tokens.push_back(tk);

        blk.push_back(mBlk);
    }


    return 0;
}

std::string asm8051::current_block_info()
{
    T_ASM_CONTEXT &m_context = * (T_ASM_CONTEXT*)mp_context;

    std::stringstream strA;
    strA<<"line:"<<m_context.m_current_block.m_line_no<<". "
       << m_context.m_current_block.m_source <<std::endl;

    return strA.str();
}



int asm8051::debug_out1(std::ostream &fout)
{
    //std::ofstream fout;
    //fout.open(mfile);
    T_ASM_CONTEXT &m_context = * (T_ASM_CONTEXT*)mp_context;

    fout<<"====preprocess====\n";
    for(auto it=m_context.m_preprocess_var.begin();it!= m_context.m_preprocess_var.end();++it)
    {
        fout<<it->first<<" EQU "<< it->second.val_str<<"("<<it->second.get_type_str()<<"-"<<it->second.m_resolved <<")" <<"\n";
    }

    fout<<"====label====\n";
    for(auto it=m_context.m_label_address.begin();it!=m_context.m_label_address.end();++it)
    {
        fout<<it->first<<" LABEL_ADDR: " <<std::hex<<it->second<<"H\n";
    }

    fout<<"====text_block====\n";
    for(auto it=m_context.m_text_block.begin();it!=m_context.m_text_block.end();++it)
    {
        fout<<it->m_line_no<<". "<<  it->m_source<<". TOKEN:";
        for(unsigned i=0;i<it->m_tokens.size();++i)
        {
            fout<<it->m_tokens[i].val_str<<"("<<it->m_tokens[i].get_type_str()<<"-"<<it->m_tokens[i].m_resolved <<")"<<", ";
        }
        fout<<"\n";
    }

    //fout.close();
    return 0;
}


int asm8051::compile_1()
{

    compile_start();


    ///去掉注释，添加reg51头文件
    if(m_is_debug)
    {
        cout<<"compile-1 start-add src finish\n";
        debug_out1(cdbg);
        cout<<"compile-1 finish\n";
    }
    //确定地址
    int ret1 = compile_first();

    ///此处已经确定地址，并进行过宏定义的替换
    if(m_is_debug)
    {
        cout<<"compile-2 start--compile_first_finish\n";
        debug_out1(cdbg);
        cout<<"compile-2 finish\n";
    }

    int ret2 = compile_update_label();

    if(m_is_debug)
    {
        cout<<"compile-3 start--update_label finish\n";
        debug_out1(cdbg);
        cout<<"compile-3 finish\n";
    }

    int ret3 = compile_second();
    if(m_is_debug)
    {
        cout<<"compile-3 start---compile_second finish\n";
        debug_out1(cdbg);
        cout<<"compile-4 finish\n";
    }

    return ret1+ret2+ret3;
}



int asm8051::compile_start()
{
    T_ASM_CONTEXT &m_context = * (T_ASM_CONTEXT*)mp_context;

    m_context.m_current_line_no = 0;
    m_context.m_current_address = 0;
    m_context.m_label_address.clear();
    m_context.m_preprocess_var.clear();

}

int asm8051::compile_first()
{
    T_ASM_CONTEXT &m_context = * (T_ASM_CONTEXT*)mp_context;

    int need_ext = 0;



    for (unsigned k1=0;k1<m_context.m_text_block.size();++k1)
    {
        int ret = process_one_line(&m_context, k1, 1);

        if(ret==3)
        {
            ///当前指令被扩展，需要重新编译当前指令和之后的指令
            ret = process_one_line(&m_context, k1, 1);
            assert(ret!=3);

            need_ext++;
        }
    }

    return need_ext;
}

int asm8051::compile_check()
{
    int unresolved_check=0;
    T_ASM_CONTEXT &m_context = * (T_ASM_CONTEXT*)mp_context;
    for(unsigned i=0;i<m_context.m_text_block.size();++i)
    {
        for(unsigned j=0;j<m_context.m_text_block[i].m_tokens.size();++j)
        {
            //unsigned long addr = m_context.m_text_block[i].m_address;
            asm_token &ctoken = m_context.m_text_block[i].m_tokens[j];
            if(ctoken.m_resolved==0)
            {
                unresolved_check--;
                cerr<<"ERROR:unresolved: "<<ctoken.val_str<<"\n";
            }
        }
    }
    return unresolved_check;
}

int asm8051::compile_update_label()
{
    //更新label到各指令中

    T_ASM_CONTEXT &m_context = * (T_ASM_CONTEXT*)mp_context;
    for(unsigned i=0;i<m_context.m_text_block.size();++i)
    {
        for(unsigned j=0;j<m_context.m_text_block[i].m_tokens.size();++j)
        {
            unsigned long addr = m_context.m_text_block[i].m_address;
            asm_token &ctoken = m_context.m_text_block[i].m_tokens[j];


            if(ctoken.m_resolved==0)
            {
                /// 如果某个指令虽然没有标签的KEYWORD，但是有未resolved的token，则也要二次解析
                /// MOV DPTR, #LAB2
                m_context.m_text_block_need_refresh_index.push_back(i);
                break;
            }
        }
    }
    return 0;
}

int asm8051::compile_second()
{
    T_ASM_CONTEXT &m_context = * (T_ASM_CONTEXT*)mp_context;

    int need_ext = 0;

    //////////////////////////////////////////////////////////////////////////
    ///第二遍处理需要重定位的代码
    //////////////////////////////////////////////////////////////////////////
    for (unsigned k=0;k<m_context.m_text_block_need_refresh_index.size();++k)
    {
        int ret = process_one_line(&m_context, m_context.m_text_block_need_refresh_index[k], 0);
        if(ret==3)
        {
            ///当前指令被扩展，需要重新编译当前指令和之后的指令
            ret = process_one_line(&m_context, m_context.m_text_block_need_refresh_index[k], 0);
            assert(ret!=3);

            need_ext++;
        }
    }
    return need_ext;
}

int asm8051::process_one_line(void *mCtx, int index, int first_time)
{
    T_ASM_CONTEXT &m_context = * (T_ASM_CONTEXT*)mp_context;

    m_context.m_current_block = m_context.m_text_block[index];

    std::vector<asm_token> &m_token = m_context.m_current_block.m_tokens;

    if (!first_time)
    {
        //第二遍的时候，地址已经固定
        //每一个block的地址需要单独读出来，因为并不是顺序编译第二遍，只有需要编译的block才会编译（含有revolved=0的block）
        m_context.m_current_address = m_context.m_text_block[index].m_address;
    }

    if(m_token.size()==0)
    {
        cout<<"index:"<<index<<"\n";
        cout<<"ERROR: line:"<<m_context.m_current_block.m_line_no<<". "<<current_block_info();
        cerr<<"ERROR: line:"<<m_context.m_current_block.m_line_no<<". "<<current_block_info();
        cerr<<"dump:\n";
        this->debug_out1(cerr);
        assert(0);
        return -1;
    }

    std::string cmd_world = m_context.m_current_block.m_tokens[0].val_str;


    //////////////////////////////////////////////////////////////////////////
    ///
    /// 预处理
    bool is_macro = 0;
    int macro_index = 0;
    for(unsigned i=0;i<m_token.size();++i)
    {
        if (m_token[i].type==TOKEN_MACRO)
        {
            is_macro = 1;
            macro_index = i;
            break;
        }
    }


    if(is_macro)
    {
        auto it = m_context.m_line_macro_ptr.find(m_token[macro_index].val_str);
        if (it== m_context.m_line_macro_ptr.end())
        {
            //未找到命令？？？
            cout<<"macro not found error!!!"<< cmd_world <<std::endl;
            return -3;
        }

        ///处理宏定义
        int ret = (*it->second)(&m_context);
        if((ret!=0)&&(ret!=1))
        {
            cout<<"ERROR: line:"<<m_context.m_current_block.m_line_no<<"index:"<< index<<". "<< m_context.m_current_block.m_source<<"process_one_line-macro" <<std::endl;
            cerr<<"ERROR: line:"<<m_context.m_current_block.m_line_no<<"index:"<< index<<". "<< m_context.m_current_block.m_source<<"process_one_line-macro" <<std::endl;
        }

        m_context.m_text_block[index] = m_context.m_current_block;
        return 0;
    }



    //////////////////////////////////////////////////////////////////////////


    //////////////////////////////////////////////////////////////////////////
    /// process label
    if(m_token[0].type==TOKEN_LABEL)
    {
        if(first_time)
        {
            if(m_context.m_label_address.find(m_token[0].val_str)==m_context.m_label_address.end())
            {
                m_context.m_label_address[m_token[0].val_str] = m_context.m_current_address;
            }
            else
            {
                if(m_context.m_label_address[m_token[0].val_str] != m_context.m_current_address)
                {
                    ///处理label。添加label的地址标记. FIXME TODO 此处对于添加标签时，如果标签已经存在，则报标签重复错误
                    cout<<"ERROR: label repeat. labelname="<<m_token[0].val_str<<"old_val:"<<m_context.m_label_address[m_token[0].val_str]<<". new_val"<< m_context.m_current_address <<"\n";
                    cerr<<"ERROR: label repeat. labelname="<<m_token[0].val_str<<"old_val:"<<m_context.m_label_address[m_token[0].val_str]<<". new_val"<< m_context.m_current_address <<"\n";
                    cout<<"ERROR: line:"<<m_context.m_current_block.m_line_no<<"index:"<< index<<". "<< m_context.m_current_block.m_source<<"process_one_line-macro" <<std::endl;
                    cerr<<"ERROR: line:"<<m_context.m_current_block.m_line_no<<"index:"<< index<<". "<< m_context.m_current_block.m_source<<"process_one_line-macro" <<std::endl;

                    return -1;
                }
            }
        }
        return 0;
    }

    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////
    ///对应的命令，处理前需要先预处理，将对应的字符串替换掉
    /// 2020.7.6 将对token的求值，从当前指令生成前，改到生成后，因为要想生成正确的地址，需要先获取指令长度。
    /// 如果生成了错误的地址，则后期可能认为已经resolved，而无法再次生成正确的地址
    for(unsigned i=1;i<m_token.size();++i)
    {
        if(1!=m_token[i].m_resolved)
        {
            ///此token需要处理.预处理变量替换，表达式求值
            m_context.eval_token(m_token[i], m_context.m_current_address, m_context.m_current_block.m_hex_text.size(), first_time);
        }
    }

    //////////////////////////////////////////////////////////////////////////


    //////////////////////////////////////////////////////////////////////////
    ///命令行指令码生成

    std::map<std::string, CODE_GEN_FUNC_PTR>::iterator it =
            m_context.m_line_key_word_ptr.find(cmd_world);

    if (it== m_context.m_line_key_word_ptr.end())
    {
        //未找到命令？？？
        cout<<"ERROR: line:"<<m_context.m_current_block.m_line_no  << ". cmd not found error!!!"<< cmd_world <<"process_one_line-keyword ptr" <<std::endl;
        cerr<<"ERROR: line:"<<m_context.m_current_block.m_line_no  << ". cmd not found error!!!"<< cmd_world <<"process_one_line-keyword ptr" <<std::endl;
        return -2;
    }


    int ret = (*it->second)(&m_context);
    if((ret<0))
    {
        cout<<"ERROR: line:"<<m_context.m_current_block.m_line_no<<". cmd format could not match. "<<current_block_info();
        cerr<<"ERROR: line:"<<m_context.m_current_block.m_line_no<<". cmd format could not match. "<<current_block_info();
        return -3;
    }
    else if(ret==2)
    {
        if(m_context.m_jmp_auto_extend)
        {
            if(m_context.extend_inst(index))
            {
                //指令被扩展，返回3
                //未更新m_current_address 所以返回3的行必须再次处理
                return 3;
            }
            else
            {
                cout<<"WARNING: line:"<<m_context.m_current_block.m_line_no<<". param range truncated. "<<current_block_info();
            }
        }
        cout<<"WARNING: line:"<<m_context.m_current_block.m_line_no<<". param range truncated. "<<current_block_info();
    }

    //////////////////////////////////////////////////////////////////////////



    //////////////////////////////////////////////////////////////////////////


    m_context.m_text_block[index] = m_context.m_current_block;

    ///更新每个指令的地址
    if (first_time)
    {
        m_context.m_text_block[index].m_address = m_context.m_current_address;
        m_context.m_current_address+=m_context.m_current_block.m_hex_text.size();
    }

    return 0;
}




