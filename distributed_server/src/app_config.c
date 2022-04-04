#include "app_config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"

cJSON *root;

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

GpioType get_gpio_type(char* tag){
  if(strstr(tag, "Lâmpada") && strstr(tag, "01"))
    return LAMP_ROOM_1;

  if(strstr(tag, "Lâmpada") && strstr(tag, "02"))
    return LAMP_ROOM_2;

  if(strstr(tag, "Lâmpadas do Corredor"))
    return LAMP_HALL;

  if(strstr(tag, "Ar-Condicionado"))
    return AIR_CONDITIONING;

  if(strstr(tag, "Sensor de Presença"))
    return PRESENCE;

  if(strstr(tag, "Sensor de Fumaça"))
    return SMOKE;

  if(strstr(tag, "Janela") && strstr(tag, "01"))
    return WINDOW_ROOM_1;

  if(strstr(tag, "Janela") && strstr(tag, "02"))
    return WINDOW_ROOM_2;

  if(strstr(tag ,"Porta Entrada"))
    return DOOR;

  if(strstr(tag, "Pessoas Entrando"))
    return PEOPLE_COUNT_IN;

  if(strstr(tag, "Pessoas Saindo"))
    return PEOPLE_COUNT_OUT;

  if(strstr(tag, "Aspersor"))
    return WATER_SPRINKLER;

  return NOT_FOUND;
}

GpioEntry* add_gpio_to_config(cJSON *obj_keys, int arr_size){
  GpioEntry* arr = malloc(sizeof(GpioEntry) * arr_size);

  for(int i=0; i < arr_size; i++){
    GpioEntry entry;

    cJSON *subitem = cJSON_GetArrayItem(obj_keys, i);
    cJSON *tag = cJSON_GetObjectItem(subitem, "tag");
    cJSON *gpio_pin = cJSON_GetObjectItem(subitem, "gpio");

    entry.type = get_gpio_type(tag->valuestring);
    entry.pin = gpio_pin->valueint;
    arr[i] = entry;
  }
  return arr;
}

void load_config(){
  char* json_config = read_config_file();

  root = cJSON_Parse(json_config);
  cJSON *central_server_ip = cJSON_GetObjectItem(root, "ip_servidor_central");
  cJSON *central_server_port = cJSON_GetObjectItem(root, "porta_servidor_central");

  app_config.central_server_ip = central_server_ip->valuestring;
  app_config.central_server_port = central_server_port->valueint;

  cJSON *inputs = cJSON_GetObjectItem(root, "inputs");
  app_config.inputs_size = cJSON_GetArraySize(inputs);
  app_config.inputs = add_gpio_to_config(inputs, app_config.inputs_size);

  cJSON *outputs = cJSON_GetObjectItem(root, "outputs");
  app_config.outputs_size = cJSON_GetArraySize(outputs);
  app_config.outputs = add_gpio_to_config(outputs, app_config.outputs_size);
}

int get_people_count_in_idx(){
  for(int i = 0; i < app_config.inputs_size; i++){
    if(app_config.inputs[i].type == PEOPLE_COUNT_IN)
      return i;
  }
  return -1;
}

int get_people_count_out_idx(){
  for(int i = 0; i < app_config.inputs_size; i++){
    if(app_config.inputs[i].type == PEOPLE_COUNT_OUT)
      return i;
  }
  return -1;
}
