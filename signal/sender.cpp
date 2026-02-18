#include <iostream>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cout << "Usage: ./sender <PID>\n";
    return 1;
  }

  int pid = std::stoi(argv[1]);

  kill(pid, SIGUSR1);

  return 0;
}
