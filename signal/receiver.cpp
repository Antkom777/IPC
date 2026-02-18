#include <iostream>
#include <signal.h>
#include <unistd.h>

void handler(int signum) { std::cout << "Received signal: " << signum << "\n"; }

int main() {
  signal(SIGUSR1, handler);

  std::cout << "My PID: " << getpid() << "\n";
  std::cout << "Waiting for signal...\n";

  while (true) {
    pause(); // waiting for a signal
  }

  return 0;
}
