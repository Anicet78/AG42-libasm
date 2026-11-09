extern malloc

section .text

; rdi -> t_list** begin_list
; rsi -> void* data
; rdx -> t_list* next

global ft_list_push_front
ft_list_push_front:
	test rdi, rdi
	jz .error
	push rdi
	mov rdi, 16
	call malloc wrt ..plt
	test rax, rax
	jz .error
	pop rdi
	mov rdx, [rdi]
	mov [rax], rsi
	mov [rax + 8], rdx
	mov [rdi], rax
	ret

.error:
	ret
