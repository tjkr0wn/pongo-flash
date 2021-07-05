.text

.pool
.set platform_get_boot_device, 0x10000796c
.set platform_enable_boot_interface, 0x100007a10
.set security_init, 0x100009b14
.set flash_nand_init, 0x100003a84
.set lookup_image_in_bdev, 0x100001a4c

.globl _init
_init:
  sub     sp, sp, #0x20
  stp     x30, x29, [sp, #0x10]
  add     x1,sp,#0x8
  add     x2,sp,#0x4
  mov     x3,sp
  mov     x0,#0x0
  ldr     x29, =platform_get_boot_device
  blr     x29
  cbz     w0,fail
  ldp     w25,w22,[sp, #0x4]
  ldr     w23,[sp]
  mov     w0,#0x1
  mov     x1,x22
  mov     x2,x23
  ldr     x29, =platform_enable_boot_interface
  blr     x29
  mov     w0,#0x1
  ldr     x29, =security_init
  blr     x29
  mov     w28,#0x696c0000
  movk    w28,#0x6c62
  mov     x0,x23
  ldr     x29, =flash_nand_init
  blr     x29
  mov	    x0, #0x7246
  movk	  x0, #0x1, lsl #16
  movk	  x0, #0x1, lsl #32
  mov     w1, w28 //Doesn't really matter, lookup_image_in_bdev hardcodes to illb anyways
  ldr     x29, =lookup_image_in_bdev
  blr     x29
  cbnz    x0, exit

fail:
  mov     x0, #0x41

exit:
  ldp     x30, x29, [sp, #0x10]
  add     sp, sp, #0x20
  ret
