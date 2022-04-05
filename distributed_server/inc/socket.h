#ifndef SOCKET_H
#define SOCKET_H
#define SOCKET_BUFF_SIZE 100

void init_socket();
void send_socket_message(char* message);
void receive_socket_message(char* message);
void close_socket();

#endif