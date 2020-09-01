.cpu cortex-m0
sentence:
    .asciz "Hello world, the ANSWER is 42! @[]`{}~" 
.text
.align 2
.global print_asciz
.global application

application:
    PUSH {LR}
    LDR R0, =sentence
    BL print_asciz
    POP {PC}
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