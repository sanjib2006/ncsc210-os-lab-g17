// shared structure for the getpinfo() system call.
// this captures a snapshot of all active processes from the process table.


#define MAX_PROCS 64 // must match NPROC in param.h

struct pinfo {
  int pid[MAX_PROCS];       // process ID
  int state[MAX_PROCS];     // procstate enum (UNUSED=0 … ZOMBIE=5)
  uint64 sz[MAX_PROCS];     // memory size
  char name[MAX_PROCS][16]; // process name
  int num_procs;            // number of active entries filled
};
