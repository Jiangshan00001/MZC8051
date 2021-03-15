BUILD_DIR=../../../build/asm8051/
PROG=$(BUILD_DIR)asm8051.exe
PROG_LIB=$(BUILD_DIR)asm8051.a

SRCS_A51 += test_zhushi1.a51

SRCS_A51 += test_jb_ext1.a51 test_jb_ext2.a51 test_jc_ext1.a51 test_jc_ext2.a51
SRCS_A51 += test_sjmp_ext1.a51 test_sjmp_ext2.a51 test_sjmp_ext3.a51 test_sjmp_ext4.a51
SRCS_A51 += test_predefined1.a51
SRCS_A51 += test_sjmp1.a51 test_sjmp2.a51 test_equ_2.a51 
SRCS_A51 += test_label_opr.a51

SRCS_A51 +=  asm_test1.a51 asm_test2.a51  stc8a_test1.a51 stc8a_test2.a51 stc8a_test3.a51 \
           stc8a_test4.a51  stc8a_test5.a51 stc8a_test6.a51 stc_paomadeng.a51  
			 
SRCS_A51+=stc_hc595.a51 

#SRCS_A51 += stc_hongwai1.a51



KEIL_HEX= $(SRCS_A51:.a51=_keil.hex)
SELF_HEX= $(SRCS_A51:.a51=_self.hex)

KEIL_A51=$(KEIL_HEX:.hex=.a51)
SELF_A51=$(SELF_HEX:.hex=.a51)


DIFF_SRC=$(SRCS_A51:.a51=.diff)

TMP_SRC=compile_1.txt compile_2.txt compile_3.txt compile_4.txt
ASM8051_EXE=$(PROG)



SRCS=  $(SRCS_LEXYACC) $(SRCS_ASM8051_LIB)   $(SRCS_MAIN)
PROG_LIB_OBJS=$(addprefix $(BUILD_DIR), $(SRCS_LEXYACC:.cpp=.o) ) $(addprefix $(BUILD_DIR), $(SRCS_ASM8051_LIB:.cpp=.o) )
OBJS=$(addprefix $(BUILD_DIR), $(SRCS:.cpp=.o) )
BUILD_PATHTMP=$(dir $(abspath $(OBJS))) 
BUILD_PATH=$(sort $(BUILD_PATHTMP))




CURR_DIR=$(shell pwd)
CC=gcc
CXX=g++
CXX_FLAGS= -g -Wall  -fpermissive
AR=ar
STRIP=strip

INCS = -I$(CURR_DIR)  -I$(CURR_DIR)/lex_yacc/


all: $(ASM8051_EXE)  $(KEIL_A51) $(SELF_A51) $(DIFF_SRC)
	echo "finish!"

$(BUILD_PATH):
	mkdir -p $(BUILD_PATH)

$(ASM8051_EXE):
	make -C ../src;

%.diff:%_keil.a51 %_self.a51
	diff  $^ > $@
	

%.a51:%.hex
	$(ASM8051_EXE) -dis -nd $^  $@
	


%_self.hex:%.a51
	$(ASM8051_EXE) -asm -d  $^  $@

%_self.yy:%.a51
	$(ASM8051_EXE) -yy -nd  $^  $@


$(BUILD_DIR)%.o:%.cc
	$(CXX) $(INCS) $(CXX_FLAGS) -c $^ -o $@

$(BUILD_DIR)%.o:%.cpp
	$(CXX) $(INCS) $(CXX_FLAGS) -c $^ -o $@


.PHONY: $(SRCS_LEXYACC) all  clean 

clean:
	rm -rf $(KEIL_A51) $(SELF_A51) $(SELF_HEX) $(DIFF_SRC) $(TMP_SRC)
