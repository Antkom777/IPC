#include <fcntl.h>
#include <iostream>
#include <sys/mman.h>
#include <unistd.h>

int main() {
  const char *filename = "shared.dat";

  int fd = open(filename, O_RDWR, 0666);

  void *ptr = mmap(nullptr, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  if (ptr == MAP_FAILED) {
    perror("mmap");
    return 1;
  }

  std::cout << "Read: " << (char *)ptr << "\n";

  munmap(ptr, 4096);
  close(fd);

  return 0;
}
