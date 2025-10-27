global _ft_strdup
extern _malloc
global _ft_strlen
global _ft_strcpy

_ft_strdup:
    call _ft_strlen
    add rax, 1 ; +1 pour le \0 a la fin
    push rdi ; push le rdi fans la stack
    mov rdi, rax
    call _malloc
    pop r8
    mov rdi, rax
    mov rsi, r8
    call _ft_strcpy
    ret