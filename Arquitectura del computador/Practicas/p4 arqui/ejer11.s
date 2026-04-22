.data
str_resultado:	.asciz	"det= %d\n"
str_uso:	.asciz	"Uso: ejer11.o a b c d\n"
.text
.global main


uso:
	push 	{lr}
	ldr	r0, =str_uso
	bl	printf
	pop	{lr}
	bx	lr
det:
	mul	r3, r3, r6
	mul	r4, r5, r4
	sub	r3, r3, r4
	mov	r0, r3
	bx lr
main:
	push	{lr}
	cmp	r0, #5
	bllt	uso
	poplt	{lr}
	bxlt	lr
	sub	sp, sp, #16
	ldmia	r1,{r2-r7}
	@ Cargo a como entero
	mov	r0,r3
	bl	atoi
	str	r0, [sp,#12] @guardo el primer argumento en la pila
	@ b como entero
	mov	r0,r4
	bl	atoi
	str	r0, [sp,#8]
	@ c como entero
	mov	r0,r5
	bl 	atoi
	str	r0, [sp, #4]
	@ de como entero
	mov	r0,r6
	bl	atoi
	str	r0, [sp]
	
	ldmia	sp!, {r3-r6}
	bl	det
	mov	r1, r0
	ldr	r0, =str_resultado
	bl 	printf
	pop	{lr}
	bx	lr
