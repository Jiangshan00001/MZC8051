#include "json_io.h"
//#include "icode_manage.h"
//#include "comp_context.h"
// for convenience
using json = nlohmann::json;


json_io::json_io()
{
    is_save_default = 0;
    //m_new_inst = NULL;
}

json_io::~json_io()
{

}

std::string json_io::to_json(int skip_ptr)
{
    return this->to_json_in(skip_ptr).dump();
}

nlohmann::json json_io::to_json_in(int skip_ptr)
{
    json j;

    //skip_ptr=skip_ptr+skip_ptr;

    for(int i=0;i<m_property_name.size();++i)
    {
        switch(m_property_type[i])
        {
        case JSON_IO_TYPE_STD_STRING:
        {
            std::string c_val = * (std::string *)((void*)this+m_property_addr[i]);
            if(c_val == m_property_default_val[i].val_obj_name)
            {
                continue;
            }
            j[m_property_name[i] ] = c_val;
        }
            break;
        case JSON_IO_TYPE_INT:
        {
            int c_val = * (int*)((void*)this+m_property_addr[i]);
            if(m_property_default_val[i].val_int ==c_val)
            {
                continue;
            }
            j[m_property_name[i] ] = c_val;
        }
            break;
        case JSON_IO_TYPE_LONG_LONG:
        {
            long long c_val = * (long long *)((void*)this+m_property_addr[i]);
            if(m_property_default_val[i].val_long_long ==c_val)
            {
                continue;
            }
            j[m_property_name[i] ] = c_val;
        }
            break;
        case JSON_IO_TYPE_FLOAT:
        {
            float c_val = * (float *)((void*)this+m_property_addr[i]);
            if(m_property_default_val[i].val_float ==c_val)
            {
                continue;
            }
            j[m_property_name[i] ] = c_val;
        }
            break;
        case JSON_IO_TYPE_VECTOR_INT:
        {
            std::vector<int>& c_val = * (std::vector<int> *)((void*)this+m_property_addr[i]);
            if(c_val.size()==0)
            {
                continue;
            }
            j[m_property_name[i] ] = c_val;
        }
            break;



        case  JSON_IO_TYPE_OBJ:
        {
            if(skip_ptr>1)
            {
                // icode_type_ref->skip_ptr=1.
                // 之后会变为2，就是ref引用的内容，不会再添加指针
                continue;
            }


            json_io **obj_c = ((json_io**)((void*)this+m_property_addr[i]));
            if((*obj_c)!=NULL)
            {
                int skip_next = skip_ptr+skip_ptr;
                if(m_property_name[i]=="m_parent")
                {///@FIXME 此处硬编码m_parent的特殊性，避免json数据重复
                  skip_next += 2;
                }
                j[m_property_name[i] ] = (*obj_c)->to_json_in(skip_next);
            }
            else
            {
                continue;
                //j[m_property_name[i] ] = nullptr;
            }
        }
            break;

        default:
            break;
        }
    }

    return j;
}

bool json_io::from_json(std::string str1)
{
    json j;
    j = json::parse(str1);
    return from_json_in(j);
}

bool json_io::from_json_in(nlohmann::json &j)
{

    for (json::iterator it = j.begin(); it != j.end(); ++it)
    {
      //std::cout << it.key() << " : " << it.value() << "\n";
      std::string k = it.key();

      ///查找位置
      int index = -1;
      for(int i=0;i<m_property_name.size();++i)
      {
          if(m_property_name[i]==k)
          {
              index = i;
              break;
          }
      }

      if(index==-1)
      {
          continue;
      }

      ///赋值
      ///

      switch(m_property_type[index])
      {
      case JSON_IO_TYPE_STD_STRING:
          * (std::string*)((void*)this+m_property_addr[index]) = it.value();
          break;
      case JSON_IO_TYPE_INT:
          * (int*)((void*)this+m_property_addr[index]) = it.value();
          break;
      case JSON_IO_TYPE_LONG_LONG:
          * (long long*)((void*)this+m_property_addr[index]) = it.value();
          break;
      case JSON_IO_TYPE_FLOAT:
          * (float*)((void*)this+m_property_addr[index]) = it.value();
          break;

      case JSON_IO_TYPE_UNSIGNED:
            * (unsigned*)((void*)this+m_property_addr[index]) = it.value();
          break;
      case JSON_IO_TYPE_UNSIGNED_LONG:
            * (unsigned long*)((void*)this+m_property_addr[index]) = it.value();
          break;
      case JSON_IO_TYPE_VECTOR_INT:
      {
          std::vector<int>& c_val = * (std::vector<int> *)((void*)this+m_property_addr[index]);
          for(int i=0;i<it.value().size();++i)
          {
          c_val.push_back(it.value()[i]);
          }


      }
          break;

      case  JSON_IO_TYPE_OBJ:
      {
          json_io **obj_c = ((json_io**)((void*)this+m_property_addr[index]));


          if(it.value().is_null())
          {
            (*obj_c) = NULL;
          }
          else
          {
              *obj_c = NULL;//(json_io*)  m_new_inst->m_top_icodes->new_icode();
                      //json_obj_new(m_property_default_val[index].val_obj_name);//此处生成新的变量
              if(*obj_c!=NULL)
              {
                  (*obj_c)->from_json_in(it.value());
              }
          }
      }
          break;

      default:
          break;
      }
    }

    return 1;
}

void json_io::set_property(std::string name, json_io **addr, char obj_type_name[100])
{
    m_property_name.push_back(name);
    m_property_addr.push_back((long long)addr-(long long)this);

    m_property_type.push_back(JSON_IO_TYPE_OBJ);
    union json_val_un v1;
    memcpy(v1.val_obj_name, obj_type_name, sizeof(v1.val_obj_name));
    m_property_default_val.push_back(v1);
}

void json_io::set_property(std::string name, std::vector<int> *addr)
{
    m_property_name.push_back(name);
    m_property_addr.push_back((long long)addr-(long long)this);

    m_property_type.push_back(JSON_IO_TYPE_VECTOR_INT);
    union json_val_un v1;
    v1.val_long_long = 0;
    m_property_default_val.push_back(v1);
}

void json_io::set_property(std::string name, std::string *addr, const char init_var[])
{
    m_property_name.push_back(name);
    m_property_addr.push_back((long long)addr-(long long)this);

    m_property_type.push_back(JSON_IO_TYPE_STD_STRING);
    union json_val_un v1;
    strncpy(v1.val_obj_name, init_var, sizeof(v1.val_obj_name));
    m_property_default_val.push_back(v1);
}

void json_io::set_property(std::string name, int *addr, int val_def)
{
    m_property_name.push_back(name);
    m_property_addr.push_back((long long)addr-(long long)this);

    m_property_type.push_back(JSON_IO_TYPE_INT);
    union json_val_un v1;
    v1.val_int = val_def;
    m_property_default_val.push_back(v1);
}
void json_io::set_property(std::string name, unsigned long *addr, unsigned long val_def)
{
    m_property_name.push_back(name);
    m_property_addr.push_back((long long)addr-(long long)this);

    m_property_type.push_back(JSON_IO_TYPE_UNSIGNED_LONG);
    union json_val_un v1;
    v1.val_unsigned_long = val_def;
    m_property_default_val.push_back(v1);
}

void json_io::set_property(std::string name, long long *addr, long long val_def)
{
    m_property_name.push_back(name);
    m_property_addr.push_back((long long)addr-(long long)this);

    m_property_type.push_back(JSON_IO_TYPE_LONG_LONG);
    union json_val_un v1;
    v1.val_long_long = val_def;
    m_property_default_val.push_back(v1);
}

void json_io::set_property(std::string name, float *addr, float val_def)
{
    m_property_name.push_back(name);
    m_property_addr.push_back((long long)addr-(long long)this);

    m_property_type.push_back(JSON_IO_TYPE_FLOAT);
    union json_val_un v1;
    v1.val_float = val_def;
    m_property_default_val.push_back(v1);
}
