#include "app.h"
#include <unistd.h>
#include <stdio.h>
#include "gpio.h"
#include "app_config.h"

void app_loop(){
  int people_count = 0;

  int people_in_idx = get_people_count_in_idx();
  int people_out_idx = get_people_count_out_idx();

  if(people_in_idx == -1 || people_out_idx == -1){
    printf("[GPIO PIN ERROR] - Error on getting people in and out pin.\n");
    return;
  }


  GpioEntry people_in = app_config.inputs[people_in_idx];
  GpioEntry people_out = app_config.inputs[people_out_idx];

  printf("GPIO IN: %d\n", people_in.pin);
  printf("GPIO OUT: %d\n", people_out.pin);

  int in = 0, out = 0;

  while(1){
    int tmp_in = read_gpio(people_in.pin);
    int tmp_out = read_gpio(people_out.pin);

    printf("old in: %d\n", in);
    printf("old out: %d\n", out);

    printf("tmp in: %d\n", tmp_in);
    printf("tmp out: %d\n", tmp_out);

    if(tmp_in != in || tmp_in == 0){
      in = tmp_in;
      people_count = people_count + in;
    }

    if(tmp_out != out || tmp_out == 0){
      out = tmp_out;
      people_count = people_count - out;
    }
    printf("Total: %d\n", people_count);
    // printf("In: %d\n", in);
    // printf("Out: %d\n\n", out);
    usleep(200000);

  }
}

