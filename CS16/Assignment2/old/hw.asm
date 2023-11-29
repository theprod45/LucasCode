;hw.asm
bits 32
global _start
%define system_call int 0x80
section .text
_start:
	; Result1 = (X-Y) + (X+Y)
	; RESULT1 = A + B
	mov eax, X
	add eax, Y
	mov B, eax

	mov eax, X
	sub eax, Y
	mov A, eax
	
	mov eax, A
	add eax, B
	mov RESULT1, eax
	
	; Result2 = Result1 - (X+Y)
	; RESULT2 = RESULT1 - B
	mov eax, RESULT1
	sub eax, B
	mov RESULT2, B
	
	;syscall exit(0)
	xor ebx, ebx
	mov eax, 0x1
	system_call
section .data
	X DWORD 1000h
	Y DWORD 2000h
	A DWORD ?
	B DWORD ?
	RESULT1 DWORD ?
	RESULT2 DWORD ?

