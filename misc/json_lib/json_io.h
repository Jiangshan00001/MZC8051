#ifndef JSON_IO_H
#define JSON_IO_H

#include <string>
#include <vector>

#include "json.hpp"


union json_val_un
{
    int val_int;
    unsigned val_unsigned;
    long val_long;
    unsigned long val_unsigned_long;

    long long val_long_long;
    unsigned long long val_unsigned_long_long;
    double val_double;
    float val_float;
    char val_obj_name[100];
};


typedef enum JSON_IO_TYPE
{
    JSON_IO_TYPE_INT = 1,
    JSON_IO_TYPE_UNSIGNED = 2,
    JSON_IO_TYPE_LONG = 3,
    JSON_IO_TYPE_LONG_LONG = 4,
    JSON_IO_TYPE_DOUBLE = 5,
    JSON_IO_TYPE_FLOAT = 6,
    JSON_IO_TYPE_UNSIGNED_LONG = 7,
    JSON_IO_TYPE_UNSIGNED_LONG_LONG = 8,
    JSON_IO_TYPE_OBJ=9,
    JSON_IO_TYPE_STD_STRING=10,
    JSON_IO_TYPE_VECTOR_INT=11,

}JSON_IO_TYPE_T;

///此函数由外部实现，用于obj对象的创建
extern void * json_obj_new( char obj_type_name[100]);


/// 参考代码： https://www.cnblogs.com/tragicguy/p/3603778.html
///
///
class json_io
{
public:
    json_io();
    virtual ~json_io();

    virtual std::string to_json(int skip_ptr=0);
    virtual nlohmann::json to_json_in(int skip_ptr=0);
    virtual bool from_json(std::string str1);
    virtual bool from_json_in(nlohmann::json& j);
    void set_property(std::string name, int *addr, int val_def=0);
    void set_property(std::string name, unsigned long *addr, unsigned long val_def=0);
    void set_property(std::string name, long long *addr, long long val_def=0);
    void set_property(std::string name, std::string *addr, const char init_var[100]);
    void set_property(std::string name, float *addr, float val_def=0);
    void set_property(std::string name, json_io **addr, char obj_type_name[100]);
    void set_property(std::string name, std::vector<int> *addr);



    std::vector<std::string> m_property_name;
    std::vector<long long> m_property_addr;//void*. addr-this is saved
    std::vector<JSON_IO_TYPE_T> m_property_type;
    std::vector<union json_val_un> m_property_default_val;


    //转为json时，如果值为默认值，是否保存
    int is_save_default;

    //class icode_manage * m_new_inst;
};

#endif //
