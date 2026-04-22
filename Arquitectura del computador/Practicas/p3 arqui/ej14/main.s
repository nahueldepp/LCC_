.data
str_1:  .asciz "Cantidad de argumentos ingresados: %d. La suma es %d\n"
str_2:  .asciz "Ingrese al menos un argumento\n"

.text
.global main
main:
    # prologo
    pushq %rbp # guardamos el registro rbp(base de la pila)
    movq %rsp, %rbp # modificamos el inicio de la pila
    cmpq $1, %rdi # chequea la cantidad de argumentos
    jle print_str_2 # si son 1 o menos salta a str_2
    subq $16, %rsp # reservamos dos espacios en la pila, uno para la cantidad
    # de argumentos(rdi) y otro para el puntero al array de los mismos (rdi)
    decq %rdi # decremento la cantidad de argumentos para luego ubicarlos correctamente
    movq %rdi, -8(%rbp) # guardo la cantidad de argumentos en la pila
    movq %rsi, -16(%rbp) # guardo el puntero al array de argumentos en la pila
    movq -8(%rbp), %r12

    movq -16(%rbp), %rbx # puntero de argv
    xor %rax, %rax
convertir_caracteres: 
    movq (%rbx,%r12,8), %rdi # movemos &argv[rcx]= rdi
    call atoi   # rax ahora es el valor númerico
    pushq %rax # pusheo el valor en la pila
    decq %r12
    cmpq $1, %r12 # solo quiero los argumentos de [1,n-1]
    jae convertir_caracteres # convierto todos los caracteres en enteros y los apilo

    movq -8(%rbp), %rcx # receteamos rcx al número de argumentos
    movq $0, %rbx # se usara rbx para almacenar la suma 
suma: 
    popq %rax # desapilamos los argumentos
    mul %rax # %rax*%rax
    addq %rax, %rbx # a1^2+ rbx
    loop suma

    movq %rbx, %rdx # colocamos en rdx para pasarlo a printf (tercer argumento)

print_str_1:
    movq $str_1, %rdi # string a imprimir
    movq -8(%rbp), %rsi # prier argumento del string (cantidad de argumentos)
    call printf
    jmp fin

print_str_2: 
    movq $str_2, %rdi
    call printf

fin: 
    movq %rbp, %rsp
    popq %rbp
    ret



