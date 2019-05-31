%define SYS_READ 0
%define SYS_WRITE 1
%define SYS_EXIT 60

%define STDIN 0
%define STDOUT 1

%define EXIT_SUCCESS 0
%define MAX_STR_SIZE 64

BITS 64


section .data
message:	db	"Input string: "
message_len:	equ	$ - message
newline:	db	10
newline_len:	equ	$ - newline

section .bss
input_str	resb	MAX_STR_SIZE

section .text

global _start
_start:
	mov	rax, SYS_WRITE
	mov	rdi, STDOUT
	mov	rsi, message
	mov	rdx, message_len
	syscall
	mov	rax, SYS_READ
	mov	rdi, STDIN
	mov	rsi, input_str
	mov	rdx, MAX_STR_SIZE
	syscall

	mov	rsi, input_str
main_loop:
	call	strsplit
	cmp	rax, 0
	je	last_word
	push	rdi
	mov	rdx, rax
	mov	rax, SYS_WRITE
	; rsi already contains what we need
	mov	rdi, STDOUT
	syscall
	mov	rax, SYS_WRITE
	mov	rdi, STDOUT
	mov	rsi, newline
	mov	rdx, newline_len
	syscall
	pop	rsi
	jmp	main_loop

last_word:
	mov	rax, SYS_WRITE
	; rsi already contains what we need
	mov	rdi, STDOUT
	; rdx already contains what we need
	syscall

exit:
	mov	rax, SYS_EXIT
	mov	rdi, EXIT_SUCCESS
	syscall

; Split string by first word
; Arguments:
;   rsi - string address [preserved]
; Return values:
;   rax - length of first word
;   rdi - address of second word
; Docs:
;   rax equals zero if string cannot be splitted,
;   in this case rdx stores count of bytes processed
strsplit:
	enter	0, 0
	mov	rax, 0
	mov	rcx, 0
strsplit_loop:
	mov	dl, [rsi+rcx]
	cmp	dl, 0
	je	strsplit_error
	cmp	dl, " "
	je	strsplit_found
	inc	rcx
	jmp	strsplit_loop
strsplit_exit:
	leave
	ret
strsplit_error:
	mov	rdx, rcx
	jmp strsplit_exit
strsplit_found:
	mov	rax, rcx
	mov	rdi, rsi
	add	rdi, rcx
	inc	rdi
	jmp	strsplit_exit
