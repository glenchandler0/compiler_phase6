# Function generate called!
foo2:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$foo2.size, %esp
# Return call
	movl	$2, %eax
	jmp	.L0
.L0:
	movl	%ebp, %esp
	popl	%ebp
	ret

	.set	foo2.size, 0
	.globl	foo2

# Function generate called!
foo:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$foo.size, %esp
# Return call
# Multiply call
	movl	8(%ebp), %eax
	imull	8(%ebp), %eax
	jmp	.L1
.L1:
	movl	%ebp, %esp
	popl	%ebp
	ret

	.set	foo.size, 0
	.globl	foo

# Function generate called!
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$main.size, %esp
	movl	$3, %eax
	movl	%eax, x
# Call generate called!
	pushl	x
	call	foo
	addl	$4, %esp
	movl	%eax, x
# Call generate called!
	pushl	x
	call	print_num
	addl	$4, %esp
.L2:
	movl	%ebp, %esp
	popl	%ebp
	ret

	.set	main.size, 0
	.globl	main

	.comm	x, 4
	.comm	y, 4
	.data
