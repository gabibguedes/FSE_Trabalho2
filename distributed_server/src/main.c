#include <stdio.h>
#include <signal.h>
#include <string.h>
#include "app_config.h"
#include "socket.h"
#include "gpio.h"
#include "app.h"

struct sigaction old_action;

void sigint_handler(int sig_no) {
  printf("Programa encerrado\n");
  close_socket();

  sigaction(SIGINT, &old_action, NULL);
  kill(0, SIGINT);
}

int main(){
  struct sigaction action;
  memset(&action, 0, sizeof(action));
  action.sa_handler = &sigint_handler;
  sigaction(SIGINT, &action, &old_action);

  load_config();
  init_socket();
  initialize_gpio();
  app_loop();

  return 0;
}
