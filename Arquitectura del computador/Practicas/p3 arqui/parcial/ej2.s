.data
a:  .word -1,-2,0xff,0xab
b:  .quad 0x12345678
str1:   .asciz "%d\n"

.text
.global main
main:
    movl a, %eax
    movq $a, %rbx
    movl $3, %ecx
    movw (%rbx,%rcx,1), %ax 
    movb 0x5(%rbx), %al
    leaq b, %rbx
    movl (%rbx,%rcx,1), %eax
    movl $-1, %r8d
    imull %r8d
    ret 