#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  if(argc < 2) {
    printf(2, "usage: policy id...\nid's:\n0 - Uniform time distribution\n1 - Priority scheduling\n2 - Dynamic tickets allocation\n");
    exit(0);
  }
  int i = atoi(argv[1]);
  asm("push %0; movl $23, %%eax; int $64;"
		:
		:"r"(i)
		:"%eax");
}