; CalcGrade.asm

section .data
  val: DB 0

section .text
global _start
_start:
  mov eax, 65 ; for some reason my assembler wasn't recognizing val's previous value so needed to reset
  mov [val], eax
  mov ebx, 90
  cmp ebx, [val]
  JBE A
  mov ebx, 80
  cmp ebx, [val]
  JBE B
  mov ebx, 70
  cmp ebx, [val]
  JBE C
  mov ebx, 60
  cmp ebx, [val]
  JBE D
  mov ebx, 50
  cmp ebx, [val]
  JBE F
  JMP QUIT
A:
  mov al, 'A'
  jmp QUIT
B:
  mov al, 'B'
  jmp QUIT
C:
  mov al, 'C'
  jmp QUIT
D:
  mov al, 'D'
  jmp QUIT
F:
  mov al, 'F'
  jmp QUIT

QUIT:
  int 0x80
  mov eax, 1
  int 0x80
  
