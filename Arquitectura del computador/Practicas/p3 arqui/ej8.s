.global main

main:    
      movl $-1, %eax # Solo para este tamaño el mov pone en 0 la parte alta 
               # del registro
      movl $2, %ecx
      imull %ecx # tengo -2 en eax en 32 bits, quiero extenderlo a 64
      salq $32,%rax
      sarq $32,%rax

      xorq %rax, %rax
      xorq %rdx, %rdx
      movw $-1, %ax  #16 bits, 2 bytes, parte baja de ax (ah/al)
      movw $2, %cx #16 bits, 2 bytes
      mulw %cx #multiplicacion para unsigned
      #la multiplicaccion resulta de 32 bits(4 bytes), los mas significativos estas en dx()
      #los menos significativos en ax

      #extendemos a 32 bits
      movzwl %ax, %eax
      movzwl %dx, %edx
      shll $16, %edx # movemos los 16 bits a la parte alta de edx
      orl %edx, %eax #copiamos en la parte alta de edx la parte alta de eax       
      ret


