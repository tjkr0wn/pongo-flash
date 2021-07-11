#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "common.h"
#include "debugger_log.h"
#include "SecureROM_offsets.h"
#include "structs.h"

/* ROM code only takes up 8 pages */
asm(".section __TEXT,__romreloc\n"
    ".align 14\n"
    ".space 0x20000, 0x0\n"
    ".section __TEXT,__text\n");

/* L3 page tables for relocated ROM */
/* XXX the MMU doesn't seem to like reading from AOP SRAM for ptes */
/* asm(".section __TEXT,__romrelocptes\n" */
/*     ".align 14\n" */
/*     ".space 0x4000, 0x0\n" */
/*     ".section __TEXT,__text\n"); */

bool init(void){
    /* Set up the logging system before anything else */
    loginit();
    return true;
}
