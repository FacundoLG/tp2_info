#ifndef LOG_H
#define LOG_H
#include <windows.h>
#define RED 12
#define WHITE 15
#define GREEN 10
#define CYAN 11


void printErr(char * message);
void printLog(char * message,int success);
void printMessage(char * message);
HANDLE hconsole();
#endif // LOG_H
