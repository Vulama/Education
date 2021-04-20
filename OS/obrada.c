#define _XOPEN_SOURCE
#define _XOPEN_SOURCE_EXTENDED

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>
 
#define N 6
 
int OZNAKA_CEKANJA[N];
int PRIORITET[N];
int TEKUCI_PRIORITET;
 
void ispis(int i, char x);
 
int sig[]={SIGUSR1, SIGUSR2, SIGALRM, SIGXFSZ , SIGINT};
void zabrani_prekidanje(){
   int i;
   for(i=0; i<5; i++)
      sighold(sig[i]);
}
void dozvoli_prekidanje(){
   int i;
   for(i=0; i<5; i++)
      sigrelse(sig[i]);
}
 
void obrada_signala(int i){
    ispis(i,'P');
    for (int j = 1; j < 6; j++)
    {
        ispis(i,j+'0');
        sleep(1);
    }
    ispis(i,'K');
}
void prekidna_rutina(int sig){
   int n=-1;
   zabrani_prekidanje();
   switch(sig){
        case SIGUSR1: 
            n=1; 
            printf("- X - - - -\n");
            break;
        case SIGUSR2: 
            n=2; 
            printf("- - X - - -\n");
            break;
        case SIGALRM: 
            n=3; 
            printf("- - - X - -\n");
            break;
        case SIGXFSZ: 
            n=4; 
            printf("- - - - X -\n");
            break;
        case SIGINT: 
            n=5; 
            printf("- - - - - X\n");
            break;
         break;
      
   }
   OZNAKA_CEKANJA[n]++;
   int x;

   do{
      /* odredi signal najveceg prioriteta koji ceka na obradu */
      x = 0;
      for(int j=TEKUCI_PRIORITET+1; j<N; j++){
          if(OZNAKA_CEKANJA[j]!=0){
              x=j;
          }
      }
      /* ako postoji signal koji ceka i prioritetniji je od trenutnog posla, idi u obradu */
      if(x > 0){
         OZNAKA_CEKANJA[x] = 0;
         PRIORITET[x] = TEKUCI_PRIORITET;
         TEKUCI_PRIORITET = x;
         dozvoli_prekidanje();
         obrada_signala(x);
         zabrani_prekidanje();
         TEKUCI_PRIORITET = PRIORITET[x];
      }
   }while(x > 0);
}

void ispis(int i, char x){
    char niz[]={'-',' ','-',' ','-',' ','-',' ','-',' ','-','\0'};
    niz[i*2]=x;
    printf("%s\n", niz);
    fflush(stdout);
}
 
int main(void)
{
   sigset (SIGUSR1, prekidna_rutina);
   sigset (SIGUSR2, prekidna_rutina);
   sigset (SIGALRM, prekidna_rutina);
   sigset (SIGXFSZ, prekidna_rutina);
   sigset (SIGINT, prekidna_rutina);
 
   printf("Proces obrade prekida, PID=%d\n", getpid());
   printf("G 1 2 3 4 5\n");
   printf("-----------\n");
   for(int i=0; i<100; i++){
       ispis(0,i%10+1+'0');
       sleep(1);
   }
 
   printf ("Zavrsio osnovni program\n");
   return 0;
}