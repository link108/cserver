// by cmotevasselani
// Basic test server
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>



void handle_request(int socket, char* key, char* value) {
  char out_buffer[1024];
  if (!strcmp(key, "decrement")) {
    char* message_format = "you just sent: %d";
    sprintf(out_buffer, message_format, atoi(value));
    printf("outbuff: %s", out_buffer);
    // why is atoi bad and how to fix? strtol was not working with: (int)strtol(value, .., 10)
    printf("value as int: %d\n", atoi(value));
  } else {
    //strcpy(out_buffer, "Hello World\n");
    sprintf(out_buffer, "Hello World");
  }
  send(socket, out_buffer, sizeof(out_buffer), 0);
}





void intHandler(int handle_this) {
  close(7891);
  exit(0);
}

int main() {
  static const int SERVER_PORT = 7891;
  int welcomeSocket, newSocket;
  char out_buffer[1024], in_buffer[1024];
  struct sockaddr_in serverAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size;


  signal(SIGINT, intHandler);
  // set up socket, call to socket returns a file descriptor (fd)
  welcomeSocket = socket(AF_INET, SOCK_STREAM, 0);

  // TODO: Pull this into a separate file
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
    // receive data
    recv(newSocket, in_buffer, 1024, 0);

    int colon_pos;
    char* value;
    char* key;

    in_buffer[strlen(in_buffer) - 1] = '\0';
    printf("received: '%s' from client\n", in_buffer);

    colon_pos = (int)(strchr(in_buffer, ':') - in_buffer);
    in_buffer[colon_pos] = '\0';
    key = &in_buffer[0];
    value = &in_buffer[colon_pos + 1];
    handle_request(newSocket, key, value);

  } while(true);




  return 0;
}






