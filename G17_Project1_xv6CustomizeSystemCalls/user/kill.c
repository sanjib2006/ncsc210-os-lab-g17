#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char **argv)
{
  if(argc < 2){
    fprintf(2, "usage: kill pid\n");
    exit(1);
  }

  int pid = atoi(argv[1]);

  char buf[20];
  int mode = 0, time = 0;

  printf("0: normal kill\n1: immediate kill\n2: kill after time\n");
  printf("Enter choice: ");

  gets(buf, sizeof(buf));
  mode = atoi(buf);

  if(mode == 2){
    printf("Enter time (ticks): ");
    gets(buf, sizeof(buf));
    time = atoi(buf);
    printf("Process %d will be killed after %d ticks.\n", pid, time);
  }

  if(kill(pid, mode, time) < 0)
    printf("kill failed\n");
  else if(mode != 2)
    printf("Kill signal sent successfully to process %d.\n", pid);

  exit(0);
}