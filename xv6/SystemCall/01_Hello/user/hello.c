#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc,char* argv[]){
    int ret = hello();
    printf("hello() returned %d\n", ret);
    exit(0);
}
