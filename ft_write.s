; Écrit dans un descripteur de fichier (wrapper syscall write)
global ft_write

ft_write:
    mov rax, 1
    syscall
    cmp rax, 0
    jl error
    ret

error:
    mov rax, -1
    ret