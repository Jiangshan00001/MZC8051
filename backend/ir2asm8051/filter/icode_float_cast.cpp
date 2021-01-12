#include "icode.h"
#include "icodes.h"
#include "icode_float_cast.h"
#include "mylog.h"

using mylog::cerr;

icode_float_cast::icode_float_cast()
{
}


icode *icode_float_cast::new_to_float_icode(icode *ic, icode ** tmp_val)
{

    icode * call_cast = pcompi->new_icode(ICODE_TYPE_CALL);

    call_cast->sub_icode.clear();
    call_cast->sub_icode.push_back(pcompi->new_ref_icode(ic));

    sym* s = pcompi->m_sym_manage.find_symbol("_sys_fcast");

    call_cast->result = pcompi->new_ref_icode( s->def_icode);
    assert(call_cast->result->result!=NULL);

    *tmp_val = pcompi->new_ref_icode(pcompi->get_def_var(call_cast->result)->sub_icode[0]);

    return call_cast;
}
icode *icode_float_cast::new_float_to_int_icode(icode *ic, icode ** tmp_val)
{

    icode * call_cast = pcompi->new_icode(ICODE_TYPE_CALL);

    call_cast->sub_icode.clear();
    call_cast->sub_icode.push_back(ic);


    sym* s = pcompi->m_sym_manage.find_symbol("_sys_castf");

    call_cast->result = pcompi->new_ref_icode( s->def_icode );
    assert(call_cast->result->result!=NULL);

    *tmp_val = pcompi->new_ref_icode(pcompi->get_def_var(call_cast->result)->sub_icode[0]);

    return call_cast;
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

    if((ic->m_type==ICODE_TYPE_EXP_OP)&&
            ((ic->name=="=")||
             (ic->name=="+=")||
             (ic->name=="-=")||
             (ic->name=="*=")||
             (ic->name=="/=")||
             (ic->name=="%=")||
             (ic->name=="&=")||
             (ic->name=="|=")||
             (ic->name=="^=")||
             (ic->name=="<<=")||
             (ic->name==">>=")
             )
            )
    {
        /// =号， 如果是float a = 1; 或者 int a; float b; a=b; b=a;此时需要类型转换函数插入操作
        /// 先转换类型，再赋值
        icode *right = pcompi->get_def_var(ic->right);
        icode *result = pcompi->get_def_var(ic->result);

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

            /// =号。右边是float，左边不是float
            /// 需要将float转为int
            /// _sys_castf
            ///
            ///

            ic->right = new_tmp_val;
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

            ic->right = new_tmp_val;
            //parent.insert(parent.begin()+index,call_cast);
            this->m_icode_to_insert_before_inst.push_back(call_cast);
            return 1;
        }
        return 0;
    }
    if((ic->m_type==ICODE_TYPE_EXP_OP)&&
            ((ic->name=="+")||
             (ic->name=="-")||
             (ic->name=="*")||
             (ic->name=="/")||
             (ic->name=="%")||
             (ic->name=="&")||
             (ic->name=="|")||
             (ic->name=="^")||
             (ic->name=="<<")||
             (ic->name==">>")

             )
            )
    {
        icode *right = pcompi->get_def_var(ic->right);
        icode *left = pcompi->get_def_var(ic->left);
        icode *result = pcompi->get_def_var(ic->result);

        if(result==NULL)
        {
            //没有result。结果无用？？
            return 0;
        }


        if(right->is_float()&& left->is_float() && result->is_float())
        {
            return 0;
        }

        if((!right->is_float())&& (!left->is_float()) && (!result->is_float()))
        {
            return 0;
        }


        if((right->is_float())&&(!left->is_float()))
        {
            icode *new_tmp_val;
            icode * call_cast_ic = new_to_float_icode(ic->left, &new_tmp_val);
            ic->left = new_tmp_val;
            //parent.insert(parent.begin()+index,call_cast_ic);
            //index++;
            this->m_icode_to_insert_before_inst.push_back(call_cast_ic);
        }
        if((!right->is_float())&&(left->is_float()))
        {
            icode *new_tmp_val;
            icode * call_cast_ic = new_to_float_icode(ic->right, &new_tmp_val);
            ic->right = new_tmp_val;
            //parent.insert(parent.begin()+index,call_cast_ic);
            //index++;
            this->m_icode_to_insert_before_inst.push_back(call_cast_ic);
        }

        if((
                    (ic->name=="==")||
                    (ic->name=="!=")||
                    (ic->name=="<")||
                    (ic->name==">")||
                    (ic->name=="<=")||
                    (ic->name==">=")
                    ))
        {
            //比较算符，result如果是float，则需要转换
            if(result->is_float())
            {
                icode *new_tmp_val = pcompi->new_temp_var();
                icode *new_tmp_val2;
                ic->result = new_tmp_val;
                new_tmp_val->m_bit_width=8;
                icode * call_cast_ic = new_to_float_icode(new_tmp_val, &new_tmp_val2);

                icode *mov = pcompi->new_copy_icode_gen(new_tmp_val2, result);

                //parent.insert(parent.begin()+index,new_tmp_val);
                //index++;
                //parent.insert(parent.begin()+index+1,call_cast_ic);
                //parent.insert(parent.begin()+index+2,mov);
                this->m_icode_to_insert_before_inst.push_back(new_tmp_val);
                this->m_icode_to_insert_after_inst.push_back(call_cast_ic);
                this->m_icode_to_insert_after_inst.push_back(mov);
            }

            return 0;
        }
        if((result->is_float())&&(!left->is_float()))
        {
            icode *new_tmp_val = pcompi->new_temp_var();
            icode *new_tmp_val2;
            ic->result = new_tmp_val;
            new_tmp_val->set_width_from(left);
            icode * call_cast_ic = new_to_float_icode(new_tmp_val, &new_tmp_val2);

            icode *mov = pcompi->new_copy_icode_gen(new_tmp_val2, result);


            //parent.insert(parent.begin()+index,new_tmp_val);
            //index++;
            //parent.insert(parent.begin()+index+1,call_cast_ic);
            //parent.insert(parent.begin()+index+2,mov);
            this->m_icode_to_insert_before_inst.push_back(new_tmp_val);
            this->m_icode_to_insert_after_inst.push_back(call_cast_ic);
            this->m_icode_to_insert_after_inst.push_back(mov);
        }
        else if((!result->is_float())&&(left->is_float()))
        {
            icode *new_tmp_val = pcompi->new_temp_var();
            icode *new_tmp_val2;
            ic->result = new_tmp_val;
            new_tmp_val->set_width_from(left);
            new_tmp_val->is_float32 = 1;

            icode * call_cast_ic = new_float_to_int_icode(new_tmp_val, &new_tmp_val2);

            icode *mov = pcompi->new_copy_icode_gen(new_tmp_val2, result);



            //parent.insert(parent.begin()+index,new_tmp_val);
            //index++;
            //parent.insert(parent.begin()+index+1,call_cast_ic);
            //parent.insert(parent.begin()+index+2,mov);
            this->m_icode_to_insert_before_inst.push_back(new_tmp_val);
            this->m_icode_to_insert_after_inst.push_back(call_cast_ic);
            this->m_icode_to_insert_after_inst.push_back(mov);
        }
    }



    return 0;
}

