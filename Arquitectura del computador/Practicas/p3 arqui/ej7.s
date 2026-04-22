
.global main    
main:
    movq $0x1122334455667788, %rax
    ror $32, %rax
    rol $32, %rax
    adc %rax, %rax

    loop

    w:
    comparacion
    jump fin
    cw:
    hacer iteracion
    jump w
    fin:
    
    ret
