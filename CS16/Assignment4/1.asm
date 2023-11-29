; Question 1

section .data
array DW 50 DUP(0)
sentinel DW 0xFFFF;

section .text
global _start
_start:
  mov esi, array
  mov ecx, 5
  L1: cmp DWORD [esi], 0 ; check for zero
      jz Found ; Jump if found
      cmp ecx, 0 ; Now check if we at end
      jz AtEnd ; Jump if at end
      dec ecx ; decrement ecx
      jmp L1  ; jump to top 

  Found:
    jmp Quit
  AtEnd:
    mov esi, sentinel
    jmp Quit
  Quit:
    int 0x80
    mov eax, 1
    int 0x80
