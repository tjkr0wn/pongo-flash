/*

pongo-flash flash NAND (OVER SPI) driver
Original Source: https://github.com/tjkr0wn/pongo-flash
Written by: Tarek Joumaa (tjkr0wn)

STATUS: DEVELOPMENT

*/

#include <stdint.h>
asm(".space 0x620, 0x0\n\t");
asm(".text\n");

extern uint64_t _platform_prep_nand_stack_init(uintptr_t log);
extern int flash_nand_init(int which_device);

uint32_t read_blockdev(uintptr_t log) {
  uint64_t boot_arg = platform_prep_nand_stack_init(log);
  if (flash_nand_init(boot_arg) != 0) {
    return 0x41;
  }
  

  return image_info;
}
