	.text
	.file	"compare.c"
	.globl	main                    # -- Begin function main
	.p2align	4, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# %bb.0:                                # %entry
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movl	$0, -4(%rbp)
	movabsq	$.L.str, %rdi
	movb	$0, %al
	callq	get_int
	movl	%eax, -8(%rbp)
	movabsq	$.L.str.1, %rdi
	movb	$0, %al
	callq	get_int
	movl	%eax, -12(%rbp)
	movl	-8(%rbp), %eax
	cmpl	-12(%rbp), %eax
	jge	.LBB0_2
# %bb.1:                                # %if.then
	movabsq	$.L.str.2, %rdi
	movb	$0, %al
	callq	printf
	movl	%eax, -16(%rbp)         # 4-byte Spill
	jmp	.LBB0_3
.LBB0_2:                                # %if.else
	movabsq	$.L.str.3, %rdi
	movb	$0, %al
	callq	printf
	movl	%eax, -20(%rbp)         # 4-byte Spill
.LBB0_3:                                # %if.end
	movl	-4(%rbp), %eax
	addq	$32, %rsp
	popq	%rbp
	.cfi_def_cfa %rsp, 8
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc
                                        # -- End function
	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	"x: "
	.size	.L.str, 4

	.type	.L.str.1,@object        # @.str.1
.L.str.1:
	.asciz	"y: "
	.size	.L.str.1, 4

	.type	.L.str.2,@object        # @.str.2
.L.str.2:
	.asciz	"x is less than y\n"
	.size	.L.str.2, 18

	.type	.L.str.3,@object        # @.str.3
.L.str.3:
	.asciz	"x is not less than y\n"
	.size	.L.str.3, 22


	.ident	"clang version 7.0.0 (git@github.com:apple/swift-clang.git 47d458b5f9bc87d268c756820ee07dacb21a3309) (git@github.com:apple/swift-llvm.git 34250a6eef79ee8a83c5cfb4deb1583176dcbb63)"
	.section	".note.GNU-stack","",@progbits
	.addrsig
	.addrsig_sym main
	.addrsig_sym get_int
	.addrsig_sym printf
