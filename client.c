// by cmotevasselani
// Basic test client

#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>
#include "utils.h"

void error(const char* msg) {
  perror(msg);
}

int main() {
  static const int SERVER_PORT = 7892;
  int clientSocket;
  int num_to_decrement;
  char in_buffer[1024], temp_in_buffer[1024], out_buffer[1024];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;
  char *message_format = "%s:%d";
  char message[1024];
  char* key = "decrement";
  char* value = "50";

  do {
    // set up data to send
    num_to_decrement = atoi(value);
    sprintf(message, message_format, key, num_to_decrement);

    // set up socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    createSockaddr_in(&serverAddr, SERVER_PORT, "127.0.0.1");
    printf("%s\n", "before connecting to socket");

    // Connect to socket
    addr_size = sizeof(serverAddr);
    if(connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size) < 0) {
      error("Error connecting\n");
    }
    printf("%s\n", "after connecting to socket");

    strcpy(out_buffer, message);
    int sentBytes = send(clientSocket, out_buffer, sizeof(out_buffer), 0);
    printf("sent %d bytes from %s\n", sentBytes, "client");
    if (sentBytes == -1) {
      printf("error: %s\n", strerror(errno));
    }

    printf("client just sent: ");
    printf(message_format, key, num_to_decrement);
    printf("\n");

    // read from host
    recv(clientSocket, in_buffer, 1024, 0);

    strncpy(temp_in_buffer, in_buffer, 1024);

    printf("Data received from server: '%s'\n", in_buffer);
    printf("temp data: '%s'\n", temp_in_buffer);

    handleRequest(clientSocket, in_buffer, "client");
    setKeyValue(&key, &value, temp_in_buffer);

    //printf("(client.c): key: %s, value: %s\n", key, value);
    int shutdownStatus = close(clientSocket);
    printf("(client.c) Closed socket: %d, with status: %d\n", clientSocket, shutdownStatus);
    usleep(50000);
  } while(true);
  

  return 0;
}
