extern malloc
extern ft_strlen
extern ft_strcpy

section .text

global ft_strdup
ft_strdup:
	call ft_strlen
	push rdi
	mov rdi, rax
	call malloc wrt ..plt
	test rax, rax
	jz .error
	pop rdi
	mov rsi, rdi
	mov rdi, rax
	call ft_strcpy

.error:
	ret
