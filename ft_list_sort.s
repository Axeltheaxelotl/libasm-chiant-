; void ft_list_sort(t_list **begin_list, int (*cmp)());

global ft_list_sort


ft_list_sorl ; (premier noeud)
    ;verfier si la liste est vide ou NULL 
    test rax, rax ; verifi si la liste et NULL
    jz .c_la_fin ; si NULL return

    mov rax, [rdi] ; rdi = 1ere noeud de la list 
    test rax, rax ; verifie si le premier noeud et vide
    jz .c_la_fin



;boucle extern - repete jusqu a aucun echange
.boucle.externe
    xor r8, r8 ; r8 = flag a echange =  (faux)
    mov r9, [rdi] ;r9  current = 1ere noued de la liste

;boucle interne - parcourir tous les elements de la liste
.boucle.interne
    mov r10, [r9 + 8] ;r10 = suivant
    test r10, r10 ;verifie si le suivant est null
    jz .verifie_si_echange ; si null on atteint la fin de la liste

    ; apple fonction de comparaison
    ; sauvegarder les registre avant l appel de fonction
    ; parceque la fonction cmp peu changer les registres, a bon ? bas oui mdr hahaha
    push rdi ; sauvegarde begin list
    push rsi ; sauvegarde cmp (pointeur fonction)
    push r8 ; sauvegarde le putain de drapeau 
    push r9  ; sauvegarde du putain de courant
    push r10 ; sauvegarde du putain de suivant

    ;preparer les fils de pute d arguments pour cmp