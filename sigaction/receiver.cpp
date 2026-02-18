#include <cstring>
#include <errno.h>
#include <iostream>
#include <signal.h>
#include <unistd.h>

void handler(int signum, siginfo_t *info, void *context) {
  write(1, "\n--- Signal handler start ---\n", 30);

  char buffer[256];

  // signal number
  snprintf(buffer, sizeof(buffer), "Signal number: %d\n", signum);
  write(1, buffer, strlen(buffer));

  // sender PID
  snprintf(buffer, sizeof(buffer), "Sender PID: %d\n", info->si_pid);
  write(1, buffer, strlen(buffer));

  // sender UID
  snprintf(buffer, sizeof(buffer), "Sender UID: %d\n", info->si_uid);
  write(1, buffer, strlen(buffer));

  // value passed
  snprintf(buffer, sizeof(buffer), "Value passed: %d\n",
           info->si_value.sival_int);
  write(1, buffer, strlen(buffer));

  write(1, "--- Signal handler end ---\n", 28);
}

int main() {
  struct sigaction sa;

  memset(&sa, 0, sizeof(sa));

  // use extended handler
  sa.sa_sigaction = handler;

  // block SIGUSR2 during SIGUSR1
  sigemptyset(&sa.sa_mask);
  sigaddset(&sa.sa_mask, SIGUSR2);

  // flags
  sa.sa_flags = SA_SIGINFO    // receive siginfo_t
                | SA_RESTART  // restart system calls
                | SA_NODEFER; // do not block the same signal

  if (sigaction(SIGUSR1, &sa, nullptr) == -1) {
    perror("sigaction");
    return 1;
  }

  std::cout << "Receiver PID: " << getpid() << std::endl;
  std::cout << "Waiting for SIGUSR1...\n";

  while (true) {
    pause();
  }

  return 0;
}
