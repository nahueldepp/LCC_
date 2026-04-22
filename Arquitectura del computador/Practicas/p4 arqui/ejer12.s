.data 
str_suma:	.asciz "La suma es: %d\n"
a:	.word	1,2,3,4
b:	.word	2,3,4,5

.text
.global main


suma:
	mov	r4, #0 	@i
	mov	r5, #0	@result
loop:	
	cmp	r4, r2
	ldrlt	r6, [r0], #4 @a[i]
	ldrlt	r7, [r1], #4 @b[i]
	addlt	r5, r6, r7
	add	r4, r4 ,#1
	blt	loop
	mov	r0, r5
	bx	lr
main:
	push	{lr}
	mov	r2,#4	@L
	ldr	r0, =a
	ldr	r1, =b
	bl	suma
	mov	r1, r0
	ldr	r0, =str_suma
	bl	printf
	mov	r0,#0 
	pop	{lr}
	bx	lr
