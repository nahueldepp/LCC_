.global  main
main:
         movq $0xFFFFFFFF, %rax #Un número N
         movq $0, %rbx #cantidad de unos en el numero N
         movq $64, %rcx #moviemientos a realizar

while_1:
         cmpq $0, %rcx #comparación de cantidad demmovimientos a realizar
         jz fin 
operacion:
         ror $1, %rax
         adcq $0, %rbx
         decq %rcx
         jmp while_1
fin:

