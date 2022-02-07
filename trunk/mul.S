#
# mul.S
#

#include "arithmetic.S"
#include "common.S"

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
    jno         0f
    orl         $aoverflow, (%rdx)
0:
    ret
    funsz       muls64s64

    defun       mulu64u64
    movq        %rdx, %rcx
    movq        %rdi, %rax
    mulq        %rsi
    jno         0f
    orl         $aoverflow, (%rcx)
0:
    ret
    funsz       mulu64u64

    defun       muls32s32
    movl        %edi, %eax
    imull       %esi, %eax
    jno         0f
    orl         $aoverflow, (%rdx)
0:
    ret
    funsz       muls32s32

    defun       mulu32u32
    movq        %rdx, %rcx
    movl        %edi, %eax
    mull        %esi
    jno         0f
    orl         $aoverflow, (%rcx)
0:
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
    pushl       %ebp
    movl        %esp, %ebp
    movl        8(%esp), %edx       # a
    testl       %edx, %edx
    jnz         0f
    movl        12(%esp), %ecx      # b
    testl       %ecx, %ecx
    jz          9f
0:
    movl        16(%esp), %ecx      # c
    testl       %ecx, %ecx
    jnz         1f
    movl        20(%esp), %eax      # d
    testl       %eax, %eax
    jz          9f
1:
    testl       %edx, %edx
    jnz         2f
    movl        12(%esp), %ecx      # b
    cmpl        $1, %ecx
    je          1f
2:
    movl        16(%esp), %ecx      # c
    testl       %ecx, %ecx
    jnz         3f
    cmpl        $1, %eax
    je          0f
3:
    testl       %ecx, %ecx          # get sign of c
    lahf
    shll        $4, %eax
    testl       %edx, %edx          # get sign of a
    lahf
    shrl        $12, %eax
    pushl       %eax
    movl        %edx, %eax
    testl       %eax, %eax
    jns         4f
                                    # get absolute value of a + b
    andl        $0x7fffffff, %eax   # 1) clear sign bit
                                    # 2) subtract 1 from a + b
    movl        16(%esp), %edx      # 2a) b
    subl        $1, %edx            # 2b) b'
    jc          2f
                                    # 2c) a' = a
                                    # 3) subtract a' + b' from INT_MAX
    movl        %eax, %ecx
    movl        $0xffffffff, %eax
    subl        %edx, %eax          # 3a) b'
    jc          2f
    movl        $0x7fffffff, %edx
    subl        %ecx, %edx          # 3b) a'
                                    # 4) save abs(a + b) on stack
    movl        %eax, 16(%esp)      # 4a) b'
    movl        %edx, 12(%esp)      # 4b) a'
4:
    movl        20(%esp), %ecx      # c
    testl       %ecx, %ecx
    jns         5f
                                    # get absolute value of c + d
    andl        $0x7fffffff, %ecx   # 1) clear sign bit
                                    # 2) subtract 1 from c + d
    movl        24(%esp), %edx      # 2a) d
    subl        $1, %edx            # 2b) d'
    jc          2f
                                    # 2c) c' = c
                                    # 3) subtract c' + d' from INT_MAX
    movl        $0xffffffff, %eax
    subl        %edx, %eax          # 3a) d'
    jc          2f
    movl        $0x7fffffff, %edx
    subl        %ecx, %edx          # 3b) c'
                                    # 4) save abs(c + d) on stack
    movl        %eax, 24(%esp)      # 4a) d'
    movl        %edx, 20(%esp)      # 4b) c'
5:
    movl        20(%esp), %ecx      # c
    testl       %ecx, %ecx
    jz          6f
    movl        12(%esp), %eax      # a
    testl       %eax, %eax
    jnz         2f
    movl        16(%esp), %eax      # b
    mull        %ecx                # bc
    jo          2f
    movl        24(%esp), %ecx      # d
    jmp         7f
6:
    movl        12(%esp), %eax      # a
    movl        24(%esp), %ecx      # d
    mull        %ecx                # ad
    jo          2f
7:
    pushl       %eax
    movl        20(%esp), %eax      # b
    mull        %ecx                # bd
    movl        %eax, %ecx
    popl        %eax
    addl        %edx, %eax          # Lh + (H1l + H2l)
    jc          2f
    testl       $0x80000000, %eax
    jnz         2f
    popl        %edx
    testl       $0x00000088, %edx   # determine sign of product
    jp          8f
                                    # subtract 1 from Hl + Ll
    subl        $1, %ecx
    jc          3f
                                    # subtract Hl' + L1' from INT_MAX
    movl        $0xffffffff, %edx
    subl        %ecx, %edx
    jc          3f
    movl        %edx, %ecx
    movl        $0x7fffffff, %edx
    subl        %eax, %edx
    movl        %edx, %eax
    orl         $0x80000000, %eax
8:
    movl        24(%esp), %edx
    movl        %eax, (%edx)
    movl        28(%esp), %edx
    movl        %ecx, (%edx)
    popl        %ebp
    ret
9:
    movl        24(%esp), %edx
    movl        $0, (%edx)
    movl        28(%esp), %edx
    movl        $0, (%edx)
    popl        %ebp
    ret
0:
    movl        8(%esp), %eax
    movl        24(%esp), %edx
    movl        %eax, (%edx)
    movl        12(%esp), %ecx
    movl        28(%esp), %edx
    movl        %ecx, (%edx)
    popl        %ebp
    ret
1:
    movl        16(%esp), %eax
    movl        24(%esp), %edx
    movl        %eax, (%edx)
    movl        20(%esp), %ecx
    movl        28(%esp), %edx
    movl        %ecx, (%edx)
    popl        %ebp
    ret
2:
    popl        %edx
3:
    movl        32(%esp), %edx
    orl         $aoverflow, (%edx)
    popl        %ebp
    ret

    defun       _mulu64u64
    pushl       %ebp
    movl        %esp, %ebp
    movl        8(%esp), %eax   # a
    movl        16(%esp), %ecx  # c
    testl       %ecx, %ecx
    jz          0f
    testl       %eax, %eax
    jnz         2f
    movl        12(%esp), %eax  # b
    mull        %ecx
    jo          2f
    movl        20(%esp), %ecx  # d
    jmp         1f
0:
    movl        20(%esp), %ecx  # d
    mull        %ecx
    jo          2f
1:
    pushl       %eax
    movl        16(%esp), %eax  # b
    mull        %ecx
    movl        %eax, %ecx
    popl        %eax
    addl        %edx, %eax
    jc          2f
    movl        24(%esp), %edx
    movl        %eax, (%edx)
    movl        28(%esp), %edx
    movl        %ecx, (%edx)
    popl        %ebp
    ret
2:
    movl        32(%esp), %edx
    orl         $aoverflow, (%edx)
    popl        %ebp
    ret

    defun       muls32s32
    pushl       %ebp
    movl        %esp, %ebp
    movl        8(%esp), %eax
    movl        12(%esp), %ecx
    imull       %ecx, %eax
    jno         0f
    movl        16(%esp), %edx
    orl         $aoverflow, (%edx)
0:
    popl        %ebp
    ret
    funsz       muls32s32

    defun       mulu32u32
    pushl       %ebp
    movl        %esp, %ebp
    movl        8(%esp), %eax
    movl        12(%esp), %ecx
    mull        %ecx
    jno         0f
    movl        16(%esp), %ecx
    orl         $aoverflow, (%ecx)
0:
    popl        %ebp
    ret
    funsz       mulu32u32

#endif

# vi: set expandtab sw=4 ts=4:
