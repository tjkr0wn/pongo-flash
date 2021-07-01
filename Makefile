#TODO: Make this more extensible/cover more targets
CC									= xcrun -sdk $(iphoneos) clang
OBJCOPY							= gobjcopy
C_FLAGS							= -e _read_blockdev -target arm64-apple-darwin -lSystem -ffreestanding -Wall -nostdlib -fno-stack-protector

SRC_CORE_TESTS			= core/tests/init.S

SRC_MAIN_TESTS			= tests/read_blockdev.c
OBJ_MAIN_TESTS			= main_test.o
BIN_MAIN_TESTS			= main_test.bin


main_tests:
	$(CC) $(C_FLAGS) $(SRC_MAIN_TESTS) $(SRC_CORE_TESTS) -o $(OBJ_MAIN_TESTS)
	$(OBJCOPY) -O binary -j .text $(OBJ_MAIN_TESTS) $(BIN_MAIN_TESTS)
	rm $(OBJ_MAIN_TESTS)
