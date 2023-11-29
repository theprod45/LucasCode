;4.asm
;while( ebx <= val1){
;  ebx = ebx + 5;
;  val1 = val1 - 1;
;
;}

section .data
  val1: DD 10

section .text
global _start
_start:
  mov ebx, 0
  L1: cmp ebx, [val1]
    JA QUIT ; if not <= quit
    add ebx, 5
    mov eax, [val1]
    dec eax
    mov [val1], eax
    jmp L1 

  QUIT:
    int 0x80
    mov eax, 1
    int 0x80
