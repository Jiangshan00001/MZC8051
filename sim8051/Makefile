SRC_DIR := src
OBJ_DIR := ../../build/sim8051/
INCLUDE_DIR := inc

IMPORT_LIB := $(OBJ_DIR)../misc/misc.a
CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)  
OBJ_FILES := $(addprefix $(OBJ_DIR)/,$(notdir $(CPP_FILES:.cpp=.o)))

PROG_LIB_OBJS := $(filter-out $(OBJ_DIR)/main_console.o $(OBJ_DIR)/number2str.o, $(OBJ_FILES))

AR=ar
STRIP=strip

LD_FLAGS := -static 
LD_LIBS := 
#-lncurses
CC_FLAGS := -I $(INCLUDE_DIR)  -I../misc/util/ -O3 -g -std=c++11 -Wall

EXE_FILE := sim8051

PROG_LIB := $(OBJ_DIR)/sim8051.a

.PHONY: all clean test
all: $(OBJ_DIR)/$(EXE_FILE) $(PROG_LIB)


$(PROG_LIB):$(PROG_LIB_OBJS)
	$(AR) -rcs $@ $^


clean:
	rm -rf $(OBJ_FILES) $(OBJ_DIR)

test: $(OBJ_DIR)/$(EXE_FILE)
	cat ./bin/cmd | ./$(OBJ_DIR)/$(EXE_FILE)

$(OBJ_DIR)/$(EXE_FILE): $(OBJ_FILES)
	@echo "Linking $@"
	@g++  $^  $(LD_FLAGS)  $(IMPORT_LIB)  $(LD_LIBS) -o $@ 

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling $<"
	@mkdir -p $(OBJ_DIR)
	@g++ $(CC_FLAGS) -c -o $@ $<

CC_FLAGS += -MMD -MP
-include $(OBJ_FILES:.o=.d)
