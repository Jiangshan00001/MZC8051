#ifndef ICODE_H
#define ICODE_H
#include <string>
#include <vector>
#include <deque>
//#include "c51_addr.h"
#include "icode_type.h"

#include "icode_base.h"
#include "json_io.h"



/**
 * @brief The icode class 语言的中间代码表示形式
 *
 *
 * 2020.12.13 去除json的支持class_init_json_io
 *
 */
class icode:public json_io
{
public:

    icode();
    icode(int icode_num);
    ~icode();


public:
    /// icode 转为字符串函数
    std::string to_str(int is_one_line=0, int is_dbg=1);
    icode* from_str(const std::string &istr);
    /// icode 转为字符串相关函数
    ///
    ///
    std::string that_to_str(icode *that);
private:

    /// 根据数据类型，输出 i32 u64 f32 i8 等字符串
    std::string get_var_type();

    ///  将vector<icode*>类型的变量，转为str
    std::string vector_icode_ptr_cont(std::vector<icode *> vec1);


public:

    /// 转为dot语言
    int to_dot(std::string &def_str, std::string &ref_str);
    int from_dot();



public:

    /// icode的操作类函数
    /// 包括：合并，修改 等

    /// 将两个icode合并到一起。如果child是block，则直接将内部sub_icode合并到当前icode的sub_icode，省略掉一层block
    icode *merge_icode(icode *child);

    /// 将两个icode合并到一起。和 merge_icode 的区别是，当child是block时，不会省略
    icode *merge_icode_raw(icode *child);

    /// 将child的属性，复制到this中
    icode *merge_atrr(icode *child);

    /// 判断两个icode的引用是否是同一个
    bool is_ref_equal(icode *next);

    // icode_type类型和字符串名字的转换
    static std::string get_type_str(int type_int);
    static int get_type_int(std::string type_str);

public://icode base

    ICODE_TYPE m_type;
    std::string name;

    ///2020.12.6
    /// 添加此变量，如果此变量有内容，则引用时用此变量
    /// 用于结构体内部变量
    /// struct A
    /// {
    /// int b;
    /// char c;
    /// }d;
    /// d.b 变量的name=b; full_name=d.b
    std::string m_full_name;

    //icode的唯一标号--待废弃。改为和实例指针数值一样
    unsigned long m_icode_number;


    /// ICODE_TYPE_FUNC
    /// 内部的子指令  ICODE_TYPE_BLOCK
    std::vector<icode*> sub_icode;


    //算符 ICODE_TYPE_EXP_OP
    icode *left;
    icode *right;
    icode *result;
    icode *m_parent; ///< icode是parent，暂时只有icode_var_scope里会使用。var_scope里会重新填充parent，并根据此设置变量范围

    int m_level;//代码所在层级

    // 目标指令相关内容可以放到这里，由目标指令生成
    class c51_addr * target;


    // 变量被引用次数.未用
    int m_ref_number;
    int m_ref_read_number;
    int m_ref_write_number;



    /// directive source
    std::string m_dir_source;
    int m_dir_line_no;

    std::string m_source;//当前行的源代码
    int m_line_no;///当前行号


    void set_left(icode *mleft);
    void set_right(icode *mright);
    void set_result(icode *mresult);


public:
    /// icode转为dot的相关函数
    ///
    /// return def_str
    virtual std::string to_dotb();
    static int get_dot_index();
    static int g_icode_base_dot_index;
    std::string get_dot_name1();
    std::string get_dot_name();
    std::string get_dot_start_name_ref_block();
    std::string get_dot_end_name_ref_block();


    std::string get_name();

public://icode array
    //-----------------------
    std::vector<icode*> array_cnt;//每一层数组对应的个数，应该是常量。 在变量声明中，为数组大小。在变量使用中，为数组读取的索引号
    std::vector<icode*> array_shift;///< 待废弃，使用array_cnt代替。

    int get_array_bit_width();
    int set_array_bit_width(int total_bit_width);
    int refresh_array_total_bit_width();

public://icode_var

    ///ICODE_TYPE_DEF_VAR
    int m_bit_width;//位宽度，char 的位宽是8
    std::string m_type_str;//变量的类型字符串



    int is_typedef:1;//是否是一个typedef的类型声明
    int is_extern:1;
    int is_static:1;
    int is_thread_local:1;
    int is_auto:1;
    int is_register:1;

    int is_sbit:1;
    int is_sfr:1;
    int is_sfr16:1;
    int is_sfr32:1;
    int is_data:1;
    int is_idata:1;
    int is_pdata:1;
    int is_xdata:1;

    //是代码地址常量。此处表示代表是代码标签，标签在name中。
    // 此时不能再用num的值，而是应该用这个标签
    int is_code:1;


    int is_interrupt:1;//函数属性，是否是中断函数
    int is_using_group:1;//是否选择某个寄存器组
    int is_reentrant:1;
    int is_regparams:1;




    // 此处解决signed char的问题。
    // char默认为无符号。如果前面有signed 则必须有符号。
    // 解析时，先解析signed ,再解析char.
    // 解析 char时，默认is_signed设置为0.除非is_signed_force=1
    int is_signed_force:1;//如果signed明确标识，则设置此标识。
    int is_signed:1;
    int is_float32:1;



    ///function_specifier
    int is_inline:1;
    int is_noreturn:1;



    ///type_qualifier
    int is_const:1;
    int is_restrict:1;
    int is_volatile:1;
    int is_atomic:1;


    int is_array;///0--不是数组。 1--一维数组。2-二维数组。。。

    //-----------------------
    /// 1--一维指针 2--二维指针（指针的指针）
    int is_ptr;



    /// 如果一个变量是is_register,则此处可以描述需要使用的寄存器。如果没有，则系统自动分配
    std::string m_register_desc;

    ///icode_number_
    /// 保存变量范围的block的icode_number
    int m_var_scope;
    /// 辅助变量，用于 icode_var_scope使用
    /// 1-统计变量在那几个icode_number中使用
    /// 2-将多个block号合并为一个
    std::vector<int> m_var_scope_vec;

    //-----------------------

    ///  是否是var_in变量引用
    bool is_var_in();

    bool is_def_var();
    void set_width_from(icode * from);

    bool is_float();

    bool is_symbol();

    virtual int to_dot_var(std::string &def_str, std::string &ref_str);

public://icode ptr
    icode *m_in_ptr_type;///< 如果是指针或数组，则此变量表示指针/数组指向的内容的类型
    //int m_in_ptr_bit_width;///< --废弃 如果此变量是ptr。则此变量为指针指向的数据内容的位宽
    //int m_in_ptr_is_float32;///< --废弃
    //int m_in_ptr_is_signed;///< --废弃
public://icode const


    // ICODE_TYPE_I_CONST
    //改为有符号数。所有常数默认都为有符号数
    long  long num;
    //ICODE_TYPE_F_CONST
    float fnum;

    bool is_const_var();
    bool is_const_list();

    void const_copy_from(class icode* ic);
    void const_refresh_width();

    virtual int to_dot_const(std::string &def_str, std::string &ref_str);
public://icode func

    /// icode是函数类型时，获取函数名称标号
    std::string get_func_label();
    static std::string  get_func_label(std::string fname);

    /// icode是函数类型时，获取函数结束标号
    std::string get_func_end_label();
    /// icode是函数类型时，获取函数返回位置标号
    std::string get_func_ret_label();


    int m_interrupt_num;
    int m_using_group_num;


    /// 此处是寄存器描述，只在函数的icode中使用，说明参数放入寄存器而不是堆栈或固定位置
    /// 只有 is_regparams=1时起作用
    std::string m_reg_params_desc;

    int is_naked;//名称前不加内容

    virtual int to_dot_func(std::string &def_str, std::string &ref_str);

public://icode label
    /// icode是标签时，需要获取标签标号字符串
    std::string get_block_start_label();
    std::string get_block_end_label();

public://icode struct union
    int is_struct:1;
    int is_union:1;
    //int is_in_struct:1; 暂时不添加，需要时再添加

    ///结构体相关信息、union相关信息也是这些
    /// 后期此m_struct_name废弃，在m_struct_type[i].name中保存name信息。里面的full_name有带结构体名称的全名
    std::vector<std::string> m_struct_name;
    std::vector<class icode*> m_struct_type;
    int m_struct_offset_byte;
    int m_struct_offset_bit;
    icode *get_member_icode(std::string member_name);
    int get_member_offset_bit_width(std::string member_name);

};
std::ostream& operator<<(std::ostream &out, const  icode &s);


#endif // ICODE_H

