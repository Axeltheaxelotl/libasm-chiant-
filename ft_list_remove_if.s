; ChatGPT : La fonction parcourt la liste chaînée et supprime tous les nœuds dont
; la donnée est égale à la valeur donnée, en libérant proprement leur mémoire
section .text
    global ft_list_remove_if
    extern free

ft_list_remove_if:
    push rbp
    mov rbp, rsp
    push r12
    push r13
    push r14
    push r15
    push rbx

    test rdi, rdi
    jz .return
    
    mov rax, [rdi]
    test rax, rax
    jz .return

    mov r12, rdi
    mov r13, rsi
    mov r14, rdx
    mov r15, rcx

.remove_head:
    mov rbx, [r12]
    test rbx, rbx
    jz .traverse_list

    mov rdi, [rbx]
    mov rsi, r13
    call r14

    test eax, eax
    jnz .traverse_list

    mov rax, [rbx + 8]
    mov [r12], rax

    mov rdi, [rbx]
    call r15

    mov rdi, rbx
    call free wrt ..plt

    jmp .remove_head

.traverse_list:
    mov rbx, [r12]
    test rbx, rbx
    jz .return

    mov rax, [rbx + 8]
    test rax, rax
    jz .return

.check_next_node:
    mov rdi, [rax]
    mov rsi, r13
    push rax
    push rbx
    call r14
    pop rbx
    pop rax

    test eax, eax
    jnz .no_match_move_next

    mov rcx, rax
    mov rax, [rax + 8]
    mov [rbx + 8], rax

    push rax
    push rbx
    mov rdi, [rcx]
    call r15
    
    mov rdi, rcx
    call free wrt ..plt
    pop rbx
    pop rax

    test rax, rax
    jz .return
    jmp .check_next_node

.no_match_move_next:
    mov rbx, rax
    mov rax, [rax + 8]
    test rax, rax
    jnz .check_next_node

.return:
    pop rbx
    pop r15
    pop r14
    pop r13
    pop r12
    pop rbp
    ret