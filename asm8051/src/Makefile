BUILD_DIR=../../../build/asm8051/
PROG=$(BUILD_DIR)asm8051.exe
PROG_LIB=$(BUILD_DIR)asm8051.a

IMPORT_LIB=$(BUILD_DIR)../misc/misc.a

SRCS_ASM8051_LIB= asm_to.cpp to_asm.cpp \
			hex_generator.cpp dis_funcs.cpp asm_funcs.cpp text_block.cpp\
			asmc51_predefined_symbol.cpp  bit_addr_parse.cpp asm_extend_jmp.cpp\
            api/asm8051_api.cpp  context/comp_context.cpp context/icode.cpp

SRCS_COMMON= 

SRCS_LEXYACC= lex_yacc/parser.cpp lex_yacc/scanner.cpp  lex_yacc_adapt/driver.cpp \
            lex_yacc_adapt/token_defs.cpp  lex_yacc_adapt/comp_context_yy_debug.cpp \
			lex_yacc/ly/comp_context_gen.cpp lex_yacc/ly/comp_context_gen_funcs.cpp \
			lex_yacc/ly/comp_context_gen_funcs_token.cpp

SRCS_MAIN=main_console.cpp



SRCS=  $(SRCS_LEXYACC) $(SRCS_ASM8051_LIB) $(SRCS_COMMON)   $(SRCS_MAIN)
PROG_LIB_OBJS=$(addprefix $(BUILD_DIR), $(SRCS_LEXYACC:.cpp=.o) ) $(addprefix $(BUILD_DIR), $(SRCS_ASM8051_LIB:.cpp=.o) )
OBJS=$(addprefix $(BUILD_DIR), $(SRCS:.cpp=.o) )
BUILD_PATHTMP=$(dir $(abspath $(OBJS))) 
BUILD_PATH=$(sort $(BUILD_PATHTMP))


CURR_DIR=$(shell pwd)
CC=gcc
CXX=g++
CXX_FLAGS:= -g -Wall  -fpermissive -O0
AR=ar
STRIP=strip

INCS = -I$(CURR_DIR)  -I$(CURR_DIR)/context/  -I$(CURR_DIR)/lex_yacc/  -I$(CURR_DIR)/lex_yacc/ly/  -I$(CURR_DIR)/lex_yacc_adapt/   -I$(CURR_DIR)/../../misc/util/ -I$(CURR_DIR)/api/ -I/include/


all:  $(BUILD_PATH) $(PROG_LIB)  $(PROG)
	make -C lex_yacc
	echo "finish!"

$(BUILD_PATH):
	mkdir -p $(BUILD_PATH)

$(SRCS_LEXYACC):
	make -C lex_yacc

$(PROG): $(OBJS)
	$(CXX) -static -g $^  $(IMPORT_LIB)  -o $@
	#$(STRIP) $@

$(PROG_LIB):$(PROG_LIB_OBJS)
	$(AR) -rcs $@ $^

$(BUILD_DIR)%.o:%.c
	$(CC) $(INCS) $(CXX_FLAGS) -c $< -o $@
	
$(BUILD_DIR)%.o:%.cc
	$(CXX) $(INCS) $(CXX_FLAGS) -c $< -o $@

$(BUILD_DIR)%.o:%.cpp
	$(CXX) $(INCS) $(CXX_FLAGS) -c $< -o $@


CXX_FLAGS += -MMD -MP
#CC_FLAGS = $(CXX_FLAGS) -MMD -MP
-include $(OBJS:.o=.d)


.PHONY: clean all 
clean:
	rm -rf $(OBJS) $(PROG_LIB) $(PROG)
	make -C lex_yacc clean
