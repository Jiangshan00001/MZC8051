CTOOL=/d/tsdx/compiler/editor8051_v2/build/yacc_to_front_code.exe

all:
	$(CTOOL) -t test parser_no_code.yy  parser_test.yy NS_IR2ICODE
	$(CTOOL) -t yy_with_code parser_no_code.yy  parser_tmp.yy NS_IR2ICODE
	$(CTOOL) -t cpp_switch parser_no_code.yy  comp_context_gen_tmp.cpp NS_IR2ICODE
	$(CTOOL) -t cpp_func parser_no_code.yy  comp_context_gen_funcs_tmp.cpp NS_IR2ICODE
	$(CTOOL) -t defh parser_no_code.yy  comp_context_gen_defs_tmp.h NS_IR2ICODE
	$(CTOOL) -t dot parser_no_code.yy  parser_no_code.dot NS_IR2ICODE
	$(CTOOL) -t debug_list parser_no_code.yy  comp_context_yy_debug.tmp NS_IR2ICODE
	
	
clean:
	rm -rf parser_test.yy parser_tmp.yy comp_context_gen_tmp.cpp comp_context_gen_funcs_tmp.cpp comp_context_gen_defs_tmp.h parser_no_code.dot
