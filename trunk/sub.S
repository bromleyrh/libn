#
# sub.S
#

#include "arithmetic.S"
#include "common.S"

#ifdef X86_64
    expfun      subs64s64
    expfun      subu64u64
#else
    .globl      _subs64s64
    .globl      _subu64u64
#endif

    expfun      subs32s32
    expfun      subu32u32

    .text

#ifdef X86_64
    defun       subs64s64
    movq        %rdi, %rax
    subq        %rsi, %rax
    jno         0f
    orl         $aoverflow, (%rdx)
0:
    ret
    funsz       subs64s64

    defun       subu64u64
    movq        %rdi, %rax
    subq        %rsi, %rax
    jnc         0f
    orl         $aoverflow, (%rdx)
0:
    ret
    funsz       subu64u64

    defun       subs32s32
    movl        %edi, %eax
    subl        %esi, %eax
    jno         0f
    orl         $aoverflow, (%rdx)
0:
    ret
    funsz       subs32s32

    defun       subu32u32
    movl        %edi, %eax
    subl        %esi, %eax
    jnc         0f
    orl         $aoverflow, (%rdx)
0:
    ret
    funsz       subu32u32

#else
    defun       _subs64s64
    pushl       %ebp
    movl        %esp, %ebp
    movl        12(%esp), %eax
    movl        20(%esp), %ecx
    movl        28(%esp), %edx
    subl        %ecx, %eax
    movl        %eax, (%edx)
    movl        8(%esp), %eax
    movl        16(%esp), %ecx
    movl        24(%esp), %edx
    sbbl        %ecx, %eax
    movl        %eax, (%edx)
    jno         0f
    movl        32(%esp), %edx
    orl         $aoverflow, (%edx)
0:
    popl        %ebp
    ret

    defun       _subu64u64
    pushl       %ebp
    movl        %esp, %ebp
    movl        12(%esp), %eax
    movl        20(%esp), %ecx
    movl        28(%esp), %edx
    subl        %ecx, %eax
    movl        %eax, (%edx)
    movl        8(%esp), %eax
    movl        16(%esp), %ecx
    movl        24(%esp), %edx
    sbbl        %ecx, %eax
    movl        %eax, (%edx)
    jnc         0f
    movl        32(%esp), %edx
    orl         $aoverflow, (%edx)
0:
    popl        %ebp
    ret

    defun       subs32s32
    pushl       %ebp
    movl        %esp, %ebp
    movl        8(%esp), %eax
    movl        12(%esp), %ecx
    subl        %ecx, %eax
    jno         0f
    movl        16(%esp), %edx
    orl         $aoverflow, (%edx)
0:
    popl        %ebp
    ret
    funsz       subs32s32

    defun       subu32u32
    pushl       %ebp
    movl        %esp, %ebp
    movl        8(%esp), %eax
    movl        12(%esp), %ecx
    subl        %ecx, %eax
    jnc         0f
    movl        16(%esp), %edx
    orl         $aoverflow, (%edx)
0:
    popl        %ebp
    ret
    funsz       subu32u32

#endif

# vi: set expandtab sw=4 ts=4:
