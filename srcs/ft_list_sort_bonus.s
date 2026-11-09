section .text

; rdi -> t_list** begin_list
; rsi -> t_list* current
; rdx -> t_list* next
; rcx -> int (*cmp)(void* data1, void* data2)

global ft_list_sort
ft_list_sort:
	test rdi, rdi
	jz .end
	mov rcx, rsi
	mov rsi, [rdi]
	test rsi, rsi
	jz .end

.lstloop:
	mov rdx, [rsi + 8]
	test rdx, rdx
	jz .end
	push rdi
	push rsi
	push rdx
	push rcx
	mov rdi, [rsi]
	mov rsi, [rdx]
	call rcx
	pop rcx
	pop rdx
	pop rsi
	pop rdi
	test rax, rax
	jg .sort
	mov rsi, rdx
	jmp .lstloop

; sort
; r8 -> t_list* current
; r9 -> t_list* next
.sort_init:
	mov r8, [rdi]

.sort_next:
	cmp r8, rdx
	je .lstloop
	mov r9, [r8 + 8]
	push rdi
	push rsi
	push rdx
	push rcx
	push r8
	push r9
	mov rdi, [r8]
	mov rsi, [r9]
	call rcx
	pop r9
	pop r8
	pop rcx
	pop rdx
	pop rsi
	pop rdi
	mov r8, r9
	test rax, rax
	jg .sort_next

.end:
	ret
