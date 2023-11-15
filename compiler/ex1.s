	.text
	.def	@feat.00;
	.scl	3;
	.type	0;
	.endef
	.globl	@feat.00
.set @feat.00, 0
	.file	"Grace program"
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
	subq	$32, %rsp
	.seh_stackalloc 32
	leaq	32(%rsp), %rbp
	.seh_setframe %rbp, 32
	.seh_endprologue
	callq	__main
	callq	main.1
	xorl	%eax, %eax
	addq	$32, %rsp
	popq	%rbp
	retq
	.seh_endproc
                                        # -- End function
	.def	main.1;
	.scl	2;
	.type	32;
	.endef
	.globl	main.1                          # -- Begin function main.1
	.p2align	4, 0x90
main.1:                                 # @main.1
.seh_proc main.1
# %bb.0:                                # %main.1-entry
	pushq	%rsi
	.seh_pushreg %rsi
	subq	$32, %rsp
	.seh_stackalloc 32
	.seh_endprologue
	movb	$97, .Lvars_int(%rip)
	movl	$5, %ecx
	callq	writeInteger
	leaq	.Lnl(%rip), %rsi
	movq	%rsi, %rcx
	callq	writeString
	leaq	.LvarName(%rip), %rcx
	callq	writeString
	movq	%rsi, %rcx
	callq	writeString
	nop
	addq	$32, %rsp
	popq	%rsi
	retq
	.seh_endproc
                                        # -- End function
	.lcomm	.Lvars_int,20,16                # @vars_int
	.lcomm	.Lvars_char,6,16                # @vars_char
	.lcomm	.LArray_Int_vars,20,16          # @Array_Int_vars
	.lcomm	.LArray_Char_vars,5,16          # @Array_Char_vars
	.section	.rdata,"dr"
.Lnl:                                   # @nl
	.asciz	"\n"

.LvarName:                              # @varName
	.asciz	"\"hi\""

