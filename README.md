# MZC8051

https://jiangshan00001.github.io/

![Build Status](https://github.com/Jiangshan00001/MZC8051/workflows/mzc8051_ubuntu_build/badge.svg)


a c compiler for mcu8051.

欢迎任何人参与和完善：一个人可以走的很快，但是一群人却可以走的更远。


源码说明：

- [asm8051: 8051的asm到hex的汇编编译器](doc/asm8051.md)
- [ir/irread: 定义的中间语言。中间语言的读写](doc/ir.md)
- [cfront: c语言的前端](doc/cfront.md)
- [backend/ir2asm8051 ir转为8051汇编语言的后端代码](doc/ir2asm8051.md)
- [misc 其他公共函数等](doc/misc.md)
- [lmake 简单的make的部分功能实现，用于生成项目和编译程序用](doc/lmake.md)
- [sim8051 8051的仿真代码，用于测试验证生成的hex代码运行功能是否正确](doc/sim8051.md)
- [ide_one 总体编译器统一集成编译项目](doc/ide_one.md)
- 希望对编译器技术感兴趣的人一起讨论学习。
- 可以在项目的issues中讨论。

[使用说明](doc/usage.md)



some code is from github:

- json lib is from:https://github.com/nlohmann/json
- sim8051 is mostly from: https://github.com/andersdellien/8051-sim
- simplecpp: https://github.com/danmar/simplecpp

if there is any license issue, please contact me.


