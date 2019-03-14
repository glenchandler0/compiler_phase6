main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$main.size, %esp
# Assign called!
	movl	$11, a
# End assign!
# Assign called!
	movl	$2, b
# End assign!
# Assign called!
# Divide called!
	movl	a, %eax
	movl	%eax, %edx
	sarl	$31, %edx
	idivl	b
	movl	%eax, c
# End assign!
# Assign called!
# Remainder called!
	movl	%eax, -4(%ebp)
	movl	a, %eax
	movl	%edx, -8(%ebp)
	movl	%eax, %edx
	sarl	$31, %edx
	idivl	b
	movl	%edx, d
# End assign!
	movl	%ebp, %esp
	popl	%ebp
	ret

	.set	main.size, 0
	.globl	main

	.comm	a, 4
	.comm	b, 4
	.comm	c, 4
	.comm	d, 4
