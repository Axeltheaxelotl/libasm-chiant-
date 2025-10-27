global _ft_strcmp

_ft_strcmp:
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
    jmp  _ft_strcmp

exit:
movzx rax, al0
movzx r8, bl
sub rax, r8
ret
