#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"
#include "vm.h"

extern struct proc proc[];

uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  kexit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return kfork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return kwait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int t;
  int n;

  argint(0, &n);
  argint(1, &t);
  addr = myproc()->sz;

  if(t == SBRK_EAGER || n < 0) {
    if(growproc(n) < 0) {
      return -1;
    }
  } else {
    // Lazily allocate memory for this process: increase its memory
    // size but don't allocate memory. If the processes uses the
    // memory, vmfault() will allocate it.
    if(addr + n < addr)
      return -1;
    if(addr + n > TRAPFRAME)
      return -1;
    myproc()->sz += n;
  }
  return addr;
}

uint64
sys_pause(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kkill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

<<<<<<< Updated upstream
uint64
sys_getpinfo(void)
{
  uint64 addr;
  argaddr(0, &addr);
  return kgetpinfo(addr);
=======
// sendmsg(int pid, char *msg)
// Copies msg from caller's address space into the target process's msg buffer.
// Returns 0 on success, -1 if pid not found or msg copy fails.
uint64
sys_sendmsg(void)
{
  int pid;
  char msg[128];
  struct proc *p;

  argint(0, &pid);
  if(argstr(1, msg, sizeof(msg)) < 0)
    return -1;

  for(p = proc; p < &proc[NPROC]; p++){
    acquire(&p->lock);
    if(p->pid == pid){
      safestrcpy(p->msg, msg, sizeof(p->msg));
      p->has_msg = 1;
      release(&p->lock);
      return 0;
    }
    release(&p->lock);
  }
  return -1;
}

// recvmsg(char *buf)
// Copies the waiting message out to the caller's buffer.
// Returns 0 on success, -1 if no message is waiting or copyout fails.
uint64
sys_recvmsg(void)
{
  uint64 addr;
  struct proc *p = myproc();

  argaddr(0, &addr);

  if(p->has_msg == 0)
    return -1;

  if(copyout(p->pagetable, addr, p->msg, sizeof(p->msg)) < 0)
    return -1;

  p->has_msg = 0;
  return 0;
>>>>>>> Stashed changes
}
