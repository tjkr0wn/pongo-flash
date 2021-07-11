asm(".space 0x620, 0x0\n\t");
asm(".text\n");

extern long init(void);

long read_blockdev(void (*print_log)(const char *fmt, ...)) {
  long image_info = init();
  print_log("Custom api for code exec is functional...\n");
  return image_info;
}
