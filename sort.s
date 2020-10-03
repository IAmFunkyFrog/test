	.file	"sort.c"
	.text
	.globl	sort
	.def	sort;	.scl	2;	.type	32;	.endef
	.seh_proc	sort
sort:
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$40, %rsp
	.seh_stackalloc	40
	.seh_endprologue
	movq	%rdx, %rsi
	leaq	-8(%rdx), %rax
	cmpq	%rcx, %rax
	jbe	.L1
	subq	%rcx, %rdx
	sarq	$3, %rdx
	movq	%rdx, %r8
	shrq	$63, %rdx
	addq	%r8, %rdx
	sarq	%rdx
	movq	(%rcx,%rdx,8), %r8
	movq	%rcx, %rbx
.L3:
	movq	(%rbx), %rdx
	cmpq	%rdx, %r8
	jle	.L8
.L4:
	addq	$8, %rbx
	movq	(%rbx), %rdx
	cmpq	%r8, %rdx
	jl	.L4
.L8:
	movq	(%rax), %r9
	cmpq	%r9, %r8
	jge	.L5
.L6:
	subq	$8, %rax
	movq	(%rax), %r9
	cmpq	%r8, %r9
	jg	.L6
.L5:
	cmpq	%rax, %rbx
	jbe	.L12
.L7:
	leaq	8(%rax), %rdx
	call	sort
	movq	%rsi, %rdx
	movq	%rbx, %rcx
	call	sort
	nop
.L1:
	addq	$40, %rsp
	popq	%rbx
	popq	%rsi
	ret
.L12:
	movq	%r9, (%rbx)
	movslq	%edx, %rdx
	movq	%rdx, (%rax)
	addq	$8, %rbx
	subq	$8, %rax
	cmpq	%rax, %rbx
	jbe	.L3
	jmp	.L7
	.seh_endproc
	.ident	"GCC: (x86_64-posix-seh-rev0, Built by MinGW-W64 project) 8.1.0"
