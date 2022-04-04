#ifndef DHT22_H
#define DHT22_H

typedef struct dht22
{
  float temperature;
  float humidity;
} Dht22;

Dht22 get_dht22_data(int pin);

#endif