interrupt_stub:
    push %rax
    push %rbx
    push %rcx
    push %rdx
    push %rbp
    push %rdi
    push %rsi

    push %fs
    push %gs

    push %r8
    push %r9
    push %r10
    push %r11
    push %r12
    push %r13
    push %r14
    push %r15

    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    mov %rsp, %rdi
    call interrupt_dispatch
    mov %rax, %rsp

    pop %r15
    pop %r14
    pop %r13
    pop %r12
    pop %r11
    pop %r10
    pop %r9
    pop %r8

    pop %gs
    pop %fs

    pop %rsi
    pop %rdi
    pop %rbp
    pop %rdx
    pop %rcx
    pop %rbx
    pop %rax

    //remove the vector number + error code
    add $8, %rsp
    iretq


.align 16
.global vector_0_handler
vector_0_handler:
    // Vector 0 - #DE Divide by 0. No error code so we push one.
    pushq $0
    // Vector Number
    pushq $0
    jmp interrupt_stub

//align to the next 16-byte boundary
.align 16
vector_1_handler:
    // Vector 1 - #DB Debug. No error code so we push one.
    pushq $0
    // Vector Number
    pushq $1
    jmp interrupt_stub

.align 16
vector_2_handler:
    // Vector 2 - #NMI Non-Maskable Input. No error code so we push one.
    pushq $0
    // Vector Number
    pushq 2
    jmp interrupt_stub

.align 16
vector_3_handler:
    // Vector 3 - #BP Breakpoint. No error code so we push one.
    pushq $0
    // Vector Number
    pushq 3
    jmp interrupt_stub

.align 16
vector_4_handler:
    // Vector 4 - #OF Overflow. No error code so we push one.
    pushq $0
    // Vector Number
    pushq 4
    jmp interrupt_stub

.align 16
vector_5_handler:
    // Vector 5 - #BR Bound Range Exceeded. No error code so we push one.
    pushq $0
    // Vector Number
    pushq 5
    jmp interrupt_stub

.align 16
vector_6_handler:
    // Vector 6 - #UD Invalid Opcode. No error code so we push one.
    pushq $0
    // Vector Number
    pushq 6
    jmp interrupt_stub

.align 16
vector_7_handler:
    // Vector 7 - #NM Device not available. No error code so we push one.
    pushq $0
    // Vector Number
    pushq 7
    jmp interrupt_stub

.align 16
vector_8_handler:
    // Vector 8 - #DF Double Fault. Has an error code (always 0).
    // Vector Number
    pushq 8
    jmp interrupt_stub

.align 16
vector_9_handler:
    // Vector 9 - Unused (used to be x87 segment overrun). Still pushing values so that there is a handler function if something completely fucks up.
    pushq $0
    // Vector Number
    pushq 9
    jmp interrupt_stub

.align 16
vector_10_handler:
    // Vector 10 - #TS Invalid TSS. Has an error code.
    // Vector Number
    pushq 10
    jmp interrupt_stub

.align 16
vector_11_handler:
    // Vector 11 - #NP Segment Not Present. Has an error code.
    // Vector Number
    pushq 11
    jmp interrupt_stub

.align 16
vector_12_handler:
    // Vector 12 - #SS Stack-Segment Fault. Has an error code.
    // Vector Number
    pushq 12
    jmp interrupt_stub

.align 16
vector_13_handler:
    // Vector 13 - General Protection Fault. Has an error code.
    // Vector Number
    pushq $13
    jmp interrupt_stub

.align 16
vector_14_handler:
    // Vector 14 - #PF Page Fault. Has an error code.
    // Vector Number
    pushq 14
    jmp interrupt_stub

.align 16
vector_15_handler:
    // Vector 15 - Unused.
    pushq $0
    // Vector Number
    pushq 15
    jmp interrupt_stub

.align 16
vector_16_handler:
    // Vector 16 - #MF x87 FPU Error. No error code so we push one.
    pushq $0
    // Vector Number
    pushq 16
    jmp interrupt_stub

.align 16
vector_17_handler:
    // Vector 17 - #AC Alignment Check. Has an error code (always 0).
    // Vector Number
    pushq 17
    jmp interrupt_stub

.align 16
vector_18_handler:
    // Vector 18 - #MC Machine Check. No error code so we push one.
    pushq $0
    // Vector Number
    pushq 18
    jmp interrupt_stub

.align 16
vector_19_handler:
    // Vector 19 - #XF SIMD (SSE/AVX) error. No error code so we push one.
    pushq $0
    // Vector Number
    pushq 19
    jmp interrupt_stub

// Vectors 20-31 are unused
