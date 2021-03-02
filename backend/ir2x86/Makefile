BUILD_DIR=../../../build/ir2x86/
PROG=$(BUILD_DIR)ir2x86.exe
PROG_LIB=$(BUILD_DIR)ir2x86.a

IMPORT_LIB = $(BUILD_DIR)../irread/irread.a  $(BUILD_DIR)../misc/misc.a

SRCS_LEXYACC= 

SRCS_CPP = 	 api/ir2x86_api.cpp

			
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
INCS = -I$(CURR_DIR) -I$(CURR_DIR)/../../ir/irread/icode_lib/ -I$(CURR_DIR)/../../misc/json_lib/  -I$(CURR_DIR)/../../misc/util/  -I$(CURR_DIR)/common/util  -I$(CURR_DIR)/target/MCS51 -I$(CURR_DIR)/filter/  -I$(CURR_DIR)/../../ir/irread/filter/ 

all: $(BUILD_PATH) $(SRCS_LEXYACC)  $(PROG_LIB) 
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
