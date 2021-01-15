# MZC8051

https://jiangshan00001.github.io/

![Build Status](https://github.com/Jiangshan00001/MZC8051/workflows/mzc8051_ubuntu_build/badge.svg)


a c compiler for mcu8051.



代码说明：

- asm8051: 8051的asm到hex的汇编编译器。
- ir/irread: 定义的中间语言。中间语言的读写。
- cfront: c语言的前端。
- backend/ir2asm8051 ir转为8051汇编语言的后端代码。
- misc 其他公共函数等。
- lmake 简单的make的部分功能实现，用于生成项目和编译程序用。
- sim8051 8051的仿真代码，用于测试验证生成的hex代码运行功能是否正确。
- ide_one 总体编译器统一集成编译项目。
- 希望对编译器技术感兴趣的人一起讨论学习。
- 可以在项目的issues中讨论。

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

some code is from internet:

- json lib is from:https://github.com/nlohmann/json
- sim8051 is mostly from: https://github.com/andersdellien/8051-sim
- simplecpp: https://github.com/danmar/simplecpp
if there is any license issue, please contact me.


