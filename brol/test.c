#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/time.h>

int main()
{
    struct timeval t;
    struct timezone tz;
    long long unsigned int nb;
    gettimeofday(&t, &tz);
    
    nb = t.tv_sec;
    printf("\nminutes =>|%lu|\n", nb);
    usleep(5000000);
    gettimeofday(&t, &tz);
    nb = t.tv_sec;
    printf("\nminutes =>|%lu|\n", nb);
    /*printf("\nfull temps =>|%lu|\n", t.tv_sec);
    printf("\nminutes =>|%lu|\n", t.tv_sec / 60);
    printf("\nheures =>|%lu|\n", (t.tv_sec / 60) / 60);
    printf("\njours =>|%lu|\n", ((t.tv_sec / 60) / 60) / 24);
    printf("\nmois =>|%lu|\n", (((t.tv_sec / 60) / 60) / 24) / 30);
    printf("\nannees =>|%lu|\n", ((((t.tv_sec / 60) / 60) / 24) / 30) / 12);*/
    return (0);
}