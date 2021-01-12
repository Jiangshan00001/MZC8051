#include "icode.h"
#include "icode_func.h"


std::string icode::get_func_label(std::string fname)
{
    return "_func_"+fname;
}

std::string icode::get_func_label()
{
    if(is_naked)
    {
        return this->name;
    }

    return get_func_label(this->name);
}

std::string icode::get_func_end_label()
{
    if(m_reg_params_desc.size()>0)
    {
        return this->name+"_end";
    }

    return "_func_"+this->name+"_end";
}

std::string icode::get_func_ret_label()
{
    if(m_reg_params_desc.size()>0)
    {
        return this->name+"_ret_LABEL";
    }

    return "_func_"+this->name+"_ret_LABEL";
}

int icode::to_dot_func(std::string &def_str, std::string &ref_str)
{
    std::stringstream stA;

    ref_str = this->get_dot_name();

    if(this->m_type==ICODE_TYPE_FUNC)
    {

        stA.clear();
        stA.str("");


        stA<<"subgraph " <<ref_str<< "{\n"<<
                 "label=\""<< this->name<<"\"\n";



        ///---------------
        /// 添加函数属性

        if(is_regparams)
        {
            stA<<"\""<< "regparams:"<< this->m_reg_params_desc<<"\"\n";
        }

        std::string ref_str_last;
        for(unsigned i=0;i<this->sub_icode.size();++i)
        {
            std::string def_str1, ref_str1;
            this->sub_icode[i]->to_dot(def_str1, ref_str1);
            stA<< def_str1;


            ref_str1 = this->sub_icode[i]->get_dot_start_name_ref_block();

            if(i>0)
            {
                stA<< ref_str_last<<"->"<< ref_str1<<"[color=red]\n";
            }

            ref_str1 = this->sub_icode[i]->get_dot_end_name_ref_block();

            ref_str_last = ref_str1;
        }

        stA<<"}\n";
        def_str=stA.str();
    }
    else if(this->m_type==ICODE_TYPE_CALL)
    {
        stA<<ref_str<<" [label=call]\n";

        if(this->result){
            std::string def_str1, ref_str1;
            this->result->to_dot(def_str1, ref_str1);
            stA<<def_str1;
            stA<<ref_str<<"->"<< ref_str1<<"[label=result]\n";
        }



        std::string ref_str_last;
        for(unsigned i=0;i<this->sub_icode.size();++i)
        {
            std::string def_str1, ref_str1;
            this->sub_icode[i]->to_dot(def_str1, ref_str1);

            stA<<def_str1;

            stA<<ref_str<<"->" << ref_str1<<"[label=subi_"<< i<< "]\n";
        }


        def_str = stA.str();
    }
    else if(m_type==ICODE_TYPE_BLOCK)
    {
        ref_str=this->get_dot_name();
        stA<<" subgraph "<< ref_str<<"{\nlabel="<<ref_str<<"\n";

        if(this->sub_icode.size()>0){
            std::string ref_str_last;
            for(unsigned i=0;i<this->sub_icode.size();++i)
            {
                std::string def_str1, ref_str1;
                this->sub_icode[i]->to_dot(def_str1, ref_str1);

                stA<<def_str1;
                ref_str1 = this->sub_icode[i]->get_dot_start_name_ref_block();

                if(i>0)
                {
                    stA<< ref_str_last<<"->"<< ref_str1<<"[color=red style=dotted]\n";
                }

                ref_str1 = this->sub_icode[i]->get_dot_end_name_ref_block();
                ref_str_last = ref_str1;
            }
        }
        else{
            //stA<<"EMPTY\n";
        }


        stA<<"}\n";

        def_str = stA.str();
    }



    return 0;
}


