#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  int sock = socket(AF_INET, SOCK_STREAM, 0);

  sockaddr_in addr{};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(8080);
  inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

  connect(sock, (sockaddr *)&addr, sizeof(addr));

  const char *msg = "Hello from client";
  write(sock, msg, strlen(msg) + 1);

  char buffer[128]{};
  read(sock, buffer, sizeof(buffer));

  std::cout << "Server replied: " << buffer << "\n";

  close(sock);
  return 0;
}
