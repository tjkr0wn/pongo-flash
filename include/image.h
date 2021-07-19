/*

pongo-flash flash NAND (OVER SPI) driver
Original Source: https://github.com/tjkr0wn/pongo-flash
Written by: Tarek Joumaa (tjkr0wn)

STATUS: DEVELOPMENT

*/
#include <image.h>
#ifndef IMAGE_H
#define IMAGE_H

struct image_info {
  uint32_t imageLength;
  uint32_t imageAllocation;
  uint32_t imageType;
  uint32_t imagePrivateMagic;
  uint32_t imageOptions;
  void *imagePrivate;
};

#endif
