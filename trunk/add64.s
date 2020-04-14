    .globl  _add64

    .text
_add64:
    mov     %rsi, %rax
    add     %rdx, %rax
    pushf
    pop     %rbx
    and     $0x800, %rbx
    test    %rbx, %rbx
    jne     overflow
    mov     %rax, (%rdi)
    mov     $0, %rax
    ret
overflow:
    mov     $1, %rax
    ret
