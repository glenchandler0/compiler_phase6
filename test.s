# Function generate called!
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$main.size, %esp
	movl	$1000, x
# Cast call
	movl	x, %eax
	cvtsi2sd	%eax, %xmm0
	movsd	%xmm0, y
# Cast call
	movsd	y, %xmm1
	cvttsd2si	%xmm1, %eax
	movl	%eax, x
# Call generate called!
	pushl	y
	call	print_double
	addl	$8, %esp
# Call generate called!
	pushl	x
	call	print_num
	addl	$4, %esp
.L0:
	movl	%ebp, %esp
	popl	%ebp
	ret

	.set	main.size, 0
	.globl	main

	.comm	x, 4
	.comm	y, 8
	.comm	z, 1
	.data
