#include "app.h"

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#include "gpio.h"
#include "app_config.h"
#include "dht22.h"
#include "cJSON.h"
#include "socket.h"
#include "message_handler.h"

// Threads
pthread_t people_count_thread;
pthread_t dht22_thread;
pthread_t socket_listener_thread;

// People count arguments
int people_count = 0;
int people_in = 0;
int people_out = 0;

// Dht22 sensor data
Dht22 sensor;

// GPIO inputs
GpioRead *inputs;
GpioRead *outputs;

void* count_people(void *arg){
  while (1) {
    int tmp_in = read_gpio(app_config.people_in.pin);
    int tmp_out = read_gpio(app_config.people_out.pin);
    if(tmp_in != people_in || tmp_in == 0){
      people_in = tmp_in;
      people_count = people_count + people_in;
    }

    if(tmp_out != people_out || tmp_out == 0){
      people_out = tmp_out;
      people_count = people_count - people_out;
    }
    usleep(200000);
  }
}

void* dht22_sensors_data(void *arg){
  while (1){
    sensor = get_dht22_data(app_config.temp_and_humidity.pin);
  }
}

GpioRead* init_gpio_read(GpioEntry* entries, int size){
  GpioRead * arr = malloc(sizeof(GpioRead) * size);
  for(int i=0; i< size; i++){
    GpioRead gpio;
    gpio.entry = entries[i];
    gpio.value = 0;
    arr[i] = gpio;
  }
  return arr;
}

void init_input_and_outputs_read(){
  inputs = init_gpio_read(app_config.inputs, app_config.inputs_size);
  outputs = init_gpio_read(app_config.outputs, app_config.outputs_size);
}

void read_inputs_and_outputs(){
  for(int i=0; i < app_config.inputs_size; i++)
    inputs[i].value = read_gpio(inputs[i].entry.pin);

  for(int i=0; i < app_config.outputs_size; i++)
    outputs[i].value = read_gpio(outputs[i].entry.pin);
}

void add_gpio_to_json(cJSON * item, char* tag, GpioRead *arr, int size){
  cJSON *gpios = cJSON_CreateArray();
  cJSON_AddItemToObject(item, tag, gpios);
  for(int i=0; i<size; i++){
    cJSON *gpio;
    cJSON_AddItemToArray(gpios, gpio = cJSON_CreateObject());
    cJSON_AddItemToObject(gpio, "tag", cJSON_CreateString(arr[i].entry.label));
    cJSON_AddItemToObject(gpio, "gpio", cJSON_CreateNumber(arr[i].entry.pin));
    cJSON_AddItemToObject(gpio, "value", cJSON_CreateBool(arr[i].value));
  }
}

char* build_json(){
  char* out;
  cJSON *root = cJSON_CreateObject();
  cJSON_AddItemToObject(root, "name", cJSON_CreateString(app_config.name));
  cJSON_AddItemToObject(root, "server_ip", cJSON_CreateString(app_config.this_server_ip));
  cJSON_AddItemToObject(root, "port", cJSON_CreateNumber(app_config.this_server_port));
  cJSON_AddItemToObject(root, "message", cJSON_CreateString("update values"));
  cJSON_AddItemToObject(root, "code", cJSON_CreateNumber(1));

  cJSON *data = cJSON_CreateObject();
  cJSON_AddItemToObject(root, "data", data);
  cJSON_AddItemToObject(data, "temperature", cJSON_CreateNumber(sensor.temperature));
  cJSON_AddItemToObject(data, "humidity", cJSON_CreateNumber(sensor.humidity));
  cJSON_AddItemToObject(data, "people_count", cJSON_CreateNumber(people_count));
  cJSON_AddItemToObject(data, "alarm", cJSON_CreateBool(app_config.alarm));

  add_gpio_to_json(data, "inputs", inputs, app_config.inputs_size);
  add_gpio_to_json(data, "outputs", outputs, app_config.outputs_size);

  out = cJSON_Print(root);
  cJSON_Delete(root);
  return out;
}

void print_inputs(){
  for(int i=0; i<app_config.inputs_size; i++){
    printf("%s: %d\n", inputs[i].entry.label, inputs[i].value);
  }
}

void *listen_socket(void *arg){
  while (1){
    char *message = malloc(100);
    receive_socket_message(message);\
    if(strlen(message) > 0){
      read_message(message);
    }
  }
}

void app_loop(){
  pthread_create(&people_count_thread, NULL, count_people, NULL);
  pthread_create(&dht22_thread, NULL, dht22_sensors_data, NULL);
  pthread_create(&socket_listener_thread, NULL, listen_socket, NULL);

  init_input_and_outputs_read();

  while(1){
    read_inputs_and_outputs();
    send_socket_message(build_json());
    sleep(1);
  }

  pthread_join(people_count_thread, NULL);
  pthread_join(dht22_thread, NULL);
  pthread_join(socket_listener_thread, NULL);
}

