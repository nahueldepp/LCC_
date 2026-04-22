.data
array: .word 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
ins1: 	.asciz "Instruccion1: %d\n"
ins2:	.asciz "Instruccion2: %d\n"
.text
instruccion1:
	push	{lr} 
	ldr 	r2, =array
        ldr 	r2, [r2,#24]
        add 	r1, r1, r2
	ldr 	r0, =ins1
	bl 	printf
	pop	{lr}
        bx 	lr
instruccion2:
	push	{lr}
	ldr	r2, =array
	ldr	r0, [r2,#20]
	add	r2,#32
	add	r0, r0, r1
	str	r0, [r2]
	ldr	r1, [r2]
	ldr	r0, =ins2
	bl	printf
	pop	{lr}
	bx	lr
	
.global main
main: 
	push 	{lr}
	sub	sp, sp, #12
	movs	r0, #5
	movs	r1, #6
	str	r0, [sp,#8]
	str	r1, [sp,#4]
	bl	instruccion1
	ldr	r1, [sp,#4]
	bl	instruccion2
	add	sp,sp,#12
	pop 	{lr}
	bx lr

