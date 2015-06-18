// by cmotevasselani
// Basic test server
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main() {
  static const int SERVER_PORT = 7891;
  int welcomeSocket, newSocket;
  char out_buffer[1024], in_buffer[1024];
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;

  // set up socket, call to socket returns a file descriptor (fd)
  welcomeSocket = socket(AF_INET, SOCK_STREAM, 0);

  // set up serverAddr struct
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(SERVER_PORT);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));
  bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  do {

    // max 5 connections... however only prints "Error!" if hits the limit
    if(listen(welcomeSocket, 5) == 0) {
      printf("Listening\n");
     } else {
       printf("Error!\n");
     }

    // accept connection 
    addr_size = sizeof(serverStorage);
    newSocket = accept(welcomeSocket, (struct sockaddr *) &serverAddr, &addr_size);

    recv(newSocket, in_buffer, 1024, 0);
    printf("sizeof(in_buffer): %lu\n", sizeof(in_buffer));
    printf("strlen(buffer): %lu\n", strlen(in_buffer));
    in_buffer[strlen(in_buffer) - 1] = '\0';
    printf("strlen(buffer) after adding null: %lu\n", strlen(in_buffer));
    printf("received: %s from client\n", in_buffer);


    // send message to socket 
    strcpy(out_buffer, "Hello World\n");
    send(newSocket, out_buffer, sizeof(out_buffer), 0);
  } while(true);




  return 0;
}
