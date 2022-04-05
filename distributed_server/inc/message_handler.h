#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

typedef enum message_type{
  UPDATE_DATA=1,
  SET_GPIO=2,
  ALARM=3
} MessageType;

void read_message(char* message);

#endif