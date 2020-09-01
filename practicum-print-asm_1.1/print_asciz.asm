.cpu cortex-m0
.text
.align 2
.global print_asciz

print_asciz:    
    PUSH { R5, LR}
    MOV R5, R0
loop:
    LDRB R0, [R5]
    ADD R0, R0, #0
    BEQ done
    BL uart_put_char
    ADD R5, R5, #1
    B loop
done:    
    POP { R5, PC }