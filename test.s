# Function generate called!
foo2:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$foo2.size, %esp
# Return call
	movl	$2, %eax
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
	movl	$4, -4(%ebp)
# Return call
# Multiply call
	movl	-4(%ebp), %edx
	imull	-4(%ebp), %edx
	movl	%eax, -4(%ebp)
	movl	%edx, %eax
	movl	%ebp, %esp
	popl	%ebp
	ret

	.set	foo.size, 4
	.globl	foo

# Function generate called!
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$main.size, %esp
	movl	$3, x
# Call generate called!
	movl	%eax, -8(%ebp)
	call	foo
	movl	%eax, x
# Call generate called!
	pushl	x
	movl	%eax, -12(%ebp)
	call	print_num
	addl	$4, %esp
# Add call
# Add call
# Add call
# Call generate called!
	movl	%eax, -16(%ebp)
	call	foo
# Call generate called!
	movl	%eax, -20(%ebp)
	call	foo
	movl	-20(%ebp), %edx
	addl	%eax, %edx
# Call generate called!
	movl	%edx, -24(%ebp)
	call	foo
	movl	-24(%ebp), %edx
	addl	%eax, %edx
# Call generate called!
	movl	%edx, -28(%ebp)
	call	foo
	movl	-28(%ebp), %edx
	addl	%eax, %edx
	movl	%edx, y
# Call generate called!
	pushl	y
	movl	%edx, -32(%ebp)
	call	print_num
	addl	$4, %esp
	movl	%ebp, %esp
	popl	%ebp
	ret

	.set	main.size, 0
	.globl	main

	.comm	x, 4
	.comm	y, 4
