global _ft_write

_ft_write:
    mov rax, 1
    syscall
    cmp rax, 0
    jl error
    ret

error:
    mov rax, -1
    ret