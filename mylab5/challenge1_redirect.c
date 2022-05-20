#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include<fcntl.h>
/*#define MSGSIZE 16

char *msg1 = "Hello, world #1";
char *msg2 = "Hello, world #2";
char *msg3 = "Hello, world #3";

int main(void)
{
    char inbuf[MSGSIZE];

    int p[2];

    int j, pid;

    if (pipe(&p[0]) < 0)
    {
        printf("pipe call error!\n");
        exit(1);
    } else {
        if ((pid = fork()) < 0) 
        {
            printf("fork call error!\n");
            exit(2);
        }

        if (pid > 0)
        {
            close(p[0]);
            write(p[1], msg1, MSGSIZE);
            printf("Sender: %s \n", msg1);
            sleep(1);
            write(p[1], msg2, MSGSIZE);
            printf("Sender: %s \n", msg2);
            sleep(2);
            write(p[1], msg3, MSGSIZE);
            printf("Sender: %s \n", msg3);
            wait((int *) 0);
        }

        if (pid == 0)
        {
            close(p[1]);
            for (j = 0; j < 3; j++)
            {
                read(p[0], inbuf, MSGSIZE);
                printf("%s \n", inbuf);
            }
        }

    }

    return 0;

}*/
int main()
{
    write(1,"111\n",4);
    close(1);
    open("challenge1.txt",O_RDWR+O_CREAT);
    system("ls");
    return 0;
}