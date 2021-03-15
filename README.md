# MZC8051

https://jiangshan00001.github.io/

![Build Status](https://github.com/Jiangshan00001/MZC8051/workflows/mzc8051_ubuntu_build/badge.svg)


a c compiler for mcu8051.



示例程序：


```
void main()
{
int a=4;
}

```


生成对应的ir

```
func:$main;
	ret_type: $__main_ret,u0;
	{:
def_var: $a,i16;
opr: "init", null;, iconst:0x4:0x10;, %a;
};
func_end:%main;


```

生成对应的8051asm:
```
ORG 0000H; program entry
LJMP __main_before;
__main_before:
MOV 0x81, #0x7f; sp<-#0x7f
NOP;
NOP;
NOP;
LCALL _func___init_global_var;
LJMP _func_main;
_func___init_global_var:
_func___init_global_var_ret_LABEL:
RET;
_func_main:
;def_var: $a,i16;
;addr: 0x8
;opr: "init", null;, iconst:0x4:0x8;, %a;

MOV 0x8, #0x4;
MOV 0x9, #0x0;
_func_main_ret_LABEL:
RET;
```


生成对应的hex:
```
:1000000002000375817F00000012000F0200102221
:0700100075080475090022C8
:00000001FF
```





欢迎任何人参与和完善：一个人可以走的很快，但是一群人却可以走的更远。


## 程序使用说明：

当前有3个例程在release中：
example_test: led01 led02 shumaguan01

[程序使用说明](doc/usage.md)




## 源码说明：

名称 | 说明 | 当前状态
--|--|--
[asm8051](doc/asm8051.md) | 8051的asm到hex的汇编编译器 | ✅ 
[ir/irread](doc/ir.md) | 定义的中间语言。中间语言的读写 |🕗 
[cfront](doc/cfront.md) | c语言的前端 | 🕗 
[backend/ir2asm8051](doc/ir2asm8051.md) | ir转为8051汇编语言的后端代码 | 🕗 
[sim8051](doc/sim8051.md) | 8051的仿真代码，用于测试验证生成的hex代码运行功能是否正确 | ✅  
[lmake](doc/lmake.md) | 简单的make的部分功能实现，用于生成项目和编译程序用 | ❌ 
[ide_one](doc/ide_one.md) | 总体编译器统一集成编译项目 | ✅  
[misc](doc/misc.md) | 其他公共函数等 | ✅  


 希望对编译器技术感兴趣的人一起讨论学习。
 可以在项目的issues中讨论。

## 开发说明：

- [ir格式说明](doc/ir_format.md)
- [如何添加新的前端](doc/add_new_front_how_to.md)
- [如何添加新的后端](doc/add_new_backend_how_to.md)
- [如何添加新的中间代码过滤器](doc/add_new_filter_how_to.md)


some code is from github:

- json: https://github.com/nlohmann/json
- sim8051: https://github.com/andersdellien/8051-sim
- simplecpp: https://github.com/danmar/simplecpp

if there is any license issue, please contact me.





# 需要的帮助
- 在github项目上点赞和fork
- 对项目方向代码结构等方面提出各种问题
- 编译器使用者：测试并提交异常问题或正常通过的例程代码
- 编译器开发/爱好者：添加项目文档，添加前端/后端代码
- 芯片开发/爱好者：添加新的前端/后端代码，运行时库代码
- 其他：提供使用或者特定开发需求，提供资金支持






some resource I find useful:
-   LCC: A Retargetable C Compiler: Design and Implementation
    http://www.amazon.com/dp/0805316701,
    https://github.com/drh/lcc

-   TCC: Tiny C Compiler
    http://bellard.org/tcc/,
    http://repo.or.cz/w/tinycc.git/tree

-   C99 standard final draft
    http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1124.pdf

-   C11 standard final draft
    http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf

-   Dave Prosser's C Preprocessing Algorithm
    http://www.spinellis.gr/blog/20060626/

-   The x86-64 ABI
    http://www.x86-64.org/documentation/abi.pdf
