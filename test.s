# Function generate called!
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$main.size, %esp
	movl	$100, x
# If call
# LessThan call
	movl	x, %eax
	cmpl	$20, %eax
	setl	%al
	movzbl	%al, %eax
	cmpl	$0, %eax
	je	.L2
# Call generate called!
	pushl	x
	call	print_num
	addl	$4, %esp
	jmp	.L3
.L2:
	movl	$200, x
# Call generate called!
	pushl	x
	call	print_num
	addl	$4, %esp
.L3:
.L0:
	movl	%ebp, %esp
	popl	%ebp
	ret

	.set	main.size, 0
	.globl	main

	.comm	x, 4
