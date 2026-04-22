.global main
main:
    movq $0x1122334455667788, %rax
    movq $0x1122334455667788, %rbx
    addq %rbx, %rax
    ret

    