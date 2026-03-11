//gettimeofday()를 통한 시스템콜 비용측정
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/syscall.h>

int main(int argc, char *argv[]) {

    int n = atoi(argv[1]);
    int i;  

    struct timeval start, end;

    gettimeofday(&start, NULL);

    for (i = 0; i < n; i++) {
        getpid();
    }

    gettimeofday(&end, NULL);

    long sec = end.tv_sec - start.tv_sec;
    long usec = end.tv_usec - start.tv_usec;

    double total = sec * 1000000.0 + usec; 

    printf("average syscall time : %f us\n", total / n);

    return 0;
}

