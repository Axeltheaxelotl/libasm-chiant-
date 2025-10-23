global _ft_strlen

_ft_strlen:
	mov		rax, 0
	jmp		enormebite

enormebite:
	cmp		BYTE [rdi + rax], 0
	je		exit
	inc		rax
	jmp		enormebite

exit:
	ret
