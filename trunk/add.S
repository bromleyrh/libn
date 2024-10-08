#
# add.S
#

#include "arithmetic.S"
#include "common.S"

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
    jno         0f
    orl         $aoverflow, (%rdx)
0:
    ret
    funsz       adds64s64

    defun       addu64u64
    movq        %rdi, %rax
    addq        %rsi, %rax
    jnc         0f
    orl         $aoverflow, (%rdx)
0:
    ret
    funsz       addu64u64

    defun       adds32s32
    movl        %edi, %eax
    addl        %esi, %eax
    jno         0f
    orl         $aoverflow, (%rdx)
0:
    ret
    funsz       adds32s32

    defun       addu32u32
    movl        %edi, %eax
    addl        %esi, %eax
    jnc         0f
    orl         $aoverflow, (%rdx)
0:
    ret
    funsz       addu32u32

#else
    defun       _adds64s64
    pushl       %ebp
    movl        %esp, %ebp
    movl        12(%esp), %eax
    movl        20(%esp), %ecx
    movl        28(%esp), %edx
    addl        %ecx, %eax
    movl        %eax, (%edx)
    movl        8(%esp), %eax
    movl        16(%esp), %ecx
    movl        24(%esp), %edx
    adcl        %ecx, %eax
    movl        %eax, (%edx)
    jno         0f
    movl        32(%esp), %edx
    orl         $aoverflow, (%edx)
0:
    popl        %ebp
    ret

    defun       _addu64u64
    pushl       %ebp
    movl        %esp, %ebp
    movl        12(%esp), %eax
    movl        20(%esp), %ecx
    movl        28(%esp), %edx
    addl        %ecx, %eax
    movl        %eax, (%edx)
    movl        8(%esp), %eax
    movl        16(%esp), %ecx
    movl        24(%esp), %edx
    adcl        %ecx, %eax
    movl        %eax, (%edx)
    jnc         0f
    movl        32(%esp), %edx
    orl         $aoverflow, (%edx)
0:
    popl        %ebp
    ret

    defun       adds32s32
    pushl       %ebp
    movl        %esp, %ebp
    movl        8(%esp), %eax
    movl        12(%esp), %ecx
    addl        %ecx, %eax
    jno         0f
    movl        16(%esp), %edx
    orl         $aoverflow, (%edx)
0:
    popl        %ebp
    ret
    funsz       adds32s32

    defun       addu32u32
    pushl       %ebp
    movl        %esp, %ebp
    movl        8(%esp), %eax
    movl        12(%esp), %ecx
    addl        %ecx, %eax
    jnc         0f
    movl        16(%esp), %edx
    orl         $aoverflow, (%edx)
0:
    popl        %ebp
    ret
    funsz       addu32u32

#endif

# vi: set expandtab sw=4 ts=4:
