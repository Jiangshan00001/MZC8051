BUILD_DIR=../../../build/cfront/
PROG=$(BUILD_DIR)cfront.exe
PROG_LIB=$(BUILD_DIR)cfront.a
IMPORT_LIB= $(BUILD_DIR)../irread/irread.a $(BUILD_DIR)../misc/misc.a 

SRCS_LEXYACC= lex_yacc/parser.cpp lex_yacc/scanner.cpp  lex_yacc/ly/comp_context_gen.cpp    lex_yacc/ly/funcs/ast_to_icode_common.cpp lex_yacc/ly/funcs/ast_to_icode_declaration.cpp lex_yacc/ly/funcs/ast_to_icode_declarator.cpp lex_yacc/ly/funcs/ast_to_icode_enum_specifier.cpp lex_yacc/ly/funcs/ast_to_icode_expr.cpp lex_yacc/ly/funcs/ast_to_icode_func.cpp lex_yacc/ly/funcs/ast_to_icode_gen_other.cpp lex_yacc/ly/funcs/ast_to_icode_jump.cpp lex_yacc/ly/funcs/ast_to_icode_start.cpp lex_yacc/ly/funcs/ast_to_icode_statement.cpp lex_yacc/ly/funcs/ast_to_icode_storage_class_specifier.cpp lex_yacc/ly/funcs/ast_to_icode_struct_or_union_specifier.cpp lex_yacc/ly/funcs/ast_to_icode_type_specifier.cpp  lex_yacc/ly/comp_context_yy_debug.cpp



SRCS_CPP = 		lex_yacc_adapt/driver.cpp  context/comp_context.cpp context/token_defs.cpp  api/c8051_api.cpp	

SRCS_TARGET = 		target/MCS51/bit_addr_parse.cpp target/MCS51/c51_addr.cpp  target/MCS51/c51_var_manage.cpp \
			 target/MCS51/get_j_data_byte.cpp  target/MCS51/icode_to_c51.cpp \
			 target/MCS51/icode_to_c51_opr.cpp  target/MCS51/icode_to_c51_sys_func.cpp \
			 target/MCS51/icode_to_c51_mov.cpp 
			
SRCS_COMMON_ICODE =  


SRCS_COMMON_UTIL= 
					 
SRCS_COMMON_JSON = 


SRCS_COMMON=$(SRCS_COMMON_ICODE) $(SRCS_COMMON_UTIL) $(SRCS_COMMON_JSON)


SRCS_MAIN=main/main_console.cpp

SRCS=   $(SRCS_LEXYACC)  $(SRCS_MAIN) $(SRCS_CPP)  $(SRCS_COMMON)
PROG_LIB_OBJS=$(addprefix $(BUILD_DIR), $(SRCS_LEXYACC:.cpp=.o) )   $(addprefix $(BUILD_DIR), $(SRCS_CPP:.cpp=.o) ) 
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
INCS = -I$(CURR_DIR) -I$(CURR_DIR)/lex_yacc  -I$(CURR_DIR)/lex_yacc/ly -I$(CURR_DIR)/lex_yacc_adapt -I$(CURR_DIR)/context -I$(CURR_DIR)/../../ir/irread/icode_lib -I$(CURR_DIR)/../../misc/json_lib -I$(CURR_DIR)/../../misc/cpp_lib  -I$(CURR_DIR)/../../misc/util  -I$(CURR_DIR)/target/MCS51  -I/include/

all: $(BUILD_PATH) $(SRCS_LEXYACC)  $(PROG_LIB)  $(PROG)
	echo "finish!"


$(BUILD_PATH):
	mkdir -p $(BUILD_PATH)

lex_yacc:
	make -C lex_yacc

$(SRCS_LEXYACC):
	make -C lex_yacc

$(PROG): $(OBJS)
	$(CXX) -static -g $^  $(IMPORT_LIB) -o $@

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
	rm -rf $(OBJS) $(OBJS_ADD_SRC) $(PROG_LIB) $(PROG)



#ifneq "$(MAKECMDGOALS)" "dep"
#include $(DEPS)
#endif
