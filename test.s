# Function generate called!
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$main.size, %esp
	movl	$2, z
# Cast call
	movsd	a, %xmm0
	cvttsd2si	%xmm0, %eax
	movl	%eax, z
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
	.comm	a, 8
