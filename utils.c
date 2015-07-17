// by cmotevasselani

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include "utils.h"

void createSockaddr_in(struct sockaddr_in* serverAddr, int port, char* ipv4) {
  serverAddr->sin_family = AF_INET;
  serverAddr->sin_port = htons(port);
  serverAddr->sin_addr.s_addr = inet_addr(ipv4);
  memset(serverAddr->sin_zero, '\0', sizeof(serverAddr->sin_zero));
}

void handle_request(int socket, char in_buffer[], char* sender) {
  char* key;
  char* value;
  setKeyValue(&key, &value, in_buffer);

  char out_buffer[1024];
  if (!strcmp(key, "decrement")) {
    int number_to_decrement = atoi(value);
    char* message_format = "decrement:%d";
    sprintf(out_buffer, message_format, number_to_decrement - 1);
    printf("%s sent: '", sender);
    printf(message_format, number_to_decrement - 1);
    printf("'\n");
    // why is atoi bad and how to fix? strtol was not working with: (int)strtol(value, .., 10)
  } else {
    sprintf(out_buffer, "Hello World");
  }
  int sentBytes = send(socket, out_buffer, sizeof(out_buffer), 0);

}

void setKeyValue(char** key, char** value, char in_buffer[]) {
  int colon_pos = (int)(strchr(in_buffer, ':') - in_buffer);
  in_buffer[colon_pos] = '\0';
  *key = &in_buffer[0];
  *value = &in_buffer[colon_pos + 1];
}


