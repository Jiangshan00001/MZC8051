#include <algorithm>
#include "icode.h"
#include "icodes.h"
#include "icode_var_scope.h"

icode_var_scope::icode_var_scope()
{
}


int icode_var_scope::process_one_icode(icode *ic,
                               std::vector<icode *> &parent,
                                   int index, void *user_data, class icode *iparent)
{
    /// 生成一个树形结构
    /// 用于变量范围核查
    /// 只修改var的 m_var_scope字段
    /// 修复parent。因为之前没有填好，所以现在要讲parent重新填好
    ///
    if((user_data==NULL)||*((int*)user_data)==0)
    {
        ///清除parent
        clear_parent(ic);
        return 0;
    }
    if((*(int*)user_data)==1)
    {
        ///为变量添加scope辅助信息
        return icode_scope_fill(ic);
    }

    //计算变量的scope
    //if((*(int*)user_data)==2)
    return fix_var_scope(ic);
}

///
/// \brief 去除所有icode的parent
/// \param ic
///
void icode_var_scope::clear_parent(icode *ic)
{
    ic->m_parent = NULL;

    if(ic->is_def_var())
    {
        ic->m_var_scope_vec.clear();
        ic->m_var_scope = -1;
    }

    for(int i=0;i<ic->array_cnt.size();++i)
    {
        ic->array_cnt[i]->m_parent = NULL;
        ic->array_cnt[i]->m_var_scope_vec.clear();
    }
    for(int i=0;i<ic->m_struct_type.size();++i)
    {
        ic->m_struct_type[i]->m_parent = NULL;
        ic->m_struct_type[i]->m_var_scope_vec.clear();
    }
}



///
/// \brief 为child添加parent属性。如果child是var，则还会添加m_var_scope_vec
/// \param parent
/// \param child
///
void icode_var_scope::add_parent(icode *parent, icode **child)
{
    if(((*child)->m_parent!=NULL)&&
            ((*child)->m_type==ICODE_TYPE_SYMBOL_REF)&&
            ((*child)->m_parent!=parent)
            )
    {
        /// child的parent已经存在了，并且当前child是ref，则说明
        /// child在其他地方有被使用，因为部分变量的ref，可能会同时被多个地方使用
        /// 导致已经添加了parent，所以此处重新生成ref
        (*child) = pcompi->new_ref_icode((*child));
    }
    (*child)->m_parent = parent;

    ///添加变量的ref的vec icode number
    ///


    ///child 是一个ref或者var_in_var类型，
    if(((*child)->result!=NULL)&&
            ((*child)->result->is_def_var()))
    {
        icode *var = pcompi->get_def_var((*child)->result);
        var->m_var_scope_vec.push_back((*child)->m_icode_number);
    }

#if 0
    for(int i=0;i<ic->array_cnt.size();++i)
    {
        ic->array_cnt[i]->m_parent = NULL;
    }
    for(int i=0;i<ic->m_struct_type.size();++i)
    {
        ic->m_struct_type[i]->m_parent = NULL;
    }

    if((*child)->is_def_var())
    {
        icode *var = (*child);
        var->m_var_scope_vec.push_back(parent->m_icode_number);
    }
#endif
}

/// 此函数添加parent到所有ic中
int icode_var_scope::icode_scope_fill(icode *ic)
{

    if((ic->m_type==ICODE_TYPE_SYMBOL_REF)||
            (ic->m_type==ICODE_TYPE_DEF_VAR_IN_VAR)||
            (ic->m_type==ICODE_TYPE_DEF_VAR_IN_VAR_TMP))
    {
        ///这三个，里面的result都是引用，不能设置parent
        return 0;
    }

    if(ic->left!=NULL)
    {
        add_parent(ic, &ic->left);
    }
    if(ic->right!=NULL)
    {
        add_parent(ic, &ic->right);
    }
    if(ic->result!=NULL)
    {
        add_parent(ic, &ic->result);
    }
    for(int i=0;i<ic->sub_icode.size();++i)
    {
        add_parent(ic, &ic->sub_icode[i]);
    }
    for(int i=0;i<ic->array_cnt.size();++i)
    {
        add_parent(ic, &ic->array_cnt[i]);
    }

    for(int i=0;i<ic->m_struct_type.size();++i)
    {
        add_parent(ic, &ic->m_struct_type[i]);
    }

    return 0;
}

int icode_var_scope::fix_var_scope(icode *ic)
{
    if(!ic->is_def_var())
    {
        ///不是变量，不做处理
        return 0;
    }


    ///此处找到变量的parent，和引用，查看外部的scope
    ///


    std::vector< std::vector<int> > blk_vec;

    std::vector<int> blks = this->find_var_blocks(ic);
    blk_vec.push_back(blks);
    for(int i=0;i<ic->m_var_scope_vec.size();++i)
    {
        std::vector<int> blks1 = find_var_blocks(ic->m_var_scope_vec[i]);
        blk_vec.push_back(blks1);
    }
    for(int i=0;i<ic->m_struct_type.size();++i)
    {
        fix_var_scope(ic->m_struct_type[i]);
        ///如果是结构体，则结构体的数据可能被访问，导致变量声明空间扩展
        std::vector<int> blks1 = find_var_blocks(ic->m_struct_type[i]->m_var_scope);
        blk_vec.push_back(blks1);
    }

    ///清除vec，不然下次再运行会重复叠加
    //ic->m_var_scope_vec.clear();


    ////////////////////
    /// 此处根据blk_vec，获取多个vec的最终block
    ///

    if(blk_vec.size()==0)
    {
        ///一个都没有，未使用的全局变量？？？
        ic->m_var_scope = -1;
        return 0;
    }
    if(blk_vec[0].size()==0)
    {
        /// 有使用的全局变量？？
        ic->m_var_scope = -1;
        return 0;
    }


    for(int i=0;i<blk_vec.size();++i)
    {
        if(blk_vec[i].size()==0)
        {
            ic->m_var_scope = -1;
            return 0;
        }
    }



    int scope_number = blk_vec[0][0];
    int scope_index = 0;
    while(scope_index<blk_vec[0].size())
    {
        scope_number = blk_vec[0][scope_index];
        int is_all_fit = 1;
        for(int i=1;i<blk_vec.size();++i)
        {
            if(std::find(blk_vec[i].begin(), blk_vec[i].end(),scope_number)==blk_vec[i].end())
            {
                is_all_fit = 0;
                break;
            }
        }
        if(is_all_fit)
        {

            ic->m_var_scope = scope_number;
            return 0;
        }
        scope_index++;
    }

    ic->m_var_scope = -1;
    return 0;
}




/// 查找某个变量ic，所有的parent为block或者func的类型的ic
/// 前提是ic的parent还有parent。parent属性要都正确才行
std::vector<int> icode_var_scope::find_var_blocks(icode *ic)
{
    std::vector<int> vec;


    while(ic)
    {
        if(ic==NULL)
        {
            break;
        }
        if(ic->m_type==ICODE_TYPE_BLOCK)
        {
            vec.push_back(ic->m_icode_number);
        }
        else if(ic->m_type==ICODE_TYPE_FUNC)
        {
            vec.push_back(ic->m_icode_number);
            break;
        }
        ic = ic->m_parent;
    }
    return vec;
}

std::vector<int> icode_var_scope::find_var_blocks(int icode_number)
{
    assert(pcompi->m_icode_number_dict.find(icode_number)!=pcompi->m_icode_number_dict.end());
    icode *ic = pcompi->m_icode_number_dict[icode_number];
    return find_var_blocks(ic);
}


