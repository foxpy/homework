all: 57

57: 57.o
	ld -o 57 57.o

57.o: 57.asm
	nasm -gdwarf -O0 -f elf64 -o 57.o 57.asm

clean:
	$(RM) 57.o 57
