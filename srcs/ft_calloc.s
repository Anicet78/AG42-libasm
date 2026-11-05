extern malloc
extern ft_strlen
extern ft_strcpy

section .text

global ft_calloc
ft_calloc:
	mov rax, rsi
	mul rdi
	jo .error
	mov rdi, rax
	push rdi
	call malloc wrt ..plt
	test rax, rax
	jz .error
	pop rdi
	mov dl, 0
	dec rdi

.zloop:
	mov [rax + rdi], dl
	dec rdi
	jns .zloop
	ret

.error:
	xor rax, rax
	ret
