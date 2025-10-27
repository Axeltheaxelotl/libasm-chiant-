global _ft_read

_ft_read:
    mov rax, 0
    syscall
    cmp rax, 0
    jl error
    ret

error:
    mov rax, -1
    ret