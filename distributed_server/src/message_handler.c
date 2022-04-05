#include "message_handler.h"
#include <stdio.h>
#include <string.h>
#include "cJSON.h"
#include "app_config.h"
#include "gpio.h"

void set_gpio(cJSON *root){
  cJSON *gpio = cJSON_GetObjectItem(root, "gpio");
  cJSON *value = cJSON_GetObjectItem(root, "value");

  write_gpio(gpio->valueint, value->valueint);
}

void set_alarm(cJSON *root){
  cJSON *value = cJSON_GetObjectItem(root, "value");
  app_config.alarm = value->valueint;
}

int validate_server_and_port(char* server, int port){
  if(strcmp(server, app_config.this_server_ip) != 0 ||
      port != app_config.this_server_port){
    printf("[MESSAGE ERROR] - Message with wrong server or port\n");
    return 0;
  }
  return 1;
}

void read_message(char *message){
  cJSON *root = cJSON_Parse(message);
  cJSON *type = cJSON_GetObjectItem(root, "type");
  cJSON *ip = cJSON_GetObjectItem(root, "server_ip");
  cJSON *port = cJSON_GetObjectItem(root, "port");

  if(!validate_server_and_port(ip->valuestring, port->valueint))
    return;

  switch (type->valueint){
  case SET_GPIO:
    set_gpio(root);
    break;
  case ALARM:
    set_alarm(root);
    break;

  default:
    printf("[MESSAGE ERROR] - Can't handle message type %d\n", type->valueint);
    break;
  }
}
