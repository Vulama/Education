#define _XOPEN_SOURCE
#define _XOPEN_SOURCE_EXTENDED

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>
#include <time.h>

int pid=0;

void prekidna_rutina(int sig){
   kill(pid,SIGKILL);
   exit(0);
}

int main(int argc, char *argv[]){
   pid=atoi(argv[1]);
   sigset(SIGINT, prekidna_rutina);

   while(1){
    srand(time(NULL));  
    int r = rand()%3+3; 
    sleep(r);
    r = rand()%4;

    if(r==0) r=10;
    else if(r==1) r=12;
    else if(r==2) r=14;
    else r=25;

    kill(pid,r);

   }
   return 0;
}