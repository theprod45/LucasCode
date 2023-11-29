section .data
    X DW 1000h
    Y DW 2000h
    A DW ?
    B DW ?
    RESULT1 DW ?
    RESULT2 DW ?

section .text
    global _start
    
_start:
    mov ax, [X]
    add ax, [Y]
    mov [B], ax
    
    mov ax, [X]
    sub ax, [Y]
    mov [A], ax
    
    mov ax, [A]
    add ax, [B]
    mov [RESULT1], ax
    
    ; Result2 = Result1 - (X+Y)
    ; RESULT2 = RESULT1 - B
    mov ax, [RESULT1]
    sub ax, [B]
    mov [RESULT2], ax
    
    ; Exit
    mov eax, 1
    xor ebx, ebx
    int 0x80
