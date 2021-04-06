/// 2020.7.31 将记录类拆分为2个lei
#include <iostream>
#include <fstream>
#include "mylog.h"

namespace mylog {


MyLog cout("INFO:");
MyLog cerr("ERROR:");
MyLog cdbg("DEBUG:");
MyLog cwarn("WARN:");
MyLog csummary("SUMMARY:");
}

mylog::MyStreamBuf::MyStreamBuf()
{

}

mylog::MyStreamBuf::~MyStreamBuf()
{

}

int mylog::MyStreamBuf::overflow(int c)
{
    m_callback->foo(c);
    return 0;
}


mylog::MyLog::MyLog(std::string prefix) 
{
    m_stream_buf.m_callback = this;
    this->init(&m_stream_buf);
    is_c_cout = 1;
    m_is_new_line = 1;
    m_prefix=prefix;

    m_line_count = 0;

}

mylog::MyLog::~MyLog()
{


}


void mylog::MyLog::foo(char c)
{
    if(m_is_new_line)
    {
        m_is_new_line = 0;
        if(is_c_cout) std::cout<<m_prefix;
        if(m_log_stream.is_open()) m_log_stream<<m_prefix;


    }

    if(is_c_cout)std::cout.put(c);
    if(m_log_stream.is_open()) m_log_stream<<c;
    m_log_stream.flush();

    if(c=='\n')
    {
        m_is_new_line = 1;

        m_line_count++;
    }
}

int mylog::MyLog::set_log_file(std::string file_name)
{
    if(file_name.size()>0)
    {
        m_log_file_name = file_name;
    }

    if(m_log_stream.is_open())
    {
        m_log_stream.close();
    }
    m_log_stream.open(m_log_file_name.c_str(), std::ios_base::out| std::ios_base::app );
    return 0;
}

int mylog::MyLog::close_log_file()
{
    if(m_log_stream.is_open())
    {
        m_log_stream.close();
    }
    return 0;
}

int mylog::MyLog::set_cout_output(int is_out)
{
    is_c_cout = is_out;
    return 0;
}

mylog::MyLog &mylog::MyLog::print_hex(std::string istr, int num_of_one_line)
{
    for(unsigned i=0;i<istr.size();++i)
    {
        unsigned char A = istr[i];
        unsigned char AA = ((A & 0xf0)>>4);
        unsigned char AB = ((A & 0x0F)>>0);
            if((i!=0) &&(i%num_of_one_line==0))
            {
                foo('\n');
            }
            else
            {
                foo(' ');
            }
        foo(char_to_hex_disp(AA));
        foo(char_to_hex_disp(AB));
    }
    foo('\n');
    return *this;

}

unsigned char mylog::MyLog::char_to_hex_disp(unsigned char ia)
{
    if((ia>=0)&&
            (ia<=9))
    {
        return ia+'0';
    }
    else if ((ia>=10)&&
            (ia<=15))
    {
        return ia-10+'A';
    }
        return 'G';
}
