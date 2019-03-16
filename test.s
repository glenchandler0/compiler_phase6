# Function generate called!
allocate:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$allocate.size, %esp
	movl	$0, %eax
	movl	%eax, -4(%ebp)
# Cast call
# Call generate called!
# Multiply call
	movl	8(%ebp), %eax
	imull	$4, %eax
	pushl	%eax
	call	malloc
	addl	$4, %esp
	movl	%eax, -8(%ebp)
# While call
.L1:
# LessThan call
	movl	-4(%ebp), %eax
	cmpl	8(%ebp), %eax
	setl	%al
	movzbl	%al, %eax
	cmpl	$0, %eax
	je	.L2
# Call generate called!
# Multiply call
	movl	8(%ebp), %eax
	imull	$4, %eax
	pushl	%eax
	call	malloc
	addl	$4, %esp
#Left is dereference
# Add call
# Multiply call
	movl	-4(%ebp), %edx
	imull	$4, %edx
	movl	-8(%ebp), %ecx
	addl	%edx, %ecx
	movl	%eax, (%ecx)
# Add call
	movl	-4(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -4(%ebp)
	jmp	.L1
.L2:
# Return call
	movl	-8(%ebp), %eax
	jmp	.L0
.L0:
	movl	%ebp, %esp
	popl	%ebp
	ret

	.set	allocate.size, 8
	.globl	allocate

# Function generate called!
initialize:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$initialize.size, %esp
	movl	$0, %eax
	movl	%eax, -4(%ebp)
# While call
.L4:
# LessThan call
	movl	-4(%ebp), %eax
	cmpl	12(%ebp), %eax
	setl	%al
	movzbl	%al, %eax
	cmpl	$0, %eax
	je	.L5
	movl	$0, %eax
	movl	%eax, -8(%ebp)
# While call
.L6:
# LessThan call
	movl	-8(%ebp), %eax
	cmpl	12(%ebp), %eax
	setl	%al
	movzbl	%al, %eax
	cmpl	$0, %eax
	je	.L7
# Add call
	movl	-4(%ebp), %eax
	addl	-8(%ebp), %eax
#Left is dereference
# Add call
# Dereference call
# Add call
# Multiply call
	movl	-4(%ebp), %edx
	imull	$4, %edx
	movl	8(%ebp), %ecx
	addl	%edx, %ecx
	movl	(%ecx), %edx
# Multiply call
	movl	-8(%ebp), %ecx
	imull	$4, %ecx
	addl	%ecx, %edx
	movl	%eax, (%edx)
# Add call
	movl	-8(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -8(%ebp)
	jmp	.L6
.L7:
# Add call
	movl	-4(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -4(%ebp)
	jmp	.L4
.L5:
.L3:
	movl	%ebp, %esp
	popl	%ebp
	ret

	.set	initialize.size, 8
	.globl	initialize

# Function generate called!
display:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$display.size, %esp
	movl	$0, %eax
	movl	%eax, -4(%ebp)
# While call
.L9:
# LessThan call
	movl	-4(%ebp), %eax
	cmpl	12(%ebp), %eax
	setl	%al
	movzbl	%al, %eax
	cmpl	$0, %eax
	je	.L10
	movl	$0, %eax
	movl	%eax, -8(%ebp)
# While call
.L11:
# LessThan call
	movl	-8(%ebp), %eax
	cmpl	12(%ebp), %eax
	setl	%al
	movzbl	%al, %eax
	cmpl	$0, %eax
	je	.L12
# Dereference call
# Add call
# Multiply call
	movl	-4(%ebp), %eax
	imull	$4, %eax
	movl	8(%ebp), %edx
	addl	%eax, %edx
	movl	(%edx), %eax
	movl	%eax, -12(%ebp)
# Call generate called!
# Dereference call
# Add call
# Multiply call
	movl	-8(%ebp), %eax
	imull	$4, %eax
	movl	-12(%ebp), %edx
	addl	%eax, %edx
	movl	(%edx), %eax
	pushl	%eax
# Address call
# String here
	leal	.L13, %edx
	pushl	%edx
	call	printf
	addl	$8, %esp
# Add call
	movl	-8(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -8(%ebp)
	jmp	.L11
.L12:
# Add call
	movl	-4(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -4(%ebp)
# Call generate called!
# Address call
# String here
	leal	.L14, %eax
	pushl	%eax
	call	printf
	addl	$4, %esp
	jmp	.L9
.L10:
.L8:
	movl	%ebp, %esp
	popl	%ebp
	ret

	.set	display.size, 12
	.globl	display

# Function generate called!
deallocate:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$deallocate.size, %esp
	movl	$0, %eax
	movl	%eax, -4(%ebp)
# While call
.L16:
# LessThan call
	movl	-4(%ebp), %eax
	cmpl	12(%ebp), %eax
	setl	%al
	movzbl	%al, %eax
	cmpl	$0, %eax
	je	.L17
# Call generate called!
# Dereference call
# Add call
# Multiply call
	movl	-4(%ebp), %eax
	imull	$4, %eax
	movl	8(%ebp), %edx
	addl	%eax, %edx
	movl	(%edx), %eax
	pushl	%eax
	call	free
	addl	$4, %esp
# Add call
	movl	-4(%ebp), %eax
	addl	$1, %eax
	movl	%eax, -4(%ebp)
	jmp	.L16
.L17:
# Call generate called!
	pushl	8(%ebp)
	call	free
	addl	$4, %esp
.L15:
	movl	%ebp, %esp
	popl	%ebp
	ret

	.set	deallocate.size, 4
	.globl	deallocate

# Function generate called!
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$main.size, %esp
# Call generate called!
# Address call
	leal	-8(%ebp), %eax
	pushl	%eax
# Address call
# String here
	leal	.L19, %edx
	pushl	%edx
	call	scanf
	addl	$8, %esp
# Call generate called!
	pushl	-8(%ebp)
	call	allocate
	addl	$4, %esp
	movl	%eax, -4(%ebp)
# Call generate called!
	pushl	-8(%ebp)
	pushl	-4(%ebp)
	call	initialize
	addl	$8, %esp
# Call generate called!
	pushl	-8(%ebp)
	pushl	-4(%ebp)
	call	display
	addl	$8, %esp
# Call generate called!
	pushl	-8(%ebp)
	pushl	-4(%ebp)
	call	deallocate
	addl	$8, %esp
.L18:
	movl	%ebp, %esp
	popl	%ebp
	ret

	.set	main.size, 8
	.globl	main

	.data
.L13:	.asciz "%d "
.L14:	.asciz "\n"
.L19:	.asciz "%d"
