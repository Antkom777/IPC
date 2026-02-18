#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main() {
  const char *path = "/tmp/mysocket";

  int server_fd = socket(AF_UNIX, SOCK_STREAM, 0);

  sockaddr_un addr{};
  addr.sun_family = AF_UNIX;
  std::strcpy(addr.sun_path, path);

  unlink(path); // remove any existing socket file

  bind(server_fd, (sockaddr *)&addr, sizeof(addr));
  listen(server_fd, 1);

  std::cout << "Waiting for connection...\n";

  int client_fd = accept(server_fd, nullptr, nullptr);

  char buffer[128];
  read(client_fd, buffer, sizeof(buffer));

  std::cout << "Received: " << buffer << "\n";

  close(client_fd);
  close(server_fd);
  unlink(path);

  return 0;
}
