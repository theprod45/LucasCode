;program2.asm
;2
section .data
	X : DD 0x0, 0x2, 0x5, 0x9, 0xA
	SUM : DD 0
	T : DD 0 
section .text
global _start
_start:
	mov eax, 0
	mov ebx, 0 ; clearing reg Can also xor ebx. ebx
	mov eax, X ; Move the X mem address into eax
	
	mov ecx, 4; LOOPING 4 times cuz array is size 5
L1: mov ebx, [eax] ; Load the value of eax into ebx
	mov [T], ebx ; Must use Temp variables, Move that value into T
	add eax, 0x4 ; Increment eax , X[n+!]
	mov ebx, [eax] ; mov number into ebx so when we sub we dont effect mem
	sub ebx, [T] ; Do subtraction
	add [SUM], ebx ; Now add the result to the SUM Variable
loop L1
	;sysExit
	int 0x80
	mov eax, 1
	int 0x80
	
