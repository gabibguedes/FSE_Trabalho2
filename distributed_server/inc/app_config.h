#ifndef APP_CONFIG_H
#define APP_CONFIG_H

typedef struct app_config {
  char* central_server_ip;
  int central_server_port;
} AppConfig;

AppConfig app_config;
void load_config();

#endif
