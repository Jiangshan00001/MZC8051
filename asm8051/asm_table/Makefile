CSV_TO_CODE=/d/tsdx/compiler/editor8051_v2/build/asm_csv_to_code.exe
all:
	$(CSV_TO_CODE) -t csv dis_list.csv  asm_list.csv cmd_list.txt operand_list.txt
	$(CSV_TO_CODE) -t dis dis_list.csv  operand_list.csv dis_funcs.cpp dis_funcs.h NS_AMS8051HEX
	cp dis_funcs.cpp ../src/;
	cp dis_funcs.h ../src/;
	$(CSV_TO_CODE) -t asm asm_list.csv  operand_list.csv asm_funcs.cpp asm_funcs.h NS_AMS8051HEX
	cp asm_funcs.cpp ../src/;
	cp asm_funcs.h ../src/;	
clean:
	rm -rf cmd_list.txt asm_list.txt