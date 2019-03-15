# Function generate called!
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$main.size, %esp
	movl	$3, z
# Address call
	leal	z, %eax
	movl	%eax, y
#Left is dereference
	movl	y, %edx
	movl	$4, (%edx)
# Call generate called!
	pushl	z
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
