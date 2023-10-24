	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"aris.ll"
	.def	main;
	.scl	2;
	.type	32;
	.endef
	.globl	main                            # -- Begin function main
	.p2align	4, 0x90
main:                                   # @main
.seh_proc main
# %bb.0:                                # %main-entry
	pushq	%rbp
	.seh_pushreg %rbp
	subq	$32, %rsp
	.seh_stackalloc 32
	leaq	32(%rsp), %rbp
	.seh_setframe %rbp, 32
	.seh_endprologue
	callq	__main
	movl	$5, .Lvars_int+40(%rip)
	movl	$7, .Lvars_int+48(%rip)
	movl	$5, %ecx
	movl	$7, %edx
	callq	solve
	movl	%eax, .Lvars_int+32(%rip)
	addq	$32, %rsp
	popq	%rbp
	retq
	.seh_endproc
                                        # -- End function
	.def	solve;
	.scl	2;
	.type	32;
	.endef
	.globl	solve                           # -- Begin function solve
	.p2align	4, 0x90
solve:                                  # @solve
# %bb.0:                                # %solve-entry
                                        # kill: def $edx killed $edx def $rdx
                                        # kill: def $ecx killed $ecx def $rcx
	movl	%ecx, .Lvars_int+8(%rip)
	movl	%edx, .Lvars_int+16(%rip)
	leal	(%rcx,%rdx), %eax
	movl	%eax, .Lvars_int+24(%rip)
	retq
                                        # -- End function
	.lcomm	.Lvars_int,44,16                # @vars_int
	.lcomm	.Lvars_char,5,16                # @vars_char
	.section	.rdata,"dr"
.Lnl:                                   # @nl
	.asciz	"\n"

