
如何使用lmake集成命令，实现项目代码编译执行？

```shell
在windows系统下；
打开一个命令行窗口（开始-运行-输入cmd后回车）。
进入当前目录：cd 当前路径。

创建工程：
./MZC8051.exe -x lmake -m create -i . -o project_name

编译工程：
cd project_name;
../MZC8051.exe -x lmake -i . -m make

清理工程：
../MZC8051.exe -x lmake -i . -m clean

添加代码：
默认代码在main.c中。
通过修改Makefile中的SRC_C变量可以添加或删除源文件。

-------------------------------
how to use?
in windows. 
open cmd.
cd to $this directiory$.

create a project:
./MZC8051.exe -x lmake -m create -i . -o project_name

make project:
cd project_name;
../MZC8051.exe -x lmake -i . -m make

clean project:
../MZC8051.exe -x lmake -i . -m clean

add code:
default code is in main.c.
this could be changed from modifying SRC_C var in Makefile.


```


如何使用单独命令，实现代码编译？

```shell

测试： test_add1.c: #include "_simtrap.h" void main() { char a=1; char b=1; char c; c=a+b; _sim_assert(c==2); _sim_exit(); }
预处理：
../../release/v2.1/MZC8051.exe -x cpp -i test_add1.c -o test_add1.c2 -I ../../release/v2.1/inc/c8051/ -D MZC8051V21
c语言转为ir语言：
../../release/v2.1/MZC8051.exe -x c2ir -i test_add1.c2 -o test_add1.ir
ir语言转为asm汇编：
../../release/v2.1/MZC8051.exe -x ir2asm8051 -i test_add1.ir -I ../../release/v2.1/inc/c8051/ -D MZC8051V21 -o test_add1.asm
asm汇编转为hex：
../../release/v2.1/MZC8051.exe -x asm8051 -i test_add1.asm -o test_add1.hex
hex仿真执行：
../../release/v2.1/MZC8051.exe -x sim8051 -i test_add1.hex > test_add1.ret
hex反汇编：
../../release/v2.1/MZC8051.exe -x dis8051 -i test_add1.hex -o test_add1.dis

```



