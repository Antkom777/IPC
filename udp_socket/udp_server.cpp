#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  int sock = socket(AF_INET, SOCK_DGRAM, 0);

  sockaddr_in addr{};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(9090);
  addr.sin_addr.s_addr = INADDR_ANY;

  bind(sock, (sockaddr *)&addr, sizeof(addr));

  std::cout << "UDP server waiting on port 9090...\n";

  char buffer[128]{};
  sockaddr_in client_addr{};
  socklen_t len = sizeof(client_addr);

  ssize_t n =
      recvfrom(sock, buffer, sizeof(buffer), 0, (sockaddr *)&client_addr, &len);

  std::cout << "Received: " << buffer << "\n";

  const char *reply = "Hello from UDP server";

  sendto(sock, reply, strlen(reply) + 1, 0, (sockaddr *)&client_addr, len);

  close(sock);
  return 0;
}
