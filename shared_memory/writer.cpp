#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
  const char *name = "/my_shared_mem";

  int fd = shm_open(name, O_CREAT | O_RDWR, 0666);

  ftruncate(fd, 4096);

  void *ptr = mmap(0, 4096, PROT_WRITE, MAP_SHARED, fd, 0);

  const char *msg = "Hello from shared memory";
  std::memcpy(ptr, msg, strlen(msg) + 1);

  std::cout << "Message written\n";

  munmap(ptr, 4096);
  close(fd);

  return 0;
}
