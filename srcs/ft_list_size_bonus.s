extern malloc

section .text

; rdi -> t_list* begin_list
; rsi -> current ptr

global ft_list_size
ft_list_size:
	xor eax, eax
	test rdi, rdi
	jz .end

.lstloop:
	inc eax
	mov rsi, [rdi + 8]
	test rsi, rsi
	jz .end
	jmp .lstloop

.end:
	ret
