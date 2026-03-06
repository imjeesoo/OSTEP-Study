//실험 목적 : 파일디스크립터에 대해 이해하고, close()와 open()을 통해 표준출력(stdout, fd1) 파일을 redirection 해본다. 
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(){ 
    pid_t rc;
    rc = fork(); 
    if (rc == 0) { 
        close(1);
        open("test.txt",O_CREAT|O_TRUNC|O_WRONLY,0644); //가장 낮은 번호의 fd번호부터 할당 되므로 close한 fd1번을 할당받을것으로 예측.
        printf("hello!\n");
        exit(3);
    }
return 0;
}

//결과 : 
