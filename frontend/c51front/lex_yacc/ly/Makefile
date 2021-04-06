CTOOL=/d/tsdx/compiler/editor8051_v2/build/yacc_to_front_code.exe

all:
	$(CTOOL) -t test parser_no_code.yy  parser_test.yy NS_C512IR
	$(CTOOL) -t yy_with_code parser_no_code.yy  parser_tmp.yy NS_C512IR
	$(CTOOL) -t cpp_switch parser_no_code.yy  comp_context_gen_tmp.cpp NS_C512IR
	$(CTOOL) -t cpp_func parser_no_code.yy  comp_context_gen_funcs_tmp.cpp NS_C512IR
	$(CTOOL) -t defh parser_no_code.yy  comp_context_gen_defs_tmp.h NS_C512IR
	$(CTOOL) -t dot parser_no_code.yy  parser_no_code.dot NS_C512IR
	$(CTOOL) -t debug_list parser_no_code.yy  comp_context_yy_debug.tmp NS_C512IR
	
clean:
	rm -rf parser_test.yy parser_tmp.yy comp_context_gen_tmp.cpp comp_context_gen_funcs_tmp.cpp comp_context_gen_defs_tmp.h parser_no_code.dot  comp_context_yy_debug.tmp