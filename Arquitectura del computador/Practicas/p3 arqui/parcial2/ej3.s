.data
str1:   .long 1,2,3,4
g:      .quad 0x1122334455667788
msg:    .asciz  "Hola mundo"

.text
.global main
main:
    movl    str1, %eax    # rax= 0x0000000000000001
    movl    str1+4, %eax  # rax= 0x0000000000000002
    movb    str1+16, %al  # rax= 0x0000000000000088
    movq    $3, %rbx      # rbx= 0x0000000000000003
    movb    str1(,%rbx,4), %al  # rax= 0x0000000000000004
    leaq    msg, %rax   # rax= 0x00000000404040
    movb    g(,%rbx, 1), %al # rax= 0x00000000404055
    movl    $0, %eax    #   rax= 0x0
    ret

