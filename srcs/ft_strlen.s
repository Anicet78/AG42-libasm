section .text

global ft_strlen
ft_strlen:
	mov rax, rdi

.lenloop:
	cmp byte [rax], 0
	je .end
	inc rax
	jmp .lenloop

.end:
	sub rax, rdi
	ret
