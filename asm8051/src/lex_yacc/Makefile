OBJS=scanner.cpp parser.cpp parser.h stack.hh position.hh location.hh 
#FlexLexer.h

all:$(OBJS)


scanner.cpp:ly/scanner.ll
	flex -o $@    $^

#FlexLexer.h:ly/scanner.ll
#	flex -o scanner.cpp $^

parser.cpp:ly/parser.yy
	bison -v --warnings=all --report=all $^  --defines=parser.h  --output=$@
parser.h:ly/parser.yy
        bison -v --warnings=all  $^  --defines=parser.h  --output=$@

stack.hh:ly/parser.yy
	bison -v --warnings=all $^  --defines=parser.h  --output=$@
position.hh:ly/parser.yy
	bison -v --warnings=all $^  --defines=parser.h  --output=$@
location.hh:ly/parser.yy
	bison -v --warnings=all $^  --defines=parser.h  --output=$@

.PHONY: clean all
clean:
	rm -rf $(OBJS) parser.output
