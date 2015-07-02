#ifndef _utils_h
#define _utils_h

void createSockaddr_in(struct sockaddr_in*, int, char*);

void handle_request(int, char[], char*);

void setKeyValue(char*, char*, char[]);

#endif

