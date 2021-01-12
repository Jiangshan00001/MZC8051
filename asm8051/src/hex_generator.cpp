#include <iostream>
#include <iosfwd>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <split.h>
#include <trim.h>
#include <assert.h>
#include "hex_generator.h"


std::string HByteToStr(const unsigned char mC)
{
	unsigned char mTmpStr[4]={0,0,0,0};
	///0--F
	if (mC<0xA)
	{
		mTmpStr[0] =(mC+'0');
	}
	else
	{
		mTmpStr[0] =(mC-10+'A');
	}
	return std::string((char*)mTmpStr);
}

unsigned char HStrToByte(const unsigned char mC)
{
    //unsigned char mTmpStr[4]={0,0,0,0};
    ///0--F
    if (mC<'A')
    {
         return (mC-'0');
    }
    return (mC-'A'+10);
}

std::string ByteToStr(const unsigned char mC)
{
    ///0x12(int)--->"12"(str)
	unsigned a = ((mC&0xf0)>>4);
	unsigned b = (mC&0x0f);

	return HByteToStr(a) + HByteToStr(b) ;	
}

unsigned int StrToByte(std::string mC)
{
    ///"12"(str)--->0x12(int)

    unsigned int a = HStrToByte(mC[0]);
    unsigned int b = HStrToByte(mC[1]);

    return (unsigned int)(b+a*16);
}



//: 10 1234 00 021234513F2925102724123935143734  2A
//:1012440047413F5E5556575487520953784382812C
//:0E125400B081B534E6B443E3BE54E0B654DDD9
//:00000001FF

///格式说明 : 每一行前为":"
/// 1字节为数据个数"10"
/// 2字节为数据起始地址"1234"
/// 1字节为数据类型， 00---数据记录，01--文件结束记录
/// 1字节为 校验码



std::vector< unsigned int> hex_str_to_ints(std::string mstr1)
{
    std::vector< unsigned int> ret ;

    for(unsigned i=0;i<mstr1.size();)
    {
        unsigned int a = StrToByte(mstr1.substr(i,2));
        i+=2;
        ret.push_back(a);
    }
    return ret;
}


std::vector<hex_block> hex_file_to_hex_data(std::string hex_file_data)
{
    std::vector<std::string> lines = split(hex_file_data,"\n");
    unsigned long line_addr = 0;
    std::vector<hex_block> ret;

    for(unsigned i=0;i<lines.size();++i)
    {
        hex_block m_block;
        std::string one_line = trim(lines[i]);
        if(one_line.size()==0)
        {
            continue;
        }

        one_line=one_line.substr(1);//去掉 :
        std::vector< unsigned int> ints = hex_str_to_ints(one_line);

        assert(ints.size()>3);

        unsigned long data_num = ints[0];
        unsigned long data_addr = (ints[1]<<8)+(ints[2]);
        unsigned long data_type = ints[3];

        if(data_type==1)
        {
            //eof
            break;
        }
        m_block.m_address = data_addr + line_addr;
        m_block.m_bin.resize(data_num);
        for(unsigned j=0;j<data_num;j++)
        {
            m_block.m_bin[j] = ints[j+4];
        }
        m_block.m_crc = ints[data_num+4];
        ret.push_back(m_block);
    }



    ///对于多个block，查看是否有可以合并的，如果有，则合并
    /// 合并之前，先按照地址大小进行排序，小地址放前面

    std::sort(ret.begin(), ret.end(), hex_block_cmp);


    for(int i=0;i<((int)ret.size())-1;)
    {
        if(ret[i].m_address+ret[i].m_bin.size()==ret[i+1].m_address)
        {
            ret[i].m_bin = ret[i].m_bin + ret[i+1].m_bin;
            ret.erase(ret.begin()+i+1);
        }
        else
        {
            i++;
        }
    }

    return ret;
}


int hex_data_to_hex_file_format(unsigned long address, std::string hex_data, std::stringstream &file_out)
{
    unsigned long mAddressHead;
    unsigned long mAddress;

    mAddressHead = mAddress = address;

    ///everything done. flush all to file
    while((mAddress-mAddressHead<hex_data.size()))
    {
        if ((hex_data.size() - (mAddress-mAddressHead))>=0x10)
        {
            //写入0x10个字节
            file_out<<":";//起始字节
            file_out<<"10";//数据个数

            file_out<<ByteToStr((mAddress>>8)) ;
            file_out<<ByteToStr(mAddress);//地址
            file_out<<"00";//数据类型
            unsigned char mCheckByte = 0x10+((mAddress>>8)&0xff)+(mAddress&0xff);
            for (int j=0;j<0x10;j++)
            {
                file_out<<ByteToStr(hex_data[mAddress-mAddressHead]);//数据类型
                mCheckByte += hex_data[mAddress-mAddressHead];
                mAddress++;
            }
            mCheckByte = -mCheckByte;
            file_out<<ByteToStr(mCheckByte);
            file_out<<"\n";
        }
        else
        {
            //有多少字节，写多少字节
            int mBytesLeft = hex_data.size() - (mAddress-mAddressHead);
            //写入mBytesLeft个字节
            file_out<<":";//起始字节
            file_out<<ByteToStr(mBytesLeft);//数据个数

            file_out<<ByteToStr((mAddress>>8)) ;
            file_out<<ByteToStr(mAddress);//地址
            file_out<<"00";//数据类型
            unsigned char mCheckByte = mBytesLeft+((mAddress>>8)&0xff)+(mAddress&0xff);
            for (int j=0;j<mBytesLeft;j++)
            {
                file_out<<ByteToStr(hex_data[mAddress-mAddressHead]);//数据类型
                mCheckByte += hex_data[mAddress-mAddressHead];
                mAddress++;
            }
            mCheckByte = (-mCheckByte);
            file_out<<ByteToStr(mCheckByte);
            file_out<<"\n";
        }
    }

    return 0;
}

std::string hex_data_to_hex_file(std::vector<hex_block> hex_data)
{
    std::stringstream ret;
    if(hex_data.empty())
    {
        return ret.str();
    }
    std::vector<hex_block> &text_block = hex_data;

    //////////////////////////////////////////////////////////////////////////
    /// skip
    while(text_block[0].m_bin.empty())
    {
        text_block.erase(text_block.begin());
    }
    for (unsigned i1=0;i1<text_block.size();++i1)
    {
        if (text_block[i1].m_bin.empty())
        {
            // no code. skip it
            text_block.erase(text_block.begin()+i1);
            --i1;
        }
    }
    //////////////////////////////////////////////////////////////////////////
    /// continuous address code, merge to one block
    for (unsigned i2=1;i2<text_block.size();++i2)
    {
        if (text_block[i2-1].m_address+text_block[i2-1].m_bin.size()== text_block[i2].m_address)
        {
            //merge
            text_block[i2-1].m_bin = text_block[i2-1].m_bin + text_block[i2].m_bin;
            text_block.erase(text_block.begin()+i2);
            --i2;
        }
    }


    //////////////////////////////////////////////////////////////////////////
    for (unsigned i3=0;i3<text_block.size();++i3)
    {
        hex_data_to_hex_file_format(text_block[i3].m_address,text_block[i3].m_bin, ret);
    }

    //file end：End of File Record
    ret<<":00000001FF"<<"\n";

    return ret.str();
}


std::string hex_generator_str(T_ASM_CONTEXT *mCtx)
{

    std::stringstream ret;


    if (mCtx->m_text_block.empty())
    {
        return ret.str();
    }


    std::vector<hex_block> text_block;


    for(unsigned i=0;i<mCtx->m_text_block.size();++i)
    {
        hex_block one;
        one.m_bin = mCtx->m_text_block[i].m_hex_text;
        one.m_address = mCtx->m_text_block[i].m_address;
        text_block.push_back(one);
    }

    return hex_data_to_hex_file(text_block);
#if 0



    std::vector<T_HEX_TEXT_BLOCK> text_block;

    //////////////////////////////////////////////////////////////////////////
    text_block = mCtx->m_text_block;//copy
    //////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////
    /// skip
    while(text_block[0].m_hex_text.empty())
    {
        text_block.erase(text_block.begin());
    }
    for (unsigned i1=0;i1<text_block.size();++i1)
    {
        if (text_block[i1].m_hex_text.empty())
        {
            // no code. skip it
            text_block.erase(text_block.begin()+i1);
            --i1;
        }
    }
    //////////////////////////////////////////////////////////////////////////
    /// continuous address code, merge to one block
    for (unsigned i2=1;i2<text_block.size();++i2)
    {
        if (text_block[i2-1].m_address+text_block[i2-1].m_hex_text.size()== text_block[i2].m_address)
        {
            //merge
            text_block[i2-1].m_hex_text = text_block[i2-1].m_hex_text + text_block[i2].m_hex_text;
            text_block.erase(text_block.begin()+i2);
            --i2;
        }
    }


    //////////////////////////////////////////////////////////////////////////
    for (unsigned i3=0;i3<text_block.size();++i3)
    {
        hex_data_to_hex_file_format(text_block[i3].m_address,text_block[i3].m_hex_text, ret);
    }

    //file end：End of File Record
    ret<<":00000001FF"<<"\n";

    return ret.str();
    #endif
}

#if 0
bool operator <(hex_block &a, hex_block &b)
{
    if(a.m_address<b.m_address)return true;
    return false;

}
#endif


 bool hex_block::operator <( hex_block &b)
{
    if(m_address<b.m_address)return true;
    return false;
}


bool hex_block_cmp(hex_block a, hex_block b)
{
    if(a.m_address<b.m_address)return true;
    return false;
}
