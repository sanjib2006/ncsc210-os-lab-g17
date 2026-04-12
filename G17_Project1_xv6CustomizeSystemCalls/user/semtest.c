#include "kernel/types.h"
#include "user/user.h"

int main(void)
{
  // Initialize semaphore with 0 (locked)
  sem_init(0, 0);
  
  int pid = fork();
  if(pid == 0) {
    // Child process: waits for parent to signal
    printf("Child: waiting on semaphore...\n");
    sem_down(0);  // Will block until parent signals
    printf("Child: semaphore acquired!\n");
    exit(0);
  } else {
    // Parent process
    printf("Parent: child is blocked on semaphore\n");
    
    // Small delay to ensure child is waiting
    int i;
    for(i = 0; i < 10000000; i++);
    
    printf("Parent: signaling semaphore\n");
    sem_up(0);    // Unblock child
    
    wait(0);      // Wait for child
    printf("Parent: child completed\n");
  }
  
  exit(0);
}
