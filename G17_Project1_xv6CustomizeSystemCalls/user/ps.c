// user-space program to display process table via getpinfo()
// Usage: ps

#include "kernel/types.h"
#include "user/user.h"

// Must match kernel/pinfo.h exactly
#define MAX_PROCS 64
struct pinfo {
  int pid[MAX_PROCS];
  int state[MAX_PROCS];
  uint64 sz[MAX_PROCS];
  char name[MAX_PROCS][16];
  int num_procs;
};

// State names matching enum procstate in proc.h
static char *states[] = {
    "UNUSED", "USED", "SLEEPING", "RUNNABLE", "RUNNING", "ZOMBIE",
};

int main(void) {
  struct pinfo pi;

  if (getpinfo(&pi) < 0) {
    fprintf(2, "ps: getpinfo failed\n");
    exit(1);
  }

  printf("PID STATE SIZE(B) NAME\n");
  printf("--- ----- ------- ----\n");

  for (int i = 0; i < pi.num_procs; i++) {
    char *state = "???";
    int s = pi.state[i];
    if (s >= 0 && s < 6)
      state = states[s];
    printf("%d %s %d %s\n", pi.pid[i], state, (int)pi.sz[i], pi.name[i]);
  }

  exit(0);
}
