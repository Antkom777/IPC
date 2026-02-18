#include <cstring>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main() {
  const char *path = "/tmp/mysocket";

  int sock = socket(AF_UNIX, SOCK_STREAM, 0);

  sockaddr_un addr{};
  addr.sun_family = AF_UNIX;
  std::strcpy(addr.sun_path, path);

  connect(sock, (sockaddr *)&addr, sizeof(addr));

  const char *msg = "Hello from client";
  write(sock, msg, strlen(msg) + 1);

  close(sock);
  return 0;
}
