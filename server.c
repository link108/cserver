// by cmotevasselani
// Basic test server

// TODO what to replace stdio with? 

#include<unistd.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<signal.h>
#include<errno.h>
#include "utils.h"
#include<signal.h>

static volatile int keepRunning = 1;
int welcomeSocket;

// dont think this does what I intend it to do.. close the port
void intHandler(int handle_this) {
  keepRunning = 0;
  printf("closing: %d\n", welcomeSocket);
  close(welcomeSocket);
  exit(0);
}

int main() {
  static const int SERVER_PORT = 7892;
  //int welcomeSocket;
  char in_buffer[1024];
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;

  // set up socket, call to socket returns a file descriptor (fd)
  welcomeSocket = socket(AF_INET, SOCK_STREAM, 0);
  signal(SIGINT, intHandler);

  createSockaddr_in(&serverAddr, SERVER_PORT, "127.0.0.1");
  int bindStatus = bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
  if (bindStatus != 0) {
    printf("bind error: %s\n", strerror(errno));
    exit(0);
  }

  do {
    // max 5 connections... however only prints "Error!" if hits the limit
    int listenWelcomeSocket = listen(welcomeSocket, 5);
    //if(listen(welcomeSocket, 5) == 0) {
    if(listenWelcomeSocket == 0) {
      printf("Server Listening\n");
      printf("welcomeSocket output: %d\n", listenWelcomeSocket);
     } else {
       printf("Error!\n");
     }

    // accept connection 
    addr_size = sizeof(serverStorage);
    int newSocket = accept(welcomeSocket, (struct sockaddr *) &serverAddr, &addr_size);
    printf("Accepted new socket: %d\n", newSocket);
    // receive data
    int recvBytes = recv(newSocket, in_buffer, 1024, 0);
    printf("Received: '%s' from client\n", in_buffer);
    printf("Received: %d bytes from client\n", recvBytes);

    handleRequest(newSocket, in_buffer, "Server");
    //int shutdownStatus = shutdown(newSocket, 0);
    int shutdownStatus = close(newSocket);
    printf("(server.c) Closed socket: %d, with status: %d\n", newSocket, shutdownStatus);
    usleep(50000);

  } while(true);
  int shutdownStatus = close(welcomeSocket);
  printf("(server.c) Closed socket: %d, with status: %d\n", welcomeSocket, shutdownStatus);

  return 0;
}
