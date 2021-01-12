#ifndef TARGET_BASE_H
#define TARGET_BASE_H
#include <string>
#include <map>
class target_base
{
public:
    target_base();
    virtual ~target_base();

    ///每种数据类型，占用的byte数。其中bit是特殊的，只占用1bit，其他都是字节
    /// bit时，返回
    virtual int get_basic_type_bit_width(const std::string &type_str);

    std::map<std::string, int> m_type_bit_list_c51;


};

#endif // TARGET_BASE_H
