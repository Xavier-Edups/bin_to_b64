section .text

; _encode_64_triplet_c(char *triplet, int32_t triplet_size, char *encoded_triplet);
    ; mov   rax, rdi   ; argument 1
    ; add   rax, rsi   ; argument 2
    ; add   rax, rdx   ; argument 3
global _encode_64_triplet
_encode_64_triplet:
    ; uint32_t triplet_value = (triplet[0] << 16) | (triplet[1] << 8) | triplet[2]; // r8
    ; concatenacao dos bytes de entrada
	mov  r8b, [rdi]
    shl  r8, 8
    mov  r8b, [rdi + 1]
    shl  r8, 8
    mov  r8b, [rdi + 2]
    mov  rax, r8

    ; encoded_triplet[0] = base_64_table[(triplet_value >> 18) & 0x3F];
	mov  r9, r8
    shr  r9, 18 ; pega um byte
    and  r9, 0x3F ; desse byte, pega 6 bits
    mov  r9b, [base_64_table + r9] ; mapeia valor de 6 bits para base 64
    mov  [rdx], r9b

    ; encoded_triplet[1] = base_64_table[(triplet_value >> 12) & 0x3F];
    mov  r9, r8
    shr  r9, 12
    and  r9, 0x3F
    mov  r9b, [base_64_table + r9]
    mov  [rdx + 1], r9b

    ; encoded_triplet[2] = base_64_table[(triplet_value >> 6) & 0x3F];
    mov  r9, r8
    shr  r9, 6
    and  r9, 0x3F
    mov  r9b, [base_64_table + r9]
    mov  [rdx + 2], r9b

    ; encoded_triplet[3] = base_64_table[triplet_value & 0x3F];
    mov  r9, r8
    and  r9, 0x3F
    mov  r9b, [base_64_table + r9]
    mov  [rdx + 3], r9b

    ; if (triplet_size < 3) encoded_triplet[3] = '=';
    cmp  rsi, 3
    jge  passou_2
    mov  byte [rdx + 3], '='

passou_2:
    ; if (triplet_size < 2) encoded_triplet[2] = '=';
    cmp  rsi, 2
    jge  passou_1
    mov  byte [rdx + 2], '='

passou_1:
    ret

section .data

base_64_table db "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/",0
