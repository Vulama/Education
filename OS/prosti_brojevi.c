#define _XOPEN_SOURCE
#define _XOPEN_SOURCE_EXTENDED

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>

int pauza = 0;
int broj = 1000000001;
int zadnji = 1000000001;

void periodicki_ispis(int n) {
    printf("%d\n", zadnji);
}

void postavi_pauzu(int n) {
    pauza = 1 - pauza;
}

void prekini(int n) {
    printf("%d\n", zadnji);
    exit(0);
}
int prost(unsigned long n) {
    unsigned long i, max;

    if((n & 1) == 0)
        return 0;

    max = sqrt(n);
    for(i = 3; i <= max; i += 2)
        if((n % i) == 0)
            return 0;

    return 1;
}

int main() {
    sigset(SIGALRM, periodicki_ispis);
    sigset(SIGINT, postavi_pauzu);
    sigset(SIGTERM, prekini);

    struct itimerval t;

    /* definiranje periodičkog slanja signala */
    /* prvi puta nakon: */
    t.it_value.tv_sec = 0;
    t.it_value.tv_usec = 500000;
    /* nakon prvog puta, periodicki sa periodom: */
    t.it_interval.tv_sec = 0;
    t.it_interval.tv_usec = 500000;

    /* pokretanje sata s pridruženim slanjem signala prema "t" */
    setitimer(ITIMER_REAL, &t, NULL);

    while (1) {
        if(prost(broj))
            zadnji=broj;
        broj++;
        while(pauza) {
            pause();
        }
    }
    return 0;
}