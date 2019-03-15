# Function generate called!
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$main.size, %esp
	movl	$1, x
	movl	$0, y
# Call generate called!
# AND call
	movl	x, %eax
	cmpl	$1, %eax
	jne	.L1
	movl	%eax, -4(%ebp)
	movl	y, %eax
	cmpl	$1, %eax
	jne	.L1
	movl	$1, %eax
	jmp	.L2
.L1:
	movl	$0, %eax
.L2:
	pushl	%eax
	call	print_num
	addl	$4, %esp
# Call generate called!
# AND call
# Not call
	movl	y, %edx
	cmpl	$0, %edx
	sete	%dl
	movzbl	%dl, %edx
	movl	%eax, -8(%ebp)
	movl	x, %eax
	cmpl	$1, %eax
	jne	.L3
	movl	%eax, -12(%ebp)
	movl	%edx, %eax
	cmpl	$1, %eax
	jne	.L3
	movl	$1, %eax
	jmp	.L4
.L3:
	movl	$0, %eax
.L4:
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
