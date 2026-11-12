extern free

section .text

; rdi -> t_list** begin_list
; rsi -> void* data_ref
; rdx -> int (*cmp)(void *, void *)
; rcx -> void (*free_fct)(void *)
; r8 -> t_list* current
; r9 -> t_list* previous

free_data:
	test rcx, rcx
	jz .no_func
	call rcx

.no_func:
	ret

global ft_list_remove_if
ft_list_remove_if:
	test rdi, rdi
	jz .end
	test rdx, rdx
	jz .end
	mov r8, [rdi]
	xor r9, r9

.lstloop:
	test r8, r8
	jz .end
	push rdi
	push rsi
	push rdx
	push rcx
	push r8
	push r9
	mov rdi, [r8]
	call rdx
	pop r9
	pop r8
	pop rcx
	pop rdx
	pop rsi
	pop rdi
	test eax, eax
	jz .remove
	mov r9, r8
	mov r8, [r8 + 8]
	jmp .lstloop

.remove:
	mov r10, [r8 + 8]
	push rdi
	push rsi
	push rdx
	push rcx
	push r9
	push r10
	push r8
	mov rdi, [r8]
	call free_data
	pop r8
	mov rdi, r8
	call free wrt ..plt
	pop r10
	pop r9
	pop rcx
	pop rdx
	pop rsi
	pop rdi
	test r9, r9
	jz .remove_first
	mov [r9 + 8], r10
	mov r8, r10
	jmp .lstloop

.remove_first:
	mov [rdi], r10
	mov r8, r10
	jmp .lstloop

.end:
	ret
