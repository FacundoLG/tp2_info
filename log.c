#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "log.h"

int log_ = 1;
int err_ = 1;

HANDLE hconsole(){
    static HANDLE console;
    return console = GetStdHandle(STD_OUTPUT_HANDLE);
}

void printErr(char * message){
    if(!err_) return;
    SetConsoleTextAttribute(hconsole(),RED);
    printf("[ERROR] %s\n",message);
    SetConsoleTextAttribute(hconsole(),WHITE);
}
void printLog(char * message,int success){
    if(!log_) return;
    if(success)  SetConsoleTextAttribute(hconsole(),GREEN);
    printf("[LOG] %s\n",message);
    SetConsoleTextAttribute(hconsole(),WHITE);
}

void printMessage(char * message){
    SetConsoleTextAttribute(hconsole(),CYAN);
    printf("%s",message);
    SetConsoleTextAttribute(hconsole(),WHITE);
}
