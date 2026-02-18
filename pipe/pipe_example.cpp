#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd[2];

  if (pipe(fd) == -1) {
    perror("pipe");
    return 1;
  }

  pid_t pid = fork();

  if (pid == 0) {
    // CHILD
    close(fd[1]); // close write-end

    char buffer[100];
    read(fd[0], buffer, sizeof(buffer));
    std::cout << "Child received: " << buffer << "\n";

    close(fd[0]);
  } else {
    // PARENT
    close(fd[0]); // close read-end

    const char *msg = "Hello from parent";
    write(fd[1], msg, strlen(msg) + 1);

    close(fd[1]);
  }

  return 0;
}
