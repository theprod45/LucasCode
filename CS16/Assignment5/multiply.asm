; muliply.asm
; Multiply AX by 26, 26 = 16 + 8 + 2
section .text
global _start
_start:
  ; start with multiplying 2 by 26
  mov eax, 0
  mov ecx, 0
  mov ax, 2 ; Using 2 as a test value
  mov bx, ax
  
  ; Multiply by 2
  shl bx, 1
  add cx, bx
  mov bx, ax
  ; Multiply by 8
  shl bx, 3
  add cx, bx
  mov bx, ax
  ; Multiply by 16
  shl bx, 4
  add cx, bx
  ;result is stored in cx
