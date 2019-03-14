main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$main.size, %esp
	movl	$17, -4(%ebp)
	movl	$5, -8(%ebp)
# Remainder call
	movl	-4(%ebp), %eax
	cltd
	movl	-8(%ebp), %ecx
	idivl	%ecx
	movl	%edx, x
	movl	%ebp, %esp
	popl	%ebp
	ret

	.set	main.size, 8
	.globl	main

	.comm	x, 4
