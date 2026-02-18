#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int fd[2];

  // 1. Create a pipe
  if (pipe(fd) == -1) {
    perror("pipe");
    return 1;
  }

  // 2. First fork -> ls
  pid_t pid1 = fork();

  if (pid1 == 0) {
    // CHILD 1 -> ls

    close(fd[0]); // close read-end

    dup2(fd[1], STDOUT_FILENO); // stdout -> pipe

    close(fd[1]);

    execlp("ls", "ls", nullptr);

    perror("exec ls failed");
    return 1;
  }

  // 3. Second fork -> grep
  pid_t pid2 = fork();

  if (pid2 == 0) {
    // CHILD 2 -> grep

    close(fd[1]); // close write-end

    dup2(fd[0], STDIN_FILENO); // stdin <- pipe

    close(fd[0]);

    execlp("grep", "grep", "", nullptr);

    perror("exec grep failed");
    return 1;
  }

  // 4. Parent
  close(fd[0]);
  close(fd[1]);

  waitpid(pid1, nullptr, 0);
  waitpid(pid2, nullptr, 0);

  return 0;
}
