#include <limits.h> //XXX TEMPORARY
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "common.h"
#include "debugger_log.h"
#include "init.h"
#include "SecureROM_offsets.h"
#include "structs.h"

/* XXX what happens when we transition over to iBoot? */
static GLOBAL(uint8_t debuggee_cpu);
static GLOBAL(uint8_t debugger_cpu) = 5;

static uint8_t curcpu(void){
    uint64_t mpidr_el1;
    asm volatile("mrs %0, mpidr_el1" : "=r" (mpidr_el1));
    return mpidr_el1 & 0xff;
}

extern __attribute__ ((noreturn)) void debugger_tick(void);

__attribute__ ((noreturn)) void debugger_tick(void){
    dbglog("%s: hello from cpu%d!\n", __func__, (uint32_t)curcpu());
    dbglog("AA%s: hello from cpu%d!\n", __func__, (uint32_t)curcpu());
    dbglog("hello from cpu%d!\n", (uint32_t)curcpu());
    dbglog("hfdsi %d\n", 444444);
    dbglog("Hello\n");
    dbglog("%s: test test\n", __func__);
    dbglog("%s%#x%%%d %p Hello world! %llx A%c %x\n",
            __func__, -2147483647, 45004, (void *)debugger_tick,
            (uint64_t)debugger_tick, 'U', (uint32_t)debugger_tick);
    dbglog("%s%#x%%%d %p Hello world! %llx A%c %x\n",
            __func__, -2147483647, 45004, (void *)debugger_tick,
            (uint64_t)debugger_tick, 'U', 84943);
    dbglog("%s%#x%%%d %p Hello world! %llx A%c %x %lld %lld\n",
            __func__, -2147483647, -45004, (void *)debugger_tick,
            (uint64_t)debugger_tick, 'U', 84943, LONG_MAX, LONG_MAX+1);

    for(;;){

    }
}

enum {
    SecureDBG_LOG_READ = 0x4000,
    SecureDBG_EXECUTE,
    SecureDBG_MAXREQ,
};

static bool is_SecureDBG_request(uint16_t req){
    return req >= SecureDBG_LOG_READ && req < SecureDBG_MAXREQ;
}

/* Our USB interface callback will preserve the original functionality
 * by calling out to the code inside src/usb_0xA1_2_arm64.S if the
 * command doesn't match any in this file. (at least, if we're executing
 * inside SecureROM, what about iBoot?) */
static int SecureDBG_usb_interface_request_handler(struct usb_request_packet *req,
        void *bufout){
    uint16_t request = req->wValue;

    if(!is_SecureDBG_request(request))
        return ipwndfu_usb_interface_request_handler(req, bufout);

    if(request == SecureDBG_LOG_READ){
        /* dbglog("%s: sending back log (bufout=%#llx)...\n", __func__, */
        /*         (uint64_t)bufout); */

        size_t len;
        char *log = getlog(&len);

        if(len == 0){
            aop_sram_strcpy(log, "!NOLOG!");
            len = 7;
        }

        aop_sram_memcpy(io_buffer, log, len);
        usb_core_do_io(0x80, io_buffer, len, NULL);
    }
    else if (request == SecureDBG_EXECUTE){
      dbglog("Got SecureDBG_EXECUTE\n");
      long (* exec)(uintptr_t log) = pongo_flash_code_dump_region;
      aop_sram_memcpy(pongo_flash_code_dump_region, io_buffer, 0x800);
      uintptr_t log = &dbglog;
      long retval = exec(log);
      usb_core_do_io(0x80, retval, sizeof(long), NULL);
    }

    return 0;
}

static GLOBAL(bool SecureDBG_init_flag) = false;

/* Called from src/usb_0xA1_2_arm64.S. Here we point SecureROM's global
 * USB interface callback to our own, set up a logging system, and kickstart
 * a debugger CPU. */
uint64_t debugger_entryp(void){
    if(SecureDBG_init_flag)
        return 0;

    if(!init())
        return 1;

    *(uint64_t *)usb_interface_request_handler = (uint64_t)SecureDBG_usb_interface_request_handler;

    dbglog("Installed USB handler\n");

    debuggee_cpu = curcpu();

    dbglog("%s: hello from SecureROM! We are CPU %d\n", __func__, debuggee_cpu);

    if(debuggee_cpu == debugger_cpu){
        dbglog("%s: why are we CPU5?\n", __func__);
        return 1;
    }

    SecureDBG_init_flag = true;

    return 0;
}
