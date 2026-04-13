#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
  int pid = fork();

  if(pid < 0){
    printf("fork failed\n");
    exit(1);
  }

  if(pid == 0){
    // Child
    char buf[128];

    // Wait until message arrives
    while(recvmsg(buf) < 0)
      ;

    printf("child received: %s\n", buf);
    exit(0);

  } else {
    // Parent

    if(sendmsg(pid, "hello from parent") < 0){
      printf("parent: sendmsg failed\n");
      exit(1);
    }

    // Wait for child to finish printing FIRST
    wait(0);

    printf("parent sent message to pid %d\n", pid);
  }

  exit(0);
}