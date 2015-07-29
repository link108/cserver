#ifndef __utils_h
#define __utils_h

void createSockaddr_in(struct sockaddr_in*, int, char*);

void handleRequest(int, char[], char*);

void sendData(int, char*, char*, char*);

void setKeyValue(char**, char**, char[]);

void processKeyValue(char**, char**, char**, char**, char*);

#endif

