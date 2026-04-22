.data
a:      .long 1,2,3,4
g:      .quad  0x1122334455667788
msg:    .asciz "imprime %c\n"

.text
.global main
main: 
    # rsp= 0x7fffffffdda8
    subq $8, %rsp # rsp= 0x7fffffffdda0 
    movq $g, %rax # rax= 0x404028= &g
    movl g+4, %eax # rax= 0x11223344 
    movq $3, %rbx # rbx= 3
    movb a(,%rbx,4), %al # &a=0x404018 ,rax= 0x404018 + 3*4= 0x404048
    leaq msg, %rdi # rdi= 0x404030
    movb (%rdi, %rbx,2), %sil # sil= %rdi + %rbx*2=0x404030 + 3*2= 0x404036 
    xorl %eax, %eax # eax= 0
    call printf 
    addq $8, %rsp # rsp=0x7fffffffdda8
    ret

# Etiqueta       | Direccion de memoria | Valor almacenado
# msg:                  0x404032            0x70 (p)
# msg+1:                0x404031            0x6d(m)
# msg:                  0x404030            0x69(I)
# g:                    0x40402f            0x11
# g:                    0x40402e            0x22
# g:                    0x40402d            0x33
# g:                    0x40402c            0x44
# g:                    0x40402b            0x55
# g:                    0x40402a            0x66
# g:                    0x404029            0x77
# g:                    0x404028            0x88
# a:                    0x404024            0x04
# a:                    0x404020            0x03
# a:                    0x40401c            0x02
# a:                    0x404018            0x01