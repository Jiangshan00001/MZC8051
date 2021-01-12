# MZC8051
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




some code is from internet:

- json lib is from:https://github.com/nlohmann/json
- sim8051 is mostly from: https://github.com/andersdellien/8051-sim

if there is any license issue, please contact me.


