all: 57 84

57: 57.o
	ld -o 57 57.o

57.o: 57.asm
	nasm -gdwarf -O0 -f elf64 -o 57.o 57.asm

84: 84.o
	ld -o 84 84.o

84.o: 84.asm
	nasm -gdwarf -O0 -f elf64 -o 84.o 84.asm

clean:
	$(RM) 57.o 57 84.o 84
