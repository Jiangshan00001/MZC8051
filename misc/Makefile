PROG_NAME=misc
BUILD_DIR=../../build/$(PROG_NAME)/
PROG=$(BUILD_DIR)$(PROG_NAME).exe
PROG_LIB=$(BUILD_DIR)$(PROG_NAME).a


SRCS_LEXYACC= 



SRCS_CPP =  cpp_lib/cpp_api.cpp  cpp_lib/simplecpp.cpp


SRCS_COMMON_UTIL= util/main_var.cpp util/str2number.cpp  util/number2str.cpp \
					 util/replace.cpp util/text_encode.cpp \
					 util/string_eval.cpp util/trim.cpp util/split.cpp \
					 util/mylog.cpp util/dir_file.cpp util/myexecute.cpp
					 
SRCS_COMMON_JSON = json_lib/json_io.cpp


SRCS_COMMON= $(SRCS_COMMON_UTIL) $(SRCS_COMMON_JSON) $(SRCS_CPP)




SRCS_MAIN=cpp_lib/simplecpp_main.cpp

SRCS=   $(SRCS_LEXYACC)  $(SRCS_MAIN) $(SRCS_CPP)  $(SRCS_COMMON)
PROG_LIB_OBJS=$(addprefix $(BUILD_DIR), $(SRCS_COMMON:.cpp=.o) )
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
INCS = -I$(CURR_DIR)  -I$(CURR_DIR)/json_lib  -I$(CURR_DIR)/util  -I$(CURR_DIR)/cpp_lib

all: $(BUILD_PATH) $(SRCS_LEXYACC)  $(PROG_LIB)  $(PROG)
	echo "finish!"


$(BUILD_PATH):
	mkdir -p $(BUILD_PATH)

lex_yacc:
	make -C lex_yacc

$(SRCS_LEXYACC):
	make -C lex_yacc

$(PROG): $(OBJS)
	$(CXX) -static -g $^  -o $@

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
	rm -rf $(OBJS) $(OBJS_ADD_SRC) $(PROG_LIB) $(PROG) $(BUILD_PATH)



#ifneq "$(MAKECMDGOALS)" "dep"
#include $(DEPS)
#endif
