#include <fcntl.h>
#include <iostream>
#include <sys/mman.h>
#include <unistd.h>

int main() {
  const char *name = "/my_shared_mem";

  int fd = shm_open(name, O_RDONLY, 0666);

  void *ptr = mmap(0, 4096, PROT_READ, MAP_SHARED, fd, 0);

  std::cout << "Received: " << static_cast<char *>(ptr) << "\n";

  munmap(ptr, 4096);
  close(fd);

  shm_unlink(name); // remove the segment

  return 0;
}
