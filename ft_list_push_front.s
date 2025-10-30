    ;typedef struct s_list{
    ;    void *data; // 8 bites
    ;    struct s_list *next; // 8 bites
    ;} t_list; // total 16 bites

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
    mov rdi, 16 ; sizeof (t_list) = 16
    call malloc
    ;verifier si malloc a reussi
    test rax, rax ; rax == NULL ?
    jz .error ; si oui on retourne
    
    ; etapes 2 remplir le nouveau noeud
    ; rax contient l'adresse du nouveau noeud
    mov [rax], r12 ; nouveau->data = data 

    ; nouveau->next = *begin_list (l'ancien premier element)
    mov rcx, [rbx]; rcx = *begin_list (deference le double pointeur)
    mov [rax + 8], rcx ; nouveau->next = ancien premier (offset 8)

    ;etape 3 mettre a jour le debut de la liste
    mov [rbx], rax ; *begin_list = nouveau

.error:
    ; restaurer les registres
    pop r12
    pop rbx
    ret

