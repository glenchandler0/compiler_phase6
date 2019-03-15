# Function generate called!
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$main.size, %esp
	movl	$10, x
# Unary function call
	movl	x, %eax
	negl	%eax
	movl	%eax, y
# Call generate called!
	pushl	y
	call	print_num
	addl	$4, %esp
# Not call
	movl	y, %edx
	cmpl	$0, %edx
	sete	%dl
	movzbl	%dl, %edx
	movl	%edx, y
# Call generate called!
	pushl	y
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
