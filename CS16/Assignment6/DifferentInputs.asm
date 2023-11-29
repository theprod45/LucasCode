; returns EAX = 1 if the value of its three parameters are all different
; otherwise, return with EAX = 0. 
; Nasm Trickery

section .data ;variable section
  testValues: DD 0x2, 0x2, 0x2
section .text
global _start
_start:
  lea edx, [testValues]
  call DifferentInputs
  call QuitProgram

; The assignment
DifferentInputs:
  mov eax, 0
  mov ecx, [edx]
  cmp ecx, [edx+4]
  jne Quit
  mov ecx, [edx+4]
  cmp ecx,[edx+8]
  jne Quit
  mov eax, 1
  ret
Quit:
  ret

QuitProgram:
  int 0x80
  mov eax, 1
  int 0x80
