#include "gpio.h"
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <string.h>

#include "app_config.h"

void initialize_gpio(){
  wiringPiSetupGpio();

  for(int i=0; i < app_config.inputs_size; i++)
    pinMode(app_config.inputs[i].pin, INPUT);
}

int read_gpio(int pin){
  return digitalRead(pin);
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

  if (strstr(tag, "Temperatura e Umidade"))
    return TEMP_AND_HUMIDITY;

  return NOT_FOUND;
}
