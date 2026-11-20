#include <avr/io.h>

FUSES = {
    .low = (FUSE_CKSEL0 & FUSE_CKSEL2 & FUSE_CKSEL3 & FUSE_SUT0 & FUSE_SUT1),
    .high = (FUSE_SPIEN & FUSE_EESAVE),
    .extended = (FUSE_BODLEVEL0)};

int main()
{
}