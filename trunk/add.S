#
# add.S
#

    .include    "common.S"

#ifdef X86_64
    expfun      adds64s64
    expfun      addu64u64
#else
    .globl      _adds64s64
    .globl      _addu64u64
#endif

    expfun      adds32s32
    expfun      addu32u32

    .text

#ifdef X86_64
    defun       adds64s64
    movq        %rdi, %rax
    addq        %rsi, %rax
    jno         out_s64s64
    orl         $1, (%rdx)
out_s64s64:
    ret
    funsz       adds64s64

    defun       addu64u64
    movq        %rdi, %rax
    addq        %rsi, %rax
    jnc         out_u64u64
    orl         $1, (%rdx)
out_u64u64:
    ret
    funsz       addu64u64

    defun       adds32s32
    movl        %edi, %eax
    addl        %esi, %eax
    jno         out_s32s32
    orl         $1, (%rdx)
out_s32s32:
    ret
    funsz       adds32s32

    defun       addu32u32
    movl        %edi, %eax
    addl        %esi, %eax
    jnc         out_u32u32
    orl         $1, (%rdx)
out_u32u32:
    ret
    funsz       addu32u32

#else
    defun       _adds64s64
    movl        4(%esp), %eax
    movl        8(%esp), %ecx
    movl        20(%esp), %edx
    addl        %ecx, %eax
    movl        %eax, (%edx)
    movl        12(%esp), %eax
    movl        16(%esp), %ecx
    movl        24(%esp), %edx
    adcl        %ecx, %eax
    movl        %eax, (%edx)
    jno         out_s64s64
    movl        28(%esp), %edx
    orl         $1, (%edx)
out_s64s64:
    ret

    defun       _addu64u64
    movl        4(%esp), %eax
    movl        8(%esp), %ecx
    movl        20(%esp), %edx
    addl        %ecx, %eax
    movl        %eax, (%edx)
    movl        12(%esp), %eax
    movl        16(%esp), %ecx
    movl        24(%esp), %edx
    adcl        %ecx, %eax
    movl        %eax, (%edx)
    jnc         out_u64u64
    movl        28(%esp), %edx
    orl         $1, (%edx)
out_u64u64:
    ret

    defun       adds32s32
    movl        4(%esp), %eax
    movl        8(%esp), %ecx
    addl        %ecx, %eax
    jno         out_s32s32
    movl        12(%esp), %edx
    orl         $1, (%edx)
out_s32s32:
    ret
    funsz       adds32s32

    defun       addu32u32
    movl        4(%esp), %eax
    movl        8(%esp), %ecx
    addl        %ecx, %eax
    jnc         out_u32u32
    movl        12(%esp), %edx
    orl         $1, (%edx)
out_u32u32:
    ret
    funsz       addu32u32

#endif

# vi: set expandtab sw=4 ts=4:
