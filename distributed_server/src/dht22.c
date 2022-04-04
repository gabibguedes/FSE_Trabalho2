/*
 *  dht.c:
 *      Author: Juergen Wolf-Hofer
 *      based on / adapted from http://www.uugear.com/portfolio/read-dht1122-temperature-humidity-sensor-from-raspberry-pi/
 *	reads temperature and humidity from DHT11 or DHT22 sensor and outputs according to selected mode
 */

#include "dht22.h"
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// CONSTANTS
#define MAX_TIMINGS 85
#define DEBUG 0
#define WAIT_TIME 2000

// GLOBAL VARIABLES
uint8_t dht_pin = 3; // default GPIO 22 (wiringPi 3)
char mode = 'c';     // valid modes are c, f, h

int data[5] = {0, 0, 0, 0, 0};
float temp_cels = -1;
float humidity = -1;

// FUNCTION DECLARATIONS
int init();
void printUsage();
int read_dht_data();

// FUNCTION DEFINITIONS
int read_dht_data()
{
  uint8_t laststate = HIGH;
  uint8_t counter = 0;
  uint8_t j = 0;
  uint8_t i;

  data[0] = data[1] = data[2] = data[3] = data[4] = 0;

  /* pull pin down for 18 milliseconds */
  pinMode(dht_pin, OUTPUT);
  digitalWrite(dht_pin, LOW);
  delay(18);

  /* prepare to read the pin */
  pinMode(dht_pin, INPUT);

  /* detect change and read data */
  for (i = 0; i < MAX_TIMINGS; i++)
  {
    counter = 0;
    while (digitalRead(dht_pin) == laststate)
    {
      counter++;
      delayMicroseconds(1);
      if (counter == 255)
      {
        break;
      }
    }
    laststate = digitalRead(dht_pin);

    if (counter == 255)
      break;

    /* ignore first 3 transitions */
    if ((i >= 4) && (i % 2 == 0))
    {
      /* shove each bit into the storage bytes */
      data[j / 8] <<= 1;
      if (counter > 16)
        data[j / 8] |= 1;
      j++;
    }
  }

  /*
   * check we read 40 bits (8bit x 5 ) + verify checksum in the last byte
   * print it out if data is good
   */
  if ((j >= 40) && (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)))
  {
    float h = (float)((data[0] << 8) + data[1]) / 10;
    if (h > 100)
    {
      h = data[0]; // for DHT11
    }
    float c = (float)(((data[2] & 0x7F) << 8) + data[3]) / 10;
    if (c > 125)
    {
      c = data[2]; // for DHT11
    }
    if (data[2] & 0x80)
    {
      c = -c;
    }
    temp_cels = c;
    humidity = h;
    if (DEBUG)
      printf("read_dht_data() Humidity = %.1f %% Temperature = %.1f *C\n", humidity, temp_cels);
    return 0; // OK
  }
  else
  {
    if (DEBUG)
      printf("read_dht_data() Data not good, skip\n");
    temp_cels = humidity = -1;
    return 1; // NOK
  }
}

void printUsage()
{
  fprintf(stdout, "Usage: dht22 t|h pin\n"
                  "             c   .. temperature celsius\n"
                  "             f   .. temperature fahrenheit\n"
                  "             h   .. humidity\n"
                  "             pin .. GPIO pin (wiringPi numbering)\n");
}

int init()
{
  if (wiringPiSetup() == -1)
  {
    fprintf(stderr, "Failed to initialize wiringPi\n");
    exit(1);
    return 1;
  }
  return 0;
}

Dht22 get_dht22_data(int pin){
  Dht22 sensor;
  dht_pin = pin;
  int done = 0;

  if (DEBUG)
    fprintf(stdout, "Reading DHT22 ... sensorPIN=%i\n", dht_pin);

  init();

  while (!done)
  {
    done = !read_dht_data();
    delay(WAIT_TIME);
  }

  sensor.temperature = temp_cels;
  sensor.humidity = humidity;

  if (DEBUG)
    printf("get_dht22_data() Humidity = %.1f %% Temperature = %.1f *C\n", humidity, temp_cels);

  return sensor;
}