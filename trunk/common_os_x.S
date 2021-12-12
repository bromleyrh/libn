#
# common_os_x.S
#

    .macro      expfun nm
    .globl      \nm
    .globl      _\nm
    .endm

    .macro      defun nm
\nm :
_\nm :
    .endm

    .macro      funsz nm
    .endm

# vi: set expandtab sw=4 ts=4:
