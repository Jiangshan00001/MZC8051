#include "icode.h"
#include "icode_visitor.h"
#include "mylog.h"

using mylog::cdbg;
using mylog::cerr;

icode_visitor::icode_visitor()
{
    m_to_rep_ic = NULL;
    m_to_erase_ic = false;
}

icode_visitor::~icode_visitor()
{

}

int icode_visitor::process_topcode(class icode *top_icode, void *user_data)
{
    std::vector<icode *> &top_icodes = top_icode->sub_icode;
    m_icode_number_set.clear();
    int ret = 0;
    for(int i=0;i<top_icodes.size();++i)
    {
        m_level = 0;
        ret += enum_one(top_icodes[i], top_icodes, i, user_data, top_icodes[i]);
        check_rep(top_icodes[i]);
        check_insert_inst(top_icodes, i);
        ret += enum_all_child( top_icodes[i], top_icodes, i, user_data, NULL);
    }
    return ret;
}

int icode_visitor::enum_one(icode *ic, std::vector<icode *> &parent, int index, void *user_data, icode *iparent)
{
    if(ic==NULL)
    {
        return 0;
    }
    if(m_icode_number_set.find(ic)!=m_icode_number_set.end())
    {
        ///已经枚举过一遍了，直接返回
        return 0;
    }

    m_icode_number_set.insert(ic);
    return process_one_icode(ic, parent, index, user_data, iparent);
}

int icode_visitor::process_one_icode(icode *ic, std::vector<icode *> &parent, int index, void *user_data, class icode *iparent)
{

    return 0;
}


void icode_visitor::level_enter()
{

}

void icode_visitor::level_leave()
{

}

int icode_visitor::enum_all_child(icode *ic, std::vector<icode *> &parent, int index, void *user_data, icode *iparent)
{
    int ret = 0;

    if(ic==NULL)
    {
        return 0;
    }


    //ret += process_one_icode(ic,parent, index, user_data, iparent);

    switch(ic->m_type)
    {

    case ICODE_TYPE_DEF_VAR_IN_VAR:
    case ICODE_TYPE_DEF_VAR_IN_VAR_TMP:
#if 0///VAR_IN_VAR和ref一样的属性，result已经被枚举过了，所以不能再枚举了
        if(ic->result)
        {
            ret += process_one_icode(ic->result,parent, index, user_data, ic);
            check_rep(ic->result);
            assert(m_to_erase_ic==false);
            enum_all(ic->result, parent, index, user_data, ic);
        }
#endif
        break;
    case ICODE_TYPE_SYMBOL_REF:
        {

        }
        break;
    case ICODE_TYPE_DEF_VAR:
    case ICODE_TYPE_DEF_VAR_TMP:
        //array
#if 0
        if(ic->array_cnt.size()>0)
        {
            for(unsigned i=0;i<ic->array_cnt.size();++i)
            {
                if(ic->array_cnt[i])
                {
                    ret += enum_one(ic->array_cnt[i],parent, index, user_data, ic);
                    check_rep(ic->array_cnt[i]);
                    assert(m_to_erase_ic==false);
                    enum_all_child(ic->array_cnt[i], parent,index, user_data, ic);
                }
            }
        }
#endif
        if(ic->m_struct_type.size()>0)
        {
            for(unsigned i=0;i<ic->m_struct_type.size();++i)
            {
                if(ic->m_struct_type[i])
                {
                    ret += enum_one(ic->m_struct_type[i],parent, index, user_data, ic);
                    check_rep(ic->m_struct_type[i]);
                    assert(m_to_erase_ic==false);
                    enum_all_child(ic->m_struct_type[i], parent,index, user_data, ic);
                }
            }
        }

        break;
    case ICODE_TYPE_EXP_OP:
        {
            if(ic->left)
            {
                ret += enum_one(ic->left,parent, index, user_data, ic);
                check_rep(ic->left);
                assert(m_to_erase_ic==false);
                ret += enum_all_child(ic->left, parent, index, user_data, ic);
            }

            if(ic->right)
            {
                ret += enum_one(ic->right,parent, index, user_data, ic);
                check_rep(ic->right);
                assert(m_to_erase_ic==false);
                ret += enum_all_child(ic->right, parent, index, user_data, ic);
            }

            if(ic->result)
            {
                ret += enum_one(ic->result,parent, index, user_data, ic);
                check_rep(ic->result);
                assert(m_to_erase_ic==false);
                ret += enum_all_child(ic->result, parent, index, user_data, ic);
            }
        }
        break;

    case ICODE_TYPE_CALL:
    {
        //NOTODO: 调用参数需要处理. 2021.1.2 此处已经修改visitor逻辑。改为通过记录指针，确保枚举所有icode一次
        // delay(array1[2]);

        for(unsigned i=0;i<ic->sub_icode.size();++i)
        {
            if(ic->sub_icode[i])
            {
                ret += enum_one(ic->sub_icode[i],parent, index, user_data, ic);
                check_rep(ic->sub_icode[i]);
                assert(m_to_erase_ic==false);
                ret += enum_all_child(ic->sub_icode[i], parent, index, user_data, ic);
            }
        }

        if(ic->result)
        {
            ret += enum_one(ic->result,parent, index, user_data, ic);
            check_rep(ic->result);
            assert(m_to_erase_ic==false);
            enum_all_child(ic->result, parent, index, user_data, ic);
        }
    }
        break;

    case ICODE_TYPE_FUNC:
        {

            //m_level++;
            //level_enter();
            ///FIXME 此处函数参数要拆分出来？？？
            for(int i=0;i<ic->sub_icode.size();++i)
            {
                if(ic->sub_icode[i]==NULL)continue;

                ret += enum_one(ic->sub_icode[i],ic->sub_icode, i, user_data, ic);
                check_rep(ic->sub_icode[i]);
                check_insert_inst(ic->sub_icode, i);

                ret += enum_all_child(ic->sub_icode[i], ic->sub_icode, i, user_data, ic);
                check_insert_inst(ic->sub_icode, i);
            }

            ///func里，现在result保存的是返回值的引用，暂时无用
            ///
            if(ic->result)
            {
                ret += enum_one(ic->result,parent, index, user_data, ic);
                check_rep(ic->result);
                assert(m_to_erase_ic==false);
                enum_all_child(ic->result, parent, index, user_data, ic);
            }

            //level_leave();
            //m_level--;
        }
        break;

    case ICODE_TYPE_BLOCK:
    case ICODE_TYPE_LABELED_BLOCK:
    case ICODE_TYPE_SCOPE:
    default:
    {
        if(ic->m_type==ICODE_TYPE_SCOPE)
        {
            m_level++;
            level_enter();
        }

        for(int i=0;i<ic->sub_icode.size();++i)
        {
            if(ic->sub_icode[i]==NULL)continue;
            ret += enum_one(ic->sub_icode[i],ic->sub_icode, i, user_data, ic);
            check_rep(ic->sub_icode[i]);
            check_insert_inst(ic->sub_icode, i);

            ret += enum_all_child(ic->sub_icode[i], ic->sub_icode, i, user_data, ic);
            check_insert_inst(ic->sub_icode, i);

        }
        if(ic->m_type==ICODE_TYPE_SCOPE)
        {
            level_leave();
            m_level--;
        }
    }
        break;
    }
    return ret;
}


void icode_visitor::check_rep(icode *&ic)
{
    if(m_to_rep_ic!=NULL)
    {
        ic = m_to_rep_ic;
        m_to_rep_ic = NULL;
    }
}

void icode_visitor::check_insert_inst(std::vector<icode *> &inst_parent, int &index)
{
    if(this->m_icode_to_insert_after_inst.size()>0)
    {
        inst_parent.insert(inst_parent.begin()+index+1, this->m_icode_to_insert_after_inst.begin(), this->m_icode_to_insert_after_inst.end());
    }
    if(this->m_icode_to_insert_before_inst.size()>0)
    {
        inst_parent.insert(inst_parent.begin()+index, this->m_icode_to_insert_before_inst.begin(), this->m_icode_to_insert_before_inst.end());
        index += this->m_icode_to_insert_before_inst.size();
    }
    if(m_to_erase_ic)
    {
        inst_parent.erase(inst_parent.begin()+index);
        m_to_erase_ic = false;
    }

    this->m_icode_to_insert_after_inst.clear();
    this->m_icode_to_insert_before_inst.clear();
}
