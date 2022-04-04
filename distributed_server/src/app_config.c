#include "app_config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h"
#include "gpio.h"

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

GpioEntry gpio_from_json(cJSON *item){
  GpioEntry gpio;

  cJSON *tag = cJSON_GetObjectItem(item, "tag");
  cJSON *gpio_pin = cJSON_GetObjectItem(item, "gpio");

  gpio.type = get_gpio_type(tag->valuestring);
  gpio.pin = gpio_pin->valueint;
  gpio.label = tag->valuestring;

  return gpio;
}

GpioEntry* add_gpio_to_config(cJSON *obj_keys, int arr_size){
  GpioEntry* arr = malloc(sizeof(GpioEntry) * arr_size);

  for(int i=0; i < arr_size; i++){
    cJSON *subitem = cJSON_GetArrayItem(obj_keys, i);
    arr[i] = gpio_from_json(subitem);
  }
  return arr;
}

void print_gpio(GpioEntry gpio){
  printf("%s\ntype: %d, gpio: %d\n\n", gpio.label, gpio.type, gpio.pin);
}

int find_input_idx_type(int type){
  for(int i = 0; i < app_config.inputs_size; i++){
    if(app_config.inputs[i].type == type)
      return i;
  }
  return -1;
}

void get_people_count_gpios(){
  int people_in_idx = find_input_idx_type(PEOPLE_COUNT_IN);
  int people_out_idx = find_input_idx_type(PEOPLE_COUNT_OUT);

  if (people_in_idx == -1 || people_out_idx == -1) {
    printf("[GPIO PIN ERROR] - Error on getting people in and out pin.\n");
    return;
  }

  app_config.people_in = app_config.inputs[people_in_idx];
  app_config.people_out = app_config.inputs[people_out_idx];
}

void load_config(){
  char* json_config = read_config_file();

  root = cJSON_Parse(json_config);
  cJSON *central_server_ip = cJSON_GetObjectItem(root, "ip_servidor_central");
  cJSON *central_server_port = cJSON_GetObjectItem(root, "porta_servidor_central");
  cJSON *name = cJSON_GetObjectItem(root, "nome");

  app_config.central_server_ip = central_server_ip->valuestring;
  app_config.central_server_port = central_server_port->valueint;
  app_config.name = name->valuestring;

  cJSON *inputs = cJSON_GetObjectItem(root, "inputs");
  app_config.inputs_size = cJSON_GetArraySize(inputs);
  app_config.inputs = add_gpio_to_config(inputs, app_config.inputs_size);

  cJSON *outputs = cJSON_GetObjectItem(root, "outputs");
  app_config.outputs_size = cJSON_GetArraySize(outputs);
  app_config.outputs = add_gpio_to_config(outputs, app_config.outputs_size);

  cJSON *temp_and_hum = cJSON_GetObjectItem(root, "sensor_temperatura");
  app_config.temp_and_humidity = add_gpio_to_config(temp_and_hum, 1)[0];

  get_people_count_gpios();
}
