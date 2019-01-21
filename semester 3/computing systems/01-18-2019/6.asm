data segment
a dw 12
b dw 34
c dw 20
d1 dw 2
d2 dw 4
data ends

code segment
assume ds:data, cs:code

start:
	mov ax, data
	mov ds, ax

	mov ax, a
	div d1
	add ax, b
	div d2
	add ax, c
	dec ax

quit:
	mov ah, 4ch
	int 21h

code ends
end start
