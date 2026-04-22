.data
str_uso: .asciz "Uso: campseino_ruso a b\n"
str_resultado:	.asciz "%d*%d= %d \n"
.text

.global main
uso: 
	push    {lr}
	ldr	r0, =str_uso
	bl	printf
	pop	{lr}
	bx	lr
loop:
	cmp	r5, #1
	addls	r0,r0,r4
	movls	pc, lr
	tst	r5, #1
	addne	r0, r0, r4
	subne	r5, r5, #1
	lsleq	r4, r4, #1
	lsreq	r5, r5, #1
	b	loop
	
main:
        push    {r5,lr}
        /*argc(argument counter) esta en r0 y argv(argument vector) esta en r1 */
        cmp     r0, #3 @prog a b
        blt     uso
	bxlt	lr
	sub	sp, sp, #16 @guardo espacio en la pila
	ldr	r0, [r1, #4]	@cargo el primer argumento en r0
	str	r0, [sp,#4]	@lo guardo en la pila
	ldr	r0, [r1, #8]	@cargo el segundo argumento en r0
	bl	atoi		@llamo a atoi con el segundo argumento
	str	r0, [sp,#8] 	@guardo el segundo argumento como entero	
	mov	r5, r0
	ldr	r0, [sp, #4]	@cargo el primer 
	bl	atoi
	str	r0, [sp,#4]	@guardo el primer argumento como entero
	mov	r4, r0 @cargo el primer argumento como entero
	mov	r0, #0

	bl	loop
	mov	r3, r0
	ldr	r2, [sp,#8]
	ldr	r1, [sp, #4]
	ldr	r0, =str_resultado
	bl printf
	add	sp, sp, #16
        pop     {r5, lr}
	bx lr
