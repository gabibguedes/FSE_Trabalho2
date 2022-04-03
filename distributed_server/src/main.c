#include <stdio.h>
#include "app_config.h"
#include "socket.h"

int main(){
  load_config();
  printf("%s:%d\n", app_config.central_server_ip, app_config.central_server_port);
  init_socket();
  send_socket_message("oie");
  close_socket();
  return 0;
}
