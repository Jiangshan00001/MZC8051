CTOOL=/d/tsdx/compiler/editor8051_v2/build/yacc_to_front_code.exe
LEXPP=/d/tsdx/compiler/editor8051_v2/build/lexpp.exe
all:
	$(CTOOL) -t test parser_no_code.yy  parser_test.yy NS_AMS8051HEX
	$(CTOOL) -t yy_with_code parser_no_code.yy  parser.yy NS_AMS8051HEX
	$(CTOOL) -t cpp_switch parser_no_code.yy  comp_context_gen.cpp NS_AMS8051HEX
	$(CTOOL) -t cpp_func parser_no_code.yy  comp_context_gen_funcs_tmp.cpp NS_AMS8051HEX
	$(CTOOL) -t defh parser_no_code.yy  comp_context_gen_defs.h NS_AMS8051HEX
	$(CTOOL) -t dot parser_no_code.yy  parser_no_code.dot NS_AMS8051HEX
	$(CTOOL) -t debug_list parser_no_code.yy  comp_context_yy_debug.tmp NS_AMS8051HEX
	$(LEXPP) -t test scanner_no_code.ll  scanner_test.ll NS_AMS8051HEX
	$(LEXPP) -t lex scanner_no_code.ll  scanner.ll NS_AMS8051HEX
clean:
	rm -rf parser_test.yy parser_tmp.yy comp_context_gen_tmp.cpp comp_context_gen_funcs_tmp.cpp comp_context_gen_defs_tmp.h parser_no_code.dot  comp_context_yy_debug.tmp scanner_test.ll 