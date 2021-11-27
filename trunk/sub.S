#
# sub.S
#

    .globl      subs64s64
    .globl      _subs64s64
    .globl      subu64u64
    .globl      _subu64u64

    .globl      subs32s32
    .globl      _subs32s32
    .globl      subu32u32
    .globl      _subu32u32

    .type       subs64s64 STT_FUNC
    .type       _subs64s64 STT_FUNC
    .type       subu64u64 STT_FUNC
    .type       _subu64u64 STT_FUNC

    .type       subs32s32 STT_FUNC
    .type       _subs32s32 STT_FUNC
    .type       subu32u32 STT_FUNC
    .type       _subu32u32 STT_FUNC

    .text

#if __WORDSIZE == 64

subs64s64:
_subs64s64:
    movq        %rdi, %rax
    subq        %rsi, %rax
    jno         out_s64s64
    orl         $1, (%rdx)
out_s64s64:
    ret

    .size       subs64s64, .-subs64s64
    .size       _subs64s64, .-_subs64s64

subu64u64:
_subu64u64:
    movq        %rdi, %rax
    subq        %rsi, %rax
    jnc         out_u64u64
    orl         $1, (%rdx)
out_u64u64:
    ret

    .size       subu64u64, .-subu64u64
    .size       _subu64u64, .-_subu64u64

subs32s32:
_subs32s32:
    movl        %edi, %eax
    subl        %esi, %eax
    jno         out_s32s32
    orl         $1, (%rdx)
out_s32s32:
    ret

    .size       subs32s32, .-subs32s32
    .size       _subs32s32, .-_subs32s32

subu32u32:
_subu32u32:
    movl        %edi, %eax
    subl        %esi, %eax
    jnc         out_u32u32
    orl         $1, (%rdx)
out_u32u32:
    ret

    .size       subu32u32, .-subu32u32
    .size       _subu32u32, .-_subu32u32

#else

subs64s64:
_subs64s64:
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

    .size       subs64s64, .-subs64s64
    .size       _subs64s64, .-_subs64s64

subu64u64:
_subu64u64:
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

    .size       subu64u64, .-subu64u64
    .size       _subu64u64, .-_subu64u64

subs32s32:
_subs32s32:
    movl        4(%esp), %eax
    movl        8(%esp), %ecx
    subl        %ecx, %eax
    jno         out_s32s32
    movl        12(%esp), %edx
    orl         $1, (%edx)
out_s32s32:
    ret

    .size       subs32s32, .-subs32s32
    .size       _subs32s32, .-_subs32s32

subu32u32:
_subu32u32:
    movl        4(%esp), %eax
    movl        8(%esp), %ecx
    subl        %ecx, %eax
    jnc         out_u32u32
    movl        12(%esp), %edx
    orl         $1, (%edx)
out_u32u32:
    ret

    .size       subu32u32, .-subu32u32
    .size       _subu32u32, .-_subu32u32

#endif

# vi: set expandtab sw=4 ts=4:
