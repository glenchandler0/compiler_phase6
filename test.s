# Function generate called!
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$main.size, %esp
# Dereference call
# Address call
	movl	x, %eax
	leal	%eax, %eax
	movl	%eax, %edx
	movl	(%edx), %edx
.L0:
	movl	%ebp, %esp
	popl	%ebp
	ret

	.set	main.size, 0
	.globl	main

	.comm	x, 4
	.comm	y, 4
	.comm	z, 4
