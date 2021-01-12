BUILD_DIR=../../build/lmake/
PROG=$(BUILD_DIR)lmake.exe
PROG_LIB=$(BUILD_DIR)lmake.a

IMPORT_LIB = $(BUILD_DIR)../misc/misc.a

SRCS_MAIN= main_console.cpp

SRCS_API = api/lmake_api.cpp
SRCS_COMMON=

SRCS=    $(SRCS_MAIN)  $(SRCS_COMMON) $(SRCS_API)
PROG_LIB_OBJS=  $(addprefix $(BUILD_DIR), $(SRCS_API:.cpp=.o) ) 
OBJS=$(addprefix $(BUILD_DIR), $(SRCS:.cpp=.o) ) 
BUILD_PATHTMP=$(dir $(abspath $(OBJS))) 
BUILD_PATH=$(sort $(BUILD_PATHTMP))


CURR_DIR=$(shell pwd)
CC=gcc
CXX=g++
CXX_FLAGS= -g -Wall  -fpermissive  
#-DUNICODE
AR=ar
INCS = -I$(CURR_DIR) 	-I$(CURR_DIR)/../misc/util/ -I$(CURR_DIR)/api/


all: $(BUILD_PATH)  $(PROG)  lib
	echo "finish!"

$(BUILD_PATH):
	mkdir -p $(BUILD_PATH)

$(PROG): $(OBJS) 
	$(CXX) -static -g  -mwindows -lkernel32 -lole32 -luser32  -lshlwapi $^   $(IMPORT_LIB) -o $@

lib:$(PROG_LIB)
	echo "finish!"

$(PROG_LIB):$(PROG_LIB_OBJS)
	$(AR) -rcs $@ $^


$(BUILD_DIR)%.o:%.c
	$(CC) $(INCS) $(CXX_FLAGS) -c $^ -o $@
	
$(BUILD_DIR)%.o:%.cc
	$(CXX) $(INCS) $(CXX_FLAGS) -c $^ -o $@

$(BUILD_DIR)%.o:%.cpp
	$(CXX) $(INCS) $(CXX_FLAGS) -c $^ -o $@




.PHONY:  clean all 
clean:
	rm -rf $(OBJS) $(PROG_LIB_OBJS) $(PROG_LIB) $(PROG) 
