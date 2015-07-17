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
  static const int SERVER_PORT = 7891;
  int clientSocket;
  int num_to_decrement;
  char in_buffer[1024], out_buffer[1024];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;
  char *message_format = "%s:%d";
  char message[1024];
  char* key = "decrement";
  char* value = "500";

  do {
    // set up data to send
    num_to_decrement = atoi(value);
    sprintf(message, message_format, key, num_to_decrement);
    printf("client just sent: ");
    printf(message_format, key, num_to_decrement);
    printf("\n");

    // set up socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    createSockaddr_in(&serverAddr, SERVER_PORT, "127.0.0.1");


    // Connect to socket
    addr_size = sizeof(serverAddr);
    if(connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size) < 0) {
      error("Error connecting\n");
    }

    strcpy(out_buffer, message);
    send(clientSocket, out_buffer, sizeof(out_buffer), 0);

    // read from host
    recv(clientSocket, in_buffer, 1024, 0);


    printf("Data received from server: '%s'\n", in_buffer);

    int colon_pos = (int)(strchr(in_buffer, ':') - in_buffer);
    in_buffer[colon_pos] = '\0';
    key = &in_buffer[0];
    value = &in_buffer[colon_pos + 1];

    //printf("Key received from server: '%s'\n", key);
    //printf("Value received from server: '%s'\n", value);
    //setKeyValue(key, value, in_buffer);

    //int shutdownStatus = shutdown(clientSocket, 0);
    int shutdownStatus = close(clientSocket);
    printf("Closed socket: %d, with status: %d\n", clientSocket, shutdownStatus);
    usleep(50000);
  } while(true);
  

  return 0;
}
