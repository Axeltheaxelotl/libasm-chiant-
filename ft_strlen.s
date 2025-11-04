; Calcule la longueur d'une chaîne de caractères
global ft_strlen

ft_strlen:
	mov		rax, 0
	jmp		enormebite

enormebite:
	cmp		BYTE [rdi + rax], 0
	je		exit
	inc		rax
	jmp		enormebite

exit:
	ret
