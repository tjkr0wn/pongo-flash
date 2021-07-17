/*

pongo-flash flash NAND (OVER SPI) driver
Original Source: https://github.com/tjkr0wn/pongo-flash
Written by: Tarek Joumaa (tjkr0wn)

STATUS: DEVELOPMENT

*/

#ifndef NAND_H
#define NAND_H

/* NO STUB */
#define calloc ((void *(*)(size_t, size_t))0x10000d238)
#define free ((void (*)(void *))0x10000d2e4)

/* STUB NEEDED */
#define platform_get_spi_frequency ((uint32_t(*)(void))0x100007b28)
#define flash_nand_init_gpio ((int(*)(void))0x1000075cc)
  /* UNKNOWN */
  #define flash_spi_read_wrapper_unknown ((int(*)((struct spi_nanddev *, uint32_t *, uint32_t *))0x100003c8c)
#define nand_readRange ((int(*)(struct spi_nanddev *, void *, uint32_t, uint32_t))0x1000075cc)
#define construct_blockdev ((int(*)(struct blockdev *, char *, uint64_t, uint32_t))0x10000c7fc)
#define register_blockdev ((int(*)(struct blockdev *))0x10000c690)

/*
  pongo-flash/decomple/spi_headers.h
*/

struct blockdev {
	struct blockdev *next;
	uint32_t flags;
	uint32_t block_size;
	uint32_t block_count;
	uint32_t block_shift;
	uint64_t total_len;
	uint32_t alignment;
	uint32_t alignment_shift;
	int (*read_hook)(struct blockdev *, void * ptr, off_t offset, uint64_t len);
	int (*read_block_hook)(struct blockdev *, void * ptr, uint32_t block, uint32_t count);
	int (*write_hook)(struct blockdev *, const void * ptr, off_t offset, uint64_t len);
	int (*write_block_hook)(struct blockdev *, const void * ptr, uint32_t block, uint32_t count);
	int (*erase_hook)(struct blockdev *, off_t offset, uint64_t len);
	char name[16];
	off_t protect_start;
	off_t protect_end;
};

struct spi_blockdev {
  struct blockdev bdev;
  uintptr_t handle;
  int (*readRange)(uintptr_t handle, uint8_t *ptr, uint32_t offset, uint32_t length);
};

struct spi_nanddev {
    struct spi_blockdev sdev;
		uint32_t spiBus;
		uint32_t spiChipSelect;
    uint32_t spiFrequency;
    uint32_t spiMode;
    uint32_t flags;
    uint32_t blockSize;
    uint32_t blockCount;
    uint32_t some_field5;
    uint32_t defaultTimeout;
    uint32_t some_field7;
};

#endif
