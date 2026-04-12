#include "kernel/types.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int ticks = 1000; // Default: sleep for a long time
  if(argc > 1)
    ticks = atoi(argv[1]);

  printf("Dummy process %d started, sleeping for %d ticks...\n", getpid(), ticks);
  sleep(ticks);
  printf("Dummy process %d waking up and exiting.\n", getpid());
  exit(0);
}
