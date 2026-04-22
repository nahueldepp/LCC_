.global main
main: 
    movb $-63, %al
    movb $-56, %bl
    add %al, %bl
    ret
