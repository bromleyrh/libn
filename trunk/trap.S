#
# trap.S
#

    .include    "arithmetic.S"
#if __APPLE__
    .include    "common_os_x.S"
#else
    .include    "common.S"
#endif

#ifdef X86_64
    expfun      atrapinit
#else
    .globl      atrapinit
#endif

    .globl      trapinit

    .text

#ifdef X86_64
    defun       atrapinit
    pushl       8(%rsp)
    pushq       %rbp
    call        trapinit
    addq        $8, %rsp
    popq        %rbp
    ret
    funsz       atrapinit

#else
    defun       atrapinit
    pushl       %ebp
    movl        %esp, %ebp
    pushl       8(%esp)
    pushl       %ebp
    call        trapinit
    addl        $8, %esp
    popl        %ebp
    ret
    funsz       atrapinit

#endif

# vi: set expandtab sw=4 ts=4:
