.text

.pool
.set platform_get_boot_device, 0x10000796c
.set platform_enable_boot_interface, 0x100007a10
.set security_init, 0x100009b14
.set flash_nor_init, 0x10000a9d0
.set lookup_image_in_bdev, 0x100001a4c

.globl _init
_init:
  str     x30, [sp, #0x50]
  mov     w0, #0x0
  sbfx    w19,w0,#0x0,#0x1
  mov     w26,#0x1c0000
  movk    w26,#0x8000
  mov     w27,#0xb
  adr     x21,0x100017241
  nop

  add     x1, sp, #0x8
  add     x2, sp, #0x4
  mov     x3, sp
  mov     x0,x19
  bl      =platform_get_boot_device
  cbz     w0, exit
  ldp     w25,w22,[sp, #0x4]
  ldr     w23,[sp]
  mov     w0,#0x1
  mov     x1,x22
  mov     x2,x23
  bl      =platform_enable_boot_interface
  mov     w0, #0x1
  bl      =security_init
  mov     w28, #0x696c0000
  movk    w28, #0x6c62
  mov     x0,x23
  bl      =flash_nor_init
  mov     x0, x21
  bl      =lookup_image_in_bdev


exit:
  ldr x30, [sp, #0x50]
  ret
