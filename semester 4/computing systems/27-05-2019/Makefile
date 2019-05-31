all: 57 92

57: 57.o
	ld -o 57 57.o

57.o: 57.asm
	nasm -gdwarf -O0 -f elf64 -o 57.o 57.asm

92: 92.o
	ld -o 92 92.o

92.o: 92.asm
	nasm -gdwarf -O0 -f elf64 -o 92.o 92.asm

clean:
	$(RM) 57.o 57 92.o 92
