.data
str_rango_i:	.asciz	"i debe estar entre 0 y 31\n"
str_resultado:	.asciz	"El resultado es %d\n"
.text
.global main

aviso:
	push	{lr}
	ldr	r0, =str_rango_i
	bl	printf
	pop	{lr}
	bx	lr

_i2:	
	mov	r1, #2
	mov	r1, r1, lsl r0
	bx	lr
	
main:
	push	{r0,lr}
	cmp	r0, #2
	blne	aviso
	bxne	lr
	ldr	r0, [r1,#4]
	bl	atoi
	bl	_i2
	ldr	r0, =str_resultado
	bl 	printf
	pop	{r0,lr}
	bx lr
