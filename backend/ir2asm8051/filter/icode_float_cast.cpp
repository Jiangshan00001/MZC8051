#include "icode.h"
#include "icodes.h"
#include "icode_float_cast.h"
#include "mylog.h"

using mylog::cerr;

icode_float_cast::icode_float_cast()
{
}

void icode_float_cast::execute(icodes *ics)
{
    pcompi = ics;
    process_topcode(ics->m_top_icodes);
}


icode *icode_float_cast::new_to_float_icode(icode *ic, icode ** tmp_val)
{

    icode *code_block = pcompi->new_icode(ICODE_TYPE_BLOCK);

    icode * call_cast = pcompi->new_icode(ICODE_TYPE_CALL);

    call_cast->sub_icode.clear();
    call_cast->sub_icode.push_back(pcompi->new_ref_icode(ic));

    sym* s = pcompi->m_sym_manage.find_symbol("_sys_fcast");

    call_cast->result = pcompi->new_ref_icode( s->def_icode);
    assert(call_cast->result->result!=NULL);

    icode *func_ret_ref = pcompi->new_ref_icode(pcompi->get_def_var(call_cast->result)->sub_icode[0]);

    icode *tmp_val2 = pcompi->new_temp_var(pcompi->get_def_var(func_ret_ref));
    tmp_val2->m_type=ICODE_TYPE_DEF_VAR_TMP;//此处func_ret_ref的类型是RET_TYPE
    tmp_val2->m_register_desc="";
    tmp_val2->m_reg_params_desc="";

    icode *ret_mov = pcompi->new_opr_icode("=", NULL, func_ret_ref,tmp_val2);


    code_block->merge_icode(call_cast);
    code_block->merge_icode(tmp_val2);
    code_block->merge_icode(ret_mov);

    *tmp_val = pcompi->new_ref_icode(tmp_val2);
    return code_block;
}
icode *icode_float_cast::new_float_to_int_icode(icode *ic, icode ** tmp_val)
{

    icode * call_cast = pcompi->new_icode(ICODE_TYPE_CALL);

    call_cast->sub_icode.clear();
    call_cast->sub_icode.push_back(pcompi->new_ref_icode(ic));


    sym* s = pcompi->m_sym_manage.find_symbol("_sys_castf");

    assert(s!=NULL);
    call_cast->result = pcompi->new_ref_icode( s->def_icode );
    assert(call_cast->result->result!=NULL);

    *tmp_val = pcompi->new_ref_icode(pcompi->get_def_var(call_cast->result)->sub_icode[0]);

    return call_cast;
}

int count_is_float(icode* to_cnt, int &float_cnt, int &non_float_cnt)
{
    if(to_cnt==NULL)return 0;
    if(to_cnt->is_float())
    {
        float_cnt++;
    }
    else
    {
        non_float_cnt++;
    }
    return 0;
}

int icode_float_cast::process_one_icode(icode *ic, std::vector<icode *> &parent, int index, void *user_data, class icode *iparent)
{
    ///赋值运算符
    ///


    if(ic->m_type==ICODE_TYPE_CALL)
    {
        if((ic->result==NULL)||
                (ic->result->result==NULL))
        {
            //无函数？
            return 0;
        }



        ///函数调用，实参和形参必须一致，如果不一致，则转换
        for(unsigned i=0;i<ic->sub_icode.size();++i)
        {
            icode *right = ic->sub_icode[i];
            if(ic->result->result->sub_icode.size()<i+1)
            {
                //参数过多？
                cerr<<"parameter number not match? func_name="<< ic->result->result->name<<". param cnt="<< i<<". fun_para_cnt="<< ic->result->result->sub_icode.size()<<"\n";
                assert(0);
                return 0;
            }
            icode *result = ic->result->result->sub_icode[i+1];

            if((right->is_float())&&(result->is_float()))
            {
                return 0;
            }
            if((!right->is_float())&&(!result->is_float()))
            {
                return 0;
            }

            if((right->is_float())&&(!result->is_float()))
            {
                icode *new_tmp_val;
                icode * call_cast_to_float = new_float_to_int_icode(ic->right, &new_tmp_val);

                ic->sub_icode[i] = new_tmp_val;
                //parent.insert(parent.begin()+index,call_cast_to_float);
                this->m_icode_to_insert_before_inst.push_back(call_cast_to_float);
                return 1;
            }
            else if((!right->is_float())&&(result->is_float()))
            {
                //_sys_fcast
                /// 整数转为float
                icode *new_tmp_val;
                icode * call_cast = new_to_float_icode(ic->right, &new_tmp_val);

                ic->sub_icode[i] = new_tmp_val;
                //parent.insert(parent.begin()+index,call_cast);
                this->m_icode_to_insert_before_inst.push_back(call_cast);

                return 1;
            }
        }
        return 0;
    }


    if(ic->m_type!=ICODE_TYPE_EXP_OP)
    {
        ///只处理op的icode
        return 0;
    }

    int float_cnt=0;
    int non_float_cnt=0;
    count_is_float(ic->right,float_cnt, non_float_cnt);
    count_is_float(ic->left,float_cnt, non_float_cnt);
    count_is_float(ic->result,float_cnt, non_float_cnt);

    if((float_cnt==0)||(non_float_cnt==0))
    {
        //没有float或者没有非float操作符，直接返回
        return 0;
    }

    std::string op_str="=+=-=*=/=%=&=|=^=<<=>>=init";
    if(op_str.find(ic->name.c_str())==std::string::npos)
    {
        //不认识的算符
        return 0;
    }


    ///-----------------------------
    /// 2021.1.30 修正float的cast
    ///
    ///
    ///
    ///
    icode *right = pcompi->get_def_var(ic->right);
    icode *left = pcompi->get_def_var(ic->left);
    icode *result = pcompi->get_def_var(ic->result);

    if(right&&(!right->is_float()))
    {
        if(right->m_type==ICODE_TYPE_I_CONST)
        {
            right->m_type=ICODE_TYPE_F_CONST;
            right->fnum = float(right->num);
            if(left && left->is_float())
            {
                right->set_width_from(left);
            }
            else
            {
                right->set_width_from(result);
            }
        }
        else
        {
            icode *new_tmp_val;
            icode * call_cast_ic = new_to_float_icode(ic->right, &new_tmp_val);
            ic->right = pcompi->new_ref_icode(new_tmp_val);
            this->m_icode_to_insert_before_inst.push_back(call_cast_ic);
        }
    }
    if(left&&(!left->is_float()))
    {
        if(left->m_type==ICODE_TYPE_I_CONST)
        {
            left->m_type=ICODE_TYPE_F_CONST;
            left->fnum = float(left->num);
            if(right && right->is_float())
            {
                left->set_width_from(right);
            }
            else
            {
                left->set_width_from(result);
            }
        }
        else
        {
            icode *new_tmp_val;
            icode * call_cast_ic = new_to_float_icode(ic->left, &new_tmp_val);
            ic->left = pcompi->new_ref_icode(new_tmp_val);
            this->m_icode_to_insert_before_inst.push_back(call_cast_ic);
        }
    }
    if(result&&(!result->is_float()))
    {
        icode *new_tmp_val = pcompi->new_temp_var();
        new_tmp_val->is_float32 = 1;
        if(right && right->is_float())
        {
            new_tmp_val->set_width_from(right);
        }
        else
        {
            new_tmp_val->set_width_from(left);
        }

        ic->result = pcompi->new_ref_icode(new_tmp_val);


        icode *new_tmp_val2;
        icode * call_cast_ic = new_float_to_int_icode(new_tmp_val, &new_tmp_val2);

        icode *mov = pcompi->new_copy_icode_gen(new_tmp_val2, result);

        this->m_icode_to_insert_before_inst.push_back(new_tmp_val);
        this->m_icode_to_insert_after_inst.push_back(call_cast_ic);
        this->m_icode_to_insert_after_inst.push_back(mov);
    }



    return 0;
}

