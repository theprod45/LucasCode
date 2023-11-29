%use masm
;section .text
;   global _start
.386
.model flat, stdcall
.stack 4096

.data
	X DWORD 1000h
	Y DWORD 2000h
	A DWORD ?
	B DWORD ?
	RESULT1 DWORD ?
	RESULT2 DWORD ?
;_start:
.code
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
	mov RESULT2, eax
	
	;Exit
	mov eax, 1
	xor ebx, ebx
	int 0x80

