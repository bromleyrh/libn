#
# mul.S
#

    .globl      muls64s64
    .globl      _muls64s64
    .globl      mulu64u64
    .globl      _mulu64u64

    .globl      muls32s32
    .globl      _muls32s32
    .globl      mulu32u32
    .globl      _mulu32u32

    .type       muls64s64 STT_FUNC
    .type       _muls64s64 STT_FUNC
    .type       mulu64u64 STT_FUNC
    .type       _mulu64u64 STT_FUNC

    .type       muls32s32 STT_FUNC
    .type       _muls32s32 STT_FUNC
    .type       mulu32u32 STT_FUNC
    .type       _mulu32u32 STT_FUNC

    .text

#if __WORDSIZE == 64

muls64s64:
_muls64s64:
    movq        %rdi, %rax
    imulq       %rsi, %rax
    jno         out_s64s64
    orl         $1, (%rdx)
out_s64s64:
    ret

    .size       muls64s64, .-muls64s64
    .size       _muls64s64, .-_muls64s64

mulu64u64:
_mulu64u64:
    movq        %rdx, %rcx
    movq        %rdi, %rax
    mulq        %rsi
    jno         out_u64u64
    orl         $1, (%rcx)
out_u64u64:
    ret

    .size       mulu64u64, .-mulu64u64
    .size       _mulu64u64, .-_mulu64u64

muls32s32:
_muls32s32:
    movl        %edi, %eax
    imull       %esi, %eax
    jno         out_s32s32
    orl         $1, (%rdx)
out_s32s32:
    ret

    .size       muls32s32, .-muls32s32
    .size       _muls32s32, .-_muls32s32

mulu32u32:
_mulu32u32:
    movq        %rdx, %rcx
    movl        %edi, %eax
    mull        %esi
    jno         out_u32u32
    orl         $1, (%rcx)
out_u32u32:
    ret

    .size       mulu32u32, .-mulu32u32
    .size       _mulu32u32, .-_mulu32u32

#else

muls32s32:
_muls32s32:
    movl        4(%esp), %eax
    movl        8(%esp), %ecx
    imull       %ecx, %eax
    jno         out_s32s32
    movl        12(%esp), %edx
    orl         $1, (%edx)
out_s32s32:
    ret

    .size       muls32s32, .-muls32s32
    .size       _muls32s32, .-_muls32s32

mulu32u32:
_mulu32u32:
    movl        4(%esp), %eax
    movl        8(%esp), %ecx
    mull        %ecx
    jno         out_u32u32
    movl        12(%esp), %ecx
    orl         $1, (%ecx)
out_u32u32:
    ret

    .size       mulu32u32, .-mulu32u32
    .size       _mulu32u32, .-_mulu32u32

#endif

# vi: set expandtab sw=4 ts=4:
