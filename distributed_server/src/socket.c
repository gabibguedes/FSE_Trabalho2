#include "socket.h"

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "app_config.h"

int socket_client;
struct sockaddr_in server_addr;
unsigned short server_port;
char *server_ip;

void init_socket(){
  server_port = (unsigned short) app_config.central_server_port;
  server_ip = app_config.central_server_ip;

  // Create socket
  if ((socket_client = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    printf("[SOCKET ERROR] - Error on initializing socket.\n");

  // Builds struct sockaddr_in
  memset(&server_addr, 0, sizeof(server_addr)); // Clear structure
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr(server_ip);
  server_addr.sin_port = htons(server_port);

  // Connect
  if (connect(socket_client, (struct sockaddr *)&server_addr,
              sizeof(server_addr)) < 0)
    printf("[SOCKET ERROR] - Error on connecting socket.\n");

}

void send_socket_message(char* message) {
  unsigned int message_size = strlen(message);
  int bytes_received, bytes_size = 0;
  char buffer[SOCKET_BUFF_SIZE];

  // Send message
  if (send(socket_client, message, message_size, 0) != message_size)
    printf("[SOCKET ERROR] - Error on sending message\n");

  // Receives response
  while (bytes_size < message_size) {
    bytes_received = recv(socket_client, buffer, SOCKET_BUFF_SIZE - 1, 0);

    if (bytes_received <= 0)
      printf("[SOCKET ERROR] - Message not received.\n");

    bytes_size += bytes_received;
    buffer[bytes_received] = '\0';
    printf("[SOCKET] - Message received: %s\n", buffer);
  }

}

void close_socket(){
  close(socket_client);
}
