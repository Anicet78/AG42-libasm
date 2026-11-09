section .text

; rax -> return
; rdi -> str
; rsi -> base
; dl  -> char
; rcx -> str len
; r8  -> base len
; r9  -> sign

global ft_atoi_base
ft_atoi_base:
	xor r8, r8

.baseloop:
	mov dl, byte [rsi + r8]
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
	mov rcx, r8
	dec rcx

.doublesloop:
	cmp rcx, 0
	jl .baseloopend
	cmp dl, byte [rsi + rcx]
	je .error
	dec rcx
	jmp .doublesloop

.baseloopend:
	inc r8
	jmp .baseloop

.validbase:
	cmp r8, 1
	jbe .error
	xor rax, rax
	mov r9, 1
	xor rcx, rcx

.strloopws:
	mov dl, byte [rdi + rcx]
	cmp dl, 0
	je .error
	cmp dl, 32
	je .strloopend
	cmp dl, 13
	jg .strsign

.strws:
	cmp dl, 8
	jge .strloopend
	jmp .strsign

.strloopend:
	inc rcx
	jmp .strloopws

.strsign:
	cmp dl, 43
	je .strloop
	cmp dl, 45
	je .setsign
	dec rcx
	jmp .strloop

.setsign:
	mov r9, -1

.strloop:
	inc rcx
	xor r10, r10
	mov dl, byte [rdi + rcx]
	cmp dl, 0
	je .end

.basecontainsc:
	cmp r10, r8
	jae .end
	cmp dl, byte [rsi + r10]
	je .stradd
	inc r10
	jmp .basecontainsc

.stradd:
	mul r8
	add rax, r10
	jmp .strloop

.end:
	mul r9
	ret

.error:
	xor rax, rax
	ret
