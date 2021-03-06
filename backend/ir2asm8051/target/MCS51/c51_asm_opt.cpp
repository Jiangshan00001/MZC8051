#include <sstream>
#include "trim.h"
#include "split.h"
#include "replace.h"
#include "c51_asm_opt.h"

c51_asm_opt::c51_asm_opt()
{
}

std::string c51_asm_opt::pin_hole(std::string &in_asm)
{
    std::stringstream istr_in(in_asm);
    std::stringstream istr_out;
    //针孔优化


    std::string one_line;

    std::string last_match_opr;
    std::string last_match_addr;
    int last_match1=0;

    while(std::getline(istr_in,one_line ))
    {
        ///获取一行
        trim(one_line);

        if(one_line.empty())
        {
            istr_out<<"\n";
            continue;
        }

        if(one_line[0]==';')
        {
            //注释
            istr_out<<one_line<<"\n";
            continue;
        }


        bool is_match = 0;
        if(one_line.find("MOV")!=one_line.npos)
        {
            /// 针对这种情况，进行优化，去除下一行
            ///MOV 0x9, A;
            /// MOV A, 0x9;
            ///
            ///
            std::vector<std::string> mov_bb = split(one_line, " ", 1);
            if(mov_bb.size()==3)
            {
                replace(mov_bb[1],",", "");
                replace(mov_bb[2],";", "");
                if((mov_bb[2]=="A"))
                {
                    last_match_opr = mov_bb[0];
                    last_match_addr = mov_bb[1];
                    last_match1 = 1;
                }
                else if(last_match1)
                {
                    last_match1 = 0;
                    if((mov_bb[1]=="A")
                            )
                    {
                        if((mov_bb[0]==last_match_opr)&&
                                (last_match_addr==mov_bb[2])
                                )
                        {
                            //此行去掉，后期不会处理
                            is_match=1;
                        }
                    }
                }
            }
        }
        else
        {
            last_match1=0;
        }


        if(!is_match)
        {
            ///没有被优化，直接放到输出
            istr_out<<one_line<<"\n";
        }



    }





    return istr_out.str();

}
