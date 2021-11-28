#
# sub.S
#

    .include    "common.S"

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
    jno         out_s64s64
    orl         $1, (%rdx)
out_s64s64:
    ret
    funsz       subs64s64

    defun       subu64u64
    movq        %rdi, %rax
    subq        %rsi, %rax
    jnc         out_u64u64
    orl         $1, (%rdx)
out_u64u64:
    ret
    funsz       subu64u64

    defun       subs32s32
    movl        %edi, %eax
    subl        %esi, %eax
    jno         out_s32s32
    orl         $1, (%rdx)
out_s32s32:
    ret
    funsz       subs32s32

    defun       subu32u32
    movl        %edi, %eax
    subl        %esi, %eax
    jnc         out_u32u32
    orl         $1, (%rdx)
out_u32u32:
    ret
    funsz       subu32u32

#else
    defun       _subs64s64
    movl        4(%esp), %eax
    movl        8(%esp), %ecx
    movl        20(%esp), %edx
    subl        %ecx, %eax
    movl        %eax, (%edx)
    movl        12(%esp), %eax
    movl        16(%esp), %ecx
    movl        24(%esp), %edx
    sbbl        %ecx, %eax
    movl        %eax, (%edx)
    jno         out_s64s64
    movl        28(%esp), %edx
    orl         $1, (%edx)
out_s64s64:
    ret

    defun       _subu64u64
    movl        4(%esp), %eax
    movl        8(%esp), %ecx
    movl        20(%esp), %edx
    subl        %ecx, %eax
    movl        %eax, (%edx)
    movl        12(%esp), %eax
    movl        16(%esp), %ecx
    movl        24(%esp), %edx
    sbbl        %ecx, %eax
    movl        %eax, (%edx)
    jnc         out_u64u64
    movl        28(%esp), %edx
    orl         $1, (%edx)
out_u64u64:
    ret

    defun       subs32s32
    movl        4(%esp), %eax
    movl        8(%esp), %ecx
    subl        %ecx, %eax
    jno         out_s32s32
    movl        12(%esp), %edx
    orl         $1, (%edx)
out_s32s32:
    ret
    funsz       subs32s32

    defun       subu32u32
    movl        4(%esp), %eax
    movl        8(%esp), %ecx
    subl        %ecx, %eax
    jnc         out_u32u32
    movl        12(%esp), %edx
    orl         $1, (%edx)
out_u32u32:
    ret
    funsz       subu32u32

#endif

# vi: set expandtab sw=4 ts=4:
