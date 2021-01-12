#include <assert.h>
#include "icode.h"
#include "icodes.h"
#include "icode_ptr_calc.h"

///
///
///
/// \brief icode_ptr_calc::icode_ptr_calc
///
icode_ptr_calc::icode_ptr_calc()
{
    m_icodes.clear();
    m_icode_result = NULL;
}

int icode_ptr_calc::process_array_result(icode *ic, std::vector<icode *> &parent, int index, void *user_data, class icode *iparent)
{

    assert(ic->is_array + ic->result->is_array>=0);
    /// int a[2][4];
    /// int b;
    /// b=a[1][2];
    /// 此处是将a[1][2]生成icode代码：
    /// temp1=a;
    /// temp2 = 2[int]*1*4
    /// temp3 = 2[int]*2
    /// temp1+= temp2
    /// temp1+=temp3
    ///
    ///
    ///
    /// 地址计算公式
    /// 假设3维数组
    /// w1= ic->array_cnt[0] * m_bit_width_array_comp/8 * result_real->array_cnt[1] *result_real->array_cnt[2]
    /// w2= ic->array_cnt[1] * m_bit_width_array_comp/8* result_real->array_cnt[2]
    /// w3= ic->array_cnt[2] * m_bit_width_array_comp/8
    /// result_real->target->m_addr +w1 +w2 +w3

    icode *result_brief = ic;

    //申请一个通用指针的变量
    icode * result_new = pcompi->new_temp_ptr_var(ic->result->m_in_ptr_type, &m_target);


    /// temp1=a;
    icode *movB = pcompi->new_copy_icode_gen(pcompi->new_ref_icode(result_brief->result), pcompi->new_ref_icode(result_new));

    this->m_icodes.push_back(result_new);
    this->m_icodes.push_back(movB);

    int array_cnt= - ic->is_array;
    int curr_arr_idx=0;
    while(array_cnt<0)
    {
        icode *tmp1 = pcompi->new_temp_var();
        /// \todo 此处指针，直接手写为16bit 2020.8.18 因为c51中地址最大为2byte，此处只需要2byte，最高byte类型在计算过程中不可能改变 2020.9.8
        tmp1->m_bit_width = 16;///@FIXME 此处暂时改为8bit，因为16bit需要库函数支持 16;// pcompi->m_to_asm.get_basic_type_bit_width("GENERIC_PTR");
        tmp1->is_signed = 0;

        /// temp2=2[int bit width]*1
        icode *movA=pcompi->new_icode(ICODE_TYPE_EXP_OP);
        movA->name="*";
        movA->left = ic->array_cnt[curr_arr_idx];
        movA->right = pcompi->new_icode(ICODE_TYPE_I_CONST);
        movA->right->num = result_brief->result->m_in_ptr_type->m_bit_width/8;
        movA->right->const_refresh_width();
        movA->result = pcompi->new_ref_icode( tmp1);

        this->m_icodes.push_back(tmp1);
        this->m_icodes.push_back(movA);

        ///temp2=temp2 * 4
        int arr_cnt2=result_brief->result->array_cnt.size()-1;
        icode *mulcomp1 = NULL;
        while(arr_cnt2>curr_arr_idx)
        {
            mulcomp1 =  pcompi->new_icode(ICODE_TYPE_EXP_OP);
            mulcomp1->name="*";
            mulcomp1->left= pcompi->new_ref_icode( tmp1);
            mulcomp1->right = result_brief->result->array_cnt[arr_cnt2];
            mulcomp1->result = pcompi->new_ref_icode(tmp1);
            this->m_icodes.push_back(mulcomp1);
            arr_cnt2--;
        }


        icode *addAA=pcompi->new_icode(ICODE_TYPE_EXP_OP);
        addAA->name = "+";
        addAA->left = pcompi->new_ref_icode( tmp1);
        addAA->right = pcompi->new_ref_icode( result_new);
        addAA->result = pcompi->new_ref_icode( result_new);
        this->m_icodes.push_back(addAA);

        array_cnt++;
        curr_arr_idx++;
    }



    //
    if(ic->is_array != ic->result->is_array)
    {
        /// 返回值是指针
        this->m_icode_result =  pcompi->new_ref_icode( result_new);

        //返回值还是指针???
        this->m_icode_result->is_ptr=0;
        this->m_icode_result->m_bit_width = result_new->m_bit_width;//长度为指针长度
    }
    else
    {
        // 返回值是内部数据

        this->m_icode_result =  pcompi->new_var_in_var_icode(result_new);
        //this->m_icode_result->is_ptr--; 函数中封装过了
        this->m_icode_result->m_bit_width = ic->result->m_bit_width;
        this->m_icode_result->m_type=ICODE_TYPE_DEF_VAR_IN_VAR_TMP;
    }

    //计算完成后，将is_array去除，避免重复计算
    /// 后续ic已经被替换，所以此ic已经无用
    ic->is_array = 0;
    ic->array_cnt.clear();

    ///========================
    /// 生成代码后，需要复制到当前icode中
    ///

    this->m_to_rep_ic = m_icode_result;
    this->m_icode_to_insert_before_inst.insert(this->m_icode_to_insert_before_inst.end(),
                                               m_icodes.begin(), m_icodes.end());
    //需要先更新ic，再插入数据，因为插入数据时，可能ic已经变化了
    //ic = m_icode_result;
    //parent.insert(parent.begin()+index,  m_icodes.begin(), m_icodes.end());

    m_icodes.clear();
    m_icode_result = NULL;
    return 1;
}

int icode_ptr_calc::process_ptr_result(icode *ic, std::vector<icode *> &parent, int index, void *user_data, icode *iparent)
{
    /// int *a;
    /// a[2]=3;
    /// 此时需要生成的icode代码：
    /// int *result_new;
    /// result_new=a;
    /// tmp1  = 2*2;
    /// *temp2 = 3;
    ///
    ///
    ///
    /// int **a;
    /// a[1];
    /// 生成的代码：
    /// int *result_new=a;
    /// tmp1  = 1*3;
    /// result_new = a+tmp1;
    ///
    /// a[1][2]=3;
    ///
    /// 生成的代码：
    /// int *result_new=a;
    /// tmp1  = 1*3;
    /// result_new = a+tmp1;
    /// result_new2 = *result_new;
    /// tmp2 = 2 * 2;
    /// result_new2+=tmp2;
    /// *result_new2=3;
    ///
    ///
    /// ic: DEF_VAR_IN_VAR
    /// ic->result: DEF_VAR is_ptr>0
    ///
    ///
    ///
    assert(ic->is_array + ic->result->is_ptr>=0);

    icode *result_brief = ic;

    int array_cnt= ic->is_array;
    int curr_arr_idx=0;
    int curr_ptr_idx = pcompi->get_def_var(ic->result)->is_ptr;


    //申请一个通用指针的变量
    icode * result_new = NULL;
    if(curr_ptr_idx==1)
    {
        result_new = pcompi->new_temp_ptr_var(ic->result->m_in_ptr_type, &m_target);
    }
    else
    {
        result_new = pcompi->new_temp_ptr_ptr_var(&m_target);
    }

    /// temp1=a;
    icode *movB = pcompi->new_copy_icode_gen(pcompi->new_ref_icode(result_brief->result), pcompi->new_ref_icode(result_new));

    this->m_icodes.push_back(result_new);
    this->m_icodes.push_back(movB);

    while(array_cnt<0)
    {
        icode *tmp1 = pcompi->new_temp_var();
        /// \todo 此处指针，直接手写为16bit 2020.8.18 因为c51中地址最大为2byte，此处只需要2byte，最高byte类型在计算过程中不可能改变 2020.9.8
        tmp1->m_bit_width = 16;///@FIXME 此处暂时改为8bit，因为16bit需要库函数支持
        tmp1->is_signed = 0;

        /// temp2=2[int bit width]*1
        icode *movA=pcompi->new_icode(ICODE_TYPE_EXP_OP);
        movA->name="*";
        movA->left = ic->array_cnt[curr_arr_idx];
        movA->right = pcompi->new_iconst_icode(result_new->m_in_ptr_type->m_bit_width/8);
        movA->result = pcompi->new_ref_icode( tmp1);

        this->m_icodes.push_back(tmp1);
        this->m_icodes.push_back(movA);


        icode *addAA=pcompi->new_icode(ICODE_TYPE_EXP_OP);
        addAA->name = "+";
        addAA->left = pcompi->new_ref_icode( tmp1);
        addAA->right = pcompi->new_ref_icode( result_new);
        addAA->result = pcompi->new_ref_icode( result_new);
        this->m_icodes.push_back(addAA);

        array_cnt++;
        curr_arr_idx++;
        curr_ptr_idx--;

        if(array_cnt<0)
        {
            ///还有下一层array需要叠加，此时需要计算出当前层级的指针
            icode *result_new_tmp1 = pcompi->new_var_in_var_icode(result_new);

            if(curr_ptr_idx==1)
            {
                result_new = pcompi->new_temp_ptr_var(result_brief->result->m_in_ptr_type, &m_target);
            }
            else
            {
                result_new = pcompi->new_temp_ptr_ptr_var(&m_target);
            }
            icode *movB = pcompi->new_copy_icode_gen(pcompi->new_ref_icode(result_new_tmp1), pcompi->new_ref_icode(result_new));

            this->m_icodes.push_back(result_new_tmp1);
            this->m_icodes.push_back(result_new);
            this->m_icodes.push_back(movB);
            //icode * result_new = pcompi->new_temp_ptr_var(ic->result->m_in_ptr_type);
        }
    }

    this->m_icode_result =  pcompi->new_var_in_var_icode(result_new);


    //计算完成后，将is_array去除，避免重复计算
    /// 后续ic已经被替换，所以此ic已经无用
    ic->is_array = 0;
    ic->array_cnt.clear();

    ///========================
    /// 生成代码后，需要复制到当前icode中
    ///

    this->m_to_rep_ic = m_icode_result;
    this->m_icode_to_insert_before_inst.insert(this->m_icode_to_insert_before_inst.end(),
                                               m_icodes.begin(), m_icodes.end());
    //需要先更新ic，再插入数据，因为插入数据时，可能ic已经变化了
    //ic = m_icode_result;
    //parent.insert(parent.begin()+index,  m_icodes.begin(), m_icodes.end());

    m_icodes.clear();
    m_icode_result = NULL;
    return 1;
}

int icode_ptr_calc::process_one_icode(icode *ic, std::vector<icode *> &parent, int index, void *user_data, class icode *iparent)
{
    if((ic->m_type!=ICODE_TYPE_DEF_VAR_IN_VAR)&&(ic->m_type!=ICODE_TYPE_DEF_VAR_IN_VAR_TMP))
    {
        return 0;
    }
    if(!ic->is_array)
    {//是数组的
        return 0;
    }

    assert(ic->result);

    if(ic->result->is_array)
    {
        return process_array_result(ic, parent, index, user_data, iparent);
    }
    if(ic->result->is_ptr)
    {
        return process_ptr_result(ic, parent, index, user_data, iparent);
    }



}

