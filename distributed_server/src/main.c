#include <stdio.h>
#include "app_config.h"
#include "socket.h"
#include "gpio.h"
#include "app.h"

int main(){
  load_config();
  // init_socket();
  // send_socket_message("oie");
  // close_socket();
  initialize_gpio();
  // read_inputs();
  app_loop();
  return 0;
}
