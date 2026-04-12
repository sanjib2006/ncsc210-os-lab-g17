#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "user.h"

int main(int argc, char** argv){
  write(1, "GoodBye\n", 8);
  poweroff();
}
