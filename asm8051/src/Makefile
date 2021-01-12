BUILD_DIR=../../../build/asm8051/
PROG=$(BUILD_DIR)asm8051.exe
PROG_LIB=$(BUILD_DIR)asm8051.a

IMPORT_LIB=$(BUILD_DIR)../misc/misc.a

SRCS_ASM8051_LIB= asm8051.cpp asm8051_lex.cpp asm_context.cpp \
            asm_keywords.cpp  asm_table.cpp asm_token.cpp dis8051.cpp \
            dis_keywords.cpp hex_generator.cpp \
             text_block.cpp  api/asm8051_api.cpp  asm_extend_keywords.cpp asm_macro_keywords.cpp

SRCS_COMMON= 

SRCS_LEXYACC= lex_yacc/parser.cpp lex_yacc/scanner.cpp  lex_yacc/driver.cpp

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

INCS = -I$(CURR_DIR)  -I$(CURR_DIR)/lex_yacc/   -I$(CURR_DIR)/../../misc/util/ -I$(CURR_DIR)/api/


all:  $(BUILD_PATH) $(PROG_LIB)  $(PROG)
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
