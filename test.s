main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$main.size, %esp
	movl	$100, -4(%ebp)
	movl	$3, -8(%ebp)
# GreaterThan call
	movl	-4(%ebp), %eax
	cmpl	-8(%ebp), %eax
	setg	%al
	movzbl	%al, %eax
	movl	%eax, x
	pushl	x
	call	print_num
	addl	$4, %esp
# LessThan call
	movl	-4(%ebp), %eax
	cmpl	x, %eax
	setl	%al
	movzbl	%al, %eax
	movl	%eax, x
	pushl	x
	call	print_num
	addl	$4, %esp
# LessOrEqual call
	movl	-4(%ebp), %eax
	cmpl	-8(%ebp), %eax
	setle	%al
	movzbl	%al, %eax
	movl	%eax, x
	pushl	x
	call	print_num
	addl	$4, %esp
# Equal call
	movl	-8(%ebp), %eax
	cmpl	-8(%ebp), %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, x
	pushl	x
	call	print_num
	addl	$4, %esp
# Not equal call
	movl	-8(%ebp), %eax
	cmpl	-8(%ebp), %eax
	setne	%al
	movzbl	%al, %eax
	movl	%eax, x
	pushl	x
	call	print_num
	addl	$4, %esp
# GreaterOrEqual call
	movl	-4(%ebp), %eax
	cmpl	-8(%ebp), %eax
	setge	%al
	movzbl	%al, %eax
	movl	%eax, x
	pushl	x
	call	print_num
	addl	$4, %esp
	movl	%ebp, %esp
	popl	%ebp
	ret

	.set	main.size, 8
	.globl	main

	.comm	x, 4
