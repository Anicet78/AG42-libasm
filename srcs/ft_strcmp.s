section .text

global ft_strcmp

ft_strcmp:
.loop:
	movzx eax, byte [rdi]
	movzx edx, byte [rsi]

	cmp eax, edx
	jne .diff

	test eax, eax
	jz .end

	inc rdi
	inc rsi
	jmp .loop

.diff:
	sub eax, edx

.end:
	ret
