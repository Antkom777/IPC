#include <cstdlib>
#include <iostream>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Usage: ./sender <PID>\n";
    return 1;
  }

  int pid = std::atoi(argv[1]);

  union sigval value;
  value.sival_int = 42;

  if (sigqueue(pid, SIGUSR1, value) == -1) {
    perror("sigqueue");
    return 1;
  }

  std::cout << "Signal sent with value 42\n";
  return 0;
}
