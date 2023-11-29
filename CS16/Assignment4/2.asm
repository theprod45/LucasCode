; 2.asm
; if(ebx <= ecx){
;   eax = 5;
;   edx =6;
;}

section .text
global _start
_start:
  ;Setting up Registers
  mov ebx, 2
  mov ecx, 1
  mov eax, 0
  mov edx, 0

  cmp ebx, ecx
  jbe YES
  jmp QUIT

  YES:
    mov eax, 5
    mov edx, 6
    jmp QUIT
  QUIT:
    int 0x80
    mov eax, 1
    int 0x80

