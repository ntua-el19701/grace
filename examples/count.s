	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"count.ll"
	.def	main;
	.scl	2;
	.type	32;
	.endef
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
main:                                   # @main
.seh_proc main
# %bb.0:                                # %entry
	pushq	%rbp
	.seh_pushreg %rbp
	pushq	%rsi
	.seh_pushreg %rsi
	pushq	%rdi
	.seh_pushreg %rdi
	subq	$32, %rsp
	.seh_stackalloc 32
	leaq	32(%rsp), %rbp
	.seh_setframe %rbp, 32
	.seh_endprologue
	callq	__main
	movl	$0, .Lvars+92(%rip)
	movl	$42, %edi
	leaq	.Lnl(%rip), %rsi
	testl	%edi, %edi
	jle	.LBB0_3
	.p2align	4, 0x90
.LBB0_2:                                # %body
                                        # =>This Inner Loop Header: Depth=1
	decl	%edi
	movl	.Lvars+92(%rip), %eax
	incl	%eax
	movl	%eax, .Lvars+92(%rip)
	movslq	%eax, %rcx
	callq	writeInteger
	movq	%rsi, %rcx
	callq	writeString
	testl	%edi, %edi
	jg	.LBB0_2
.LBB0_3:                                # %endfor
	xorl	%eax, %eax
	addq	$32, %rsp
	popq	%rdi
	popq	%rsi
	popq	%rbp
	retq
	.seh_endproc
                                        # -- End function
	.lcomm	.Lvars,104,16                   # @vars
	.section	.rdata,"dr"
.Lnl:                                   # @nl
	.asciz	"\n"

