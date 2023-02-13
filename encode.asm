section .data
    input db 0, 0, 0  ; 3 input bytes
    output dq 0       ; 4 output values (6 bits each)

section .text
    global _start

_start:
    ; Load the input bytes into the EAX register
    mov eax, dword [input]

    ; Shift the first byte 8 bits to the left
    shl eax, 8

    ; Or the second byte into the EAX register
    or eax, byte [input + 1]

    ; Shift the result 6 bits to the left
    shl eax, 6

    ; Or the third byte into the EAX register
    or eax, byte [input + 2]

    ; Split the result into 4 6-bit numbers
    ; and store them in the output array
    mov dword [output], eax
    shr eax, 24
    mov dword [output + 4], eax
    shr eax, 24
    mov dword [output + 8], eax
    shr eax, 24
    mov dword [output + 12], eax

    ; Exit the program
    mov eax, 1
    xor ebx, ebx
    int 0x80
