# Function generate called!
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$main.size, %esp
# Real here
	movsd	.L1, %xmm0
	movsd	%xmm0, y
# Cast call
# Cast call
	movsd	y, %xmm1
	cvttsd2si	%xmm1, %eax
	movb	%al, z
# Cast call
	movb	z, %al
	movsbl	%al, %eax
	cvtsi2sd	%eax, %xmm1
	movsd	%xmm1, y
# Cast call
	movsd	y, %xmm2
	cvttsd2si	%xmm2, %eax
	movl	%eax, x
# Cast call
	movl	x, %eax
	movb	%al, z
# Cast call
	movl	x, %eax
	cvtsi2sd	%eax, %xmm2
	movsd	%xmm2, y
# Cast call
	movsd	y, %xmm3
	cvttsd2si	%xmm3, %eax
	movl	%eax, x
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
.L1:	.double	3.85391
