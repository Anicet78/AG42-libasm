section .text

; rdi -> t_list** begin_list
; rsi -> t_list* current
; rdx -> t_list* next
; rcx -> int (*cmp)(void* data1, void* data2)

global ft_list_sort
ft_list_sort:
	test rdi, rdi
	jz .end
	test rsi, rsi
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
	test eax, eax
	jg .sort_init
	mov rsi, rdx
	jmp .lstloop

; sort
; r8 -> t_list* current
; r9 -> t_list* next
; r10 -> t_list* previous
; r12 -> t_list* end
.sort_init:
	xor r10, r10
	mov r8, [rdi]

.sort_next:
	cmp r8, [rdx + 8]
	je .sort_finish
	mov r9, [r8 + 8]
	push rdi
	push rsi
	push rdx
	push rcx
	push r8
	push r9
	mov rdi, [rdx]
	mov rsi, [r8]
	call rcx
	pop r9
	pop r8
	pop rcx
	pop rdx
	pop rsi
	pop rdi
	cmp eax, eax
	jle .sort_switch
	mov r10, r8
	mov r8, r9
	jmp .sort_next

.sort_switch:
	mov r11, [rdx + 8]
	mov [rdx + 8], r8
	mov [rsi + 8], r11
	test r10, r10
	jz .sort_first
	mov [r10 + 8], r9
	mov r10, r8
	jmp .sort_finish

.sort_first:
	mov [rdi], rdx
	mov r10, rdx

.sort_finish:
	mov rsi, rdx
	jmp .lstloop

.end:
	ret
