;rdi = pointeur vers string
;rax = pointeur apres les espaces
skip_whitespaces:
    mov rax, rdi ; copier le pointeur

.loop:
    movzx rcx, byte [rax]

    ; tester si c un espaces blanche
    cmp cl, ' '
    je .skip
    cmp cl, 9
    je .skip
    cmp cl, 10
    je .skip
    cmp cl, 11
    je .skip
    cmp cl, 12
    je .skip
    cmp cl, 13
    je .skip

    ret ; ce n est pas un espace, on retourne

.skip:
    inc rax ; avance au caratere suivant
    jmp .loop




; rdi = pointeur vers string
; rax = pointeur apres les signes
; rdx = sign (1 ou -1)
parse_sign:
    mov rax, rdi ; copier le pointeur
    mov rdx, 1 ; sign positif par defaut

.loop:
    movzx rcx, byte [rax]; charger le caractere
    cmp cl , '+'
    je .skip ; ne change rien skip
    cmp cl, '-'
    jne .done ; ni + ni -, on a fini
    neg rdx ; inverse le signe

.skip:
    inc rax ; caractere suivant
    jmp .loop

.done:
    ret





; dil = caractere a chercher
; rsi = pointeur vers base
; rdx = longeur de la base
; sortie rax = index du caracetere, ou -1 si pas trouve
find_in_base:
    xor rax, rax ; index = 0

.loop:
    cmp rax, rdx ; esque la bases et parcourue en entier ?
    jge .not_found
    movzx rcx, byte [rsi + rax] ; caractere de la base a l index rax
    cmp dil, cl ; esque c celui que je recherche
    je .found
    inc rax ;index++
    jmp .loop

.not_found:
    mov rax, -1 ; retourner -1

.found:
    ret














;rdi = pointeur vers base
;rax = longeur si valide, sinon 0
validate_base:
    push rbx
    push r12
    mov r12, rdi ; suavgarde le pointeur base
    xor rax, rax ; compteur = 0
    ; verifie si la base est vide
    cmp byte [r12], 0
    je .invalid

;etape 1 compter la longeur
.count_loop:
    cmp byte [r12 + rax], 0 ; fin de string ?
    je .count_done
    inc rax
    jmp .count_loop

.count_done:
    cmp rax, 2 ; longeur < 2 ?
    jl .invalid

    mov rbx, rax ; rbx = longeur de la base
    xor rcx, rcx ; rcx = index du caractere a verifier

;etapes 2 verifier chaque caractere
.check_loop:
    cmp rcx, rbx
    jge .valid ; tous les fils de pute de caracteres sont verifier

    movzx rdi, byte [r12 + rcx] ; changer caractere actuel
    ;verifie les caracteres interdits
    cmp dil, '+'
    je .invalid
    cmp dil, '-'
    je .invalid
    cmp dil, ' '
    je .invalid
    cmp dil, 9
    je .invalid
    cmp dil, 10
    je .invalid
    cmp dil, 11
    je .invalid
    cmp dil, 12
    je .invalid
    cmp dil, 13
    je .invalid

; etape 3 verifier les doublons
    lea rdx, [rcx + 1] ; rdx = index de comparaison

.check_duplicates:
    cmp rdx, rbx
    jge .next_char ;tous les suivants verifier
    movzx rax, byte [r12 + rdx] ; caractere a comparer
    cmp dil, al ; doublon ?
    je .invalid
    inc rdx
    jmp .check_duplicates

.next_char:
    inc rcx
    jmp .check_loop

.valid:
    mov rax, rbx ; retourne la longeur
    jmp .end

.invalid:
    xor rax, rax ; retourne 0

.end:
    pop r12
    pop rbx
    ret










; rdi = pointeur vers string
; rsi = pointeur vers base
; rdx = longeur de la base
; rax = nombre converti
convert_number:
    push rbx
    push r12
    push r13
    push r14

    mov r12, rdi ; string
    mov r13, rsi ; base
    mov r14, rdx ; longeur de la base
    xor rax, rax ; resultat = 0
    xor rbx, rbx ; index dans string = 0

.loop:
    movzx rdi, byte [r12 + rbx]; ca c le caractere actuel ma biche
    test dil, dil ; fin de string ?
    jz .done

    ;trouver la valeur de ce caractere dans la base
    mov rsi, r13 ; base
    mov rdx, r14 ; longeur
    push rax; sauvegard du result
    call find_in_base
    mov rcx, rax ; rcx = valeur fu caractere
    pop rax ; restaurer le result
    cmp rcx, -1 ; caractere pas dans la base ?
    je .done ; tu art
    ;algo result = result * base + valeur
    imul rax, r14 ; result *= longeur_base
    add rax, rcx ; reslut += valeur
    inc rbx ; index++
    jmp .loop

.done:
    pop r14
    pop r13
    pop r12
    pop rbx
    ret




global ft_atoi_base

;entree: rdi = string, rsi = base
;rax = nombre converti
ft_atoi_base:
    ;sauvegarder les registres utilisees
    push rbx
    push r12
    push r13
    push r14
    push r15

    mov r12, rdi ; r12 = string
    mov r13, rsi ; r13 = base

    ;etape 1 valider la putain de base de mes couilles
    mov rdi, rsi
    call validate_base
    test rax, rax ; base invalide ?
    jz .return_zero
    mov r14, rax ; r14 = longeur de la base

    ;etape 2 ignorer les putains d espace de mes couilles
    mov rdi, r12
    call skip_whitespaces
    mov r12, rax ; r12 = pointeur apres espaces

    ;etape 3 gerer les putains de signe de mes couilles
    mov r15, 1 ; sign par default
    mov rdi, r12
    call parse_sign
    mov r12, rax ; r12 = pointeur apres signes
    mov r15, rdx ; r15 = sign (-1 ou 1)

    ;etape 4 convertir le putain de nombre de mes couilles
    mov rdi, r12
    mov rsi, r13
    mov rdx, r14
    call convert_number

    ;la putain d etape 5 appliquer le putain de signe de mes couilles
    imul rax, r15
    jmp .return

.return_zero:
    xor rax, rax

.return:
    ; restaurer les registres
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbx
    ret



