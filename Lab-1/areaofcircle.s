	.file	"areaofcircle.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC2:
	.ascii "The area of circle is %f\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB10:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$48, %esp
	call	___main
	flds	LC0
	fstps	44(%esp)
	flds	44(%esp)
	fldl	LC1
	fmulp	%st, %st(1)
	flds	44(%esp)
	fmulp	%st, %st(1)
	fstps	40(%esp)
	flds	40(%esp)
	fstpl	4(%esp)
	movl	$LC2, (%esp)
	call	_printf
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE10:
	.section .rdata,"dr"
	.align 4
LC0:
	.long	1084227584
	.align 8
LC1:
	.long	-1065151889
	.long	1074340298
	.ident	"GCC: (MinGW.org GCC-6.3.0-1) 6.3.0"
	.def	_printf;	.scl	2;	.type	32;	.endef
