#TODO: Make this more extensible/cover more targets
OBJCOPY = objcopy
C_FLAGS = -e _read_blockdev -static -target arm64-apple-darwin -ffreestanding -Wall -nostdlib -fno-stack-protector

ifndef $(HOST_OS)
	ifeq ($(OS),Windows_NT)
		HOST_OS = Windows
	else
		HOST_OS := $(shell uname -s)
	endif
endif

ifeq ($(HOST_OS),Linux)
	CC = clang
	LD_FLAGS = -fuse-ld=/usr/bin/ld64
endif

ifeq ($(HOST_OS),Darwin)
	CC = xcrun -sdk $(iphoneos) clang
	LD_FLAGS =
endif

SRC_CORE_TESTS = core/tests/init.S

SRC_MAIN_TESTS = tests/read_blockdev.c

OBJ_MAIN_TESTS = main_test.o
BIN_MAIN_TESTS = main_test.bin

LD_FLAGS += -Wl,-image_base,0x180018000

main_tests:
	$(CC) $(C_FLAGS) $(LD_FLAGS) $(SRC_MAIN_TESTS) $(SRC_CORE_TESTS) -o $(OBJ_MAIN_TESTS)
	$(OBJCOPY) -O binary -j .text $(OBJ_MAIN_TESTS) $(BIN_MAIN_TESTS)
	rm $(OBJ_MAIN_TESTS)
