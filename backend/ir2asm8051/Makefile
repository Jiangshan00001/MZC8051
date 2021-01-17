BUILD_DIR=../../../build/ir2asm8051/
PROG=$(BUILD_DIR)ir2asm8051.exe
PROG_LIB=$(BUILD_DIR)ir2asm8051.a

IMPORT_LIB = $(BUILD_DIR)../irread/irread.a  $(BUILD_DIR)../misc/misc.a

SRCS_LEXYACC= 

SRCS_CPP = 	 api/ir2asm8051_api.cpp \
			 target/MCS51/bit_addr_parse.cpp target/MCS51/c51_addr.cpp  target/MCS51/c51_var_manage.cpp \
			 target/MCS51/get_j_data_byte.cpp  target/MCS51/icode_to_c51.cpp \
			 target/MCS51/icode_to_c51_opr.cpp  target/MCS51/icode_to_c51_sys_func.cpp \
			 target/MCS51/icode_to_c51_mov.cpp \
			 filter/c51_filter_manage.cpp filter/icode_collect_str.cpp filter/icode_const_folder.cpp \
			 filter/icode_dead_func.cpp filter/icode_float_cast.cpp filter/icode_float_func_opr.cpp \
			 filter/icode_func_var_register.cpp filter/icode_global_func.cpp filter/icode_inline.cpp \
			 filter/icode_ptr_calc.cpp filter/icode_ptr_copy.cpp filter/icode_ref_number.cpp \
			 filter/icode_replace.cpp filter/icode_var_scope.cpp filter/icode_unresolved.cpp \
			 filter/icode_positive_opr.cpp filter/icode_ptr_in_calc.cpp

			
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
INCS = -I$(CURR_DIR) -I$(CURR_DIR)/../../ir/irread/icode_lib/ -I$(CURR_DIR)/../../misc/json_lib/  -I$(CURR_DIR)/../../misc/util/  -I$(CURR_DIR)/common/util  -I$(CURR_DIR)/target/MCS51 -I$(CURR_DIR)/filter/

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
	rm -rf $(OBJS) $(OBJS_ADD_SRC) $(PROG_LIB) $(PROG) 



#ifneq "$(MAKECMDGOALS)" "dep"
#include $(DEPS)
#endif
