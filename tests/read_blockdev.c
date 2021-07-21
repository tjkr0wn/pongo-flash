/*

pongo-flash flash NAND (OVER SPI) driver
Original Source: https://github.com/tjkr0wn/pongo-flash
Written by: Tarek Joumaa (tjkr0wn)

STATUS: DEVELOPMENT

*/

#include <stdint.h>
#include <stdbool.h>
#include <nand.h>
asm(".space 0x620, 0x0\n\t");
asm(".text\n");

extern uint64_t platform_prep_nand_stack_init(uintptr_t log, void *boot_device, uint32_t *boot_arg);
extern void disable_boot_interface(bool enable, int boot_device, uint32_t boot_arg);

struct image_info *read_blockdev(uintptr_t log) {
  int boot_device = 0;
  uint32_t boot_arg = 0;
  int ok = -1;

  ok = platform_prep_nand_stack_init(log, &boot_device, &boot_arg);

  if (ok != 0 || flash_nand_init(boot_arg) != 0) {
    return 0x41;
  }
  uint32_t type = (uint32_t) "illb";
  struct image_info * illb = lookup_image_in_bdev(platform_blockdev_name, type);
  disable_boot_interface(false, boot_device, boot_arg);

  return illb;
}
