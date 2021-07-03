.text

.pool
.set platform_get_boot_device, 0x10000796c
.set platform_enable_boot_interface, 0x100007a10
.set security_init, 0x100009b14
.set flash_nor_init, 0x10000a9d0
.set lookup_image_in_bdev, 0x100001a4c

.globl _init
_init:
  sub     sp, sp, #0x20
  str     x30, [sp, #0x10]
  mov     w0, #0x0
  sbfx    w19,w0,#0x0,#0x1
  mov     w26,#0x1c0000
  movk    w26,#0x8000
  mov     w27,#0xb
  mov     x21, 29249
  movk    x21, 0x1, lsl 16
  movk    x21, 0x1, lsl 32
  add     x1, sp, #0x8
  add     x2, sp, #0x4
  mov     x3, sp
  mov     x0,x19
  ldr     x18, =platform_get_boot_device
  blr     x18
  cbz     w0, fail
  ldp     w25,w22,[sp, #0x4]
  ldr     w23,[sp]
  mov     w0,#0x1
  mov     x1,x22
  mov     x2,x23
  ldr     x18, =platform_enable_boot_interface
  blr     x18
  mov     w0, #0x1
  ldr     x18, =security_init
  blr     x18
  mov     w28, #0x696c0000
  movk    w28, #0x6c62
  mov     x0,x23
  ldr     x18, =flash_nor_init
  blr     x18
  mov     x0, x21
  ldr     x18, =lookup_image_in_bdev
  blr     x18
  b       exit

fail:
  mov     x0, #0x41

exit:
  ldr     x30, [sp, #0x10]
  add     sp, sp, #0x20
  ret
