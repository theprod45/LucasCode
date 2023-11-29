section .data
	A: DW 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80, 0x90
section .text
global _start
_start:
mov bx,0x90
stc
mov ax,0x80
adc bx,ax
	;add bx, 4
	;mov ax, A[bx]
	;mov ax, A[bx+2]
	;add ax, A[0]
	;mov si, A
	;mov ah, BYTE [si+4]

	;SYS exit
	int 0x80
	mov eax, 1
	int 0x80
