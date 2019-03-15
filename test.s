# Function generate called!
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$main.size, %esp
	movl	$3, z
# Address call
	leal	a, %eax
	movl	%eax, y
# Address call
	leal	y, %edx
	movl	%edx, x
# Dereference call
	movl	x, %ecx
	movl	(%ecx), %ecx
# Address call
	movl	%eax, -4(%ebp)
	leal	z, %eax
	movl	%eax, %ecx
# Call generate called!
# Dereference call
# Dereference call
	movl	%eax, -8(%ebp)
	movl	x, %eax
	movl	(%eax), %eax
	movl	(%eax), %eax
	pushl	%eax
	call	print_num
	addl	$4, %esp
.L0:
	movl	%ebp, %esp
	popl	%ebp
	ret

	.set	main.size, 0
	.globl	main

	.comm	x, 4
	.comm	y, 4
	.comm	z, 4
	.comm	a, 4
