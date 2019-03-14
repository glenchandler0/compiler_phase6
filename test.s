main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$main.size, %esp
	movl	$2, -4(%ebp)
	movl	$3, -8(%ebp)
# Add function call
	movl	-4(%ebp), %eax
	addl	-8(%ebp), %eax
	movl	%eax, x
	movl	%ebp, %esp
	popl	%ebp
	ret

	.set	main.size, 8
	.globl	main

	.comm	x, 4
