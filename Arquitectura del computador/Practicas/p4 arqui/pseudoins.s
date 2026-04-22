.data
 num:	.word 0x88776655
.text
.global main
main:
	ldr	r0, =0x11223344
 	ldr	r1, =num
	ldr	r3, [r1]
 	bx lr

