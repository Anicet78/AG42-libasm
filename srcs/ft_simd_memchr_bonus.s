section .text

global ft_simd_memchr
ft_simd_memchr:
	xor rax, rax
	movd xmm1, esi
	pshufb  xmm1, xmm1

.memloop:
	cmp rdx, 16
	jb .last
	movdqu xmm0, [rdi]
	pcmpeqb xmm0, xmm1
	pmovmskb eax, xmm0
	bsf eax, eax
	jnz .found
	add rdi, 16
	sub rdx, 16
	jmp .memloop

.last:
	test rdx, rdx
	jz .end
	cmp sil, byte [rdi]
	je .found
	dec rdx
	inc rdi
	jmp .last

.found:
	add rdi, rax
	mov rax, rdi

.end:
	ret
