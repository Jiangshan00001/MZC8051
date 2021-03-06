#include <assert.h>
#include "icode.h"
#include "icodes.h"
#include "icode_float_func_opr.h"

icode_float_func_opr::icode_float_func_opr()
{
    m_float_add_func ="_sys_fpadd";
    m_float_sub_func="_sys_fpsub";
    m_float_mul_func="_sys_fpmul";
    m_float_div_func="_sys_fpdiv";


    m_i16_mul_func = "_sys_imul_byte2";
    m_i32_mul_func = "_sys_lmul_byte4";

    m_i16_idiv_func = "_sys_idiv_byte2";
    m_u16_udiv_func = "_sys_udiv_byte2";
    m_i32_idiv_func  = "_sys_ldiv_byte4";
    m_u32_udiv_func  = "_sys_uldiv_byte4";
}

int icode_float_func_opr::process_topcode(class icode * top_ic, void *user_data, class icode *iparent)
{
    std::vector<icode *> &top_icodes= top_ic->sub_icode;

    int *user_idata = (int*)user_data;

    if((user_data==NULL)||
            (*user_idata==0))
    {
        return icode_visitor::process_topcode(top_ic, user_data);
    }

    return second_cleanup(top_icodes);
}

int icode_float_func_opr::process_one_icode(icode *ic, std::vector<icode *> &parent, int index, void *user_data, class icode *iparent)
{
    if(ic->m_type!=ICODE_TYPE_EXP_OP)
    {
        return 0;
    }
    ///当前只处理float的+-*/运算
    ///

    std::string opr_list="+-*/+=-=*=/=%=";

    if(opr_list.find(ic->name.c_str())==opr_list.npos)
    {
        /// 没有需要替换的运算符
        return 0;
    }

    int ret = process_imul(ic, parent, index);
    if(ret)return 0;

    ret = process_idiv(ic, parent, index);
    if(ret)return 0;

    ret = process_imod(ic, parent, index);
    if(ret)return 0;

    if((ic->name=="+"))
    {
        opr_1_func_ex(m_float_add_func, ic,parent, index);
    }
    if(ic->name=="+=")
    {
        opr_1_func_ex_assign(m_float_add_func, ic,parent, index);
    }
    if((ic->name=="-"))
    {
        opr_1_func_ex(m_float_sub_func, ic,parent, index);
    }
    if(ic->name=="-=")
    {
        opr_1_func_ex_assign(m_float_sub_func, ic,parent, index);
    }

    if((ic->name=="*"))
    {
        opr_1_func_ex(m_float_mul_func, ic,parent, index);
    }
    if((ic->name=="*="))
    {
         opr_1_func_ex_assign(m_float_mul_func, ic,parent, index);
    }


    if((ic->name=="/"))
    {
        opr_1_func_ex(m_float_div_func, ic,parent, index);
    }
    if(ic->name=="/=")
    {
        opr_1_func_ex_assign(m_float_div_func, ic,parent, index);
    }

    return 0;
}

int icode_float_func_opr::second_cleanup(std::vector<icode *> &top_icodes)
{

    return 0;
}

int icode_float_func_opr::opr_1_func_ex(std::string func_name, icode *ic, std::vector<icode *> &parent, int index)
{
    if((!ic->left->is_float())&&
        (!ic->right->is_float())&&
            (!ic->result->is_float())
        )
    {
        ///运算符，全不是float类型，不作处理
        return 0;
    }
    icode *real_left = ic->left;
    icode *real_right = ic->right;
    icode *real_result = ic->result;

    if((!real_left->is_float())&&
            (!real_right->is_float())
            )
    {
        //左右都不是float，只有result是float
        //此时需要将结果放入临时变量int32，将临时变量转为float，再将float写入result
        icode * tmp_var = pcompi->new_temp_var();
        tmp_var->m_bit_width =  32;//FIXME 此处使用了常数，因为转为float最多只能是32bit的

        ic->result = pcompi->new_ref_icode(tmp_var);

        icode * cast_ic = pcompi->new_icode(ICODE_TYPE_CALL);
        //cast_ic->sub_icode.push_back(real_result);
        cast_ic->sub_icode.push_back(pcompi->new_ref_icode(tmp_var));
        cast_ic->result = pcompi->new_ref_icode( pcompi->get_function("_sys_fcast"));
        assert(cast_ic->result->result!=NULL);


        icode *ret_op_ic = pcompi->new_copy_icode_gen(pcompi->new_ref_icode(cast_ic->result->result->sub_icode[0]), pcompi->new_ref_icode(real_result));

        //parent.insert(parent.begin()+index, tmp_var);
        //index++;
        //parent.insert(parent.begin()+index+1, cast_ic);
        //parent.insert(parent.begin()+index+2, ret_op_ic);

        this->m_icode_to_insert_before_inst.push_back(tmp_var);
        this->m_icode_to_insert_after_inst.push_back(cast_ic);
        this->m_icode_to_insert_after_inst.push_back(ret_op_ic);

        return 0;
    }



    if(!ic->left->is_float())
    {
        /// left不是float，进行转换并放入临时变量
        /// 临时变量代替left和right进行fpadd

        icode *tmp_var = pcompi->new_temp_var();
        tmp_var->m_bit_width = 32;
        tmp_var->is_float32 = 1;

        ic->left = pcompi->new_ref_icode(tmp_var);

        icode * cast_ic = pcompi->new_icode(ICODE_TYPE_CALL);
        //cast_ic->sub_icode.push_back(pcompi->new_ref_icode(tmp_var));
        cast_ic->sub_icode.push_back(real_left);
        cast_ic->result = pcompi->new_ref_icode(pcompi->get_function("_sys_fcast"));
        assert(cast_ic->result->result!=NULL);

        icode *ret_op_ic = pcompi->new_copy_icode_gen(pcompi->new_ref_icode(cast_ic->result->result->sub_icode[0]), pcompi->new_ref_icode(tmp_var));

        //parent.insert(parent.begin()+index, tmp_var);
        //index++;
        //parent.insert(parent.begin()+index, cast_ic);
        //index++;
        //parent.insert(parent.begin()+index, ret_op_ic);
        //index++;
        this->m_icode_to_insert_before_inst.push_back(tmp_var);
        this->m_icode_to_insert_before_inst.push_back(cast_ic);
        this->m_icode_to_insert_before_inst.push_back(ret_op_ic);

    }
    if(!ic->right->is_float())
    {
        //left不是float，进行转换并放入临时变量
        /// 临时变量代替right和left进行fpadd

        icode *tmp_var = pcompi->new_temp_var();
        tmp_var->m_bit_width = 32;
        tmp_var->is_float32 = 1;

        ic->right = pcompi->new_ref_icode(tmp_var);

        icode * cast_ic = pcompi->new_icode(ICODE_TYPE_CALL);
        //cast_ic->sub_icode.push_back(pcompi->new_ref_icode(tmp_var));
        cast_ic->sub_icode.push_back(real_right);
        cast_ic->result = pcompi->new_ref_icode(pcompi->get_function("_sys_fcast"));
        assert(cast_ic->result->result!=NULL);


        icode *ret_op_ic = pcompi->new_copy_icode_gen(pcompi->new_ref_icode(cast_ic->result->result->sub_icode[0]), pcompi->new_ref_icode(tmp_var));

        //parent.insert(parent.begin()+index, tmp_var);
        //index++;
        //parent.insert(parent.begin()+index, cast_ic);
        //index++;
        //parent.insert(parent.begin()+index, ret_op_ic);
        //index++;
        this->m_icode_to_insert_before_inst.push_back(tmp_var);
        this->m_icode_to_insert_before_inst.push_back(cast_ic);
        this->m_icode_to_insert_before_inst.push_back(ret_op_ic);
    }


    assert((ic->left->is_float())&&
        (ic->right->is_float())&&
            (ic->result->is_float())
        );
    {
        ///运算符，全float类型
        ///
        ic->m_type = ICODE_TYPE_CALL;
        ic->sub_icode.clear();
        //ic->sub_icode.push_back(ic->result);
        ic->sub_icode.push_back(ic->left);
        ic->sub_icode.push_back(ic->right);
        ic->left = NULL;
        ic->right = NULL;
        ic->result = NULL;
        ic->result = pcompi->new_ref_icode(pcompi->get_function(func_name));
        assert(ic->result->result!=NULL);


    }


    if(!real_result->is_float())
    {
        //结果不是float，则
        // 添加临时变量，将计算float结果转为int，再写入result
        icode * cast_ic = pcompi->new_icode(ICODE_TYPE_CALL);
        cast_ic->sub_icode.push_back(pcompi->new_ref_icode(ic->result->result->sub_icode[0]));
        cast_ic->result = pcompi->new_ref_icode(pcompi->get_function("_sys_castf"));
        assert(cast_ic->result->result!=NULL);


        icode *ret_op_ic = pcompi->new_copy_icode_gen(pcompi->new_ref_icode(cast_ic->result->result->sub_icode[0]), pcompi->new_ref_icode(real_result));


        //parent.insert(parent.begin()+index+1, cast_ic);
        //parent.insert(parent.begin()+index+2, ret_op_ic);
        this->m_icode_to_insert_after_inst.push_back(cast_ic);
        this->m_icode_to_insert_after_inst.push_back(ret_op_ic);

    }
    else
    {
        icode *ret_op_ic = pcompi->new_copy_icode_gen(pcompi->new_ref_icode(ic->result->result->sub_icode[0]), pcompi->new_ref_icode(real_result));
        //parent.insert(parent.begin()+index+1, ret_op_ic);
        this->m_icode_to_insert_after_inst.push_back(ret_op_ic);
    }

    return 0;
}

int icode_float_func_opr::opr_1_func_ex_assign(std::string func_name, icode *ic, std::vector<icode *> &parent, int index)
{
    if(
        (!ic->right->is_float())&&
            (!ic->result->is_float())
        )
    {
        ///运算符，全部是float类型，不作处理
        return 0;
    }
    icode *real_left = ic->left;//left是空的
    icode *real_right = ic->right;
    icode *real_result = ic->result;


    if(!real_right->is_float())
    {
        //left不是float，进行转换并放入临时变量
        /// 临时变量代替right和left进行fpadd

        icode *tmp_var = pcompi->new_temp_var();
        tmp_var->m_bit_width = 32;
        tmp_var->is_float32 = 1;

        ic->right = pcompi->new_ref_icode(tmp_var);

        icode * cast_ic = pcompi->new_icode(ICODE_TYPE_CALL);
        //cast_ic->sub_icode.push_back(pcompi->new_ref_icode(tmp_var));
        cast_ic->sub_icode.push_back(real_right);
        cast_ic->result = pcompi->new_ref_icode(pcompi->get_function("_sys_fcast"));
        assert(cast_ic->result->result!=NULL);


        icode *ret_op_ic = pcompi->new_copy_icode_gen(pcompi->new_ref_icode(cast_ic->result->result->sub_icode[0]), pcompi->new_ref_icode(tmp_var));

        //parent.insert(parent.begin()+index, tmp_var);
        //index++;
        //parent.insert(parent.begin()+index, cast_ic);
        //index++;
        //parent.insert(parent.begin()+index, ret_op_ic);
        //index++;
        this->m_icode_to_insert_before_inst.push_back(tmp_var);
        this->m_icode_to_insert_before_inst.push_back(cast_ic);
        this->m_icode_to_insert_before_inst.push_back(ret_op_ic);
    }

    icode * float_result = real_result;


    if(!float_result->is_float())
    {
        //result不是float，则换换为float，再计算


        icode *tmp_var = pcompi->new_temp_var();
        tmp_var->m_bit_width = 32;
        tmp_var->is_float32 = 1;

        float_result = pcompi->new_ref_icode(tmp_var);

        icode * cast_ic = pcompi->new_icode(ICODE_TYPE_CALL);
        //cast_ic->sub_icode.push_back(pcompi->new_ref_icode(tmp_var));
        cast_ic->sub_icode.push_back(real_result);
        cast_ic->result = pcompi->new_ref_icode(pcompi->get_function("_sys_fcast"));
        assert(cast_ic->result->result!=NULL);


        icode *ret_op_ic = pcompi->new_copy_icode_gen(pcompi->new_ref_icode(cast_ic->result->result->sub_icode[0]), pcompi->new_ref_icode(tmp_var));

        //parent.insert(parent.begin()+index, tmp_var);
        //index++;
        //parent.insert(parent.begin()+index, cast_ic);
        //index++;
        //parent.insert(parent.begin()+index, ret_op_ic);
        //index++;
        this->m_icode_to_insert_before_inst.push_back(tmp_var);
        this->m_icode_to_insert_before_inst.push_back(cast_ic);
        this->m_icode_to_insert_before_inst.push_back(ret_op_ic);
    }


    {
        ///运算符，全float类型
        ///
        ic->m_type = ICODE_TYPE_CALL;
        ic->sub_icode.clear();

        ic->sub_icode.push_back(float_result);
        ic->sub_icode.push_back(ic->right);
        ic->left = NULL;
        ic->right = NULL;
        ic->result = NULL;
        ic->result = pcompi->new_ref_icode(pcompi->get_function(func_name));
        assert(ic->result->result!=NULL);
    }


    if(!real_result->is_float())
    {
        //结果不是float，则
        // 添加临时变量，将计算float结果转为int，再写入result
        icode * cast_ic = pcompi->new_icode(ICODE_TYPE_CALL);
        cast_ic->sub_icode.push_back(pcompi->new_ref_icode(float_result));
        cast_ic->result = pcompi->new_ref_icode(pcompi->get_function("_sys_castf"));
        assert(cast_ic->result->result!=NULL);


        icode *ret_op_ic = pcompi->new_copy_icode_gen(pcompi->new_ref_icode(cast_ic->result->result->sub_icode[0]), pcompi->new_ref_icode(real_result));


        //parent.insert(parent.begin()+index+1, cast_ic);
        //parent.insert(parent.begin()+index+2, ret_op_ic);
        this->m_icode_to_insert_after_inst.push_back(cast_ic);
        this->m_icode_to_insert_after_inst.push_back(ret_op_ic);
    }

    return 0;
}


int icode_float_func_opr::process_imul(icode *ic, std::vector<icode *> &parent, int index)
{

    if((ic->name!="*")&&(ic->name!="*="))
    {
        return 0;
    }

    icode *real_right = ic->right;
    icode *real_left = ic->left;
    icode *real_result = ic->result;


    icode *right_def = pcompi->get_def_var(ic->right);
    icode *left_def = pcompi->get_def_var(ic->left);
    icode *result_def = pcompi->get_def_var(ic->result);


    if(ic->name=="*=")
    {
        left_def = result_def;
    }
    assert(right_def!=NULL);
    assert(left_def!=NULL);
    assert(result_def!=NULL);


    /// _sys_imul_byte2 int * int /  int * char / unsigned int *
    if(
        ((left_def->m_bit_width==16)||(right_def->m_bit_width==16))&&
            ((left_def->m_bit_width<=16)&&(right_def->m_bit_width<=16))&&
            (!left_def->is_float())&&(!right_def->is_float())

            )
    {
        //乘法，改为函数调用
        ic->m_type = ICODE_TYPE_CALL;
        ic->sub_icode.clear();
        ic->sub_icode.push_back(pcompi->new_ref_icode( left_def));
        ic->sub_icode.push_back(ic->right);
        ic->left = NULL;
        ic->right = NULL;
        ic->result = NULL;
        ic->result = pcompi->new_ref_icode(pcompi->get_function(m_i16_mul_func));
        assert(ic->result->result!=NULL);//2020.9.9 此处未include _sys_func_def.h时程序退出

        icode *ret_op_ic = pcompi->new_copy_icode_gen(pcompi->new_ref_icode(ic->result->result->sub_icode[0]), pcompi->new_ref_icode(real_result));

        //this->m_icode_to_insert_after_inst.insert(this->m_icode_to_insert_after_inst.end(), ret_op_ic);
        //parent.insert(parent.begin()+index+1, ret_op_ic);
        this->m_icode_to_insert_after_inst.push_back(ret_op_ic);
        return 1;
    }
    else if(
            ((left_def->m_bit_width==32)||(right_def->m_bit_width==32))&&
            (left_def->m_bit_width<=32)&&(right_def->m_bit_width<=32)&&
            (!left_def->is_float())&&(!right_def->is_float())

            )
    {
        //乘法，改为函数调用
        ic->m_type = ICODE_TYPE_CALL;
        ic->sub_icode.clear();
        ic->sub_icode.push_back(pcompi->new_ref_icode(left_def));
        ic->sub_icode.push_back(ic->right);
        ic->left = NULL;
        ic->right = NULL;
        ic->result = NULL;
        ic->result = pcompi->new_ref_icode(pcompi->get_function(m_i32_mul_func));
        assert(ic->result->result!=NULL);

        icode *ret_op_ic = pcompi->new_copy_icode_gen(pcompi->new_ref_icode(ic->result->result->sub_icode[0]), pcompi->new_ref_icode(real_result));

        //this->m_icode_to_insert_after_inst.insert(this->m_icode_to_insert_after_inst.end(), ret_op_ic);
        //parent.insert(parent.begin()+index+1, ret_op_ic);
        this->m_icode_to_insert_after_inst.push_back(ret_op_ic);
        return 1;
    }

    return 0;

}

int icode_float_func_opr::process_idiv(icode *ic, std::vector<icode *> &parent, int index)
{

    if((ic->name!="/")&&
            (ic->name!="/="))
    {
        return 0;
    }




    icode *real_right = ic->right;
    icode *real_left = ic->left;
    icode *real_result = ic->result;

    icode *right_def = pcompi->get_def_var(ic->right);
    icode *left_def = pcompi->get_def_var(ic->left);
    icode *result_def = pcompi->get_def_var(ic->result);

    /// _sys_imul_byte2 int * int /  int * char / unsigned int *


    if(ic->name=="/=")
    {
        left_def = result_def;
    }


    if(((ic->name=="/")||(ic->name=="/=")) &&
        (( left_def->get_bit_width()==8)||(right_def->get_bit_width()==8))&&
            ((left_def->get_bit_width()<=8)&&(right_def->get_bit_width()<=8))&&
            (!left_def->is_float())&&(!right_def->is_float())
            )
    {

        if((!left_def->is_signed)&&(!right_def->is_signed))
        {
            //两个都是无符号，不需要使用函数，而是后期直接翻译为汇编代码
            return 0;
        }

        //除法，改为函数调用
        ic->m_type = ICODE_TYPE_CALL;
        ic->sub_icode.clear();
        ic->sub_icode.push_back(pcompi->new_ref_icode(left_def));
        ic->sub_icode.push_back(ic->right);
        ic->left = NULL;
        ic->right = NULL;
        ic->result = NULL;


        ///有符号除法
        ic->result = pcompi->new_ref_icode(pcompi->get_function(m_i16_idiv_func));


        assert(ic->result->result!=NULL);
        icode *ret_op_ic = pcompi->new_copy_icode_gen(pcompi->new_ref_icode(ic->result->result->sub_icode[0]), pcompi->new_ref_icode(real_result));
        //parent.insert(parent.begin()+index+1, ret_op_ic);
        this->m_icode_to_insert_after_inst.push_back(ret_op_ic);
        return 1;
    }



    if(((ic->name=="/")||(ic->name=="/=")) &&
        (( left_def->m_bit_width==16)||(right_def->m_bit_width==16))&&
            ((left_def->m_bit_width<=16)&&(right_def->m_bit_width<=16))&&
            (!left_def->is_float())&&(!right_def->is_float())
            )
    {
        //乘法，改为函数调用
        ic->m_type = ICODE_TYPE_CALL;
        ic->sub_icode.clear();
        ic->sub_icode.push_back(pcompi->new_ref_icode(left_def));
        ic->sub_icode.push_back(ic->right);
        ic->left = NULL;
        ic->right = NULL;
        ic->result = NULL;



        if(left_def->is_signed|| right_def->is_signed)
        {
            ///有符号除法
            ic->result = pcompi->new_ref_icode(pcompi->get_function(m_i16_idiv_func));
        }
        else
        {
            ///无符号除法
            ic->result = pcompi->new_ref_icode(pcompi->get_function(m_u16_udiv_func));
        }

        assert(ic->result->result!=NULL);
        icode *ret_op_ic = pcompi->new_copy_icode_gen(pcompi->new_ref_icode(ic->result->result->sub_icode[0]), pcompi->new_ref_icode(real_result));
        //parent.insert(parent.begin()+index+1, ret_op_ic);
        this->m_icode_to_insert_after_inst.push_back(ret_op_ic);
        return 1;
    }

    if(((ic->name=="/")||(ic->name=="/="))&&
            ((left_def->m_bit_width==32)||(right_def->m_bit_width==32))&&
            (left_def->m_bit_width<=32)&&(right_def->m_bit_width<=32)&&
            (!left_def->is_float())&&(!right_def->is_float())

            )
    {
        //乘法，改为函数调用
        ic->m_type = ICODE_TYPE_CALL;
        ic->sub_icode.clear();
        ic->sub_icode.push_back(pcompi->new_ref_icode(left_def));
        ic->sub_icode.push_back(ic->right);
        ic->left = NULL;
        ic->right = NULL;
        ic->result = NULL;



        if(left_def->is_signed|| right_def->is_signed)
        {
            ///有符号除法
            ic->result = pcompi->new_ref_icode(pcompi->get_function(m_i32_idiv_func));
        }
        else
        {
            ///无符号除法
            ic->result = pcompi->new_ref_icode(pcompi->get_function(m_u32_udiv_func));
        }

        assert(ic->result->result!=NULL);
        icode *ret_op_ic = pcompi->new_copy_icode_gen(pcompi->new_ref_icode(ic->result->result->sub_icode[0]), pcompi->new_ref_icode(real_result));
        //parent.insert(parent.begin()+index+1, ret_op_ic);
        this->m_icode_to_insert_after_inst.push_back(ret_op_ic);
        return 1;
    }

    return 0;
}

int icode_float_func_opr::process_imod(icode *ic, std::vector<icode *> &parent, int index)
{
    if((ic->name!="%")&&
            (ic->name!="%="))
    {
        return 0;
    }




    icode *right = ic->right;
    icode *left = ic->left;
    icode *result = ic->result;


    icode *right_def = pcompi->get_def_var(ic->right);
    icode *left_def = pcompi->get_def_var(ic->left);
    icode *result_def = pcompi->get_def_var(ic->result);


    if(ic->name=="%=")
    {
        left_def = result_def;
    }



    if(((ic->name=="%")||(ic->name=="%=")) &&
        ((left_def->m_bit_width==8)||(right_def->m_bit_width==8))&&
            ((left_def->m_bit_width<=8)&&(right_def->m_bit_width<=8))&&
            (!left_def->is_float())&&(!right_def->is_float())
            )
    {


        ///求余。 8bit数值
        ///
        ///

        if((!left_def->is_signed)&&(!right_def->is_signed))
        {
            //两个都是无符号，不需要使用函数，而是后期直接翻译为汇编代码
            return 0;
        }

        icode *real_result = ic->result;
        //乘法，改为函数调用
        ic->m_type = ICODE_TYPE_CALL;
        ic->sub_icode.clear();
        ic->sub_icode.push_back(pcompi->new_ref_icode(left_def));
        ic->sub_icode.push_back(ic->right);
        ic->left = NULL;
        ic->right = NULL;
        ic->result = NULL;

        /// TODO: imode可以使用byte1，需要添加系统函数
        ///有符号除法
        ic->result = pcompi->new_ref_icode(pcompi->get_function("_sys_imod_byte2"));

        assert(ic->result->result!=NULL);
        icode *ret_op_ic = pcompi->new_copy_icode_gen(pcompi->new_ref_icode(ic->result->result->sub_icode[0]), pcompi->new_ref_icode(real_result));
        //parent.insert(parent.begin()+index+1, ret_op_ic);
        this->m_icode_to_insert_after_inst.push_back(ret_op_ic);
        return 1;
    }
    else  if(((ic->name=="%")||(ic->name=="%=")) &&
        ((left_def->m_bit_width==16)||(right_def->m_bit_width==16))&&
            ((left_def->m_bit_width<=16)&&(right_def->m_bit_width<=16))&&
            (!left_def->is_float())&&(!right_def->is_float())
            )
    {
        ///求余。 16bit数值

        icode *real_result = ic->result;
        //乘法，改为函数调用
        ic->m_type = ICODE_TYPE_CALL;
        ic->sub_icode.clear();
        ic->sub_icode.push_back(pcompi->new_ref_icode(left_def));
        ic->sub_icode.push_back(ic->right);
        ic->left = NULL;
        ic->right = NULL;
        ic->result = NULL;



        if(left_def->is_signed|| right_def->is_signed)
        {
            ///有符号除法
            ic->result = pcompi->new_ref_icode(pcompi->get_function("_sys_imod_byte2"));
        }
        else
        {
            ///无符号除法
            ic->result = pcompi->new_ref_icode(pcompi->get_function("_sys_umod_byte2"));
        }

        assert(ic->result->result!=NULL);
        icode *ret_op_ic = pcompi->new_copy_icode_gen(pcompi->new_ref_icode(ic->result->result->sub_icode[0]), pcompi->new_ref_icode(real_result));
        //parent.insert(parent.begin()+index+1, ret_op_ic);
        this->m_icode_to_insert_after_inst.push_back(ret_op_ic);
        return 1;
    }
    else if(((ic->name=="%")||(ic->name=="%="))&&
            ((left_def->m_bit_width==32)||(right_def->m_bit_width==32))&&
            (left_def->m_bit_width<=32)&&(right_def->m_bit_width<=32)&&
            (!left_def->is_float())&&(!right_def->is_float())

            )
    {
        ///求余。 32bit数值

        icode *real_result = ic->result;
        //乘法，改为函数调用
        ic->m_type = ICODE_TYPE_CALL;
        ic->sub_icode.clear();
        ic->sub_icode.push_back(pcompi->new_ref_icode(left_def));
        ic->sub_icode.push_back(ic->right);
        ic->left = NULL;
        ic->right = NULL;
        ic->result = NULL;



        if(left_def->is_signed|| right_def->is_signed)
        {
            ///有符号除法
            ic->result = pcompi->new_ref_icode(pcompi->get_function("_sys_lmod_byte4"));
        }
        else
        {
            ///无符号除法
            ic->result = pcompi->new_ref_icode(pcompi->get_function("_sys_ulmod_byte4"));
        }

        assert(ic->result->result!=NULL);
        icode *ret_op_ic = pcompi->new_copy_icode_gen(pcompi->new_ref_icode(ic->result->result->sub_icode[0]), pcompi->new_ref_icode(real_result));
        //parent.insert(parent.begin()+index+1, ret_op_ic);
        this->m_icode_to_insert_after_inst.push_back(ret_op_ic);
        return 1;
    }

    return 0;
}



