interrupt_stub:
    push %rax
    push %rbx
    //push other registers here
    push %r14
    push %r15

    call interrupt_dispatch

    pop %r15
    pop %r14
    //push other registers here
    pop %rbx
    pop %rax

    //remove the vector number + error code
    add $16, %rsp

    iret
