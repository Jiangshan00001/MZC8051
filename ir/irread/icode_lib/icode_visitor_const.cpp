#include "icode_visitor_const.h"

icode_visitor_const::icode_visitor_const()
{
    pcompi = NULL;
    m_level = 0;
    m_curr_func = NULL;
}

icode_visitor_const::~icode_visitor_const()
{

}

int icode_visitor_const::process_topcode(icode *top_icode, void *user_data)
{
    int ret = 0;
    m_level = 0;
    ret += enum_one_start(top_icode, user_data, NULL);
    ret += enum_all_child( top_icode,  user_data, NULL);
    ret += enum_one_end(top_icode, user_data, NULL);
    return 0;
}

int icode_visitor_const::process_one_icode_start(icode *ic, void *user_data, icode *iparent)
{

}

int icode_visitor_const::process_one_icode_end(icode *ic, void *user_data, icode *iparent)
{

}

void icode_visitor_const::level_enter()
{
    m_level++;
}

void icode_visitor_const::level_leave()
{
    m_level--;
}

void icode_visitor_const::reset()
{
    m_level = 0;
    m_curr_func = NULL;
    m_icode_number_set.clear();
    m_icode_number_set_end.clear();
}

int icode_visitor_const::enum_all_child(icode *ic, void *user_data, icode *iparent)
{
    int ret = 0;

    if(ic==NULL)
    {
        return 0;
    }
    switch(ic->m_type)
    {

    case ICODE_TYPE_DEF_VAR_IN_VAR:
    case ICODE_TYPE_DEF_VAR_IN_VAR_TMP:
        break;
    case ICODE_TYPE_SYMBOL_REF:
        {

        }
        break;
    case ICODE_TYPE_DEF_VAR:
    case ICODE_TYPE_DEF_VAR_TMP:
        //array

        if(ic->m_struct_type.size()>0)
        {
            for(unsigned i=0;i<ic->m_struct_type.size();++i)
            {
                if(ic->m_struct_type[i])
                {
                    ret += enum_one_start(ic->m_struct_type[i],user_data, ic);
                    enum_all_child(ic->m_struct_type[i],  user_data, ic);
                    ret += enum_one_end(ic->m_struct_type[i],user_data, ic);
                }
            }
        }

        break;
    case ICODE_TYPE_EXP_OP:
        {
            if(ic->left)
            {
                ret += enum_one_start(ic->left,user_data, ic);
                ret += enum_all_child(ic->left, user_data, ic);
                ret += enum_one_end(ic->left,user_data, ic);
            }

            if(ic->right)
            {
                ret += enum_one_start(ic->right,user_data, ic);
                ret += enum_all_child(ic->right, user_data, ic);
                ret += enum_one_end(ic->right,user_data, ic);
            }

            if(ic->result)
            {
                ret += enum_one_start(ic->result,user_data, ic);
                ret += enum_all_child(ic->result, user_data, ic);
                ret += enum_one_end(ic->result,user_data, ic);
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
                ret += enum_one_start(ic->sub_icode[i], user_data, ic);
                ret += enum_all_child(ic->sub_icode[i], user_data, ic);
                ret += enum_one_end(ic->sub_icode[i], user_data, ic);
            }
        }

        if(ic->result)
        {
            ret += enum_one_start(ic->result,user_data, ic);
            ret += enum_all_child(ic->result, user_data, ic);
            ret += enum_one_end(ic->result,user_data, ic);
        }
    }
        break;

    case ICODE_TYPE_FUNC:
        {


            this->m_curr_func = ic;

            //m_level++;
            level_enter();
            ///FIXME 此处函数参数要拆分出来？？？
            for(int i=0;i<ic->sub_icode.size();++i)
            {
                if(ic->sub_icode[i]==NULL)continue;

                ret += enum_one_start(ic->sub_icode[i],user_data, ic);
                ret += enum_all_child(ic->sub_icode[i],user_data, ic);
                ret += enum_one_end(ic->sub_icode[i],user_data, ic);
            }

            ///func里，现在result保存的是返回值的引用，暂时无用
            ///
            if(ic->result)
            {
                ret += enum_one_start(ic->result,user_data, ic);
                ret += enum_all_child(ic->result, user_data, ic);
                ret += enum_one_end(ic->result,user_data, ic);
            }

            this->m_curr_func = NULL;
            level_leave();
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
            ret += enum_one_start(ic->sub_icode[i],user_data, ic);
            ret += enum_all_child(ic->sub_icode[i],user_data, ic);
            ret += enum_one_end(ic->sub_icode[i],user_data, ic);
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

int icode_visitor_const::enum_one_start(icode *ic, void *user_data, icode *iparent)
{
    if(ic==NULL)
    {
        return 0;
    }

    std::set<class icode*> &set_curr = m_icode_number_set;
    if(set_curr.find(ic)!=set_curr.end())
    {
        ///已经枚举过一遍了，直接返回
        return 0;
    }

    set_curr.insert(ic);

    if(ic->m_type==ICODE_TYPE_FUNC)
    {
        this->m_curr_func = ic;
    }
    int ret = process_one_icode_start(ic, user_data, iparent);

    return ret;
}

int icode_visitor_const::enum_one_end(icode *ic, void *user_data, icode *iparent)
{
    if(ic==NULL)
    {
        return 0;
    }

    std::set<class icode*> &set_curr = m_icode_number_set_end;
    if(set_curr.find(ic)!=set_curr.end())
    {
        ///已经枚举过一遍了，直接返回
        return 0;
    }

    set_curr.insert(ic);

    int ret = process_one_icode_end(ic, user_data, iparent);
    if(ic->m_type==ICODE_TYPE_FUNC)
    {
        this->m_curr_func = NULL;
    }


    return ret;
}
