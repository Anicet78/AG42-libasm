section .text

global ft_strcpy
ft_strcpy:
	mov rax, rdi

.cpyloop:
	mov dl, [rsi]
	mov [rdi], dl
	test dl, dl
	je .end
	inc rdi
	inc rsi
	jmp .cpyloop

.end:
	ret
