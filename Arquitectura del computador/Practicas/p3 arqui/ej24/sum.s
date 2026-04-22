.text 
.global sum
.type sum, @function
# float* a, float* b, int len
sum:
    # prologo
    pushq %rbp
    movq %rsp,%rbp
    subq $16, %rsp
    movq %rdi, -8(%rbp)
    movq %rsi, -16(%rbp)
    movq $0, %rcx
    
for: 
    movq -8(%rbp), %rax
    movq -16(%rbp), %rbx
    movss (%rax,%rcx,4),%xmm0 # int a[0]=> float a[o]
    movss (%rbx,%rcx,4), %xmm1
    addss %xmm1, %xmm0
    movss %xmm0, (%rax,%rcx,4)
    incq %rcx
    cmp %rcx, %rdx
    ja for
    # epilogo
    movq %rbp, %rsp
    popq %rbp
    ret