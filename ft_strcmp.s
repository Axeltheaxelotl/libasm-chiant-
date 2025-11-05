; Compare deux chaînes de caractères (retourne différence)
section .text
    global ft_strcmp

ft_strcmp:
    mov al, BYTE [rdi]
    mov bl, BYTE [rsi]
    cmp al, 0
    je exit
    cmp bl, 0
    je exit
    cmp al, bl
    jne exit
    inc rdi
    inc rsi
    jmp  ft_strcmp

exit:
movzx rax, al0
movzx r8, bl
sub rax, r8
ret
