# Function generate called!
foo:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$foo.size, %esp
	movl	$2, x
# Return call
	movl	x, %eax
	jmp	.L0
	movl	$3, x
.L0:
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
# Call generate called!
	movl	%eax, -4(%ebp)
	call	foo
# Call generate called!
	pushl	x
	movl	%eax, -8(%ebp)
	call	print_num
	addl	$4, %esp
.L1:
	movl	%ebp, %esp
	popl	%ebp
	ret

	.set	main.size, 0
	.globl	main

	.comm	x, 4
