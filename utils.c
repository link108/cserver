// by cmotevasselani

#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include "utils.h"

void byah(struct sockaddr_in* serverAddr, int port, char* ipv4) {
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(port);
  serverAddr.sin_addr.s_addr = inet_addr(ipv4);
  memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));
}

//void handle_request(int socket, char* key, char* value) {
//  char out_buffer[1024];
//  if (!strcmp(key, "decrement")) {
//    int number_to_decrement = atoi(value);
//    char* message_format = "decrement:%d";
//    sprintf(out_buffer, message_format, number_to_decrement - 1);
//    // why is atoi bad and how to fix? strtol was not working with: (int)strtol(value, .., 10)
//  } else {
//    //strcpy(out_buffer, "Hello World");
//    sprintf(out_buffer, "Hello World");
//  }
//  send(socket, out_buffer, sizeof(out_buffer), 0);
//}
//
//void intHandler(int handle_this, int socket_to_close) {
//  // dont think this does what I intend it to do.. close the port
//  //printf("closing: %d\n", socket_to_close);
//  //close(socket_to_close);
//  exit(0);
//}

//struct sockaddr_in* createSockaddr_in(int port, char* ipv4) {
//  static struct sockaddr_in serverAddr;
//  serverAddr.sin_family = AF_INET;
//  serverAddr.sin_port = htons(port);
//  serverAddr.sin_addr.s_addr = inet_addr(ipv4);
//  memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));
//  return &serverAddr;
//}

