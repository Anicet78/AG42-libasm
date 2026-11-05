section .text

global ft_atoi_base
ft_atoi_base:
	mov rax, rax

.baseloop:
	mov dl, byte [rsi + rax]
	cmp dl, 0
	je .validbase
	cmp dl, 43
	je .error
	cmp dl, 45
	je .error
	cmp dl, 32
	je .error
	cmp dl, 13
	jle .whitespace
	jmp .doubles

.whitespace:
	cmp dl, 8
	jge .error

.doubles:
	mov rcx, rax
	dec rcx

.doublesloop:
	cmp rcx, 0
	jl .baseloopend
	cmp dl, byte [rsi + rcx]
	je .error
	dec rcx
	jmp .doublesloop

.baseloopend:
	inc rax
	jmp .baseloop

.validbase:
	cmp rax, 1
	jbe .error

.end:
	mov rax, 1
	ret

.error:
	xor rax, rax
	ret
