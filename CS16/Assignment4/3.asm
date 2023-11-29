; 4.asm
; if( ebx <= ecx && ecx > edx ){
;   eax = 5
;   edx = 6
;}

section .text 
global _start
_start:
  ; Setting up registers
  mov eax, 0
  mov edx, 0
  mov ebx, 0
  mov ecx, 1

  cmp ebx, ecx
  JG NOPE
  cmp ecx, edx
  JLE NOPE
  ; True
  mov eax, 5
  mov edx, 6
  jmp QUIT
  
  ; Not found
  NOPE:
    jmp QUIT

  QUIT:
    int 0x80
    mov eax,1
    int 0x80
