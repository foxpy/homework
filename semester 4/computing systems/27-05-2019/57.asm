%define SYS_READ 0
%define SYS_WRITE 1
%define SYS_EXIT 60

%define STDIN 0
%define STDOUT 1

%define EXIT_SUCCESS 0
%define MAX_STR_SIZE 64

BITS 64


section .data

prompt1:	db	"Enter string 1: "
prompt1_len:	equ	$ - prompt1
prompt2:	db	"Enter string 2: "
prompt2_len:	equ	$ - prompt2
yes:		db	"YES", 10
yes_len		equ	$ - yes
no:		db	"NO", 10
no_len:		equ	$ - no


section .bss

string1		resb	MAX_STR_SIZE
string1_len	resq	1
string2		resb	MAX_STR_SIZE
string2_len	resq	1

section .text

global _start
_start:
	; read string1
	mov	rax, SYS_WRITE
	mov	rdi, STDOUT
	mov	rsi, prompt1
	mov	rdx, prompt1_len
	syscall
	mov	rax, SYS_READ
	mov	rdi, STDIN
	mov	rsi, string1
	mov	rdx, MAX_STR_SIZE
	syscall
	mov	[string1_len], rax

	; read string2
	mov	rax, SYS_WRITE
	mov	rdi, STDOUT
	mov	rsi, prompt2
	mov	rdx, prompt2_len
	syscall
	mov	rax, SYS_READ
	mov	rdi, STDIN
	mov	rsi, string2
	mov	rdx, MAX_STR_SIZE
	syscall
	mov	[string2_len], rax

compare_len:
	cmp	[string1_len], rax
	jne	not_equal

strcmp:
	mov	rcx, [string1_len]
strcmp_loop:
	lea	rbx, [string1 + rcx]
	mov	rdx, [rbx]
	cmp	rdx, [string2 + rcx]
	jne	not_equal
	loop	strcmp_loop


equal:
	mov	rax, SYS_WRITE
	mov	rdi, STDOUT
	mov	rsi, yes
	mov	rdx, yes_len
	syscall
	jmp	exit

not_equal:
	mov	rax, SYS_WRITE
	mov	rdi, STDOUT
	mov	rsi, no
	mov	rdx, no_len
	syscall
	jmp	exit

exit:
	mov	rax, SYS_EXIT
	mov	rdi, EXIT_SUCCESS
	syscall
