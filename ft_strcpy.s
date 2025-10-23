global _ft_strcopy

_ft_strcopy:
    mov rax, 0
    jmp niquetamere

niquetamere:
    cmp BYTE [rdi + rax], 0
    je exit2
    mov cl, [rdi + rax]
    mov [rsi + rax], cl
    inc rax
    jmp niquetamere

exit2:
    mov BYTE [rsi + rax], 0
    mov rax, rsi
    ret