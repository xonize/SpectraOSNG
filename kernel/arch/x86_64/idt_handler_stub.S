interrupt_stub:
    push %rax
    push %rbx
    //push other registers here
    push %r14
    push %r15

    mov %rsp, %rdi
    call interrupt_dispatch
    mov %rax, %rsp

    pop %r15
    pop %r14
    //push other registers here
    pop %rbx
    pop %rax

    //remove the vector number + error code
    add $16, %rsp

    iret


.align 16
vector_0_handler:
    //vector 0 has no error code
    pushq $0
    //the vector number
    pushq $0
    jmp interrupt_stub

//align to the next 16-byte boundary
.align 16
    vector_1_handler:
    //also needs a dummy error code
    pushq $0
    //vector number
    pushq $1
    jmp interrupt_stub

// skips a whole load
// TODO: implement reserved vectors

.align 16
vector_13_handler:
    //vector 13(#GP) does push an error code
    //so we wont. Just the vector number.
    pushq $13
    jmp interrupt_stub
