.global main
main:
        MOV     r0, #5              @ movimiento con inmediato
        MOV     r1, #3              @ otro movimiento

        ADD     r2, r0, r1          @ aritmética: r2 = 5 + 3
        SUB     r3, r2, #1          @ aritmética con inmediato: r3 = 8 - 1

        ORR     r4, r3, #0x10       @ lógica: OR con un inmediato
        AND     r5, r4, r1, LSL #1  @ lógica con barrel shifter:
                                     @ r5 = r4 AND (r1 << 1)

        CMP     r5, #20             @ comparación con inmediato
        BGT     mayor               @ ramificación si r5 > 20

        MOV     r6, #0              @ si no es mayor, poner 0 en r6
        B       fin

mayor:
        MOV     r6, #1              @ si es mayor, poner 1 en r6

fin:
                                    @ fin del ejemplo

        BX LR                       @ retorna
