data segment
mass db 10h, 20h, 30h, 40h, 50h, 60h, 70h, 80h
data ends

code segment
assume cs: code, ds: data

start:
	mov ax, data
	mov ds, ax
	lea bx, mass

	mov ax, 0h
	mov bx, 0h
	mov cx, 4h
	mov dx, 0007h

begin:
	mov bl, dh
	mov al, [bx]
	mov bl, dl
	mov ah, [bx]
	mov [bx], al
	mov bl, dh
	mov [bx], ah
	inc dh
	dec dl
	loop begin

quit:
	mov ax, 4c00h
	int 21h

code ends
end start
