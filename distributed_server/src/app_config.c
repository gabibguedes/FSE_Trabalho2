#include "app_config.h"

#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

char* read_config_file(){
  char * buffer = 0;
  long length;
  FILE * f = fopen ("./config.json", "rb");

  if(f){
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    buffer = malloc(length);
    if (buffer){
      fread(buffer, 1, length, f);
    }
    fclose (f);
  }
  return buffer;
}

void load_config(){
  char* json_config = read_config_file();

  cJSON *root = cJSON_Parse(json_config);
  cJSON *central_server_ip = cJSON_GetObjectItem(root, "ip_servidor_central");
  cJSON *central_server_port = cJSON_GetObjectItem(root, "porta_servidor_central");

  app_config.central_server_ip = central_server_ip->valuestring;
  app_config.central_server_port = central_server_port->valueint;
}

