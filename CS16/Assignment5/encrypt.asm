INCLUDE Irvine32.inc

.DATA
    key     BYTE -2, 4, 1, 0, -3, 5, 2, -4, -4, 6
    message BYTE "This is a test message.", 0

.CODE
main PROC
    ; Encrypt the message
    mov edx, OFFSET message
    call EncryptMessage

    ; Print the encrypted message
    mov edx, OFFSET message
    call WriteString

    ; Exit program
    exit
main ENDP

EncryptMessage PROC
    pushad

    mov esi, OFFSET key  ; Point to the encryption key
    xor ecx, ecx        ; Clear counter

encrypt_loop:
    mov al, [edx + ecx] ; Get the next byte from the message
    test al, al         ; Check for null terminator
    jz end_loop

    mov dl, [esi]       ; Get the rotation value from the key
    test dl, dl         ; Check if positive or negative rotation
    jg rotate_right
    jl rotate_left

    jmp next_iteration  ; No rotation if rotation value is 0

rotate_left:
    neg dl              ; Negate the rotation value
    ror al, dl          ; Rotate the byte to the left
    jmp next_iteration

rotate_right:
    ror al, dl          ; Rotate the byte to the right

next_iteration:
    mov [edx + ecx], al ; Store the encrypted byte back to the message
    inc ecx             ; Increment counter
    inc esi             ; Move to the next key value
    cmp ecx, 10         ; Check if 10 bytes have been encrypted
    jne encrypt_loop

    popad
    ret

end_loop:
    popad
    ret
EncryptMessage ENDP

END main
