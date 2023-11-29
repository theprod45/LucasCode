;Concatenates a source string to the end of a target string. Sufficient space must exist in the 
; target string to accomodate the new characters. Pass pointers to the sourcce and target strings.

section .data
  targetString:DB "ABCDE",10 DUP(0)
  sourceString:DB "FGH", 0

section .text
global _start
_start:
  ; Load sourceString into edx
  lea edx, [sourceString]
  ; Load targetString into eax
  lea eax, [targetString]
  call StrConcat
  call Quit

StrConcat:
  mov ecx, [edx]
  mov [eax+5], ecx
  mov ecx, [edx+1]
  mov [eax+6], ecx
  mov ecx, [edx+2]
  mov [eax+7], ecx
  ret
  
Quit:
  int 0x80
  mov eax, 1
  int 0x80
