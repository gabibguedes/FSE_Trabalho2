#include "gpio.h"
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include "app_config.h"

void initialize_gpio(){
  wiringPiSetupGpio();

  for(int i=0; i < app_config.inputs_size; i++)
    pinMode(app_config.inputs[i].pin, INPUT);
}

void read_inputs(){
  for(int i=0; i < app_config.inputs_size; i++)
    printf("gpio:%d, value: %d\n", app_config.inputs[i].pin, digitalRead(app_config.inputs[i].pin));
}

int read_gpio(int pin){
  return digitalRead(pin);
}
