.data
var:	.word 0x8000
.text	
.global main
main:
 ldr 	r3, =var
 ldr	r3, [r3]
 str	r6, [r3, #12] 	 
 strb	r7, [r3], #4 	
 ldrh	r5, [r3], #8 	
 ldr	r12, [r3, #12]! 
 bx lr

