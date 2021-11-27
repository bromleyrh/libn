#
# add.S
#

    .globl      adds64s64
    .globl      _adds64s64
    .globl      addu64u64
    .globl      _addu64u64

    .globl      adds32s32
    .globl      _adds32s32
    .globl      addu32u32
    .globl      _addu32u32

    .type       adds64s64 STT_FUNC
    .type       _adds64s64 STT_FUNC
    .type       addu64u64 STT_FUNC
    .type       _addu64u64 STT_FUNC

    .type       adds32s32 STT_FUNC
    .type       _adds32s32 STT_FUNC
    .type       addu32u32 STT_FUNC
    .type       _addu32u32 STT_FUNC

    .text

#if __WORDSIZE == 64

adds64s64:
_adds64s64:
    movq        %rdi, %rax
    addq        %rsi, %rax
    jno         out_s64s64
    orl         $1, (%rdx)
out_s64s64:
    ret

    .size       adds64s64, .-adds64s64
    .size       _adds64s64, .-_adds64s64

addu64u64:
_addu64u64:
    movq        %rdi, %rax
    addq        %rsi, %rax
    jnc         out_u64u64
    orl         $1, (%rdx)
out_u64u64:
    ret

    .size       addu64u64, .-addu64u64
    .size       _addu64u64, .-_addu64u64

adds32s32:
_adds32s32:
    movl        %edi, %eax
    addl        %esi, %eax
    jno         out_s32s32
    orl         $1, (%rdx)
out_s32s32:
    ret

    .size       adds32s32, .-adds32s32
    .size       _adds32s32, .-_adds32s32

addu32u32:
_addu32u32:
    movl        %edi, %eax
    addl        %esi, %eax
    jnc         out_u32u32
    orl         $1, (%rdx)
out_u32u32:
    ret

    .size       addu32u32, .-addu32u32
    .size       _addu32u32, .-_addu32u32

#else

adds64s64:
_adds64s64:
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

    .size       adds64s64, .-adds64s64
    .size       _adds64s64, .-_adds64s64

addu64u64:
_addu64u64:
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

    .size       addu64u64, .-addu64u64
    .size       _addu64u64, .-_addu64u64

adds32s32:
_adds32s32:
    movl        4(%esp), %eax
    movl        8(%esp), %ecx
    addl        %ecx, %eax
    jno         out_s32s32
    movl        12(%esp), %edx
    orl         $1, (%edx)
out_s32s32:
    ret

    .size       adds32s32, .-adds32s32
    .size       _adds32s32, .-_adds32s32

addu32u32:
_addu32u32:
    movl        4(%esp), %eax
    movl        8(%esp), %ecx
    addl        %ecx, %eax
    jnc         out_u32u32
    movl        12(%esp), %edx
    orl         $1, (%edx)
out_u32u32:
    ret

    .size       addu32u32, .-addu32u32
    .size       _addu32u32, .-_addu32u32

#endif

# vi: set expandtab sw=4 ts=4:
