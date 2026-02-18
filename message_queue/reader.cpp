#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <mqueue.h>

int main() {
  const char *name = "/my_queue";

  mqd_t mq = mq_open(name, O_RDONLY);
  if (mq == (mqd_t)-1) {
    perror("mq_open reader");
    return 1;
  }

  mq_attr attr{};
  if (mq_getattr(mq, &attr) == -1) {
    perror("mq_getattr");
    mq_close(mq);
    return 1;
  }

  // buffer >= mq_msgsize
  std::string buffer(static_cast<size_t>(attr.mq_msgsize), '\0');

  ssize_t n = mq_receive(mq, buffer.data(), buffer.size(), nullptr);
  if (n == -1) {
    perror("mq_receive");
    mq_close(mq);
    return 1;
  }

  // If the message doesn't have '\0' — add it for safe printing
  if (n == static_cast<ssize_t>(buffer.size()))
    buffer.back() = '\0';
  else
    buffer[static_cast<size_t>(n)] = '\0';

  std::cout << "Received: " << buffer.c_str() << "\n";

  mq_close(mq);
  mq_unlink(name);
  return 0;
}
