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
    BL convert
    BL uart_put_char
    ADD R5, R5, #1
    B loop
done:    
    POP { R5, PC }

convert:
    PUSH {R5 , LR}
    MOV R5, R0
    CMP R5, #65
    BLT doneconverting
    CMP R5, #90
    BLT iscap
    CMP R5, #97
    BLT doneconverting
    CMP R5, #122
    BLE isnoncap
    B doneconverting
iscap:
    add R0, #32
    B doneconverting
isnoncap:
    SUB R0, #32
    B doneconverting
doneconverting:
    POP {R5, PC}