#include <cstring>
#include <fcntl.h>
#include <unistd.h>

int main() {
  int fd = open("myfifo", O_WRONLY); // ← запис

  const char *msg = "Hello from writer\n";
  write(fd, msg, strlen(msg));

  close(fd);
  return 0;
}
