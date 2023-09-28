	.file	"sqr.cpp"
	.text
	.p2align 4
	.globl	_Z3sqri
	.type	_Z3sqri, @function
_Z3sqri:
.LFB0:
	.cfi_startproc
	movl	%edi, %eax
	imull	%edi, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	_Z3sqri, .-_Z3sqri
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	movl	$4, %eax
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (mk-2022.0) 11.2.0"
	.section	.note.GNU-stack,"",@progbits
