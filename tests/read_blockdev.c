asm(".section .text\n");
extern void * _init(void);

int main(void) {
  int image_info = _init();
  return image_info;
}
