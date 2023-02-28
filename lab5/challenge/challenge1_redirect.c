#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include<fcntl.h>
int main()
{
    write(1,"111\n",4);
    close(1);
    open("challenge1.txt",O_RDWR+O_CREAT);
    system("ls");
    return 0;
}