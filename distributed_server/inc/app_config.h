#ifndef APP_CONFIG_H
#define APP_CONFIG_H

typedef enum gpio_type {
  LAMP_ROOM_1 = 1,
  LAMP_ROOM_2 = 2,
  LAMP_HALL = 3,
  AIR_CONDITIONING  = 4,
  PRESENCE = 5,
  SMOKE = 6,
  WINDOW_ROOM_1 = 7,
  WINDOW_ROOM_2 = 8,
  DOOR = 9,
  PEOPLE_COUNT_IN = 10,
  PEOPLE_COUNT_OUT = 11,
  WATER_SPRINKLER = 12,
  NOT_FOUND = 404
} GpioType;

typedef struct gpio_entry {
  GpioType type;
  int pin;

} GpioEntry;

typedef struct app_config {
  char* central_server_ip;
  int central_server_port;
  GpioEntry* inputs;
  GpioEntry* outputs;
  int inputs_size;
  int outputs_size;
} AppConfig;

AppConfig app_config;
void load_config();
int get_people_count_in_idx();
int get_people_count_out_idx();

#endif
