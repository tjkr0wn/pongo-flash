#include <stdint.h>
asm(".space 0x620, 0x0\n\t");
asm(".text\n");

extern long init(uintptr_t log);

long read_blockdev(uintptr_t log) {
  long image_info = init(log);
  return image_info;
}
