;program1.asm
;1
section .data
	X: DD 0x100, 0x200, 0x300, 0x400, 0x500, 0x600

section .text
global _start
_start:
	mov eax, 0 ; Makes it easier to debug
	mov eax, X ; Move into eax the first memory address of X
	mov ecx, 3  ; Gonna loop 3 times cuz the array is size 6
L1: mov ebx,[eax] ; Move into ebx whatever eax is POINTING to
	add eax, 0x4 ; Inc eax to go to next element
	xchg [eax], ebx ; Move the previous element into the next
	sub eax, 0x4 ; Go back to put the next value back in the prev
	xchg [eax], ebx ; put the next val in the prev
	add eax, 0x8 ; inc twice 
loop L1
	;sysExit
	int 0x80
	mov eax, 1
	int 0x80
