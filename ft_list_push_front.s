global ft_list_push_front
extern malloc

;rdi = t_list **begin_list
;rsi = void *data
; sortie bas rien mdr void pd
ft_list_push_front:
    push rbx ; sauvegarde rbx
    push r12 ;
    mov rbx, rdi ; rbx = begin_list (t_list **)
    mov r12, rsi ; r12 = data (void *)
    
    ; allouer 16 bytes pour le nouveau noeud
    mov rdi 16 ; sizeof (t_list) = 16
    call malloc
    ;verifier si malloc a reussi
    test rax, rax ; rax == NULL ?
    jz .error ; si oui on retourne

