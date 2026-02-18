#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  int sock = socket(AF_INET, SOCK_DGRAM, 0);

  sockaddr_in server_addr{};
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(9090);
  inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

  const char *msg = "Hello from UDP client";

  sendto(sock, msg, strlen(msg) + 1, 0, (sockaddr *)&server_addr,
         sizeof(server_addr));

  char buffer[128]{};
  sockaddr_in reply_addr{};
  socklen_t len = sizeof(reply_addr);

  recvfrom(sock, buffer, sizeof(buffer), 0, (sockaddr *)&reply_addr, &len);

  std::cout << "Server replied: " << buffer << "\n";

  close(sock);
  return 0;
}
