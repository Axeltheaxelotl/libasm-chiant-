; Copie une chaîne de caractères depuis src vers dest
section .text
    global ft_strcpy

ft_strcpy:
    mov rax, 0
    jmp niquetamere

niquetamere:
    cmp BYTE [rdi + rax], 0
    je exit
    mov cl, [rdi + rax]
    mov [rsi + rax], cl
    inc rax
    jmp niquetamere

exit:
    mov BYTE [rsi + rax], 0
    mov rax, rsi
    ret