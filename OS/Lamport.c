#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdatomic.h>

atomic_int *ULAZ, *BROJ;

int counter;
int n, m;

void *dretva (void *x){
    for(int j=0;j<m;j++){
        int *i = x;
        ULAZ[*i]=1;
        int max=BROJ[0];
        for(int j=1; j<n; j++){
            if(max<BROJ[j]) max=BROJ[j];
        }
        BROJ[*i]=max+1;
        ULAZ[*i]=0;

        for(int j=0;j<n;j++){
            while(ULAZ[j]!=0){
                ;
            }
            while(BROJ[j] != 0 && (BROJ[j]<BROJ[*i] || (BROJ[j] == BROJ[*i] && j<*i))){
                ;
            }
        }
        
        counter++;
        
        BROJ[*i]=0;
    }
    return 0;
}

int main(int argc, char *argv[]){
    counter=0;
    n=atoi(argv[1]);
    m=atoi(argv[2]);

    ULAZ=(atomic_int *)malloc (n * sizeof(atomic_int));
    BROJ=(atomic_int *)malloc (n * sizeof(atomic_int));

    if(n>0 && m>0){
        int BR[n];
        pthread_t t[n];
        for(int i=0; i<n; i++){
            BR[i]=i;
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