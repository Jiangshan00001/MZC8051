#include "comp_context.h"
#include "icode.h"
#include "token_defs.h"
#include "parser.h"
#include "driver.h"
#include "target_base.h"
#include "comp_context_gen_defs.h"
#include "mylog.h"

#include "target_base.h"
#include "comp_context_yy_debug.h"

using mylog::cerr;
using mylog::cout;
using mylog::cwarn;

namespace NS_C512IR{

comp_context::comp_context(int target_typ):
    icode_manage(target_typ)
{
    m_just_ret_tree = 0;
}

comp_context::~comp_context()
{
}



void comp_context::parse_start_token(token_defs &start_tk)
{
    printf("get token:\n");
    this->ast_to_icode(&start_tk, 0, 0);
    printf("parse finish!\n");
}



int comp_context::add_function(token_defs *func)
{
    if(m_just_ret_tree)
    {
        m_yy_tree = m_yy_tree +"============\n"+ token_to_tree(func);

        //此处生成tree
        return 0;
    }

    icode* funci = ast_to_icode(func);
    add_to_top_icodes(funci);

    /// add_symbol 函数symbol 在ast-to-icode时已经加入符号表
    return 0;
}

int comp_context::add_declaration(token_defs *declaration)
{
    if(m_just_ret_tree)
    {
        m_yy_tree = m_yy_tree +"============\n"+ token_to_tree(declaration);

        //此处生成tree
        return 0;
    }

    icode *a = ast_to_icode(declaration);

    add_to_top_icodes(a);


    return 0;
}


int comp_context::add_to_top_icodes(icode *ic)
{
    if(ic->m_type==ICODE_TYPE_BLOCK)
    {
        for(unsigned i=0;i<ic->sub_icode.size();++i)
        {
            add_to_top_icodes(ic->sub_icode[i]);
        }
        return 0;
    }
    ///检查是否已经存在，如果已经存在，则不再重复添加
    if(std::find(m_top_icodes->m_top_icodes->sub_icode.begin(), m_top_icodes->m_top_icodes->sub_icode.end(), ic)==m_top_icodes->m_top_icodes->sub_icode.end())
    {
        ///FIXME此处如果变量已经生命过，则不再重复填入top_icodes.
        /// 函数无此问题，因为函数声明如果已经声明过，则不再返回声明的icode
        /// 函数声明应该和此采用一致的行为，但是暂时没有，理论上应该可以工作
        /// 不一致的原因是： 变量的new_var需要一直返回正确的变量，如果已经定义过了，则返回之前icode，方便后期操作
        /// function的ast_to_icode_func_decl 当时定义的是不返回icode，需要后面自己查找icode
        /// 后期可以统一定义为返回icode，这样不用再次查找了!
        /// 如果要修改，需要修改  function的ast_to_icode_func_decl 和相关的调用
        /// 通过添加 is_already_defined 解决

        m_top_icodes->m_top_icodes->sub_icode.push_back(ic);
        if(ic->m_type==ICODE_TYPE_FUNC)
        {
            m_functions[ic->name] = ic;
        }
    }

    return 0;
}


int comp_context::check_type(std::string text1)
{
    //
    //example::Parser::token::ENUMERATION_CONSTANT;
#if 1
    sym* c =this->find_symbol(text1);

    if(c!=NULL)
    {
        if(c->def_icode->is_typedef)
        {
            return Parser::token::TYPEDEF_NAME;
        }
    }

    if(m_enum_items.find(text1)!=m_enum_items.end())
    {
        return Parser::token::ENUMERATION_CONSTANT;
    }
#endif
    return  (Parser::token::IDENTIFIER);
}

icode *comp_context::new_ref_icode(icode *to_ref)
{
    return m_top_icodes->new_ref_icode(to_ref);
}



icode* comp_context::ast_to_icode_func_definition(token_defs *tdefs, bool need_result_icode, icode *ret)
{
    //0x4d01-function_definition->declaration_specifiers declarator declaration_list compound_statement
    //IAN_FUNCTION_DEFINITION_2 -0x4d02-function_definition->declaration_specifiers declarator compound_statement

    /// declaration_specifiers(int) declarator(main)  compound_statement({int a=1;})

    assert(tdefs->m_tk_type_int==IAN_FUNCTION_DEFINITION_2);
    //0x4d01--此处为老式的c语言语法，暂不实现


    icode *a = ret;
    a->m_type=ICODE_TYPE_BLOCK;


    ///函数，最顶层
    //this->m_level = 0;



    ///函数处理
    token_defs *declaration_specifiers = tdefs->m_tk_elems[0];
    token_defs *declarator = tdefs->m_tk_elems[1];
    token_defs *compound_statement = NULL;
    std::string func_name;

    compound_statement = tdefs->m_tk_elems[2];



    if(ast_to_icode_func_decl(declaration_specifiers, declarator,ret, func_name)<0)
    {
        return ret;
    }


    sym *s = find_symbol(func_name);
    assert(s!=NULL);

    if(!s->def_icode->is_extern)
    {
        //函数重复定义？？？
        cout<<"ERROR: function redefined:"<< func_name <<"\n";
        a->m_type = ICODE_TYPE_BLOCK;
        a->sub_icode.clear();
        return a;
    }

    a = s->def_icode;
    ///之前函数是extern声明，现在改为定义，去掉extern属性
    a->is_extern = 0;


    ///添加当前函数的icode指针，方便函数内部转码时使用
    this->m_curr_func = a;


    //unsigned symbol_list_size_before = get_symbol_list_size();
    this->level_enter();
    //this->m_level++;

    //进入一个函数定义，不管如何，都需要重新载入符号表种的函数入参数和返回值
    assert(a->sub_icode[0]->m_type==ICODE_TYPE_FUNC_RET_TYPE);
    add_symbol(a->sub_icode[0]->name, a->sub_icode[0]);

    for(unsigned i=1;i<a->sub_icode.size();++i)
    {
        icode *arg1 = a->sub_icode[i];
        assert(arg1->m_type == ICODE_TYPE_FUNC_DEF_ARG);
        add_symbol(arg1->name, arg1);
    }



    // 函数运行程序
    icode *b = ast_to_icode(compound_statement);


    if(b->m_type==ICODE_TYPE_BLOCK)
    {
        a->sub_icode.insert(a->sub_icode.end(), b->sub_icode.begin(), b->sub_icode.end());
    }
    else
    {
        a->sub_icode.push_back(b);
    }

    //this->m_level--;
    this->level_leave();
    //set_symbol_list_size(symbol_list_size_before);

    return ret;
}
///此函数后期会废弃，改为icode_manage::new_var函数
int comp_context::ast_to_icode_func_decl(token_defs *declaration_specifiers, token_defs *declarator, icode *ret, std::string &func_name)
{
    //IAN_FUNCTION_DEFINITION_2 -0x4d02-function_definition->declaration_specifiers declarator compound_statement

    //0x1b02--//declaration->declaration_specifiers init_declarator_list ';'
    //         declaration_specifiers(void) init_declarator_list(a()) ;
    // 0x310d: //direct_declarator->direct_declarator '(' ')'
    // 0x310c: //direct_declarator->direct_declarator '(' parameter_type_list ')'

    icode *func = ret;

    icode *type_ic = new_icode();
    type_ic->m_type=ICODE_TYPE_DEF_VAR;

    ast_to_icode(declaration_specifiers, 0, type_ic);

    ///--------------------------
    /// 2020.9.14 添加调试位置信息
    type_ic->m_dir_line_no = declaration_specifiers->line_no;
    type_ic->m_dir_source = declaration_specifiers->m_file_name;
    type_ic->m_source = mp_driver->streamname;
    type_ic->m_line_no = type_ic->m_dir_line_no;/// \todo 此处行号信息没有
    ///--------------------------


    ///函数名称和参数解析完成，会生成参数的符号，解析完成后，就把参数符号表中去除
    /// 不然就会变成全局变量
    //unsigned symbol_list_size_before = get_symbol_list_size();
    //this->m_level++;
    this->level_enter();

    //先解析函数名称和参数列表、名称在返回值的name字段。参数列表在sub_ic字段
    icode * decl_ic=ast_to_icode(declarator, 1);

    //this->set_symbol_list_size(symbol_list_size_before);
    //this->m_level--;
    this->level_leave();


    func_name = decl_ic->result->name;
    //查找是否有此函数
    sym* s = find_symbol(decl_ic->result->name);
    if(s!=NULL)
    {
        ///之前已经声明过了
        {
            //检查extern 和当前类型是否一致
            //TODO: 符号重复定义。未检查
            //如果一致，则替换为之前函数声明

            /// 此处从1开始，因为decl_ic中，0位置已经添加了一个空的返回值占位符
            for(unsigned i=1;i<decl_ic->result->sub_icode.size();++i)
            {
                icode *arg1 = decl_ic->result->sub_icode[i];
                arg1->m_type = ICODE_TYPE_FUNC_DEF_ARG;
                if(s->def_icode->sub_icode[i]->m_bit_width!=arg1->m_bit_width)
                {
                    cerr<<"func:"<<s->name<<"decl different. arg:"<<i<<". bitwidth:"<<s->def_icode->sub_icode[i]->m_bit_width
                       <<" VS "<< arg1->m_bit_width<<"\n";
                }
                if(s->def_icode->sub_icode[i]->name!=arg1->name)
                {
                    cwarn<<"func:"<<s->name<<"decl different. arg:"<<i<<". name:"<<s->def_icode->sub_icode[i]->name
                       <<" VS "<< arg1->name <<"\n";
                    s->def_icode->sub_icode[i]->name=arg1->name;
                }
            }
        }
        return 0;
    }

    //无声明，则此处添加
    func->m_type = ICODE_TYPE_FUNC;

    func->name = decl_ic->result->name;
    func->is_extern = 1;


    if(type_ic->is_inline)
    {
        //声明时是否是inline
        /// inline  void func1();
        /// inline 参数在返回值的属性上
        /// 需要转移到函数体的属性上
        func->is_inline = 1;
        type_ic->is_inline = 0;
    }


    //添加函数符号表
    add_symbol(func->name, func);
    this->m_functions[func->name] = func;


    //返回值
    int is_already_exist = 0;

    icode *ic_ret_v = this->new_var(this->get_func_ret_var_name(func->name), type_ic, is_already_exist);

    ///=====
    /// bug fix:
    /// 因为函数如果是extern属性，则type_ic为extern。但是函数返回值不能有extern属性
    ///
    ///

    ic_ret_v->is_extern = 0;
    ic_ret_v->is_static = 0;

    ///=====


    assert(is_already_exist==0);
    ic_ret_v->m_type=ICODE_TYPE_FUNC_RET_TYPE;
    func->sub_icode.push_back(ic_ret_v);

    ///参数
    /// 此处从1开始，因为decl_ic中，0位置已经添加了一个空的返回值占位符
    for(unsigned i=1;i<decl_ic->result->sub_icode.size();++i)
    {
        icode *arg1 = decl_ic->result->sub_icode[i];
        arg1->m_type = ICODE_TYPE_FUNC_DEF_ARG;
        func->merge_icode(arg1);
    }
    //其他函数属性
    func->merge_atrr(decl_ic->result);

    //函数返回值的引用
    func->result = new_ref_icode(func->sub_icode[0]);



    //2021.3.20 添加函数指针的支持
    func->is_ptr = decl_ic->result->is_ptr;
    func->is_typedef = type_ic->is_typedef;

    /// TODO: 函数指针的处理--待添加
    if(func->is_ptr)
    {
        //函数指针，则是变量或者typedef类型???
        // 定义一个变量，类型是函数指针


    }

    if(func->is_typedef)
    {
        //typdef必须是函数指针
        assert(func->is_ptr);
        //定义一个变量，类型是函数指针。typdef名称是func->name

    }



    return 0;
}

int get_initializer_scope_cnt(icode* initializer)
{
    int cnt=0;

    while(1)
    {
        if(initializer->m_type==ICODE_TYPE_SCOPE)
        {
            cnt++;
        }

        if(initializer->sub_icode.size()>0)
        {
            initializer = initializer->sub_icode[0];
        }
        else
        {
            break;
        }
    }
    return cnt;
}

void const_list_to_flat2(icode* initializer, icode * const_list, icode* array_in_type, int in_array, int array_cnt)
{
    for(int i=0;i<const_list->sub_icode.size();++i)
    {
        icode *curr_list = const_list->sub_icode[i];

        if(curr_list->m_type==ICODE_TYPE_CONST_LIST)
        {
            if(in_array>array_cnt)
            {
                const_list_to_flat2(initializer, curr_list->sub_icode[0], array_in_type->m_struct_type[i], in_array+1, array_cnt);
            }
            else
            {
                const_list_to_flat2(initializer, curr_list, array_in_type, in_array, array_cnt);
            }

        }
        else if(curr_list->m_type==ICODE_TYPE_SCOPE)
        {
            assert(curr_list->sub_icode.size()==1);
            //const_list_to_flat2(initializer, curr_list->sub_icode[0], array_in_type, in_array+1, array_cnt);
#if 1
            if(in_array>array_cnt)
            {
                const_list_to_flat2(initializer, curr_list->sub_icode[0], array_in_type->m_struct_type[i], in_array+1, array_cnt);
            }
            else
            {
                const_list_to_flat2(initializer, curr_list->sub_icode[0], array_in_type, in_array+1, array_cnt);
            }
#endif
        }
        else if((curr_list->m_type==ICODE_TYPE_F_CONST)||
                (curr_list->m_type==ICODE_TYPE_I_CONST)
                )
        {
            if(in_array>array_cnt)
            {
                curr_list->m_bit_width = array_in_type->m_struct_type[i]->m_bit_width;
            }
            else
            {
                curr_list->m_bit_width = array_in_type->m_bit_width;
            }
            initializer->sub_icode.push_back(curr_list);
        }
        else
        {
            assert(0);
        }
    }
}



int comp_context::correct_initializer_width_from_declarator(icode *var, icode *initializer)
{
    /// int a=1;
    ///var: ICODE_TYPE_DEF_VAR (4)
    /// initializer ICODE_TYPE_I_CONST (1)
    assert(var->is_def_var());


    /// 结构体的初始值：
    /// struct A
    /// {
    /// int a;
    /// char b;
    /// } ;
    /// struct A c={1,3};
    /// struct A c[5]={{1,3},{2,4} };
    if(var->is_array)
    {
        ///int a[][3][2]={ {{1,2},{3,4},{5,6}},{{1,2},{3,4},{5,6}},{{1,2},{3,4},{5,6}},{{1,2},{3,4},{5,6}}  };
        /// 初始化数组。之前是const_list，现在改为scope，scope里面是const_list。 const_list里是scope或者const
        /// int a[5]={1,2,3,4};


        if(initializer->m_type==ICODE_TYPE_SCOPE)
        {
            ///TODO: 此处代码对于 char a[]={"abcdedf"};没有处理。需要处理

            ///内部元素的宽度
            int elem_bit_width = var->m_in_ptr_type->m_bit_width;

            int init_scope_cnt = get_initializer_scope_cnt(initializer);

            assert(init_scope_cnt>=var->is_array);

            int target_total_bit_width = var->get_array_bit_width();
            int first_cnt = initializer->sub_icode[0]->sub_icode.size();
            if(target_total_bit_width==0)
            {
                assert(var->array_cnt.size()>0);
                assert(var->array_cnt[0]->m_type==ICODE_TYPE_I_CONST);
                assert(var->array_cnt[0]->num==0);
                var->array_cnt[0]->num = first_cnt;
                target_total_bit_width = var->get_array_bit_width();
            }


            assert(initializer->sub_icode.size()==1);
            icode* const_list = initializer->sub_icode[0];
            initializer->sub_icode.clear();
            initializer->m_type=ICODE_TYPE_CONST_LIST;
            const_list_to_flat2(initializer,const_list, var->m_in_ptr_type,1, var->is_array);
            initializer->const_refresh_width();
            int const_array_bit_width = initializer->m_bit_width;

            /// 大小去除。如果初始化数据太多，则去除。如果太少，则补0
            while(const_array_bit_width>target_total_bit_width)
            {
                initializer->sub_icode.pop_back();
                initializer->const_refresh_width();
                const_array_bit_width = initializer->m_bit_width;
            }

            while(const_array_bit_width<target_total_bit_width)
            {
                icode *nic = new_icode(ICODE_TYPE_I_CONST);
                nic->m_bit_width = 8;
                nic->num = 0;
                initializer->sub_icode.push_back(nic);
                initializer->const_refresh_width();
                const_array_bit_width = initializer->m_bit_width;
            }
        }


#if 0
        if(initializer->m_type==ICODE_TYPE_CONST_LIST)
        {
            int total_bit_width=0;
            for(unsigned i=0;i<initializer->sub_icode.size();++i)
            {
                assert(initializer->sub_icode[i]->m_type==ICODE_TYPE_I_CONST);
                initializer->sub_icode[i]->m_bit_width = var->m_in_ptr_type->m_bit_width;
                total_bit_width+=initializer->sub_icode[i]->m_bit_width;
            }

            int target_total_bit_width = var->get_array_bit_width();
            if(target_total_bit_width==0)
            {
                /// 数组通过初始值确定大小
                /// int a[]={1,2,5,3,4};
                /// int a[5][]={1,2,5,3,4};

                var->set_array_bit_width(total_bit_width);
                target_total_bit_width = var->get_array_bit_width();
            }
            if(total_bit_width>target_total_bit_width)
            {
                cout<<"WARNING: data truncated. " <<*var <<" init data too more. just truncated the last\n";
                int comp_cnt = target_total_bit_width/var->m_in_ptr_type->m_bit_width;
                initializer->sub_icode.resize(comp_cnt);
            }
            else if(total_bit_width<target_total_bit_width)
            {
                //数据补0
                int left_bit = target_total_bit_width-total_bit_width;
                int left_comp = left_bit / var->m_in_ptr_type->m_bit_width;
                for(unsigned i=0;i<left_comp;++i)
                {
                    icode * icn = new_icode(ICODE_TYPE_I_CONST);
                    initializer->sub_icode.push_back(icn);
                    icn->num = 0;
                    icn->m_bit_width = var->m_in_ptr_type->m_bit_width;
                }
            }
            initializer->m_bit_width = target_total_bit_width;
        }

#endif

       else  if((initializer->m_type==ICODE_TYPE_CONST_STRING)||
            ((initializer->m_type==ICODE_TYPE_SYMBOL_REF)&&(initializer->result->m_type==ICODE_TYPE_CONST_STRING))
            )
        {
            if(initializer->m_type==ICODE_TYPE_SYMBOL_REF)
            {
                initializer = initializer->result;
            }


            ///如果是字符串，则只能给char 或者 unsigned char 数组赋值
            int total_bit_width=0;
            total_bit_width = (initializer->name.size()+1)*8;
            int target_total_bit_width = var->get_array_bit_width();
            if(target_total_bit_width==0)
            {
                /// 数组通过初始值确定大小
                /// int a[]={1,2,5,3,4};
                /// int a[5][]={1,2,5,3,4};

                var->set_array_bit_width(total_bit_width);
                target_total_bit_width = var->get_array_bit_width();
            }
            if(total_bit_width>target_total_bit_width)
            {
                cout<<"WARNING: data truncated. " <<*var <<" init data too more. just truncated the last\n";
                int comp_cnt = target_total_bit_width/var->m_in_ptr_type->m_bit_width;
                initializer->name.resize(comp_cnt);
            }
            else if(total_bit_width<target_total_bit_width)
            {
                //数据补0
                initializer->name.resize( target_total_bit_width/8);
                initializer->m_bit_width = target_total_bit_width;
            }
        }
        else
        {
            assert(0);
        }

    }
    else  if(var->is_array==0)
    {
        if((var->is_sbit)||
                (var->is_sfr)||
                (var->is_sfr16)||
                (var->is_sfr32))
        {
            //特殊功能寄存器，初始值是特殊的，此处不做bit_width限定！！！
            return 0;
        }

        if(initializer->m_type==ICODE_TYPE_SCOPE)
        {
            icode *const_list = initializer->sub_icode[0];
            initializer->sub_icode.clear();
            initializer->m_type=ICODE_TYPE_CONST_LIST;
            const_list_to_flat2(initializer,const_list, var,1, var->is_array);
            initializer->const_refresh_width();
        }


        if(initializer->m_bit_width > var->m_bit_width)
        {
            cout<<"WARNING: data truncated:"<<*var<<"init data:"<< *initializer<<"bit change from:"<< initializer->m_bit_width<<". to:"<< var->m_bit_width<< "\n";
        }
        initializer->m_bit_width = var->m_bit_width;
    }





    return 0;
}




///         curr->merge_icode(ret);
icode* comp_context::release_tmp_if_need(icode *c)
{

    icode * a = new_icode();
    a->m_type = ICODE_TYPE_BLOCK;

    //不再通过此函数进行变量释放。而是后期通过代码分析进行变量处理

    return a;
}

icode * comp_context::new_copy_icode_gen(icode *from, icode *to)
{
    return m_top_icodes->new_copy_icode_gen(from, to);

}


icode *comp_context::new_temp_ptr_var(icode *in_ptr_type)
{
    return m_top_icodes->new_temp_ptr_var(in_ptr_type);

}

icode *comp_context::mov_icode(icode *left, icode *result)
{
    return new_copy_icode_gen(left, result);
}



icode *comp_context::new_var_in_var_icode(icode *to_ref)
{

    return m_top_icodes->new_var_in_var_icode(to_ref);
}



icode* comp_context::ast_to_icode_a_op_b(token_defs *tdefs, bool need_result_icode, icode *ret, icode *result_ic)
{
    icode *a = ret;

    assert(tdefs->m_tk_elems.size()==3);
    //additive_expression '+' multiplicative_expression
    //additive_expression '-' multiplicative_expression

    //multiplicative_expression '*' cast_expression
    //multiplicative_expression '/' cast_expression
    //multiplicative_expression '%' cast_expression


    token_defs *additive_expression = tdefs->m_tk_elems[0];
    token_defs *opr = tdefs->m_tk_elems[1];
    token_defs *multiplicative_expression = tdefs->m_tk_elems[2];
    icode *b = new_icode();
    b->m_type = ICODE_TYPE_EXP_OP;
    b->name = opr->val_str;

    icode *c = ast_to_icode(additive_expression, 1);
    icode *d = ast_to_icode(multiplicative_expression, 1);

    a->merge_icode(c);
    a->merge_icode(d);


    b->left = c->result;
    b->right = d->result;

    if(need_result_icode)
    {
        if(result_ic==NULL)
        {
            b->result=0;
            icode *e = new_temp_var();
            a->merge_icode(e);

            icode *e_ref = new_ref_icode(e);
            b->result = e_ref;
            a->result = e_ref;

            ///TODO: 优化：1bit 2020.6.30 此处需要区分是关系运算符，还是算术运算符。如关系运算符，返回值只需要1bit数值
            //此处需要区分是关系运算符，还是算术运算符。
            // 算术运算符没有问题，关系运算符，返回值只需要1bit数值
            // eg: 1+2 ==>3
            // eg: 1<2 --> 1

            if((opr->val_str==">")||
                    (opr->val_str=="<")||
                    (opr->val_str==">=")||
                    (opr->val_str=="<=")||
                    (opr->val_str=="==")||
                    (opr->val_str=="!=")
                    )
            {
                ///比较的运算结果，默认为8bit无符号
                e->m_bit_width = 8;
                e->is_signed = 0;
                e->is_float32 = 0;
            }
            else
            {
                e->set_width_from(c->result);
                e->set_width_from(d->result);
            }
        }
        else
        {
            b->result = new_ref_icode(result_ic);
            a->result = b->result;
        }
    }
    a->merge_icode(b);
    return a;
}



icode *comp_context::new_jmp_icode(icode *labeled_block,ICODE_TYPE label_start_end_ref)
{
    icode *jmp_code= new_icode();

    jmp_code->m_type = ICODE_TYPE_EXP_OP;
    jmp_code->name = "JMP";//跳转指令

    //跳转到icb1的起始位置,重新判断表达式的值
    jmp_code->result = new_icode();
    jmp_code->result->m_type = label_start_end_ref ;
    jmp_code->result->result = labeled_block;
    return jmp_code;
}

icode *comp_context::new_jnz_icode(icode *result, icode *labeled_block, std::string jz_str, ICODE_TYPE label_start_end_ref)
{
    icode * jmp_code = new_icode();
    jmp_code->m_type = ICODE_TYPE_EXP_OP;
    jmp_code->name = jz_str;//非零跳转指令


    ///要判断的值
    jmp_code->left = result;

    //非零，跳转到icb1的起始位置
    jmp_code->result = new_icode();
    jmp_code->result->m_type = label_start_end_ref;
    jmp_code->result->result = labeled_block;
    return jmp_code;
}


std::string comp_context::token_to_tree(token_defs *tdefs)
{
    std::map<int, std::string> m_ast_type;
    std::map<int, std::string> m_elem_type;

    for(int i=0;i<g_ast_debug_str.size();++i)
    {
        m_ast_type[g_ast_debug_str[i].m_type] = g_ast_debug_str[i].m_name;
    }
    for(int i=0;i<g_elem_debug_str.size();++i)
    {
        m_elem_type[g_elem_debug_str[i].m_type] = g_elem_debug_str[i].m_name;
    }





    std::stringstream ss;
    if(tdefs==NULL){ return "";}
    if((tdefs->m_type==TOKEN_DEFS_TYPE_AST)||(tdefs->m_tk_type_int_list.size()>0))
    {
        //return ast_to_icode_ast(tdefs, need_result_icode, result_ic);
        int top_type=tdefs->m_tk_type_int;
        if(tdefs->m_tk_type_int_list.size()>0)
        {
            top_type=tdefs->m_tk_type_int_list[tdefs->m_tk_type_int_list.size()-1];
            tdefs->m_tk_type_int_list.pop_back();
        }
        /// 此处显示字符串
        ///
        /// top_type
        ss<<m_ast_type[top_type]<<"\n";


        if((tdefs->m_type==TOKEN_DEFS_TYPE_AST)&&
                (tdefs->m_tk_type_int_list.size()==0)&&
                (tdefs->m_tk_elems.size()==0)
                )
        {//ast 已经处理完成
            return ss.str();
        }

        /// 处理子类字符串
        ///
        if(tdefs->m_tk_type_int_list.size()>0)//(tdefs->m_tk_elems.size()==0)
        {
            ss<< token_to_tree(tdefs);
        }
        else  if(tdefs->m_type==TOKEN_DEFS_TYPE_ELEM)
        {
            ss<< token_to_tree(tdefs);
        }
        else
        {
            ss<<"-\n";
            for(int i=0;i<tdefs->m_tk_elems.size();++i)
            {
                ss<< token_to_tree(tdefs->m_tk_elems[i]);
            }
        }
    }
    else if(tdefs->m_type==TOKEN_DEFS_TYPE_ELEM)
    {
        //return ast_to_icode_elem(tdefs, need_result_icode, result_ic);
        //tdefs->m_token_type
        ss<<m_elem_type[tdefs->m_token_type]<<"("<< tdefs->val_str<<")" <<"\n";
        ss<<"=\n";
    }
    else
    {
        assert(0);
    }



    return ss.str();
}



}


