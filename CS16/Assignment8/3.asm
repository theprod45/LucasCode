INCLUDE Irvine32.inc

.DATA
    X REAL8 ?
    Y REAL8 ?
    lowerMsg BYTE "X is lower", 0
    higherMsg BYTE "X is higher", 0

.CODE
main PROC
    ; Input values for X and Y (assuming they are already assigned)

    ; Compare X and Y
    fld QWORD PTR X     ; Load X into FPU stack
    fcomp QWORD PTR Y   ; Compare X and Y
    fstsw ax            ; Store FPU status word
    sahf                ; Copy status flags to CPU flags

    ; Branch based on the result of the comparison
    jb lower            ; Jump if X < Y
    jnb higher          ; Jump if X >= Y

lower:
    ; Print "X is lower"
    mov edx, OFFSET lowerMsg
    call WriteString
    jmp end

higher:
    ; Print "X is higher"
    mov edx, OFFSET higherMsg
    call WriteString

end:
    ; Exit program
    exit
main ENDP

END main
