; Trie une liste chaînée avec une fonction de comparaison

section .text
    global ft_list_sort

ft_list_sort:
    test rdi, rdi
    jz .fin
    
    mov rax, [rdi]
    test rax, rax
    jz .fin
    
.boucle_externe:
    xor r8, r8
    mov r9, [rdi]
    
.boucle_interne:
    mov r10, [r9 + 8]
    test r10, r10
    jz .verifier_si_echange
    
    push rdi
    push rsi
    push r8
    push r9
    push r10
    
    mov rdi, [r9]
    mov rsi, [r10]
    call [rsp + 8]
    
    pop r10
    pop r9
    pop r8
    pop rsi
    pop rdi
    
    cmp eax, 0
    jle .pas_d_echange
    
    mov r11, [r9]
    mov r12, [r10]
    mov [r9], r12
    mov [r10], r11
    
    mov r8, 1
    
.pas_d_echange:
    mov r9, r10
    jmp .boucle_interne
    
.verifier_si_echange:
    test r8, r8
    jnz .boucle_externe
    
.fin:
    ret