#include <assert.h>
#include "icode.h"
#include "icodes.h"
#include "icode_inline.h"

icode_inline::icode_inline()
{
}

icode_inline::~icode_inline()
{

}

int icode_inline::process_one_icode(icode *ic, std::vector<icode *> &parent, int index, void *user_data, class icode *iparent)
{
    if(ic->m_type!=ICODE_TYPE_CALL)
    {
        return 0;
    }

    //只处理函数调用
    if(ic->left==NULL)
    {
        //空函数引用？没有函数？
        return 0;
    }
    if(ic->left->result==NULL)
    {
        //空函数引用？没有函数？
        return 0;
    }

    //icode *func_ref = ic->left;
    icode *func = ic->left->result;

    if(!func->is_inline)
    {
        return 0;
    }


    //只处理inline函数的调用
    std::vector<class icode*> m_icodes;




    std::vector<class icode*> nparams;
    std::map<class icode *, class icode *> param_old_new_ptr;

    ///参数生成新的变量： 返回值和参数
    for(unsigned i=0;i<func->sub_icode.size();++i)
    {
        icode *ic1=func->sub_icode[i];
        if((ic1->m_type==ICODE_TYPE_FUNC_RET_TYPE)||
                (ic1->m_type==ICODE_TYPE_FUNC_DEF_ARG))
        {
            icode *p1 = pcompi->new_icode(*ic1);
            p1->m_type=ICODE_TYPE_DEF_VAR_TMP;

            param_old_new_ptr[ic1]=p1;

            nparams.push_back(p1);

            m_icodes.push_back(p1);
        }
        else
        {
            break;
        }
    }



    for(unsigned i=0;i<ic->sub_icode.size();++i)
    {
        if(nparams.size()<=i+1)
        {
            //函数实际参数没有那么多
            break;
        }

        icode *movi = pcompi->new_copy_icode_gen(ic->sub_icode[i], nparams[i+1]);
        m_icodes.push_back(movi);
    }


    ///先将func内部代码复制到m_icode中，再处理，
    /// 因为可能会嵌套inline函数，所以需要parent即时修改

    m_icodes.insert(m_icodes.end(), func->sub_icode.begin()+nparams.size(), func->sub_icode.end());


    //前面的参数已经处理过了
    for(unsigned i=nparams.size();i<m_icodes.size();++i)
    {
        icode * n = inline_copy(m_icodes[i], param_old_new_ptr, m_icodes, i, 1);
        m_icodes[i] = n;
    }
    for(unsigned i=nparams.size();i<m_icodes.size();++i)
    {
        icode * n = inline_copy(m_icodes[i], param_old_new_ptr, m_icodes, i, 0);
        m_icodes[i] = n;
    }


    for(unsigned i=index+1;i<parent.size();++i)
    {
        //认为parent是当前作用域的block。函数返回值需要在此后使用
        inline_replace(parent[i], param_old_new_ptr);
    }


    //替换call函数
    //parent.erase(parent.begin()+index);
    //parent.insert(parent.begin()+index, m_icodes.begin(), m_icodes.end());
    this->m_to_erase_ic = true;
    this->m_icode_to_insert_before_inst.insert(this->m_icode_to_insert_before_inst.end(), m_icodes.begin(), m_icodes.end());

    return 0;
}

icode *icode_inline::inline_copy(icode *ic, std::map<icode *, icode *> &old_new_var_ptr, std::vector<icode *> &parent, int index, int is_alloc)
{
    icode *nic = NULL;
    if(is_alloc){
        nic=pcompi->new_icode(*ic);
    }
    else{
        nic= ic;
    }
    switch(nic->m_type)
    {
    case ICODE_TYPE_BLOCK:
    case ICODE_TYPE_LABELED_BLOCK:
    {

        for(unsigned i=0;i<nic->sub_icode.size();++i)
        {
            icode *sb = inline_copy(nic->sub_icode[i], old_new_var_ptr, nic->sub_icode, i, is_alloc);
            nic->sub_icode[i] = sb;
        }
        if((nic->m_type==ICODE_TYPE_LABELED_BLOCK)&&is_alloc)
        {
            //需要新旧替换的 labeled_block
            old_new_var_ptr[ic] = nic;
        }
    }
        break;

    case ICODE_TYPE_DEF_VAR:
    {
        if(is_alloc){
            old_new_var_ptr[ic] = nic;
        }
    }
        break;

    case ICODE_TYPE_DEF_VAR_TMP:
    case ICODE_TYPE_FUNC_RET_TYPE:
    case ICODE_TYPE_FUNC_DEF_ARG:
    {
        if(is_alloc){
            nic->m_type = ICODE_TYPE_DEF_VAR_TMP;
            old_new_var_ptr[ic] = nic;
        }
    }
        break;
    case ICODE_TYPE_CONST_STRING:
    {
        if(is_alloc){
            old_new_var_ptr[ic] = nic;
        }
    }
        break;
    case ICODE_TYPE_CALL:
    {
        this->process_one_icode(nic, parent, index, NULL,NULL);
    }

        break;



    case ICODE_TYPE_I_CONST:
    case ICODE_TYPE_F_CONST:
    case ICODE_TYPE_CONST_LIST:
    {}
        break;

        break;
    case ICODE_TYPE_FUNC:
    {
        //inline函数中，应该不能再添加其他函数
        assert(0);
        break;
    }

    case ICODE_TYPE_FUNC_RETURN:
        break;


    case ICODE_TYPE_EXP_OP:
    {
        if(nic->left)
        {
            nic->left= inline_copy(nic->left, old_new_var_ptr,parent, index, is_alloc);
        }
        if(nic->right)
        {
            nic->right= inline_copy(nic->right, old_new_var_ptr,parent, index, is_alloc);
        }
        if(nic->result)
        {
            nic->result= inline_copy(nic->result, old_new_var_ptr,parent, index, is_alloc);
        }
    }
        break;


    case ICODE_TYPE_LABELED_BLOCK_START_REF:
    case ICODE_TYPE_LABELED_BLOCK_END_REF:
        inline_replace(nic, old_new_var_ptr);
        break;

    case ICODE_TYPE_SYMBOL_REF:
    {
        inline_replace(nic, old_new_var_ptr);
    }
        break;


    default:
    {
        if(ic->left)
        {
            nic->left = inline_copy(nic->left, old_new_var_ptr,parent, index, is_alloc);
        }

        if(ic->right)
        {
            nic->right = inline_copy(nic->right, old_new_var_ptr,parent, index, is_alloc);
        }
        if(ic->result)
        {
            nic->result = inline_copy(nic->result, old_new_var_ptr,parent, index, is_alloc);
        }
        for(unsigned i=0;i<ic->sub_icode.size();++i)
        {
            icode *sb = inline_copy(nic->sub_icode[i], old_new_var_ptr, parent, index, is_alloc);
            nic->sub_icode[i] = sb;
        }

    }
        break;

    }

    return nic;
}

icode *icode_inline::inline_replace(icode *ic, std::map<icode *, icode *> &old_new_var_ptr)
{
    if(ic->left)
    {
        if(old_new_var_ptr.find( ic->left)!=old_new_var_ptr.end())
        {
            ic->left = old_new_var_ptr[ic->left];
        }
        else
        {
            inline_replace(ic->left, old_new_var_ptr);
        }
    }
    if(ic->right)
    {
        if(old_new_var_ptr.find( ic->right)!=old_new_var_ptr.end())
        {
            ic->right = old_new_var_ptr[ic->right];
        }
        else
        {
            inline_replace(ic->right, old_new_var_ptr);
        }
    }
    if(ic->result)
    {
        if(old_new_var_ptr.find( ic->result)!=old_new_var_ptr.end())
        {
            ic->result = old_new_var_ptr[ic->result];
        }
        else
        {
            inline_replace(ic->result, old_new_var_ptr);
        }
    }

    for(unsigned i=0;i<ic->sub_icode.size();++i)
    {
        if(old_new_var_ptr.find( ic->sub_icode[i])!=old_new_var_ptr.end())
        {
            ic->sub_icode[i] = old_new_var_ptr[ic->sub_icode[i] ];
        }
        else
        {
            inline_replace(ic->sub_icode[i], old_new_var_ptr);
        }
    }



    return ic;
}








