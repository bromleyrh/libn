#
# mul.S
#

    .include    "common.S"

#ifdef X86_64
    expfun      muls64s64
    expfun      mulu64u64
#else
    .globl      _muls64s64
    .globl      _mulu64u64
#endif

    expfun      muls32s32
    expfun      mulu32u32

    .text

#ifdef X86_64
    defun       muls64s64
    movq        %rdi, %rax
    imulq       %rsi, %rax
    jno         out_s64s64
    orl         $1, (%rdx)
out_s64s64:
    ret
    funsz       muls64s64

    defun       mulu64u64
    movq        %rdx, %rcx
    movq        %rdi, %rax
    mulq        %rsi
    jno         out_u64u64
    orl         $1, (%rcx)
out_u64u64:
    ret
    funsz       mulu64u64

    defun       muls32s32
    movl        %edi, %eax
    imull       %esi, %eax
    jno         out_s32s32
    orl         $1, (%rdx)
out_s32s32:
    ret
    funsz       muls32s32

    defun       mulu32u32
    movq        %rdx, %rcx
    movl        %edi, %eax
    mull        %esi
    jno         out_u32u32
    orl         $1, (%rcx)
out_u32u32:
    ret
    funsz       mulu32u32

#else

#
# p = (a + b) * (c + d)
# p = ac + (ad + bc) + bd
# H1 = ad, H2 = bc, L = bd
# p = (H1l + H2l) + Lh + Ll
# p = (H1l + H2l + Lh) + Ll
# p = Hl + Ll
#

    defun       _muls64s64
    movl        4(%esp), %edx       # a
    movl        12(%esp), %ecx      # c
    testl       %ecx, %ecx          # get sign of c
    lahf
    shrl        $8, %eax
    testl       %edx, %edx          # get sign of a
    lahf
    pushl       %eax
    movl        %edx, %eax
    andl        $0x7fffffff, %ecx
    jz          mul_ad_s64s64
    andl        $0x7fffffff, %eax
    jnz         overflow_s64s64
    movl        8(%esp), %eax       # b
    mull        %ecx
    jo          overflow_s64s64
    movl        16(%esp), %ecx      # d
    jmp         mul_bd_s64s64
mul_ad_s64s64:
    movl        16(%esp), %ecx      # d
    mull        %ecx
    jo          overflow_s64s64
mul_bd_s64s64:
    pushl       %eax
    movl        8(%esp), %eax       # b
    mull        %ecx
    movl        %eax, %ecx
    popl        %eax
    addl        %edx, %eax
    jc          overflow_s64s64
    testl       $0xf0000000, %eax
    jnz         overflow_s64s64
    popl        %edx
    andl        $0x00007070, %edx   # determine sign of product
    jnp         nosign_s64s64
    orl         $0x70000000, %eax
nosign_s64s64:
    movl        28(%esp), %edx
    movl        %eax, (%edx)
    movl        32(%esp), %edx
    movl        %ecx, (%edx)
    ret
overflow_s64s64:
    movl        36(%esp), %edx
    orl         $1, (%edx)
    ret

    defun       _mulu64u64
    movl        4(%esp), %eax   # a
    movl        12(%esp), %ecx  # c
    testl       %ecx, %ecx
    jz          mul_ad_u64u64
    testl       %eax, %eax
    jnz         overflow_u64u64
    movl        8(%esp), %eax   # b
    mull        %ecx
    jo          overflow_u64u64
    movl        16(%esp), %ecx  # d
    jmp         mul_bd_u64u64
mul_ad_u64u64:
    movl        16(%esp), %ecx  # d
    mull        %ecx
    jo          overflow_u64u64
mul_bd_u64u64:
    pushl       %eax
    movl        8(%esp), %eax   # b
    mull        %ecx
    movl        %eax, %ecx
    popl        %eax
    addl        %edx, %eax
    jc          overflow_u64u64
    movl        28(%esp), %edx
    movl        %eax, (%edx)
    movl        32(%esp), %edx
    movl        %ecx, (%edx)
    ret
overflow_u64u64:
    movl        36(%esp), %edx
    orl         $1, (%edx)
    ret

    defun       muls32s32
    movl        4(%esp), %eax
    movl        8(%esp), %ecx
    imull       %ecx, %eax
    jno         out_s32s32
    movl        12(%esp), %edx
    orl         $1, (%edx)
out_s32s32:
    ret
    funsz       muls32s32

    defun       mulu32u32
    movl        4(%esp), %eax
    movl        8(%esp), %ecx
    mull        %ecx
    jno         out_u32u32
    movl        12(%esp), %ecx
    orl         $1, (%ecx)
out_u32u32:
    ret
    funsz       mulu32u32

#endif

# vi: set expandtab sw=4 ts=4:
