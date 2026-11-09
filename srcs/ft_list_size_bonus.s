section .text

; rdi -> t_list* begin_list
; rsi -> t_list* current ptr

global ft_list_size
ft_list_size:
	xor eax, eax
	test rdi, rdi
	jz .end

.lstloop:
	inc eax
	mov rdi, [rdi + 8]
	test rdi, rdi
	jnz .lstloop

.end:
	ret
