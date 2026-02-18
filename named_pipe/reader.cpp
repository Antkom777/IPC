#include <fcntl.h>
#include <iostream>
#include <unistd.h>

int main() {
  char buffer[128];

  int fd = open("myfifo", O_RDONLY); // ← читання

  ssize_t n = read(fd, buffer, sizeof(buffer));
  write(STDOUT_FILENO, buffer, n);

  close(fd);
  return 0;
}
