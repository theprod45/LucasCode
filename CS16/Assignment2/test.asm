;test.asm
section .data
	X: DD 0x1000
	Y: DD 0x2000
	A: DD 0
	B: DD 0
	RESULT1: DD 0
	RESULT2: DD 0

section .text
global _start
_start:
	mov eax, 0
	mov ebx, 0
	; result1 = (X-Y)+ (X + Y)
	; (2-1) + (1+2) = 4
	; Add X+Y and store in B
	mov eax, [X]
	add eax, [Y]
	mov [B], eax
	; X-Y store in A
	mov eax, [X]
	sub eax, [Y]
	mov [A], eax
	; ADD A+B and store in RESULTS
	mov eax, [A]
	add eax, [B]
	mov [RESULT1], eax
	; RESULT2 = RESULT1 - (X+Y)
	; RESULT2 = RESULT1 - B = 1
	mov eax, [RESULT1]
	sub eax, [B]
	mov [RESULT2] , eax
	
	; EAX is R1 , EBX IS R2
	mov eax, [RESULT1]
	mov ebx, [RESULT2]

	;System Exit, This called the Linux Kernel to do something, So Wont work on non-Linux Machine
	int 0x80 ; calls the kernel
	mov eax, 1 ; system call number (sys_exit)
	int 0x80 ; call kernel
