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
#include "logger.c"

void error(const char* msg) {
  perror(msg);
}

enum LogLevel LOG_LEVEL = INFO;
static struct Logger * clientLogger;

void cLog(char * msg) {
  logMsg(clientLogger, LOG_LEVEL, msg);
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
  clientLogger = createLogger(__FILE__, LOG_LEVEL);
  //char* log_msg = malloc(sizeof(char) * 128);

  do {
    //memset(in_buffer, 0, 1024);
    //memset(temp_in_buffer, 0, 1024);
    // set up data to send
    num_to_decrement = atoi(value);
    sprintf(message, message_format, key, num_to_decrement);

    // set up socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    createSockaddr_in(&serverAddr, SERVER_PORT, "127.0.0.1");
    printf("%s\n", "before connecting to socket");
    cLog("before connecting to socket");

    // Connect to socket
    addr_size = sizeof(serverAddr);
    if(connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size) < 0) {
      error("Error connecting\n");
    }
    cLog("after connecting to socket");
    printf("%s\n", "after connecting to socket");

    strcpy(out_buffer, message);
    int sentBytes = send(clientSocket, out_buffer, sizeof(out_buffer), 0);
    printf("sent %d bytes from %s\n", sentBytes, "client");
    //sprintf(log_msg, "sent %d bytes from %s\n", sentBytes, "client");
    //cLog(log_msg);
    if (sentBytes == -1) {
      error("");
      printf("error: %s\n", strerror(errno));
      cLog("failed to send");
    } else {
      cLog("succeeded in sending");
    }

    printf("client just sent: ");
    //sprintf(log_msg, message_format, key, num_to_decrement);
    //cLog(log_msg);
    //printf("\n");

    // read from host
    recv(clientSocket, in_buffer, 1024, 0);

    strncpy(temp_in_buffer, in_buffer, 1024);

    cLog("received data from sever");
    printf("Data received from server: '%s'\n", in_buffer);
    //sprintf(log_msg, "Data received from server: '%s'\n", in_buffer);
    //cLog(log_msg);
    printf("temp data: '%s'\n", temp_in_buffer);
    //sprintf(log_msg, "temp data: '%s'\n", temp_in_buffer);
    //cLog(log_msg);

    handleRequest(clientSocket, in_buffer, "client");
    setKeyValue(&key, &value, temp_in_buffer);

    //printf("(client.c): key: %s, value: %s\n", key, value);
    int shutdownStatus = close(clientSocket);
    //sprintf(log_msg, "(client.c) Closed socket: %d, with status: %d\n", clientSocket, shutdownStatus);
    //cLog(log_msg);
    usleep(50000);
  } while(true);
  

  return 0;
}
