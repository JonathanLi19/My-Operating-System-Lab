#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include <sys/types.h>
#include <fcntl.h>

int main()
{

    int fd[2];
    char buffer[1024];
    int old_stdout = dup(1);
    pipe(fd);
    dup2(fd[1], 1);
    system("ls");
    int size=read(fd[0],buffer,1024);
    dup2(old_stdout, 1);
    printf("I read %d bytes from the process forked from system\n",size);
    printf("%s\n", buffer);
}