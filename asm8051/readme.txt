一个8051单片机的汇编器/反汇编器。

代码生产工具：
yacc_to_front_code: yy_no_code-->parser.yy comp_context_gen
								comp_context_gen_defs comp_context_yy_debug
lexpp: scanner_no_code --> scanner.ll
asm_csv_to_code: dis_list.csv  asm_list.csv--> cmd_list.txt operand_list.txt
				dis_list.csv operand_list.csv -->	dis_funcs.cpp/h

v4
添加asm和hex接口


v3:
可以生成yy文字，说明解析asm文本正常。
 ../../../build/asm8051/asm8051.exe -yy -d asm_test1.a51 asm_test1_yy.a51
下一步计划添加实际生成hex的文字。





此处记录下汇编器的生成过程，以便生成其他汇编器时仿照。

1 预处理：去除注释，替换部分宏定义。--手写
2 词法分析，语法分析。--flex+bison
3 对应汇编代码生成。---
4 生成指定格式：hex格式。---手写代码



1 添加域名空间： NS_AMS8051HEX
2 添加文件token_defs。修改其中的命名空间为 NS_AMS8051HEX
3 scanner.ll 
	修改命名空间为：NS_AMS8051HEX。 
	scanner基类名称：ASMFlexLexer
3 修改parser.ll 
	命名空间：NS_AMS8051HEX
	%name-prefix="NS_AMS8051HEX"
	%define "parser_class_name" "Parser" 类名
4 添加lex_yacc_adapt
	driver.cpp/h
	scanner.cpp/h
	修改命名空间：NS_AMS8051HEX
	
	
	
	








this is a 8051 


=====================
编译流程：

源程序-->预处理（去除注释，拆分单词,组合指令）-(dbg1)->
			第一遍处理(处理宏定义，生成指令，生成标签列表)-(dbg2)->标签添加(各地址指令里，标签替换)-(dbg3)->第二遍处理(重新生成地址相关指令)-(dbg4)->hex文件







TODO:

汇编器中加入链接功能：
    支持多个汇编文件输入，生成hex
        .global FUNC1 VAR1 VAR2 VAR3

        FUNC1: label1
        VAR1 xdata 20H
        VAR2 data 20H
        VAR3 idata 20H


        .extern TEST1


        .code
        ORG 100H
        sjmp $



    支持通过#line 获取位置信息，用于出错时的显示----XXX
    对于大小写的支持。标号大小写不转换为全大写，而是大小写敏感






测试自动化  -make--XXX
不支持的语法：
1 c语言的多行注释： /**/
2 $的运算 sjmp $+4---XXX
3 PUSH/POP AR5 AR4 AR7







===================================================
如何添加新的指令 USING 0
1 scanner.ll中添加
"USING" {TOKEN_DEFAULT_AC( token::TK_MACRO,1,0);}
"SHL"   { TOKEN_DEFAULT_AC( token::TK_SHL,1,0);}
"MOD"   { TOKEN_DEFAULT_AC( token::TK_MOD,1,0);}
2 parser.yy中添加 TK_SHL  TK_MOD

3 parser.yy中添加解析规则
TK_SHL 和 TK_MOD 都放在 not_expr中即可
| expr_elem TK_MOD expr_elem {
		$$.type=TOKEN_PARENT;
		$$.child_type=TOKEN_OPR;
		$$.val_str= $1.val_str +" MOD " + $3.val_str;
		$1.type=TOKEN_OPR;
		$$.m_childs.push_back($1);
		$$.m_childs.push_back($2);
		$$.m_childs.push_back($3);
		$$.m_resolved=0;
	}

4 
T_ASM_CONTEXT::eval_token 函数中，添加  SHL MOD 两个算符的实现
USING 在宏定义中实现 m_line_macro_ptr
DB 在指令中实现 m_line_key_word_ptr

===================================================
历史记录：

2020.7.15
disassmble中m3.csv的错误修正：
MOV data addr data addr. 应该是 机器码：mov src dst。 人工汇编代码：mov dst, src


2020.7.9
添加编译完成后，对于resolved=0的参数的检查。




2020.7.6
添加范围检查
每个参数的范围
问题：SJMP中负数范围如何检查。当前使用(0xff &val)!=val 来判断。只能判断正数，不能判断负数？？？？


2020.7.1
stc_hc595.a51 文件编译不通过。
需要添加的指令：
USING   0
DB
SHL
MOD



2020.6.4
bug:stc8a_test5.a51编译不通过，错误是因为 NOT指令 # not 40H


2020.6.3
代码：
ORG 0000H
UART_ISR:
	JNB	TI,CHKRI
	
CHKRI:
	CLR	TI

编译不通过，原因是TI, CHKRI两个变量没有替换？？？？？


2020.6.3
MOV的汇编，mov dest, src 还是mov src, dst???
keil中注释，机器码为：mov src, dst
8051-inst-doc0509中，机器码为mov dst src
怀疑是keil文档写错了
查询stc15.pdf文档，发现是 mov src dst
怀疑是atmel文档写错。
keil中生成的机器码也为： mov src dst
所以改为和keil一致



2020.6.2

暂时无法解析指令：
MOV     R3, #HIGH (Fosc_KHZ / 13)
其中： Fosc_KHZ    EQU 11059


无法解析指令：
Fosc_KHZ    EQU 11059   ;11059KHZ
TIMER0_RELOAD   EQU     (65536 - FOSC_KHZ)  EQU need exactly 3 tokens. not5.

无法解析指令：
LED8            DATA    30H     ;   显示缓冲 30H ~ 37H
MOV     LED8+1, B



无法解析指令：
DB  0BFH,086H,0DBH,0CFH,0E6H,0EDH,0FDH,087H,0FFH,0EFH,046H

无法解析指令：
USING   0       ;选择第0组R0~R7

TODO:
1 需要一个词法分析工具。
  输入字符串，输出token.
2 词法分析工具出来的表达式，要先求值，再计算






2020.6.2
针对
LOOP:JMP LOOP
语句，添加 JMP的新语法，使用复制sjmp loop
语句，添加CALL的新语法， 使用复制acall loop

ANL     A,#NOT 40H 语句的支持 #中添加not算符的支持
对二进制数字#10000010B 的支持 ->82 不时8A


2020.6.1
JMP LOOP 编译错误
MOV	DPTR,#BGV 编译错误。 BGV	EQU	0FDF7H

2020.6.1

原始文档：
8051-inst-doc0509.pdf
8051-inst-doc0509.docx

m1.csv 指令名称列表 44个
m2.csv 指令名称和对应的操作符注释
m2_add_calc.csv 将m2.csv通过手工添加的计算公式，用于生成机器码



2020.5.31
使用stc的汇编例程代码。
1 将反汇编改为正常显示
2 将汇编通过预处理的方式，改为正常编译
3 将反汇编，添加定义的方式，替换内部的寄存器名字




2020.5.13
MOV的汇编，mov dest, src 还是mov src, dst???
keil中注释，机器码为：mov src, dst
8051-inst-doc0509中，机器码为mov dst src
怀疑是keil文档写错了

2020.5.13
BUGFIX
对于部分指令，dis不对的问题

2020.4.7

label系统完成
所有指令翻译对照完成
FIXME: label是keyword，所以跳转只能用label，不能使用数字地址
TODO: cc500


2020.4.5
1 添加代码自动生成--根据m2添加公式后。

TODO:
1 添加label系统。在每行处理时，如果发现有label, 则追加一个text_block单独用于label.
2 添加define宏定义
3 添加EQU 宏定义？？？
4 添加DS DBIT定义？
5 添加 SEGMENT定义？？？
6 移植8cc到此处...
7 移植编辑器textadept
8 网站推广
9 年付费？？？








1 试用pdcurses（textadept补丁可加？） 生成编辑器???





1 解码if（）后面的数字，改为TOKEN_等定义字符串
2 添加人工解码函数，人工代码和自动生成的类型检查代码分离
3 c语言移植 c88
