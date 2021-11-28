#
# common.S
#

    .macro      expfun nm
    .globl      \nm
    .globl      _\nm
#ifndef __APPLE__
    .type       \nm STT_FUNC
    .type       _\nm STT_FUNC
#endif
    .endm

    .macro      defun nm
\nm :
_\nm :
    .endm

    .macro      funsz nm
#ifndef __APPLE__
    .size       \nm, .-\nm
    .size       _\nm, .-_\nm
#endif
    .endm

# vi: set expandtab sw=4 ts=4:
