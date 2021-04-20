#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int id;
int *counter;

void Proces(int m){
    for(int i = 0; i < m; i++){
        *counter=*counter + 1;
    }
    return;
}

int main(int argc, char *argv[]){
    int n=atoi(argv[1]);
    int m=atoi(argv[2]);
    
    id=shmget(IPC_PRIVATE, sizeof(int), 0600);
    if(id==-1){
        printf("No mem\n");
        exit(1);
    }
    
    counter=(int *) shmat(id, NULL, 0);
    *counter=0;

    if(n>0 && m>0){
        for(int i=0; i < n; i++){
            switch (fork())
            {
            case -1:
                printf("Fail");
                break;
            case 0:
                Proces(m);
                exit(0);
            default:
                break;
            }
        }
        Proces(0);
        for(int i=0; i < n; i++){
            wait(NULL);
        }
        printf("A=%d\n",*counter);

        shmctl(id,IPC_RMID, NULL);
    }else{
        printf("Neispravan upis\n");
    }
    return 0;
}