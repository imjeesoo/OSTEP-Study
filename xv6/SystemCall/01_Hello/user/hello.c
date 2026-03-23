#include "kernel/types.h"
#include "user/user.h"

int main(int argc,char* argv[])
{
    int re = hello();
    printf("hello() returned %d\n",re);
    exit(0);
}
