; Lit depuis un descripteur de fichier (wrapper syscall read)

section .text
    global ft_read 

ft_read:
    mov rax, 0
    syscall
    cmp rax, 0
    jl error
    ret

error:
    mov rax, -1
    ret