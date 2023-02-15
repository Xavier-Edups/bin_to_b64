global _encode_64_triplet

section .data

base_64_table:
    db  'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/'

section .text

; _encode_64_triplet_c(char *triplet, int32_t triplet_size, char *encoded_triplet);
_encode_64_triplet:
    ; uint32_t triplet_value = (triplet[0] << 16) | (triplet[1] << 8) | triplet[2]; // r8
    mov  r8b, [rdi]
    shl  r8, 8
    mov  r8b, [rdi + 1]
    shl  r8, 8
    mov  r8b, [rdi + 2]
    mov  rax, r8

    ; encoded_triplet[0] = base_64_table[(triplet_value >> 18) & 0x3F];
    mov  r9, r8
    shr  r9, 18
    mov  [rdx], r9b

    ; mov   rax, rdi   ; argument 1
    ; add   rax, rsi   ; argument 2
    ; add   rax, rdx   ; argument 3
    ret