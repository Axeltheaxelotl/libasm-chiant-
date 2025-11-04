; Duplique une chaîne de caractères (allocation dynamique)
global ft_strdup
extern malloc
extern ft_strlen
extern ft_strcpy

ft_strdup:
    call ft_strlen
    add rax, 1 ; +1 pour le \0 a la fin
    push rdi ; push le rdi dans la stack
    mov rdi, rax
    call malloc
    pop r8
    mov rdi, rax
    mov rsi, r8
    call ft_strcpy
    ret