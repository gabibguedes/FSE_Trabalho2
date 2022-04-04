#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include "gpio.h"
typedef struct app_config {
  char* central_server_ip;
  int central_server_port;

  char* this_server_ip;
  int this_server_port;

  char* name;

  GpioEntry* inputs;
  GpioEntry* outputs;
  int inputs_size;
  int outputs_size;

  GpioEntry temp_and_humidity;
  GpioEntry people_in;
  GpioEntry people_out;
} AppConfig;

AppConfig app_config;
void load_config();
int get_people_count_in_idx();
int get_people_count_out_idx();
void print_gpio(GpioEntry gpio);

#endif
