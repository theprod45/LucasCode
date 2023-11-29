INCLUDE Irvine32.inc

DECIMAL_OFFSET EQU 5

.DATA
    decimal_one BYTE "100123456789765",0
    decimal_two BYTE "987654",0
    decimal_three BYTE "1234567890",0

.CODE
main PROC
    ; Test with decimal_one
    mov edx, OFFSET decimal_one
    mov ecx, LENGTHOF decimal_one - 1
    mov ebx, DECIMAL_OFFSET
    call WriteScaled

    ; Test with decimal_two
    mov edx, OFFSET decimal_two
    mov ecx, LENGTHOF decimal_two - 1
    mov ebx, DECIMAL_OFFSET
    call WriteScaled

    ; Test with decimal_three
    mov edx, OFFSET decimal_three
    mov ecx, LENGTHOF decimal_three - 1
    mov ebx, DECIMAL_OFFSET
    call WriteScaled

    ; Exit program
    exit
main ENDP

WriteScaled PROC
    pushad
    sub ecx, 1   ; Adjust length for zero-based index

    mov eax, ecx ; Copy length to eax
    add eax, ebx ; Add decimal offset

    movzx edi, byte ptr [edx + ecx] ; Load the last digit
    cmp edi, 0
    je skip_decimal

    sub edi, '0' ; Convert from ASCII to decimal

    ; Output digits before the decimal point
    mov ecx, eax
    before_decimal:
        mov eax, edi
        xor edx, edx
        mov ebx, 10
        div ebx
        add edx, '0' ; Convert remainder to ASCII
        push edx     ; Store remainder
        mov edi, eax ; Move quotient to edi
        loop before_decimal

    ; Output decimal point
    mov eax, '.'
    push eax

    skip_decimal:
    ; Output digits after the decimal point
    lea ecx, [edx + edi] ; Move offset to ecx

    mov eax, ecx ; Copy length to eax
    sub eax, ebx ; Subtract decimal offset

    movzx edi, byte ptr [edx + ecx] ; Load the first digit after the decimal point
    cmp edi, 0
    je end

    sub edi, '0' ; Convert from ASCII to decimal

    after_decimal:
        mov eax, edi
        xor edx, edx
        mov ebx, 10
        div ebx
        add edx, '0' ; Convert remainder to ASCII
        push edx     ; Store remainder
        mov edi, eax ; Move quotient to edi
        loop after_decimal

    end:
    ; Output digits
    mov edx, OFFSET decimal_one
    add edx, ecx ; Adjust offset
    mov ecx, eax ; Number of digits
    mov ebx, 1   ; File descriptor (stdout)
    mov eax, 4   ; System call number (write)
    int 0x80

    ; Clean up stack and return
    add esp, ecx
    popad
    ret
WriteScaled ENDP

END main
