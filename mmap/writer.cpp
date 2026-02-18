#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <sys/mman.h>
#include <unistd.h>

int main() {
  const char *filename = "shared.dat";

  int fd = open(filename, O_CREAT | O_RDWR, 0666);

  ftruncate(fd, 4096); // set file size to 4096 bytes

  void *ptr = mmap(nullptr, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  if (ptr == MAP_FAILED) {
    perror("mmap");
    return 1;
  }

  strcpy((char *)ptr, "Hello via mmap!");

  std::cout << "Message written\n";

  munmap(ptr, 4096);
  close(fd);

  return 0;
}
