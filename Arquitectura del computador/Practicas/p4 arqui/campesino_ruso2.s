.text
    .global campesino_ruso
campesino_ruso:
    push    {lr}            @ guardar retorno
    mov     r2, #0          @ res = 0  (r2)

loop:
    cmp     r1, #1          @ while (j > 1)
    addls   r0, r2, r0      @ si j <= 1: return res + i
    popls   {pc}            @ vuelve (NO es branch; carga PC desde stack)

    tst     r1, #1          @ if (j & 1)
    addne   r2, r2, r0      @   res += i
    subne   r1, r1, #1      @   j -= 1
    moveq   r0, r0, lsl #1  @ else i *= 2
    lsreq   r1, r1, #1      @      j /= 2  (unsigned)

    b       loop            @ <- ÚNICO salto explícito
