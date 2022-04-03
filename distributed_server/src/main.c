#include <stdio.h>
#include "cJSON.h"

int main(){
  char json_string[] = "{\"name\": \"Jack (\"Bee\") Nimble\",\"format\": {\"type\": \"rect\" }}";

  cJSON *root = cJSON_Parse(json_string);

  cJSON *format = cJSON_GetObjectItem(root, "format");
  cJSON *type = cJSON_GetObjectItem(format, "type");
  if (cJSON_IsString(type))
  {
    printf("type: %s\n", type->valuestring);
  }
  // cJSON_Delete(root);
  return 0;
}
