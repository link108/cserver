// by cmotevasselani

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

enum LogLevel {
  INFO = 0,
  WARN,
  DEBUG
};

struct Logger {
  char * name;
  char ** msgs;
  int numMsgs;
  enum LogLevel logLevel;
};

void logMsg(struct Logger * log, int logLevel, char * msg) {
  if (logLevel <= log->logLevel) {
    if (strlen(msg) < 128) {
      strcpy(log->msgs[log->numMsgs], msg);
      printf("%s: %s\n", log->name, log->msgs[log->numMsgs]);
      log->numMsgs++;
    }
  }
}

struct Logger * createLogger(char * name, enum LogLevel logLevel) {
  struct Logger * logger = malloc(sizeof(struct Logger));
  logger->name = malloc(strlen(name));
  logger->name = name;
  logger->logLevel = logLevel;
  logger->numMsgs = 0;
  logger->msgs = malloc(sizeof(char *) * 1024);
  for (int i=0; i < 1024; i++) {
    logger->msgs[i] = malloc(sizeof(char) * 128);
  }
  return logger;
}

int main() {
  struct Logger * logger = createLogger("simpleLogger", INFO);
  logMsg(logger, WARN, "msg");
  logMsg(logger, INFO, "msg1");
  logMsg(logger, DEBUG, "msg2");
  return 0;
}
