.text
.global main
main: 
 mov	r7, #0x8c, 4
 mov	r7, #0x42, 30
 mvn	r7, #2
 mvn	r7, #0x8c, 4
 bx	lr
