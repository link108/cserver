// by cmotevasselani

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include "logger.h"

void logMsg(struct Logger * log, int logLevel, char * msg) {
  if (logLevel <= log->logLevel) {
    char temp[128];
    if (strlen(msg) < 128) {
      int strLen = strlen(msg);
      strncpy(temp, msg, strlen(msg));
      temp[strLen] = '\n';
      temp[strLen + 1] = '\0';
      //printf("%s: %s\n", log->name, log->msgs[log->numMsgs]);
      write(log->logFd, temp, strlen(temp));
      //write(log->logFd, "\n", strlen("\n"));
      log->numMsgs++;
    }
  }
}

struct Logger * createLogger(char * name, enum LogLevel logLevel) {
  struct Logger * logger = malloc(sizeof(struct Logger));
  logger->name = malloc(strlen(name));
  logger->name = malloc(strlen(name) + strlen(LOG_EXT) + 1);
  strncpy(logger->name, name, strlen(name));
  strncat(logger->name, LOG_EXT, strlen(LOG_EXT));
  logger->logFd = open(logger->name, O_RDWR | O_CREAT | O_APPEND, 0644);
  if (-1 == logger->logFd) {
    printf("failed opening %s\n", logger->name);
    perror("");
    return NULL;
  }
  logger->logLevel = logLevel;
  logger->numMsgs = 0;
  logger->msgs = malloc(sizeof(char *) * 1024);
  for (int i=0; i < 1024; i++) {
    logger->msgs[i] = malloc(sizeof(char) * 128);
  }
  return logger;
}

