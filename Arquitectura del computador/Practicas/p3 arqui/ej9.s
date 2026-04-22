.data
a:      .word -1
b:      .byte 0xaa, 99
c:      .float 1.5
strt:    .asciz "Hola mundo\n"
.text
.global main
main:
    leaq a, %rdx
    movw (%rdx), %ax # ax= 0xffff
    movb b+1(%rip), %al # al=0x63
    movl strt, %esi
    movl c, %edi
    
    ret
# Etiqueta       | Direccion de memoria | Valor almacenado
# str:                  0x404019              o
# str:                  0x404018              H
# c:                    0x404014             1.5
# b:                    0x404013             99
# b:                    0x404012            -86
# a:                    0x404010            -1
#
#
#
#
#
#
#
#
