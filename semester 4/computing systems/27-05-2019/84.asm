%define SYS_READ 0
%define SYS_WRITE 1
%define SYS_EXIT 60

%define STDIN 0
%define STDOUT 1

%define EXIT_SUCCESS 0

BITS 64


section .data
string1:	db	"qwertyuiop", 0
string1_len:	equ	$ - string1
string2:	db	"ert", 0
string2_len:	equ	$ - string2

section .bss

section .text

global _start
_start:
	mov	rsi, string2
	mov	rdi, string1
	call	substr

exit:
	mov	rax, SYS_EXIT
	mov	rdi, EXIT_SUCCESS
	syscall


; find substring in string and return its addr in rax
; Arguments:
; rsi - &substr
; rdi - &str
substr:
	enter	0, 0
	mov	rcx, 0
substr_loop:
	mov	dl, [rdi+rcx]
	cmp	rdx, 0
	je	substr_exit
	inc	rcx
	jmp 	substr_loop

substr_exit:
	leave
	ret
