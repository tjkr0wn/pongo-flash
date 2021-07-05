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

/*struct proper_spi_blockdev in Ghidra*/
/*struct nor_blockdev renamed to spi_blockdev. NOTE: At ROM time, there should be no write capabilities. This includes erasing.*/
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
    uint32_t blockSize;//I.E. We can determine this by comparing decompilation of flash_nor_init and flash_nand_init. Both fields were 0x1000
    uint32_t blockCount;
    uint32_t some_field5;
    uint32_t defaultTimeout;
    uint32_t some_field7;
};
