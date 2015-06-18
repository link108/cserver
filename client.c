// by cmotevasselani
// Basic test client
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<errno.h>

void error(const char* msg) {
  perror(msg);
}

int main() {
  static const int SERVER_PORT = 7891;
  int clientSocket;
  int num_to_decrement = 500;
  char in_buffer[1024], out_buffer[1024];
  struct sockaddr_in serverAddr;
  socklen_t addr_size;
  char *message_format = "decrement:%d\n";
  char message[1024];

  // set up data to send
  sprintf(message, message_format, num_to_decrement);
  printf(message_format, num_to_decrement);


  // set up socket
  clientSocket = socket(AF_INET, SOCK_STREAM, 0);

  // set up serverAddr struct
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(SERVER_PORT);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof(serverAddr.sin_zero));

  // Connect to socket
  addr_size = sizeof(serverAddr);
  if(connect(clientSocket, (struct sockaddr *) &serverAddr, addr_size) < 0) {
    error("Error connecting");
  }

  strcpy(out_buffer, message);
  send(clientSocket, out_buffer, sizeof(out_buffer), 0);

  // read from host
  recv(clientSocket, in_buffer, 1024, 0);

  printf("Data received from server: '%s'\n", in_buffer);



  return 0;
}
