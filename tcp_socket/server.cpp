#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);

  sockaddr_in addr{};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);       // port 8080
  addr.sin_addr.s_addr = INADDR_ANY; // listen on all interfaces

  bind(server_fd, (sockaddr *)&addr, sizeof(addr));
  listen(server_fd, 1);

  std::cout << "Waiting on port 8080...\n";

  int client_fd = accept(server_fd, nullptr, nullptr);

  char buffer[128]{};
  read(client_fd, buffer, sizeof(buffer));

  std::cout << "Received: " << buffer << "\n";

  const char *reply = "Hello from server";
  write(client_fd, reply, strlen(reply) + 1);

  close(client_fd);
  close(server_fd);

  return 0;
}
