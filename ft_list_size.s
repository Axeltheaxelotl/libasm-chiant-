; Compte le nombre d'éléments dans une liste chaînée
section .text
    global ft_list_size

ft_list_size:
    xor rax, rax ; initialise le fils de pute de compteur a 0
    test rdi, rdi
    jz .erreur_de_fils_de_pute

.loop
    test rdi, rdi
    jz .erreur_de_fils_de_pute
    inc rax
    mov rdi, [rdi + 8]
    jmp .loop

.erreur_de_fils_de_pute:
    ret