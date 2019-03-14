main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$main.size, %esp
	movl	$2, -4(%ebp)
	movl	$3, -8(%ebp)
# Add call
	movl	0x15a2c20, %eax
	addl	0x15a2c70, 0x15a2c20
	movl	%ebp, %esp
	popl	%ebp
	ret

	.set	main.size, 8
	.globl	main

	.comm	x, 4
