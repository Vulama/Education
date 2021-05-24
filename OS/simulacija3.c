#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int x[50];
int crtica='-'-'0';
int state[10];

int n=0;

void ispis(int r){
    for(int i=0;i<r;i++){
        printf("%d",i%10);
    }
    printf("\n");
    for(int i=0;i<r;i++){
        printf("%c",x[i]+'0');
    }
    
    printf("\n");
}

void ispuna(int r){
    for(int i=0;i<r;i++){
       x[i]=crtica;
    }
}

int provjera(int r){
    int index=-1;
    int duljina=n+1;
    int counter=0;
    for(int i=0;i<n;i++){
        while(x[i]==crtica){
            counter++;
            i++;
        }
        if(counter<duljina && counter>=r){
            duljina=counter;
            index=i-counter;
        }
        counter=0;
    }
    return index;
}

int popuni(int index, int r, int counter){
   for(int i=0;i<r;i++){
       x[index+i]=counter;
   }
}

void prazni(int o){
    int token=0;
    for(int i=0;i<n;i++){
        if(x[i]==o){
            x[i]=crtica;
            token=1;
        }
    }
    if(!token) printf("Ne postoji traženi zahtjev\n");
}

int main(){
    int counter=0;
    srand(time(NULL));
    int r = rand()%20+30;
    n=r;
    ispuna(n);
    printf("%d\n",r);
    ispis(n);
    
    for(int i=0;i<20;i++){
        sleep(2);
        int temp=0;
        scanf("%d",&temp);
        if(temp==0){
            int token=0;
            for(int i=0;i<10;i++){
                if(state[i]==0){
                    token=1;
                    break;
                }
            }
            if(token==1){
                r=rand()%5+1;
                counter=0;
                while(state[counter]!=0) counter++;
                state[counter]=1;
                printf("Novi zahtjev %d za %d spremničkih mjesta\n",counter,r);
                int index=provjera(r);
                if(index==-1){
                    printf("Nema mjesta\n");
                }
                else{
                    popuni(index, r, counter);
                    counter++;
                }
            }else{
                printf("Svi brojevi su zauzeti...\n");
            }
        }else if(temp==1){
            printf("Koji zahtjev treba osloboditi?\n");
            int oslobodi;
            scanf("%d",&oslobodi);
            state[oslobodi]=0;
            prazni(oslobodi);
        }else{
            printf("Defragmentacija\n");
            int tmp[n];
            int counter=0;
            for(int j=0;j<n;j++){
                if(x[j]!=crtica){
                    tmp[counter]=x[j];
                    counter++;
                }
            }
            for(int j=counter;j<n;j++){
                tmp[j]=crtica;
            }
            for(int j=0;j<n;j++){
                x[j]=tmp[j];
            }
        }
        ispis(n);    
    }
}