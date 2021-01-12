#include "asm8051_lex.h"
#include<sstream>

#include <iostream>
#include <algorithm>
#include <ctype.h>
#include "asm_context.h"
#include "trim.h"
#include "split.h"
#include "replace.h"
#include "asm_token.h"

using namespace std;
// simple way in STL


#if 0
unsigned long StrToNumber(string  mHexStr)
{
    mHexStr = trim(mHexStr);
    if(mHexStr.size()==0)
    {
        return 0;
    }

    std::stringstream ss;
    unsigned long x=0;


    if(mHexStr.size()>3)
    {
        ///字符串是： NOT 20H
        if(mHexStr.find("NOT ")==0)
        {
            std::string tmp11= mHexStr.substr(4);
            tmp11=trim(tmp11);
            unsigned long a = StrToNumber(tmp11);
            return ~a;
        }
    }
    if(mHexStr.size()>3)
    {
        if(mHexStr.find("LOW")==0)
        {
            std::string tmp11= mHexStr.substr(3);
            tmp11=trim(tmp11);
            unsigned long a = StrToNumber(tmp11);
            return (0xff&a);
        }
    }
    if(mHexStr.size()>4)
    {
        if(mHexStr.find("HIGH")==0)
        {
            std::string tmp11= mHexStr.substr(4);
            tmp11=trim(tmp11);
            unsigned long a = StrToNumber(tmp11);
            return ((a>>8)&0xff);
        }
    }


    if(mHexStr[0]=='(')
    {
        //右括号，需要去除括号
        size_t lindex = mHexStr.find(')');
        std::string sub_str = mHexStr.substr(1, lindex-1);
        unsigned long a = StrToNumber(sub_str);
        ///FIXME 此处没有考虑运算符
        return a;
    }

    size_t lindex2 = mHexStr.find('/');
    if(lindex2 != std::string::npos)
    {
        std::vector<std::string> wds = split(mHexStr, "/");
        unsigned long a = StrToNumber( wds[0]);
        unsigned long b = StrToNumber( wds[1]);
        return a/b;
    }








    if((mHexStr[mHexStr.size()-1]=='H')||(mHexStr[mHexStr.size()-1]=='h'))
    {
        ss << std::hex << mHexStr;
        ss >> x;
        return x;
    }

    if(mHexStr.size()>2)
    {
        if((mHexStr[0]=='0')&&((mHexStr[1]=='X')||(mHexStr[1]=='x')))
        {
            ss << std::hex << mHexStr.substr(2);
            ss >> x;
            return x;
        }
    }

    if((mHexStr[mHexStr.size()-1]=='B')||(mHexStr[mHexStr.size()-1]=='b'))
    {
        x=0;
        for(unsigned i=0;i<mHexStr.size();++i)
        {
            if((mHexStr[i]!='1')&&(mHexStr[i]!='0'))
            {
                break;
            }

            x<<=1;
            if(mHexStr[i]=='1')
            {
                x+=1;
            }

        }
        return x;
    }


    ss << mHexStr;
    ss >> x;
    return x;
}

std::string NumberToStr(long num)
{
    std::stringstream s;
    std::string ss;
    s<<std::hex<<num<<"H";
    return s.str();
}

#endif


typedef int (*op_tmp) (int i);


string &T_ASM_CONTEXT::asm_line_preprocess(string &mOneLine)
{

#if 1
    //去除注释. 汇编中，一行的;之后为注释
    if(mOneLine.find(";")!=mOneLine.npos)
    {
        //std::cout<<one_line_text<<"\n";
        mOneLine = mOneLine.substr(0, mOneLine.find(";"));
        //std::cout<<one_line_text<<"\n";
    }

    trim1(mOneLine);

    //去除开头是 双斜杠的c语言语法注释
    if(mOneLine.size()>2)
    {
        if((mOneLine[0]=='/')&&(mOneLine[1]=='/'))
        {
            mOneLine="";
            return mOneLine;
        }
    }

#endif

    /// 将\t改为空格，方便统一处理
    mOneLine = replace(mOneLine, "\t", " ");
    mOneLine = replace(mOneLine, "\r", " ");

    //去除空格
    // trim
    trim1(mOneLine);


    ///添加#line 的处理
    if(mOneLine.size()>5)
    {
        if(mOneLine[0]=='#')
        {
            ///此处为预处理命令，命令完成后，需要清空mOneLine

            if(mOneLine.substr(0, 5)=="#line")
            {
                std::vector<std::string> dir_str = split(mOneLine," ");
                this->m_dir_source = replace(dir_str[2], "\n", "");
                this->m_dir_line_no = StrToNumber(dir_str[1]);
            }

            mOneLine.clear();
        }
    }

    // lower--->upper
    transform<std::basic_string<char>::iterator, std::basic_string<char>::iterator, op_tmp>(mOneLine.begin(), mOneLine.end(), mOneLine.begin(), toupper);

    return mOneLine;
}

int T_ASM_CONTEXT::eval_token(asm_token &tk, unsigned long curr_addr, unsigned curr_cmd_byte_size, int not_eval_label)
{

    if(tk.m_resolved==1)
    {
        //已经是确定的数值 了
        return 0;
    }

    if(tk.type==TOKEN_KEYWORD)
    {
        auto it=m_preprocess_var.find(tk.val_str);
        if(it!=m_preprocess_var.end())
        {
            //token替换
            tk = it->second;
            return 0;
        }


        if(tk.val_str=="$")
        {
            if(!not_eval_label)
            {
                tk.num = curr_addr;
                tk.rel = tk.num - curr_addr - curr_cmd_byte_size;
                tk.m_resolved = 2;
                return 0;
            }
        }

        /// 检查是否是标签，如果是标签，则替换为标签对应的值
        /// 如果标签地址未确定，则延后确定
        if(this->m_label_address.find(tk.val_str)!=this->m_label_address.end())
        {
            if(!not_eval_label)
            {
                tk.num = this->m_label_address[tk.val_str];
                tk.rel = tk.num- curr_addr - curr_cmd_byte_size;
                tk.m_resolved = 2;
                return 0;
            }
        }


        //此处是未知的变量？？？
        //可能是后面的label，暂未查到，可以下一遍确定
        tk.m_resolved = 0;
        return 0;
    }

    if(tk.type==TOKEN_DIV_NUM)
    {
        eval_token(tk.m_childs[0], curr_addr,  curr_cmd_byte_size);
        if(tk.m_childs[0].m_resolved)
        {
            tk.m_resolved = 2;
            tk.num = tk.m_childs[0].num;
            //tk.m_childs.clear();
        }

        return 0;
    }

    if (tk.type==TOKEN_J_DATA)
    {
        eval_token(tk.m_childs[0], curr_addr,  curr_cmd_byte_size);
        if(tk.m_childs[0].m_resolved)
        {
            tk.m_resolved = 2;
            tk.num = tk.m_childs[0].num;
            //tk.m_childs.clear();
        }

        return 0;
    }


    if((tk.child_type==TOKEN_OPR)&&(tk.m_childs.size()>0))
    {
        if(tk.m_childs[0].val_str=="&")
        {
          eval_token(tk.m_childs[1], curr_addr,  curr_cmd_byte_size);
          eval_token(tk.m_childs[2], curr_addr,  curr_cmd_byte_size);

          if((!tk.m_childs[1].m_resolved)||
                  (!tk.m_childs[2].m_resolved)
                  )
          {
              return 0;
          }

          unsigned a = tk.m_childs[1].num;
          unsigned b = tk.m_childs[2].num;

          tk.num = a&b;
          tk.m_resolved = 2;
          tk.type = TOKEN_NUM;
        }
        else if(tk.m_childs[0].val_str=="<<")
        {
          eval_token(tk.m_childs[1], curr_addr,  curr_cmd_byte_size);
          eval_token(tk.m_childs[2], curr_addr,  curr_cmd_byte_size);

          if((!tk.m_childs[1].m_resolved)||
                  (!tk.m_childs[2].m_resolved)
                  )
          {
              return 0;
          }

          unsigned a = tk.m_childs[1].num;
          unsigned b = tk.m_childs[2].num;

          tk.num = a<<b;
          tk.m_resolved = 2;
          tk.type = TOKEN_NUM;
        }
        else if(tk.m_childs[0].val_str==">>")
        {
          eval_token(tk.m_childs[1], curr_addr,  curr_cmd_byte_size);
          eval_token(tk.m_childs[2], curr_addr,  curr_cmd_byte_size);

          if((!tk.m_childs[1].m_resolved)||
                  (!tk.m_childs[2].m_resolved)
                  )
          {
              return 0;
          }

          unsigned a = tk.m_childs[1].num;
          unsigned b = tk.m_childs[2].num;

          tk.num = a>>b;
          tk.m_resolved = 2;
          tk.type = TOKEN_NUM;
        }
        else if(tk.m_childs[0].val_str=="(")
        {
            eval_token(tk.m_childs[1], curr_addr,  curr_cmd_byte_size);
            if(tk.m_childs[1].m_resolved)
            {
                tk.num = tk.m_childs[1].num;
                tk.rel =  tk.m_childs[1].num;
                //tk.m_childs.clear();
                tk.m_resolved = 2;
            }
        }
        else if(tk.m_childs[0].val_str=="NOT")
        {
            eval_token(tk.m_childs[1], curr_addr,  curr_cmd_byte_size);
            if(tk.m_childs[1].m_resolved)
            {
                tk.num = ~tk.m_childs[1].num;
                //tk.m_childs.clear();
                tk.m_resolved = 2;
            }
        }
        else if(tk.m_childs[0].val_str=="HIGH")
        {
            eval_token(tk.m_childs[1], curr_addr,  curr_cmd_byte_size);
            if(tk.m_childs[1].m_resolved)
            {
                tk.num = ((tk.m_childs[1].num)>>8)&0xff;
                //tk.m_childs.clear();
                tk.m_resolved = 2;
            }
        }
        else if(tk.m_childs[0].val_str=="LOW")
        {
            eval_token(tk.m_childs[1], curr_addr,  curr_cmd_byte_size);
            if(tk.m_childs[1].m_resolved)
            {
                tk.num = 0xff&(tk.m_childs[1].num);
                tk.m_resolved = 2;
            }
        }
        else if(tk.m_childs[0].val_str==".")
        {

            eval_token(tk.m_childs[1], curr_addr,  curr_cmd_byte_size);
            eval_token(tk.m_childs[2], curr_addr,  curr_cmd_byte_size);

            if((!tk.m_childs[1].m_resolved)||
                    (!tk.m_childs[2].m_resolved)
                    )
            {
                return 0;
            }

            unsigned a = tk.m_childs[1].num;
            unsigned b = tk.m_childs[2].num;
            unsigned c = 0;
            //std::cout<<"eval ."<<a<<". "<<b<<". "<<c<<std::endl;
            if(bit_addr_parse(a,b,c))
            {
                tk.num = c;
                tk.m_resolved = 2;
                tk.type = TOKEN_NUM;
                //tk.m_childs.clear();
            }
            else
            {
                cerr<<"ERROR: BIT PARSE " <<tk.val_str<<". a="<<a<<". b="<<b<<". c="<<c<<"\n";
            }
        }
        else  if(tk.m_childs[0].val_str=="/")
        {
            eval_token(tk.m_childs[1], curr_addr,  curr_cmd_byte_size);
            eval_token(tk.m_childs[2], curr_addr,  curr_cmd_byte_size);

            if((!tk.m_childs[1].m_resolved)||
                    (!tk.m_childs[2].m_resolved)
                    )
            {
                return 0;
            }

            unsigned a = tk.m_childs[1].num;
            unsigned b = tk.m_childs[2].num;
            //unsigned c = 0;
            if(b==0){a=0;b=1;std::cout<<"ERROR:line:"<<tk.line_no <<". div by zero error\n";}
            tk.num = a/b;
            tk.m_resolved = 2;
            tk.type = TOKEN_NUM;
            //tk.m_childs.clear();
        }
        else  if(tk.m_childs[0].val_str=="+")
        {
            eval_token(tk.m_childs[1], curr_addr,  curr_cmd_byte_size);
            eval_token(tk.m_childs[2], curr_addr,  curr_cmd_byte_size);

            if((!tk.m_childs[1].m_resolved)||
                    (!tk.m_childs[2].m_resolved)
                    )
            {
                return 0;
            }

            unsigned a = tk.m_childs[1].num;
            unsigned b = tk.m_childs[2].num;
            //unsigned c = 0;
            tk.num = a+b;
            tk.m_resolved = 2;
            tk.type = TOKEN_NUM;
            //tk.m_childs.clear();
        }
        else  if(tk.m_childs[0].val_str=="-")
        {
            eval_token(tk.m_childs[1], curr_addr,  curr_cmd_byte_size);
            eval_token(tk.m_childs[2], curr_addr,  curr_cmd_byte_size);

            if((!tk.m_childs[1].m_resolved)||
                    (!tk.m_childs[2].m_resolved)
                    )
            {
                return 0;
            }


            unsigned a = tk.m_childs[1].num;
            unsigned b = tk.m_childs[2].num;
            //unsigned c = 0;
            tk.num = a-b;
            tk.m_resolved = 2;
            tk.type = TOKEN_NUM;
            //tk.m_childs.clear();
        }
        else if(tk.m_childs[0].val_str=="SHL")
        {
            eval_token(tk.m_childs[1], curr_addr,  curr_cmd_byte_size);
            eval_token(tk.m_childs[2], curr_addr,  curr_cmd_byte_size);

            if((!tk.m_childs[1].m_resolved)||
                    (!tk.m_childs[2].m_resolved)
                    )
            {
                return 0;
            }


            tk.num = tk.m_childs[1].num<<tk.m_childs[2].num;
            //tk.m_childs.clear();
            tk.m_resolved = 2;
        }
        else if(tk.m_childs[0].val_str=="MOD")
        {
            eval_token(tk.m_childs[1], curr_addr,  curr_cmd_byte_size);
            eval_token(tk.m_childs[2], curr_addr,  curr_cmd_byte_size);

            if((!tk.m_childs[1].m_resolved)||
                    (!tk.m_childs[2].m_resolved)
                    )
            {
                return 0;
            }


            tk.num = tk.m_childs[1].num % tk.m_childs[2].num;
            //tk.m_childs.clear();
            tk.m_resolved = 2;
        }
        else
        {
            std::cout<<"ERROR: token type not processed:"<<tk.m_childs[0].val_str<<"\n";
        }
    }


    ///检查tk里，是否有label var
    ///
    return 0;
}



