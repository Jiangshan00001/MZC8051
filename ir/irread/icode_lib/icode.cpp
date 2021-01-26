


/**
 *
 * \todo 编译器中，添加全局变量，说明编译的错误个数，警告个数
 *
 *
 *
 *




  */


/**
*
*
* @page compile_intro 编译说明
* @{
*
* @ref ptr_compile_intro1
*
* @ref ptr_compile_intro2
*
*
* @}
*
*
*
*
*
*
* @defgroup ptr_compile_intro1 对于指针的编译说明-变量声明和定义
* @{
* 各种算符对应的icode的表示：
*
*  -# 普通变量定义 int a;-->
* @code
*             {
                "m_bit_width": 16,
                "m_icode_number": 5,
                "m_type": "DEF_VAR",
                "m_type_str": " int",
                "name": "a",
                "this": 350282504
            }

  @endcode

*  -# 结构体变量定义
@code

*
* struct A
* {
* int a;
* char b;
* } bb;
*
{
                "is_struct": 1,
                "m_bit_width": 24,
                "m_icode_number": 13,
                "m_struct_name": [
                    "a",
                    "b"
                ],
                "m_struct_type": [
                    {
                        "m_bit_width": 16,
                        "m_icode_number": 5,
                        "m_type": "DEF_VAR",
                        "m_type_str": " int",
                        "name": "a",
                        "this": 350356992
                    },
                    {
                        "is_signed": 0,
                        "m_bit_width": 8,
                        "m_icode_number": 9,
                        "m_type": "DEF_VAR",
                        "m_type_str": " char",
                        "name": "b",
                        "this": 350379824
                    }
                ],
                "m_type": "DEF_VAR",
                "m_type_str": " struct A",
                "name": "bb",
                "this": 350402624
            }


@endcode

*  -# typedef
@code
  typedef unsigned int u16;

    {
        "is_signed": 0,
        "is_typedef": 1,
        "m_bit_width": 16,
        "m_icode_number": 5,
        "m_type": "DEF_VAR",
        "m_type_str": " typedef unsigned int",
        "name": "u16",
        "this": 12281848
    }

    u16 a;
            {
                "m_bit_width": 16,
                "m_icode_number": 13,
                "m_type": "DEF_VAR",
                "m_type_str": "u16",
                "name": "a",
                "result": {
                    "is_signed": 0,
                    "is_typedef": 1,
                    "m_bit_width": 16,
                    "m_icode_number": 5,
                    "m_type": "DEF_VAR",
                    "m_type_str": " typedef unsigned int",
                    "name": "u16",
                    "this": 12281848
                },
                "this": 12309912
            }

@endcode

*  -# 数组定义 char a[2][4];
@code
*
*       {"m_type":ICODE_TYPE_DEF_VAR,"m_bit_width":16,"m_icode_number":0,"m_type_str":" int","name":"a"}
*
*       char a[2][4];     --->ICODE_TYPE_DEF_VAR-> is_array=2. array_cnt=[2，4]
* {
  "array_cnt": [
    {
      "m_bit_width": 8,
      "m_icode_number": 7,
      "m_type": I_CONST,
      "name": "2",
      "num": 2
    },
    {
      "m_bit_width": 8,
      "m_icode_number": 10,
      "m_type": I_CONST,
      "name": "4",
      "num": 4
    }
  ],
  "is_array": 2,
  "m_bit_width": 16,
  "m_icode_number": 13,
  "m_in_ptr_type": {
    "m_bit_width": 16,
    "m_icode_number": 14,
    "m_type": ICODE_TYPE_DEF_VAR,
    "m_type_str": " int",
    "name": "a"
  },
  "m_type": ICODE_TYPE_DEF_VAR,
  "m_type_str": " int",
  "name": "a"
}
*

*
* c51_addr:
* ic->target里是一个常数，内容是3个字节的指针，对于代码空间是DATA_TYPE_J_DATA_LABEL类型
*                    对于内存空间是DATA_TYPE_J_DATA类型
*                    因为代码空间的地址现在无法确定，只能通过标签来表示代码空间常数
* ic->target->ptr_target里是指向内容的空间
@endcode
*
*  -# 指针定义 int *a;
@code
*   int *a; ----->ICODE_TYPE_DEF_VAR is_ptr=1; {"is_ptr":1,"m_bit_width":24,"m_icode_number":6,"m_in_ptr_bit_width":16,"m_in_ptr_is_signed":-1,"m_type":4,"m_type_str":" int","name":"a"}
*
*   ast_to_icode_decarator.cpp中， func_IAN_DECLARATOR_1 返回一个ICODE_TYPE_BLOCK类型的icode，
*       其result是指针变量 is_ptr=1
*
*   指针类型变量定义，is_ptr中保存指针层级， m_in_ptr_type保存指针指向的数据类型
*
*

*
* {
        "is_ptr": 1,
        "m_bit_width": 24,
        "m_icode_number": 6,
        "m_in_ptr_type": {
          "m_bit_width": 16,
          "m_icode_number": 7,
          "m_type": "DEF_VAR",
          "m_type_str": " int",
          "name": "a"
        },
        "m_type": "DEF_VAR",
        "m_type_str": " int",
        "name": "a"
      }
*
@endcode
*
*  -# 多维指针定义 char ***a;      ----->ICODE_TYPE_DEF_VAR is_ptr=3
@code
* struct A{
* int b;
* char c;
* }; --->ICODE_TYPE_DEF_VAR is_struct. is_union. m_struct_name, m_struct_type
*
*
*
* int &b = a;   --->相当于 int *b;  ICODE_TYPE_DEF_VAR_IN_VAR
*
@endcode

*
* @}
*
*
  */

/**
* @defgroup ptr_compile_intro2 对于指针的编译说明-变量使用
* @{
*
*
* - *a;
* *a=2;
* @code
* {
      "is_ptr": -1,
      "m_icode_number": 24,
      "m_type": "DEF_VAR_IN",
      "result": {
        "m_icode_number": 23,
        "m_type": "SYMBOL_REF",
        "result": {
          "is_ptr": 1,
          "m_bit_width": 24,
          "m_icode_number": 16,
          "m_level": 2,
          "m_type": "DEF_VAR",
          "m_type_str": " int",
          "name": "a"
        }
      }
    }

* @endcode
*
*
*
*
*
*
* 数组访问，一种是result就是数组：
* @code
* a[1][2] -->
{
  "array_cnt": [
    {
      "m_bit_width": 8,
      "m_icode_number": 32,
      "m_type": I_CONST,
      "name": "1",
      "num": 1
    },
    {
      "m_bit_width": 8,
      "m_icode_number": 34,
      "m_type": I_CONST,
      "name": "2",
      "num": 2
    }
  ],
  "is_array": -2,
  "m_icode_number": 30,
  "m_type": DEF_VAR_IN,
  "result": {
    "array_cnt": [
      {
        "m_bit_width": 8,
        "m_icode_number": 7,
        "m_type": 1,
        "name": "2",
        "num": 2
      },
      {
        "m_bit_width": 8,
        "m_icode_number": 10,
        "m_type": 1,
        "name": "4",
        "num": 4
      }
    ],
    "is_array": 2,
    "m_bit_width": 16,
    "m_icode_number": 13,
    "m_in_ptr_type": {
      "m_bit_width": 16,
      "m_icode_number": 14,
      "m_type": DEF_VAR,
      "m_type_str": " int",
      "name": "a"
    },
    "m_type": DEF_VAR,
    "m_type_str": " int",
    "name": "a"
  }
}
* @endcode
*
*另一种是result是指针，但是通过数组的方式来访问：
* int *a;
* a[2]=3;
*
* @code
* {
  "array_cnt": [
    {
      "m_bit_width": 8,
      "m_icode_number": 25,
      "m_type": "I_CONST",
      "num": 2
    }
  ],
  "is_array": -1,
  "m_icode_number": 23,
  "m_type": "DEF_VAR_IN",
  "result": {
    "is_ptr": 1,
    "m_bit_width": 24,
    "m_icode_number": 16,
    "m_in_ptr_type": {
      "m_bit_width": 16,
      "m_icode_number": 17,
      "m_level": 2,
      "m_type": "DEF_VAR",
      "m_type_str": " int",
      "name": "a"
    },
    "m_level": 2,
    "m_type": "DEF_VAR",
    "m_type_str": " int",
    "name": "a"
  }
}
* @endcode
*
*
*
* 数组需要生成代码来计算指针，计算的转换在icode_ptr_calc中实现
*
*
*
*
* - a.b的使用
*
*
*
*
*
*
* a->b
* 在函数 \ref func_IAN_POSTFIX_EXPRESSION_6 中实现
*
*
*
* a[3] ----------------> ICODE_TYPE_DEF_VAR_IN_VAR-->* (3x2+address_of(a)).  ref. ref->result-a; ref->is_array=-1 ref->array_cnt=[3]
* *a   ----------------> ICODE_TYPE_DEF_VAR_IN_VAR
* &a   ----------------> address_of
* &a;---> address_of 算符。 有right属性为a的ref，result引用为结果赋值对象。
* a->b ----------------> ICODE_TYPE_DEF_VAR_IN_VAR
* a.b  ----------------> ICODE_TYPE_DEF_VAR_IN_VAR
*
*
*
* sizeof
*
*
*
* @}
**/





///
///
/// ICODE_TYPE_I_CONST
/// icode *t= new_icode():
/// t->num = const_num;
/// t->m_bit_width = ?
/// t->const_refresh_width();
///
///
/// ICODE_TYPE_SYMBOL_REF
///  参数引用: result中是结果。
///  如果 is_array!=0，则是数组读写。
///
///
/// ICODE_TYPE_LABELED_BLOCK_START_REF
/// ICODE_TYPE_LABELED_BLOCK_END_REF
///  参数：result中是对应的block
///
///
/// ICODE_TYPE_CALL:
/// sub_icode[0]--ret 返回值 实参
/// sub_icode[1]--参数1 实参
/// sub_icode[2]--参数2 实参
/// 。。。
/// result --- 被调函数的icode...之前是left，2020.8.9 改为result。 此处是ref，还是直接的icode?????.应该为ref
///
///
///
///




#include <map>
#include <string>
#include <vector>
#include <iostream>

#include "icode.h"
#include "ast_base.h"
#include "mylog.h"
//#include "comp_context.h"

#include "replace.h"


#define set_if_true(k) if(k){j[#k] = 1;}
#define set_if_false(k) if(!k){j[#k] = 0;}

#define get_if_exist(k) if(j.find(#k)!=j.end()){ k = j[#k];}



using mylog::cout;
using mylog::cerr;


extern std::map<int, std::string> g_icode_type_2_str;
extern std::map<std::string, int> g_icode_str_2_type;



icode::icode()
{
    cout<<"icode new error\n";
    cout<<"this should never be called. as no icode_number init \n";
    assert(0);
}

icode::icode(int icode_num)
{
    if(g_icode_type_2_str.empty())
    {
        load_icode_debug_info();
    }

    m_type=ICODE_TYPE_UNKNOWN;
    //name

    m_icode_number = (unsigned long)this ;//icode_num;

    left = 0;
    right = 0;
    result = 0;
    m_parent = NULL;

    m_level = 0;

    target = 0;

    m_ref_number=0;
    m_ref_read_number = 0;
    m_ref_write_number = 0;

    //m_dir_source
    m_dir_line_no = 0;
    m_line_no = 0;

    //icode var

    m_bit_width = 0;

    is_typedef=0;//是否是一个typedef的类型声明
    is_extern=0;
    is_static=0;
    is_thread_local=0;
    is_auto=0;
    is_register=0;


    is_sbit = 0;
    is_sfr = 0;
    is_sfr16 = 0;
    is_sfr32 = 0;
    is_data = 0;
    is_idata = 0;
    is_pdata = 0;
    is_xdata = 0;

    is_code = 0;

    is_interrupt = 0;//函数属性，是否是中断函数
    is_using_group = 0;//是否选择某个寄存器组
    is_reentrant = 0;
    is_regparams = 0;


    // 此处解决signed char的问题。
    // char默认为无符号。如果前面有signed 则必须有符号。
    // 解析时，先解析signed ,再解析char.
    // 解析 char时，默认is_signed设置为0.除非is_signed_force=1
    is_signed_force = 0;
    is_signed=1;//默认数值都是带符号的。只有unsigned时，才变0。 char默认无符号
    is_float32 =0;

    is_inline = 0;
    is_noreturn = 0;

    is_const = 0;
    is_restrict = 0;
    is_volatile = 0;
    is_atomic = 0;


    is_array=0;
    //array_shift = NULL;
    is_ptr=0;

    m_var_scope = 0;

    m_in_ptr_type = NULL;
    //m_in_ptr_bit_width = 0;
    //m_in_ptr_is_float32 = 0;
    //m_in_ptr_is_signed = 0;


    //const
    num = 0;
    fnum = 0;




    //func
    m_interrupt_num = 0;
    m_using_group_num = 0;

    is_naked = 0;

    //struct_union
    is_struct = 0;
    is_union = 0;

    m_struct_offset_byte = 0;
    m_struct_offset_bit = 0;

}

icode::~icode()
{

}


icode *icode::merge_icode_raw(icode *child)
{
    if(child==NULL)return this;

    //if(child->m_type==ICODE_TYPE_BLOCK)
    //{
    //    this->sub_icode.insert(this->sub_icode.end(), child->sub_icode.begin(), child->sub_icode.end());
    //}
    //else
    {
        this->sub_icode.push_back(child);
    }

    return this;
}

icode * icode::merge_icode(icode *child)
{
    if(child==NULL)return this;

    if(child->m_type==ICODE_TYPE_BLOCK)
    {
        this->sub_icode.insert(this->sub_icode.end(), child->sub_icode.begin(), child->sub_icode.end());
    }
    else
    {
        this->sub_icode.push_back(child);
    }

    return this;
}

icode *icode::merge_atrr(icode *child)
{

    /// 属性值是只叠加，不减少
    if(child->is_typedef)is_typedef = 1;
    if(child->is_extern)is_extern = 1;
    if(child->is_static)is_static = 1;
    if(child->is_thread_local)is_thread_local = 1;
    if(child->is_auto)is_auto = 1;
    if(child->is_register)is_register = 1;


    if(child->is_sbit)is_sbit = 1;
    if(child->is_sfr)is_sfr = 1;
    if(child->is_sfr16)is_sfr16 = 1;
    if(child->is_sfr32)is_sfr32 = 1;
    if(child->is_data)is_data = 1;
    if(child->is_idata) is_idata = 1;
    if(child->is_pdata)is_pdata = 1;
    if(child->is_xdata)is_xdata = 1;
    if(child->is_code)is_code=1;

    if(child->is_interrupt)
    {
        is_interrupt=1;
        m_interrupt_num = child->m_interrupt_num;
    }
    if(child->is_using_group){
        is_using_group =1;
        m_using_group_num = child->m_using_group_num;
    }
    if(child->is_regparams){
        is_regparams=1;
        m_reg_params_desc = child->m_reg_params_desc;
    }
    if(child->is_reentrant)is_reentrant=1;

    if(child->is_signed)is_signed=1;
    if(child->is_float32)is_float32=1;
    if(child->is_inline)is_inline=1;
    if(child->is_noreturn)is_noreturn=1;

    if(child->is_const)is_const = 1;
    if(child->is_restrict)is_restrict = 1;
    if(child->is_volatile)is_volatile = 1;
    if(child->is_atomic)is_atomic = 1;

    if(child->is_struct)is_struct = 1;
    if(child->is_union)is_union = 1;

    if(child->is_array)is_array=child->is_array;
    if(child->is_ptr)is_ptr=child->is_ptr;

    return this;
}



std::string string_to_printf(std::string strA)
{
    std::string retA=strA;
    replace(retA, "\n", "\\n");
    replace(retA, "\r", "\\r");
    replace(retA, "\t", "\\t");
    replace(retA, "\v", "\\v");
    replace(retA, "\f", "\\f");
    replace(retA, "\"", "\\\"");

    return retA;
}



std::string icode::get_var_type()
{
    std::stringstream ss1;


    {
        if(this->is_float32)
        {
            return "f32";
        }


        if(this->is_signed)
        {
            ss1<<"i";
        }
        else
        {
            ss1<<"u";
        }
        ss1<<this->m_bit_width;
    }


    if(this->is_array)
    {
        std::string basic_type = this->m_in_ptr_type->get_var_type();
        ss1<< "["<<basic_type<<"]";
        for(int i=0;i<(int)this->array_cnt.size();++i)
            ss1<<"["<<this->array_cnt[i]->to_str(1)<<"]";
    }

    if(this->is_ptr)
    {
        ss1<<"*"<< this->is_ptr<<"*[" ;
        ss1<<this->m_in_ptr_type->get_var_type()<<"]";
    }



    if(this->is_struct&& (!this->is_ptr))
    {

        ss1<<"(";
        for(int i=0;i<(int)this->m_struct_type.size();++i)
        {
            ss1<<this->m_struct_type[i]->to_str(1);
        }
        ss1<<")";
    }
    if(this->is_union&& (!this->is_ptr))
    {
        ss1<<"((";
        for(int i=0;i<(int)this->m_struct_type.size();++i)
        {
            ss1<<this->m_struct_type[i]->to_str(1);
        }
        ss1<<"))";
    }






    if(this->is_typedef)
    {
        ss1<<","<< " TYPEDEF(1) ";
    }
    if(this->is_extern)
    {
        ss1<<", EXTERN(1) ";
    }
    if(this->is_static)
    {
        ss1<<", STATIC(1) ";
    }
    if(this->is_sfr)
    {
        ss1<<", SFR(1) ";
    }
    if(this->is_sfr16)
    {
        ss1<<", SFR16(1) ";
    }
    if(this->is_sfr32)
    {
        ss1<<", SFR32(1) ";
    }
    if(this->is_idata)
    {
        ss1<<", IDATA(1) ";
    }
    if(this->is_xdata)
    {
        ss1<<", XDATA(1) ";
    }
    if(this->is_naked)
    {
        ss1<<", NAKED(1) ";
    }
    if(this->is_register)
    {
        //某个变量，是寄存器参数
        ss1<<", REGISTER(\""<<this->m_register_desc<<"\") ";
    }
    if(this->is_sbit)
    {
        ss1<<", SBIT(1) ";
    }
    if(this->is_code)
    {
        ss1<<", CODE(1) ";
    }
    if(this->is_const)
    {
        ss1<<", CONST(1) ";
    }

    return ss1.str();
}

std::string icode::vector_icode_ptr_cont(std::vector<icode *> vec1)
{
    std::stringstream strA;

    for(unsigned i=0;i<vec1.size();++i)
    {
        strA<< vec1[i]->to_str();
    }
    return strA.str();
}


bool icode::is_ref_equal(icode *next)
{
    icode *cmp1= this;
    icode *cmp2= next;


    if(next==NULL)
    {
        return false;
    }


    bool is_this_ptr = 0;
    bool is_next_ptr = 0;
    if((this->m_type==ICODE_TYPE_SYMBOL_REF)&&
            ((this->is_array!=0)||
             (this->is_ptr!=0))
            )
    {
        //指针
        is_this_ptr = 1;
    }

    if((next->m_type==ICODE_TYPE_SYMBOL_REF)&&
            ((next->is_array!=0)||
             (next->is_ptr!=0))
            )
    {
        is_next_ptr = 1;
    }

    if(is_next_ptr!=is_this_ptr)
    {
        //指针和非指针比较，直接返回false
        return false;
    }
    if(is_next_ptr && is_this_ptr)
    {
        //两个指针比较较
        if((this->result==NULL)||
                (next->result==NULL))
        {
            //指针不指向实际内容
            return false;
        }
        if(this->result!=next->result)
        {
            return false;
        }
        if(this->is_array!=next->is_array)
        {
            return false;
        }
        if(this->is_ptr!=next->is_ptr)
        {
            return false;
        }
        //指针判断是否相等，没有好的办法，咱时确定
        if(this!=next)
        {
            return false;
        }
        return true;
    }




    if((this->m_type==ICODE_TYPE_SYMBOL_REF)&&
            (this->is_array==0)&&
            (this->is_ptr==0)
            )
    {

        cmp1=this->result;
    }
    if((next->m_type==ICODE_TYPE_SYMBOL_REF)&&
            (this->is_array==0)&&
            (this->is_ptr==0)
            )
    {
        cmp2 = next->result;
    }

    /// 两个引用的比较
    /// 如果是非指针，则直接比较。如果是指针，需要比较指针的位置

    //cout<<"cmp1"<<*cmp1<<"addr:"<< cmp1<<"\n";
    //cout<<"cmp2"<<*cmp2<<"addr:"<< cmp2<<"\n";
    return cmp1==cmp2;

}

int icode::to_dot(std::string &def_str, std::string &ref_str)
{

    std::stringstream stA;
    if(m_type==ICODE_TYPE_CONST_LIST)
    {
        ref_str=this->get_dot_name();

        stA<<ref_str<<" [label=\"const_list\"]\n";
        def_str=stA.str();
    }
    else if(m_type==ICODE_TYPE_SYMBOL_REF)
    {
        ref_str=this->get_dot_name();
        stA.clear();
        stA.str("");
        ///此处对于数组的引用未处理显示 TODO: to_dot 2020.8.10
        stA<< ref_str<<"[ label=ref]\n" ;

        if(this->result!=NULL){
            if(this->result->m_type==ICODE_TYPE_FUNC){
            stA<< ref_str<< "->" << this->result->get_dot_name()<<"[label=result_"<< this->result->name << " ]\n";
            }
            else{
            stA<< ref_str<< "->" << this->result->get_dot_name()<<"[label=result]\n";
            }
        }
        def_str=stA.str();
        return 0;
    }
    else if(m_type==ICODE_TYPE_FUNC_RETURN)
    {
        ref_str=this->get_dot_name();
        stA.clear();
        stA.str("");
        stA<<ref_str<<"[label="<< "return]\n";
        def_str = stA.str();
    }
    else if((m_type==ICODE_TYPE_LABELED_BLOCK))
    {
        ref_str = this->get_dot_name();

        stA<< ref_str<<"[ label=label]\n" ;
        def_str=stA.str();
    }
    else if(m_type==ICODE_TYPE_LABELED_BLOCK_START_REF)
    {
        ref_str = this->get_dot_name();

        stA<< ref_str<<"[ label=ref_start]\n" ;
        if(this->result!=NULL){
            stA<< ref_str<< "->" << this->result->get_dot_name()<<"[label=result]\n";
        }
        def_str=stA.str();
    }
    else if (m_type==ICODE_TYPE_EXP_OP)
    {
        ref_str = this->get_dot_name();
        stA.clear();
        stA.str("");
        stA<<ref_str<<"[ label=\"" << string_to_printf(this->name)<<"\"]\n";
        if(this->left!=NULL)
        {
            std::string def_str1, ref_str1;
            this->left->to_dot(def_str1, ref_str1);
            stA<<def_str1;

            ref_str1 = this->left->get_dot_start_name_ref_block();
            stA<<ref_str<<"->"<<ref_str1<<"[label=\"left\"]\n";
        }
        if(this->right!=NULL)
        {
            std::string def_str1, ref_str1;
            this->right->to_dot(def_str1, ref_str1);
            stA<<def_str1;

            ref_str1 = this->right->get_dot_start_name_ref_block();
            stA<<ref_str<<"->"<<ref_str1<<"[label=\"right\"]\n";
        }
        if(this->result!=NULL)
        {
            std::string def_str1, ref_str1;
            this->result->to_dot(def_str1, ref_str1);
            stA<<def_str1;

            ref_str1 = this->result->get_dot_start_name_ref_block();
            stA<<ref_str<<"->"<<ref_str1<<"[label=\"result\"]\n";
        }

        def_str=stA.str();
    }

    else if((this->m_type==ICODE_TYPE_FUNC)||(this->m_type==ICODE_TYPE_CALL)||(m_type==ICODE_TYPE_BLOCK))
    {
        return to_dot_func(def_str, ref_str);
    }
    else if((this->m_type==ICODE_TYPE_I_CONST)||(this->m_type==ICODE_TYPE_F_CONST))
    {
        return to_dot_const(def_str, ref_str);
    }
    else if((this->m_type==ICODE_TYPE_DEF_VAR)||(this->m_type==ICODE_TYPE_DEF_VAR_TMP)||
            (this->m_type==ICODE_TYPE_FUNC_DEF_ARG)||
            (this->m_type==ICODE_TYPE_FUNC_RET_TYPE)||
            (this->m_type==ICODE_TYPE_DEF_VAR_IN_VAR)||
            (this->m_type==ICODE_TYPE_DEF_VAR_IN_VAR_TMP)
            )
    {
        return to_dot_var(def_str, ref_str);
    }
    else if(this->m_type==ICODE_TYPE_ASM)
    {
        ref_str=this->get_dot_name();
        stA.clear();
        stA.str("");
        std::string asm_str = string_to_printf(this->name);
        if(asm_str.size()>20)
        {
            asm_str.resize(20);
            asm_str=asm_str+"...";
        }
        stA<<ref_str<<"[ label=\"ASM: " << asm_str<<"\"]\n";
        def_str=stA.str();

    }

    else if(m_type==ICODE_TYPE_CONST_STRING)
    {
        ref_str=this->get_dot_name();
        stA.clear();
        stA.str("");

        std::string asm_str = string_to_printf(this->name);
        if(asm_str.size()>20)
        {
            asm_str.resize(20);
            asm_str=asm_str+"...";
        }
        stA<<ref_str<<"[ label=\"STR " << asm_str<<"\"]\n";
        def_str=stA.str();
    }
    else if(this->m_type==ICODE_TYPE_UNKNOWN)
    {
        ref_str="unknown";
        def_str="unknown\n";
    }

    return 0;
}






std::ostream &operator<<(std::ostream &out, const icode &s)
{
    out<<"{";
    out<<"CTYPE:icode,";
    out<<"type:";
    out<< g_icode_type_2_str[ ((int)s.m_type) ];
    out<< ",";
    out<<"name:"<<s.name<<",";

    if(1)
    {
        out<<"bit_width:"<<s.m_bit_width<<",";
    }
    out<<"icode_number:"<<s.m_icode_number<<",";


    for(unsigned i=0;i<s.sub_icode.size();++i)
    {
        out<<"sub_"<<i<<":"<<*s.sub_icode[i]<<",";
    }

    PTR_JSON_OUT(s.left, "left", out);
    PTR_JSON_OUT(s.right, "right", out);
    PTR_JSON_OUT(s.result, "result", out);

    out<<"}";
    return out;
}
