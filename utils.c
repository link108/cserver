// by cmotevasselani

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include "utils.h"

void createSockaddr_in(struct sockaddr_in* serverAddr, int port, char* ipv4) {
  serverAddr->sin_family = AF_INET;
  serverAddr->sin_port = htons(port);
  serverAddr->sin_addr.s_addr = inet_addr(ipv4);
  memset(serverAddr->sin_zero, '\0', sizeof(serverAddr->sin_zero));
}

void handleRequest(int socket, char in_buffer[], char* sender) {
  char * inKey, * inValue;
  char * outKey, * outValue;
  setKeyValue(&inKey, &inValue, in_buffer);
  processKeyValue(&inKey, &inValue, &outKey, &outValue);
  sendData(socket, outKey, outValue, sender);
}

void sendData(int socket, char* key, char* value, char* sender) {
  char* out_buffer = (char*)malloc(1024);
  char* message_format = "%s:%d";
  int num = atoi(value);
  printf("Key: %s\n", key);
  printf("Num: %d\n", num);
  sprintf(out_buffer, message_format, key, num - 1);
  printf("%s sent: '", sender);
  printf("%s", out_buffer);
  printf("\n");
  int sentBytes = send(socket, out_buffer, strlen(out_buffer), 0);
  printf("sent %d bytes from %s\n", sentBytes, sender);
  if (sentBytes == -1) {
    printf("error: %s", strerror(errno));
  }
}

void setKeyValue(char** key, char** value, char in_buffer[]) {
  int colon_pos = (int)(strchr(in_buffer, ':') - in_buffer);
  in_buffer[colon_pos] = '\0';
  *key = &in_buffer[0];
  *value = &in_buffer[colon_pos + 1];
}

void processKeyValue(char** inKey, char** inValue, char** outKey, char** outValue) {
  printf("processing key/value on server side");
  if (0 == strcmp("decrement", *inKey)) {
    printf("%s", "decrementing");
    int retNum = atoi(*inValue);
    if (retNum == -1) {
      printf("error: %s", strerror(errno));
    }
    retNum--;
    printf("ret: %d\n", retNum);
    printf("ret addr: %x\n", &retNum);
    printf("inKey: %s\n", inKey);
    printf("inKey deref: %s\n", *inKey);
    *outValue = (char*)&retNum;
    *outKey = *inKey;
    printf("outKey: %s\n", *outKey);
    printf("outValue: %s\n", *outValue);
    printf("server: key: %s, value: %s", *outKey, *outValue);
  } 
  //else if ("increment" == *inKey)
  //*outKey = *inKey;
  //*outValue = *inValue;
}







