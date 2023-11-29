section .text
	global _start

_start:
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
	
	;Exit
	mov eax, 1
	xor ebx, ebx
	int 0x80

section .data
	X DW 1000h
	Y DW 2000h
	A DW ?
	B DW ?
	RESULT1 DW ?
	RESULT2 DW ?
	
