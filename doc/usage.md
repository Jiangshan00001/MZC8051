

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