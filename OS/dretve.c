#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int counter;

void *dretva (void *x){
    int *iterator = x;
    for (int i=0; i < *iterator; i++){
        counter++;
    }
    return 0;
}

int main(int argc, char *argv[]){
    counter=0;
    int n=atoi(argv[1]);
    int m=atoi(argv[2]);
    if(n>0 && m>0){
        int BR[n];
        pthread_t t[n];
        for(int i=0; i<n; i++){
            BR[i]=m;
            if(pthread_create(&t[i], NULL, dretva, &BR[i])){
                exit(1);
            }
        }
        for(int i=0; i<n; i++){
            pthread_join(t[i], NULL);
        }
        printf("A=%d\n",counter);
    }else{
        printf("Neispravan upis\n");
    }
    return 0;
}