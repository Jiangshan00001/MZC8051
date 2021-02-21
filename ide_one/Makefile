BUILD_DIR=../../build/ide_one/
PROG=$(BUILD_DIR)MZC8051.exe
PROG_LIB=$(BUILD_DIR)MZC8051.a


IMPORT_LIB = $(BUILD_DIR)../cfront/cfront.a  $(BUILD_DIR)../ir2asm8051/ir2asm8051.a\
				 $(BUILD_DIR)../irread/irread.a   $(BUILD_DIR)../sim8051/sim8051.a     \
				  $(BUILD_DIR)../asm8051/asm8051.a   $(BUILD_DIR)../lmake/lmake.a    $(BUILD_DIR)../misc/misc.a 
				  


SRCS_MAIN= main_console.cpp

SRCS_COMMON_ICODE =  

SRCS_COMMON_UTIL= 
					 
SRCS_COMMON_JSON =
					 
SRCS_COMMON_CPP = 

SRCS_COMMON=$(SRCS_COMMON_ICODE) $(SRCS_COMMON_UTIL) $(SRCS_COMMON_JSON) $(SRCS_COMMON_CPP)

SRCS=    $(SRCS_MAIN)  $(SRCS_COMMON)
PROG_LIB_OBJS= 
OBJS=$(addprefix $(BUILD_DIR), $(SRCS:.cpp=.o) ) 
BUILD_PATHTMP=$(dir $(abspath $(OBJS))) 
BUILD_PATH=$(sort $(BUILD_PATHTMP))


CURR_DIR=$(shell pwd)
CC=gcc
CXX=g++
CXX_FLAGS= -g -Wall  -fpermissive  
#-DUNICODE
AR=ar
INCS = -I$(CURR_DIR) 	   \
		-I$(CURR_DIR)/../asm8051/src/api/  \
		-I$(CURR_DIR)/../frontend/cfront/api/  \
		-I$(CURR_DIR)/../lmake/api/   \
		-I$(CURR_DIR)/../sim8051/api/ \
		-I$(CURR_DIR)/../sim8051/inc/ \		
		-I$(CURR_DIR)/../ir/irread/icode_lib \
		-I$(CURR_DIR)/../misc/cpp_lib  \
		-I$(CURR_DIR)/../misc/json_lib \
		 -I$(CURR_DIR)/../misc/util \
		 -I$(CURR_DIR)/../ir/irread/api/  \
		 -I$(CURR_DIR)/../backend/ir2asm8051/api/  
		
#  
all: $(BUILD_PATH)  $(PROG)
	echo "finish!"

$(BUILD_PATH):
	mkdir -p $(BUILD_PATH)

#  -lkernel32 -luser32 
$(PROG): $(OBJS) $(IMPORT_LIB)
	$(CXX) -static -g $^  -o $@



$(BUILD_DIR)%.o:%.c
	$(CC) $(INCS) $(CXX_FLAGS) -c $^ -o $@
	
$(BUILD_DIR)%.o:%.cc
	$(CXX) $(INCS) $(CXX_FLAGS) -c $^ -o $@

$(BUILD_DIR)%.o:%.cpp
	$(CXX) $(INCS) $(CXX_FLAGS) -c $^ -o $@




.PHONY: clean all 
clean:
	rm -rf $(OBJS) $(OBJS_ADD_SRC) $(PROG_LIB) $(PROG) 
