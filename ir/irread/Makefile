PROG_NAME=irread
BUILD_DIR=../../../build/$(PROG_NAME)/
PROG=$(BUILD_DIR)$(PROG_NAME).exe
PROG_LIB=$(BUILD_DIR)$(PROG_NAME).a

IMPORT_LIB =$(BUILD_DIR)../misc/misc.a

SRCS_LEXYACC= lex_yacc/parser.cpp lex_yacc/scanner.cpp  lex_yacc/ly/comp_context_gen.cpp   lex_yacc/ly/comp_context_gen_funcs.cpp	lex_yacc_adapt/driver.cpp  context/comp_context.cpp context/token_defs.cpp api/ir_api.cpp

SRCS_COMMON_ICODE =  icode_lib/ast_base.cpp icode_lib/icode.cpp \
			 icode_lib/icode_array.cpp  icode_lib/icode_base.cpp \
			  icode_lib/icode_from_str.cpp  icode_lib/icode_func.cpp \
			  icode_lib/icode_iconst.cpp  icode_lib/icode_io.cpp \
			  icode_lib/icode_label.cpp  icode_lib/icode_manage.cpp \
			  icode_lib/icode_string.cpp  icode_lib/icode_struct_union.cpp \
			  icode_lib/icode_to_str.cpp  icode_lib/icode_var.cpp \
			  icode_lib/icode_visitor.cpp  icode_lib/mem_alloc.cpp \
			  icode_lib/reg_alloc.cpp  icode_lib/sym.cpp \
			  icode_lib/sym_manage.cpp  icode_lib/target_base.cpp  icode_lib/icodes.cpp \


SRCS_COMMON_UTIL= 
SRCS_COMMON_JSON = 


SRCS_COMMON=$(SRCS_COMMON_ICODE) $(SRCS_COMMON_UTIL) $(SRCS_COMMON_JSON)




SRCS_MAIN=main/main_console.cpp

SRCS=   $(SRCS_LEXYACC)  $(SRCS_MAIN) $(SRCS_LEX_ADAPT)  $(SRCS_COMMON)
PROG_LIB_OBJS=$(addprefix $(BUILD_DIR), $(SRCS_LEXYACC:.cpp=.o) )   $(addprefix $(BUILD_DIR), $(SRCS_COMMON:.cpp=.o) ) 
OBJS=$(addprefix $(BUILD_DIR), $(SRCS:.cpp=.o) ) 
BUILD_PATHTMP=$(dir $(abspath $(OBJS))) 
BUILD_PATH=$(sort $(BUILD_PATHTMP))


CURR_DIR=$(shell pwd)
CC=gcc
CXX=g++
CXX_FLAGS:= -g -Wall  -fpermissive
AR=ar
RM=rm
RMFLAGS= -rf
INCS = -I$(CURR_DIR) -I$(CURR_DIR)/lex_yacc  -I$(CURR_DIR)/lex_yacc/ly -I$(CURR_DIR)/lex_yacc_adapt -I$(CURR_DIR)/context  -I$(CURR_DIR)/icode_lib -I$(CURR_DIR)/../../misc/json_lib  -I$(CURR_DIR)/../../misc/util   -I$(CURR_DIR)/target/MCS51 -I/include/

all: $(BUILD_PATH) $(SRCS_LEXYACC)  $(PROG_LIB)  $(PROG)
	echo "finish!"


$(BUILD_PATH):
	mkdir -p $(BUILD_PATH)

lex_yacc:
	make -C lex_yacc

$(SRCS_LEXYACC):
	make -C lex_yacc

$(PROG): $(OBJS)
	$(CXX) -static -g $^   $(IMPORT_LIB) -o $@

$(PROG_LIB):$(PROG_LIB_OBJS)
	ar -rcs	  $@ $^


$(BUILD_DIR)%.o:%.c
	$(CC) $(INCS) $(CXX_FLAGS) -c $< -o $@
	
$(BUILD_DIR)%.o:%.cc
	$(CXX) $(INCS) $(CXX_FLAGS) -c $< -o $@

$(BUILD_DIR)%.o:%.cpp
	$(CXX) $(INCS) $(CXX_FLAGS) -c $< -o $@


CXX_FLAGS += -MMD -MP
-include $(OBJS:.o=.d)

.PHONY:  clean all  lex_yacc
clean:
	make -C lex_yacc clean
	rm -rf $(OBJS) $(PROG_LIB) $(PROG)



#ifneq "$(MAKECMDGOALS)" "dep"
#include $(DEPS)
#endif
