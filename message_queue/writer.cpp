#include <cerrno>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <mqueue.h>

int main() {
  const char *name = "/my_queue";

  mq_attr attr{};
  attr.mq_maxmsg = 10;
  attr.mq_msgsize = 128;

  mqd_t mq = mq_open(name, O_CREAT | O_WRONLY, 0666, &attr);
  if (mq == (mqd_t)-1) {
    perror("mq_open writer");
    return 1;
  }

  const char *msg = "Hello from message queue";

  // +1 to add '\0'
  if (mq_send(mq, msg, std::strlen(msg) + 1, 0) == -1) {
    perror("mq_send");
    mq_close(mq);
    return 1;
  }

  std::cout << "Message sent\n";
  mq_close(mq);
  return 0;
}
