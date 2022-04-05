#ifndef GPIO_H
#define GPIO_H

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
  TEMP_AND_HUMIDITY = 13,
  NOT_FOUND = 404
} GpioType;

typedef struct gpio_entry {
  GpioType type;
  int pin;
  char* label;
} GpioEntry;

typedef struct gpio_read {
  GpioEntry entry;
  int value;
} GpioRead;

void initialize_gpio();
int read_gpio(int pin);
void write_gpio(int pin, int value);
GpioType get_gpio_type(char *tag);

#endif