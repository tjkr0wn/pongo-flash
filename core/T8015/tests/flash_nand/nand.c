/*

pongo-flash flash NAND (OVER SPI) driver
Original Source: https://github.com/tjkr0wn/pongo-flash
Written by: Tarek Joumaa (tjkr0wn)

STATUS: DEVELOPMENT

*/

/* TODO COUNT: 1 */
#include <nand.h>
#include <stddef.h>
#include <string.h>
#include <T8015.h>


int flash_nand_init(int which_device)
{
  uint32_t uVar2;
  int result = -1;
  uint uVar4;
  struct spi_nanddev *dev = NULL;
  int uVar5;
  uint32_t local_40;
  uint32_t local_3c;

  dev = (struct spi_nanddev *) calloc(1, 0xa8);
  if (which_device == 0 && dev != NULL) {
    dev->spiBus = 0;
    dev->spiFrequency = platform_get_spi_frequency();
    dev->spiMode = 1;
    dev->defaultTimeout = 1000000;
    result = flash_nand_init_gpio();
    if (-1 < result) {
      local_3c = 0;
      result = flash_spi_read_wrapper_unknown(dev,&local_3c,&local_40);
      if (result == 0) {
        dev->some_field5 = local_40;
        local_3c = 1;
        result = flash_spi_read_wrapper_unknown(dev,&local_3c,&local_40);
        if (result == 0) {
          dev->blockSize = 0x1000;
          dev->blockCount = local_40;
          dev->flags = 0;
          (dev->sdev).handle = (uintptr_t) dev;
          (dev->sdev).readRange = nand_readRange;
          platform_blockdev_name = (char *) malloc(strlen(SPI_NAND0));
          strcpy(platform_blockdev_name, SPI_NAND0);
          if (platform_blockdev_name != NULL) {
            construct_blockdev((struct blockdev *)dev, platform_blockdev_name, (local_40 << 0xc), 0x1000);
            (dev->sdev).bdev.read_block_hook = nand_read_block_hook;
            register_blockdev((struct blockdev *)dev);
            uVar4 = 0;
            goto exit;
          }
        }
      }
    }
  }
  if (dev) free(dev);
  uVar4 = 0xffffffff;

  exit:
    return uVar4 & uVar4 >> 0x1f;

  /* TODO: Normally we'd need a panic here, but this is still in a development phase */
  //panic_wrapper(uVar5);
}
