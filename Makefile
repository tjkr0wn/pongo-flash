#TODO: Make this more extensible/cover more targets
C_FLAGS = -e _read_blockdev -static -target arm64-apple-darwin -ffreestanding -Wall -nostdlib -fno-stack-protector

PLATFORM = T8015

SRC_CORE_TESTS = core/$(PLATFORM)/tests/init.S

SRC_CORE_FLASH_NAND = core/$(PLATFORM)/tests/flash_nand/nand.c

SRC_CORE_TESTS += $(SRC_CORE_FLASH_NAND)

SRC_MAIN_TESTS = tests/read_blockdev.c

OBJ_MAIN_TESTS = main_test.o
BIN_MAIN_TESTS = main_test.bin

ifndef $(HOST_OS)
	ifeq ($(OS),Windows_NT)
		HOST_OS = Windows
	else
		HOST_OS := $(shell uname -s)
	endif
endif

ifeq ($(HOST_OS),Linux)
	CC = clang
	OBJCOPY = vmacho
	BINCOPY	= $(OBJCOPY) $(OBJ_MAIN_TESTS) $(BIN_MAIN_TESTS)
	LD_FLAGS = -fuse-ld=/usr/bin/ld64
endif

ifeq ($(HOST_OS),Darwin)
	CC = xcrun -sdk $(iphoneos) clang
	OBJCOPY = gobjcopy
	BINCOPY = $(OBJCOPY) -O binary -j .text $(OBJ_MAIN_TESTS) $(BIN_MAIN_TESTS)
	LD_FLAGS =
endif

LD_FLAGS += -Wl,-image_base,0x180018000

main_tests:
	$(CC) $(C_FLAGS) $(LD_FLAGS) $(SRC_MAIN_TESTS) $(SRC_CORE_TESTS) -o $(OBJ_MAIN_TESTS)
	$(BINCOPY)
	dd if=$(BIN_MAIN_TESTS) of=$(BIN_MAIN_TESTS).final bs=1 skip=1568
	rm $(OBJ_MAIN_TESTS) $(BIN_MAIN_TESTS)
