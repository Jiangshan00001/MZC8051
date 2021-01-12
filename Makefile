

all:
	make -C misc
	make -C lmake
	make -C asm8051
	make -C ir
	make -C frontend
	make -C backend
	make -C sim8051
	make -C ide_one

clean:
	make -C misc clean
	make -C lmake clean
	make -C asm8051 clean
	make -C ir clean
	make -C frontend clean
	make -C backend clean
	make -C sim8051 clean
	make -C ide_one clean

