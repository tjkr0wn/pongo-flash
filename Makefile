#TODO: Make this more extensible/cover more targets
CC									= xcrun -sdk iphoneos clang
OBJCOPY							= gobjcopy
C_FLAGS							= -arch arm64 -ffreestanding -Wall -nostdlib -fno-stack-protector

SRC_CORE_TESTS			= core/tests/init.S
OBJ_CORE_TESTS			= init.o
BIN_CORE_TESTS			= init.bin

SRC_MAIN_TESTS			= tests/read_blockdev.c
OBJ_MAIN_TESTS			= read_blockdev_test.o
BIN_MAIN_TESTS			= read_blockdev_test.bin


core_tests:
	$(CC) $(C_FLAGS) $(SRC_CORE_TESTS) -o $(OBJ_CORE_TESTS)
	#$(OBJCOPY) -O binary -j .text $(OBJ_CORE_TESTS) $(BIN_CORE_TESTS)
	#rm $(OBJ_CORE_TESTS)

main_tests:
	$(CC) $(C_FLAGS) $(SRC_MAIN_TESTS) $(OBJ_CORE_TESTS) -o $(OBJ_MAIN_TESTS)
	$(OBJCOPY) -O binary -j .text $(OBJ_MAIN_TESTS) $(BIN_MAIN_TESTS)
	rm $(OBJ_CORE_TESTS) $(OBJ_MAIN_TESTS)
