/*

pongo-flash flash NAND (OVER SPI) driver
Original Source: https://github.com/tjkr0wn/pongo-flash
Written by: Tarek Joumaa (tjkr0wn)

STATUS: DEVELOPMENT

*/

.text

.pool
.set platform_get_boot_device, 0x10000796c
.set platform_enable_boot_interface, 0x100007a10
.set flash_nand_init, 0x100003a84
.set lookup_image_in_bdev, 0x100001a4c
.set iboot_vers_string, 0x100000280

.globl _platform_prep_nand_stack_init
.globl _disable_boot_interface

/*
_disable_boot_interface:
  mov     w28,#0x696c0000
  movk    w28,#0x6c62
  mov     x0, #0x7246
  movk	  x0, #0x1, lsl #16
  movk	  x0, #0x1, lsl #32

  /* Doesn't really matter, lookup_image_in_bdev hardcodes to illb anyways */
  mov     w1, w28

  ldr     x29, =lookup_image_in_bdev
  blr     x29
  cbnz    x0, exit

fail:
  mov     x0, #0x41

exit:
  mov     x28, x0
  mov     w0,#0x0
  ldp     x1, x2, [sp, #0x20]
  ldr     x29, =platform_enable_boot_interface
  blr     x29
  mov     x0, x28
  ldp     x30, x29, [sp, #0x10]
  add     sp, sp, #0x30
  ret
*/

_platform_prep_nand_stack_init:
  sub     sp, sp, #0x30
  stp     x30, x29, [sp, #0x10]

  /* This will tell us if the execute command was successful */
  mov     x1, x0
  ldr     x0, =iboot_vers_string
  blr     x1

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
  stp     x1, x2, [sp, #0x20]
  ldr     x29, =platform_enable_boot_interface
  blr     x29
  mov     x0, x23
  b       exit

fail:
  mov     x0, #0x41

exit:
  ldp     x30, x29, [sp, #0x10]
  add     sp, sp, #0x30
  ret
