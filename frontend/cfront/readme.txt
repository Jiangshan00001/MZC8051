2020.12.18
c8051->c8051_v1
c8051_v3->c8051



2020.12.18
添加c8051到此例程中
1 修改命名空间为NS_C2IR
2 修改lex yacc的解析文件为c语言的语法
3 修改lex，token_defs 添加对应的参数支持
4 修改yacc文件，funcs文件，添加icode库。
5 






2020.12.17
v3和v2的区别是，v2的命名空间是example,v3的是exampleA

命名空间修改：
1 ly:Makefile: 后面的example 改为exampleA
  make
  比较并更新comp_context_gen.cpp comp_context_gen_defs.h comp_context_gen_funcs.cpp 3个文件。
2 parser.yy: /* namespace to enclose parser in */ %name-prefix="exampleA"
	#define YYSTYPE exampleA::token_defs
3 scanner.ll 后面代码中的命名空间修改
4 comp_context.h/cpp token_defs.h/cpp 修改命名空间
5 lex_yacc_adapt/scanner.h  driver.h/cpp 修改命名空间


----------
此处为flex bison在cpp环境下的使用示例
原文在：
https://github.com/bingmann/flex-bison-cpp-example/




--------------------------
如何从yy l 文件生成代码


--------------------------


使用说明:

如何修改example的命名空间？

	scanner.h example->替换
	driver.h  example->替换
	driver.cpp example->替换
	parser.yy  example-> 修改两个地方：
		%name-prefix="example"
		void example::Parser::error(const Parser::location_type& l,
					const std::string& m)

	scanner.ll 修改：
		4处地方
		
	注意：
		scanner中，系统默认生成的类在scanner.h中被重命名为exampleFlexLexer
		需要修改名字，避免多个同时使用时冲突
		
		
	主函数：exprtest.cpp
		
		
		
如何修改yystype返回值？
    去掉%union
	#define YYSTYPE token_defs
	其中token_defs为一个类

		
如何添加/修改lex yacc的规则？
	
